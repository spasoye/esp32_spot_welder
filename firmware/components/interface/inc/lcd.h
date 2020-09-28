#include <stdio.h>
#include <interface.h>

#ifndef LCD_H
#define LCD_H

/**
 * @brief Initialize LCD
 * @note TODO: pass pinout and configuration
 * @retval 0 -> ok
 *         1 -> not ok
 */
uint8_t lcd_init(void);

/**
 * @brief  Updates pulse on time value.
 * @note   None
 * @param  dur_val: Value that we want to update to.
 * @retval 0 -> ok
 *         1 -> not ok
 */
uint8_t lcd_set_on(uint16_t dur_val);

/**
 * @brief  Updates pulse off time value.
 * @note   None
 * @param  dur_val: Value that we want to update to.
 * @retval 0 -> ok
 *         1 -> not ok
 */
uint8_t lcd_set_off(uint16_t dur_val);

/**
 * @brief  Updates number of pulses value.
 * @note   
 * @param  num_val: Value that we want to update to.
 * @retval 0 -> ok
 *         1 -> not ok
 */
uint8_t lcd_set_num(uint8_t num_val);

/**
 * @brief  Place cursor to user defined position.
 * @note   None.
 * @param  *p_pos: Position where we want to put the cursor to. 
 * @retval 0 -> ok
 *         1 -> not ok 
 */
uint8_t lcd_user_pointer(uint8_t *p_pos, interface_property prop);

#endif