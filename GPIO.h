#ifndef GPIO_H_
#define GPIO_H_

uint8_t g_ButtonPress = 0;

 gpio_pin_config_t sw_config = {
        kGPIO_DigitalInput,
        0,
    };


gpio_pin_config_t led_config = {
        kGPIO_DigitalOutput,
        0,
    };

#define PIN22         22u
#define PIN6         6u
#define PIN4         4u

#endif /* GPIO_H_ */
