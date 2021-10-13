# Aurdoino Tetris Implementation
This repository holds a custom implementation for the [Tetris Game](https://en.wikipedia.org/wiki/Tetris) on an [Aurdoino Uno](https://store.arduino.cc/products/arduino-uno-rev3), 
done as a course project for Fall 2018's [Prof. Asadi](http://sharif.edu/~asadi/)'s Computer Structure and Language course at [Sharif University of Technology](http://ce.sharif.edu/): 

Both the `main.c` and `main.ino` implementations are essensially the same and the two formats are merely for convinence. All the hyperparameters are defined on top of the implemented module and can be changed to suit arbitrary hardware configurations. 

* **SCREEN_DIN_PIN**: Screen Digital Input pin (default: 2)
* **SCREEN_CS_PIN**: Screen Clear Pin (default: 1)
* **SCREEN_CLK_PIN**: Screen Clock Pin (default: 0)
* **DEVICE_WIDTH**: Each screen module's width in # LEDs (default: 8)
* **DEVICE_HEIGHT**: Each screen module's height in # LEDs (default: 8)
* **SCREEN_HEIGHT**: Screen height in # LEDs (default: 16)
* **SCREEN_WIDTH**: Screen width in # LEDs (default: 8)
* **JYS_X_PIN**: Joystick X analog pin (default: 0)
* **JYS_Y_PIN**: Joystick Y analog pin (default: 1)
* **JYS_BTN_PIN**: Joystick's digital button (default: 3)
* **JYS_VCC_PIN**: Joystick's vcc pin (default: 5)

## Requirements
* An Aurdoino Uno or a similar piece of hardware
* [Installed Max7219 driver](https://github.com/wayoda/LedControl)
* Max7219 LED dot matrix unit (or a stack of them, change the configurations appropriately) 
* Simple analog joystick module (with digital middle button)
* Everything else is basically plug n' play!

## LICENSE
MIT LICENSE, See [LISENCE](https://github.com/vahidzee/aurdoino-tetris/blob/master/LICENSE).