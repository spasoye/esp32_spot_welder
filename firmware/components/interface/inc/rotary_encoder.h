#include <stdio.h>

#ifndef ROT_ENC_H
#define ROT_ENC_H

typedef enum _event_t
{
    CW,
    CCW,
    CLICK
} encoder_event_t;

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


#endif