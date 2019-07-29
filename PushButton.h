#ifndef PUSH_BUTTON_H
#define PUSH_BUTTON_H

#include "Arduino.h"

class PushButton {
  public:
    PushButton(byte pin);
    bool readButton();
    bool currentState();
    bool fallingEdge();
    bool risingEdge();
     
  private:
    int _ioPin = 0;
    bool _currentState = true;
    bool _lastState = false;
};

#endif
