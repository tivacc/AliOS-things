
#include "espressif/esp_common.h"
#include "gpio.h"
#include <stdio.h>
#include "aos/kernel.h"
#include "aos/yloop.h"
#include "bsp_board.h"

#define WIFI_LED_GPIO_PIN        GPIO_Pin_2
#define WIFI_LED_GPIO_MODE       GPIO_Mode_Output
#define WIFI_LED_GPIO_PULLUP     GPIO_PullUp_DIS //GPIO_PullUp_DIS
#define WIFI_LED_GPIO_INTRTYPE   GPIO_PIN_INTR_DISABLE

#define LED_GPIO_PIN             GPIO_Pin_12
#define LED_GPIO_MODE            GPIO_Mode_Output
#define LED_GPIO_PULLUP          GPIO_PullUp_EN //GPIO_PullUp_DIS
#define LED_GPIO_INTRTYPE        GPIO_PIN_INTR_DISABLE

#if DEVICE_SUPPORT_SUBG == 1
#define KEY1_GPIO_PIN            GPIO_Pin_14
#define KEY1_GPIO_MODE           GPIO_Mode_Output
#define KEY1_GPIO_PULLUP         GPIO_PullUp_EN //GPIO_PullUp_DIS
#define KEY1_GPIO_INTRTYPE       GPIO_PIN_INTR_DISABLE //GPIO_PIN_INTR_NEGEDGE

#define KEY2_GPIO_PIN            GPIO_Pin_13
#define KEY2_GPIO_MODE           GPIO_Mode_Input
#define KEY2_GPIO_PULLUP         GPIO_PullUp_EN //GPIO_PullUp_DIS
#define KEY2_GPIO_INTRTYPE       GPIO_PIN_INTR_DISABLE


#define WIRE_DATAM_GPIO_PIN      GPIO_Pin_4
#define WIRE_DATAM_GPIO_NO       4
#define WIRE_DATAM_GPIO_MODE     GPIO_Mode_Input
#define WIRE_DATAM_GPIO_PULLUP   GPIO_PullUp_EN //GPIO_PullUp_DIS
#define WIRE_DATAM_GPIO_INTRTYPE GPIO_PIN_INTR_NEGEDGE

#define WIRE_DATAP_GPIO_PIN      GPIO_Pin_5
#define WIRE_DATAP_GPIO_NO       5
#define WIRE_DATAP_GPIO_MODE     GPIO_Mode_Input
#define WIRE_DATAP_GPIO_PULLUP   GPIO_PullUp_EN //GPIO_PullUp_DIS
#define WIRE_DATAP_GPIO_INTRTYPE GPIO_PIN_INTR_NEGEDGE


/*#define WIRE_DATAP_GPIO_PIN      GPIO_Pin_4
#define WIRE_DATAP_GPIO_NO       4
#define WIRE_DATAP_GPIO_MODE     GPIO_Mode_Input
#define WIRE_DATAP_GPIO_PULLUP   GPIO_PullUp_EN //GPIO_PullUp_DIS
#define WIRE_DATAP_GPIO_INTRTYPE GPIO_PIN_INTR_NEGEDGE

#define WIRE_DATAM_GPIO_PIN      GPIO_Pin_5
#define WIRE_DATAM_GPIO_NO       5
#define WIRE_DATAM_GPIO_MODE     GPIO_Mode_Input
#define WIRE_DATAM_GPIO_PULLUP   GPIO_PullUp_EN //GPIO_PullUp_DIS
#define WIRE_DATAM_GPIO_INTRTYPE GPIO_PIN_INTR_NEGEDGE*/
#endif


#if DEVICE_SUPPORT_SUBG == 1
static int keyTempState = 0;
uint32_t wireless_key_state = 0;
#endif

#if DEVICE_SUPPORT_SUBG == 1
//extern api
uint8_t   DataNum;
uint8_t   RevData;
uint8_t   RevTime;
uint8_t   InRfData[5];
uint8_t   LastDat = 0x03;
static uint8_t wireless_key_detcet(void)
{  
    uint8_t num,Dat;
    //S_DP_PIN = D+
    //S_DM_PIN = D-

    //Dat  = S_DP_DM_PIN&S_DP_NO_DAT;
    Dat  = (wire_datap_state_func()<<1) | (wire_datam_state_func());
    //if(Dat != LastDat)
    {
        if(Dat == 0x00)
        {
            DataNum = 0;
            RevData = 0;
            RevTime = 5;//250;   //2ms---250 10ms--50
            InRfData[0] = 0;
            InRfData[1] = 0;
            InRfData[2] = 0;
            InRfData[3] = 0;
            InRfData[4] = 0;
        }
        //else if((Dat == (wire_datap_state_func()<<1))||(Dat == (wire_datam_state_func())))
        else if((Dat == 0x02)||(Dat == 0x01))
        {
            RevData <<= 1;
            RevData |= wire_datap_state_func();//S_DP_PIN;
            
            DataNum++;
            if((DataNum%8)==0)
            {
                num = DataNum/8;
                num = num - 1;
                InRfData[num] = RevData;
                if(num == 4)
                {
                    DataNum = 0;
                    RevData = 0;
                    LastDat = 0x03;//S_DP_NO_DAT;
                    
                    //return 1;
                    keyTempState = 1;
                    wireless_key_state = keyTempState;
                }
            }
        }
        else //0x60
        {
        }
        LastDat = Dat;
    }

    keyTempState = 0;
    //return 0;
}
#endif


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
    return (gpio_input_get() & 0x01<<2) >> 2;
}

