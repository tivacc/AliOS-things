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

//***********************************************************

#define USE_CUSTOME_DOMAIN          (0)
#if USE_CUSTOME_DOMAIN
    #define CUSTOME_DOMAIN_MQTT     "iot-as-mqtt.cn-shanghai.aliyuncs.com"
    #define CUSTOME_DOMAIN_HTTP     "iot-auth.cn-shanghai.aliyuncs.com"
#endif

#define LIGHT_YIELD_TIMEOUT_MS      (200)
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
} fly_light_ctx_t;

static fly_light_ctx_t fly_light_ctx;

//***********************************************************
static uint64_t light_update_sec(void)
{
    static uint64_t time_start_ms = 0;

    if (time_start_ms == 0) {
        time_start_ms = HAL_UptimeMs();
    }

    return (HAL_UptimeMs() - time_start_ms) / 1000;
}


static fly_light_ctx_t *fly_light_get_ctx(void)
{
    return &fly_light_ctx;
}


static int light_master_dev_available(void)
{
    fly_light_ctx_t *light_ctx = fly_light_get_ctx();

    if (light_ctx->cloud_connected && light_ctx->master_initialized) {
        return 1;
    }

    return 0;
}


static int light_initialized(const int devid)
{
    fly_light_ctx_t *light_ctx = fly_light_get_ctx();
    EXAMPLE_TRACE("Device Initialized, Devid: %d", devid);

    if (light_ctx->master_devid == devid) {
        light_ctx->master_initialized = 1;
    }

    return 0;
}


static int light_connected_event_handler(void)
{
    int ret = 0;
    fly_light_ctx_t *light_ctx = fly_light_get_ctx();

    EXAMPLE_TRACE("Cloud Connected");
    extern uint32_t wifi_config_state;
    wifi_config_state = 3;
    light_ctx->cloud_connected = 1;

    #if defined(ENABLE_AOS_OTA) 
    //if connected ,initlize the ota 
    EXAMPLE_TRACE("Initialize OTA parameters");
    /*
    ota_service_t ctx = {0};
    memset(&ctx, 0, sizeof(ota_service_t));
    strncpy(ctx.pk, PRODUCT_KEY, sizeof(ctx.pk)-1);
    strncpy(ctx.dn, DEVICE_NAME, sizeof(ctx.dn)-1);
    strncpy(ctx.ds, DEVICE_SECRET, sizeof(ctx.ds)-1);
    ctx.trans_protcol = 0;
    ctx.dl_protcol = 3;
    ota_service_init(&ctx);
    */

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
    EXAMPLE_TRACE("ota init result: %d", ret);
    #endif

    return 0;
}


int light_connect_fail_handler(void)
{
    EXAMPLE_TRACE("Cloud Connect Fail,Reconnect");
    fly_light_ctx_t *light_ctx = fly_light_get_ctx();
    light_ctx->cloud_connected = 0;

    IOT_Linkkit_Connect(light_ctx->master_devid);
}

void light_reconnect(void *p)
{
    int res = 0;
    fly_light_ctx_t *light_ctx = fly_light_get_ctx();
    light_ctx->cloud_connected = 0;

    extern uint32_t wifi_config_state;
    wifi_config_state = 2;

    do 
    {
        HAL_SleepMs(1000);
        res = IOT_Linkkit_Connect(light_ctx->master_devid);
    }while((res < 0) && (wifi_config_state < 4));

    aos_task_exit(0);
}

static int light_disconnected_event_handler(void)
{
    EXAMPLE_TRACE("Cloud Disconnected");
    extern uint32_t wifi_config_state;
    if(wifi_config_state < 4)
    {
        aos_task_new("light_reconnect", light_reconnect, NULL, 4096);
    }
    
    
    #if defined(ENABLE_AOS_OTA)
    /*
    ota_service_t ctx = {0};
    memset(&ctx, 0, sizeof(ota_service_t));
    strncpy(ctx.pk, PRODUCT_KEY, sizeof(ctx.pk)-1);
    strncpy(ctx.dn, DEVICE_NAME, sizeof(ctx.dn)-1);
    strncpy(ctx.ds, DEVICE_SECRET, sizeof(ctx.ds)-1);
    ctx.trans_protcol = 0;
    ctx.dl_protcol = 3;
    ota_service_deinit(&ctx);
    */
    /*char tempProductKey[PRODUCT_KEY_LEN + 1] = {0};
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
    ota_service_deinit(&ctx);*/
    #endif

    return 0;
}


