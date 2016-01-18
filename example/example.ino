
#include <Arduino.h>
#include <CLIO_STEERING_WHEEL_CMD.h>

uint8_t  inputs[3]  = {0, 1, 2}; //analog A0, A1, A2
uint8_t  outputs[3] = {10, 9, 8}; //digital D7, D6, D5
WHEEL_CMD controller(inputs, outputs);

String buttons_str_test[9] = {
    "BTN_SOURCE_RIGHT",
    "BTN_MUTE",
    "BTN_SOURCE_LEFT",
    "BTN_WHEEL_1",
    "BTN_WHEEL_2",
    "BTN_WHEEL_3",
    "BTN_MODE",
    "BTN_VOL_UP",
    "BTN_VOL_DOWN",
};

void setup() {
    Serial.begin(9600);
    Serial.println("Hello world");
};

void loop() {

    controller.update();

    for (uint8_t i=0; i < NB_BUTTONS; i++) {
        if (i>2 && i < 6) { // do not pass on wheel buttons
            continue;
        }
        uint8_t btn = controller.getButton(i);
        if (btn == PRESSED) {
            Serial.print(buttons_str_test[i]);
            Serial.println(F(" PRESS "));
        } else if (btn == HOLD) {
            Serial.print(buttons_str_test[i]);
            Serial.println(F(" HOLD "));
        }
        /*else { // btn == NO_NEWS
            Serial.println("no new state");
        }*/
    }

    uint8_t wheel = controller.getWheel();
    if (wheel == WHEEL_UP) {
        Serial.println(F("Wheel UP"));
    } else if (wheel == WHEEL_DOWN) {
        Serial.println(F("Wheel DOWN"));
    }

}