void wifi_led_config_func(uint8_t state)
{
    
    if(state == 0) // off led
    {
        gpio_output_conf(0, WIFI_LED_GPIO_PIN, WIFI_LED_GPIO_PIN, 0);
    }
    else if(state == 1)      //on led
    {
        gpio_output_conf(WIFI_LED_GPIO_PIN, 0, WIFI_LED_GPIO_PIN, 0);
    }
    else if(state == 3) //toggle led
    {
        if(wifi_led_state_func())    //if get 1,off led
        {
            gpio_output_conf(0, WIFI_LED_GPIO_PIN, WIFI_LED_GPIO_PIN, 0);
        }
        else                    //if get 0,on led
        {
            gpio_output_conf(WIFI_LED_GPIO_PIN, 0, WIFI_LED_GPIO_PIN, 0);
        }
    }
    else                //other state,off led
    {
        gpio_output_conf(0, WIFI_LED_GPIO_PIN, WIFI_LED_GPIO_PIN, 0);
    }

}

void led_gpio_init(void)
{   
    GPIO_ConfigTypeDef led_gpio_cnf;
    led_gpio_cnf.GPIO_Pin = LED_GPIO_PIN;
    led_gpio_cnf.GPIO_Mode = LED_GPIO_MODE;
    led_gpio_cnf.GPIO_Pullup = LED_GPIO_PULLUP;
    led_gpio_cnf.GPIO_IntrType = LED_GPIO_INTRTYPE;
    gpio_config(&led_gpio_cnf);    
}

uint32_t led_state_func(void)
{
    return ((gpio_input_get() & 0x01<<12) >> 12);
}

void led_config_func(uint8_t state)
{
    
    if(state == 0) // off led
    {
        gpio_output_conf(0, LED_GPIO_PIN, LED_GPIO_PIN, 0);
    }
    else if(state == 1)      //on led
    {
        gpio_output_conf(LED_GPIO_PIN, 0, LED_GPIO_PIN, 0);
    }
    else if(state == 3) //toggle led
    {
        if(led_state_func())    //if get 1,off led
        {
            gpio_output_conf(0, LED_GPIO_PIN, LED_GPIO_PIN, 0);
        }
        else                    //if get 0,on led
        {
            gpio_output_conf(LED_GPIO_PIN, 0, LED_GPIO_PIN, 0);
        }
    }
    else                //other state,off led
    {
        gpio_output_conf(0, LED_GPIO_PIN, LED_GPIO_PIN, 0);
    }

}


#if DEVICE_SUPPORT_SUBG == 1
void wire_gpio_init(void)
{
    GPIO_ConfigTypeDef wire_gpio_cnf;
    wire_gpio_cnf.GPIO_Pin = WIRE_DATAP_GPIO_PIN;
    wire_gpio_cnf.GPIO_Mode = WIRE_DATAP_GPIO_MODE;
    wire_gpio_cnf.GPIO_Pullup = WIRE_DATAP_GPIO_PULLUP;
    wire_gpio_cnf.GPIO_IntrType = WIRE_DATAP_GPIO_INTRTYPE;
    gpio_config(&wire_gpio_cnf);

    wire_gpio_cnf.GPIO_Pin = WIRE_DATAM_GPIO_PIN;
    wire_gpio_cnf.GPIO_Mode = WIRE_DATAM_GPIO_MODE;
    wire_gpio_cnf.GPIO_Pullup = WIRE_DATAM_GPIO_PULLUP;
    wire_gpio_cnf.GPIO_IntrType = WIRE_DATAM_GPIO_INTRTYPE;
    gpio_config(&wire_gpio_cnf);
}

static void fly_gpio4_isr_handler()
{
    //uint32_t level = GPIO_INPUT_GET(WIRE_DATAM_GPIO_NO);
    //if(level == 0) 
    {
        printf("test p1.\n");
        //wireless_key_detcet();
    }
}

static void fly_gpio5_isr_handler()
{
    //uint32_t level = GPIO_INPUT_GET(WIRE_DATAP_GPIO_NO);
    //if (level == 0) 
    {
        printf("test p2.\n");
        //wireless_key_detcet();
    }
}

