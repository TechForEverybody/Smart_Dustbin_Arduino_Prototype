#include <LiquidCrystal.h>
int triggerpin = 3;
int echopin = 2;
float distance, time_value;
float speed_of_sound = 0.0343;
int led_light = 10;
const int rs = 8, en = 9, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
void setup()
{
    lcd.begin(16, 2);
    lcd.print("Length=");
    Serial.begin(9600);
    pinMode(triggerpin, OUTPUT);
    pinMode(echopin, INPUT);
    pinMode(led_light, OUTPUT);
}

void loop()
{
    // resetting the system of triggering the waves
    digitalWrite(triggerpin, LOW);
    delayMicroseconds(10);

    // sending the waves for 10 miroseconds and then stopping the trigging the waves
    digitalWrite(triggerpin, HIGH);
    delayMicroseconds(10);
    digitalWrite(triggerpin, LOW);

    // taking the time of travel of sound wave from triggring it to the recieving
    time_value = pulseIn(echopin, HIGH);

    // calculating the distance of the object from the sound wave is reflected
    distance = (speed_of_sound * time_value)/2;
    Serial.print("Distance = ");
    Serial.print(distance);
    Serial.print(" cm\n");
    lcd.setCursor(7, 0);
    lcd.print(distance);
    lcd.print(" cm");
    if (distance < 15)
    {
        Serial.print("Open the dustbin\n");
        digitalWrite(led_light, HIGH);
    }
    else
    {
        Serial.print("dustbin is closed, no need to open\n");
        digitalWrite(led_light, LOW);
    }

    delay(1000);
}
