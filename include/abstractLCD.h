#ifndef _ABSTRACT_LCD_H_
#define _ABSTRACT_LCD_H_

#include "abstractSTM32.h"
#include <bits/stdint-intn.h>
#include <bits/stdint-uintn.h>
#include <cstdint>

/**
 * Struct for storing data about LCD (For prototype was taken WH1602B-NYG-CT)
 */
struct lcd {
    /** Port ID. Can be GPIOA...GPIOK */
    uint8_t port : 4;

    /** Operating voltage for LCD. Set -1 if it does not connected to the MCU */
    int8_t VO;

    /** Switchs between DATA and INSTRUCTION modes */
    uint8_t RC : 4;

    /** Switchs between READ and WRITE modes */
    uint8_t RW : 4;

    /** Chip enable signal */
    uint8_t E : 4;

    /** 
     * Bitmap of D0 - D7 pins. Pins should be connected to MCU in ascending order 
     * (i.e. D4 cannot be connected to 7th pin while D5 connected to 6th pin).
     * In case of half-byte connection only 4 bits should be specifled.
     * Example: D0 - 0, D1 - 3, D2 - 4, D3 - 7 => DB = 0b10001101
     */
    uint16_t DB;

    /** Control LCD backlight. Set -1 if it does not connected to the MCU */
    int8_t LED;

    /** 
     * Setting of pwm. 
     * ABST_NO_PWM - disable PWM, use digital levels of brightness.
     * ABST_SOFT_PWM - use :c:func:`abst_pwm_soft` to provide PWM
     * ABST_HARD_PWM - use :c:func:`abst_pwm_hard` to provide PWM
     */
    uint8_t pwm_setting : 2;

    /** 
     * Pointer to the miliseconds delay function. 
     * If NULL is set delay_us will be used.
     * If both pointers set to NULL functions from AbstractSTM32Fx will be used.
     */
    void *(delay_ms)(uint32_t);

    /** 
     * Pointer to the microseconds delay function. 
     * If NULL is set delay_ms will be used. 
     * If both pointers set to NULL functions from AbstractSTM32Fx will be used.
     */
    void *(delay_us)(uint32_t);

    /** True if half-byte mode, false overwise */
    uint8_t is_half_byte : 1;

    /* Service variable to store VO pin. Must not be modified by user */
    struct pin _VO_pin_ptr_;

    /* Service variable to store RC pin. Must not be modified by user */
    struct pin _RC_pin_ptr_;

    /* Service variable to store RW pin. Must not be modified by user */
    struct pin _RW_pin_ptr_;

    /* Service variable to store E pin. Must not be modified by user */
    struct pin _E_pin_ptr_;

    /* Service variable to store LED pin. Must not be modified by user */
    struct pin _LED_pin_ptr_;

    /* Service variable to store DB pin group. Must not be modified by user */
    struct pin_group _DB_group_ptr_;
};

enum PWM_SETTING {
    ABST_NO_PWM = 0,
    ABST_SOFT_PWM,
    ABST_HARD_PWM
};

int abst_lcd_init(struct lcd *lcd_ptr);

int __attribute__ ((weak)) _abst_lcd_connect_half_byte(struct lcd *lcd_ptr);

#endif // _ABSTRACT_LCD_H_