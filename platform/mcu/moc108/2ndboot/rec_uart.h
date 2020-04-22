
#ifndef __REC_UART_H__
#define __REC_UART_H__

#include "rec_pub.h"

#define PER_CLK             26000000

/* GPIO MACROS */
#define REG_GPIO_BASE_ADDR                  (0x0802800UL)
#define REG_GPIO_0_CONFIG_ADDR              (REG_GPIO_BASE_ADDR + 0x00 * 4)
#define REG_GPIO_1_CONFIG_ADDR              (REG_GPIO_BASE_ADDR + 0x01 * 4)
#define REG_GPIO_10_CONFIG_ADDR             (REG_GPIO_BASE_ADDR + 0x0A * 4)
#define REG_GPIO_11_CONFIG_ADDR             (REG_GPIO_BASE_ADDR + 0x0B * 4)

#define REG_GPIO_FUNTION_MODE_ADDR          (REG_GPIO_BASE_ADDR + 0x20 * 4)
#define REG_GPIO_FUNTION_MODE               (*((volatile unsigned long *) REG_GPIO_FUNTION_MODE_ADDR))

#define REG_GPIO_0_CONFIG                   (*((volatile unsigned long *) REG_GPIO_0_CONFIG_ADDR))
#define REG_GPIO_1_CONFIG                   (*((volatile unsigned long *) REG_GPIO_1_CONFIG_ADDR))
#define REG_GPIO_10_CONFIG                  (*((volatile unsigned long *) REG_GPIO_10_CONFIG_ADDR))
#define REG_GPIO_11_CONFIG                  (*((volatile unsigned long *) REG_GPIO_11_CONFIG_ADDR))

#define GPIO_CFG_OUTPUT_ENABLE_POSI         3
#define GPIO_CFG_OUTPUT_ENABLE_MASK         (0x01UL << GPIO_CFG_OUTPUT_ENABLE_POSI)

#define GPIO_CFG_FUNCTION_ENABLE_POSI       6
#define GPIO_CFG_FUNCTION_ENABLE_MASK       (0x01UL << GPIO_CFG_FUNCTION_ENABLE_POSI)
#define GPIO_CFG_FUNCTION_ENABLE_SET        (0x01UL << GPIO_CFG_FUNCTION_ENABLE_POSI)

#define GPIO_UART0_RX_PIN                   10
#define GPIO_UART0_TX_PIN                   11
#define GPIO_UART0_RX_CONFIG                REG_GPIO_10_CONFIG
#define GPIO_UART0_TX_CONFIG                REG_GPIO_11_CONFIG

#define GPIO_UART1_TX_PIN                   0
#define GPIO_UART1_RX_PIN                   1
#define GPIO_UART1_TX_CONFIG                REG_GPIO_0_CONFIG
#define GPIO_UART1_RX_CONFIG                REG_GPIO_1_CONFIG

#define GPIO_X_FUNTION_MODE_POSI(x)         (x)
#define GPIO_X_FUNTION_MODE_MASK(x)         (0x01UL << GPIO_X_FUNTION_MODE_POSI(x))

/* ICU MACROS */
#define REG_ICU_BASE_ADDR                   (0x00802000UL)
    
#define REG_ICU_PERI_CLK_PWD_ADDR           (REG_ICU_BASE_ADDR + 0x2 * 4)
#define REG_ICU_PERI_CLK_PWD_MASK           0x000BFFFFUL
#define REG_ICU_PERI_CLK_PWD                (*((volatile unsigned long *) REG_ICU_PERI_CLK_PWD_ADDR))
    
#define ICU_PERI_CLK_PWD_SET(x)             do {REG_ICU_PERI_CLK_PWD |=  (x);} while(0)
#define ICU_PERI_CLK_PWD_CLEAR(x)           do {REG_ICU_PERI_CLK_PWD &= ~(x);} while(0)
    
#define ICU_PERI_CLK_PWD_UART0_POSI         0
#define ICU_PERI_CLK_PWD_UART0_MASK         (0x01UL << ICU_PERI_CLK_PWD_UART0_POSI)
#define ICU_PERI_CLK_PWD_UART1_POSI         1
#define ICU_PERI_CLK_PWD_UART1_MASK         (0x01UL << ICU_PERI_CLK_PWD_UART1_POSI)

/* UART0 MACROS */
#define REG_UART0_BASE_ADDR                 (0x00802100UL)

#define REG_UART0_CONFIG_ADDR               (REG_UART0_BASE_ADDR + 0 * 4)
#define REG_UART0_CONFIG_MASK               0x001FFFFF
#define REG_UART0_CONFIG                    (*((volatile unsigned long *) REG_UART0_CONFIG_ADDR))

#define UART0_CONFIG_TX_ENABLE_POSI         0
#define UART0_CONFIG_TX_ENABLE_MASK         (0x01UL << UART0_CONFIG_TX_ENABLE_POSI)
#define UART0_CONFIG_TX_ENABLE_CLEAR        (0x00UL << UART0_CONFIG_TX_ENABLE_POSI)
#define UART0_CONFIG_TX_ENABLE_SET          (0x01UL << UART0_CONFIG_TX_ENABLE_POSI)

#define UART0_CONFIG_RX_ENABLE_POSI         1
#define UART0_CONFIG_RX_ENABLE_MASK         (0x01UL << UART0_CONFIG_RX_ENABLE_POSI)
#define UART0_CONFIG_RX_ENABLE_CLEAR        (0x00UL << UART0_CONFIG_RX_ENABLE_POSI)
#define UART0_CONFIG_RX_ENABLE_SET          (0x01UL << UART0_CONFIG_RX_ENABLE_POSI)

