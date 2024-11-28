
#ifndef TFT_H
#define TFT_H
#include "touch.h"

void TFT_init(void);
//void TFT_touch(void);
void TFT_display(void);
void TFT_buttons(void);
void erase_flash(void);
void read_flash(void);
void load_flash_data(void);
void write_flash(void);
void attach_flash(void);
void init_flash(void);
/* some pre-definded colors */
#define RED 0xff0000UL
#define ORANGE 0xffa500UL
#define GREEN 0x00ff00UL
#define BLUE 0x0000ffUL
#define BLUE_1 0x5dade2L
#define YELLOW 0xffff00UL
#define MAGENTA 0xff00ffUL
#define PURPLE 0x800080UL
#define WHITE 0xffffffUL
#define BLACK 0x000000UL
#define GREY 0x505050UL
#define LIGHTGREY 0x808080UL
#define DARKGREY 0x303030UL

#define DISPLAY_WIDTH 800
#define DISPLAY_HEIGHT 480


#endif /* TFT_H */
