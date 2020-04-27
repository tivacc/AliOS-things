/*
 * Copyright (C) 2015-2018 Alibaba Group Holding Limited
 */
#ifndef __BSP_BOARD_H__
#define __BSP_BOARD_H__

#define SERIAL_TYPE_KEY_WRITE    1

typedef struct fly_key_write_tag {
    uint8_t payload[32];
    uint8_t checkSumH;
    uint8_t checkSumL;
    uint8_t finishCode1;
    uint8_t finishCode2;
}fly_key_write_t;




extern fly_key_write_t fly_key_write;
//bsp api
void wifi_key_init(void);

uint32_t wifi_key_state_func(void);

void wifi_led_init(void);

uint32_t wifi_led_state_func(void);

void wifi_led_config_func(uint8_t state);

void zcd_gpio_init(void);

uint8_t serial_init(void);

uint8_t serial_receive_handler(uint8_t serialType);

uint8_t serial_send_handler(uint8_t serialType,uint8_t datLen,uint8_t *dataSend);

#endif

