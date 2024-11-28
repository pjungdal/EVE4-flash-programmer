#include <Arduino.h>
#include <SPI.h>
#include "EVE.h"
#include "tft.h"
#include "EVE.h"

#include "tft.h"

void setup()
{	
    pinMode(EVE_CS, OUTPUT);
	digitalWrite(EVE_CS, HIGH);
	pinMode(EVE_PDN, OUTPUT);
	digitalWrite(EVE_PDN, LOW);
	Serial.begin(115200);
#if defined (ESP32) || (ARDUINO_NUCLEO_F446RE)
#ifdef EVE_USE_ESP_IDF
	EVE_init_spi();
	#endif
#else
	SPI.begin(); /* sets up the SPI to run in Mode 0 and 1 MHz */
	SPI.beginTransaction(SPISettings(8000000, MSBFIRST, SPI_MODE0));
#endif

	TFT_init();

}
void loop()
{	uint32_t current_millis;
	static uint32_t previous_millis = 0;
	static uint8_t display_delay = 0;
	static uint16_t led = 0;
	static uint8_t led_state = 0;
	uint32_t micros_start, micros_end;
	current_millis = millis();

    if ((current_millis - previous_millis) > 10) /* execute the code every 10 milli-seconds */
    {
        previous_millis = current_millis;

        micros_start = micros();
        TFT_touch();
        micros_end = micros();

        display_delay++;
        if (display_delay > 3) /* refresh the display every 20ms */
        {
            display_delay = 0;
            micros_start = micros();
            TFT_display();
            micros_end = micros();
        }
    }
}