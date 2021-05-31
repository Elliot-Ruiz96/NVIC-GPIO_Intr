#ifndef GPIO_H_
#define GPIO_H_

#include <stdint.h>

#define PIN22         22u
#define PIN6         6u
#define PIN4         4u

uint8_t GPIO_get_intr(void);

void GPIO_set_intr(void);

#endif /* GPIO_H_ */
