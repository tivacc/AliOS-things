/*
 * Copyright (C) 2015-2018 Alibaba Group Holding Limited
 */
#ifdef DEPRECATED_LINKKIT
#include "deprecated/solo.c"
#else
#include "stdio.h"
#include "iot_export.h"
#include "iot_import.h"
#include "cJSON.h"
#include "app_entry.h"
#include "aos/hal/gpio.h"
#include "app_entry.h"
#include "bsp_board.h"

#if defined(ENABLE_AOS_OTA) 
#include "ota/ota_service.h"
#endif


uint8_t flyCurtainError = 0;
//***********************************************************

#define USE_CUSTOME_DOMAIN          (0)
#if USE_CUSTOME_DOMAIN
    #define CUSTOME_DOMAIN_MQTT     "iot-as-mqtt.cn-shanghai.aliyuncs.com"
    #define CUSTOME_DOMAIN_HTTP     "iot-auth.cn-shanghai.aliyuncs.com"
#endif

#define curtain_YIELD_TIMEOUT_MS      (200)
#define EXAMPLE_TRACE(...)                               \
    do {                                                     \
        HAL_Printf("\033[1;32;40m%s.%d: ", __func__, __LINE__);  \
        HAL_Printf(__VA_ARGS__);                                 \
        HAL_Printf("\033[0m\r\n");                                   \
    } while (0)

//***********************************************************
typedef struct {
    int master_devid;
    int cloud_connected;
    int master_initialized;
} fly_curtain_ctx_t;

static fly_curtain_ctx_t fly_curtain_ctx;

//***********************************************************
static uint64_t curtain_update_sec(void)
{
    static uint64_t time_start_ms = 0;

    if (time_start_ms == 0) {
        time_start_ms = HAL_UptimeMs();
    }

    return (HAL_UptimeMs() - time_start_ms) / 1000;
}


static fly_curtain_ctx_t *fly_curtain_get_ctx(void)
{
    return &fly_curtain_ctx;
}


static int curtain_master_dev_available(void)
{
    fly_curtain_ctx_t *curtain_ctx = fly_curtain_get_ctx();

    if (curtain_ctx->cloud_connected && curtain_ctx->master_initialized) {
        return 1;
    }

    return 0;
}


static int curtain_initialized(const int devid)
{
    fly_curtain_ctx_t *curtain_ctx = fly_curtain_get_ctx();
    printf("Device Initialized, Devid: %d", devid);

    if (curtain_ctx->master_devid == devid) {
        curtain_ctx->master_initialized = 1;
    }

    return 0;
}

static int curtain_connected_event_handler(void)
{
    int ret = 0;
    fly_curtain_ctx_t *curtain_ctx = fly_curtain_get_ctx();

    printf("Cloud Connected");
    extern uint32_t wifi_config_state;
    wifi_config_state = 3;
    curtain_ctx->cloud_connected = 1;

    #if defined(ENABLE_AOS_OTA) 
    //if connected ,initlize the ota 
    printf("Initialize OTA parameters");
   
    char tempProductKey[PRODUCT_KEY_LEN + 1] = {0};
    char tempDeviceName[DEVICE_NAME_LEN + 1] = {0};
    char tempDeviceSecret[DEVICE_SECRET_LEN + 1] = {0};
    HAL_GetProductKey(tempProductKey);
    HAL_GetDeviceName(tempDeviceName);
    HAL_GetDeviceSecret(tempDeviceSecret);

    static ota_service_t ctx = {0};
    memset(&ctx, 0, sizeof(ota_service_t));
    strncpy(ctx.pk, tempProductKey, sizeof(ctx.pk)-1);
    strncpy(ctx.dn, tempDeviceName, sizeof(ctx.dn)-1);
    strncpy(ctx.ds, tempDeviceSecret, sizeof(ctx.ds)-1);
    ctx.trans_protcol = 0;
    ctx.dl_protcol = 3;

    ret = ota_service_init(&ctx);
    printf("ota init result: %d", ret);
    #endif

    return 0;
}


