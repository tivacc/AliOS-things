/*
 * Copyright (C) 2015-2018 Alibaba Group Holding Limited
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "esp_common.h"
#include "aos/cli.h"
#include "aos/kernel.h"
#include "ulog/ulog.h"
#include "aos/yloop.h"
#include <k_api.h>
#include "netmgr.h"
#include "iot_export.h"
#include "iot_import.h"
#include "app_entry.h"
#include "bsp_board.h"
#include "aos/hal/gpio.h"
#include "aos/hal/uart.h"
#include "driver/uart.h"

#ifdef CSP_LINUXHOST
    #include <signal.h>
#endif

#if defined(ENABLE_AOS_OTA) 
    #include "ota/ota_service.h"
#endif

#define KV_KEY_ALIYUN_CONFIG        "light_aliyun_config"
#define KV_KEY_PRODUCT_KEY          "light_product_key"
#define KV_KEY_PRODUCT_SECRET       "light_product_secret"
#define KV_KEY_DEVICE_NAME          "light_device_name"
#define KV_KEY_DEVICE_SECRET        "light_device_secret"
#define KV_KEY_CONFIG_STATE         "awss_config_state"

#define HAL_WAIT_FOREVER            0xFFFFFFFFU


//***********************************************************

static char         linkkit_started     = 0;
static aos_timer_t  fly_event_timer;

uint8_t  uartRcv_flag = 0;
uint32_t recv_size = 0;
uint8_t receive_bytes[100];
uart_dev_t   uart;
aos_timer_t  uartRcv_timer;


uint8_t productKey[20] = {0};
uint8_t productSecret[32] = {0};
uint8_t deviceName[32] = {0};
uint8_t deviceSecret[62] = {0};

uint32_t wifi_config_state   = 0;
uint32_t wireless_ctrl_state = 0;

//***********************************************************


//***********************************************************
static void linkkit_reset(void)
{
    netmgr_clear_ap_config();
    HAL_Reboot();
}

void awss_reset_dev_ap(void)
{
    awss_dev_ap_stop();
    netmgr_clear_ap_config();
}

void awss_open_dev_ap(void)
{
    awss_dev_ap_start();
}

static void awss_close_dev_ap(void)
{
    awss_dev_ap_stop();
}

static void key_config_event(input_event_t *eventinfo, void *priv_data)
{
    if (eventinfo->type != EV_KEY) {
        return;
    }

    if (eventinfo->code == CODE_BOOT) 
    {
        if (eventinfo->value == VALUE_KEY_CLICK) 
        {
            led_config_func(3);
        }
    }
}

static void wifi_service_event(input_event_t *event, void *priv_data)
{
    if (event->type != EV_WIFI) {
        return;
    }

    if (event->code == CODE_WIFI_ON_DISCONNECT) {
        wifi_config_state = 4;
        wifi_led_config_func(0);        //off led
    }
    

    if (event->code != CODE_WIFI_ON_GOT_IP) {
        return;
    }    

    //if the connection has been disconnect,when it reconnect to router,
    //light on the led.
    if(wifi_config_state == 4)
    {
        wifi_config_state = 3;
    }

    netmgr_ap_config_t config;
    memset(&config, 0, sizeof(netmgr_ap_config_t));
    netmgr_get_ap_config(&config);
    LOG("wifi_service_event config.ssid %s", config.ssid);

    if (!linkkit_started) {
        #ifdef MQTT_DIRECT
        aos_task_new("linkkit", (void (*)(void *))linkkit_main, NULL, 1024 * 6);
        #else
        aos_task_new("linkkit", (void (*)(void *))linkkit_main, NULL, 1024 * 8);
        #endif

        linkkit_started = 1;
    }
}


static int keyTempCnt = 0;
static uint8_t  subgCtrlState       = 0;
static uint8_t  subgCtrlPreState    = 0;
static uint32_t wifi_led_time       = 0;
static uint32_t wifi_config_time    = 0;
static uint32_t wifi_config_key_cnt = 0;

static void fly_event_poll_func()
{
    rec_wdt_feed();
    char configState;

    #if 0
    keyTempCnt += 1;
    if(keyTempCnt >= 50 )
    {   
        keyTempCnt = 0;
        extern k_mm_head *g_kmm_head;
        int free = g_kmm_head->free_size;
        LOG("============free heap size =%d==========", free);
    }
    #endif

    #if DEVICE_SUPPORT_SUBG == 1
    extern uint8_t   DataNum;
    extern uint8_t   RevData;
    extern uint8_t   RevTime;
    extern uint8_t   LastDat;
    if(RevTime > 0)
    {
        RevTime--;
    }
    else
    {
        DataNum = 0;
        RevData = 0;
        LastDat = 0x03;
    }

    if(subgCtrlState != subg_key_state_func())
    {
        subgCtrlState = subg_key_state_func();
        wireless_ctrl_state = 1;
    }
    #endif
    
    {
        if(wifi_config_state == 1)
        {
            wifi_led_time += 1;
            if(wifi_led_time > 1)
            {
                //printf("wifi_config_state led\r\n");
                wifi_led_time = 0;
                wifi_led_config_func(3);        //toggle led --200ms
            } 
        }
        else if(wifi_config_state == 2)
        {   
            wifi_led_time += 1;
            if(wifi_led_time > 10)
            {
                wifi_led_time = 0;
                wifi_led_config_func(3);        //toggle led --1000ms
            } 
        }
        else if(wifi_config_state == 3)
        {
            wifi_config_state = 0;

            configState = 0x5A;
            HAL_Kv_Set(KV_KEY_CONFIG_STATE,&configState,sizeof(configState),0);

            wifi_led_config_func(1);            //on led
        }
        else if(wifi_config_state == 4)         //off led
        {
            /*if wifi disconnected,start detect the subg,if level switch
            5 times in 7s,the device will clear the configuration,then
            reboot device for reconfiguration.otherwise ,clear the count,
            wait for next level switch.*/
            if(subgCtrlPreState != subgCtrlState)
            {
                //printf("key pressed.\n");
                subgCtrlPreState = subgCtrlState;
                wifi_config_key_cnt += 1;

                if(wifi_config_key_cnt >= 4)
                {
                    //printf("config valid.\n");
                    wifi_config_key_cnt = 0;

                    configState = 0x5A;
                    HAL_Kv_Set(KV_KEY_CONFIG_STATE,&configState,sizeof(configState),0);
                    linkkit_reset();
                }
            }

            if(wifi_config_time >= 100)
            {
                //printf("timeout,config invalid.\n");
                wifi_config_time = 0;
                wifi_config_key_cnt = 0;               
            }
        }

        if(wifi_config_key_cnt >= 1)
        {
            wifi_config_time += 1;
        }
    }

    
}

