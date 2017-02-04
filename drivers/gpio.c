#include <gpio.h>

void gpio_select_function(uint32_t pin, uint32_t function)
{
	if(pin < 53 && pin > 7){
		uint32_t *gpio = (uint32_t *)GPIO_BASE;

		uint32_t shift = pin;
		uint32_t index = 0;

		if(pin > 10){
			shift = pin % 10;
			index = (pin / 10) * 4;
		}
		shift *= 3;
		function = function << shift;
		gpio[index] = function;
	}
	
}

void gpio_set_pin(uint32_t pin, uint32_t value)
{
	if(pin < 53){
		uint32_t *gpio = (uint32_t *)GPIO_BASE;

		uint32_t set = pin / 32;
		uint32_t bit = 1 << (pin & 0x1f);

		if(value)
			gpio[set+7] = bit;
		else
			gpio[set+10] = bit;
	}
}