int curtain_connect_fail_handler(void)
{
    printf("Cloud Connect Fail,Reconnect");
    fly_curtain_ctx_t *curtain_ctx = fly_curtain_get_ctx();
    curtain_ctx->cloud_connected = 0;

    IOT_Linkkit_Connect(curtain_ctx->master_devid);
}

void curtain_reconnect(void *p)
{
    int res = 0;
    fly_curtain_ctx_t *curtain_ctx = fly_curtain_get_ctx();
    curtain_ctx->cloud_connected = 0;

    extern uint32_t wifi_config_state;
    wifi_config_state = 2;

    do 
    {
        HAL_SleepMs(1000);
        res = IOT_Linkkit_Connect(curtain_ctx->master_devid);
    }while((res < 0) && (wifi_config_state < 4));

    aos_task_exit(0);
}

static int curtain_disconnected_event_handler(void)
{
    printf("Cloud Disconnected");
    extern uint32_t wifi_config_state;
    if(wifi_config_state < 4)
    {
        aos_task_new("curtain_reconnect", curtain_reconnect, NULL, 4096);
    }

    return 0;
}


static int curtain_service_request_event_handler(const int devid, 
        const char *serviceid, 
        const int serviceid_len,
        const char *request, 
        const int request_len,
        char **response, int *response_len)
{
    int contrastratio = 0, to_cloud = 0;
    cJSON *root = NULL, *item_transparency = NULL, *item_from_cloud = NULL;
    printf("Service Request Received, Devid: %d, Service ID: %.*s, Payload: %s", 
            devid, serviceid_len,serviceid,request);

    /* Parse Root */
    root = cJSON_Parse(request);
    if (root == NULL || !cJSON_IsObject(root)) {
        printf("JSON Parse Error");
        return -1;
    }

    if (strlen("Custom") == serviceid_len && \
            memcmp("Custom", serviceid, serviceid_len) == 0) 
    {
        /* Parse Item */
        const char *response_fmt = "{\"Contrastratio\":%d}";
        item_transparency = cJSON_GetObjectItem(root, "transparency");
        if (item_transparency == NULL || !cJSON_IsNumber(item_transparency)) {
            cJSON_Delete(root);
            return -1;
        }
        printf("transparency: %d", item_transparency->valueint);
        contrastratio = item_transparency->valueint + 1;

        /* Send Service Response To Cloud */
        *response_len = strlen(response_fmt) + 10 + 1;
        *response = (char *)HAL_Malloc(*response_len);
        if (*response == NULL) {
            printf("Memory Not Enough");
            return -1;
        }
        memset(*response, 0, *response_len);
        HAL_Snprintf(*response, *response_len, response_fmt, contrastratio);
        *response_len = strlen(*response);
    } 
    else if (strlen("SyncService") == serviceid_len && \
            memcmp("SyncService", serviceid, serviceid_len) == 0) 
    {
        /* Parse Item */
        const char *response_fmt = "{\"ToCloud\":%d}";
        item_from_cloud = cJSON_GetObjectItem(root, "FromCloud");
        if (item_from_cloud == NULL || !cJSON_IsNumber(item_from_cloud)) 
        {
            cJSON_Delete(root);
            return -1;
        }
        printf("FromCloud: %d", item_from_cloud->valueint);
        to_cloud = item_from_cloud->valueint + 1;

        /* Send Service Response To Cloud */
        *response_len = strlen(response_fmt) + 10 + 1;
        *response = (char *)HAL_Malloc(*response_len);
        if (*response == NULL) {
            printf("Memory Not Enough");
            return -1;
        }
        memset(*response, 0, *response_len);
        HAL_Snprintf(*response, *response_len, response_fmt, to_cloud);
        *response_len = strlen(*response);
    }
    cJSON_Delete(root);

    return 0;
}


