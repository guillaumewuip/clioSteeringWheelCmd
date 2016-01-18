#include "CLIO_STEERING_WHEEL_CMD.h"

#include "Arduino.h"

uint8_t buttons_indexes[NB_BUTTONS] = {0, 1, 2, 6, 7, 8};
uint8_t wheel_indexes[NB_WHEEL] = {3, 4, 5};

WHEEL_CMD::WHEEL_CMD(uint8_t *inputs, uint8_t *outputs) {
    _inputs = inputs;
    _outputs = outputs;

    _intervalPress = INTERVAL_PRESS;
    _intervalHold = INTERVAL_HOLD;
};

void WHEEL_CMD::setIntervalPress(int interval) {
    _intervalPress = interval;
};

void WHEEL_CMD::setIntervalHold(int interval) {
    _intervalHold = interval;
};

void WHEEL_CMD::update() {

    bool keys[9] = {
        false, false, false,
        false, false, false,
        false, false, false,
    };

    for (uint8_t c=0; c < NB_OUTPUTS; c++) { //for each output
        //make the output HIGH
        pinMode(_outputs[c], OUTPUT);
        digitalWrite(_outputs[c], LOW);

        for (uint8_t k=0; k < NB_INPUTS; k++) { //listen each input
            keys[k*3 + c] = analogRead(_inputs[k]) == 0;
        }

        //reset the output to LOW
        digitalWrite(_outputs[c], HIGH);
        pinMode(_outputs[c], INPUT);
    }

    for (uint8_t i=0; i < NB_BUTTONS; i++) {
        //do not overflow uint16_t number
        _states[i] = keys[i];
        keys[i] && _buttons[i] < 0x7fff && _buttons[i]++;
    }

    //Serial.println();
    //for(uint8_t i =0; i < NB_BUTTONS; i++) {
        //Serial.print(keys[i]);
        //if ((i+1)%3 == 0) {
            //Serial.println();
        //}
    //}
    //Serial.println();

};

uint8_t WHEEL_CMD::getButton(uint8_t button) {

    uint8_t result;

    if (button != 3 && button != 4 && button != 5) {

        if (!_states[button] && _buttons[button] > _intervalPress
                && _buttons[button] < _intervalHold) {
            _buttons[button] = 0;
            return PRESSED;
        } else if (_buttons[button] == _intervalHold) {
            _buttons[button] = -_intervalPress*7;
            return HOLD;
        } else {
            return NO_NEWS;
        }
    }

};

uint8_t WHEEL_CMD::getWheel() {

    //if all true wheel buttons are down, we're on a transition
    if (_buttons[3] == 0 and _buttons[4] == 0 and _buttons[5] == 0) {
        return NO_NEWS;
    }

    //which wheel button is up ?
    uint8_t tmp;
    if (_buttons[3] > 0) {
        tmp = 0;
        _buttons[3] = 0;
    } else if (_buttons[4] > 0) {
        tmp = 1;
        _buttons[4] = 0;
    } else {
        tmp = 2;
        _buttons[5] = 0;
    }

    //if it has change since last time
    if (tmp != _currentWheel and _currentWheel != 3) {
        uint8_t result;

        //update wheel status
        _lastWheel = _currentWheel;
        _currentWheel = tmp;

        if ((_lastWheel == 0 && _currentWheel == 1)
            || (_lastWheel == 1 && _currentWheel == 2)
            || (_lastWheel == 2 && _currentWheel == 0)) {
            return WHEEL_DOWN;
        } else{
            return WHEEL_UP;
        }

    } else {
        //if _currentWheel == 3, it's the first time we're here
        //so we return NO_NEWS and update _currentWheel
        //in order to prevent rising event at arduino start
        if (_currentWheel == 3) {
            _currentWheel = tmp;
        }
        return NO_NEWS;
    }

};
