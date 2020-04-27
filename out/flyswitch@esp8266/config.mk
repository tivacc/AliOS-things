AOS_SDK_MAKEFILES           		+= ./app/example/flyswitch/aos.mk ./board/esp8266/aos.mk ./middleware/linkkit/sdk-c/aos.mk ./network/netmgr/aos.mk ./utility/cjson/aos.mk ./middleware/uagent/ota/aos.mk ./platform/mcu/esp8266/aos.mk ./kernel/init/aos.mk ./middleware/linkkit/sdk-c/src/ref-impl/hal/os/alios/aos.mk ./middleware/linkkit/sdk-c/src/services/linkkit/cm/aos.mk ./middleware/linkkit/sdk-c/src/services/linkkit/dm/aos.mk ./middleware/linkkit/sdk-c/src/services/linkkit/dev_reset/aos.mk ./middleware/linkkit/sdk-c/src/services/dev_bind/aos.mk ./middleware/linkkit/sdk-c/src/protocol/coap/server/aos.mk ./middleware/linkkit/sdk-c/src/protocol/mqtt/aos.mk ./middleware/linkkit/sdk-c/src/services/awss/aos.mk ./kernel/fs/kv/aos.mk ./osal/aos/aos.mk ./network/yloop/aos.mk ./security/mbedtls/aos.mk ./utility/libc/aos.mk ./kernel/debug/aos.mk ./network/lwip/aos.mk ./security/alicrypto/aos.mk ./middleware/uagent/ota/2nd_boot/aos.mk ./kernel/rhino/aos.mk ./platform/arch/xtensa/lx106/aos.mk ./middleware/uagent/ulog/aos.mk ./utility/activation/aos.mk ./utility/activation/chip_code/aos.mk ./middleware/linkkit/sdk-c/src/infra/utils/aos.mk ./middleware/linkkit/sdk-c/src/infra/log/aos.mk ./middleware/linkkit/sdk-c/src/infra/system/aos.mk ./middleware/linkkit/sdk-c/src/sdk-impl/aos.mk ./middleware/linkkit/sdk-c/src/protocol/coap/CoAPPacket/aos.mk ./kernel/fs/vfs/aos.mk ./security/ls_osa/aos.mk
TOOLCHAIN_NAME            		:= GCC
AOS_SDK_LDFLAGS             		+= -Wl,--gc-sections -Wl,--cref -nostdlib -Lplatform/mcu/esp8266/bsp/lib -Wl,--no-check-sections -Wl,--gc-sections -mtext-section-literals -fno-builtin-printf -Wl,-static -u call_user_start -Wl,-EL -mlongcalls -Lplatform/mcu/esp8266/bsp/ld
AOS_SDK_LDS_FILES                     += platform/mcu/esp8266/bsp/ld/eagle.app.v6.new.1024.app1.ld
AOS_SDK_LDS_INCLUDES                  += 
AOS_SDK_2BOOT_SUPPORT                 += 
AOS_SDK_IMG1_XIP1_LD_FILE                 += 
AOS_SDK_IMG2_XIP2_LD_FILE                 += 
AOS_SDK_CFLAGS			+= -DSYSINFO_PRODUCT_MODEL=\"ALI_AOS_ESP8266\" -DSYSINFO_DEVICE_NAME=\"ESP8266\" -DBOARD_ESP8266 -DAOS_OTA_RECOVERY_TYPE=2 -DAOS_OTA_BANK_DUAL -D_IS_LINKKIT_ -DFORCE_SSL_VERIFY -DCOAP_OBSERVE_SERVER_SUPPORTED -DCOAP_OBSERVE_CLIENT_SUPPORTED -DCOAP_SERV_MULTITHREAD -DCOAP_USE_PLATFORM_MEMORY -DCOAP_USE_PLATFORM_LOG -u call_user_start -fno-inline-functions -ffunction-sections -fdata-sections -mlongcalls -DESPOS_FOR_ESP8266 -Wl,-static -DXT_USE_THREAD_SAFE_CLIB=0 -DSYSINFO_2BOOT_VERSION=\"aos-2nd_boot-1.0.0\"
AOS_SDK_ASMFLAGS			+= 
AOS_SDK_LINK_SCRIPT         		+= 
AOS_SDK_LINK_SCRIPT_CMD    	 	+= 
AOS_SDK_PREBUILT_LIBRARIES 	 	+= ./platform/mcu/esp8266/bsp/lib/libhal.a ./platform/mcu/esp8266/bsp/lib/libcrypto.a ./platform/mcu/esp8266/bsp/lib/libmain.a ./platform/mcu/esp8266/bsp/lib/libcirom.a ./platform/mcu/esp8266/bsp/lib/libnet80211.a ./platform/mcu/esp8266/bsp/lib/libpp.a ./platform/mcu/esp8266/bsp/lib/libwpa.a ./platform/mcu/esp8266/bsp/lib/libphy.a ./platform/mcu/esp8266/bsp/lib/libgcc.a ./platform/mcu/esp8266/bsp/lib/liblwip.a ./platform/mcu/esp8266/bsp/lib/libpwm.a
AOS_SDK_CERTIFICATES       	 	+= 
AOS_SDK_PRE_APP_BUILDS      		+= 
AOS_SDK_LINK_FILES          		+=                                                                          
AOS_SDK_INCLUDES           	 	+=                                                                         -I./app/example/flyswitch/./ -I./board/esp8266/. -I./middleware/linkkit/sdk-c/include/exports -I./middleware/linkkit/sdk-c/include/imports -I./middleware/linkkit/sdk-c/include -I./middleware/linkkit/sdk-c/../../../middleware/linkkit/sdk-c/src/sdk-impl -I./middleware/linkkit/sdk-c/../../../middleware/linkkit/sdk-c/src/infra/utils/digest -I./middleware/linkkit/sdk-c/../../../middleware/linkkit/sdk-c/src/infra/utils -I./middleware/linkkit/sdk-c/../../../middleware/linkkit/sdk-c/src/infra/utils/misc -I./middleware/linkkit/sdk-c/../../../middleware/linkkit/sdk-c/src/infra/log -I./middleware/linkkit/sdk-c/../../../middleware/linkkit/sdk-c/src/infra/system -I./middleware/linkkit/sdk-c/../../../middleware/linkkit/sdk-c/include/exports -I./middleware/linkkit/sdk-c/../../../middleware/linkkit/sdk-c/include/imports -I./middleware/linkkit/sdk-c/../../../middleware/linkkit/sdk-c/include -I./middleware/linkkit/sdk-c/../../../middleware/linkkit/sdk-c/src/protocol/alcs -I./middleware/linkkit/sdk-c/../../../middleware/linkkit/sdk-c/src/protocol/coap/server -I./middleware/linkkit/sdk-c/../../../middleware/linkkit/sdk-c/src/services/linkkit/dev_reset -I./middleware/linkkit/sdk-c/../../../middleware/linkkit/sdk-c/src/services/dev_bind -I./middleware/linkkit/sdk-c/../../../middleware/linkkit/sdk-c/src/services/dev_bind/utility -I./middleware/linkkit/sdk-c/../../../middleware/linkkit/sdk-c/src/services/awss -I./middleware/linkkit/sdk-c/../../../middleware/linkkit/sdk-c/src/services/linkkit/dm -I./middleware/linkkit/sdk-c/../../../middleware/linkkit/sdk-c/src/services/linkkit/cm -I./middleware/linkkit/sdk-c/../../../middleware/linkkit/sdk-c/src/services/mdal/mal -I./middleware/linkkit/sdk-c/../../../middleware/linkkit/sdk-c/src/services/ota -I./middleware/linkkit/sdk-c/../../../middleware/linkkit/sdk-c/src/services/ota/impl -I./middleware/linkkit/sdk-c/../../../middleware/linkkit/sdk-c/src/utils/misc -I./middleware/linkkit/sdk-c/../../../middleware/linkkit/sdk-c/src/protocol/mqtt -I./middleware/linkkit/sdk-c/../../../middleware/linkkit/sdk-c/src/protocol/mqtt/client -I./network/netmgr/include -I./utility/cjson/include -I./middleware/uagent/ota/include -I./middleware/uagent/ota/hal -I./middleware/uagent/ota/ota_core/verify -I./middleware/uagent/ota/2nd_boot -I./platform/mcu/esp8266/bsp/include -I./platform/mcu/esp8266/bsp/include/xtensa -I./platform/mcu/esp8266/bsp/include/espressif -I./platform/mcu/esp8266/bsp/include/espressif/esp8266 -I./platform/mcu/esp8266/bsp/include/lwip -I./platform/mcu/esp8266/bsp/include/lwip/ipv4 -I./platform/mcu/esp8266/bsp/include/lwip/ipv6 -I./platform/mcu/esp8266/bsp/include/driver -I./platform/mcu/esp8266/common -I./platform/mcu/esp8266/hal/rec -I./platform/mcu/esp8266/espos/include -I./kernel/init/include -I./kernel/fs/kv/. -I./kernel/fs/kv/include -I./osal/aos/. -I./network/yloop/include -I./network/yloop/hal -I./security/mbedtls/../include -I./kernel/debug/./ -I./kernel/debug/./include -I./security/alicrypto/../include/icrypto -I./middleware/uagent/ota/2nd_boot/. -I./kernel/rhino/include -I./kernel/rhino/./ -I./platform/arch/xtensa/lx106/. -I./platform/arch/xtensa/lx106/./include -I./platform/arch/xtensa/lx106/./include/frxt -I./middleware/uagent/ulog/include -I./utility/activation/. -I./utility/activation/chip_code/. -I./kernel/fs/vfs/. -I./kernel/fs/vfs/include -I./security/ls_osa/../include/osa -I./include -I./include/hal -I./include/hal/soc -I./include/network
AOS_SDK_DEFINES             		+=                                               -DBUILD_BIN -DUSE_YLOOP -DENABLE_AOS_OTA -DESP8266_CHIPSET -DLOCAL_PORT_ENHANCED_RAND -DWITH_VENDOR_LWIP -DBUILD_AOS -DCONFIG_HTTP_AUTH_TIMEOUT=500 -DCONFIG_MID_HTTP_TIMEOUT=500 -DCONFIG_GUIDER_AUTH_TIMEOUT=500 -DWITH_MQTT_ZIP_TOPIC=1 -DWITH_MQTT_SUB_SHORTCUT=1 -DWITH_MQTT_DYN_BUF=1 -DCOAP_SERV_MULTITHREAD -DNET_WITH_WIFI -DAOS_NETMGR -DOTA_CONFIG_MQTT -DOTA_CONFIG_FW_MD5 -DOTA_CONFIG_RSA -DOTA_SIGNAL_CHANNEL=1 -DCONFIG_ESP_LWIP -DCOAP_WITH_YLOOP -DMBEDTLS_AES_ROM_TABLES -DRHINO_CONFIG_TIMER_TASK_STACK_SIZE=1024 -DAWSS_SUPPORT_DEV_RESET_STATIS -DAWSS_SUPPORT_DEV_BIND_STATIS -DESP8266_CONFIG -DAWSS_SUPPORT_STATIS -DCONFIG_YWSS -DAWSS_SUPPORT_DEV_AP -DAWSS_SUPPORT_SMARTCONFIG -DAWSS_SUPPORT_SMARTCONFIG_WPS -DAWSS_SUPPORT_AHA -DAWSS_SUPPORT_ADHA -DAWSS_SUPPORT_APLIST -DAWSS_DISABLE_REGISTRAR -DAOS_COMP_KV -DOSAL_RHINO -DAOS_HAL -DAOS_LOOP -DAOS_COMP_DEBUG -DWITH_LWIP -DAOS_COMP_RHINO -DAOS_COMP_ULOG -DAOS_COMP_VFS -DMCU_FAMILY=\"mcu_esp8266\"
COMPONENTS                		:= flyswitch board_esp8266 linkkit_sdk_c netmgr cjson ota mcu_esp8266 kernel_init iotx-hal libiot_cm libiot_dm libdev_reset libdev_bind libiot_coap_local libiot_mqtt libawss kv osal_aos yloop imbedtls newlib_stub debug lwip alicrypto ota_2nd_boot rhino arch_xtensa_lx106 ulog activation chip_code libiot_utils libiot_log libiot_system libiot_sdk_impl libiot_coap_coappack vfs ls_osa
PLATFORM_DIRECTORY        		:= esp8266
APP_FULL                  		:= flyswitch
PLATFORM                  		:= esp8266
HOST_MCU_FAMILY                  	:= mcu_esp8266
SUPPORT_MBINS                          := no
APP                       		:= flyswitch
HOST_OPENOCD              		:= esp8266
JTAG              		        := jlink_swd
HOST_ARCH                 		:= xtensa
NO_BUILD_BOOTLOADER           	:= 
NO_BOOTLOADER_REQUIRED         	:= 
flyswitch_LOCATION         := ./app/example/flyswitch/
board_esp8266_LOCATION         := ./board/esp8266/
linkkit_sdk_c_LOCATION         := ./middleware/linkkit/sdk-c/
netmgr_LOCATION         := ./network/netmgr/
cjson_LOCATION         := ./utility/cjson/
ota_LOCATION         := ./middleware/uagent/ota/
mcu_esp8266_LOCATION         := ./platform/mcu/esp8266/
kernel_init_LOCATION         := ./kernel/init/
iotx-hal_LOCATION         := ./middleware/linkkit/sdk-c/src/ref-impl/hal/os/alios/
libiot_cm_LOCATION         := ./middleware/linkkit/sdk-c/src/services/linkkit/cm/
libiot_dm_LOCATION         := ./middleware/linkkit/sdk-c/src/services/linkkit/dm/
libdev_reset_LOCATION         := ./middleware/linkkit/sdk-c/src/services/linkkit/dev_reset/
libdev_bind_LOCATION         := ./middleware/linkkit/sdk-c/src/services/dev_bind/
libiot_coap_local_LOCATION         := ./middleware/linkkit/sdk-c/src/protocol/coap/server/
libiot_mqtt_LOCATION         := ./middleware/linkkit/sdk-c/src/protocol/mqtt/
libawss_LOCATION         := ./middleware/linkkit/sdk-c/src/services/awss/
kv_LOCATION         := ./kernel/fs/kv/
osal_aos_LOCATION         := ./osal/aos/
yloop_LOCATION         := ./network/yloop/
imbedtls_LOCATION         := ./security/mbedtls/
newlib_stub_LOCATION         := ./utility/libc/
debug_LOCATION         := ./kernel/debug/
lwip_LOCATION         := ./network/lwip/
alicrypto_LOCATION         := ./security/alicrypto/
ota_2nd_boot_LOCATION         := ./middleware/uagent/ota/2nd_boot/
rhino_LOCATION         := ./kernel/rhino/
arch_xtensa_lx106_LOCATION         := ./platform/arch/xtensa/lx106/
ulog_LOCATION         := ./middleware/uagent/ulog/
activation_LOCATION         := ./utility/activation/
chip_code_LOCATION         := ./utility/activation/chip_code/
libiot_utils_LOCATION         := ./middleware/linkkit/sdk-c/src/infra/utils/
libiot_log_LOCATION         := ./middleware/linkkit/sdk-c/src/infra/log/
libiot_system_LOCATION         := ./middleware/linkkit/sdk-c/src/infra/system/
libiot_sdk_impl_LOCATION         := ./middleware/linkkit/sdk-c/src/sdk-impl/
libiot_coap_coappack_LOCATION         := ./middleware/linkkit/sdk-c/src/protocol/coap/CoAPPacket/
vfs_LOCATION         := ./kernel/fs/vfs/
ls_osa_LOCATION         := ./security/ls_osa/
flyswitch_SOURCES          += app_entry.c bsp_board.c fly_queue.c fly_switch.c
board_esp8266_SOURCES          += board.c
linkkit_sdk_c_SOURCES          += 
netmgr_SOURCES          += hal/wifi.c interfaces/netmgr_wifi.c netmgr.c
cjson_SOURCES          += cJSON.c cJSON_Utils.c
ota_SOURCES          += hal/ota_hal_module.c hal/ota_hal_os.c hal/ota_hal_plat.c ota_core/download/ota_download_http.c ota_core/ota_service.c ota_core/transport/ota_transport_mqtt.c ota_core/verify/ota_hash.c ota_core/verify/ota_sign.c
mcu_esp8266_SOURCES          += aos/hook_impl.c aos/soc_impl.c bsp/driver/gpio.c bsp/driver/hw_timer.c bsp/driver/i2c_master.c bsp/driver/interrupt.c bsp/driver/spi_interface.c bsp/driver/uart.c bsp/entry.c bsp/heap_iram.c bsp/key.c bsp/syscall.c espos/platform/rhino/espos_misc.c espos/platform/rhino/espos_mutex.c espos/platform/rhino/espos_queue.c espos/platform/rhino/espos_scheduler.c espos/platform/rhino/espos_semaphore.c espos/platform/rhino/espos_spinlock.c espos/platform/rhino/espos_task.c espos/platform/rhino/espos_time.c espos/platform/rhino/espos_timer.c hal/flash.c hal/gpio.c hal/misc.c hal/rec/rec_flash.c hal/rec/rec_sys.c hal/rec/rec_uart.c hal/rec/rec_wdt.c hal/uart.c hal/upgrade_lib.c hal/wifi_port.c
kernel_init_SOURCES          += aos_init.c
iotx-hal_SOURCES          += HAL_AWSS_rhino.c HAL_Crypt_rhino.c HAL_OS_rhino.c HAL_PRODUCT_rhino.c HAL_TCP_rhino.c HAL_TLS_mbedtls.c HAL_UDP_rhino.c
libiot_cm_SOURCES          += ./iotx_cm.c iotx_cm_mqtt.c
libiot_dm_SOURCES          += ./client/dm_client.c ./client/dm_client_adapter.c ./dm_api.c ./dm_cota.c ./dm_fota.c ./dm_ipc.c ./dm_manager.c ./dm_message.c ./dm_message_cache.c ./dm_msg_process.c ./dm_opt.c ./dm_ota.c ./dm_shadow.c ./dm_tsl_alink.c ./dm_utils.c ./server/dm_server.c ./server/dm_server_adapter.c
libdev_reset_SOURCES          += awss_reset.c awss_reset_statis.c
libdev_bind_SOURCES          += awss_bind.c awss_bind_statis.c awss_cmp_coap.c awss_cmp_mqtt.c awss_event.c awss_notify.c awss_packet.c awss_report.c awss_timer.c os/os_misc.c passwd.c
libiot_coap_local_SOURCES          += ./CoAPExport.c ./CoAPMessage.c ./CoAPNetwork.c ./CoAPObserve.c ./CoAPPlatform.c ./CoAPResource.c ./CoAPServer.c
libiot_mqtt_SOURCES          += ./MQTTPacket/MQTTConnectClient.c ./MQTTPacket/MQTTDeserializePublish.c ./MQTTPacket/MQTTPacket.c ./MQTTPacket/MQTTSerializePublish.c ./MQTTPacket/MQTTSubscribeClient.c ./MQTTPacket/MQTTUnsubscribeClient.c ./client/mqtt_client.c
libawss_SOURCES          += awss.c awss_adha.c awss_aha.c awss_aplist.c awss_crypt.c awss_dev_ap.c awss_enrollee.c awss_ht40.c awss_info.c awss_main.c awss_registrar.c awss_smartconfig.c awss_statis.c awss_wifimgr.c awss_wps.c zconfig_ieee80211.c zconfig_protocol.c zconfig_utils.c zconfig_vendor_common.c
kv_SOURCES          += kv.c kv_adapt.c kv_cli.c
osal_aos_SOURCES          += common.c kv.c rhino.c vfs.c
yloop_SOURCES          += hal/loop_hal_alios.c src/device.c src/local_event.c src/select.c src/workqueue.c src/yloop.c
imbedtls_SOURCES          += src/aes.c src/aesni.c src/arc4.c src/asn1parse.c src/asn1write.c src/base64.c src/bignum.c src/blowfish.c src/camellia.c src/ccm.c src/cipher.c src/cipher_wrap.c src/cmac.c src/ctr_drbg.c src/debug.c src/des.c src/dhm.c src/ecdh.c src/ecdsa.c src/ecjpake.c src/ecp.c src/ecp_curves.c src/entropy.c src/entropy_poll.c src/error.c src/gcm.c src/havege.c src/hmac_drbg.c src/mbedtls_alt.c src/mbedtls_net.c src/mbedtls_ssl.c src/md.c src/md2.c src/md4.c src/md5.c src/md_wrap.c src/memory_buffer_alloc.c src/net_sockets.c src/oid.c src/padlock.c src/pem.c src/pk.c src/pk_wrap.c src/pkcs11.c src/pkcs12.c src/pkcs5.c src/pkparse.c src/pkwrite.c src/platform.c src/ripemd160.c src/rsa.c src/sha1.c src/sha256.c src/sha512.c src/ssl_cache.c src/ssl_ciphersuites.c src/ssl_cli.c src/ssl_cookie.c src/ssl_srv.c src/ssl_ticket.c src/ssl_tls.c src/threading.c src/timing.c src/version.c src/version_features.c src/x509.c src/x509_create.c src/x509_crl.c src/x509_crt.c src/x509_csr.c src/x509write_crt.c src/x509write_csr.c src/xtea.c
newlib_stub_SOURCES          += newlib_stub.c
debug_SOURCES          += debug_backtrace.c debug_cpuusage.c debug_infoget.c debug_overview.c debug_panic.c
lwip_SOURCES          += 
alicrypto_SOURCES          += ./api/src/api_aes.c ./api/src/api_hash.c ./api/src/api_hmac.c ./api/src/api_init.c ./api/src/api_rand.c ./api/src/api_rsa.c ./api/src/api_sm2.c ./api/src/api_sm4.c ./core/src/aes.c ./core/src/asn1parse.c ./core/src/bignum.c ./core/src/ecp.c ./core/src/ecp_curves.c ./core/src/hash_wrap.c ./core/src/hmac.c ./core/src/md5.c ./core/src/oid.c ./core/src/rsa.c ./core/src/sha1.c ./core/src/sha256.c ./core/src/sm2.c ./core/src/sm3.c ./core/src/sm4.c ./sal/src/sal_aes.c ./sal/src/sal_hash.c ./sal/src/sal_hmac.c ./sal/src/sal_rand.c ./sal/src/sal_rsa.c ./sal/src/sal_sm2.c ./sal/src/sal_sm4.c
ota_2nd_boot_SOURCES          += nbpatch/flash_hal.c nbpatch/nbpatch.c nbpatch/nbpatch_io.c nbpatch/nbpatch_main.c nbpatch/rec_md5.c nbpatch/rec_verify_fw.c nbpatch/xzdec.c rec_2boot.c rec_libc.c rec_main.c rec_ymodem.c xz/linux/lib/xz/xz_crc32.c xz/linux/lib/xz/xz_dec_lzma2.c xz/linux/lib/xz/xz_dec_stream.c
rhino_SOURCES          += k_buf_queue.c k_dyn_mem_proc.c k_err.c k_event.c k_idle.c k_mm.c k_mm_blk.c k_mm_debug.c k_mutex.c k_obj.c k_pend.c k_queue.c k_ringbuf.c k_sched.c k_sem.c k_spin_lock.c k_stats.c k_sys.c k_task.c k_task_sem.c k_tick.c k_time.c k_timer.c k_workqueue.c
arch_xtensa_lx106_SOURCES          += backtrace.c panic.c port.c xtensa_panic.S xtensa_vectors.S
ulog_SOURCES          += log.c ulog_init.c
activation_SOURCES          += activation.c
chip_code_SOURCES          += chip_code.c
libiot_utils_SOURCES          += ./digest/utils_base64.c ./digest/utils_hmac.c ./digest/utils_md5.c ./digest/utils_sha1.c ./digest/utils_sha256.c ./misc/json_parser.c ./misc/json_token.c ./misc/lite-cjson.c ./misc/mem_stats.c ./misc/utils_epoch_time.c ./misc/utils_event.c ./misc/utils_httpc.c ./misc/utils_net.c ./misc/utils_string.c ./misc/utils_timer.c
libiot_log_SOURCES          += ./iotx_log.c
libiot_system_SOURCES          += ./ca.c ./event.c ./facility/fac_string.c ./guider.c ./report.c
libiot_sdk_impl_SOURCES          += ./deprecated_linkkit/impl_gateway.c ./deprecated_linkkit/impl_ntp.c ./deprecated_linkkit/impl_solo.c ./impl_dynreg.c ./impl_linkkit.c ./impl_logpost.c ./sdk-impl.c
libiot_coap_coappack_SOURCES          += ./CoAPDeserialize.c ./CoAPMessage.c ./CoAPSerialize.c
vfs_SOURCES          += vfs.c vfs_adapt.c vfs_file.c vfs_inode.c
ls_osa_SOURCES          += /src/ls_osa.c
flyswitch_CHECK_HEADERS    += 
board_esp8266_CHECK_HEADERS    += 
linkkit_sdk_c_CHECK_HEADERS    += 
netmgr_CHECK_HEADERS    += 
cjson_CHECK_HEADERS    += 
ota_CHECK_HEADERS    += 
mcu_esp8266_CHECK_HEADERS    += 
kernel_init_CHECK_HEADERS    += 
iotx-hal_CHECK_HEADERS    += 
libiot_cm_CHECK_HEADERS    += 
libiot_dm_CHECK_HEADERS    += 
libdev_reset_CHECK_HEADERS    += 
libdev_bind_CHECK_HEADERS    += 
libiot_coap_local_CHECK_HEADERS    += 
libiot_mqtt_CHECK_HEADERS    += 
libawss_CHECK_HEADERS    += 
kv_CHECK_HEADERS    += 
osal_aos_CHECK_HEADERS    += 
yloop_CHECK_HEADERS    += 
imbedtls_CHECK_HEADERS    += 
newlib_stub_CHECK_HEADERS    += 
debug_CHECK_HEADERS    += 
lwip_CHECK_HEADERS    += 
alicrypto_CHECK_HEADERS    += 
ota_2nd_boot_CHECK_HEADERS    += 
rhino_CHECK_HEADERS    += 
arch_xtensa_lx106_CHECK_HEADERS    += 
ulog_CHECK_HEADERS    += 
activation_CHECK_HEADERS    += 
chip_code_CHECK_HEADERS    += 
libiot_utils_CHECK_HEADERS    += 
libiot_log_CHECK_HEADERS    += 
libiot_system_CHECK_HEADERS    += 
libiot_sdk_impl_CHECK_HEADERS    += 
libiot_coap_coappack_CHECK_HEADERS    += 
vfs_CHECK_HEADERS    += 
ls_osa_CHECK_HEADERS    += 
flyswitch_INCLUDES         := 
board_esp8266_INCLUDES         := 
linkkit_sdk_c_INCLUDES         := 
netmgr_INCLUDES         := 
cjson_INCLUDES         := 
ota_INCLUDES         := 
mcu_esp8266_INCLUDES         := 
kernel_init_INCLUDES         := 
iotx-hal_INCLUDES         := 
libiot_cm_INCLUDES         := -I./middleware/linkkit/sdk-c/src/services/linkkit/cm/../../../../src/infra -I./middleware/linkkit/sdk-c/src/services/linkkit/cm/../../../../src/infra/log -I./middleware/linkkit/sdk-c/src/services/linkkit/cm/../../../../src/infra/utils -I./middleware/linkkit/sdk-c/src/services/linkkit/cm/../../../../src/infra/utils/misc -I./middleware/linkkit/sdk-c/src/services/linkkit/cm/../../../../src/infra/utils/digest -I./middleware/linkkit/sdk-c/src/services/linkkit/cm/../../../../src/infra/system -I./middleware/linkkit/sdk-c/src/services/linkkit/cm/../../../../src/protocol/mqtt -I./middleware/linkkit/sdk-c/src/services/linkkit/cm/../../../../src/protocol/mqtt/client -I./middleware/linkkit/sdk-c/src/services/linkkit/cm/../../../../src/protocol/mqtt/MQTTPacket -I./middleware/linkkit/sdk-c/src/services/linkkit/cm/./example -I./middleware/linkkit/sdk-c/src/services/linkkit/cm/./include
libiot_dm_INCLUDES         := -I./middleware/linkkit/sdk-c/src/services/linkkit/dm/./server -I./middleware/linkkit/sdk-c/src/services/linkkit/dm/./client -I./middleware/linkkit/sdk-c/src/services/linkkit/dm/../../../../src/infra -I./middleware/linkkit/sdk-c/src/services/linkkit/dm/../../../../src/infra/log -I./middleware/linkkit/sdk-c/src/services/linkkit/dm/../../../../src/infra/utils -I./middleware/linkkit/sdk-c/src/services/linkkit/dm/../../../../src/infra/utils/misc -I./middleware/linkkit/sdk-c/src/services/linkkit/dm/../../../../src/infra/utils/digest -I./middleware/linkkit/sdk-c/src/services/linkkit/dm/../../../../src/infra/system -I./middleware/linkkit/sdk-c/src/services/linkkit/dm/../../../../src/services/linkkit/cm -I./middleware/linkkit/sdk-c/src/services/linkkit/dm/../../../../src/services/linkkit/cm/include -I./middleware/linkkit/sdk-c/src/services/linkkit/dm/./example
libdev_reset_INCLUDES         := -I./middleware/linkkit/sdk-c/src/services/linkkit/dev_reset/. -I./middleware/linkkit/sdk-c/src/services/linkkit/dev_reset/.
libdev_bind_INCLUDES         := -I./middleware/linkkit/sdk-c/src/services/dev_bind/. -I./middleware/linkkit/sdk-c/src/services/dev_bind/./os/ -I./middleware/linkkit/sdk-c/src/services/dev_bind/./os/product/ -I./middleware/linkkit/sdk-c/src/services/dev_bind/./os/platform/ -I./middleware/linkkit/sdk-c/src/services/dev_bind/../linkkit/dev_reset/ -I./middleware/linkkit/sdk-c/src/services/dev_bind/. -I./middleware/linkkit/sdk-c/src/services/dev_bind/./os/ -I./middleware/linkkit/sdk-c/src/services/dev_bind/./os/product/ -I./middleware/linkkit/sdk-c/src/services/dev_bind/./os/platform/ -I./middleware/linkkit/sdk-c/src/services/dev_bind/../linkkit/dev_reset/
libiot_coap_local_INCLUDES         := -I./middleware/linkkit/sdk-c/src/protocol/coap/server/../../../../src/infra -I./middleware/linkkit/sdk-c/src/protocol/coap/server/../../../../src/infra/log -I./middleware/linkkit/sdk-c/src/protocol/coap/server/../../../../src/infra/utils -I./middleware/linkkit/sdk-c/src/protocol/coap/server/../../../../src/infra/utils/misc -I./middleware/linkkit/sdk-c/src/protocol/coap/server/../../../../src/infra/utils/digest -I./middleware/linkkit/sdk-c/src/protocol/coap/server/../../../../src/infra/system -I./middleware/linkkit/sdk-c/src/protocol/coap/server/../../../../src/protocol/mqtt -I./middleware/linkkit/sdk-c/src/protocol/coap/server/../../../../src/protocol/mqtt/client -I./middleware/linkkit/sdk-c/src/protocol/coap/server/../../../../src/protocol/mqtt/MQTTPacket
libiot_mqtt_INCLUDES         := -I./middleware/linkkit/sdk-c/src/protocol/mqtt/../../../src/infra -I./middleware/linkkit/sdk-c/src/protocol/mqtt/../../../src/infra/log -I./middleware/linkkit/sdk-c/src/protocol/mqtt/../../../src/infra/utils -I./middleware/linkkit/sdk-c/src/protocol/mqtt/../../../src/infra/utils/misc -I./middleware/linkkit/sdk-c/src/protocol/mqtt/../../../src/infra/utils/digest -I./middleware/linkkit/sdk-c/src/protocol/mqtt/../../../src/infra/system -I./middleware/linkkit/sdk-c/src/protocol/mqtt/./client -I./middleware/linkkit/sdk-c/src/protocol/mqtt/./MQTTPacket
libawss_INCLUDES         := -I./middleware/linkkit/sdk-c/src/services/awss/. -I./middleware/linkkit/sdk-c/src/services/awss/../dev_bind/os/ -I./middleware/linkkit/sdk-c/src/services/awss/../dev_bind/os/product/ -I./middleware/linkkit/sdk-c/src/services/awss/../dev_bind/os/platform/ -I./middleware/linkkit/sdk-c/src/services/awss/. -I./middleware/linkkit/sdk-c/src/services/awss/../dev_bind/os/ -I./middleware/linkkit/sdk-c/src/services/awss/../dev_bind/os/product/ -I./middleware/linkkit/sdk-c/src/services/awss/../dev_bind/os/platform/
kv_INCLUDES         := 
osal_aos_INCLUDES         := 
yloop_INCLUDES         := 
imbedtls_INCLUDES         := 
newlib_stub_INCLUDES         := 
debug_INCLUDES         := 
lwip_INCLUDES         := 
alicrypto_INCLUDES         := -I./security/alicrypto/./core/inc -I./security/alicrypto/./sal/inc -I./security/alicrypto/./api/inc -I./security/alicrypto/./hal/inc -I./security/alicrypto/./config
ota_2nd_boot_INCLUDES         := -I./middleware/uagent/ota/2nd_boot/xz/linux/include/linux -I./middleware/uagent/ota/2nd_boot/xz/linux/lib/xz -I./middleware/uagent/ota/2nd_boot/xz/userspace -I./middleware/uagent/ota/2nd_boot/nbpatch -I./middleware/uagent/ota/2nd_boot/xz/linux/include/linux -I./middleware/uagent/ota/2nd_boot/xz/linux/lib/xz -I./middleware/uagent/ota/2nd_boot/xz/userspace -I./middleware/uagent/ota/2nd_boot/nbpatch
rhino_INCLUDES         := 
arch_xtensa_lx106_INCLUDES         := 
ulog_INCLUDES         := 
activation_INCLUDES         := 
chip_code_INCLUDES         := 
libiot_utils_INCLUDES         := -I./middleware/linkkit/sdk-c/src/infra/utils/../../../src/infra/log -I./middleware/linkkit/sdk-c/src/infra/utils/./misc -I./middleware/linkkit/sdk-c/src/infra/utils/./digest
libiot_log_INCLUDES         := -I./middleware/linkkit/sdk-c/src/infra/log/../../../src/infra/utils -I./middleware/linkkit/sdk-c/src/infra/log/../../../src/infra/utils/misc -I./middleware/linkkit/sdk-c/src/infra/log/../../../src/infra/utils/digest
libiot_system_INCLUDES         := -I./middleware/linkkit/sdk-c/src/infra/system/../../../src/infra/utils -I./middleware/linkkit/sdk-c/src/infra/system/../../../src/infra/utils/misc -I./middleware/linkkit/sdk-c/src/infra/system/../../../src/infra/utils/digest -I./middleware/linkkit/sdk-c/src/infra/system/../../../src/infra/log -I./middleware/linkkit/sdk-c/src/infra/system/../../../src/security/pro -I./middleware/linkkit/sdk-c/src/infra/system/../../../src/security/pro/crypto -I./middleware/linkkit/sdk-c/src/infra/system/../../../src/security/pro/id2 -I./middleware/linkkit/sdk-c/src/infra/system/../../../src/security/pro/km -I./middleware/linkkit/sdk-c/src/infra/system/../../../src/security/pro/itls
libiot_sdk_impl_INCLUDES         := -I./middleware/linkkit/sdk-c/src/sdk-impl/../../src/infra -I./middleware/linkkit/sdk-c/src/sdk-impl/../../src/infra/log -I./middleware/linkkit/sdk-c/src/sdk-impl/../../src/infra/utils -I./middleware/linkkit/sdk-c/src/sdk-impl/../../src/infra/utils/misc -I./middleware/linkkit/sdk-c/src/sdk-impl/../../src/infra/utils/digest -I./middleware/linkkit/sdk-c/src/sdk-impl/../../src/infra/system
libiot_coap_coappack_INCLUDES         := -I./middleware/linkkit/sdk-c/src/protocol/coap/CoAPPacket/../../../../src/infra -I./middleware/linkkit/sdk-c/src/protocol/coap/CoAPPacket/../../../../src/infra/log -I./middleware/linkkit/sdk-c/src/protocol/coap/CoAPPacket/../../../../src/infra/utils -I./middleware/linkkit/sdk-c/src/protocol/coap/CoAPPacket/../../../../src/infra/utils/misc -I./middleware/linkkit/sdk-c/src/protocol/coap/CoAPPacket/../../../../src/infra/utils/digest -I./middleware/linkkit/sdk-c/src/protocol/coap/CoAPPacket/../../../../src/infra/system -I./middleware/linkkit/sdk-c/src/protocol/coap/CoAPPacket/../../../../src/protocol/mqtt -I./middleware/linkkit/sdk-c/src/protocol/coap/CoAPPacket/../../../../src/protocol/coap -I./middleware/linkkit/sdk-c/src/protocol/coap/CoAPPacket/../../../../src/protocol/mqtt/client -I./middleware/linkkit/sdk-c/src/protocol/coap/CoAPPacket/../../../../src/protocol/mqtt/MQTTPacket
vfs_INCLUDES         := 
ls_osa_INCLUDES         := 
flyswitch_DEFINES          := 
board_esp8266_DEFINES          := 
linkkit_sdk_c_DEFINES          := 
netmgr_DEFINES          := 
cjson_DEFINES          := 
ota_DEFINES          := 
mcu_esp8266_DEFINES          := 
kernel_init_DEFINES          := 
iotx-hal_DEFINES          := 
libiot_cm_DEFINES          := 
libiot_dm_DEFINES          := 
libdev_reset_DEFINES          := -DUSE_LPTHREAD -DDEBUG
libdev_bind_DEFINES          := -DUSE_LPTHREAD -DDEBUG
libiot_coap_local_DEFINES          := 
libiot_mqtt_DEFINES          := 
libawss_DEFINES          := -DUSE_LPTHREAD -DDEBUG
kv_DEFINES          := 
osal_aos_DEFINES          := 
yloop_DEFINES          := 
imbedtls_DEFINES          := -DCONFIG_PLAT_AOS -DLWIP_ENABLED -DXTENSE_MALLOC_IRAM -DCONFIG_PLAT_AOS -DLWIP_ENABLED -DXTENSE_MALLOC_IRAM
newlib_stub_DEFINES          := 
debug_DEFINES          := 
lwip_DEFINES          := 
alicrypto_DEFINES          := -DCONFIG_PLAT_AOS -DCONFIG_CRYPT_ALI_ALGO=1 -DCONFIG_SAL_AES_ECB=1 -DCONFIG_HAL_AES_ECB=0 -DCONFIG_SAL_AES_CBC=1 -DCONFIG_HAL_AES_CBC=0 -DCONFIG_SAL_AES_CTR=1 -DCONFIG_HAL_AES_CTR=0 -DCONFIG_SAL_AES_CFB=1 -DCONFIG_HAL_AES_CFB=0 -DCONFIG_SAL_SHA1=1 -DCONFIG_HAL_SHA1=0 -DCONFIG_SAL_SHA256=1 -DCONFIG_HAL_SHA256=0 -DCONFIG_SAL_MD5=1 -DCONFIG_HAL_MD5=0 -DALI_ALGO_AES_ROM_TABLES -DCONFIG_PLAT_AOS -DCONFIG_CRYPT_ALI_ALGO=1 -DCONFIG_SAL_AES_ECB=1 -DCONFIG_HAL_AES_ECB=0 -DCONFIG_SAL_AES_CBC=1 -DCONFIG_HAL_AES_CBC=0 -DCONFIG_SAL_AES_CTR=1 -DCONFIG_HAL_AES_CTR=0 -DCONFIG_SAL_AES_CFB=1 -DCONFIG_HAL_AES_CFB=0 -DCONFIG_SAL_SHA1=1 -DCONFIG_HAL_SHA1=0 -DCONFIG_SAL_SHA256=1 -DCONFIG_HAL_SHA256=0 -DCONFIG_SAL_MD5=1 -DCONFIG_HAL_MD5=0 -DALI_ALGO_AES_ROM_TABLES
ota_2nd_boot_DEFINES          := 
rhino_DEFINES          := 
arch_xtensa_lx106_DEFINES          := 
ulog_DEFINES          := 
activation_DEFINES          := 
chip_code_DEFINES          := 
libiot_utils_DEFINES          := 
libiot_log_DEFINES          := 
libiot_system_DEFINES          := 
libiot_sdk_impl_DEFINES          := 
libiot_coap_coappack_DEFINES          := 
vfs_DEFINES          := 
ls_osa_DEFINES          := -DCONFIG_NET_ENABLED -DCONFIG_NET_ENABLED
flyswitch_CFLAGS           :=  -DSYSINFO_PRODUCT_MODEL=\"ALI_AOS_ESP8266\" -DSYSINFO_DEVICE_NAME=\"ESP8266\" -DBOARD_ESP8266 -DAOS_OTA_RECOVERY_TYPE=2 -DAOS_OTA_BANK_DUAL  -D_IS_LINKKIT_ -DFORCE_SSL_VERIFY -DCOAP_OBSERVE_SERVER_SUPPORTED -DCOAP_OBSERVE_CLIENT_SUPPORTED -DCOAP_SERV_MULTITHREAD -DCOAP_USE_PLATFORM_MEMORY -DCOAP_USE_PLATFORM_LOG      -u call_user_start -fno-inline-functions -ffunction-sections -fdata-sections -mlongcalls -DESPOS_FOR_ESP8266 -Wl,-static -DXT_USE_THREAD_SAFE_CLIB=0                   -DSYSINFO_2BOOT_VERSION=\"aos-2nd_boot-1.0.0\"              -ggdb -Os   -DPLATFORM=\"esp8266\" -DSYSINFO_APP_VERSION=\"app-1.0.0-20200426.0145\"  -include out/config/autoconf.h  
board_esp8266_CFLAGS           :=  -DSYSINFO_PRODUCT_MODEL=\"ALI_AOS_ESP8266\" -DSYSINFO_DEVICE_NAME=\"ESP8266\" -DBOARD_ESP8266 -DAOS_OTA_RECOVERY_TYPE=2 -DAOS_OTA_BANK_DUAL  -D_IS_LINKKIT_ -DFORCE_SSL_VERIFY -DCOAP_OBSERVE_SERVER_SUPPORTED -DCOAP_OBSERVE_CLIENT_SUPPORTED -DCOAP_SERV_MULTITHREAD -DCOAP_USE_PLATFORM_MEMORY -DCOAP_USE_PLATFORM_LOG      -u call_user_start -fno-inline-functions -ffunction-sections -fdata-sections -mlongcalls -DESPOS_FOR_ESP8266 -Wl,-static -DXT_USE_THREAD_SAFE_CLIB=0                   -DSYSINFO_2BOOT_VERSION=\"aos-2nd_boot-1.0.0\"              -ggdb -Os   -DPLATFORM=\"esp8266\" -DSYSINFO_APP_VERSION=\"app-1.0.0-20200426.0145\"  -include out/config/autoconf.h  
linkkit_sdk_c_CFLAGS           :=  -DSYSINFO_PRODUCT_MODEL=\"ALI_AOS_ESP8266\" -DSYSINFO_DEVICE_NAME=\"ESP8266\" -DBOARD_ESP8266 -DAOS_OTA_RECOVERY_TYPE=2 -DAOS_OTA_BANK_DUAL  -D_IS_LINKKIT_ -DFORCE_SSL_VERIFY -DCOAP_OBSERVE_SERVER_SUPPORTED -DCOAP_OBSERVE_CLIENT_SUPPORTED -DCOAP_SERV_MULTITHREAD -DCOAP_USE_PLATFORM_MEMORY -DCOAP_USE_PLATFORM_LOG      -u call_user_start -fno-inline-functions -ffunction-sections -fdata-sections -mlongcalls -DESPOS_FOR_ESP8266 -Wl,-static -DXT_USE_THREAD_SAFE_CLIB=0                   -DSYSINFO_2BOOT_VERSION=\"aos-2nd_boot-1.0.0\"              -ggdb -Os   -DPLATFORM=\"esp8266\" -DSYSINFO_APP_VERSION=\"app-1.0.0-20200426.0145\"  -include out/config/autoconf.h  
netmgr_CFLAGS           :=  -DSYSINFO_PRODUCT_MODEL=\"ALI_AOS_ESP8266\" -DSYSINFO_DEVICE_NAME=\"ESP8266\" -DBOARD_ESP8266 -DAOS_OTA_RECOVERY_TYPE=2 -DAOS_OTA_BANK_DUAL  -D_IS_LINKKIT_ -DFORCE_SSL_VERIFY -DCOAP_OBSERVE_SERVER_SUPPORTED -DCOAP_OBSERVE_CLIENT_SUPPORTED -DCOAP_SERV_MULTITHREAD -DCOAP_USE_PLATFORM_MEMORY -DCOAP_USE_PLATFORM_LOG      -u call_user_start -fno-inline-functions -ffunction-sections -fdata-sections -mlongcalls -DESPOS_FOR_ESP8266 -Wl,-static -DXT_USE_THREAD_SAFE_CLIB=0                   -DSYSINFO_2BOOT_VERSION=\"aos-2nd_boot-1.0.0\"              -ggdb -Os   -DPLATFORM=\"esp8266\" -DSYSINFO_APP_VERSION=\"app-1.0.0-20200426.0145\"  -include out/config/autoconf.h  
cjson_CFLAGS           :=  -DSYSINFO_PRODUCT_MODEL=\"ALI_AOS_ESP8266\" -DSYSINFO_DEVICE_NAME=\"ESP8266\" -DBOARD_ESP8266 -DAOS_OTA_RECOVERY_TYPE=2 -DAOS_OTA_BANK_DUAL  -D_IS_LINKKIT_ -DFORCE_SSL_VERIFY -DCOAP_OBSERVE_SERVER_SUPPORTED -DCOAP_OBSERVE_CLIENT_SUPPORTED -DCOAP_SERV_MULTITHREAD -DCOAP_USE_PLATFORM_MEMORY -DCOAP_USE_PLATFORM_LOG      -u call_user_start -fno-inline-functions -ffunction-sections -fdata-sections -mlongcalls -DESPOS_FOR_ESP8266 -Wl,-static -DXT_USE_THREAD_SAFE_CLIB=0                   -DSYSINFO_2BOOT_VERSION=\"aos-2nd_boot-1.0.0\"              -ggdb -Os   -DPLATFORM=\"esp8266\" -DSYSINFO_APP_VERSION=\"app-1.0.0-20200426.0145\"  -include out/config/autoconf.h  
ota_CFLAGS           :=  -DSYSINFO_PRODUCT_MODEL=\"ALI_AOS_ESP8266\" -DSYSINFO_DEVICE_NAME=\"ESP8266\" -DBOARD_ESP8266 -DAOS_OTA_RECOVERY_TYPE=2 -DAOS_OTA_BANK_DUAL  -D_IS_LINKKIT_ -DFORCE_SSL_VERIFY -DCOAP_OBSERVE_SERVER_SUPPORTED -DCOAP_OBSERVE_CLIENT_SUPPORTED -DCOAP_SERV_MULTITHREAD -DCOAP_USE_PLATFORM_MEMORY -DCOAP_USE_PLATFORM_LOG      -u call_user_start -fno-inline-functions -ffunction-sections -fdata-sections -mlongcalls -DESPOS_FOR_ESP8266 -Wl,-static -DXT_USE_THREAD_SAFE_CLIB=0                   -DSYSINFO_2BOOT_VERSION=\"aos-2nd_boot-1.0.0\"              -ggdb -Os   -DPLATFORM=\"esp8266\" -DSYSINFO_APP_VERSION=\"app-1.0.0-20200426.0145\"  -include out/config/autoconf.h  -Wall -Werror -Wall -Werror
mcu_esp8266_CFLAGS           :=  -DSYSINFO_PRODUCT_MODEL=\"ALI_AOS_ESP8266\" -DSYSINFO_DEVICE_NAME=\"ESP8266\" -DBOARD_ESP8266 -DAOS_OTA_RECOVERY_TYPE=2 -DAOS_OTA_BANK_DUAL  -D_IS_LINKKIT_ -DFORCE_SSL_VERIFY -DCOAP_OBSERVE_SERVER_SUPPORTED -DCOAP_OBSERVE_CLIENT_SUPPORTED -DCOAP_SERV_MULTITHREAD -DCOAP_USE_PLATFORM_MEMORY -DCOAP_USE_PLATFORM_LOG      -u call_user_start -fno-inline-functions -ffunction-sections -fdata-sections -mlongcalls -DESPOS_FOR_ESP8266 -Wl,-static -DXT_USE_THREAD_SAFE_CLIB=0                   -DSYSINFO_2BOOT_VERSION=\"aos-2nd_boot-1.0.0\"              -ggdb -Os   -DPLATFORM=\"esp8266\" -DSYSINFO_APP_VERSION=\"app-1.0.0-20200426.0145\"  -include out/config/autoconf.h  -std=gnu99 -DENABLE_WIFI -Iplatform/mcu/esp8266/bsp
kernel_init_CFLAGS           :=  -DSYSINFO_PRODUCT_MODEL=\"ALI_AOS_ESP8266\" -DSYSINFO_DEVICE_NAME=\"ESP8266\" -DBOARD_ESP8266 -DAOS_OTA_RECOVERY_TYPE=2 -DAOS_OTA_BANK_DUAL  -D_IS_LINKKIT_ -DFORCE_SSL_VERIFY -DCOAP_OBSERVE_SERVER_SUPPORTED -DCOAP_OBSERVE_CLIENT_SUPPORTED -DCOAP_SERV_MULTITHREAD -DCOAP_USE_PLATFORM_MEMORY -DCOAP_USE_PLATFORM_LOG      -u call_user_start -fno-inline-functions -ffunction-sections -fdata-sections -mlongcalls -DESPOS_FOR_ESP8266 -Wl,-static -DXT_USE_THREAD_SAFE_CLIB=0                   -DSYSINFO_2BOOT_VERSION=\"aos-2nd_boot-1.0.0\"              -ggdb -Os   -DPLATFORM=\"esp8266\" -DSYSINFO_APP_VERSION=\"app-1.0.0-20200426.0145\"  -include out/config/autoconf.h  
iotx-hal_CFLAGS           :=  -DSYSINFO_PRODUCT_MODEL=\"ALI_AOS_ESP8266\" -DSYSINFO_DEVICE_NAME=\"ESP8266\" -DBOARD_ESP8266 -DAOS_OTA_RECOVERY_TYPE=2 -DAOS_OTA_BANK_DUAL  -D_IS_LINKKIT_ -DFORCE_SSL_VERIFY -DCOAP_OBSERVE_SERVER_SUPPORTED -DCOAP_OBSERVE_CLIENT_SUPPORTED -DCOAP_SERV_MULTITHREAD -DCOAP_USE_PLATFORM_MEMORY -DCOAP_USE_PLATFORM_LOG      -u call_user_start -fno-inline-functions -ffunction-sections -fdata-sections -mlongcalls -DESPOS_FOR_ESP8266 -Wl,-static -DXT_USE_THREAD_SAFE_CLIB=0                   -DSYSINFO_2BOOT_VERSION=\"aos-2nd_boot-1.0.0\"              -ggdb -Os   -DPLATFORM=\"esp8266\" -DSYSINFO_APP_VERSION=\"app-1.0.0-20200426.0145\"  -include out/config/autoconf.h  
libiot_cm_CFLAGS           :=  -DSYSINFO_PRODUCT_MODEL=\"ALI_AOS_ESP8266\" -DSYSINFO_DEVICE_NAME=\"ESP8266\" -DBOARD_ESP8266 -DAOS_OTA_RECOVERY_TYPE=2 -DAOS_OTA_BANK_DUAL  -D_IS_LINKKIT_ -DFORCE_SSL_VERIFY -DCOAP_OBSERVE_SERVER_SUPPORTED -DCOAP_OBSERVE_CLIENT_SUPPORTED -DCOAP_SERV_MULTITHREAD -DCOAP_USE_PLATFORM_MEMORY -DCOAP_USE_PLATFORM_LOG      -u call_user_start -fno-inline-functions -ffunction-sections -fdata-sections -mlongcalls -DESPOS_FOR_ESP8266 -Wl,-static -DXT_USE_THREAD_SAFE_CLIB=0                   -DSYSINFO_2BOOT_VERSION=\"aos-2nd_boot-1.0.0\"              -ggdb -Os   -DPLATFORM=\"esp8266\" -DSYSINFO_APP_VERSION=\"app-1.0.0-20200426.0145\"  -include out/config/autoconf.h  
libiot_dm_CFLAGS           :=  -DSYSINFO_PRODUCT_MODEL=\"ALI_AOS_ESP8266\" -DSYSINFO_DEVICE_NAME=\"ESP8266\" -DBOARD_ESP8266 -DAOS_OTA_RECOVERY_TYPE=2 -DAOS_OTA_BANK_DUAL  -D_IS_LINKKIT_ -DFORCE_SSL_VERIFY -DCOAP_OBSERVE_SERVER_SUPPORTED -DCOAP_OBSERVE_CLIENT_SUPPORTED -DCOAP_SERV_MULTITHREAD -DCOAP_USE_PLATFORM_MEMORY -DCOAP_USE_PLATFORM_LOG      -u call_user_start -fno-inline-functions -ffunction-sections -fdata-sections -mlongcalls -DESPOS_FOR_ESP8266 -Wl,-static -DXT_USE_THREAD_SAFE_CLIB=0                   -DSYSINFO_2BOOT_VERSION=\"aos-2nd_boot-1.0.0\"              -ggdb -Os   -DPLATFORM=\"esp8266\" -DSYSINFO_APP_VERSION=\"app-1.0.0-20200426.0145\"  -include out/config/autoconf.h  
libdev_reset_CFLAGS           :=  -DSYSINFO_PRODUCT_MODEL=\"ALI_AOS_ESP8266\" -DSYSINFO_DEVICE_NAME=\"ESP8266\" -DBOARD_ESP8266 -DAOS_OTA_RECOVERY_TYPE=2 -DAOS_OTA_BANK_DUAL  -D_IS_LINKKIT_ -DFORCE_SSL_VERIFY -DCOAP_OBSERVE_SERVER_SUPPORTED -DCOAP_OBSERVE_CLIENT_SUPPORTED -DCOAP_SERV_MULTITHREAD -DCOAP_USE_PLATFORM_MEMORY -DCOAP_USE_PLATFORM_LOG      -u call_user_start -fno-inline-functions -ffunction-sections -fdata-sections -mlongcalls -DESPOS_FOR_ESP8266 -Wl,-static -DXT_USE_THREAD_SAFE_CLIB=0                   -DSYSINFO_2BOOT_VERSION=\"aos-2nd_boot-1.0.0\"              -ggdb -Os   -DPLATFORM=\"esp8266\" -DSYSINFO_APP_VERSION=\"app-1.0.0-20200426.0145\"  -include out/config/autoconf.h  
libdev_bind_CFLAGS           :=  -DSYSINFO_PRODUCT_MODEL=\"ALI_AOS_ESP8266\" -DSYSINFO_DEVICE_NAME=\"ESP8266\" -DBOARD_ESP8266 -DAOS_OTA_RECOVERY_TYPE=2 -DAOS_OTA_BANK_DUAL  -D_IS_LINKKIT_ -DFORCE_SSL_VERIFY -DCOAP_OBSERVE_SERVER_SUPPORTED -DCOAP_OBSERVE_CLIENT_SUPPORTED -DCOAP_SERV_MULTITHREAD -DCOAP_USE_PLATFORM_MEMORY -DCOAP_USE_PLATFORM_LOG      -u call_user_start -fno-inline-functions -ffunction-sections -fdata-sections -mlongcalls -DESPOS_FOR_ESP8266 -Wl,-static -DXT_USE_THREAD_SAFE_CLIB=0                   -DSYSINFO_2BOOT_VERSION=\"aos-2nd_boot-1.0.0\"              -ggdb -Os   -DPLATFORM=\"esp8266\" -DSYSINFO_APP_VERSION=\"app-1.0.0-20200426.0145\"  -include out/config/autoconf.h  
libiot_coap_local_CFLAGS           :=  -DSYSINFO_PRODUCT_MODEL=\"ALI_AOS_ESP8266\" -DSYSINFO_DEVICE_NAME=\"ESP8266\" -DBOARD_ESP8266 -DAOS_OTA_RECOVERY_TYPE=2 -DAOS_OTA_BANK_DUAL  -D_IS_LINKKIT_ -DFORCE_SSL_VERIFY -DCOAP_OBSERVE_SERVER_SUPPORTED -DCOAP_OBSERVE_CLIENT_SUPPORTED -DCOAP_SERV_MULTITHREAD -DCOAP_USE_PLATFORM_MEMORY -DCOAP_USE_PLATFORM_LOG      -u call_user_start -fno-inline-functions -ffunction-sections -fdata-sections -mlongcalls -DESPOS_FOR_ESP8266 -Wl,-static -DXT_USE_THREAD_SAFE_CLIB=0                   -DSYSINFO_2BOOT_VERSION=\"aos-2nd_boot-1.0.0\"              -ggdb -Os   -DPLATFORM=\"esp8266\" -DSYSINFO_APP_VERSION=\"app-1.0.0-20200426.0145\"  -include out/config/autoconf.h  
libiot_mqtt_CFLAGS           :=  -DSYSINFO_PRODUCT_MODEL=\"ALI_AOS_ESP8266\" -DSYSINFO_DEVICE_NAME=\"ESP8266\" -DBOARD_ESP8266 -DAOS_OTA_RECOVERY_TYPE=2 -DAOS_OTA_BANK_DUAL  -D_IS_LINKKIT_ -DFORCE_SSL_VERIFY -DCOAP_OBSERVE_SERVER_SUPPORTED -DCOAP_OBSERVE_CLIENT_SUPPORTED -DCOAP_SERV_MULTITHREAD -DCOAP_USE_PLATFORM_MEMORY -DCOAP_USE_PLATFORM_LOG      -u call_user_start -fno-inline-functions -ffunction-sections -fdata-sections -mlongcalls -DESPOS_FOR_ESP8266 -Wl,-static -DXT_USE_THREAD_SAFE_CLIB=0                   -DSYSINFO_2BOOT_VERSION=\"aos-2nd_boot-1.0.0\"              -ggdb -Os   -DPLATFORM=\"esp8266\" -DSYSINFO_APP_VERSION=\"app-1.0.0-20200426.0145\"  -include out/config/autoconf.h  
libawss_CFLAGS           :=  -DSYSINFO_PRODUCT_MODEL=\"ALI_AOS_ESP8266\" -DSYSINFO_DEVICE_NAME=\"ESP8266\" -DBOARD_ESP8266 -DAOS_OTA_RECOVERY_TYPE=2 -DAOS_OTA_BANK_DUAL  -D_IS_LINKKIT_ -DFORCE_SSL_VERIFY -DCOAP_OBSERVE_SERVER_SUPPORTED -DCOAP_OBSERVE_CLIENT_SUPPORTED -DCOAP_SERV_MULTITHREAD -DCOAP_USE_PLATFORM_MEMORY -DCOAP_USE_PLATFORM_LOG      -u call_user_start -fno-inline-functions -ffunction-sections -fdata-sections -mlongcalls -DESPOS_FOR_ESP8266 -Wl,-static -DXT_USE_THREAD_SAFE_CLIB=0                   -DSYSINFO_2BOOT_VERSION=\"aos-2nd_boot-1.0.0\"              -ggdb -Os   -DPLATFORM=\"esp8266\" -DSYSINFO_APP_VERSION=\"app-1.0.0-20200426.0145\"  -include out/config/autoconf.h  
kv_CFLAGS           :=  -DSYSINFO_PRODUCT_MODEL=\"ALI_AOS_ESP8266\" -DSYSINFO_DEVICE_NAME=\"ESP8266\" -DBOARD_ESP8266 -DAOS_OTA_RECOVERY_TYPE=2 -DAOS_OTA_BANK_DUAL  -D_IS_LINKKIT_ -DFORCE_SSL_VERIFY -DCOAP_OBSERVE_SERVER_SUPPORTED -DCOAP_OBSERVE_CLIENT_SUPPORTED -DCOAP_SERV_MULTITHREAD -DCOAP_USE_PLATFORM_MEMORY -DCOAP_USE_PLATFORM_LOG      -u call_user_start -fno-inline-functions -ffunction-sections -fdata-sections -mlongcalls -DESPOS_FOR_ESP8266 -Wl,-static -DXT_USE_THREAD_SAFE_CLIB=0                   -DSYSINFO_2BOOT_VERSION=\"aos-2nd_boot-1.0.0\"              -ggdb -Os   -DPLATFORM=\"esp8266\" -DSYSINFO_APP_VERSION=\"app-1.0.0-20200426.0145\"  -include out/config/autoconf.h  -Wall -Werror -Wall -Werror
osal_aos_CFLAGS           :=  -DSYSINFO_PRODUCT_MODEL=\"ALI_AOS_ESP8266\" -DSYSINFO_DEVICE_NAME=\"ESP8266\" -DBOARD_ESP8266 -DAOS_OTA_RECOVERY_TYPE=2 -DAOS_OTA_BANK_DUAL  -D_IS_LINKKIT_ -DFORCE_SSL_VERIFY -DCOAP_OBSERVE_SERVER_SUPPORTED -DCOAP_OBSERVE_CLIENT_SUPPORTED -DCOAP_SERV_MULTITHREAD -DCOAP_USE_PLATFORM_MEMORY -DCOAP_USE_PLATFORM_LOG      -u call_user_start -fno-inline-functions -ffunction-sections -fdata-sections -mlongcalls -DESPOS_FOR_ESP8266 -Wl,-static -DXT_USE_THREAD_SAFE_CLIB=0                   -DSYSINFO_2BOOT_VERSION=\"aos-2nd_boot-1.0.0\"              -ggdb -Os   -DPLATFORM=\"esp8266\" -DSYSINFO_APP_VERSION=\"app-1.0.0-20200426.0145\"  -include out/config/autoconf.h  -Wall -Werror -Wall -Werror
yloop_CFLAGS           :=  -DSYSINFO_PRODUCT_MODEL=\"ALI_AOS_ESP8266\" -DSYSINFO_DEVICE_NAME=\"ESP8266\" -DBOARD_ESP8266 -DAOS_OTA_RECOVERY_TYPE=2 -DAOS_OTA_BANK_DUAL  -D_IS_LINKKIT_ -DFORCE_SSL_VERIFY -DCOAP_OBSERVE_SERVER_SUPPORTED -DCOAP_OBSERVE_CLIENT_SUPPORTED -DCOAP_SERV_MULTITHREAD -DCOAP_USE_PLATFORM_MEMORY -DCOAP_USE_PLATFORM_LOG      -u call_user_start -fno-inline-functions -ffunction-sections -fdata-sections -mlongcalls -DESPOS_FOR_ESP8266 -Wl,-static -DXT_USE_THREAD_SAFE_CLIB=0                   -DSYSINFO_2BOOT_VERSION=\"aos-2nd_boot-1.0.0\"              -ggdb -Os   -DPLATFORM=\"esp8266\" -DSYSINFO_APP_VERSION=\"app-1.0.0-20200426.0145\"  -include out/config/autoconf.h  -Wall -Werror -Wall -Werror
imbedtls_CFLAGS           :=  -DSYSINFO_PRODUCT_MODEL=\"ALI_AOS_ESP8266\" -DSYSINFO_DEVICE_NAME=\"ESP8266\" -DBOARD_ESP8266 -DAOS_OTA_RECOVERY_TYPE=2 -DAOS_OTA_BANK_DUAL  -D_IS_LINKKIT_ -DFORCE_SSL_VERIFY -DCOAP_OBSERVE_SERVER_SUPPORTED -DCOAP_OBSERVE_CLIENT_SUPPORTED -DCOAP_SERV_MULTITHREAD -DCOAP_USE_PLATFORM_MEMORY -DCOAP_USE_PLATFORM_LOG      -u call_user_start -fno-inline-functions -ffunction-sections -fdata-sections -mlongcalls -DESPOS_FOR_ESP8266 -Wl,-static -DXT_USE_THREAD_SAFE_CLIB=0                   -DSYSINFO_2BOOT_VERSION=\"aos-2nd_boot-1.0.0\"              -ggdb -Os   -DPLATFORM=\"esp8266\" -DSYSINFO_APP_VERSION=\"app-1.0.0-20200426.0145\"  -include out/config/autoconf.h  -Wall -Werror -Wall -Werror
newlib_stub_CFLAGS           :=  -DSYSINFO_PRODUCT_MODEL=\"ALI_AOS_ESP8266\" -DSYSINFO_DEVICE_NAME=\"ESP8266\" -DBOARD_ESP8266 -DAOS_OTA_RECOVERY_TYPE=2 -DAOS_OTA_BANK_DUAL  -D_IS_LINKKIT_ -DFORCE_SSL_VERIFY -DCOAP_OBSERVE_SERVER_SUPPORTED -DCOAP_OBSERVE_CLIENT_SUPPORTED -DCOAP_SERV_MULTITHREAD -DCOAP_USE_PLATFORM_MEMORY -DCOAP_USE_PLATFORM_LOG      -u call_user_start -fno-inline-functions -ffunction-sections -fdata-sections -mlongcalls -DESPOS_FOR_ESP8266 -Wl,-static -DXT_USE_THREAD_SAFE_CLIB=0                   -DSYSINFO_2BOOT_VERSION=\"aos-2nd_boot-1.0.0\"              -ggdb -Os   -DPLATFORM=\"esp8266\" -DSYSINFO_APP_VERSION=\"app-1.0.0-20200426.0145\"  -include out/config/autoconf.h  
debug_CFLAGS           :=  -DSYSINFO_PRODUCT_MODEL=\"ALI_AOS_ESP8266\" -DSYSINFO_DEVICE_NAME=\"ESP8266\" -DBOARD_ESP8266 -DAOS_OTA_RECOVERY_TYPE=2 -DAOS_OTA_BANK_DUAL  -D_IS_LINKKIT_ -DFORCE_SSL_VERIFY -DCOAP_OBSERVE_SERVER_SUPPORTED -DCOAP_OBSERVE_CLIENT_SUPPORTED -DCOAP_SERV_MULTITHREAD -DCOAP_USE_PLATFORM_MEMORY -DCOAP_USE_PLATFORM_LOG      -u call_user_start -fno-inline-functions -ffunction-sections -fdata-sections -mlongcalls -DESPOS_FOR_ESP8266 -Wl,-static -DXT_USE_THREAD_SAFE_CLIB=0                   -DSYSINFO_2BOOT_VERSION=\"aos-2nd_boot-1.0.0\"              -ggdb -Os   -DPLATFORM=\"esp8266\" -DSYSINFO_APP_VERSION=\"app-1.0.0-20200426.0145\"  -include out/config/autoconf.h  -Wall -Werror -Wall -Werror
lwip_CFLAGS           :=  -DSYSINFO_PRODUCT_MODEL=\"ALI_AOS_ESP8266\" -DSYSINFO_DEVICE_NAME=\"ESP8266\" -DBOARD_ESP8266 -DAOS_OTA_RECOVERY_TYPE=2 -DAOS_OTA_BANK_DUAL  -D_IS_LINKKIT_ -DFORCE_SSL_VERIFY -DCOAP_OBSERVE_SERVER_SUPPORTED -DCOAP_OBSERVE_CLIENT_SUPPORTED -DCOAP_SERV_MULTITHREAD -DCOAP_USE_PLATFORM_MEMORY -DCOAP_USE_PLATFORM_LOG      -u call_user_start -fno-inline-functions -ffunction-sections -fdata-sections -mlongcalls -DESPOS_FOR_ESP8266 -Wl,-static -DXT_USE_THREAD_SAFE_CLIB=0                   -DSYSINFO_2BOOT_VERSION=\"aos-2nd_boot-1.0.0\"              -ggdb -Os   -DPLATFORM=\"esp8266\" -DSYSINFO_APP_VERSION=\"app-1.0.0-20200426.0145\"  -include out/config/autoconf.h  
alicrypto_CFLAGS           :=  -DSYSINFO_PRODUCT_MODEL=\"ALI_AOS_ESP8266\" -DSYSINFO_DEVICE_NAME=\"ESP8266\" -DBOARD_ESP8266 -DAOS_OTA_RECOVERY_TYPE=2 -DAOS_OTA_BANK_DUAL  -D_IS_LINKKIT_ -DFORCE_SSL_VERIFY -DCOAP_OBSERVE_SERVER_SUPPORTED -DCOAP_OBSERVE_CLIENT_SUPPORTED -DCOAP_SERV_MULTITHREAD -DCOAP_USE_PLATFORM_MEMORY -DCOAP_USE_PLATFORM_LOG      -u call_user_start -fno-inline-functions -ffunction-sections -fdata-sections -mlongcalls -DESPOS_FOR_ESP8266 -Wl,-static -DXT_USE_THREAD_SAFE_CLIB=0                   -DSYSINFO_2BOOT_VERSION=\"aos-2nd_boot-1.0.0\"              -ggdb -Os   -DPLATFORM=\"esp8266\" -DSYSINFO_APP_VERSION=\"app-1.0.0-20200426.0145\"  -include out/config/autoconf.h  
ota_2nd_boot_CFLAGS           :=  -DSYSINFO_PRODUCT_MODEL=\"ALI_AOS_ESP8266\" -DSYSINFO_DEVICE_NAME=\"ESP8266\" -DBOARD_ESP8266 -DAOS_OTA_RECOVERY_TYPE=2 -DAOS_OTA_BANK_DUAL  -D_IS_LINKKIT_ -DFORCE_SSL_VERIFY -DCOAP_OBSERVE_SERVER_SUPPORTED -DCOAP_OBSERVE_CLIENT_SUPPORTED -DCOAP_SERV_MULTITHREAD -DCOAP_USE_PLATFORM_MEMORY -DCOAP_USE_PLATFORM_LOG      -u call_user_start -fno-inline-functions -ffunction-sections -fdata-sections -mlongcalls -DESPOS_FOR_ESP8266 -Wl,-static -DXT_USE_THREAD_SAFE_CLIB=0                   -DSYSINFO_2BOOT_VERSION=\"aos-2nd_boot-1.0.0\"              -ggdb -Os   -DPLATFORM=\"esp8266\" -DSYSINFO_APP_VERSION=\"app-1.0.0-20200426.0145\"  -include out/config/autoconf.h  -Wall -Werror -Wall -Werror
rhino_CFLAGS           :=  -DSYSINFO_PRODUCT_MODEL=\"ALI_AOS_ESP8266\" -DSYSINFO_DEVICE_NAME=\"ESP8266\" -DBOARD_ESP8266 -DAOS_OTA_RECOVERY_TYPE=2 -DAOS_OTA_BANK_DUAL  -D_IS_LINKKIT_ -DFORCE_SSL_VERIFY -DCOAP_OBSERVE_SERVER_SUPPORTED -DCOAP_OBSERVE_CLIENT_SUPPORTED -DCOAP_SERV_MULTITHREAD -DCOAP_USE_PLATFORM_MEMORY -DCOAP_USE_PLATFORM_LOG      -u call_user_start -fno-inline-functions -ffunction-sections -fdata-sections -mlongcalls -DESPOS_FOR_ESP8266 -Wl,-static -DXT_USE_THREAD_SAFE_CLIB=0                   -DSYSINFO_2BOOT_VERSION=\"aos-2nd_boot-1.0.0\"              -ggdb -Os   -DPLATFORM=\"esp8266\" -DSYSINFO_APP_VERSION=\"app-1.0.0-20200426.0145\"  -include out/config/autoconf.h  -Wall -Werror -Wall -Werror
arch_xtensa_lx106_CFLAGS           :=  -DSYSINFO_PRODUCT_MODEL=\"ALI_AOS_ESP8266\" -DSYSINFO_DEVICE_NAME=\"ESP8266\" -DBOARD_ESP8266 -DAOS_OTA_RECOVERY_TYPE=2 -DAOS_OTA_BANK_DUAL  -D_IS_LINKKIT_ -DFORCE_SSL_VERIFY -DCOAP_OBSERVE_SERVER_SUPPORTED -DCOAP_OBSERVE_CLIENT_SUPPORTED -DCOAP_SERV_MULTITHREAD -DCOAP_USE_PLATFORM_MEMORY -DCOAP_USE_PLATFORM_LOG      -u call_user_start -fno-inline-functions -ffunction-sections -fdata-sections -mlongcalls -DESPOS_FOR_ESP8266 -Wl,-static -DXT_USE_THREAD_SAFE_CLIB=0                   -DSYSINFO_2BOOT_VERSION=\"aos-2nd_boot-1.0.0\"              -ggdb -Os   -DPLATFORM=\"esp8266\" -DSYSINFO_APP_VERSION=\"app-1.0.0-20200426.0145\"  -include out/config/autoconf.h  
ulog_CFLAGS           :=  -DSYSINFO_PRODUCT_MODEL=\"ALI_AOS_ESP8266\" -DSYSINFO_DEVICE_NAME=\"ESP8266\" -DBOARD_ESP8266 -DAOS_OTA_RECOVERY_TYPE=2 -DAOS_OTA_BANK_DUAL  -D_IS_LINKKIT_ -DFORCE_SSL_VERIFY -DCOAP_OBSERVE_SERVER_SUPPORTED -DCOAP_OBSERVE_CLIENT_SUPPORTED -DCOAP_SERV_MULTITHREAD -DCOAP_USE_PLATFORM_MEMORY -DCOAP_USE_PLATFORM_LOG      -u call_user_start -fno-inline-functions -ffunction-sections -fdata-sections -mlongcalls -DESPOS_FOR_ESP8266 -Wl,-static -DXT_USE_THREAD_SAFE_CLIB=0                   -DSYSINFO_2BOOT_VERSION=\"aos-2nd_boot-1.0.0\"              -ggdb -Os   -DPLATFORM=\"esp8266\" -DSYSINFO_APP_VERSION=\"app-1.0.0-20200426.0145\"  -include out/config/autoconf.h  
activation_CFLAGS           :=  -DSYSINFO_PRODUCT_MODEL=\"ALI_AOS_ESP8266\" -DSYSINFO_DEVICE_NAME=\"ESP8266\" -DBOARD_ESP8266 -DAOS_OTA_RECOVERY_TYPE=2 -DAOS_OTA_BANK_DUAL  -D_IS_LINKKIT_ -DFORCE_SSL_VERIFY -DCOAP_OBSERVE_SERVER_SUPPORTED -DCOAP_OBSERVE_CLIENT_SUPPORTED -DCOAP_SERV_MULTITHREAD -DCOAP_USE_PLATFORM_MEMORY -DCOAP_USE_PLATFORM_LOG      -u call_user_start -fno-inline-functions -ffunction-sections -fdata-sections -mlongcalls -DESPOS_FOR_ESP8266 -Wl,-static -DXT_USE_THREAD_SAFE_CLIB=0                   -DSYSINFO_2BOOT_VERSION=\"aos-2nd_boot-1.0.0\"              -ggdb -Os   -DPLATFORM=\"esp8266\" -DSYSINFO_APP_VERSION=\"app-1.0.0-20200426.0145\"  -include out/config/autoconf.h  
chip_code_CFLAGS           :=  -DSYSINFO_PRODUCT_MODEL=\"ALI_AOS_ESP8266\" -DSYSINFO_DEVICE_NAME=\"ESP8266\" -DBOARD_ESP8266 -DAOS_OTA_RECOVERY_TYPE=2 -DAOS_OTA_BANK_DUAL  -D_IS_LINKKIT_ -DFORCE_SSL_VERIFY -DCOAP_OBSERVE_SERVER_SUPPORTED -DCOAP_OBSERVE_CLIENT_SUPPORTED -DCOAP_SERV_MULTITHREAD -DCOAP_USE_PLATFORM_MEMORY -DCOAP_USE_PLATFORM_LOG      -u call_user_start -fno-inline-functions -ffunction-sections -fdata-sections -mlongcalls -DESPOS_FOR_ESP8266 -Wl,-static -DXT_USE_THREAD_SAFE_CLIB=0                   -DSYSINFO_2BOOT_VERSION=\"aos-2nd_boot-1.0.0\"              -ggdb -Os   -DPLATFORM=\"esp8266\" -DSYSINFO_APP_VERSION=\"app-1.0.0-20200426.0145\"  -include out/config/autoconf.h  
libiot_utils_CFLAGS           :=  -DSYSINFO_PRODUCT_MODEL=\"ALI_AOS_ESP8266\" -DSYSINFO_DEVICE_NAME=\"ESP8266\" -DBOARD_ESP8266 -DAOS_OTA_RECOVERY_TYPE=2 -DAOS_OTA_BANK_DUAL  -D_IS_LINKKIT_ -DFORCE_SSL_VERIFY -DCOAP_OBSERVE_SERVER_SUPPORTED -DCOAP_OBSERVE_CLIENT_SUPPORTED -DCOAP_SERV_MULTITHREAD -DCOAP_USE_PLATFORM_MEMORY -DCOAP_USE_PLATFORM_LOG      -u call_user_start -fno-inline-functions -ffunction-sections -fdata-sections -mlongcalls -DESPOS_FOR_ESP8266 -Wl,-static -DXT_USE_THREAD_SAFE_CLIB=0                   -DSYSINFO_2BOOT_VERSION=\"aos-2nd_boot-1.0.0\"              -ggdb -Os   -DPLATFORM=\"esp8266\" -DSYSINFO_APP_VERSION=\"app-1.0.0-20200426.0145\"  -include out/config/autoconf.h  
libiot_log_CFLAGS           :=  -DSYSINFO_PRODUCT_MODEL=\"ALI_AOS_ESP8266\" -DSYSINFO_DEVICE_NAME=\"ESP8266\" -DBOARD_ESP8266 -DAOS_OTA_RECOVERY_TYPE=2 -DAOS_OTA_BANK_DUAL  -D_IS_LINKKIT_ -DFORCE_SSL_VERIFY -DCOAP_OBSERVE_SERVER_SUPPORTED -DCOAP_OBSERVE_CLIENT_SUPPORTED -DCOAP_SERV_MULTITHREAD -DCOAP_USE_PLATFORM_MEMORY -DCOAP_USE_PLATFORM_LOG      -u call_user_start -fno-inline-functions -ffunction-sections -fdata-sections -mlongcalls -DESPOS_FOR_ESP8266 -Wl,-static -DXT_USE_THREAD_SAFE_CLIB=0                   -DSYSINFO_2BOOT_VERSION=\"aos-2nd_boot-1.0.0\"              -ggdb -Os   -DPLATFORM=\"esp8266\" -DSYSINFO_APP_VERSION=\"app-1.0.0-20200426.0145\"  -include out/config/autoconf.h  
libiot_system_CFLAGS           :=  -DSYSINFO_PRODUCT_MODEL=\"ALI_AOS_ESP8266\" -DSYSINFO_DEVICE_NAME=\"ESP8266\" -DBOARD_ESP8266 -DAOS_OTA_RECOVERY_TYPE=2 -DAOS_OTA_BANK_DUAL  -D_IS_LINKKIT_ -DFORCE_SSL_VERIFY -DCOAP_OBSERVE_SERVER_SUPPORTED -DCOAP_OBSERVE_CLIENT_SUPPORTED -DCOAP_SERV_MULTITHREAD -DCOAP_USE_PLATFORM_MEMORY -DCOAP_USE_PLATFORM_LOG      -u call_user_start -fno-inline-functions -ffunction-sections -fdata-sections -mlongcalls -DESPOS_FOR_ESP8266 -Wl,-static -DXT_USE_THREAD_SAFE_CLIB=0                   -DSYSINFO_2BOOT_VERSION=\"aos-2nd_boot-1.0.0\"              -ggdb -Os   -DPLATFORM=\"esp8266\" -DSYSINFO_APP_VERSION=\"app-1.0.0-20200426.0145\"  -include out/config/autoconf.h  
libiot_sdk_impl_CFLAGS           :=  -DSYSINFO_PRODUCT_MODEL=\"ALI_AOS_ESP8266\" -DSYSINFO_DEVICE_NAME=\"ESP8266\" -DBOARD_ESP8266 -DAOS_OTA_RECOVERY_TYPE=2 -DAOS_OTA_BANK_DUAL  -D_IS_LINKKIT_ -DFORCE_SSL_VERIFY -DCOAP_OBSERVE_SERVER_SUPPORTED -DCOAP_OBSERVE_CLIENT_SUPPORTED -DCOAP_SERV_MULTITHREAD -DCOAP_USE_PLATFORM_MEMORY -DCOAP_USE_PLATFORM_LOG      -u call_user_start -fno-inline-functions -ffunction-sections -fdata-sections -mlongcalls -DESPOS_FOR_ESP8266 -Wl,-static -DXT_USE_THREAD_SAFE_CLIB=0                   -DSYSINFO_2BOOT_VERSION=\"aos-2nd_boot-1.0.0\"              -ggdb -Os   -DPLATFORM=\"esp8266\" -DSYSINFO_APP_VERSION=\"app-1.0.0-20200426.0145\"  -include out/config/autoconf.h  
libiot_coap_coappack_CFLAGS           :=  -DSYSINFO_PRODUCT_MODEL=\"ALI_AOS_ESP8266\" -DSYSINFO_DEVICE_NAME=\"ESP8266\" -DBOARD_ESP8266 -DAOS_OTA_RECOVERY_TYPE=2 -DAOS_OTA_BANK_DUAL  -D_IS_LINKKIT_ -DFORCE_SSL_VERIFY -DCOAP_OBSERVE_SERVER_SUPPORTED -DCOAP_OBSERVE_CLIENT_SUPPORTED -DCOAP_SERV_MULTITHREAD -DCOAP_USE_PLATFORM_MEMORY -DCOAP_USE_PLATFORM_LOG      -u call_user_start -fno-inline-functions -ffunction-sections -fdata-sections -mlongcalls -DESPOS_FOR_ESP8266 -Wl,-static -DXT_USE_THREAD_SAFE_CLIB=0                   -DSYSINFO_2BOOT_VERSION=\"aos-2nd_boot-1.0.0\"              -ggdb -Os   -DPLATFORM=\"esp8266\" -DSYSINFO_APP_VERSION=\"app-1.0.0-20200426.0145\"  -include out/config/autoconf.h  
vfs_CFLAGS           :=  -DSYSINFO_PRODUCT_MODEL=\"ALI_AOS_ESP8266\" -DSYSINFO_DEVICE_NAME=\"ESP8266\" -DBOARD_ESP8266 -DAOS_OTA_RECOVERY_TYPE=2 -DAOS_OTA_BANK_DUAL  -D_IS_LINKKIT_ -DFORCE_SSL_VERIFY -DCOAP_OBSERVE_SERVER_SUPPORTED -DCOAP_OBSERVE_CLIENT_SUPPORTED -DCOAP_SERV_MULTITHREAD -DCOAP_USE_PLATFORM_MEMORY -DCOAP_USE_PLATFORM_LOG      -u call_user_start -fno-inline-functions -ffunction-sections -fdata-sections -mlongcalls -DESPOS_FOR_ESP8266 -Wl,-static -DXT_USE_THREAD_SAFE_CLIB=0                   -DSYSINFO_2BOOT_VERSION=\"aos-2nd_boot-1.0.0\"              -ggdb -Os   -DPLATFORM=\"esp8266\" -DSYSINFO_APP_VERSION=\"app-1.0.0-20200426.0145\"  -include out/config/autoconf.h  -Wall -Werror -Wall -Werror
ls_osa_CFLAGS           :=  -DSYSINFO_PRODUCT_MODEL=\"ALI_AOS_ESP8266\" -DSYSINFO_DEVICE_NAME=\"ESP8266\" -DBOARD_ESP8266 -DAOS_OTA_RECOVERY_TYPE=2 -DAOS_OTA_BANK_DUAL  -D_IS_LINKKIT_ -DFORCE_SSL_VERIFY -DCOAP_OBSERVE_SERVER_SUPPORTED -DCOAP_OBSERVE_CLIENT_SUPPORTED -DCOAP_SERV_MULTITHREAD -DCOAP_USE_PLATFORM_MEMORY -DCOAP_USE_PLATFORM_LOG      -u call_user_start -fno-inline-functions -ffunction-sections -fdata-sections -mlongcalls -DESPOS_FOR_ESP8266 -Wl,-static -DXT_USE_THREAD_SAFE_CLIB=0                   -DSYSINFO_2BOOT_VERSION=\"aos-2nd_boot-1.0.0\"              -ggdb -Os   -DPLATFORM=\"esp8266\" -DSYSINFO_APP_VERSION=\"app-1.0.0-20200426.0145\"  -include out/config/autoconf.h  
flyswitch_CXXFLAGS         :=                                      -ggdb -Os   -DPLATFORM=\"esp8266\" -DSYSINFO_APP_VERSION=\"app-1.0.0-20200426.0145\"  -include out/config/autoconf.h  
board_esp8266_CXXFLAGS         :=                                      -ggdb -Os   -DPLATFORM=\"esp8266\" -DSYSINFO_APP_VERSION=\"app-1.0.0-20200426.0145\"  -include out/config/autoconf.h  
linkkit_sdk_c_CXXFLAGS         :=                                      -ggdb -Os   -DPLATFORM=\"esp8266\" -DSYSINFO_APP_VERSION=\"app-1.0.0-20200426.0145\"  -include out/config/autoconf.h  
netmgr_CXXFLAGS         :=                                      -ggdb -Os   -DPLATFORM=\"esp8266\" -DSYSINFO_APP_VERSION=\"app-1.0.0-20200426.0145\"  -include out/config/autoconf.h  
cjson_CXXFLAGS         :=                                      -ggdb -Os   -DPLATFORM=\"esp8266\" -DSYSINFO_APP_VERSION=\"app-1.0.0-20200426.0145\"  -include out/config/autoconf.h  
ota_CXXFLAGS         :=                                      -ggdb -Os   -DPLATFORM=\"esp8266\" -DSYSINFO_APP_VERSION=\"app-1.0.0-20200426.0145\"  -include out/config/autoconf.h  
mcu_esp8266_CXXFLAGS         :=                                      -ggdb -Os   -DPLATFORM=\"esp8266\" -DSYSINFO_APP_VERSION=\"app-1.0.0-20200426.0145\"  -include out/config/autoconf.h  
kernel_init_CXXFLAGS         :=                                      -ggdb -Os   -DPLATFORM=\"esp8266\" -DSYSINFO_APP_VERSION=\"app-1.0.0-20200426.0145\"  -include out/config/autoconf.h  
iotx-hal_CXXFLAGS         :=                                      -ggdb -Os   -DPLATFORM=\"esp8266\" -DSYSINFO_APP_VERSION=\"app-1.0.0-20200426.0145\"  -include out/config/autoconf.h  
libiot_cm_CXXFLAGS         :=                                      -ggdb -Os   -DPLATFORM=\"esp8266\" -DSYSINFO_APP_VERSION=\"app-1.0.0-20200426.0145\"  -include out/config/autoconf.h  
libiot_dm_CXXFLAGS         :=                                      -ggdb -Os   -DPLATFORM=\"esp8266\" -DSYSINFO_APP_VERSION=\"app-1.0.0-20200426.0145\"  -include out/config/autoconf.h  
libdev_reset_CXXFLAGS         :=                                      -ggdb -Os   -DPLATFORM=\"esp8266\" -DSYSINFO_APP_VERSION=\"app-1.0.0-20200426.0145\"  -include out/config/autoconf.h  
libdev_bind_CXXFLAGS         :=                                      -ggdb -Os   -DPLATFORM=\"esp8266\" -DSYSINFO_APP_VERSION=\"app-1.0.0-20200426.0145\"  -include out/config/autoconf.h  
libiot_coap_local_CXXFLAGS         :=                                      -ggdb -Os   -DPLATFORM=\"esp8266\" -DSYSINFO_APP_VERSION=\"app-1.0.0-20200426.0145\"  -include out/config/autoconf.h  
libiot_mqtt_CXXFLAGS         :=                                      -ggdb -Os   -DPLATFORM=\"esp8266\" -DSYSINFO_APP_VERSION=\"app-1.0.0-20200426.0145\"  -include out/config/autoconf.h  
libawss_CXXFLAGS         :=                                      -ggdb -Os   -DPLATFORM=\"esp8266\" -DSYSINFO_APP_VERSION=\"app-1.0.0-20200426.0145\"  -include out/config/autoconf.h  
kv_CXXFLAGS         :=                                      -ggdb -Os   -DPLATFORM=\"esp8266\" -DSYSINFO_APP_VERSION=\"app-1.0.0-20200426.0145\"  -include out/config/autoconf.h  
osal_aos_CXXFLAGS         :=                                      -ggdb -Os   -DPLATFORM=\"esp8266\" -DSYSINFO_APP_VERSION=\"app-1.0.0-20200426.0145\"  -include out/config/autoconf.h  
yloop_CXXFLAGS         :=                                      -ggdb -Os   -DPLATFORM=\"esp8266\" -DSYSINFO_APP_VERSION=\"app-1.0.0-20200426.0145\"  -include out/config/autoconf.h  
imbedtls_CXXFLAGS         :=                                      -ggdb -Os   -DPLATFORM=\"esp8266\" -DSYSINFO_APP_VERSION=\"app-1.0.0-20200426.0145\"  -include out/config/autoconf.h  
newlib_stub_CXXFLAGS         :=                                      -ggdb -Os   -DPLATFORM=\"esp8266\" -DSYSINFO_APP_VERSION=\"app-1.0.0-20200426.0145\"  -include out/config/autoconf.h  
debug_CXXFLAGS         :=                                      -ggdb -Os   -DPLATFORM=\"esp8266\" -DSYSINFO_APP_VERSION=\"app-1.0.0-20200426.0145\"  -include out/config/autoconf.h  
lwip_CXXFLAGS         :=                                      -ggdb -Os   -DPLATFORM=\"esp8266\" -DSYSINFO_APP_VERSION=\"app-1.0.0-20200426.0145\"  -include out/config/autoconf.h  
alicrypto_CXXFLAGS         :=                                      -ggdb -Os   -DPLATFORM=\"esp8266\" -DSYSINFO_APP_VERSION=\"app-1.0.0-20200426.0145\"  -include out/config/autoconf.h  
ota_2nd_boot_CXXFLAGS         :=                                      -ggdb -Os   -DPLATFORM=\"esp8266\" -DSYSINFO_APP_VERSION=\"app-1.0.0-20200426.0145\"  -include out/config/autoconf.h  
rhino_CXXFLAGS         :=                                      -ggdb -Os   -DPLATFORM=\"esp8266\" -DSYSINFO_APP_VERSION=\"app-1.0.0-20200426.0145\"  -include out/config/autoconf.h  
arch_xtensa_lx106_CXXFLAGS         :=                                      -ggdb -Os   -DPLATFORM=\"esp8266\" -DSYSINFO_APP_VERSION=\"app-1.0.0-20200426.0145\"  -include out/config/autoconf.h  
ulog_CXXFLAGS         :=                                      -ggdb -Os   -DPLATFORM=\"esp8266\" -DSYSINFO_APP_VERSION=\"app-1.0.0-20200426.0145\"  -include out/config/autoconf.h  
activation_CXXFLAGS         :=                                      -ggdb -Os   -DPLATFORM=\"esp8266\" -DSYSINFO_APP_VERSION=\"app-1.0.0-20200426.0145\"  -include out/config/autoconf.h  
chip_code_CXXFLAGS         :=                                      -ggdb -Os   -DPLATFORM=\"esp8266\" -DSYSINFO_APP_VERSION=\"app-1.0.0-20200426.0145\"  -include out/config/autoconf.h  
libiot_utils_CXXFLAGS         :=                                      -ggdb -Os   -DPLATFORM=\"esp8266\" -DSYSINFO_APP_VERSION=\"app-1.0.0-20200426.0145\"  -include out/config/autoconf.h  
libiot_log_CXXFLAGS         :=                                      -ggdb -Os   -DPLATFORM=\"esp8266\" -DSYSINFO_APP_VERSION=\"app-1.0.0-20200426.0145\"  -include out/config/autoconf.h  
libiot_system_CXXFLAGS         :=                                      -ggdb -Os   -DPLATFORM=\"esp8266\" -DSYSINFO_APP_VERSION=\"app-1.0.0-20200426.0145\"  -include out/config/autoconf.h  
libiot_sdk_impl_CXXFLAGS         :=                                      -ggdb -Os   -DPLATFORM=\"esp8266\" -DSYSINFO_APP_VERSION=\"app-1.0.0-20200426.0145\"  -include out/config/autoconf.h  
libiot_coap_coappack_CXXFLAGS         :=                                      -ggdb -Os   -DPLATFORM=\"esp8266\" -DSYSINFO_APP_VERSION=\"app-1.0.0-20200426.0145\"  -include out/config/autoconf.h  
vfs_CXXFLAGS         :=                                      -ggdb -Os   -DPLATFORM=\"esp8266\" -DSYSINFO_APP_VERSION=\"app-1.0.0-20200426.0145\"  -include out/config/autoconf.h  
ls_osa_CXXFLAGS         :=                                      -ggdb -Os   -DPLATFORM=\"esp8266\" -DSYSINFO_APP_VERSION=\"app-1.0.0-20200426.0145\"  -include out/config/autoconf.h  
flyswitch_ASMFLAGS         := -include out/config/autoconf.h
board_esp8266_ASMFLAGS         := -include out/config/autoconf.h
linkkit_sdk_c_ASMFLAGS         := -include out/config/autoconf.h
netmgr_ASMFLAGS         := -include out/config/autoconf.h
cjson_ASMFLAGS         := -include out/config/autoconf.h
ota_ASMFLAGS         := -include out/config/autoconf.h
mcu_esp8266_ASMFLAGS         := -include out/config/autoconf.h
kernel_init_ASMFLAGS         := -include out/config/autoconf.h
iotx-hal_ASMFLAGS         := -include out/config/autoconf.h
libiot_cm_ASMFLAGS         := -include out/config/autoconf.h
libiot_dm_ASMFLAGS         := -include out/config/autoconf.h
libdev_reset_ASMFLAGS         := -include out/config/autoconf.h
libdev_bind_ASMFLAGS         := -include out/config/autoconf.h
libiot_coap_local_ASMFLAGS         := -include out/config/autoconf.h
libiot_mqtt_ASMFLAGS         := -include out/config/autoconf.h
libawss_ASMFLAGS         := -include out/config/autoconf.h
kv_ASMFLAGS         := -include out/config/autoconf.h
osal_aos_ASMFLAGS         := -include out/config/autoconf.h
yloop_ASMFLAGS         := -include out/config/autoconf.h
imbedtls_ASMFLAGS         := -include out/config/autoconf.h
newlib_stub_ASMFLAGS         := -include out/config/autoconf.h
debug_ASMFLAGS         := -include out/config/autoconf.h
lwip_ASMFLAGS         := -include out/config/autoconf.h
alicrypto_ASMFLAGS         := -include out/config/autoconf.h
ota_2nd_boot_ASMFLAGS         := -include out/config/autoconf.h
rhino_ASMFLAGS         := -include out/config/autoconf.h
arch_xtensa_lx106_ASMFLAGS         := -include out/config/autoconf.h
ulog_ASMFLAGS         := -include out/config/autoconf.h
activation_ASMFLAGS         := -include out/config/autoconf.h
chip_code_ASMFLAGS         := -include out/config/autoconf.h
libiot_utils_ASMFLAGS         := -include out/config/autoconf.h
libiot_log_ASMFLAGS         := -include out/config/autoconf.h
libiot_system_ASMFLAGS         := -include out/config/autoconf.h
libiot_sdk_impl_ASMFLAGS         := -include out/config/autoconf.h
libiot_coap_coappack_ASMFLAGS         := -include out/config/autoconf.h
vfs_ASMFLAGS         := -include out/config/autoconf.h
ls_osa_ASMFLAGS         := -include out/config/autoconf.h
flyswitch_MAKEFILE         := ./app/example/flyswitch/aos.mk
board_esp8266_MAKEFILE         := ./board/esp8266/aos.mk
linkkit_sdk_c_MAKEFILE         := ./middleware/linkkit/sdk-c/aos.mk
netmgr_MAKEFILE         := ./network/netmgr/aos.mk
cjson_MAKEFILE         := ./utility/cjson/aos.mk
ota_MAKEFILE         := ./middleware/uagent/ota/aos.mk
mcu_esp8266_MAKEFILE         := ./platform/mcu/esp8266/aos.mk
kernel_init_MAKEFILE         := ./kernel/init/aos.mk
iotx-hal_MAKEFILE         := ./middleware/linkkit/sdk-c/src/ref-impl/hal/os/alios/aos.mk
libiot_cm_MAKEFILE         := ./middleware/linkkit/sdk-c/src/services/linkkit/cm/aos.mk
libiot_dm_MAKEFILE         := ./middleware/linkkit/sdk-c/src/services/linkkit/dm/aos.mk
libdev_reset_MAKEFILE         := ./middleware/linkkit/sdk-c/src/services/linkkit/dev_reset/aos.mk
libdev_bind_MAKEFILE         := ./middleware/linkkit/sdk-c/src/services/dev_bind/aos.mk
libiot_coap_local_MAKEFILE         := ./middleware/linkkit/sdk-c/src/protocol/coap/server/aos.mk
libiot_mqtt_MAKEFILE         := ./middleware/linkkit/sdk-c/src/protocol/mqtt/aos.mk
libawss_MAKEFILE         := ./middleware/linkkit/sdk-c/src/services/awss/aos.mk
kv_MAKEFILE         := ./kernel/fs/kv/aos.mk
osal_aos_MAKEFILE         := ./osal/aos/aos.mk
yloop_MAKEFILE         := ./network/yloop/aos.mk
imbedtls_MAKEFILE         := ./security/mbedtls/aos.mk
newlib_stub_MAKEFILE         := ./utility/libc/aos.mk
debug_MAKEFILE         := ./kernel/debug/aos.mk
lwip_MAKEFILE         := ./network/lwip/aos.mk
alicrypto_MAKEFILE         := ./security/alicrypto/aos.mk
ota_2nd_boot_MAKEFILE         := ./middleware/uagent/ota/2nd_boot/aos.mk
rhino_MAKEFILE         := ./kernel/rhino/aos.mk
arch_xtensa_lx106_MAKEFILE         := ./platform/arch/xtensa/lx106/aos.mk
ulog_MAKEFILE         := ./middleware/uagent/ulog/aos.mk
activation_MAKEFILE         := ./utility/activation/aos.mk
chip_code_MAKEFILE         := ./utility/activation/chip_code/aos.mk
libiot_utils_MAKEFILE         := ./middleware/linkkit/sdk-c/src/infra/utils/aos.mk
libiot_log_MAKEFILE         := ./middleware/linkkit/sdk-c/src/infra/log/aos.mk
libiot_system_MAKEFILE         := ./middleware/linkkit/sdk-c/src/infra/system/aos.mk
libiot_sdk_impl_MAKEFILE         := ./middleware/linkkit/sdk-c/src/sdk-impl/aos.mk
libiot_coap_coappack_MAKEFILE         := ./middleware/linkkit/sdk-c/src/protocol/coap/CoAPPacket/aos.mk
vfs_MAKEFILE         := ./kernel/fs/vfs/aos.mk
ls_osa_MAKEFILE         := ./security/ls_osa/aos.mk
flyswitch_PRE_BUILD_TARGETS:= 
board_esp8266_PRE_BUILD_TARGETS:= 
linkkit_sdk_c_PRE_BUILD_TARGETS:= 
netmgr_PRE_BUILD_TARGETS:= 
cjson_PRE_BUILD_TARGETS:= 
ota_PRE_BUILD_TARGETS:= 
mcu_esp8266_PRE_BUILD_TARGETS:= 
kernel_init_PRE_BUILD_TARGETS:= 
iotx-hal_PRE_BUILD_TARGETS:= 
libiot_cm_PRE_BUILD_TARGETS:= 
libiot_dm_PRE_BUILD_TARGETS:= 
libdev_reset_PRE_BUILD_TARGETS:= 
libdev_bind_PRE_BUILD_TARGETS:= 
libiot_coap_local_PRE_BUILD_TARGETS:= 
libiot_mqtt_PRE_BUILD_TARGETS:= 
libawss_PRE_BUILD_TARGETS:= 
kv_PRE_BUILD_TARGETS:= 
osal_aos_PRE_BUILD_TARGETS:= 
yloop_PRE_BUILD_TARGETS:= 
imbedtls_PRE_BUILD_TARGETS:= 
newlib_stub_PRE_BUILD_TARGETS:= 
debug_PRE_BUILD_TARGETS:= 
lwip_PRE_BUILD_TARGETS:= 
alicrypto_PRE_BUILD_TARGETS:= 
ota_2nd_boot_PRE_BUILD_TARGETS:= 
rhino_PRE_BUILD_TARGETS:= 
arch_xtensa_lx106_PRE_BUILD_TARGETS:= 
ulog_PRE_BUILD_TARGETS:= 
activation_PRE_BUILD_TARGETS:= 
chip_code_PRE_BUILD_TARGETS:= 
libiot_utils_PRE_BUILD_TARGETS:= 
libiot_log_PRE_BUILD_TARGETS:= 
libiot_system_PRE_BUILD_TARGETS:= 
libiot_sdk_impl_PRE_BUILD_TARGETS:= 
libiot_coap_coappack_PRE_BUILD_TARGETS:= 
vfs_PRE_BUILD_TARGETS:= 
ls_osa_PRE_BUILD_TARGETS:= 
flyswitch_PREBUILT_LIBRARY := 
board_esp8266_PREBUILT_LIBRARY := 
linkkit_sdk_c_PREBUILT_LIBRARY := 
netmgr_PREBUILT_LIBRARY := 
cjson_PREBUILT_LIBRARY := 
ota_PREBUILT_LIBRARY := 
mcu_esp8266_PREBUILT_LIBRARY := ./platform/mcu/esp8266/bsp/lib/libhal.a ./platform/mcu/esp8266/bsp/lib/libcrypto.a ./platform/mcu/esp8266/bsp/lib/libmain.a ./platform/mcu/esp8266/bsp/lib/libcirom.a ./platform/mcu/esp8266/bsp/lib/libnet80211.a ./platform/mcu/esp8266/bsp/lib/libpp.a ./platform/mcu/esp8266/bsp/lib/libwpa.a ./platform/mcu/esp8266/bsp/lib/libphy.a ./platform/mcu/esp8266/bsp/lib/libgcc.a ./platform/mcu/esp8266/bsp/lib/liblwip.a ./platform/mcu/esp8266/bsp/lib/libpwm.a
kernel_init_PREBUILT_LIBRARY := 
iotx-hal_PREBUILT_LIBRARY := 
libiot_cm_PREBUILT_LIBRARY := 
libiot_dm_PREBUILT_LIBRARY := 
libdev_reset_PREBUILT_LIBRARY := 
libdev_bind_PREBUILT_LIBRARY := 
libiot_coap_local_PREBUILT_LIBRARY := 
libiot_mqtt_PREBUILT_LIBRARY := 
libawss_PREBUILT_LIBRARY := 
kv_PREBUILT_LIBRARY := 
osal_aos_PREBUILT_LIBRARY := 
yloop_PREBUILT_LIBRARY := 
imbedtls_PREBUILT_LIBRARY := 
newlib_stub_PREBUILT_LIBRARY := 
debug_PREBUILT_LIBRARY := 
lwip_PREBUILT_LIBRARY := 
alicrypto_PREBUILT_LIBRARY := 
ota_2nd_boot_PREBUILT_LIBRARY := 
rhino_PREBUILT_LIBRARY := 
arch_xtensa_lx106_PREBUILT_LIBRARY := 
ulog_PREBUILT_LIBRARY := 
activation_PREBUILT_LIBRARY := 
chip_code_PREBUILT_LIBRARY := 
libiot_utils_PREBUILT_LIBRARY := 
libiot_log_PREBUILT_LIBRARY := 
libiot_system_PREBUILT_LIBRARY := 
libiot_sdk_impl_PREBUILT_LIBRARY := 
libiot_coap_coappack_PREBUILT_LIBRARY := 
vfs_PREBUILT_LIBRARY := 
ls_osa_PREBUILT_LIBRARY := 
flyswitch_MBINS_TYPE             := app
board_esp8266_MBINS_TYPE             := kernel
linkkit_sdk_c_MBINS_TYPE             := kernel
netmgr_MBINS_TYPE             := kernel
cjson_MBINS_TYPE             := share
ota_MBINS_TYPE             := kernel
mcu_esp8266_MBINS_TYPE             := kernel
kernel_init_MBINS_TYPE             := kernel
iotx-hal_MBINS_TYPE             := kernel
libiot_cm_MBINS_TYPE             := kernel
libiot_dm_MBINS_TYPE             := kernel
libdev_reset_MBINS_TYPE             := kernel
libdev_bind_MBINS_TYPE             := kernel
libiot_coap_local_MBINS_TYPE             := kernel
libiot_mqtt_MBINS_TYPE             := kernel
libawss_MBINS_TYPE             := kernel
kv_MBINS_TYPE             := kernel
osal_aos_MBINS_TYPE             := kernel
yloop_MBINS_TYPE             := kernel
imbedtls_MBINS_TYPE             := kernel
newlib_stub_MBINS_TYPE             := share
debug_MBINS_TYPE             := kernel
lwip_MBINS_TYPE             := kernel
alicrypto_MBINS_TYPE             := kernel
ota_2nd_boot_MBINS_TYPE             := kernel
rhino_MBINS_TYPE             := kernel
arch_xtensa_lx106_MBINS_TYPE             := kernel
ulog_MBINS_TYPE             := kernel
activation_MBINS_TYPE             := share
chip_code_MBINS_TYPE             := kernel
libiot_utils_MBINS_TYPE             := kernel
libiot_log_MBINS_TYPE             := kernel
libiot_system_MBINS_TYPE             := kernel
libiot_sdk_impl_MBINS_TYPE             := kernel
libiot_coap_coappack_MBINS_TYPE             := kernel
vfs_MBINS_TYPE             := kernel
ls_osa_MBINS_TYPE             := kernel
flyswitch_POPULATE_INCLUDES      := 
board_esp8266_POPULATE_INCLUDES      := 
linkkit_sdk_c_POPULATE_INCLUDES      := 
netmgr_POPULATE_INCLUDES      := 
cjson_POPULATE_INCLUDES      := 
ota_POPULATE_INCLUDES      := 
mcu_esp8266_POPULATE_INCLUDES      := 
kernel_init_POPULATE_INCLUDES      := 
iotx-hal_POPULATE_INCLUDES      := 
libiot_cm_POPULATE_INCLUDES      := 
libiot_dm_POPULATE_INCLUDES      := 
libdev_reset_POPULATE_INCLUDES      := 
libdev_bind_POPULATE_INCLUDES      := 
libiot_coap_local_POPULATE_INCLUDES      := 
libiot_mqtt_POPULATE_INCLUDES      := 
libawss_POPULATE_INCLUDES      := 
kv_POPULATE_INCLUDES      := 
osal_aos_POPULATE_INCLUDES      := 
yloop_POPULATE_INCLUDES      := 
imbedtls_POPULATE_INCLUDES      := 
newlib_stub_POPULATE_INCLUDES      := 
debug_POPULATE_INCLUDES      := 
lwip_POPULATE_INCLUDES      := 
alicrypto_POPULATE_INCLUDES      := 
ota_2nd_boot_POPULATE_INCLUDES      := 
rhino_POPULATE_INCLUDES      := 
arch_xtensa_lx106_POPULATE_INCLUDES      := 
ulog_POPULATE_INCLUDES      := 
activation_POPULATE_INCLUDES      := 
chip_code_POPULATE_INCLUDES      := 
libiot_utils_POPULATE_INCLUDES      := 
libiot_log_POPULATE_INCLUDES      := 
libiot_system_POPULATE_INCLUDES      := 
libiot_sdk_impl_POPULATE_INCLUDES      := 
libiot_coap_coappack_POPULATE_INCLUDES      := 
vfs_POPULATE_INCLUDES      := 
ls_osa_POPULATE_INCLUDES      := 
OBJ-y := activation alicrypto arch_xtensa_lx106 chip_code cjson debug esp8266 flyswitch imbedtls iotx-hal kernel_init kv libawss libdev_bind libdev_reset libiot_cm libiot_coap_local libiot_dm libiot_log libiot_mqtt libiot_system libiot_utils linkkit_sdk_c ls_osa lwip mcu_esp8266 netmgr newlib_stub osal_aos ota ota_2nd_boot rhino ulog vfs yloop
AOS_SDK_UNIT_TEST_SOURCES   		:=                                                                          
INTERNAL_MEMORY_RESOURCES 		:= 
EXTRA_TARGET_MAKEFILES 			:=    ./platform/mcu/esp8266//gen_crc_bin.mk
APPS_START_SECTOR 				:=  
BOOTLOADER_FIRMWARE				:=  
ATE_FIRMWARE				        :=  
APPLICATION_FIRMWARE				:=  
PARAMETER_1_IMAGE					:=  
PARAMETER_2_IMAGE					:=  
FILESYSTEM_IMAGE					:=  
WIFI_FIRMWARE						:=  
BT_PATCH_FIRMWARE					:=  
AOS_ROM_SYMBOL_LIST_FILE 		:= 
AOS_SDK_CHIP_SPECIFIC_SCRIPT		:=                                     
AOS_SDK_CONVERTER_OUTPUT_FILE	:=                                     
AOS_SDK_FINAL_OUTPUT_FILE 		:=                                     
AOS_RAM_STUB_LIST_FILE 			:= 
PING_PONG_OTA 					:= 
AOS_CPLUSPLUS_FLAGS:=                                     
KEIL_DEVICE :=                                     
KEIL_VENDOR :=                                     
IAR_OGCMENU :=                                     