static int curtain_property_set_event_handler(const int devid, 
                const char *request, const int request_len)
{
    int res = 0;
    char *response = NULL;
    uint32_t curtainState = 0;
    cJSON *request_root = NULL;
    cJSON*item_curtainOperation = NULL;
    cJSON*item_curtainposition = NULL;
    uint8_t ctrlLen = 0;
    uint8_t crtlData[32];

    fly_curtain_ctx_t *curtain_ctx = fly_curtain_get_ctx();
    printf("Property Set Received, Devid: %d, Request: %s", devid, request);

    request_root = cJSON_Parse(request);
    if (request_root == NULL) {
        printf("JSON Parse Error");
        return -1;
    }
    
    item_curtainOperation = cJSON_GetObjectItem(request_root, "CurtainOperation");
    item_curtainposition = cJSON_GetObjectItem(request_root, "CurtainPosition");

    if(item_curtainOperation != NULL)
    {
        printf("item_curtainOperation: %d", item_curtainOperation->valueint);
        crtlData[ctrlLen++] = 0x03;
        crtlData[ctrlLen++] = (item_curtainOperation->valueint == 0x00)?0x02:((item_curtainOperation->valueint == 0x01)?0x01:0x03);
        serial_send_handler(SERIAL_TYPE_CURTAIN_CTRL,ctrlLen,crtlData);
    }
    else if(item_curtainposition != NULL)
    {
        printf("item_curtainposition: %d", item_curtainposition->valueint);
        crtlData[ctrlLen++] = 0x03;
        crtlData[ctrlLen++] = 0x04;
        crtlData[ctrlLen++] = (item_curtainposition->valueint>100)?100:item_curtainposition->valueint;
        serial_send_handler(SERIAL_TYPE_CURTAIN_CTRL,ctrlLen,crtlData);
    }   
    else
    {
        cJSON_Delete(request_root);
        return -1;
    } 

    cJSON_Delete(request_root);
    return 0;
}


static int curtain_property_get_event_handler(const int devid, 
        const char *request, const int request_len, char **response, int *response_len)
{
    printf("Property Get Received, Devid: %d, Request: %s", devid, request);
    
    uint8_t ctrlLen = 0;
    uint8_t crtlData[32];

    crtlData[ctrlLen++] = 0x01;
    crtlData[ctrlLen++] = 0x02;
    crtlData[ctrlLen++] = 0x01;
    serial_send_handler(SERIAL_TYPE_CURTAIN_CTRL,ctrlLen,crtlData);
    return SUCCESS_RETURN;
}


static int curtain_trigger_event_reply_event_handler(const int devid, 
        const int msgid, const int code, const char *eventid,
        const int eventid_len, const char *message, const int message_len)
{
    printf("Trigger Event Reply Received, Devid: %d, Message ID: %d, Code: %d, EventID: %.*s, Message: %.*s", 
                devid,msgid, code,eventid_len, eventid, message_len, message);

    return 0;
}


static int curtain_timestamp_reply_event_handler(const char *timestamp)
{
    printf("Current Timestamp: %s", timestamp);

    return 0;
}


/** type:
  *
  * 0 - new firmware exist
  *
  */
static int curtain_fota_event_handler(int type, const char *version)
{
    char buffer[128] = {0};
    int buffer_length = 128;
    fly_curtain_ctx_t *curtain_ctx = fly_curtain_get_ctx();

    if (type == 0) {
        printf("New Firmware Version: %s", version);

        IOT_Linkkit_Query(curtain_ctx->master_devid, ITM_MSG_QUERY_FOTA_DATA, (unsigned char *)buffer, buffer_length);
    }

    return 0;
}


void curtain_post_property(void)
{
    int res = 0;
    fly_curtain_ctx_t *curtain_ctx = fly_curtain_get_ctx();

    cJSON *dev_property ;
    dev_property = cJSON_CreateObject();
    if(!dev_property)
    {
        return;
    }

    if(fly_curtain_ctrl.ctrlCode == 0x03)
    {
        if((fly_curtain_ctrl.payload[0] == 0x01) || \
            (fly_curtain_ctrl.payload[0] == 0x02) || \
            (fly_curtain_ctrl.payload[0] == 0x03))
        {
            cJSON_AddNumberToObject(dev_property,"CurtainOperation",fly_curtain_ctrl.payload[0]);
        }
        else if(fly_curtain_ctrl.payload[0] == 0x04)
        {
            cJSON_AddNumberToObject(dev_property,"CurtainPosition",fly_curtain_ctrl.payload[1]);
        }
    }

    unsigned char *tempString = (unsigned char *)cJSON_PrintUnformatted(dev_property);
    res = IOT_Linkkit_Report(curtain_ctx->master_devid, ITM_MSG_POST_PROPERTY,tempString, strlen(tempString));
    cJSON_free(tempString);

    printf("Post Curtain Property Message ID: %d", res);
    cJSON_Delete(dev_property);
}


