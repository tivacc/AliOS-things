
#include "espressif/esp_common.h"
#include "gpio.h"
#include <stdio.h>
#include "aos/kernel.h"
#include "aos/yloop.h"

#define KEY1_GPIO_PIN    GPIO_Pin_14
#define KEY1_GPIO_MODE   GPIO_Mode_Input
#define KEY1_GPIO_PULLUP GPIO_PullUp_EN //GPIO_PullUp_DIS
#define KEY1_GPIO_INTRTYPE GPIO_PIN_INTR_NEGEDGE

#define KEY2_GPIO_PIN    GPIO_Pin_13
#define KEY2_GPIO_MODE   GPIO_Mode_Input
#define KEY2_GPIO_PULLUP GPIO_PullUp_EN //GPIO_PullUp_DIS
#define KEY2_GPIO_INTRTYPE GPIO_PIN_INTR_NEGEDGE

#define KEY3_GPIO_PIN    GPIO_Pin_15
#define KEY3_GPIO_MODE   GPIO_Mode_Input
#define KEY3_GPIO_PULLUP GPIO_PullUp_EN //GPIO_PullUp_DIS
#define KEY3_GPIO_INTRTYPE GPIO_PIN_INTR_NEGEDGE

#define KEY4_GPIO_PIN    GPIO_Pin_5
#define KEY4_GPIO_MODE   GPIO_Mode_Input
#define KEY4_GPIO_PULLUP GPIO_PullUp_EN //GPIO_PullUp_DIS
#define KEY4_GPIO_INTRTYPE GPIO_PIN_INTR_NEGEDGE

#define FLY_KEY_CONFIG          0

static uint64_t   key1_time = 0;
static uint64_t   key2_time = 0;
static uint64_t   key3_time = 0;
static uint64_t   key4_time = 0;

static void key1_poll_func(void *arg)
{
    #if FLY_KEY_CONFIG
    uint32_t level = GPIO_INPUT_GET(14);
    uint64_t diff;

    if (level == 0) {
        aos_post_delayed_action(10, key1_poll_func, NULL);
    } else {
        diff = aos_now_ms() - key1_time;
        if (diff > 6000) { /*long long press */
            key1_time = 0;
            aos_post_event(EV_KEY, CODE_BOOT, VALUE_KEY_LLTCLICK);
        } else if (diff > 2000) { /* long press */
            key1_time = 0;
            aos_post_event(EV_KEY, CODE_BOOT, VALUE_KEY_LTCLICK);
        } else if (diff > 40) { /* short press */
            key1_time = 0;
            aos_post_event(EV_KEY, CODE_BOOT, VALUE_KEY_CLICK);
        } else {
            aos_post_delayed_action(10, key1_poll_func, NULL);
        }
    }
    #endif
}

static void fly_key1_isr_handler()
{
    #if FLY_KEY_CONFIG
    uint32_t level = GPIO_INPUT_GET(14);

    if ((level == 0) && (key1_time == 0)) {
        key1_time = aos_now_ms();
        aos_schedule_call(key1_poll_func, NULL);
    }
    #endif
}


static void key2_poll_func(void *arg)
{
    #if FLY_KEY_CONFIG
    uint32_t level = GPIO_INPUT_GET(13);
    uint64_t diff;

    if (level == 0) {
        aos_post_delayed_action(10, key2_poll_func, NULL);
    } else {
        diff = aos_now_ms() - key2_time;
        if (diff > 40) { /* short press */
            key2_time = 0;
            aos_post_event(EV_KEY, CODE_BOOT, VALUE_KEY_CLICK);
        } else {
            aos_post_delayed_action(10, key2_poll_func, NULL);
        }
    }
    #endif
}

static void fly_key2_isr_handler()
{
    #if FLY_KEY_CONFIG
    uint32_t level = GPIO_INPUT_GET(13);

    if ((level == 0) && (key2_time == 0)) {
        key2_time = aos_now_ms();
        aos_schedule_call(key2_poll_func, NULL);
    }
    #endif
}


static void key3_poll_func(void *arg)
{
    #if FLY_KEY_CONFIG
    uint32_t level = GPIO_INPUT_GET(15);
    uint64_t diff;

    if (level == 0) {
        aos_post_delayed_action(10, key3_poll_func, NULL);
    } else {
        diff = aos_now_ms() - key3_time;
        if (diff > 40) { /* short press */
            key3_time = 0;
            aos_post_event(EV_KEY, CODE_BOOT, VALUE_KEY_CLICK);
        } else {
            aos_post_delayed_action(10, key3_poll_func, NULL);
        }
    }
    #endif
}