#define UART0_CONFIG_IRDA_MODE_POSI         2
#define UART0_CONFIG_IRDA_MODE_MASK         (0x01UL << UART0_CONFIG_IRDA_MODE_POSI)
#define UART0_CONFIG_IRDA_MODE_CLEAR        (0x00UL << UART0_CONFIG_IRDA_MODE_POSI)
#define UART0_CONFIG_IRDA_MODE_SET          (0x01UL << UART0_CONFIG_IRDA_MODE_POSI)

#define UART0_CONFIG_LENGTH_POSI            3
#define UART0_CONFIG_LENGTH_MASK            (0x03UL << UART0_CONFIG_LENGTH_POSI)
#define UART0_CONFIG_LENGTH_5_BIT           (0x00UL << UART0_CONFIG_LENGTH_POSI)
#define UART0_CONFIG_LENGTH_6_BIT           (0x01UL << UART0_CONFIG_LENGTH_POSI)
#define UART0_CONFIG_LENGTH_7_BIT           (0x02UL << UART0_CONFIG_LENGTH_POSI)
#define UART0_CONFIG_LENGTH_8_BIT           (0x03UL << UART0_CONFIG_LENGTH_POSI)

#define UART0_CONFIG_PAR_ENABLE_POSI        5
#define UART0_CONFIG_PAR_ENABLE_MASK        (0x01UL << UART0_CONFIG_PAR_ENABLE_POSI)
#define UART0_CONFIG_PAR_ENABLE_CLEAR       (0x00UL << UART0_CONFIG_PAR_ENABLE_POSI)
#define UART0_CONFIG_PAR_ENABLE_SET         (0x01UL << UART0_CONFIG_PAR_ENABLE_POSI)

#define UART0_CONFIG_PAR_MODE_POSI          6
#define UART0_CONFIG_PAR_MODE_MASK          (0x01UL << UART0_CONFIG_PAR_MODE_POSI)
#define UART0_CONFIG_PAR_MODE_EVEN          (0x00UL << UART0_CONFIG_PAR_MODE_POSI)
#define UART0_CONFIG_PAR_MODE_ODD           (0x01UL << UART0_CONFIG_PAR_MODE_POSI)

#define UART0_CONFIG_STOP_LEN_POSI          7
#define UART0_CONFIG_STOP_LEN_MASK          (0x01UL << UART0_CONFIG_STOP_LEN_POSI)
#define UART0_CONFIG_STOP_LEN_1_BIT         (0x00UL << UART0_CONFIG_STOP_LEN_POSI)
#define UART0_CONFIG_STOP_LEN_2_BIT         (0x01UL << UART0_CONFIG_STOP_LEN_POSI)

#define UART0_CONFIG_CLK_DIVID_POSI         8
#define UART0_CONFIG_CLK_DIVID_MASK         (0x1FFFUL << UART0_CONFIG_CLK_DIVID_POSI)


#define REG_UART0_FIFO_CONFIG_ADDR          (REG_UART0_BASE_ADDR + 1 * 4)
#define REG_UART0_FIFO_CONFIG_MASK          0x0003FFFF
#define REG_UART0_FIFO_CONFIG               (*((volatile unsigned long *) REG_UART0_FIFO_CONFIG_ADDR))

#define UART0_FIFO_CONFIG_TX_THRESHOLD_POSI     0
#define UART0_FIFO_CONFIG_TX_THRESHOLD_MASK     (0x00FFUL << UART0_FIFO_CONFIG_TX_THRESHOLD_POSI)

#define UART0_FIFO_CONFIG_RX_THRESHOLD_POSI     8
#define UART0_FIFO_CONFIG_RX_THRESHOLD_MASK     (0x00FFUL << UART0_FIFO_CONFIG_RX_THRESHOLD_POSI)

#define UART0_FIFO_CONFIG_RX_STOP_TIME_POSI     16
#define UART0_FIFO_CONFIG_RX_STOP_TIME_MASK     (0x0003UL << UART0_FIFO_CONFIG_RX_STOP_TIME_POSI)


#define REG_UART0_FIFO_STATUS_ADDR              (REG_UART0_BASE_ADDR + 2 * 4)
#define REG_UART0_FIFO_STATUS_MASK              0x003FFFFF
#define REG_UART0_FIFO_STATUS                   (*((volatile unsigned long *) REG_UART0_FIFO_STATUS_ADDR))

#define UART0_FIFO_STATUS_TX_FIFO_CNT_POSI      0
#define UART0_FIFO_STATUS_TX_FIFO_CNT_MASK      (0x00FFUL << UART0_FIFO_STATUS_TX_FIFO_CNT_POSI)
#define UART0_FIFO_STATUS_TX_FIFO_CNT_GET       (REG_UART0_FIFO_STATUS & UART0_FIFO_STATUS_TX_FIFO_CNT_MASK)

#define UART0_FIFO_STATUS_RX_FIFO_CNT_POSI      8
#define UART0_FIFO_STATUS_RX_FIFO_CNT_MASK      (0x00FFUL << UART0_FIFO_STATUS_RX_FIFO_CNT_POSI)
#define UART0_FIFO_STATUS_RX_FIFO_CNT_GET       (REG_UART0_FIFO_STATUS & UART0_FIFO_STATUS_RX_FIFO_CNT_MASK)

#define UART0_FIFO_STATUS_TX_FIFO_FULL_POSI     16
#define UART0_FIFO_STATUS_TX_FIFO_FULL_MASK     (0x01UL << UART0_FIFO_STATUS_TX_FIFO_FULL_POSI)
#define UART0_FIFO_STATUS_TX_FIFO_FULL_GET      (REG_UART0_FIFO_STATUS & UART0_FIFO_STATUS_TX_FIFO_FULL_MASK)

