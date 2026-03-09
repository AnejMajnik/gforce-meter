#pragma once
#define LGFX_USE_V1
#include <LovyanGFX.hpp>

class LGFX : public lgfx::LGFX_Device {
    lgfx::Panel_GC9A01  _panel;
    lgfx::Bus_SPI       _bus;
    lgfx::Light_PWM     _light;

public:
    LGFX() {
        auto bus_cfg = _bus.config();
        bus_cfg.spi_host = SPI3_HOST;
        bus_cfg.freq_write = 80000000;
        bus_cfg.pin_mosi = 11;
        bus_cfg.pin_miso = -1;
        bus_cfg.pin_sclk = 10;
        bus_cfg.pin_dc   = 8;
        _bus.config(bus_cfg);
        _panel.setBus(&_bus);

        auto pan_cfg = _panel.config();
        pan_cfg.pin_cs   = 9;
        pan_cfg.pin_rst  = 12;
        pan_cfg.pin_busy = -1;

        //pan_cfg.rgb_order = true;

        pan_cfg.memory_width  = 240;
        pan_cfg.memory_height = 240;
        pan_cfg.panel_width   = 240;
        pan_cfg.panel_height  = 240;

        _panel.config(pan_cfg);
        

        auto bl_cfg = _light.config();
        bl_cfg.pin_bl      = 40;
        bl_cfg.invert      = false;
        bl_cfg.freq        = 44100;
        bl_cfg.pwm_channel = 0;
        _light.config(bl_cfg);
        _panel.setLight(&_light);

        setPanel(&_panel);
    }
};