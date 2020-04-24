#include "aos/kernel.h"
#include <k_api.h>
#include "iot_export.h"
#include "iot_import.h"
#include "fly_light_ctrl.h"

#define DIMMING_SPEED				100
#define DIMMING_PRECISION			2
#define ABS_MINUS(x, y)				(x < y ? (y - x) : (x - y))

os_timer_t		smooth_timer;
uint32_t		light_duty_now[PWM_CHANNEL_CNT];
uint32_t		light_duty_cur[PWM_CHANNEL_CNT];

extern light_state_t 	lightState;

void light_pwm_calc(uint8_t lum, uint32_t ct)
{
	uint32_t xm,ym;
	uint32_t temp1,temp2,temp3;
    uint32_t newct = ct/100;

    uint32_t xc = 3053;
	uint32_t yc = 3217;
	uint32_t lc = 100;

	uint32_t xw = 4597;
	uint32_t yw = 4104;
	uint32_t lw = 100;
    if(ct > 7000)
    {
        temp1 = (1000*20064)/(newct*newct*newct);   	//10000
        temp2 = (100*19018)/(newct*newct);        		//10000
        temp3 = (10*2575/newct);                    	//10000
        xm = temp2+temp3+2370-temp1;
    }
    else
    {
        temp1 = (1000*46070)/(newct*newct*newct);
        temp2 = (100*29678)/(newct*newct);
        temp3 = (10*991/newct);
        xm = temp2+temp3+2441-temp1;
    }

    ym = (28700*xm - 3*xm*xm  - 2750*10000)/10000; //10000

	printf("xm=%d,ym=%d\n", xm,ym);

	double test1=  ((xm-xc)*lum*yw);
	double test2=  ((xw-xm)*lum*yc);

    light_duty_cur[0]=(test1/((xw-xm)*yc+(xm-xc)*ym))*10;
	light_duty_cur[1]=(test2/((xw-xm)*yc+(xm-xc)*ym))*10;
}

void light_ctrl_smooth_timer_proc(void* arg)
{
	uint8_t	i;	
	for(i = 0; i < PWM_CHANNEL_CNT; i++)
	{	
		if((light_duty_now[i] + DIMMING_PRECISION) >= light_duty_cur[i])
		{
			light_duty_now[i] = light_duty_cur[i];
		}
		else
		{
			light_duty_now[i] = light_duty_now[i]+DIMMING_PRECISION;
		}
	}

	pwm_set_duty(light_duty_now[LIGHT_CHANNEL_LUM], LIGHT_CHANNEL_LUM);
	pwm_set_duty(light_duty_now[LIGHT_CHANNEL_CT], LIGHT_CHANNEL_CT);		
	pwm_start();	

	if((light_duty_now[LIGHT_CHANNEL_LUM] == light_duty_cur[LIGHT_CHANNEL_LUM]) &&\
				(light_duty_now[LIGHT_CHANNEL_CT] == light_duty_cur[LIGHT_CHANNEL_CT]))
	{
		os_timer_disarm(&smooth_timer);
	}
}

void  light_ctrl_init(void)
{	
	uint32_t dlum,dct; 
	uint32_t pwm_duty_init[PWM_CHANNEL_CNT];
	
	uint32_t io_info[][3] = 
	{
		{PWM_0_OUT_IO_MUX,PWM_0_OUT_IO_FUNC,PWM_0_OUT_IO_NUM},
		{PWM_1_OUT_IO_MUX,PWM_1_OUT_IO_FUNC,PWM_1_OUT_IO_NUM},
	};

	light_pwm_calc(lightState.lightLum,lightState.lightCt);

	os_timer_setfn(&smooth_timer, light_ctrl_smooth_timer_proc, NULL);
	os_timer_arm(&smooth_timer, 100, true);

	pwm_init(PWM_PERIOD,  pwm_duty_init, PWM_CHANNEL_CNT, io_info);
	pwm_start();
}

void  light_ctrl_smooth()
{
	os_timer_disarm(&smooth_timer);
	os_timer_setfn(&smooth_timer, light_ctrl_smooth_timer_proc, NULL);
	os_timer_arm(&smooth_timer, DIMMING_SPEED , true);
}

void  light_ctrl_onoff(void)
{
	if(lightState.lightOn)
	{
		light_pwm_calc(lightState.lightLum,lightState.lightCt);
	}
	else
	{
		//light_pwm_calc(0,0);
		light_duty_cur[LIGHT_CHANNEL_LUM] = 0;
		light_duty_cur[LIGHT_CHANNEL_CT] = 0;
	}
	
	light_ctrl_smooth();
}

void  light_ctrl_white(void)
{
	if(lightState.lightOn)
	{
		light_pwm_calc(lightState.lightLum,lightState.lightCt);
		light_ctrl_smooth();
	}
}

void light_save_state(uint8_t typeParam,uint32_t lightParam)
{
    if(typeParam == 0)
    {
        lightState.lightOn = lightParam;
    }
    else if(typeParam == 1)
    {
        lightState.lightLum = lightParam;
    }
    else if(typeParam == 2)
    {
        lightState.lightCt = lightParam;
    }
       
    HAL_Kv_Set("fly_light_state",&lightState,sizeof(light_state_t),0);
}

uint32_t light_get_state(uint8_t typeParam)
{
	uint32_t lightParam;
	if(typeParam == 0)
    {
        lightParam = lightState.lightOn;
    }
    else if(typeParam == 1)
    {
        lightParam = lightState.lightLum;
    }
    else if(typeParam == 2)
    {
        lightParam = lightState.lightCt;
    }

    return lightParam;

}