#include "Arduino.h"
#include "PushButton.h"

PushButton::PushButton (byte pin ) {
    _ioPin = pin;
    pinMode(pin, INPUT_PULLUP);
  }

  // Read the current state without reading the button 
  bool PushButton::currentState() {
      return _currentState;
  }

  // Read the state of the button and set the current state
  bool PushButton::readButton () {
     _currentState = digitalRead(_ioPin) == HIGH ? true : false;
     return _currentState;
  }

  bool PushButton::fallingEdge() {
      bool newState = digitalRead(_ioPin);
      if (_currentState && (newState == LOW)) {
          _currentState = false;
          return true;
      } else {
          _currentState = newState == HIGH ? true : false;
        return false;
      }
  }

  bool PushButton::risingEdge() {
      bool newState = digitalRead(_ioPin);
      if (!_currentState && (newState == HIGH)) {
          _currentState = true;
          return true;
      } else {
          _currentState = newState == HIGH ? true : false;
        return false;
      }
    
  }
