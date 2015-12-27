
Clio Steering Wheel controller
=============================

*En Français plus loin ci-dessous.*

![Steering wheel controller](http://images.forum-auto.com/mesimages/834364/1.jpg)

#Story
I own a beautiful little [Renault Clio 2](https://fr.wikipedia.org/wiki/Renault_Clio_II).
As I was [building a Arduino-based radio](https://github.com/guillaumewuip/autoradio)
for the car, I wanted to be able to control it with the steering wheel
controller.

Here's a library to listen to the controller.

#Wiring and init
Simply remove the existing radio to find the good cable.

It's basically a matrix type keypad :

![Wiring](http://mike.f.free.fr/cmd1.jpg)

The library need the green, blue and yellow wires to be linked to digital pins,
and the black, brown and red ones to analog pins. Be carefull, order is
important !

```cpp
uint8_t  inputs[3]  = {
    0, //black
    1, //brown
    2  //red
}; //analog A0, A1, A2
uint8_t  outputs[3] = {
    7, //green
    6, //blue
    5  //yellow
}; //digital D7, D6, D5
WHEEL_CMD controller(inputs, outputs);
```

#API
See [example.ino](example/example.ino).

## `WHEEL_CMD::controller.update()`
Update buttons status.

Will goes on each output wire and check if there is a button pressed.

```cpp
void loop() {
    controller.update()
    //stuff
}
```

## `WHEEL_CMD::controller.getButton(uint8_t button)`
It returns the events `PRESSED`, `HOLD` or `NO_NEWS` of a button.

`button` could be :

- `BTN_SOURCE_RIGHT`
- `BTN_MUTE`
- `BTN_SOURCE_LEFT`
- `BTN_WHEEL_1`
- `BTN_WHEEL_2`
- `BTN_WHEEL_3`
- `BTN_MODE`
- `BTN_VOL_UP`
- `BTN_VOL_DOWN`

`PRESS` and `HOLD` events are fired after a certain number of `loop()`
defined by the `INTERVAL_PRESS` and `INTERVAL_HOLD` constants.

```cpp
uint8_t btn = controller.getButton(BTN_VOL_UP);
if (btn == PRESSED) {
    Serial.print(buttons_str_test[BTN_VOL_UP]);
    Serial.println(F("Volume up please"));
} else if (btn == HOLD) {
    Serial.print(buttons_str_test[BTN_VOL_UP]);
    Serial.println(F("Volume up is hold"));
}
```

## `WHEEL_CMD::getWheel()`
It returns `WHEEL_UP`, `WHEEL_DOWN` or `NO_NEWS` events of the little wheel
behind the controller.

```cpp
uint8_t wheel = controller.getWheel();
if (wheel == WHEEL_UP) {
    Serial.println(F("Wheel UP"));
} else if (wheel == WHEEL_DOWN) {
    Serial.println(F("Wheel DOWN"));
}
```

-----

**French:**

Je possède une Renault Clio 2 pour laquelle j'ai construit un autoradio Arduino
pour remplacer l'autoradio d'origine qui rendait l'âme.

J'ai eu besoin de développer cette librairie pour écouter les commandes envoyées
par le conducteur via la manette placée sous le volant

