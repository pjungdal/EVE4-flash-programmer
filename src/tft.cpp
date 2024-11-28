#include "EVE.h"
#include "tft.h"

uint8_t tft_active = 0;
bool buttons_init =false;
extern const uint8_t upbutton[12288] PROGMEM;
extern const uint8_t pagebutton[12288] PROGMEM;
extern const uint8_t returnbutton[12288] PROGMEM;
extern const uint8_t downbutton[12288] PROGMEM;
extern const uint8_t menubutton[12288] PROGMEM;
extern const uint8_t blob[4096] PROGMEM;

char status_str[200];
uint8_t disp=false;
uint8_t programming=false;
uint8_t erasing=false;
uint8_t flashstatus = 0;
void TFT_buttons(void)
{
if(tft_active != 0U)
{
if (!buttons_init){
EVE_cmd_dl(DL_TAG + 10U);
EVE_cmd_fgcolor(0);
EVE_cmd_button(680,0,120,100,27,0,"Erase");
EVE_cmd_dl(DL_TAG);

EVE_cmd_dl(DL_TAG + 20U);
EVE_cmd_button(680,100,120,90,27,0,"Load");
EVE_cmd_dl(DL_TAG);

EVE_cmd_dl(DL_TAG + 30U);
EVE_cmd_button(680,190,120,100,27,0,"Program");
EVE_cmd_dl(DL_TAG);

EVE_cmd_dl(DL_TAG + 40U);
EVE_cmd_button(680,290,120,90,27,0,"Read");
EVE_cmd_dl(DL_TAG);

EVE_cmd_dl(DL_TAG + 50U);
EVE_cmd_button(680,380,120,100,27,0,"Init flash");
EVE_cmd_dl(DL_TAG);
//buttons_init=true;
}
}
}
void initStaticBackground(void)
{
    EVE_cmd_dl(CMD_DLSTART); /* Start the display list */
    EVE_cmd_dl(DL_TAG); /* no tag = 0 - do not use the following objects for touch-detection */
    EVE_cmd_dl(DL_END);
  


}

void TFT_init(void)
{
uint32_t src,width,heigth;
char str[100];	
uint8_t ftData8;
uint32_t ftaddress;
uint32_t count;
uint32_t flstatus;
if (E_OK == EVE_init())
	{

		tft_active = 1;
		EVE_cmd_flashattach();
		Serial.println(EVE_cmd_flashfast(),16);
		flashstatus=EVE_memRead8(REG_FLASH_STATUS);
        EVE_memWrite8(REG_PWM_DUTY, 0x30);
		initStaticBackground();
		switch (flashstatus){
			case 0:sprintf(status_str,"%s ","Flash status: FLASH_STATUS_INIT ");
			break;
			case 1:sprintf(status_str,"%s ","Flash status: FLASH_STATUS_DETACHED");
			break;
			case 2:sprintf(status_str,"%s ","Flash status: FLASH_STATUS_BASIC");
			break;
			case 3:sprintf(status_str,"%s ","Flash status: FLASH_STATUS_FULL");
			break;
		}
				Serial.print("TFT init");Serial.print(" status:");Serial.println(status_str);
		disp=false;
    }
}
void read_flash(){
Serial.println("read flash");
Serial.println(EVE_cmd_flashfast(),16);
sprintf(status_str,"%s ","Flash read and displayed");
attach_flash();
disp=true;
}
void load_flash_data(){
	uint32_t src,width,heigth;
char str[100];	
uint8_t ftData8;
uint32_t count;
uint32_t ram_g_adr=0;

for (count=0;(count < 4096);count++){
	ftData8= blob[count];
	EVE_memWrite8(ram_g_adr,ftData8);
	ram_g_adr++;
}
Serial.print("1 block: ");Serial.print(ram_g_adr);Serial.print(" HEX: ");Serial.println(ram_g_adr,16);
for (count=0;(count < 12288);count++){
	ftData8= pagebutton[count];
	EVE_memWrite8(ram_g_adr,ftData8);
	ram_g_adr++;
}
Serial.print("2 block: ");Serial.print(ram_g_adr);Serial.print(" HEX: ");Serial.println(ram_g_adr,16);

for (count=0;(count < 12288);count++){
	ftData8= upbutton[count];
	EVE_memWrite8(ram_g_adr,ftData8);
	ram_g_adr++;
}
Serial.print("3 block: ");Serial.print(ram_g_adr);Serial.print(" HEX: ");Serial.println(ram_g_adr,16);

for (count=0;(count < 12288);count++){
	ftData8= returnbutton[count];
	EVE_memWrite8(ram_g_adr,ftData8);
	ram_g_adr++;
}
Serial.print("4 block: ");Serial.print(ram_g_adr);Serial.print(" HEX: ");Serial.println(ram_g_adr,16);

for (count=0;(count < 12288);count++){
	ftData8= downbutton[count];
	EVE_memWrite8(ram_g_adr,ftData8);
	ram_g_adr++;
}
Serial.print("5 block: ");Serial.print(ram_g_adr);Serial.print(" HEX: ");Serial.println(ram_g_adr,16);


for (count=0;(count < 12288);count++){
	ftData8= menubutton[count];
	EVE_memWrite8(ram_g_adr,ftData8);
	ram_g_adr++;
}
Serial.print("6 block: ");Serial.print(ram_g_adr);Serial.print(" HEX: ");Serial.println(ram_g_adr,16);

sprintf(status_str,"%s ","Flash data loaded");
disp=false;
}
void write_flash(void){

if (!programming){
programming=true;
Serial.println("program flash");
sprintf(status_str,"%s ","Writing data to flash");
EVE_cmd_flashupdate(0,0,65536);
Serial.println("Complete");
attach_flash();
disp=false;
}
}
void init_flash(void){
uint32_t src,width,heigth;
char str[100];	
uint8_t ftData8;
uint32_t ftaddress;
uint32_t count;
Serial.println("init flash");
ftaddress=0;
/*	for (count=0;(count < 4096);count++){
		ftaddress=count; ftData8= blob[ftaddress];

		EVE_memWrite8(ftaddress,ftData8);
	}
	EVE_cmd_flashupdate(0,0,4096);	*/
	//attach_flash();
	disp=false;
	//erase_flash();
}