static void wire_gpio_isr(void *arg)
{
    uint32_t gpio_status = GPIO_REG_READ(GPIO_STATUS_ADDRESS);

    GPIO_REG_WRITE(GPIO_STATUS_W1TC_ADDRESS, gpio_status);

    if ((gpio_status & (1 << WIRE_DATAM_GPIO_NO)) || (gpio_status & (1 << WIRE_DATAP_GPIO_NO)))
    {
        wireless_key_detcet();
    }
    /*
    {
        fly_gpio4_isr_handler();
    }
    else if (gpio_status & (1 << WIRE_DATAP_GPIO_NO))
    {
        fly_gpio5_isr_handler();
    }
    else
    {
        ;
    }
    */
}

static void wire_gpio_enable_isr(void)
{
    _xt_isr_unmask(1 << ETS_GPIO_INUM);
}

void wire_gpio_init1(void)
{
    gpio_intr_handler_register(wire_gpio_isr, NULL);

    GPIO_ConfigTypeDef wire_gpio_cnf;
    wire_gpio_cnf.GPIO_Pin = WIRE_DATAP_GPIO_PIN;
    wire_gpio_cnf.GPIO_Mode = WIRE_DATAP_GPIO_MODE;
    wire_gpio_cnf.GPIO_Pullup = WIRE_DATAP_GPIO_PULLUP;
    wire_gpio_cnf.GPIO_IntrType = WIRE_DATAP_GPIO_INTRTYPE;
    gpio_config(&wire_gpio_cnf);

    wire_gpio_cnf.GPIO_Pin = WIRE_DATAM_GPIO_PIN;
    wire_gpio_cnf.GPIO_Mode = WIRE_DATAM_GPIO_MODE;
    wire_gpio_cnf.GPIO_Pullup = WIRE_DATAM_GPIO_PULLUP;
    wire_gpio_cnf.GPIO_IntrType = WIRE_DATAM_GPIO_INTRTYPE;
    gpio_config(&wire_gpio_cnf);

    wire_gpio_enable_isr();
}

uint32_t wire_datap_state_func(void)
{
    return (gpio_input_get() & (0x01<<WIRE_DATAP_GPIO_NO)) >> WIRE_DATAP_GPIO_NO;
}

uint32_t wire_datam_state_func(void)
{
    return (gpio_input_get() & (0x01<<WIRE_DATAM_GPIO_NO)) >> WIRE_DATAM_GPIO_NO;
}

void subg_key_init(void)
{
    GPIO_ConfigTypeDef subg_gpio_cnf;
    subg_gpio_cnf.GPIO_Pin = KEY1_GPIO_PIN;
    subg_gpio_cnf.GPIO_Mode = KEY1_GPIO_MODE;
    subg_gpio_cnf.GPIO_Pullup = KEY1_GPIO_PULLUP;
    subg_gpio_cnf.GPIO_IntrType = KEY1_GPIO_INTRTYPE;
    gpio_config(&subg_gpio_cnf);

    subg_gpio_cnf.GPIO_Pin = KEY2_GPIO_PIN;
    subg_gpio_cnf.GPIO_Mode = KEY2_GPIO_MODE;
    subg_gpio_cnf.GPIO_Pullup = KEY2_GPIO_PULLUP;
    subg_gpio_cnf.GPIO_IntrType = KEY2_GPIO_INTRTYPE;
    gpio_config(&subg_gpio_cnf);
}

void subg_key_config_func(uint8_t keyCh,uint8_t state) 
{
    if(keyCh == 0)
    {
        if(state == 0) // off led
        {
            gpio_output_conf(0, KEY1_GPIO_PIN, KEY1_GPIO_PIN, 0);
        }
        else if(state == 1)      //on led
        {
            gpio_output_conf(KEY1_GPIO_PIN, 0, KEY1_GPIO_PIN, 0);
        }
        else if(state == 2) //toggle led
        {
            if((gpio_input_get() & (0x01<<14)) >> 14)    //if get 1,off led
            {
                gpio_output_conf(0, KEY1_GPIO_PIN, KEY1_GPIO_PIN, 0);
            }
            else                    //if get 0,on led
            {
                gpio_output_conf(KEY1_GPIO_PIN, 0, KEY1_GPIO_PIN, 0);
            }
        }
    }
    /*
    else if(keyCh == 1)
    {
        if(state == 0) // off led
        {
            gpio_output_conf(0, KEY2_GPIO_PIN, KEY2_GPIO_PIN, 0);
        }
        else if(state == 1)      //on led
        {
            gpio_output_conf(KEY2_GPIO_PIN, 0, KEY2_GPIO_PIN, 0);
        }
    }
    */
}

uint32_t subg_key_state_func(void)
{
    return ((gpio_input_get() & (0x01<<13)) >> 13);
}
#endif