#define UART0_FIFO_STATUS_TX_FIFO_EMPTY_POSI    17
#define UART0_FIFO_STATUS_TX_FIFO_EMPTY_MASK    (0x01UL << UART0_FIFO_STATUS_TX_FIFO_EMPTY_POSI)
#define UART0_FIFO_STATUS_TX_FIFO_EMPTY_GET     (REG_UART0_FIFO_STATUS & UART0_FIFO_STATUS_TX_FIFO_EMPTY_MASK)

#define UART0_FIFO_STATUS_RX_FIFO_FULL_POSI     18
#define UART0_FIFO_STATUS_RX_FIFO_FULL_MASK     (0x01UL << UART0_FIFO_STATUS_RX_FIFO_FULL_POSI)
#define UART0_FIFO_STATUS_RX_FIFO_FULL_GET      (REG_UART0_FIFO_STATUS & UART0_FIFO_STATUS_RX_FIFO_FULL_MASK)

#define UART0_FIFO_STATUS_RX_FIFO_EMPTY_POSI    19
#define UART0_FIFO_STATUS_RX_FIFO_EMPTY_MASK    (0x01UL << UART0_FIFO_STATUS_RX_FIFO_EMPTY_POSI)
#define UART0_FIFO_STATUS_RX_FIFO_EMPTY_GET     (REG_UART0_FIFO_STATUS & UART0_FIFO_STATUS_RX_FIFO_EMPTY_MASK)

#define UART0_FIFO_STATUS_WR_READY_POSI         20
#define UART0_FIFO_STATUS_WR_READY_MASK         (0x01UL << UART0_FIFO_STATUS_WR_READY_POSI)
#define UART0_FIFO_STATUS_WR_READY_GET          (REG_UART0_FIFO_STATUS & UART0_FIFO_STATUS_WR_READY_MASK)

#define UART0_FIFO_STATUS_RD_READY_POSI         21
#define UART0_FIFO_STATUS_RD_READY_MASK         (0x01UL << UART0_FIFO_STATUS_RD_READY_POSI)
#define UART0_FIFO_STATUS_RD_READY_GET          (REG_UART0_FIFO_STATUS & UART0_FIFO_STATUS_RD_READY_MASK)


#define REG_UART0_FIFO_PORT_ADDR                (REG_UART0_BASE_ADDR + 3 * 4)
#define REG_UART0_FIFO_PORT_MASK                0x00FFUL
#define REG_UART0_FIFO_PORT                     (*((volatile unsigned long *) REG_UART0_FIFO_PORT_ADDR))

#define UART0_FIFO_PORT_TX_DATA_POSI            0
#define UART0_FIFO_PORT_TX_DATA_MASK            (0x00FFUL << UART0_FIFO_PORT_TX_DATA_POSI)

#define UART0_FIFO_PORT_RX_DATA_POSI            0
#define UART0_FIFO_PORT_RX_DATA_MASK            (0x00FFUL << UART0_FIFO_PORT_RX_DATA_POSI)
#define UART0_FIFO_PORT_RX_DATA                 (REG_UART0_FIFO_PORT & UART0_FIFO_PORT_RX_DATA_MASK)


#define REG_UART0_INT_ENABLE_ADDR               (REG_UART0_BASE_ADDR + 4 * 4)
#define REG_UART0_INT_ENABLE_MASK               0x00FFUL
#define REG_UART0_INT_ENABLE                    (*((volatile unsigned long *) REG_UART0_INT_ENABLE_ADDR))

#define UART0_INT_ENABLE_TX_NEED_WR_POSI        0
#define UART0_INT_ENABLE_TX_NEED_WR_MASK        (0x01UL << UART0_INT_ENABLE_TX_NEED_WR_POSI)
#define UART0_INT_ENABLE_TX_NEED_WR_CLEAR       (0x00UL << UART0_INT_ENABLE_TX_NEED_WR_POSI)
#define UART0_INT_ENABLE_TX_NEED_WR_SET         (0x01UL << UART0_INT_ENABLE_TX_NEED_WR_POSI)

#define UART0_INT_ENABLE_RX_NEED_RD_POSI        1
#define UART0_INT_ENABLE_RX_NEED_RD_MASK        (0x01UL << UART0_INT_ENABLE_RX_NEED_RD_POSI)
#define UART0_INT_ENABLE_RX_NEED_RD_CLEAR       (0x00UL << UART0_INT_ENABLE_RX_NEED_RD_POSI)
#define UART0_INT_ENABLE_RX_NEED_RD_SET         (0x01UL << UART0_INT_ENABLE_RX_NEED_RD_POSI)

#define UART0_INT_ENABLE_RX_OVER_FLOW_POSI      2
#define UART0_INT_ENABLE_RX_OVER_FLOW_MASK      (0x01UL << UART0_INT_ENABLE_RX_OVER_FLOW_POSI)
#define UART0_INT_ENABLE_RX_OVER_FLOW_CLEAR     (0x00UL << UART0_INT_ENABLE_RX_OVER_FLOW_POSI)
#define UART0_INT_ENABLE_RX_OVER_FLOW_SET       (0x01UL << UART0_INT_ENABLE_RX_OVER_FLOW_POSI)

#define UART0_INT_ENABLE_RX_PARITY_ERR_POSI     3
#define UART0_INT_ENABLE_RX_PARITY_ERR_MASK     (0x01UL << UART0_INT_ENABLE_RX_PARITY_ERR_POSI)
#define UART0_INT_ENABLE_RX_PARITY_ERR_CLEAR    (0x00UL << UART0_INT_ENABLE_RX_PARITY_ERR_POSI)
#define UART0_INT_ENABLE_RX_PARITY_ERR_SET      (0x01UL << UART0_INT_ENABLE_RX_PARITY_ERR_POSI)

