#ifndef _LCD_H
#define _LCD_H

int lcd_init(void);
esp_err_t lcd_display_jpg(char *data, int width, int height);
#endif
