
#ifndef CLIO_STEERING_WHEEL_CMD_H
#define CLIO_STEERING_WHEEL_CMD_H

#include "Arduino.h"

#define NB_INPUTS  3
#define NB_OUTPUTS 3
#define NB_BUTTONS 9
#define NB_WHEEL   3

#define NO_NEWS    0
#define HOLD       2
#define PRESSED    1
#define WHEEL_UP   2
#define WHEEL_DOWN 1

#define BTN_SOURCE_RIGHT  0
#define BTN_MUTE          1
#define BTN_SOURCE_LEFT   2
#define BTN_WHEEL_1       3
#define BTN_WHEEL_2       4
#define BTN_WHEEL_3       5
#define BTN_MODE          6
#define BTN_VOL_UP        7
#define BTN_VOL_DOWN      8

#define INTERVAL_PRESS    70
#define INTERVAL_HOLD     750

class WHEEL_CMD {
    public:
        /**
         * WHEEL_CMD
         *
         * @constructor
         * @abstract    An object to listen to Clio's buttons
         * @discussion  Below is the wiring of the controller
         *              3 wires as outputs (O1, O2, O3)
         *              3 wires as inputs  (I1, I2, I3)
         *              When pushing a button on the controller, it make a
         *              connexion between an output and an input
         *              This library will activate alternatly each output
         *              with +5V while listenning on analog inputs.
         *              This way, we can guess wich button is pressed.
         *
         * @see         http://www.forum-auto.com/marques/renault/sujet73603.htm
         *              (French)
         * @see http://mike.f.free.fr/cmd1.jpg for the image
         *
         * Wiring :

                 O1 O2 O3
                  |  |  |
            I1 ---|--|--|-  (black)
            I2 ---|--|--|-  (brown)
            I3 ---|--|--|-  (red)
                  |  |  |
              (green)|  |
                  (blue)|
                     (yellow)

         *
         * @example
         *

            uint8_t[3]  inputs  = {0, 1, 2}; //analog A0, A1, A2
            uint8_t[3]  outputs = {7, 6, 5}; //digital D7, D6, D5
            controller = WHEEL_CMD(inputs, outputs);

         *
         * @param   {*[3]uint8_t}    Pointer to array : 3 pins where the inputs
         *                           wire are linked to (analog pins)
         * @param   {*[3]uint8_t}    Pointer to array : 3 pins where the outputs
         *                           wire are linked to (digital pins)
         */
        WHEEL_CMD(uint8_t *inputs, uint8_t *outputs);

        /**
         * update()
         *
         * @method
         * @abstract    Update each button state
         * @discussion  You have to call this method before getting any
         *              new state. Typically in each loop();
         */
        void update();

        /**
         * getButton()
         *
         * @method
         * @abstract    Get button status (OFF, ON, HOLD)
         * @discussion  6 buttons on the controller:
         *              BTN_SOURCE_RIGHT
         *              BTN_MUTE
         *              BTN_SOURCE_LEFT
         *              BTN_MODE
         *              BTN_VOL_UP
         *              BTN_VOL_DOWN
         *
         * @example
         *
            control.update();
            if (control.getButton(NB_MUTE) == ON) {
                Serial.println("Mute pressed !");
            }
         *
         * @returns     {uint8_t}   Button's status
         *                          NO_NEWS, PRESSED or HOLD
         */
        uint8_t getButton(uint8_t button);

        /**
         * getWheel()
         *
         * @method
         * @abstract    Get wheel direction
         *
         * @example
         *
            control.update();
            if (control.getWheel() == UP) {
                Serial.println("Wheel is going UP");
            } else if (control.getWheel() == DOWN) {
                Serial.println("Wheel is going DOWN");
            }
         *
         * @returns {uint8_t}   Wheel direction
         *                      NO_NEWS (not moving), WHEEL_UP or WHEEL_DOWN
         */
        uint8_t getWheel();

    private:
        uint8_t     *_inputs;
        uint8_t     *_outputs;
        uint16_t    _buttons[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
        uint8_t     _lastWheel;
        uint8_t     _currentWheel = 3;

};


#endif
