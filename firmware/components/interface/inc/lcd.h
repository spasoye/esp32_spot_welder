#include <stdio.h>

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
 * @brief  Updates duration value.
 * @note   None
 * @param  dur_val: Value that we want to update to.
 * @retval 0 -> ok
 *         1 -> not ok
 */
uint8_t lcd_set_dur(uint16_t dur_val);

/**
 * @brief  Place cursor to user defined position.
 * @note   None.
 * @param  *p_pos: Position where we want to put the cursor to. 
 * @retval 0 -> ok
 *         1 -> not ok 
 */
uint8_t lcd_user_pointer(uint8_t *p_pos);

/**
 * @brief  Prints ! in top right corner.
 * @note   
 * @param  lvl: Level of warning.
 * @retval None
 */
void lcd_set_warning(uint8_t lvl);

#endif