static void fly_key3_isr_handler()
{
    #if FLY_KEY_CONFIG
    uint32_t level = GPIO_INPUT_GET(15);

    if ((level == 0) && (key3_time == 0)) {
        key3_time = aos_now_ms();
        aos_schedule_call(key3_poll_func, NULL);
    }
    #endif
}

static void key4_poll_func(void *arg)
{
    #if FLY_KEY_CONFIG
    uint32_t level = GPIO_INPUT_GET(5);
    uint64_t diff;

    if (level == 0) {
        aos_post_delayed_action(10, key4_poll_func, NULL);
    } else {
        diff = aos_now_ms() - key4_time;
        if (diff > 40) { /* short press */
            key4_time = 0;
            aos_post_event(EV_KEY, CODE_BOOT, VALUE_KEY_CLICK);
        } else {
            aos_post_delayed_action(10, key4_poll_func, NULL);
        }
    }
    #endif
}

static void fly_key4_isr_handler()
{
    #if FLY_KEY_CONFIG
    uint32_t level = GPIO_INPUT_GET(5);

    if ((level == 0) && (key4_time == 0)) {
        key4_time = aos_now_ms();
        aos_schedule_call(key4_poll_func, NULL);
    }
    #endif
}

static void key_gpio_isr(void *arg)
{
    #if FLY_KEY_CONFIG
    uint32_t gpio_status = GPIO_REG_READ(GPIO_STATUS_ADDRESS);

    GPIO_REG_WRITE(GPIO_STATUS_W1TC_ADDRESS, gpio_status);

    if (gpio_status & (1 << 14))
    {
        fly_key1_isr_handler();
    }
    else if (gpio_status & (1 << 13))
    {
        fly_key2_isr_handler();
    }
    else if (gpio_status & (1 << 15))
    {
        fly_key3_isr_handler();
    }
    else if (gpio_status & (1 << 5))
    {
        fly_key4_isr_handler();
    }
    else
    {
        ;
    }

    #endif
}


static void key_gpio_enable_isr(void)
{
    #if FLY_KEY_CONFIG
    _xt_isr_unmask(1 << ETS_GPIO_INUM);
    #endif
}

void key_gpio_init(void)
{
    #if FLY_KEY_CONFIG
    GPIO_ConfigTypeDef key_gpio_cnf;

    gpio_intr_handler_register(key_gpio_isr, NULL);

    key_gpio_cnf.GPIO_Pin = KEY1_GPIO_PIN;
    key_gpio_cnf.GPIO_Mode = KEY1_GPIO_MODE;
    key_gpio_cnf.GPIO_Pullup = KEY1_GPIO_PULLUP;
    key_gpio_cnf.GPIO_IntrType = KEY1_GPIO_INTRTYPE;
    gpio_config(&key_gpio_cnf);

    key_gpio_cnf.GPIO_Pin = KEY2_GPIO_PIN;
    key_gpio_cnf.GPIO_Mode = KEY2_GPIO_MODE;
    key_gpio_cnf.GPIO_Pullup = KEY2_GPIO_PULLUP;
    key_gpio_cnf.GPIO_IntrType = KEY2_GPIO_INTRTYPE;
    gpio_config(&key_gpio_cnf);

    key_gpio_cnf.GPIO_Pin = KEY3_GPIO_PIN;
    key_gpio_cnf.GPIO_Mode = KEY3_GPIO_MODE;
    key_gpio_cnf.GPIO_Pullup = KEY3_GPIO_PULLUP;
    key_gpio_cnf.GPIO_IntrType = KEY3_GPIO_INTRTYPE;
    gpio_config(&key_gpio_cnf);

    key_gpio_cnf.GPIO_Pin = KEY4_GPIO_PIN;
    key_gpio_cnf.GPIO_Mode = KEY4_GPIO_MODE;
    key_gpio_cnf.GPIO_Pullup = KEY4_GPIO_PULLUP;
    key_gpio_cnf.GPIO_IntrType = KEY4_GPIO_INTRTYPE;
    gpio_config(&key_gpio_cnf);

    key_gpio_enable_isr();

    #endif
}