static uint8_t oneKeyOneDev = 0;
static void uartrcv_poll_func()
{
    uint32_t i;        
    uint32_t checkSum = 0;
    uint8_t send_bytes[15] = {0};

    int32_t ret = -1;
    uint8_t tempData;
    uint32_t tempDataLen;

    ETS_UART_INTR_DISABLE();
    ret = hal_uart_recv_II(&uart, &receive_bytes[recv_size], 100, &recv_size, HAL_WAIT_FOREVER);
    ETS_UART_INTR_ENABLE();
    if ((ret == 0))
    {   
        uartRcv_flag = 1;
        if(uartRcv_flag)
        {
            //printf("recv_size:%d\r\n",recv_size);
            uartRcv_flag = 0;
            //finish cmd rcv,then process the cmd
            if((recv_size>=2) && (receive_bytes[recv_size-2] == 0x0D) && (receive_bytes[recv_size-1] == 0x0A))
            {
                //printf("process the rcv data.%s",receive_bytes);
                for(i=0;i<recv_size-4;i++)
                {
                    checkSum += receive_bytes[i];
                }

                if(checkSum == ((receive_bytes[recv_size-4]<<8)+(receive_bytes[recv_size-3])))
                {
                    if(oneKeyOneDev == 0)
                    {
                        oneKeyOneDev = 1;
                        if(!(strncmp(receive_bytes,"start",5)))
                        {
                            send_bytes[0] = 'o';
                            send_bytes[1] = 'k';
                            send_bytes[2] = (send_bytes[0] + (send_bytes[1])>>8) & 0xff;
                            send_bytes[3] = (send_bytes[0] + (send_bytes[1])) & 0xff;
                            send_bytes[4] = 0x0D;
                            send_bytes[5] = 0x0A;
                            hal_uart_send(&uart,send_bytes,6,1000); 
                        }
                    }
                    else if(oneKeyOneDev == 1)
                    {   
                        oneKeyOneDev = 0;

                        {
                        memset(productKey, 0, sizeof(productKey));
                        strncpy(productKey, &receive_bytes[0],11);
                        //printf("productKey:%s",productKey);
                        HAL_Kv_Set(KV_KEY_PRODUCT_KEY,productKey,sizeof(productKey),0);

                        memset(productSecret, 0, sizeof(productSecret));
                        strncpy(productSecret, &receive_bytes[11],16);
                        //printf("productSecret:%s",productSecret);
                        HAL_Kv_Set(KV_KEY_PRODUCT_SECRET,productSecret,sizeof(productSecret),0);

                        memset(deviceName, 0, sizeof(deviceName));
                        strncpy(deviceName, &receive_bytes[27],recv_size-11-16-32-4);
                        //printf("deviceName:%s",deviceName);
                        HAL_Kv_Set(KV_KEY_DEVICE_NAME,deviceName,sizeof(deviceName),0);

                        memset(deviceSecret, 0, sizeof(deviceSecret));
                        strncpy(deviceSecret, &receive_bytes[recv_size-4-32],32);
                        //printf("deviceSecret:%s",deviceSecret);
                        HAL_Kv_Set(KV_KEY_DEVICE_SECRET,deviceSecret,sizeof(deviceSecret),0);

                        char aliyunConfig[2] = {0};
                        int aliyunConfigLen = 0; 
                        aliyunConfigLen = sizeof(aliyunConfig);

                        aliyunConfig[0] = 0x55;
                        aliyunConfig[1] = 0xAA;
                        HAL_Kv_Set(KV_KEY_ALIYUN_CONFIG,&aliyunConfig,sizeof(aliyunConfig),0);

                        send_bytes[0] = 'o';
                        send_bytes[1] = 'k';
                        send_bytes[2] = (send_bytes[0] + (send_bytes[1])>>8) & 0xff;
                        send_bytes[3] = (send_bytes[0] + (send_bytes[1])) & 0xff;
                        send_bytes[4] = 0x0D;
                        send_bytes[5] = 0x0A;
                        hal_uart_send(&uart,send_bytes,6,1000); 

                        linkkit_reset();
                        }
                    }
                }
                else
                {
                    send_bytes[0] = 'e';
                    send_bytes[1] = 'r';
                    send_bytes[2] = (send_bytes[0] + (send_bytes[1])>>8) & 0xff;
                    send_bytes[3] = (send_bytes[0] + (send_bytes[1])) & 0xff;
                    send_bytes[4] = 0x0D;
                    send_bytes[5] = 0x0A;
                    hal_uart_send(&uart,send_bytes,6,1000); 
                }

                recv_size = 0;
            }
            else
            {
                ;//printf("data not rcv finish.\r\n");
            }
        }
    }
}


