#include <Arduino.h>
#include "display.h"
#include <lvgl.h>
#include "QMI8658.h"

void setup() {
    Serial.begin(115200);

    Wire.setPins(6, 7);
    Wire.begin();  

    display_init();
    QMI8658_init();
}

void loop() {
    float acc[3];
    float gyro[3];
    QMI8658_read_xyz(acc, gyro, NULL);
    Serial.printf("acc: %.2f %.2f %.2f\n", acc[0]/1000, acc[1]/1000, acc[2]/1000);
    Serial.printf("gyro: %.2f %.2f %.2f\n", gyro[0], gyro[1], gyro[2]);
    display_update();
    delay(500);
}