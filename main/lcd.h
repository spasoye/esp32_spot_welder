#include <stdio.h>

#ifndef BLE_IF_H
#define BLE_IF_H

/**
 * @brief Initialize LCD
 * @note TODO: pass pinout and configuration
 * @retval 0 -> ok
 *         1 -> not ok
 */
uint8_t lcd_init(void);

/**
 * @brief  Updates duration value.
 * @note   None
 * @param  dur_val: Value that we want to update to.
 * @retval 0 -> ok
 *         1 -> not ok
 */
uint8_t lcd_set_dur(uint16_t dur_val);

#endif