static void linkkit_event_monitor(int event)
{
    switch (event) {
        case IOTX_AWSS_START: // AWSS start without enbale, just supports device discover
            // operate led to indicate user        
            LOG("IOTX_AWSS_START");
            break;
        case IOTX_AWSS_ENABLE: // AWSS enable, AWSS doesn't parse awss packet until AWSS is enabled.
            LOG("IOTX_AWSS_ENABLE");
            // operate led to indicate user
            break;
        case IOTX_AWSS_LOCK_CHAN: // AWSS lock channel(Got AWSS sync packet)
            LOG("IOTX_AWSS_LOCK_CHAN");
            // operate led to indicate user
            break;
        case IOTX_AWSS_PASSWD_ERR: // AWSS decrypt passwd error
            LOG("IOTX_AWSS_PASSWD_ERR");
            // operate led to indicate user
            break;
        case IOTX_AWSS_GOT_SSID_PASSWD:
            LOG("IOTX_AWSS_GOT_SSID_PASSWD");
            // operate led to indicate user
            break;
        case IOTX_AWSS_CONNECT_ADHA: // AWSS try to connnect adha (device
                                     // discover, router solution)
            LOG("IOTX_AWSS_CONNECT_ADHA");
            // operate led to indicate user
            break;
        case IOTX_AWSS_CONNECT_ADHA_FAIL: // AWSS fails to connect adha
            LOG("IOTX_AWSS_CONNECT_ADHA_FAIL");
            // operate led to indicate user
            break;
        case IOTX_AWSS_CONNECT_AHA: // AWSS try to connect aha (AP solution)
            LOG("IOTX_AWSS_CONNECT_AHA");
            // operate led to indicate user
            break;
        case IOTX_AWSS_CONNECT_AHA_FAIL: // AWSS fails to connect aha
            LOG("IOTX_AWSS_CONNECT_AHA_FAIL");
            // operate led to indicate user
            break;
        case IOTX_AWSS_SETUP_NOTIFY: // AWSS sends out device setup information
                                     // (AP and router solution)
            LOG("IOTX_AWSS_SETUP_NOTIFY");
            // operate led to indicate user
            break;
        case IOTX_AWSS_CONNECT_ROUTER: // AWSS try to connect destination router
            LOG("IOTX_AWSS_CONNECT_ROUTER");
            // operate led to indicate user
            break;
        case IOTX_AWSS_CONNECT_ROUTER_FAIL: // AWSS fails to connect destination
                                            // router.
            LOG("IOTX_AWSS_CONNECT_ROUTER_FAIL");
            // operate led to indicate user
            break;
        case IOTX_AWSS_GOT_IP: // AWSS connects destination successfully and got
                               // ip address
            wifi_config_state = 2;
            LOG("IOTX_AWSS_GOT_IP");
            // operate led to indicate user
            break;
        case IOTX_AWSS_SUC_NOTIFY: // AWSS sends out success notify (AWSS
                                   // sucess)
            LOG("IOTX_AWSS_SUC_NOTIFY");
            // operate led to indicate user
            break;
        case IOTX_AWSS_BIND_NOTIFY: // AWSS sends out bind notify information to
                                    // support bind between user and device
            LOG("IOTX_AWSS_BIND_NOTIFY");
            // operate led to indicate user
            break;
        case IOTX_AWSS_ENABLE_TIMEOUT: // AWSS enable timeout
                                       // user needs to enable awss again to support get ssid & passwd of router
            LOG("IOTX_AWSS_ENALBE_TIMEOUT");
            // operate led to indicate user
            break;
        case IOTX_CONN_CLOUD: // Device try to connect cloud
            LOG("IOTX_CONN_CLOUD");
            // operate led to indicate user
            break;
        case IOTX_CONN_CLOUD_FAIL: // Device fails to connect cloud, refer to
                                   // net_sockets.h for error code
            wifi_config_state = 2;
            extern int light_connect_fail_handler(void);
            light_connect_fail_handler();
            LOG("IOTX_CONN_CLOUD_FAIL");
            // operate led to indicate user
            break;
        case IOTX_CONN_CLOUD_SUC: // Device connects cloud successfully
            wifi_config_state = 3;
            LOG("IOTX_CONN_CLOUD_SUC");
            // operate led to indicate user
            break;
        case IOTX_RESET: // Linkkit reset success (just got reset response from
                         // cloud without any other operation)
            LOG("IOTX_RESET");
            // operate led to indicate user
            break;
        default:
            break;
    }
}

