#include "gpio.h"
#include <stdio.h>
#include "aos/kernel.h"
#include "aos/yloop.h"
#include "bsp_board.h"
#include "esp_common.h"
#include "aos/hal/gpio.h"
#include "aos/hal/uart.h"
#include "driver/uart.h"
#include "fly_queue.h"

#define WIFI_LED_GPIO_NUM        2
#define WIFI_LED_GPIO_PIN        GPIO_Pin_2
#define WIFI_LED_GPIO_MODE       GPIO_Mode_Output
#define WIFI_LED_GPIO_PULLUP     GPIO_PullUp_DIS //GPIO_PullUp_DIS
#define WIFI_LED_GPIO_INTRTYPE   GPIO_PIN_INTR_DISABLE

#define LED_GPIO_NUM             12
#define LED_GPIO_PIN             GPIO_Pin_12
#define LED_GPIO_MODE            GPIO_Mode_Output
#define LED_GPIO_PULLUP          GPIO_PullUp_EN //GPIO_PullUp_DIS
#define LED_GPIO_INTRTYPE        GPIO_PIN_INTR_DISABLE

uint32_t    recv_size = 0;
uint32_t    send_size = 0;
uint8_t     serial_bytes[100];

uart_dev_t  uart;
fly_key_write_t fly_key_write;
fly_curtain_ctrl_t fly_curtain_ctrl;

void wifi_key_init(void)
{
    gpio16_input_conf();
}

uint32_t wifi_key_state_func(void)
{
    return gpio16_input_get();
}

void wifi_led_init(void)
{
    GPIO_ConfigTypeDef led_gpio_cnf;
    led_gpio_cnf.GPIO_Pin = WIFI_LED_GPIO_PIN;
    led_gpio_cnf.GPIO_Mode = WIFI_LED_GPIO_MODE;
    led_gpio_cnf.GPIO_Pullup = WIFI_LED_GPIO_PULLUP;
    led_gpio_cnf.GPIO_IntrType = WIFI_LED_GPIO_INTRTYPE;
    gpio_config(&led_gpio_cnf);
}

uint32_t wifi_led_state_func(void)
{
    return (gpio_input_get() & 0x01<<WIFI_LED_GPIO_NUM) >> WIFI_LED_GPIO_NUM;
}

void wifi_led_config_func(uint8_t state)
{
    
    if(state == 0)          // off led
    {
        gpio_output_conf(0, WIFI_LED_GPIO_PIN, WIFI_LED_GPIO_PIN, 0);
    }
    else if(state == 1)      //on led
    {
        gpio_output_conf(WIFI_LED_GPIO_PIN, 0, WIFI_LED_GPIO_PIN, 0);
    }
    else if(state == 3)     //toggle led
    {
        if(wifi_led_state_func())    //if get 1,off led
        {
            gpio_output_conf(0, WIFI_LED_GPIO_PIN, WIFI_LED_GPIO_PIN, 0);
        }
        else                        //if get 0,on led
        {
            gpio_output_conf(WIFI_LED_GPIO_PIN, 0, WIFI_LED_GPIO_PIN, 0);
        }
    }
    else                            //other state,off led
    {
        gpio_output_conf(0, WIFI_LED_GPIO_PIN, WIFI_LED_GPIO_PIN, 0);
    }

}

static  uint32_t calc_crc(uint8_t crcbuf, uint32_t crc)
{
    uint8_t i;
    uint8_t chk;
    crc = crc ^ crcbuf;
    for (i = 0; i < 8; i++)
    {
        chk = crc & 1;
        crc = crc >> 1;
        crc = crc & 0x7fff;
        if (chk == 1)
            crc = crc ^ 0xa001;
        crc = crc & 0xffff;
    }
    return crc;
}


uint32_t data_crc16_check(uint32_t crc, uint8_t *buf, uint32_t len)
{
    uint8_t hi, lo;
    uint32_t i;
    for (i = 0; i < len; i++)
    {
        crc = calc_crc(*buf, crc);
        buf++;
    }
    hi = crc % 256;
    lo = crc / 256;
    crc = (hi << 8) | lo;
    return crc;
}

uint32_t data_add_check( uint8_t *buf, uint32_t len)
{
    uint32_t i;
    uint32_t crc = 0;
    for (i = 0; i < len; i++)
    {
        crc +=  buf[i];
    }

    return crc;
}