#define UART0_INT_ENABLE_RX_STOP_ERR_POSI       4
#define UART0_INT_ENABLE_RX_STOP_ERR_MASK       (0x01UL << UART0_INT_ENABLE_RX_STOP_ERR_POSI)
#define UART0_INT_ENABLE_RX_STOP_ERR_CLEAR      (0x00UL << UART0_INT_ENABLE_RX_STOP_ERR_POSI)
#define UART0_INT_ENABLE_RX_STOP_ERR_SET        (0x01UL << UART0_INT_ENABLE_RX_STOP_ERR_POSI)

#define UART0_INT_ENABLE_TX_STOP_END_POSI       5
#define UART0_INT_ENABLE_TX_STOP_END_MASK       (0x01UL << UART0_INT_ENABLE_TX_STOP_END_POSI)
#define UART0_INT_ENABLE_TX_STOP_END_CLEAR      (0x00UL << UART0_INT_ENABLE_TX_STOP_END_POSI)
#define UART0_INT_ENABLE_TX_STOP_END_SET        (0x01UL << UART0_INT_ENABLE_TX_STOP_END_POSI)

#define UART0_INT_ENABLE_RX_STOP_END_POSI       6
#define UART0_INT_ENABLE_RX_STOP_END_MASK       (0x01UL << UART0_INT_ENABLE_RX_STOP_END_POSI)
#define UART0_INT_ENABLE_RX_STOP_END_CLEAR      (0x00UL << UART0_INT_ENABLE_RX_STOP_END_POSI)
#define UART0_INT_ENABLE_RX_STOP_END_SET        (0x01UL << UART0_INT_ENABLE_RX_STOP_END_POSI)

#define UART0_INT_ENABLE_RXD_WAKEUP_POSI        7
#define UART0_INT_ENABLE_RXD_WAKEUP_MASK        (0x01UL << UART0_INT_ENABLE_RXD_WAKEUP_POSI)
#define UART0_INT_ENABLE_RXD_WAKEUP_CLEAR       (0x00UL << UART0_INT_ENABLE_RXD_WAKEUP_POSI)
#define UART0_INT_ENABLE_RXD_WAKEUP_SET         (0x01UL << UART0_INT_ENABLE_RXD_WAKEUP_POSI)


#define REG_UART0_INT_STATUS_ADDR               (REG_UART0_BASE_ADDR + 5 * 4)
#define REG_UART0_INT_STATUS_MASK               0x00FFUL
#define REG_UART0_INT_STATUS                    (*((volatile unsigned long *) REG_UART0_INT_STATUS_ADDR))


#define REG_UART0_FLOW_CONTROL_ADDR             (REG_UART0_BASE_ADDR + 6 * 4)
#define REG_UART0_FLOW_CONTROL_MASK             0x0001FFFF
#define REG_UART0_FLOW_CONTROL                  (*((volatile unsigned long *) REG_UART0_FLOW_CONTROL_ADDR))

#define UART0_FLOW_CONTROL_LOW_CNT_POSI         0
#define UART0_FLOW_CONTROL_LOW_CNT_MASK         (0x00FFUL << UART0_FLOW_CONTROL_LOW_CNT_POSI)

#define UART0_FLOW_CONTROL_HIGH_CNT_POSI        8
#define UART0_FLOW_CONTROL_HIGH_CNT_MASK        (0x00FFUL << UART0_FLOW_CONTROL_HIGH_CNT_POSI)

#define UART0_FLOW_CONTROL_ENABLE_POSI          16
#define UART0_FLOW_CONTROL_ENABLE_MASK          (0x0001UL << UART0_FLOW_CONTROL_ENABLE_POSI)


#define REG_UART0_WAKEUP_CONFIG_ADDR            (REG_UART0_BASE_ADDR + 7 * 4)
#define REG_UART0_WAKEUP_CONFIG_MASK            0x007FFFFF
#define REG_UART0_WAKEUP_CONFIG                 (*((volatile unsigned long *) REG_UART0_WAKEUP_CONFIG_ADDR))

#define UART0_WAKEUP_CONFIG_DELAY_CNT_POSI      0
#define UART0_WAKEUP_CONFIG_DELAY_CNT_MASK      (0x03FF << UART0_WAKEUP_CONFIG_DELAY_CNT_POSI)

#define UART0_WAKEUP_CONFIG_TX_WAIT_CNT_POSI    10
#define UART0_WAKEUP_CONFIG_TX_WAIT_CNT_MASK    (0x03FF << UART0_WAKEUP_CONFIG_TX_WAIT_CNT_POSI)

#define UART0_WAKEUP_CONFIG_RX_WAKE_EN_POSI     20
#define UART0_WAKEUP_CONFIG_RX_WAKE_EN_MASK     (0x01UL << UART0_WAKEUP_CONFIG_RX_WAKE_EN_POSI)
#define UART0_WAKEUP_CONFIG_RX_WAKE_EN_SET      (0x01UL << UART0_WAKEUP_CONFIG_RX_WAKE_EN_POSI)

#define UART0_WAKEUP_CONFIG_TX_WAKE_EN_POSI     21
#define UART0_WAKEUP_CONFIG_TX_WAKE_EN_MASK     (0x01UL << UART0_WAKEUP_CONFIG_TX_WAKE_EN_POSI)
#define UART0_WAKEUP_CONFIG_TX_WAKE_EN_SET      (0x01UL << UART0_WAKEUP_CONFIG_TX_WAKE_EN_POSI)

