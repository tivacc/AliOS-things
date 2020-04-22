/*
 * Copyright (C) 2015-2018 Alibaba Group Holding Limited
 */
#ifndef __APP_ENTRY_H__
#define __APP_ENTRY_H__

#include "aos/kernel.h"

typedef struct {
    int argc;
    char **argv;
}app_main_paras_t;

#ifdef EN_COMBO_NET
#include "combo_devinfo.h"
#else
#if 0
#define PRODUCT_KEY      "a18CSK69Hbs"
#define PRODUCT_SECRET   "LovrsAD3vkfJPIig"
#define DEVICE_NAME      "light1"
#define DEVICE_SECRET    "HLlq7zziHmaeFGmUoHB0wwwbIdwAz0M7"
#endif
#if 1
#define PRODUCT_KEY      "a1sj8WGN4yq"
#define PRODUCT_SECRET   "QMKf95FWlY4wgajH"
#define DEVICE_NAME      "light1"
#define DEVICE_SECRET    "hPvyUzpW4DmeWjAfo9QJogm6vmPqe7cF"
#endif
#endif


int linkkit_main(void *paras);
#endif