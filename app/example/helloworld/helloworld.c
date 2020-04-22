/*
 * Copyright (C) 2015-2017 Alibaba Group Holding Limited
 */

#include <stdio.h>
#include "cJSON.h"
#include <aos/kernel.h>


int application_start(int argc, char *argv[])
{
    int count = 0;
    int fly_light_state = 0;
    printf("nano entry here!\r\n");
    char *property_payload = "NULL";

    fly_light_state = 0;

    if(fly_light_state)
    {
    	property_payload = "{\"LightState\":1}";
    }
    else
    {
    	property_payload = "{\"LightState\":0}";
    }
    

    while(1) {
        printf("hello world! count %d \r\n", count++);
        printf(property_payload);
        printf("\n");
        aos_msleep(1000);
    };
}
