#include "display.h"
#include "lgfx_config.h"
#include <lvgl.h>

#define LCD_H_RES 240
#define LCD_V_RES 240
#define DRAW_BUF_LINES 20

static LGFX lcd;
static lv_color_t draw_buf[LCD_H_RES * DRAW_BUF_LINES];
static lv_display_t *disp;

static void flush_cb(lv_display_t *d, const lv_area_t *area, uint8_t *px_map) {
    lcd.startWrite();
    lcd.setAddrWindow(area->x1, area->y1, area->x2 - area->x1 + 1, area->y2 - area->y1 + 1);
    lcd.writePixels((lgfx::rgb565_t *)px_map, (area->x2 - area->x1 + 1) * (area->y2 - area->y1 + 1));
    lcd.endWrite();
    lv_display_flush_ready(d);
}

void display_init() {
    lcd.init();
    lcd.setBrightness(255);
    lcd.invertDisplay(true);
    
    lv_init();
    disp = lv_display_create(LCD_H_RES, LCD_V_RES);
    lv_display_set_flush_cb(disp, flush_cb);
    lv_display_set_buffers(disp, draw_buf, NULL, sizeof(draw_buf), LV_DISPLAY_RENDER_MODE_PARTIAL);

    // Test: red screen via LVGL
    lv_obj_set_style_bg_color(lv_screen_active(), lv_color_hex(0x6600ff), LV_PART_MAIN);
    lv_obj_set_style_bg_opa(lv_screen_active(), LV_OPA_COVER, LV_PART_MAIN);
}

void display_update() {
    lv_timer_handler();
}