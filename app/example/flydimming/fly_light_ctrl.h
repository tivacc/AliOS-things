#ifndef __FLY_LIGHT_CONTROLLER_H__
#define __FLY_LIGHT_CONTROLLER_H__

#include "../../../platform/mcu/esp8266/bsp/include/driver/gpio.h"
#include "../../../platform/mcu/esp8266/bsp/include/espressif/esp_timer.h"

/* PWM Output Parameter */
#define PWM_PERIOD				1000
#define PWM_TICK_CNT			22727


/* PWM Channel Config */
#define PWM_CHANNEL_CNT			2


/* GPIO for pwm channels */
#define PWM_0_OUT_IO_MUX 		PERIPHS_IO_MUX_MTDI_U
#define PWM_0_OUT_IO_NUM 		12
#define PWM_0_OUT_IO_FUNC  		FUNC_GPIO12

#define PWM_1_OUT_IO_MUX 		PERIPHS_IO_MUX_MTCK_U
#define PWM_1_OUT_IO_NUM 		13
#define PWM_1_OUT_IO_FUNC  		FUNC_GPIO13

/* Light control channel of pwm */
#define LIGHT_CHANNEL_LUM		0
#define LIGHT_CHANNEL_CT		1

typedef struct  light_state_tag
{
	uint8_t lightOn;
	uint8_t lightLum;
	uint32_t lightCt;
}light_state_t;


void  light_ctrl_init(void);

void  light_ctrl_onoff(void);

void  light_ctrl_white(void);

void light_save_state(uint8_t typeParam,uint32_t lightParam);

uint32_t light_get_state(uint8_t typeParam);


#endif /* __FLY_LIGHT_CONTROLLER_H__ */