#define UART0_WAKEUP_CONFIG_RX_NEGEDGE_WAKE_EN_POSI     22
#define UART0_WAKEUP_CONFIG_RX_NEGEDGE_WAKE_EN_MASK     (0x01UL << UART0_WAKEUP_CONFIG_RX_NEGEDGE_WAKE_EN_POSI)
#define UART0_WAKEUP_CONFIG_RX_NEGEDGE_WAKE_EN_SET      (0x01UL << UART0_WAKEUP_CONFIG_RX_NEGEDGE_WAKE_EN_POSI)

#define UART0_DEFAULT_CLK           PER_CLK
#define UART0_BAUD_115200           115200
#define UART0_BAUD_921600           921600
#define UART0_DEFAULT_BAUD          UART0_BAUD_921600
#define UART0_CLK_DIVID_SET         (UART0_DEFAULT_CLK / UART0_DEFAULT_BAUD)

#define UART0_WRITE_BYTE(v)         (REG_UART0_FIFO_PORT = (v) & 0x00ff)
#define UART0_READ_BYTE()           (REG_UART0_FIFO_PORT & 0x00ff)
#define UART0_TX_FIFO_EMPTY         (REG_UART0_FIFO_STATUS & UART0_FIFO_STATUS_TX_FIFO_EMPTY_MASK)
#define UART0_TX_WRITE_READY        (REG_UART0_FIFO_STATUS & UART0_FIFO_STATUS_WR_READY_MASK)
#define UART0_RX_READ_READY         (REG_UART0_FIFO_STATUS & UART0_FIFO_STATUS_RD_READY_MASK)

/* UART1 MACROS */
#define REG_UART1_BASE_ADDR                 (0x00802200UL)

#define REG_UART1_CONFIG_ADDR               (REG_UART1_BASE_ADDR + 0 * 4)
#define REG_UART1_CONFIG_MASK               0x001FFFFF
#define REG_UART1_CONFIG                    (*((volatile unsigned long *) REG_UART1_CONFIG_ADDR))

#define UART1_CONFIG_TX_ENABLE_POSI         0
#define UART1_CONFIG_TX_ENABLE_MASK         (0x01UL << UART1_CONFIG_TX_ENABLE_POSI)
#define UART1_CONFIG_TX_ENABLE_CLEAR        (0x00UL << UART1_CONFIG_TX_ENABLE_POSI)
#define UART1_CONFIG_TX_ENABLE_SET          (0x01UL << UART1_CONFIG_TX_ENABLE_POSI)

#define UART1_CONFIG_RX_ENABLE_POSI         1
#define UART1_CONFIG_RX_ENABLE_MASK         (0x01UL << UART1_CONFIG_RX_ENABLE_POSI)
#define UART1_CONFIG_RX_ENABLE_CLEAR        (0x00UL << UART1_CONFIG_RX_ENABLE_POSI)
#define UART1_CONFIG_RX_ENABLE_SET          (0x01UL << UART1_CONFIG_RX_ENABLE_POSI)

#define UART1_CONFIG_IRDA_MODE_POSI         2
#define UART1_CONFIG_IRDA_MODE_MASK         (0x01UL << UART1_CONFIG_IRDA_MODE_POSI)
#define UART1_CONFIG_IRDA_MODE_CLEAR        (0x00UL << UART1_CONFIG_IRDA_MODE_POSI)
#define UART1_CONFIG_IRDA_MODE_SET          (0x01UL << UART1_CONFIG_IRDA_MODE_POSI)

#define UART1_CONFIG_LENGTH_POSI            3
#define UART1_CONFIG_LENGTH_MASK            (0x03UL << UART1_CONFIG_LENGTH_POSI)
#define UART1_CONFIG_LENGTH_5               (0x00UL << UART1_CONFIG_LENGTH_POSI)
#define UART1_CONFIG_LENGTH_6               (0x01UL << UART1_CONFIG_LENGTH_POSI)
#define UART1_CONFIG_LENGTH_7               (0x02UL << UART1_CONFIG_LENGTH_POSI)
#define UART1_CONFIG_LENGTH_8               (0x03UL << UART1_CONFIG_LENGTH_POSI)

#define UART1_CONFIG_PAR_ENABLE_POSI        5
#define UART1_CONFIG_PAR_ENABLE_MASK        (0x01UL << UART1_CONFIG_PAR_ENABLE_POSI)
#define UART1_CONFIG_PAR_ENABLE_CLEAR       (0x00UL << UART1_CONFIG_PAR_ENABLE_POSI)
#define UART1_CONFIG_PAR_ENABLE_SET         (0x01UL << UART1_CONFIG_PAR_ENABLE_POSI)

#define UART1_CONFIG_PAR_MODE_POSI          6
#define UART1_CONFIG_PAR_MODE_MASK          (0x01UL << UART1_CONFIG_PAR_MODE_POSI)
#define UART1_CONFIG_PAR_MODE_EVEN          (0x00UL << UART1_CONFIG_PAR_MODE_POSI)
#define UART1_CONFIG_PAR_MODE_ODD           (0x01UL << UART1_CONFIG_PAR_MODE_POSI)

#define UART1_CONFIG_STOP_LEN_POSI          7
#define UART1_CONFIG_STOP_LEN_MASK          (0x01UL << UART1_CONFIG_STOP_LEN_POSI)
#define UART1_CONFIG_STOP_LEN_1_BIT         (0x00UL << UART1_CONFIG_STOP_LEN_POSI)
#define UART1_CONFIG_STOP_LEN_2_BIT         (0x01UL << UART1_CONFIG_STOP_LEN_POSI)

#define UART1_CONFIG_CLK_DIVID_POSI         8
#define UART1_CONFIG_CLK_DIVID_MASK         (0x1FFFUL << UART1_CONFIG_CLK_DIVID_POSI)


