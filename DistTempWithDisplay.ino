/*
 * Distance and temperature measurement with digital display.
 * Pressing the button to switch between temperature and 
 * distance measurement.
 */

#include "Task.h"
#include "TaskList.h"
#include <SimpleDHT.h>       // Temp and Humidity Sensor
#include <hcsr04.h>          // Sonar range sensor
#include <LiquidCrystal.h>   // liquid crystal display
#include "PushButton.h"

 // Pin assignment
 const int dhtPin = 4;
 const int buttonPin = 3;
 const int hcsr04TriggerPin = 5;
 const int hcsr04EchoPin = 6;
 const int rsLCDPin = 7;
 const int enLCDPin = 8;
 const int d4LCDPin = 9;
 const int d5LCDPin = 10;
 const int d6LCDPin = 11;
 const int d7LCDPin = 12;

 PushButton button1(buttonPin);       // State button to switch between Temp and Humidity and Distance
 SimpleDHT11 dht11(dhtPin);                                     // DHT temperature humidity sensor
 HCSR04 hcsr04 = HCSR04(hcsr04TriggerPin, hcsr04EchoPin);       // HCSR04 sonic range sensor
 LiquidCrystal lcd(rsLCDPin, enLCDPin, d4LCDPin, d5LCDPin, d6LCDPin, d7LCDPin);

class Task1 : public Task {
  public: 
  Task1(String n) : Task(n) {}
  void loop() {
      Serial.println("Task 1");
      delay(1000);
  }  
};

class Task2 : public Task {
  public:
  Task2(String n) : Task(n) {}
  void loop () {
      Serial.println(" Task 2");
      delay(2500);
  }
};

class MeasureTemperature : public Task {
  public:
    MeasureTemperature(String n): Task(n) {temp = humidity = 0;}
    void loop() {
      if ((err = dht11.read(&temp, &humidity, NULL)) != SimpleDHTErrSuccess) {
          Serial.print("Error reading DHT, err="); Serial.println(err);
      } else {
        Serial.print("Temp = "); Serial.print(temp); Serial.println(" C");
        Serial.print("Humidty = "); Serial.print(humidity); Serial.println(" H");
      }
      delay(2500);  // Sample ever 1.5s
    }

    byte temp;
    byte humidity;
    int err;
};

class MeasureDistance : public Task {
  public:
    MeasureDistance(String n) : Task(n) {dist = 0;};
    void loop() {
      dist = hcsr04.distanceInMillimeters();
      Serial.print("Distance = "); Serial.print(dist); Serial.println(" mm");
      delay(1000);   
    }
    long dist;
};

class ToggleButton : public Task {
  public:
    ToggleButton(String n, PushButton *b) : Task(n) { pushButton = b; prevReading = LOW; state = false;}
    void loop() {
      int reading = pushButton->readButton();
      if (reading && !prevReading) 
        state = !state;           // flip state
      Serial.print("Button = "); Serial.println(state);
      prevReading = reading;
      delay(50);
    }

    PushButton *pushButton;
    int prevReading;             // prior reading of the button
    bool state;
};

class ShowTempAndDist : public Task {
  public:
    ShowTempAndDist(String n, MeasureTemperature *temp, MeasureDistance *dist, ToggleButton *button) : Task(n) {
        measureTemperature = temp; measureDistance = dist; toggleButton = button; }
    void loop() {
      if (toggleButton->state) {
        lcd.clear();
        lcd.print("Temp = " ); lcd.print(measureTemperature->temp); lcd.print(" C");
        lcd.setCursor(0,1);
        lcd.print("Humidity = "); lcd.print(measureTemperature->humidity); lcd.print(" H");
      } else {
        lcd.clear();
        lcd.print("Dist. = "); lcd.print(measureDistance->dist); lcd.print(" mm");
      }
      delay(250);   
    }

    MeasureTemperature *measureTemperature;
    MeasureDistance *measureDistance;
    ToggleButton *toggleButton;
};


Task1 task1 = Task1("Task 1");
Task2 task2 = Task2("Task 2");
MeasureTemperature measureTemperature = MeasureTemperature("Measure Temperature");
MeasureDistance measureDistance = MeasureDistance("Measure Distance");
ToggleButton toggleButton = ToggleButton("Push Button", &button1);
ShowTempAndDist showTempAndDist = ShowTempAndDist("Show Temp and Distance", &measureTemperature, &measureDistance, &toggleButton);

TaskList taskList = TaskList();

void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);

  lcd.begin(16, 2);
  lcd.print("Booting...");

  taskList.addTask(&task1);
  taskList.addTask(&task2);
  taskList.addTask(&measureTemperature);
  taskList.addTask(&measureDistance);
  taskList.addTask(&showTempAndDist);
  taskList.addTask(&toggleButton);
}

void loop() {
  // put your main code here, to run repeatedly:

  taskList.run();
}