static void local_service_start(void)
{   
    int ret;
    wifi_key_init();
    wifi_led_init();
    wifi_led_config_func(0);
    #if DEVICE_SUPPORT_SUBG == 1
    wire_gpio_init1();
    subg_key_init();
    subg_key_config_func(0,1);
    subgCtrlState = subg_key_state_func();
    subgCtrlPreState = subgCtrlState;
    #else
    led_gpio_init();
    led_config_func(1);         //set high level when initialize
    #endif

    ret = aos_timer_new(&fly_event_timer, fly_event_poll_func, NULL, 100, 1);
    if(ret != RHINO_SUCCESS)
    {
        linkkit_reset();
    }
}


static void network_start(void *p)
{
    char configState = 0;
    int configStateLen = sizeof(configState); 
    HAL_Kv_Get(KV_KEY_CONFIG_STATE,&configState,&configStateLen);

    iotx_event_regist_cb(linkkit_event_monitor);
    extern void config_wifi_mode(int mode);
    //if KV_KEY_CONFIG_STATE is set as 0x00, device wait for button press to enter config mode
    //if KV_KEY_CONFIG_STATE is set as 0x5A, device has been config,skip this step and then connect the wifi directly.
    if(configState == 0x00)
    {
        //detect the button state in the time poll function
        wifi_config_state = 4;

        //device enter station mode
        config_wifi_mode(0x01); 
    }
    if(configState == 0x5A)
    {
        //device has been enter config mode,led blink.
        wifi_config_state = 1;
        if (netmgr_start(false) < 0) 
        {
            //clear the KV_KEY_CONFIG_STATE value for power off accidently,next power on will wait for button press still.
            configState = 0x00;
            HAL_Kv_Set(KV_KEY_CONFIG_STATE,&configState,sizeof(configState),0);

            //start config network
            awss_reset_dev_ap();
            aos_msleep(100);
            
            config_wifi_mode(0x03); 
            awss_open_dev_ap();
        }
    }
    
    aos_task_exit(0);
}

