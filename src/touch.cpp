#include "EVE.h"
#include "tft.h"
#include "touch.h"

void TFT_touch(void)
{
	uint8_t tag;
    static uint32_t touch_previous_millis = 0;
    uint32_t touch_current_millis;
	
	if(EVE_busy()) /* is EVE still processing the last display list? */
	{
		return;
	}
    touch_current_millis = millis();
	tag = EVE_memRead8(REG_TOUCH_TAG); /* read the value for the first touch point */

	switch(tag)
	{
		case 10:
            if ( ((touch_current_millis - touch_previous_millis) > 500)){
                touch_previous_millis = touch_current_millis;
			    erase_flash();
                }
			break;
		case 20:
            if ( ((touch_current_millis - touch_previous_millis) > 500)){
                touch_previous_millis = touch_current_millis;
			    load_flash_data();
                }			
            break;
		case 30:
            if ( ((touch_current_millis - touch_previous_millis) > 500)){
                touch_previous_millis = touch_current_millis;
			    write_flash();
                }
			break;
		case 40:
            if ( ((touch_current_millis - touch_previous_millis) > 500)){
                touch_previous_millis = touch_current_millis;
			    read_flash();
                }

			break;
		case 50:
            if ( ((touch_current_millis - touch_previous_millis) > 500)){
                touch_previous_millis = touch_current_millis;
			    init_flash();
                }
			break;

	}
}

