#include "abst_libopencm3.h"
#include "abstractSTM32.h"

#include <libopencm3/stm32/adc.h>

uint32_t _abst_conv_adc_resolution(uint8_t resolution)
{
#ifdef STM32F1
    return 0; // Not implemented in STM32F1
#endif // STM32F1

#ifdef STM32F4
    switch (resolution) {
        case ABST_ADC_RES_12BIT:
            return ADC_CR1_RES_12BIT;
            break;
        case ABST_ADC_RES_10BIT:
            return ADC_CR1_RES_10BIT;
            break;
        case ABST_ADC_RES_8BIT:
            return ADC_CR1_RES_8BIT;
            break;
        case ABST_ADC_RES_6BIT:
            return ADC_CR1_RES_6BIT;
            break;
        default:
            return 0; // Wrong argument
    }
#endif // STM32F4
}