#define REG_UART1_FIFO_CONFIG_ADDR          (REG_UART1_BASE_ADDR + 1 * 4)
#define REG_UART1_FIFO_CONFIG_MASK          0x0003FFFF
#define REG_UART1_FIFO_CONFIG               (*((volatile unsigned long *) REG_UART1_FIFO_CONFIG_ADDR))

#define UART1_FIFO_CONFIG_TX_THRESHOLD_POSI     0
#define UART1_FIFO_CONFIG_TX_THRESHOLD_MASK     (0x00FFUL << UART1_FIFO_CONFIG_TX_THRESHOLD_POSI)

#define UART1_FIFO_CONFIG_RX_THRESHOLD_POSI     8
#define UART1_FIFO_CONFIG_RX_THRESHOLD_MASK     (0x00FFUL << UART1_FIFO_CONFIG_RX_THRESHOLD_POSI)

#define UART1_FIFO_CONFIG_RX_STOP_TIME_POSI     16
#define UART1_FIFO_CONFIG_RX_STOP_TIME_MASK     (0x0003UL << UART1_FIFO_CONFIG_RX_STOP_TIME_POSI)


#define REG_UART1_FIFO_STATUS_ADDR              (REG_UART1_BASE_ADDR + 2 * 4)
#define REG_UART1_FIFO_STATUS_MASK              0x003FFFFF
#define REG_UART1_FIFO_STATUS                   (*((volatile unsigned long *) REG_UART1_FIFO_STATUS_ADDR))

#define UART1_FIFO_STATUS_TX_FIFO_CNT_POSI      0
#define UART1_FIFO_STATUS_TX_FIFO_CNT_MASK      (0x00FFUL << UART1_FIFO_STATUS_TX_FIFO_CNT_POSI)
#define UART1_FIFO_STATUS_TX_FIFO_CNT_GET       (REG_UART1_FIFO_STATUS & UART1_FIFO_STATUS_TX_FIFO_CNT_MASK)

#define UART1_FIFO_STATUS_RX_FIFO_CNT_POSI      8
#define UART1_FIFO_STATUS_RX_FIFO_CNT_MASK      (0x00FFUL << UART1_FIFO_STATUS_RX_FIFO_CNT_POSI)
#define UART1_FIFO_STATUS_RX_FIFO_CNT_GET       (REG_UART1_FIFO_STATUS & UART1_FIFO_STATUS_RX_FIFO_CNT_MASK)

#define UART1_FIFO_STATUS_TX_FIFO_FULL_POSI     16
#define UART1_FIFO_STATUS_TX_FIFO_FULL_MASK     (0x01UL << UART1_FIFO_STATUS_TX_FIFO_FULL_POSI)
#define UART1_FIFO_STATUS_TX_FIFO_FULL_GET      (REG_UART1_FIFO_STATUS & UART1_FIFO_STATUS_TX_FIFO_FULL_MASK)

#define UART1_FIFO_STATUS_TX_FIFO_EMPTY_POSI    17
#define UART1_FIFO_STATUS_TX_FIFO_EMPTY_MASK    (0x01UL << UART1_FIFO_STATUS_TX_FIFO_EMPTY_POSI)
#define UART1_FIFO_STATUS_TX_FIFO_EMPTY_GET     (REG_UART1_FIFO_STATUS & UART1_FIFO_STATUS_TX_FIFO_EMPTY_MASK)

#define UART1_FIFO_STATUS_RX_FIFO_FULL_POSI     18
#define UART1_FIFO_STATUS_RX_FIFO_FULL_MASK     (0x01UL << UART1_FIFO_STATUS_RX_FIFO_FULL_POSI)
#define UART1_FIFO_STATUS_RX_FIFO_FULL_GET      (REG_UART1_FIFO_STATUS & UART1_FIFO_STATUS_RX_FIFO_FULL_MASK)

#define UART1_FIFO_STATUS_RX_FIFO_EMPTY_POSI    19
#define UART1_FIFO_STATUS_RX_FIFO_EMPTY_MASK    (0x01UL << UART1_FIFO_STATUS_RX_FIFO_EMPTY_POSI)
#define UART1_FIFO_STATUS_RX_FIFO_EMPTY_GET     (REG_UART1_FIFO_STATUS & UART1_FIFO_STATUS_RX_FIFO_EMPTY_MASK)

#define UART1_FIFO_STATUS_WR_READY_POSI         20
#define UART1_FIFO_STATUS_WR_READY_MASK         (0x01UL << UART1_FIFO_STATUS_WR_READY_POSI)
#define UART1_FIFO_STATUS_WR_READY_GET          (REG_UART1_FIFO_STATUS & UART1_FIFO_STATUS_WR_READY_MASK)

#define UART1_FIFO_STATUS_RD_READY_POSI         21
#define UART1_FIFO_STATUS_RD_READY_MASK         (0x01UL << UART1_FIFO_STATUS_RD_READY_POSI)
#define UART1_FIFO_STATUS_RD_READY_GET          (REG_UART1_FIFO_STATUS & UART1_FIFO_STATUS_RD_READY_MASK)


#define REG_UART1_FIFO_PORT_ADDR                (REG_UART1_BASE_ADDR + 3 * 4)
#define REG_UART1_FIFO_PORT_MASK                0x00FFUL
#define REG_UART1_FIFO_PORT                     (*((volatile unsigned long *) REG_UART1_FIFO_PORT_ADDR))

#define UART1_FIFO_PORT_TX_DATA_POSI            0
#define UART1_FIFO_PORT_TX_DATA_MASK            (0x00FFUL << UART1_FIFO_PORT_TX_DATA_POSI)

