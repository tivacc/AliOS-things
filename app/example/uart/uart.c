/*
 * Copyright (C) 2015-2017 Alibaba Group Holding Limited
 * 
 * 
 *   this is a uart sample from hal uart for esp8266, and the same as other chips;
 *   for esp8266 , when the port set is 1 ,then the uart1 ande uart2 is the same baud_rate , but the uart1（gpio2） is for log ;
 * 
 *   这sample是一个从hal层适配esp8266的，也许同样适配其他芯片
 *   对于esp8266，如果设置串口为1，则串口一和串口零都是这个波特率，如果需要不一样，请自行修改driver ，注意串口一（gpio2）是作为日志打印。
 * 
 *   Contributor:  https://github.com/xuhongv
 * 
 * 
 */


#include "aos/kernel.h"
#include "aos/hal/uart.h"
//#include "hal/soc/uart.h"
#include "driver/uart.h"
#include "uart.h"
#include "esp_common.h"
#include "uart.h"
#include "k_api.h"

#define HAL_WAIT_FOREVER 0xFFFFFFFFU



extern char g_buf_uart[128];


static aos_timer_t  test_timer;

uart_dev_t uart;
static void test_poll_func()
{
    uint8_t receive_bytes[15];
    int32_t ret = -1;
    uint32_t i, recv_size = 0;

    ret = hal_uart_recv_II(&uart, &receive_bytes, 15, &recv_size, HAL_WAIT_FOREVER);
    printf("get data state:%d\r\n",ret);
    if ((ret == 0))
    {
        printf(" len:%d, data :%x\r\n",recv_size,receive_bytes[0]);
        hal_uart_send(&uart,receive_bytes,recv_size,1000); 
    }
}

int application_start(int argc, char *argv[])
{

    //printf("uart sample application started...\n");
    uart_config_t uartConfig;
    uartConfig.baud_rate = 9600; 
    //uart_dev_t uart;
    uart.port = 1; //for esp8266 , when the port set is 1 ,then the uart1 ande uart2 is the same baud_rate , but the uart1 is for log 
    uart.config = uartConfig;
    hal_uart_init(&uart);

    printf("uart sample application started...\n");
    uint8_t receive_bytes[15];
    int32_t ret = -1;
    uint32_t i, recv_size = 0;

    //aos_timer_new(&test_timer, test_poll_func, NULL, 2000, 1);
    while (1)
    {
        ETS_UART_INTR_DISABLE();
        ret = hal_uart_recv_II(&uart, &receive_bytes, 15, &recv_size, HAL_WAIT_FOREVER);
        ETS_UART_INTR_ENABLE();
        if ((ret == 0))
        {
            hal_uart_send(&uart,"test",4,1000); 
            //for (i = 0; i < recv_size; i++)
            //    printf("hal_uart_recv_II ch = %d ,recv_size= %d \n", receive_bytes[i], recv_size);
            // en:return by the way you came  ch: 原路返回数据
            hal_uart_send(&uart,receive_bytes,recv_size,1000); 
        }
    }
    aos_loop_run();
    return 0;
}