void curtain_post_event(void)
{
    int res = 0;
    cJSON *error_event ;
    error_event = cJSON_CreateObject();
    if(!error_event)
    {
        return;
    }
    fly_curtain_ctx_t *curtain_ctx = fly_curtain_get_ctx();
    cJSON_AddNumberToObject(error_event,"Error",flyCurtainError);
    unsigned char *tempString = (unsigned char *)cJSON_PrintUnformatted(error_event);
    res = IOT_Linkkit_Report(curtain_ctx->master_devid, ITM_MSG_POST_PROPERTY,tempString, strlen(tempString));
    cJSON_free(tempString);

    printf("Post Curtain Property Message ID: %d", res);
    cJSON_Delete(error_event);
}


void curtain_deviceinfo_update(void)
{
    int res = 0;
    fly_curtain_ctx_t *curtain_ctx = fly_curtain_get_ctx();
    char *device_info_update = "[{\"attrKey\":\"devType\",\"attrValue\":\"wificurtain\"},{\"attrKey\":\"manufacturer\",\"attrValue\":\"fengliyuan\"}]";
    res = IOT_Linkkit_Report(curtain_ctx->master_devid, ITM_MSG_DEVICEINFO_UPDATE,
                             (unsigned char *)device_info_update, strlen(device_info_update));
    printf("Device Info Update Message ID: %d", res);
}

