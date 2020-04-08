#include <stdio.h>

#ifndef ROT_ENC_H
#define ROT_ENC_H

/**
 * @brief  Inititalize rotary encoder GPIOS, handler task
 *         interrupt queue. Used for setting the ON state
 *         the relay.
 * @note   
 * @retval 0 -> ok
 *         1 -> not ok
 */
uint8_t rotary_encoder_init(void);

/**
 * @brief  Return duration value.
 * @note   
 * @retval Duration value.
 */
uint16_t rotary_encoder_get_duration(void);

/**
 * @brief  Disable all rotary encoder interrupts.
 * @note   
 * @retval None
 */
void rotary_encoder_int_disable(void);

/**
 * @brief  Enable all rotary encoder interrupts.
 * @note   
 * @retval None
 */
void rotary_encoder_int_enable(void);

#endif