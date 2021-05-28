#include <stdio.h>
#include "pin_mux.h"
#include "fsl_gpio.h"
#include "fsl_port.h"
#include "fsl_common.h"
#include "GPIO.h"

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


int main(void) {

	const port_pin_config_t porta_pin4_config = {
	    kPORT_PullUp,                                            /* Internal pull-up resistor is enabled */
	    kPORT_FastSlewRate,                                      /* Fast slew rate is configured */
	    kPORT_PassiveFilterDisable,                              /* Passive filter is disabled */
	    kPORT_OpenDrainDisable,                                  /* Open drain is disabled */
	    kPORT_HighDriveStrength,                                 /* High drive strength is configured */
	    kPORT_MuxAsGpio,                                         /* Pin is configured as PTA4 */
	    kPORT_UnlockRegister                                     /* Pin Control Register fields [15:0] are not locked */
	  };

	const port_pin_config_t portc_pin6_config = {
		    kPORT_PullUp,                                            /* Internal pull-up resistor is enabled */
		    kPORT_FastSlewRate,                                      /* Fast slew rate is configured */
		    kPORT_PassiveFilterDisable,                              /* Passive filter is disabled */
		    kPORT_OpenDrainDisable,                                  /* Open drain is disabled */
		    kPORT_HighDriveStrength,                                 /* High drive strength is configured */
		    kPORT_MuxAsGpio,                                         /* Pin is configured as PTA4 */
		    kPORT_UnlockRegister                                     /* Pin Control Register fields [15:0] are not locked */
		  };

  CLOCK_EnableClock(kCLOCK_PortA);
  CLOCK_EnableClock(kCLOCK_PortB);
  CLOCK_EnableClock(kCLOCK_PortC);

  PORT_SetPinConfig(PORTA, PIN4, &porta_pin4_config);
  PORT_SetPinConfig(PORTC, PIN6, &portc_pin6_config);

  PORT_SetPinInterruptConfig(PORTA, PIN4, kPORT_InterruptFallingEdge);
  PORT_SetPinInterruptConfig(PORTC, PIN6, kPORT_InterruptFallingEdge);

  GPIO_PinInit(GPIOA, PIN4, &sw_config);
  GPIO_PinInit(GPIOC, PIN6, &sw_config);


  PORT_SetPinMux(PORTB, PIN22, kPORT_MuxAsGpio);
  PORT_SetPinMux(PORTC, PIN6, kPORT_MuxAsGpio);


  GPIO_PinInit(GPIOB, PIN22, &led_config);
  GPIO_PinInit(GPIOC, PIN6, &sw_config);


  NVIC_EnableIRQ(PORTA_IRQn);
  NVIC_EnableIRQ(PORTC_IRQn);

  	/**It Sets the priority of the IRQ*/

  NVIC_SetPriority(PORTA_IRQn, 2);
  NVIC_SetPriority(PORTC_IRQn, 4);

    while(1) {

    	if(g_ButtonPress)
    	{
    		GPIO_PortToggle(GPIOB, 1u << PIN22);
    		SDK_DelayAtLeastUs(1000000,21000000);
    		g_ButtonPress=false;
    	}


    }
    return 0 ;
}