void erase_flash(){
uint32_t src,width,heigth;
char str[100];	
uint8_t ftData8;
uint32_t ftaddress;
uint32_t count;
uint8_t	flashstatus;
if(!erasing){
//	erasing=true;
Serial.println("erase flash");
EVE_cmd_flashattach();
EVE_cmd_flasherase();
sprintf(status_str,"%s ","Flash erased");
disp=false;
//EVE_cmd_clearcache();
attach_flash();
Serial.println(status_str);
}
}
void attach_flash(){		
//		EVE_cmd_flashattach();
//		EVE_cmd_flashfast();
		flashstatus=EVE_memRead8(REG_FLASH_STATUS);
		switch (flashstatus){
			case 0:sprintf(status_str,"%s ","Flash status: FLASH_STATUS_INIT ");
			break;
			case 1:sprintf(status_str,"%s ","Flash status: FLASH_STATUS_DETACHED");
			break;
			case 2:sprintf(status_str,"%s ","Flash status: FLASH_STATUS_BASIC");
			break;
			case 3:sprintf(status_str,"%s ","Flash status: FLASH_STATUS_FULL");
			break;
		}
}
void TFT_display(void)
{
	//if(tft_active != 0)
	{

		EVE_start_cmd_burst(); /* start writing to the cmd-fifo as one stream of bytes, only sending the address once */

		EVE_cmd_dl_burst(CMD_DLSTART); /* start the display list */
		EVE_cmd_dl_burst(DL_CLEAR_COLOR_RGB | WHITE); /* set the default clear color to white */
		EVE_cmd_dl_burst(DL_CLEAR | CLR_COL | CLR_STN | CLR_TAG); /* clear the screen - this and the previous prevent artifacts between lists, Attributes are the color, stencil and tag buffers */
		EVE_cmd_dl(DL_VERTEX_FORMAT);
		TFT_buttons();
		EVE_cmd_dl_burst(SCISSOR_SIZE(680,480));
		EVE_cmd_dl_burst(CLEAR_COLOR_RGB(0x80,0x80,0x80));
		EVE_cmd_dl_burst(CLEAR(1,0,0));

		EVE_cmd_dl_burst(DL_COLOR_RGB | BLACK);
		EVE_color_rgb_burst(RED);
		EVE_cmd_fillwidth_burst(680);
		EVE_cmd_text_burst(0,430,27,0,status_str);
if(disp){
		EVE_color_rgb_burst(WHITE);
		EVE_cmd_dl_burst(DL_BEGIN | EVE_BITMAPS);
		EVE_cmd_setbitmap_burst(0x800000|128,EVE_ASTC_4X4,120,100);
		EVE_cmd_dl_burst(VERTEX2F(0, 0));
		EVE_cmd_setbitmap_burst(0x800000|512,EVE_ASTC_4X4,120,100);
		EVE_cmd_dl_burst(VERTEX2F(120, 0));
		EVE_cmd_setbitmap_burst(0x800000|896,EVE_ASTC_4X4,120,100);
		EVE_cmd_dl_burst(VERTEX2F(240, 0));
		EVE_cmd_setbitmap_burst(0x800000|1280,EVE_ASTC_4X4,120,100);
		EVE_cmd_dl_burst(VERTEX2F(360, 0));
		EVE_cmd_setbitmap_burst(0x800000|1664,EVE_ASTC_4X4,120,100);
		EVE_cmd_dl_burst(VERTEX2F(480, 0));
		EVE_cmd_dl_burst(DL_END);}

    	EVE_execute_cmd;
		EVE_cmd_dl_burst(DL_DISPLAY); /* instruct the graphics processor to show the list */
		EVE_cmd_dl_burst(CMD_SWAP); /* make this list active */
		EVE_end_cmd_burst();
	}
}