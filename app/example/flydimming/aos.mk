NAME := flydimming

$(NAME)_MBINS_TYPE := app
$(NAME)_VERSION := 1.0.0
$(NAME)_SUMMARY := fly dimming

$(NAME)_SOURCES :=  app_entry.c bsp_board.c fly_queue.c
$(NAME)_COMPONENTS += linkkit_sdk_c

$(NAME)_COMPONENTS += netmgr cjson


# LINKKITAPP_CONFIG_DEPRECATED ?= n
# LINKKITAPP_CONFIG_PRINT_HEAP ?= n
# LINKKITAPP_CONFIG_COMBOAPP ?= n
GLOBAL_DEFINES += USE_YLOOP

ifeq ($(AOS_COMP_OTA),y)
$(NAME)_COMPONENTS += ota
GLOBAL_DEFINES += ENABLE_AOS_OTA
endif

ifeq ($(FLYDIMMING_CONFIG_CASE_SOLO),y)
$(NAME)_SOURCES += fly_dimming.c 
$(NAME)_SOURCES += fly_light_ctrl.c 
endif


ifeq ($(FLYDIMMING_CONFIG_PRINT_HEAP),y)
$(NAME)_DEFINES += CONFIG_PRINT_HEAP
endif


ifeq ($(AOS_MCU_RDA5981X),y)
GLOBAL_DEFINES += SUPPORT_DEV_AP
endif

ifneq ($(HOST_MCU_FAMILY),mcu_esp8266)
$(NAME)_COMPONENTS  += cli
else
GLOBAL_DEFINES += ESP8266_CHIPSET
endif


GLOBAL_INCLUDES += ./

