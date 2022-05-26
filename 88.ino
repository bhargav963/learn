#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define echoPin 2
#define trigPin 4

RF24 radio(7,8);

const byte address[6] = "00001";

long duration;
int distance;

void setup() {
  Serial.begin(19200);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MAX);
  radio.setDataRate(RF24_250KBPS);
  radio.stopListening();
}

void loop() {
  const char text[] = "nrf";
  const char t1[] = "Yes";
  const char t2[] = "No";
  radio.write(&text, sizeof(text));
  delay(2000);
  Serial.print(text);

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  

  if(distance<=25)
  {  
    radio.write(&t1, sizeof(t1)); 
    Serial.print(t1);
  }
  else
  {
    radio.write(&t2, sizeof(t2));
    Serial.print(t2);  
  }
  Serial.print("Distance: ");
  Serial.println(distance);
}
