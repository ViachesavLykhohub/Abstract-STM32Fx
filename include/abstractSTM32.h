#ifndef _ABSTRACT_STM32_H_
#define _ABSTRACT_STM32_H_

#include <stdint.h>
#include <stdbool.h>

/** 
 * Error codes
 */
enum abst_errors {
    /** Ok */
    ABST_OK = 0, 
    
    /** Unknown error */
    ABST_UNKNOWN_ERROR = -1, 
    
    /** Wrong parameters */
    ABST_WRONG_PARAMS = -2, 
    
    /** Not implemented yet */
    ABST_NOT_IMPLEMENTED = -3
};

/**
 * Struct for storing data about pin
 */
struct abst_pin {  
    /** 
     * GPIO Port identifier :c:type:`abst_pin_port`.
     */
    uint8_t port : 4;
    
    /** 
     * GPIO Pin number. Can be 0..15
     */
    uint8_t num : 4;
    
    /** 
     * GPIO Pin mode 
     * Can be GPIO_MODE_INPUT, GPIO_MODE_OUTPUT, GPIO_MODE_AF, GPIO_MODE_ANALOG
     */
    uint8_t mode : 2;

    /**
     * GPIO Output Pin Driver Type
     * Can be GPIO_OTYPE_OD (open drain), GPIO_OTYPE_PP (push pull)
     */
    uint8_t otype : 1;

    /**
     * GPIO Output Pin Speed
     * Can be GPIO_OSPEED_2MHZ, GPIO_OSPEED_25MHZ, GPIO_OSPEED_50MHZ, GPIO_OSPEED_100MHZ
     */
    uint8_t speed : 2;

    /** 
     * GPIO Output Pin Pullup
     * Can be GPIO_PUPD_NONE, GPIO_PUPD_PULLDOWN, GPIO_PUPD_PULLUP
     */
    uint8_t pull_up_down : 2;


    /** 
     * Flag that specify if the pin is inversed. 
     * If true, abst_digital_write and abst_digital_read functions inverse the value at the pin.
     */
    uint8_t is_inverse : 1;

    /*
     * Service variable: Must not be changed by user.
     * Used to save PWM value on the pin and used by :c:func:`abst_pwm_soft`
     */
    uint8_t __pwm_value;
};

/**
 * Struct for storing data about a pin group
 */
struct abst_pin_group {  
    /** GPIO Port ID. :c:type:`abst_pin_port`*/
    uint8_t port : 4;
    
    /** Pin identifiers. If multiple pins are to be set, use bitwise OR '|' to separate them. */
    uint16_t num : 16;
    
    /** 
     * GPIO Pins direction 
     * Can be GPIO_MODE_INPUT, GPIO_MODE_OUTPUT, GPIO_MODE_AF, GPIO_MODE_ANALOG
     */
    uint8_t mode : 2;

    /**
     * GPIO Output Pins Driver Type
     * Can be GPIO_OTYPE_OD (open drain), GPIO_OTYPE_PP (push pull)
     */
    uint8_t otype : 1;

    /**
     * GPIO Output Pins Speed
     * Can be GPIO_OSPEED_2MHZ, GPIO_OSPEED_25MHZ, GPIO_OSPEED_50MHZ, GPIO_OSPEED_100MHZ
     */
    uint8_t speed : 2;

    /** 
     * GPIO Output Pins Pullup
     * Can be GPIO_PUPD_NONE, GPIO_PUPD_PULLDOWN, GPIO_PUPD_PULLUP
     */
    uint8_t pull_up_down : 2;


    /** 
     * Flags that specify if the pins are inversed. 
     * If true, abst_digital_write and abst_digital_read functions inverse the value at the pin.
     */
    uint16_t is_inverse : 16;
};
/**
 * Port indentifier
 */
enum abst_pin_port {
    /** Port A */
    ABST_GPIOA = 0,
    /** Port B */
    ABST_GPIOB,
    /** Port C */
    ABST_GPIOC,
    /** Port D */
    ABST_GPIOD,
    /** Port E */
    ABST_GPIOE,
    /** Port F */
    ABST_GPIOF,
    /** Port G */
    ABST_GPIOG,
    /** Port H */
    ABST_GPIOH,
    /** Port I */
    ABST_GPIOI,
    /** Port J */
    ABST_GPIOJ,
    /** Port K */
    ABST_GPIOK
};

void abst_init(uint32_t ahb);

void abst_gpio_init(const struct abst_pin *pin_ptr);

void abst_group_gpio_init(const struct abst_pin_group *pin_gr_ptr);

void abst_sys_tick_handler(void);

void abst_digital_write(const struct abst_pin *pin_ptr, bool value);

void abst_group_digital_write(const struct abst_pin_group *pin_gr_ptr, uint16_t values);

void abst_toggle(const struct abst_pin *pin_ptr);

bool abst_digital_read(const struct abst_pin *pin_ptr);

uint16_t abst_group_digital_read(const struct abst_pin_group *pin_gr_ptr);

void abst_pwm_soft(struct abst_pin *pin_ptr, uint8_t value);

bool abst_stop_pwm_soft(struct abst_pin *pin_ptr);

void abst_pwm_hard(struct abst_pin *pin_ptr, uint8_t value); // TODO

uint16_t abst_adc_read(struct abst_pin *pin_ptr);

void abst_delay_ms(uint64_t miliseconds);

void abst_delay_us(uint64_t microseconds);

void abst_sleep_wfi(void);

void abst_stop_sleep(void);

uint32_t abst_time_ms(void);

#endif //_ABSTRACT_STM32_H_