uint8_t serial_init(void)
{
    uart_config_t uartConfig;
    uartConfig.baud_rate = 9600; 
    //for esp8266 , when the port set is 1 ,
    //then the uart1 ande uart2 is the same baud_rate , but the uart1 is for log 
    uart.port = 1;                  
    uart.config = uartConfig;
    //hal_uart_init_I(&uart);
    hal_uart_init(&uart);
}

//for curtain control
//1:write key
//2:control curtain
uint8_t serial_receive_handler(uint8_t serialType)
{
    int8_t ret;
    uint8_t result = 0;

    uint8_t i=0;
    uint32_t tempCrc = 0;
    
    recv_size = 0;
    ETS_UART_INTR_DISABLE();
    //ret = hal_uart_recv_I(&uart, serial_bytes, 100, &recv_size, HAL_WAIT_FOREVER);
    ret = hal_uart_recv_II(&uart, serial_bytes, 100, &recv_size, HAL_WAIT_FOREVER);
    ETS_UART_INTR_ENABLE();
    if ((ret == 0) && (recv_size>0))
    {        
        if(serialType == 1)
        {
            if((recv_size>=2) && (serial_bytes[recv_size-2] == 0x0D) && (serial_bytes[recv_size-1] == 0x0A))
            {               
                tempCrc = data_add_check(serial_bytes,recv_size-4);
                if(tempCrc == ((serial_bytes[recv_size-4]<<8)+(serial_bytes[recv_size-3])))
                {   
                    memcpy((fly_key_write.payload),serial_bytes,recv_size-4);
                    result = 1;
                }
                else
                {
                    result = 2;
                }
            }
            else
            {
                result = 2;
            }
        }
        else if(serialType == 2)
        {
            tempCrc = data_crc16_check(CURTAIN_CHECK_CRC,serial_bytes,recv_size-2);
            if(tempCrc == (serial_bytes[recv_size-3] <<8 + serial_bytes[recv_size-2]))
            {
                memcpy(&(fly_curtain_ctrl.startCode),serial_bytes,recv_size-2);
                result = 1;
            }
            else
            {
                result = 2;
            }
        }
    }

    return result;   
}

uint8_t serial_send_handler(uint8_t serialType,uint8_t datLen,uint8_t *dataSend)
{
    uint8_t result = 0;
    uint8_t i = 0;
    uint32_t tempCrc = 0;
    if(serialType == 1)
    {
        for(i=0;i<datLen;i++)
        {
            fly_key_write.payload[i] = dataSend[i];
        }
        tempCrc = data_add_check(fly_key_write.payload,2);
        fly_key_write.checkSumH = (uint8_t)((tempCrc>>8)&0xff);
        fly_key_write.checkSumL = (uint8_t)((tempCrc)&0xff);
        fly_key_write.finishCode1 = 0x0D;
        fly_key_write.finishCode2 = 0x0A;
        hal_uart_send(&uart,fly_key_write.payload,datLen,1000);
        hal_uart_send(&uart,&(fly_key_write.checkSumH),4,1000);
        result = 1;
    }
    else if(serialType == 2)
    {
        if(datLen<2)
        {
            result = 0;
        }       
        else
        {
            fly_curtain_ctrl.startCode = CURTAIN_START_CODE;
            fly_curtain_ctrl.devAddrH = (uint8_t)((CURTAIN_ID>>8)&0xFF);
            fly_curtain_ctrl.devAddrL = (uint8_t)(CURTAIN_ID&0xFF);
            fly_curtain_ctrl.ctrlCode = dataSend[0];

            for(i = 0; i < (datLen-1); i++)
            {
                fly_curtain_ctrl.payload[i] = dataSend[i+1];
            }

            tempCrc = data_crc16_check(CURTAIN_CHECK_CRC,&(fly_curtain_ctrl.startCode),datLen+3);
            fly_curtain_ctrl.checkSumH = (uint8_t)((tempCrc>>8)&0xFF);
            fly_curtain_ctrl.checkSumL = (uint8_t)((tempCrc)&0xFF);

            hal_uart_send(&uart,&(fly_curtain_ctrl.startCode),datLen+3,1000);
            hal_uart_send(&uart,&(fly_curtain_ctrl.checkSumH),2,1000);

            result = 1;
        }
    }
    
    return result;
}