#define UART1_FIFO_PORT_RX_DATA_POSI            0
#define UART1_FIFO_PORT_RX_DATA_MASK            (0x00FFUL << UART1_FIFO_PORT_RX_DATA_POSI)
#define UART1_FIFO_PORT_RX_DATA                 (REG_UART1_FIFO_PORT & UART1_FIFO_PORT_RX_DATA_MASK)


#define REG_UART1_INT_ENABLE_ADDR               (REG_UART1_BASE_ADDR + 4 * 4)
#define REG_UART1_INT_ENABLE_MASK               0x00FFUL
#define REG_UART1_INT_ENABLE                    (*((volatile unsigned long *) REG_UART1_INT_ENABLE_ADDR))

#define UART1_INT_ENABLE_TX_NEED_WR_POSI        0
#define UART1_INT_ENABLE_TX_NEED_WR_MASK        (0x01UL << UART1_INT_ENABLE_TX_NEED_WR_POSI)
#define UART1_INT_ENABLE_TX_NEED_WR_CLEAR       (0x00UL << UART1_INT_ENABLE_TX_NEED_WR_POSI)
#define UART1_INT_ENABLE_TX_NEED_WR_SET         (0x01UL << UART1_INT_ENABLE_TX_NEED_WR_POSI)

#define UART1_INT_ENABLE_RX_NEED_RD_POSI        1
#define UART1_INT_ENABLE_RX_NEED_RD_MASK        (0x01UL << UART1_INT_ENABLE_RX_NEED_RD_POSI)
#define UART1_INT_ENABLE_RX_NEED_RD_CLEAR       (0x00UL << UART1_INT_ENABLE_RX_NEED_RD_POSI)
#define UART1_INT_ENABLE_RX_NEED_RD_SET         (0x01UL << UART1_INT_ENABLE_RX_NEED_RD_POSI)

#define UART1_INT_ENABLE_RX_OVER_FLOW_POSI      2
#define UART1_INT_ENABLE_RX_OVER_FLOW_MASK      (0x01UL << UART1_INT_ENABLE_RX_OVER_FLOW_POSI)
#define UART1_INT_ENABLE_RX_OVER_FLOW_CLEAR     (0x00UL << UART1_INT_ENABLE_RX_OVER_FLOW_POSI)
#define UART1_INT_ENABLE_RX_OVER_FLOW_SET       (0x01UL << UART1_INT_ENABLE_RX_OVER_FLOW_POSI)

#define UART1_INT_ENABLE_RX_PARITY_ERR_POSI     3
#define UART1_INT_ENABLE_RX_PARITY_ERR_MASK     (0x01UL << UART1_INT_ENABLE_RX_PARITY_ERR_POSI)
#define UART1_INT_ENABLE_RX_PARITY_ERR_CLEAR    (0x00UL << UART1_INT_ENABLE_RX_PARITY_ERR_POSI)
#define UART1_INT_ENABLE_RX_PARITY_ERR_SET      (0x01UL << UART1_INT_ENABLE_RX_PARITY_ERR_POSI)

#define UART1_INT_ENABLE_RX_STOP_ERR_POSI       4
#define UART1_INT_ENABLE_RX_STOP_ERR_MASK       (0x01UL << UART1_INT_ENABLE_RX_STOP_ERR_POSI)
#define UART1_INT_ENABLE_RX_STOP_ERR_CLEAR      (0x00UL << UART1_INT_ENABLE_RX_STOP_ERR_POSI)
#define UART1_INT_ENABLE_RX_STOP_ERR_SET        (0x01UL << UART1_INT_ENABLE_RX_STOP_ERR_POSI)

#define UART1_INT_ENABLE_TX_STOP_END_POSI       5
#define UART1_INT_ENABLE_TX_STOP_END_MASK       (0x01UL << UART1_INT_ENABLE_TX_STOP_END_POSI)
#define UART1_INT_ENABLE_TX_STOP_END_CLEAR      (0x00UL << UART1_INT_ENABLE_TX_STOP_END_POSI)
#define UART1_INT_ENABLE_TX_STOP_END_SET        (0x01UL << UART1_INT_ENABLE_TX_STOP_END_POSI)

#define UART1_INT_ENABLE_RX_STOP_END_POSI       6
#define UART1_INT_ENABLE_RX_STOP_END_MASK       (0x01UL << UART1_INT_ENABLE_RX_STOP_END_POSI)
#define UART1_INT_ENABLE_RX_STOP_END_CLEAR      (0x00UL << UART1_INT_ENABLE_RX_STOP_END_POSI)
#define UART1_INT_ENABLE_RX_STOP_END_SET        (0x01UL << UART1_INT_ENABLE_RX_STOP_END_POSI)

#define UART1_INT_ENABLE_RXD_WAKEUP_POSI        7
#define UART1_INT_ENABLE_RXD_WAKEUP_MASK        (0x01UL << UART1_INT_ENABLE_RXD_WAKEUP_POSI)
#define UART1_INT_ENABLE_RXD_WAKEUP_CLEAR       (0x00UL << UART1_INT_ENABLE_RXD_WAKEUP_POSI)
#define UART1_INT_ENABLE_RXD_WAKEUP_SET         (0x01UL << UART1_INT_ENABLE_RXD_WAKEUP_POSI)


#define REG_UART1_INT_STATUS_ADDR               (REG_UART1_BASE_ADDR + 5 * 4)
#define REG_UART1_INT_STATUS_MASK               0x00FFUL
#define REG_UART1_INT_STATUS                    (*((volatile unsigned long *) REG_UART1_INT_STATUS_ADDR))


