/*
 * Copyright (C) 2015-2018 Alibaba Group Holding Limited
 */
#ifndef __BSP_BOARD_H__
#define __BSP_BOARD_H__

//1 -- WIFI&SUBG   0 -- WIFI
#define DEVICE_SUPPORT_SUBG		1


//bsp api
void wifi_key_init(void);

uint32_t wifi_key_state_func(void);

void wifi_led_init(void);

uint32_t wifi_led_state_func(void);

void wifi_led_config_func(uint8_t state);

void led_gpio_init(void);

uint32_t led_state_func(void);

void led_config_func(uint8_t state);

#if DEVICE_SUPPORT_SUBG == 1
void wire_gpio_init(void);

void wire_gpio_init1(void);

uint32_t wire_datap_state_func(void);

uint32_t wire_datam_state_func(void);

void subg_key_init(void);

void subg_key_config_func(uint8_t keyCh,uint8_t state);

uint32_t subg_key_state_func(void);
#endif

#endif

