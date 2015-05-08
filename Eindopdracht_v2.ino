#include <Adafruit_NeoPixel.h> // Neopixel library aanroepen
#define PIN 12 // Neopixel staat aangesloten op digitale pin 5
Adafruit_NeoPixel strip = Adafruit_NeoPixel(1, PIN, NEO_GRB + NEO_KHZ800); // Aangeven dat we maar 1 neopixel gebruiken

//Sensoren
int pressMeter = A0; //Force Sensitive Resistor
int pressVal;
int tiltSensor = 7; //Tiltsensor
int tiltVal;

//LED lichten
int group1 = 11; //linksboven en rechtsonder led
int group2 = 10; //rechtsboven en linksonder led
int group3 = 9; //2 middelste leds
int neopixel = 12; //Neopixel, geldt als 7e led
long colorRange; //Een int kan maximaal tot 65,535 cijfers opslaan. Daarom wordt een long gebruikt dat tot 4,294,967,295 cijfers kan opslaan.

int result; //Bewaart het nummer dat random is gekozen
int delayTime = 200; // Tijdsduur pauze tussen animatie rollen van dobbelsteen
int showTime = 500; // Tijdsduur pauze tussen aan/uit LEDS tijdens animeren

void setup() {
  Serial.begin(9600);
  strip.begin(); //start de Neopixel op
  strip.setBrightness(10); //Lichtsterkte van de Neopixel staat op 15 omdat 255 te veel licht is
  strip.show();
  pinMode(group1 , OUTPUT);
  pinMode(group2 , OUTPUT);
  pinMode(group3 , OUTPUT);
  randomSeed(analogRead(5)); //Dit zorgt ervoor dat er altijd een random nummer wordt gekozen.
}

void loop() {
  tiltVal = digitalRead(tiltSensor); //Slaat de waarde van de tiltsensor op
  pressVal = analogRead(pressMeter); //Slaat de waarde van de druksensor op
  colorRange = map(pressVal, 0, 400, 16777215, 0); //Alle mogelijke kleuren worden gemapt tussen de waardes van de druksensor
  neoPixel();
  Serial.println(tiltVal);
  if (tiltVal == 0) { //Wanneer de tiltsensor wordt gekanteld worden deze functies uitgevoerd
      diceAnimate();
      diceResult();
      diceChoice();
  }
}

void diceResult() {
  result = random(1, 8); // Kies een random getal van 1 tot 7
}

void diceChoice() {
    switch(result) {
      case 1:    // 1 Gegooid
        neoPixel();
        break;
      case 2:    // 2 Gegooid
        digitalWrite(group1, HIGH);
        break;
      case 3:    // 3 Gegooid
        digitalWrite(group1, HIGH);
        neoPixel();
        break;
      case 4:    // 4 Gegooid
        digitalWrite(group1, HIGH);
        digitalWrite(group2, HIGH);
        break;
      case 5:    // 5 Gegooid
        digitalWrite(group1, HIGH);
        digitalWrite(group2, HIGH);
        neoPixel();
        break;
      case 6:    // 6 Gegooid
        digitalWrite(group1, HIGH);
        digitalWrite(group2, HIGH);
        digitalWrite(group3, HIGH);
        break;
      case 7:    // 7 Gegooid
        digitalWrite(group1, HIGH);
        digitalWrite(group2, HIGH);
        digitalWrite(group3, HIGH);
        neoPixel();
        break;
    }
}

void diceAnimate() {
  digitalWrite(group1, LOW); //Reset, alle LEDs uit
  digitalWrite(group2, LOW);
  digitalWrite(group3, LOW);
  strip.setPixelColor(0, 0, 0, 0);
  strip.show();
  delay(delayTime);
  
  neoPixel();    // 1 Gooien
  delay(showTime);
  strip.setPixelColor(0, 0, 0, 0);
  strip.show();
  delay(delayTime);
  
  digitalWrite(group1, HIGH);    // 2 Gooien
  delay(showTime);
  digitalWrite(group1, LOW);
  delay(delayTime);
  
  digitalWrite(group1, HIGH);    // 3 Gooien
  neoPixel();
  delay(showTime);
  digitalWrite(group1, LOW);
  strip.setPixelColor(0, 0, 0, 0);
  strip.show();
  delay(delayTime);
  
  digitalWrite(group1, HIGH);    // 4 Gooien
  digitalWrite(group2, HIGH);
  delay(showTime);
  digitalWrite(group1, LOW);
  digitalWrite(group2, LOW);
  delay(delayTime);
  
  digitalWrite(group1, HIGH);    // 5 Gooien
  digitalWrite(group2, HIGH);
  neoPixel();
  delay(showTime);
  digitalWrite(group1, LOW);
  digitalWrite(group2, LOW);
  strip.setPixelColor(0, 0, 0, 0);
  strip.show();
  delay(delayTime);
  
  digitalWrite(group1, HIGH);    // 6 Gooien
  digitalWrite(group2, HIGH);
  digitalWrite(group3, HIGH);
  delay(showTime);
  digitalWrite(group1, LOW);
  digitalWrite(group2, LOW);
  digitalWrite(group3, LOW);
  delay(delayTime);
}

void neoPixel() {
  if (result == 1 || result == 3 || result == 5 || result == 7) {
    strip.setPixelColor(0, colorRange);
    strip.show();
    delay(100);
  } else {
    strip.setPixelColor(0, 0, 0, 0);
    strip.show();
  } 
}
