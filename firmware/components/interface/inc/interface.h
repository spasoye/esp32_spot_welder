#include <stdio.h>

#ifndef INTERFACE_H
#define INTERFACE_H

typedef enum _event_t
{
    CW,
    CCW,
    SHORT,
    LONG
} encoder_event_t;

typedef enum _interface_property
{
    ON_PROP,
    OFF_PROP,
    NUM_PROP
}interface_property;

interface_property curr_prop;

/**
 * @brief  Inititalize rotary encoder GPIOS, handler task,
 *         interrupt handlers. Used for setting the ON state
 *         the relay.
 * @note   
 * @retval 0 -> ok
 *         1 -> not ok
 */
uint8_t interface_init(void);

/**
 * @brief  Return duration value.
 * @note   
 * @retval Duration value.
 */
uint16_t interface_get_duration(void);

void interface_get_val(uint16_t *p_on_time,uint16_t *p_off_time, uint16_t *p_pulses);


#endif