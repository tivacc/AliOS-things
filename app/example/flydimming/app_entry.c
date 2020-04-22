/*
 * Copyright (C) 2015-2018 Alibaba Group Holding Limited
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
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
#include "fly_queue.h"

#ifdef CSP_LINUXHOST
    #include <signal.h>
#endif

#if defined(ENABLE_AOS_OTA) 
    #include "ota/ota_service.h"
#endif

// #define KV_KEY_ALIYUN_CONFIG        "curtain_aliyun_config"
// #define KV_KEY_PRODUCT_KEY          "curtain_product_key"
// #define KV_KEY_PRODUCT_SECRET       "curtain_product_secret"
// #define KV_KEY_DEVICE_NAME          "curtain_device_name"
// #define KV_KEY_DEVICE_SECRET        "curtain_device_secret"
// #define KV_KEY_CONFIG_STATE         "awss_config_state"

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


uint8_t productKey[20] = {0};
uint8_t productSecret[32] = {0};
uint8_t deviceName[32] = {0};
uint8_t deviceSecret[62] = {0};

uint32_t wifi_config_state   = 0;
uint32_t wireless_ctrl_state = 0;

extern uint32_t    recv_size;
extern uint32_t    send_size;

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
            ;
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
    //curtain on the led.
    if(wifi_config_state == 4)
    {
        wifi_config_state = 3;
    }

    netmgr_ap_config_t config;
    memset(&config, 0, sizeof(netmgr_ap_config_t));
    netmgr_get_ap_config(&config);

    if (!linkkit_started) {
        #ifdef MQTT_DIRECT
        aos_task_new("linkkit", (void (*)(void *))linkkit_main, NULL, 1024 * 6);
        #else
        aos_task_new("linkkit", (void (*)(void *))linkkit_main, NULL, 1024 * 8);
        #endif

        linkkit_started = 1;
    }
}


static uint64_t key_start_time = 0;
static void wifiConfigBtnPoll(void)
{
    char configState = 0;
    int configStateLen = 0; 

    uint64_t currentTime = 0;
    uint32_t btnState = wifi_key_state_func();
    if (btnState == 0) 
    {
        if(key_start_time == 0)
        {
            key_start_time = aos_now_ms();
        }
        else
        {
            currentTime = aos_now_ms();
            if((currentTime - key_start_time) > 5000)
            {
                configState = 0x5A;
                HAL_Kv_Set(KV_KEY_CONFIG_STATE,&configState,sizeof(configState),0);

                //reboot for enter configuration mode
                linkkit_reset();
            }
        }        
    }
    else
    {
        key_start_time = 0;
    }
}

static uint32_t wifi_led_time = 0;
static void wifiLedStateDisplay(void)
{
    //poll wifi state
    char configState = 0;
    if(wifi_config_state == 1)
    {
        wifi_led_time += 1;
        if(wifi_led_time > 1)
        {
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
}

static void curtainCtrlReq(void)
{
    //poll uart data
    uint8_t retState = serial_receive_handler(SERIAL_TYPE_CURTAIN_CTRL);
    if(retState == 1)
    {
        wireless_ctrl_state = 1;
    }
    else
    {
        wireless_ctrl_state = 0;
    }
}

static void fly_event_poll_func()
//static void fly_event_poll(void *arg1)
{
    curtainCtrlReq();
    wifiConfigBtnPoll();
    wifiLedStateDisplay();
    // wifi_led_config_func(3);        //toggle led --100ms
    // aos_post_delayed_action(100,fly_event_poll,NULL);
}

static uint8_t oneKeyOneDev = 0;
static void fly_key_uart_poll(void *arg)
{
    uint8_t keyWriteRes[32];    
    uint8_t retState = serial_receive_handler(SERIAL_TYPE_KEY_WRITE);
    if( retState == 1)
    {
        if(oneKeyOneDev == 0)
        {
            oneKeyOneDev = 1;
            if(!(strncmp(fly_key_write.payload,"start",5)))
            {
                strncpy(keyWriteRes,"ok",2);
                serial_send_handler(SERIAL_TYPE_KEY_WRITE,2,keyWriteRes);
            }
        }
        else if(oneKeyOneDev == 1)
        {   
            oneKeyOneDev = 0;

            {
            memset(productKey, 0, sizeof(productKey));
            strncpy(productKey, &(fly_key_write.payload[0]),11);
            //printf("productKey:%s",productKey);
            HAL_Kv_Set(KV_KEY_PRODUCT_KEY,productKey,sizeof(productKey),0);

            memset(productSecret, 0, sizeof(productSecret));
            strncpy(productSecret, &fly_key_write.payload[11],16);
            //printf("productSecret:%s",productSecret);
            HAL_Kv_Set(KV_KEY_PRODUCT_SECRET,productSecret,sizeof(productSecret),0);

            memset(deviceName, 0, sizeof(deviceName));
            strncpy(deviceName, &fly_key_write.payload[27],recv_size-11-16-32-4);
            //printf("deviceName:%s",deviceName);
            HAL_Kv_Set(KV_KEY_DEVICE_NAME,deviceName,sizeof(deviceName),0);

            memset(deviceSecret, 0, sizeof(deviceSecret));
            strncpy(deviceSecret, &fly_key_write.payload[recv_size-4-32],32);
            //printf("deviceSecret:%s",deviceSecret);
            HAL_Kv_Set(KV_KEY_DEVICE_SECRET,deviceSecret,sizeof(deviceSecret),0);

            char aliyunConfig[2] = {0};
            int aliyunConfigLen = 0; 
            aliyunConfigLen = sizeof(aliyunConfig);

            aliyunConfig[0] = 0x55;
            aliyunConfig[1] = 0xAA;
            HAL_Kv_Set(KV_KEY_ALIYUN_CONFIG,&aliyunConfig,sizeof(aliyunConfig),0);

            uint8_t configState = 0x00;
            HAL_Kv_Set(KV_KEY_CONFIG_STATE,&configState,sizeof(configState),0);

            strncpy(keyWriteRes,"ok",2);
            serial_send_handler(SERIAL_TYPE_KEY_WRITE,2,keyWriteRes);

            linkkit_reset();
            }
        }
    }
    else if(retState == 2)
    {
        strncpy(keyWriteRes,"er",2);
        serial_send_handler(SERIAL_TYPE_KEY_WRITE,2,keyWriteRes);
    }    

    aos_post_delayed_action(100,fly_key_uart_poll,NULL);
}

static void linkkit_event_monitor(int event)
{
    switch (event) {
        case IOTX_AWSS_START: // AWSS start without enbale, just supports device discover
            // operate led to indicate user        
            //LOG("IOTX_AWSS_START");
            break;
        case IOTX_AWSS_ENABLE: // AWSS enable, AWSS doesn't parse awss packet until AWSS is enabled.
            //LOG("IOTX_AWSS_ENABLE");
            // operate led to indicate user
            break;
        case IOTX_AWSS_LOCK_CHAN: // AWSS lock channel(Got AWSS sync packet)
            //LOG("IOTX_AWSS_LOCK_CHAN");
            // operate led to indicate user
            break;
        case IOTX_AWSS_PASSWD_ERR: // AWSS decrypt passwd error
            //LOG("IOTX_AWSS_PASSWD_ERR");
            // operate led to indicate user
            break;
        case IOTX_AWSS_GOT_SSID_PASSWD:
            //LOG("IOTX_AWSS_GOT_SSID_PASSWD");
            // operate led to indicate user
            break;
        case IOTX_AWSS_CONNECT_ADHA: // AWSS try to connnect adha (device
                                     // discover, router solution)
            //LOG("IOTX_AWSS_CONNECT_ADHA");
            // operate led to indicate user
            break;
        case IOTX_AWSS_CONNECT_ADHA_FAIL: // AWSS fails to connect adha
            //LOG("IOTX_AWSS_CONNECT_ADHA_FAIL");
            // operate led to indicate user
            break;
        case IOTX_AWSS_CONNECT_AHA: // AWSS try to connect aha (AP solution)
            //LOG("IOTX_AWSS_CONNECT_AHA");
            // operate led to indicate user
            break;
        case IOTX_AWSS_CONNECT_AHA_FAIL: // AWSS fails to connect aha
            //LOG("IOTX_AWSS_CONNECT_AHA_FAIL");
            // operate led to indicate user
            break;
        case IOTX_AWSS_SETUP_NOTIFY: // AWSS sends out device setup information
                                     // (AP and router solution)
            //LOG("IOTX_AWSS_SETUP_NOTIFY");
            // operate led to indicate user
            break;
        case IOTX_AWSS_CONNECT_ROUTER: // AWSS try to connect destination router
            //LOG("IOTX_AWSS_CONNECT_ROUTER");
            // operate led to indicate user
            break;
        case IOTX_AWSS_CONNECT_ROUTER_FAIL: // AWSS fails to connect destination
                                            // router.
            //LOG("IOTX_AWSS_CONNECT_ROUTER_FAIL");
            // operate led to indicate user
            break;
        case IOTX_AWSS_GOT_IP: // AWSS connects destination successfully and got
                               // ip address
            wifi_config_state = 2;
            //LOG("IOTX_AWSS_GOT_IP");
            // operate led to indicate user
            break;
        case IOTX_AWSS_SUC_NOTIFY: // AWSS sends out success notify (AWSS
                                   // sucess)
            //LOG("IOTX_AWSS_SUC_NOTIFY");
            // operate led to indicate user
            break;
        case IOTX_AWSS_BIND_NOTIFY: // AWSS sends out bind notify information to
                                    // support bind between user and device
            //LOG("IOTX_AWSS_BIND_NOTIFY");
            // operate led to indicate user
            break;
        case IOTX_AWSS_ENABLE_TIMEOUT: // AWSS enable timeout
                                       // user needs to enable awss again to support get ssid & passwd of router
            //LOG("IOTX_AWSS_ENALBE_TIMEOUT");
            // operate led to indicate user
            break;
        case IOTX_CONN_CLOUD: // Device try to connect cloud
            //LOG("IOTX_CONN_CLOUD");
            // operate led to indicate user
            break;
        case IOTX_CONN_CLOUD_FAIL: // Device fails to connect cloud, refer to
                                   // net_sockets.h for error code
            wifi_config_state = 2;
            extern int curtain_connect_fail_handler(void);
            curtain_connect_fail_handler();
            //LOG("IOTX_CONN_CLOUD_FAIL");
            // operate led to indicate user
            break;
        case IOTX_CONN_CLOUD_SUC: // Device connects cloud successfully
            wifi_config_state = 3;
            //LOG("IOTX_CONN_CLOUD_SUC");
            // operate led to indicate user
            break;
        case IOTX_RESET: // Linkkit reset success (just got reset response from
                         // cloud without any other operation)
            //LOG("IOTX_RESET");
            // operate led to indicate user
            break;
        default:
            break;
    }
}

static void local_service_start(void)
{   
    wifi_key_init();
    wifi_led_init();
    wifi_led_config_func(0);

    serial_init();
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
        //device enter station mode
        config_wifi_mode(0x01);
    }
    else if(configState == 0x5A)
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
    IOT_SetLogLevel(IOT_LOG_DEBUG);
    //IOT_SetLogLevel(IOT_LOG_NONE);

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

        aos_timer_new(&fly_event_timer, fly_event_poll_func, NULL, 100, 1);
        //aos_post_delayed_action(0,fly_event_poll,NULL);
        aos_task_new("network_start", network_start, NULL, 4096);
    }
    else
    {
        local_service_start();
        aos_post_delayed_action(0,fly_key_uart_poll,NULL);
    }
    
    aos_loop_run();
    return 0;
}