#define REG_UART1_FLOW_CONTROL_ADDR             (REG_UART1_BASE_ADDR + 6 * 4)
#define REG_UART1_FLOW_CONTROL_MASK             0x0001FFFF
#define REG_UART1_FLOW_CONTROL                  (*((volatile unsigned long *) REG_UART1_FLOW_CONTROL_ADDR))

#define UART1_FLOW_CONTROL_LOW_CNT_POSI         0
#define UART1_FLOW_CONTROL_LOW_CNT_MASK         (0x00FFUL << UART1_FLOW_CONTROL_LOW_CNT_POSI)

#define UART1_FLOW_CONTROL_HIGH_CNT_POSI        8
#define UART1_FLOW_CONTROL_HIGH_CNT_MASK        (0x00FFUL << UART1_FLOW_CONTROL_HIGH_CNT_POSI)

#define UART1_FLOW_CONTROL_ENABLE_POSI          16
#define UART1_FLOW_CONTROL_ENABLE_MASK          (0x0001UL << UART1_FLOW_CONTROL_ENABLE_POSI)


#define REG_UART1_WAKEUP_CONFIG_ADDR            (REG_UART1_BASE_ADDR + 7 * 4)
#define REG_UART1_WAKEUP_CONFIG_MASK            0x007FFFFF
#define REG_UART1_WAKEUP_CONFIG                 (*((volatile unsigned long *) REG_UART1_WAKEUP_CONFIG_ADDR))

#define UART1_WAKEUP_CONFIG_DELAY_CNT_POSI      0
#define UART1_WAKEUP_CONFIG_DELAY_CNT_MASK      (0x03FF << UART1_WAKEUP_CONFIG_DELAY_CNT_POSI)

#define UART1_WAKEUP_CONFIG_TX_WAIT_CNT_POSI    10
#define UART1_WAKEUP_CONFIG_TX_WAIT_CNT_MASK    (0x03FF << UART1_WAKEUP_CONFIG_TX_WAIT_CNT_POSI)

#define UART1_WAKEUP_CONFIG_RX_WAKE_EN_POSI     20
#define UART1_WAKEUP_CONFIG_RX_WAKE_EN_MASK     (0x01UL << UART1_WAKEUP_CONFIG_RX_WAKE_EN_POSI)
#define UART1_WAKEUP_CONFIG_RX_WAKE_EN_SET      (0x01UL << UART1_WAKEUP_CONFIG_RX_WAKE_EN_POSI)

#define UART1_WAKEUP_CONFIG_TX_WAKE_EN_POSI     21
#define UART1_WAKEUP_CONFIG_TX_WAKE_EN_MASK     (0x01UL << UART1_WAKEUP_CONFIG_TX_WAKE_EN_POSI)
#define UART1_WAKEUP_CONFIG_TX_WAKE_EN_SET      (0x01UL << UART1_WAKEUP_CONFIG_TX_WAKE_EN_POSI)

#define UART1_WAKEUP_CONFIG_RX_NEGEDGE_WAKE_EN_POSI     22
#define UART1_WAKEUP_CONFIG_RX_NEGEDGE_WAKE_EN_MASK     (0x01UL << UART1_WAKEUP_CONFIG_RX_NEGEDGE_WAKE_EN_POSI)
#define UART1_WAKEUP_CONFIG_RX_NEGEDGE_WAKE_EN_SET      (0x01UL << UART1_WAKEUP_CONFIG_RX_NEGEDGE_WAKE_EN_POSI)

#define UART1_DEFAULT_CLK           PER_CLK
#define UART1_BAUD_115200           115200
#define UART1_BAUD_921600           921600
#define UART1_BAUD_3M25             3250000
#define UART1_BAUD_6M5              6500000
#define UART1_DEFAULT_BAUD          UART1_BAUD_921600
#define UART1_CLK_DIVID_SET         (UART1_DEFAULT_CLK / UART1_DEFAULT_BAUD)

#define UART1_WRITE_BYTE(v)         (REG_UART1_FIFO_PORT = (v) & 0x00ff)
#define UART1_READ_BYTE()           (REG_UART1_FIFO_PORT & 0x00ff)
#define UART1_TX_FIFO_EMPTY         (REG_UART1_FIFO_STATUS & UART1_FIFO_STATUS_TX_FIFO_EMPTY_MASK)
#define UART1_TX_WRITE_READY        (REG_UART1_FIFO_STATUS & UART1_FIFO_STATUS_WR_READY_MASK)
#define UART1_RX_READ_READY         (REG_UART1_FIFO_STATUS & UART1_FIFO_STATUS_RD_READY_MASK)

/* WDT MACROS */

#define ICU_PERI_CLK_PWD_ARM_WDT_POSI   8
#define ICU_PERI_CLK_PWD_ARM_WDT_MASK   (0x01UL << ICU_PERI_CLK_PWD_ARM_WDT_POSI)

#define REG_WDT_BASE_ADDR               (0x00802900UL)
#define REG_WDT_CONFIG_ADDR             (REG_WDT_BASE_ADDR + 0*4)
#define REG_WDT_CONFIG_MASK             0x00FFFFFFUL
#define REG_WDT_CONFIG                  (*((volatile unsigned long *) REG_WDT_CONFIG_ADDR))

#define WDKEY_ENABLE1                   0x005A
#define WDKEY_ENABLE2                   0x00A5

#define WDT_CONFIG_PERIOD_POSI          0
#define WDT_CONFIG_PERIOD_MASK          (0x0000FFFFUL << WDT_CONFIG_PERIOD_POSI)

#define WDT_CONFIG_WDKEY_POSI           16
#define WDT_CONFIG_WDKEY_MASK           (0x00FFUL << WDT_CONFIG_WDKEY_POSI)


#endif // __REC_UART_H__

