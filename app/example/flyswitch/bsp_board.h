/*
 * Copyright (C) 2015-2018 Alibaba Group Holding Limited
 */
#ifndef __BSP_BOARD_H__
#define __BSP_BOARD_H__

#define CURTAIN_ID               0xFEFE
#define CURTAIN_CHECK_CRC        0xFFFF

#define CURTAIN_START_CODE		 0x55

#define SERIAL_TYPE_KEY_WRITE	 1
#define SERIAL_TYPE_CURTAIN_CTRL 2

typedef struct fly_key_write_tag {
    uint8_t payload[32];
    uint8_t checkSumH;
    uint8_t checkSumL;
    uint8_t finishCode1;
    uint8_t finishCode2;
}fly_key_write_t;


typedef struct fly_curtain_ctrl_tag {
    uint8_t startCode;
    uint8_t devAddrH;
    uint8_t devAddrL;
    uint8_t ctrlCode;
    uint8_t payload[32];
    uint8_t checkSumH;
    uint8_t checkSumL;
}fly_curtain_ctrl_t;


extern fly_key_write_t fly_key_write;
extern fly_curtain_ctrl_t fly_curtain_ctrl;
//bsp api
void wifi_key_init(void);

uint32_t wifi_key_state_func(void);

void wifi_led_init(void);

uint32_t wifi_led_state_func(void);

void wifi_led_config_func(uint8_t state);

uint8_t serial_init(void);

uint8_t serial_receive_handler(uint8_t serialType);

uint8_t serial_send_handler(uint8_t serialType,uint8_t datLen,uint8_t *dataSend);

#endif

