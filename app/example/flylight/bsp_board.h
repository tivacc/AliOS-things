/*
 * Copyright (C) 2015-2018 Alibaba Group Holding Limited
 */
#ifndef __BSP_BOARD_H__
#define __BSP_BOARD_H__



//bsp api
void wifi_key_init(void);

uint32_t wifi_key_state_func(void);

void wifi_led_init(void);

uint32_t wifi_led_state_func(void);

void wifi_led_config_func(uint8_t state);

void switch_gpio_init(void);

uint32_t switch_state_func(void);

void switch_config_func(uint8_t state);

#endif

