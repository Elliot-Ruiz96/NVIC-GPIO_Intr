#include <stdio.h>
#include "pin_mux.h"
#include "fsl_gpio.h"
#include "fsl_port.h"
#include "fsl_common.h"
#include "GPIO.h"

volatile uint8_t g_ButtonPress = 0;

void PORTA_IRQHandler(void)
{

    GPIO_PortClearInterruptFlags(GPIOA, 1U << PIN4);

    g_ButtonPress = true;
    SDK_ISR_EXIT_BARRIER;
}

void PORTC_IRQHandler(void)
{

    GPIO_PortClearInterruptFlags(GPIOC, 1U << PIN6);

    g_ButtonPress = true;
    SDK_ISR_EXIT_BARRIER;
}

uint8_t GPIO_get_intr(void){

	return(g_ButtonPress);
}

void GPIO_set_intr(void){
	g_ButtonPress = false;
}