extern uint8_t productKey[32] ;
extern uint8_t productSecret[32];
extern uint8_t deviceName[32] ;
extern uint8_t deviceSecret[62];
extern uint32_t wireless_key_state;
extern uint32_t wireless_ctrl_state;
int linkkit_main(void *paras)
{
    int                             res = 0;
    uint64_t                        time_prev_sec = 0;
    uint64_t                        time_now_sec = 0;
    uint64_t                        time_begin_sec = 0;
    
    iotx_linkkit_dev_meta_info_t    master_meta_info;
    fly_curtain_ctx_t                *curtain_ctx = fly_curtain_get_ctx();
    memset(curtain_ctx, 0, sizeof(fly_curtain_ctx_t));

    #if !defined(WIFI_PROVISION_ENABLED) || !defined(BUILD_AOS)
        set_iotx_info();
    #endif

    /* Register Callback */
    IOT_RegisterCallback(ITE_CONNECT_SUCC, curtain_connected_event_handler);
    IOT_RegisterCallback(ITE_DISCONNECTED, curtain_disconnected_event_handler);
    IOT_RegisterCallback(ITE_SERVICE_REQUST, curtain_service_request_event_handler);
    IOT_RegisterCallback(ITE_PROPERTY_SET, curtain_property_set_event_handler);
    IOT_RegisterCallback(ITE_PROPERTY_GET, curtain_property_get_event_handler);
    IOT_RegisterCallback(ITE_TRIGGER_EVENT_REPLY, curtain_trigger_event_reply_event_handler);
    IOT_RegisterCallback(ITE_TIMESTAMP_REPLY, curtain_timestamp_reply_event_handler);
    IOT_RegisterCallback(ITE_INITIALIZE_COMPLETED, curtain_initialized);
    IOT_RegisterCallback(ITE_FOTA, curtain_fota_event_handler);
    memset(&master_meta_info, 0, sizeof(iotx_linkkit_dev_meta_info_t));
    //memcpy(master_meta_info.product_key, PRODUCT_KEY, strlen(PRODUCT_KEY));
    //memcpy(master_meta_info.product_secret, PRODUCT_SECRET, strlen(PRODUCT_SECRET));
    //memcpy(master_meta_info.device_name, DEVICE_NAME, strlen(DEVICE_NAME));
    //memcpy(master_meta_info.device_secret, DEVICE_SECRET, strlen(DEVICE_SECRET));
    memcpy(master_meta_info.product_key, productKey, strlen(productKey));
    memcpy(master_meta_info.product_secret, productSecret, strlen(productSecret));
    memcpy(master_meta_info.device_name, deviceName, strlen(deviceName));
    memcpy(master_meta_info.device_secret, deviceSecret, strlen(deviceSecret));

    /* Choose Login Server, domain should be configured before IOT_Linkkit_Open() */
    #if USE_CUSTOME_DOMAIN
        IOT_Ioctl(IOTX_IOCTL_SET_MQTT_DOMAIN, (void *)CUSTOME_DOMAIN_MQTT);
        IOT_Ioctl(IOTX_IOCTL_SET_HTTP_DOMAIN, (void *)CUSTOME_DOMAIN_HTTP);
    #else
        int domain_type = IOTX_CLOUD_REGION_SHANGHAI;
        IOT_Ioctl(IOTX_IOCTL_SET_DOMAIN, (void *)&domain_type);
    #endif

    /* Choose Login Method */
    int dynamic_register = 0;
    IOT_Ioctl(IOTX_IOCTL_SET_DYNAMIC_REGISTER, (void *)&dynamic_register);

    /* Choose Whether You Need Post Property/Event Reply */
    int post_event_reply = 0;
    IOT_Ioctl(IOTX_IOCTL_RECV_EVENT_REPLY, (void *)&post_event_reply);

    /* Create Master Device Resources */
    curtain_ctx->master_devid = IOT_Linkkit_Open(IOTX_LINKKIT_DEV_TYPE_MASTER, &master_meta_info);
    if (curtain_ctx->master_devid < 0) {
        printf("IOT_Linkkit_Open Failed\n");
        return -1;
    }

    /* Start Connect Aliyun Server */
    do 
    {
        HAL_SleepMs(1000);
        res = IOT_Linkkit_Connect(curtain_ctx->master_devid);
    }while(res < 0);

    time_begin_sec = curtain_update_sec();
    while (1) {
        if((wireless_ctrl_state == 1) && curtain_master_dev_available()) {
            wireless_ctrl_state = 0;
            if(fly_curtain_ctrl.ctrlCode == 0x04)
            {
                if(fly_curtain_ctrl.payload[0] == 0x03)
                {
                    flyCurtainError = fly_curtain_ctrl.payload[1];
                    curtain_post_event();   
                }
            }
            else
            {
                curtain_post_property();
            }
        }

        IOT_Linkkit_Yield(curtain_YIELD_TIMEOUT_MS);
        time_now_sec = curtain_update_sec();
        if (time_prev_sec == time_now_sec) {
            continue;
        }

        /* Post Proprety Example */
     
        if (time_now_sec % (60*1000/curtain_YIELD_TIMEOUT_MS) == 0 && curtain_master_dev_available()) {
          uint8_t ctrlLen = 0;
          uint8_t crtlData[32];

          crtlData[ctrlLen++] = 0x01;
          crtlData[ctrlLen++] = 0x02;
          crtlData[ctrlLen++] = 0x01;
          serial_send_handler(SERIAL_TYPE_CURTAIN_CTRL,ctrlLen,crtlData);
        }
        

        /* Device Info Update Example */
        if (time_now_sec % (5*60*1000/curtain_YIELD_TIMEOUT_MS) == 0 && curtain_master_dev_available()) {
            curtain_deviceinfo_update();
        }
        time_prev_sec = time_now_sec;

        
    }

    IOT_Linkkit_Close(curtain_ctx->master_devid);

    IOT_DumpMemoryStats(IOT_LOG_DEBUG);
    IOT_SetLogLevel(IOT_LOG_NONE);

    return 0;
}
#endif
