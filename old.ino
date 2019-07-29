/*
 * Distance and temperate measurement with digital display.
 * Pressing the button the switch beteen temperater and 
 * distance measurement.
 */

 #include <SimpleDHT.h>       // Temp and Humidity Sensor
 #include <hcsr04.h>          // Sonar range sensor
 #include <LiquidCrystal.h>   // liquid crystal display
 #include <PushButton.h>      // My pushbutton library
 
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
 
 void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);

  // pinMode(buttonPin, INPUT_PULLUP);   // Mode select switch
  lcd.begin(16, 2);
  lcd.print("Booting...");
  delay(1000);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  long dist = 0;
  byte temp = 0;
  byte humidity = 0;
  int err = SimpleDHTErrSuccess;
  static bool showTemp = true;
  
  dist = hcsr04.distanceInMillimeters();
  Serial.print("Distance = "); Serial.print(dist); Serial.println(" mm");

  if ((err = dht11.read(&temp, &humidity, NULL)) != SimpleDHTErrSuccess) {
      Serial.print("Error reading DHT, err="); Serial.println(err);
  } else {
    Serial.print("Temp = "); Serial.print(temp); Serial.println(" C");
    Serial.print("Humidty = "); Serial.print(humidity); Serial.println(" H");
  }

  // If falling state then toggle switch
  button1.fallingEdge();
  Serial.print("Switch = "); Serial.println(button1.currentState()); // Serial.println(digitalRead(buttonPin));

  if (showTemp) {
    lcd.clear();
    lcd.print("Temp = " ); lcd.print(temp); lcd.print(" C");
    lcd.setCursor(0,1);
    lcd.print("Humidity = "); lcd.print(humidity); lcd.print(" H");
  } else {
    lcd.clear();
    lcd.print("Dist. = "); lcd.print(dist); lcd.print(" mm");
  }
  showTemp = !showTemp;
  Serial.print("showTemp = "); Serial.println(showTemp);

  delay(1500);

 }