static int light_service_request_event_handler(const int devid, 
        const char *serviceid, 
        const int serviceid_len,
        const char *request, 
        const int request_len,
        char **response, int *response_len)
{
    int contrastratio = 0, to_cloud = 0;
    cJSON *root = NULL, *item_transparency = NULL, *item_from_cloud = NULL;
    EXAMPLE_TRACE("Service Request Received, Devid: %d, Service ID: %.*s, Payload: %s", 
            devid, serviceid_len,serviceid,request);

    /* Parse Root */
    root = cJSON_Parse(request);
    if (root == NULL || !cJSON_IsObject(root)) {
        EXAMPLE_TRACE("JSON Parse Error");
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
        EXAMPLE_TRACE("transparency: %d", item_transparency->valueint);
        contrastratio = item_transparency->valueint + 1;

        /* Send Service Response To Cloud */
        *response_len = strlen(response_fmt) + 10 + 1;
        *response = (char *)HAL_Malloc(*response_len);
        if (*response == NULL) {
            EXAMPLE_TRACE("Memory Not Enough");
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
        EXAMPLE_TRACE("FromCloud: %d", item_from_cloud->valueint);
        to_cloud = item_from_cloud->valueint + 1;

        /* Send Service Response To Cloud */
        *response_len = strlen(response_fmt) + 10 + 1;
        *response = (char *)HAL_Malloc(*response_len);
        if (*response == NULL) {
            EXAMPLE_TRACE("Memory Not Enough");
            return -1;
        }
        memset(*response, 0, *response_len);
        HAL_Snprintf(*response, *response_len, response_fmt, to_cloud);
        *response_len = strlen(*response);
    }
    cJSON_Delete(root);

    return 0;
}


static int light_property_set_event_handler(const int devid, 
                const char *request, const int request_len)
{
    int res = 0;
    char *response = NULL;
    uint32_t lightState = 0;
    cJSON *request_root = NULL,*item_lightSwitch = NULL;

    fly_light_ctx_t *light_ctx = fly_light_get_ctx();
    EXAMPLE_TRACE("Property Set Received, Devid: %d, Request: %s", devid, request);

    request_root = cJSON_Parse(request);
    if (request_root == NULL) {
        EXAMPLE_TRACE("JSON Parse Error");
        return -1;
    }
    
    item_lightSwitch = cJSON_GetObjectItem(request_root, "LightSwitch");
    if (item_lightSwitch == NULL || !cJSON_IsNumber(item_lightSwitch)) {
        cJSON_Delete(request_root);
        return -1;
    }
    EXAMPLE_TRACE("lightSwitch: %d", item_lightSwitch->valueint);
    if(item_lightSwitch->valueint)
    {
        
        #if DEVICE_SUPPORT_SUBG == 1
        //subg_key_config_func(0,1);
        subg_key_config_func(0,2);
        #else
        led_config_func(1);
        #endif
    }
    else
    {
        #if DEVICE_SUPPORT_SUBG == 1
        //subg_key_config_func(0,0);
        subg_key_config_func(0,2);
        #else
        led_config_func(0);
        #endif
    }
    
    cJSON_Delete(request_root);


    /*
    //reply current state of led
    cJSON *response_root = NULL;
    response_root = cJSON_CreateObject();
    if (response_root == NULL) {
        EXAMPLE_TRACE("No Enough Memory");
        cJSON_Delete(request_root);
        return -1;
    }
    EXAMPLE_TRACE("subg_key_state_func: %d",subg_key_state_func());
    cJSON_AddNumberToObject(response_root, "LightSwitch", subg_key_state_func());   //read the gpio state in json
    response =  cJSON_Print(response_root);                                         //json to string
    res = IOT_Linkkit_Report(light_ctx->master_devid, ITM_MSG_POST_PROPERTY,
                             (unsigned char *)response, strlen(response));          //report to cloud
    cJSON_Delete(response_root);
    EXAMPLE_TRACE("Post Property Message ID: %d", res);
    */

    return 0;
}


static int light_property_get_event_handler(const int devid, 
        const char *request, const int request_len, char **response, int *response_len)
{
    cJSON *request_root = NULL, *item_propertyid = NULL;
    cJSON *response_root = NULL;
    int index = 0;
    EXAMPLE_TRACE("Property Get Received, Devid: %d, Request: %s", devid, request);

    fly_light_ctx_t *light_ctx = fly_light_get_ctx();

    /* Parse Request */
    request_root = cJSON_Parse(request);
    if (request_root == NULL) {
        EXAMPLE_TRACE("JSON Parse Error");
        return -1;
    }

    /* Prepare Response */
    response_root = cJSON_CreateObject();
    if (response_root == NULL) {
        EXAMPLE_TRACE("No Enough Memory");
        cJSON_Delete(request_root);
        return -1;
    }

    for (index = 0; index < cJSON_GetArraySize(request_root); index++) {
        item_propertyid = cJSON_GetArrayItem(request_root, index);
        if (item_propertyid == NULL || !cJSON_IsString(item_propertyid)) {
            EXAMPLE_TRACE("JSON Parse Error");
            cJSON_Delete(request_root);
            cJSON_Delete(response_root);
            return -1;
        }

        EXAMPLE_TRACE("Property ID, index: %d, Value: %s", index, item_propertyid->valuestring);

        if (strcmp("LightSwitch", item_propertyid->valuestring) == 0) {
            #if DEVICE_SUPPORT_SUBG == 1
            cJSON_AddNumberToObject(response_root, "LightSwitch", subg_key_state_func());
            #else
            cJSON_AddNumberToObject(response_root, "LightSwitch", led_state_func());
            #endif
        }
    }
    cJSON_Delete(request_root);

    *response = cJSON_PrintUnformatted(response_root);
    if (*response == NULL) {
        EXAMPLE_TRACE("No Enough Memory");
        cJSON_Delete(response_root);
        return -1;
    }
    *response_len = strlen(*response);
    IOT_Linkkit_Report(light_ctx->master_devid, ITM_MSG_POST_PROPERTY,
                             (unsigned char *)response, *response_len);
    
    EXAMPLE_TRACE("Property Get Response: %s", *response);
    cJSON_free(*response);
    cJSON_Delete(response_root);
    
    return SUCCESS_RETURN;
}


static int light_trigger_event_reply_event_handler(const int devid, 
        const int msgid, const int code, const char *eventid,
        const int eventid_len, const char *message, const int message_len)
{
    EXAMPLE_TRACE("Trigger Event Reply Received, Devid: %d, Message ID: %d, Code: %d, EventID: %.*s, Message: %.*s", 
                devid,msgid, code,eventid_len, eventid, message_len, message);

    return 0;
}


static int light_timestamp_reply_event_handler(const char *timestamp)
{
    EXAMPLE_TRACE("Current Timestamp: %s", timestamp);

    return 0;
}


/** type:
  *
  * 0 - new firmware exist
  *
  */
static int light_fota_event_handler(int type, const char *version)
{
    char buffer[128] = {0};
    int buffer_length = 128;
    fly_light_ctx_t *light_ctx = fly_light_get_ctx();

    if (type == 0) {
        EXAMPLE_TRACE("New Firmware Version: %s", version);

        IOT_Linkkit_Query(light_ctx->master_devid, ITM_MSG_QUERY_FOTA_DATA, (unsigned char *)buffer, buffer_length);
    }

    return 0;
}


void light_post_property(void)
{
    int res = 0;
    fly_light_ctx_t *light_ctx = fly_light_get_ctx();
    char *property_payload = "NULL";

    #if DEVICE_SUPPORT_SUBG == 1
    if(subg_key_state_func() == 1)
    #else
    if(led_state_func() == 1)
    #endif
    {
        //printf("LightSwitch:1\r\n");
        property_payload = "{\"LightSwitch\":1}";
    }
    else
    {
        //printf("LightSwitch:0\r\n");
        property_payload = "{\"LightSwitch\":0}";
    }

    
    res = IOT_Linkkit_Report(light_ctx->master_devid, ITM_MSG_POST_PROPERTY,
                             (unsigned char *)property_payload, strlen(property_payload));

    EXAMPLE_TRACE("Post Property Message ID: %d", res);
}


void light_post_event(void)
{
    int res = 0;
    fly_light_ctx_t *light_ctx = fly_light_get_ctx();
    char *event_id = "Error";
    char *event_payload = "NULL";

    event_payload = "{\"ErrorCode\":0}"; 
    res = IOT_Linkkit_TriggerEvent(light_ctx->master_devid, event_id, strlen(event_id),
                                   event_payload, strlen(event_payload));
    EXAMPLE_TRACE("Post Event Message ID: %d", res);
}


void light_deviceinfo_update(void)
{
    int res = 0;
    fly_light_ctx_t *light_ctx = fly_light_get_ctx();
    char *device_info_update = "[{\"attrKey\":\"devType\",\"attrValue\":\"wifiLight\"},{\"attrKey\":\"manufacturer\",\"attrValue\":\"fengliyuan\"}]";
    res = IOT_Linkkit_Report(light_ctx->master_devid, ITM_MSG_DEVICEINFO_UPDATE,
                             (unsigned char *)device_info_update, strlen(device_info_update));
    EXAMPLE_TRACE("Device Info Update Message ID: %d", res);
}

#if DEVICE_SUPPORT_SUBG == 1
extern uint8_t InRfData[5];
void subg_post_property(void)
{

    //printf("subg_post_property\r\n");
    int res = 0;
    fly_light_ctx_t *light_ctx = fly_light_get_ctx();

    cJSON *dev_property ;
    cJSON *pro_content;
    dev_property = cJSON_CreateObject();
    if(!dev_property)
    {
        return;
    }

    pro_content = cJSON_CreateObject();
    if(!pro_content)
    {
        return;
    }

    if(1)
    {    
    uint8_t i = 0;
    uint8_t addressBuf[7] = {0};
    for (i = 0; i < 3; i++) {
        #if 0
        //the data#3 is key value depend on low 4bit
        if(i == 2)
        {
            InRfData[i] = InRfData[i] & 0xF0;
        }
        #endif
        HAL_Snprintf((char *)(addressBuf + i * 2), 2 + 1, "%02X", InRfData[i]);
    }
    
    cJSON_AddItemToObject(dev_property,"panelProperty",pro_content);
    cJSON_AddStringToObject(pro_content,"currentAddr",addressBuf);
    if((InRfData[2] & 0x0F) == 0x00)
    {
        //msb first
        //uint8_t temp1 = (InRfData[4]<<4) + (InRfData[3]>>4);
        //uint8_t temp2 = (InRfData[3])&0x0F;
        uint16_t tempValue =  (((uint16_t)(InRfData[3]) << 8) | InRfData[4]) >> 4;
        if(tempValue & 0x0800)
        {
            cJSON_AddNumberToObject(pro_content,"currentTemp",0.0-((((~(tempValue|0xF000))&0xFFFF) + 1)*0.0625));
        }
        else
        {
            cJSON_AddNumberToObject(pro_content,"currentTemp",tempValue*0.0625);
        }         
    }
    else
    {
        cJSON_AddNumberToObject(pro_content,"currentTemp",255); //if temmperature not set ,send default value
    }
    
    unsigned char *tempString = (unsigned char *)cJSON_PrintUnformatted(dev_property);
    res = IOT_Linkkit_Report(light_ctx->master_devid, ITM_MSG_POST_PROPERTY,tempString, strlen(tempString));
    cJSON_free(tempString);

    EXAMPLE_TRACE("Post currentAddress Property Message ID: %d", res);
    cJSON_Delete(dev_property);
    }
    else
    {
        uint8_t j = 0;
        uint8_t addressBuf1[11] = {0};
        for (j = 0; j < 5; j++) 
        {            
            HAL_Snprintf((char *)(addressBuf1 + j * 2), 2 + 1, "%02X", InRfData[j]);
        }
        
        EXAMPLE_TRACE("Post current Property : %s", addressBuf1);
        cJSON_Delete(pro_content);
        cJSON_Delete(dev_property);
    }      
    

    #if 0
    cJSON_AddStringToObject(devAddr_property,"currentAddress",addressBuf); 
    unsigned char *tempString = (unsigned char *)cJSON_PrintUnformatted(devAddr_property);
    res = IOT_Linkkit_Report(light_ctx->master_devid, ITM_MSG_POST_PROPERTY,tempString, strlen(tempString));
    free(tempString);

    EXAMPLE_TRACE("Post currentAddress Property Message ID: %d", res);
    cJSON_Delete(devAddr_property);

    if((InRfData[2] & 0x0F) == 0x00)
    {
        cJSON *tempValue_property ;
        tempValue_property = cJSON_CreateObject();
        if(!tempValue_property)
        {
            return;
        }

        //lsb first
        uint8_t temp1 = (InRfData[4]<<4) + (InRfData[3]>>4);
        uint8_t temp2 = (InRfData[3])&0x0F;
        cJSON_AddNumberToObject(tempValue_property,"CurrentTemperature",((int)temp1 + (float)(temp2*0.0625)));
        tempString = (unsigned char *)cJSON_PrintUnformatted(tempValue_property);
        res = IOT_Linkkit_Report(light_ctx->master_devid, ITM_MSG_POST_PROPERTY,tempString, strlen(tempString));
        free(tempString);
        EXAMPLE_TRACE("Post CurrentTemperature Property Message ID: %d", res);
        cJSON_Delete(tempValue_property);
    }
    #endif
}
#endif

extern uint8_t productKey[32] ;
extern uint8_t productSecret[32];
extern uint8_t deviceName[32] ;
extern uint8_t deviceSecret[62];
#if DEVICE_SUPPORT_SUBG == 1
extern uint32_t wireless_key_state;
extern uint32_t wireless_ctrl_state;
#endif
int linkkit_main(void *paras)
{
    int                             res = 0;
    uint64_t                        time_prev_sec = 0;
    uint64_t                        time_now_sec = 0;
    uint64_t                        time_begin_sec = 0;
    
    iotx_linkkit_dev_meta_info_t    master_meta_info;
    fly_light_ctx_t                *light_ctx = fly_light_get_ctx();
    memset(light_ctx, 0, sizeof(fly_light_ctx_t));

    #if !defined(WIFI_PROVISION_ENABLED) || !defined(BUILD_AOS)
        set_iotx_info();
    #endif

    /* Register Callback */
    IOT_RegisterCallback(ITE_CONNECT_SUCC, light_connected_event_handler);
    IOT_RegisterCallback(ITE_DISCONNECTED, light_disconnected_event_handler);
    IOT_RegisterCallback(ITE_SERVICE_REQUST, light_service_request_event_handler);
    IOT_RegisterCallback(ITE_PROPERTY_SET, light_property_set_event_handler);
    IOT_RegisterCallback(ITE_PROPERTY_GET, light_property_get_event_handler);
    IOT_RegisterCallback(ITE_TRIGGER_EVENT_REPLY, light_trigger_event_reply_event_handler);
    IOT_RegisterCallback(ITE_TIMESTAMP_REPLY, light_timestamp_reply_event_handler);
    IOT_RegisterCallback(ITE_INITIALIZE_COMPLETED, light_initialized);
    IOT_RegisterCallback(ITE_FOTA, light_fota_event_handler);
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
    light_ctx->master_devid = IOT_Linkkit_Open(IOTX_LINKKIT_DEV_TYPE_MASTER, &master_meta_info);
    if (light_ctx->master_devid < 0) {
        EXAMPLE_TRACE("IOT_Linkkit_Open Failed\n");
        return -1;
    }

    /* Start Connect Aliyun Server */
    do 
    {
        HAL_SleepMs(1000);
        res = IOT_Linkkit_Connect(light_ctx->master_devid);
    }while(res < 0);

    /*if (res < 0) {
        EXAMPLE_TRACE("IOT_Linkkit_Connect Failed,Reconnect.\n");
        //return -1;
    }*/

    time_begin_sec = light_update_sec();
    while (1) {
        #if DEVICE_SUPPORT_SUBG == 1
        if((wireless_key_state == 1) && light_master_dev_available()) {
            wireless_key_state = 0;
            subg_post_property();
        }

        if((wireless_ctrl_state == 1) && light_master_dev_available()) {
            wireless_ctrl_state = 0;
            light_post_property();
        }
        #endif

        IOT_Linkkit_Yield(LIGHT_YIELD_TIMEOUT_MS);
        time_now_sec = light_update_sec();
        if (time_prev_sec == time_now_sec) {
            continue;
        }

        /* Post Event Example */
        if (time_now_sec % (20*1000/LIGHT_YIELD_TIMEOUT_MS) == 0 && light_master_dev_available()) {
            light_post_event();
        }

        /* Post Proprety Example */
        if (time_now_sec % (60*1000/LIGHT_YIELD_TIMEOUT_MS) == 0 && light_master_dev_available()) {
            light_post_property();
        }

        /* Device Info Update Example */
        if (time_now_sec % (5*60*1000/LIGHT_YIELD_TIMEOUT_MS) == 0 && light_master_dev_available()) {
            light_deviceinfo_update();
        }
        time_prev_sec = time_now_sec;
    }

    IOT_Linkkit_Close(light_ctx->master_devid);

    IOT_DumpMemoryStats(IOT_LOG_DEBUG);
    IOT_SetLogLevel(IOT_LOG_NONE);

    return 0;
}
#endif