void set_iotx_info()
{
    HAL_SetProductKey(productKey);
    HAL_SetProductSecret(productSecret);
    HAL_SetDeviceName(deviceName);
    HAL_SetDeviceSecret(deviceSecret);
}


//start
int application_start(int argc, char **argv)
{
    //IOT_SetLogLevel(IOT_LOG_DEBUG);
    IOT_SetLogLevel(IOT_LOG_NONE);

    char aliyunConfig[2] = {0};
    int aliyunConfigLen = 0; 
    aliyunConfigLen = sizeof(aliyunConfig);
    HAL_Kv_Get(KV_KEY_ALIYUN_CONFIG,&aliyunConfig,&aliyunConfigLen);
    if((aliyunConfig[0] == 0x55) && (aliyunConfig[1] == 0xAA))
    {
        int tempLen = 0;         
        
        tempLen = sizeof(productKey);
        memset(productKey, 0, sizeof(productKey));
        HAL_Kv_Get(KV_KEY_PRODUCT_KEY,productKey,&tempLen);
        //printf("productKey:%s",productKey);
        
        tempLen = sizeof(productSecret);
        memset(productSecret, 0, sizeof(productSecret));
        HAL_Kv_Get(KV_KEY_PRODUCT_SECRET,productSecret,&tempLen); 
        //printf("productSecret:%s",productSecret);     
        
        tempLen = sizeof(deviceName);
        memset(deviceName, 0, sizeof(deviceName));
        HAL_Kv_Get(KV_KEY_DEVICE_NAME,deviceName,&tempLen);
        //printf("deviceName:%s",deviceName);
        
        tempLen = sizeof(deviceSecret);
        memset(deviceSecret, 0, sizeof(deviceSecret));
        HAL_Kv_Get(KV_KEY_DEVICE_SECRET,deviceSecret,&tempLen);
        //printf("deviceSecret:%s",deviceSecret);
        set_iotx_info();

        local_service_start();
        netmgr_init();
        aos_register_event_filter(EV_KEY, key_config_event, NULL);
        aos_register_event_filter(EV_WIFI, wifi_service_event, NULL);


        rec_wdt_init(500);
        aos_task_new("network_start", network_start, NULL, 4096);
    }
    else
    {
        uart_config_t uartConfig;
        uartConfig.baud_rate = 9600; 
        uart.port = 1; //for esp8266 , when the port set is 1 ,then the uart1 ande uart2 is the same baud_rate , but the uart1 is for log 
        uart.config = uartConfig;
        hal_uart_init(&uart);

        int ret ; 
        ret = aos_timer_new(&uartRcv_timer, uartrcv_poll_func, NULL, 200, 1);
        if(ret != RHINO_SUCCESS)
        {
            linkkit_reset();
        }

        while (1)
        {   
            
        }
    }

    aos_loop_run();
    return 0;
}
