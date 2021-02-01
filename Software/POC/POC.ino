/*ComplimentGenerator
   POC
   by Nicolas Hippert
   nhippert@gmail.com
   https://github.com/nhippert/ComplimentGenerator
*/

#include <LiquidCrystal.h>
#include "pitches.h"
#include <Adafruit_Thermal.h>

//Pins
const int rs = 12;        //Screen rs pin
const int enable = 11;    //Screen enable pin
const int d4 = 5;         //Screen d4 pin
const int d5 = 4;         //Screen d5 pin
const int d6 = 3;         //Screen d6 pin
const int d7 = 2;         //Screen d7 pin
const int buttonPin = A5; //Press button pin
const int buzzerPin = 8;  //Buzzer pin
const int pingPin = 13;   //Ultrasonic sensor ping pin
const int echoPin = A4;   //Ultrasonic sensor echo pin
const int led1Pin = 6;    //LED 1 pin
const int led2Pin = 7;    //LED 2 pin
const int led3Pin = 10;   //LED 2 pin
const int led4Pin = 9;    //LED 4 pin
#define TX_PIN 1          //Printer tx pin
#define RX_PIN 0          //Printer rx pin

//Global constants
const int tempo = 140;    //Tempo of the music played: change this to make the song slower or faster
const int thisIsLongEnough = 500; //Determines in ms what is a long press on the button

//Variables
int buttonPushCounter = 0;   //Counter for the number of button presses
int buttonState = 0;         //Current state of the button
int lastButtonState = 0;     //Previous state of the button

//SETUP
LiquidCrystal lcd(rs, enable, d4, d5, d6, d7);
void setup() {
  //LCD
  lcd.begin(16, 2);  //Set up the LCD's number of columns and rows
  lcd.clear();       //Clear the screen

  //LOADING SCREEN
  lcd.print("Eh toi !!!");
  lcd.setCursor(0, 1);
  lcd.print("Tu sais quoi...");
  delay(50);

  //BUTTON
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);

  //SERIAL
  Serial.begin(9600);
  Serial.println("Compliment generator starting up...");

  //PRINTER
  //Printer.begin();

  //ULTRASONIC SENSOR
  pinMode(pingPin, OUTPUT);
  pinMode(echoPin, INPUT);

  //LEDs
  pinMode(led1Pin, OUTPUT);
  pinMode(led2Pin, OUTPUT);
  pinMode(led3Pin, OUTPUT);
  pinMode(led4Pin, OUTPUT);
}

void loop() {



  //TESTS
  //testUltrasonicSensor();
  //displayCompliment(randomCompliment());
  //displayDummyCompliment();
  //idleScreen();
  //playMusic();
  //buttonIsPressed();
  //buttonIsPressedLongEnough(thisIsLongEnough);
  //randomCompliment();
  //printCompliment();
  testLEDs();
  //testPrinter();
  //energySaver();
  delay(999999999999);

  //ROUTINE
  /*if (buttonIsPressedLongEnough(5)) {
    displayCompliment(randomCompliment());
    //playMusic();
    idleScreen();
    }*/
}

void testLEDs() {//Test the LEDs mimicking the behaviour they should have when activated after a long press from the user.
  digitalWrite(led1Pin, HIGH);
  delay(500);
  digitalWrite(led2Pin, HIGH);
  delay(500);
  digitalWrite(led3Pin, HIGH);
  delay(500);
  digitalWrite(led4Pin, HIGH);
  delay(500);
  turnOffAllLeds();
  delay(500);
  turnOnAllLeds();
  delay(500);
  turnOffAllLeds();
  delay(500);
  turnOnAlleds();
  delay(500);
  turnOffAllLeds();
  delay(500);
}

void turnOnAllLeds() {
  digitalWrite(led1Pin, HIGH);
  digitalWrite(led2Pin, HIGH);
  digitalWrite(led3Pin, HIGH);
  digitalWrite(led4Pin, HIGH);
}

void turnOffAllLeds() {
  digitalWrite(led1Pin, LOW);
  digitalWrite(led2Pin, LOW);
  digitalWrite(led3Pin, LOW);
  digitalWrite(led4Pin, LOW);
}

void testUltrasonicSensor() {//Test the feedback from the Ultrasonic Sensor, printing the distance mesured in cm in the console.
  long duration, inches, cm;
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(pingPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  cm = microsecondsToCentimeters(duration);
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  delay(100);
}

long microsecondsToCentimeters(long microseconds) {
  return microseconds / 29 / 2;
}

bool buttonIsPressed() {//Listens for a short press on the button
  buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH) {
    Serial.println("Button has been pressed");
    return true;
  }
  else {
    return false;
  }
}

bool buttonIsPressedLongEnough(int thatIsLongEnough) { //Listen for a long press of the main button.
  //thatIsLongEnough is the time required to press the button in seconds.

  buttonState = digitalRead(buttonPin); // read the pushbutton input pin

  // compare the buttonState to its previous state
  if (buttonState != lastButtonState) {
    // if the state has changed, increment the counter
    if (buttonState == HIGH) {
      // if the current state is HIGH then the button went from off to on:
      buttonPushCounter++;
      Serial.print(buttonPushCounter);
      Serial.println(" compliments distribués.");
      return true;
    }
    // Delay a little bit to avoid bouncing
    delay(50);
  }
  // save the current state as the last state, for next time through the loop
  lastButtonState = buttonState;
  return false;
}

String randomCompliment() { //Select a compliment (almost) randomly from a list
  //List of compliments
  String compliments[] = {
    "Tu fais du bien comme un kebab a 5h du mat",
    "Tu es beau comme un jour ferie un lundi",
    "Sans toi, je suis comme Jul sans vocodeur : rien",
  };

  //Random compliment selector
  //Review by Olivier:
  int nbCompliments = sizeof(compliments) / 6;
  //int nbCompliments = sizeof(compliments) / sizeof(String);
  int numberSelected = random(0, nbCompliments);


  //Verbose
  Serial.print("Selected compliment: #");
  Serial.print(numberSelected);
  Serial.print(" - ");
  Serial.println(compliments[numberSelected]);

  return compliments[numberSelected];
}

void displayCompliment(String selectedCompliment) { //Write a random compliment
  String words[100];
  int previousIndexOf = 0;
  int k = 0;

  //Hashing the compliment into words
  while (selectedCompliment.indexOf(' ', previousIndexOf) != -1) {
    words[k] = selectedCompliment.substring(previousIndexOf, selectedCompliment.indexOf(' ', previousIndexOf));
    previousIndexOf = selectedCompliment.indexOf(' ', previousIndexOf) + 1;

    k++;
  }
  words[k] = selectedCompliment.substring(previousIndexOf, selectedCompliment.indexOf(' ', previousIndexOf));

  //Verbose: Write the words array
  /*k = 0;
    Serial.println("Word array:");
    while (k < 100) {
    Serial.print(k);
    Serial.print(" ");
    Serial.println(words[k]);
    k++;
    }*/

  //Setup the Lines array
  int Lines[10][10];
  int m = 0;
  int n = 0;
  while (m < 10) {
    while (n < 10) {
      Lines[m][n] = 0;
      n++;
    }
    m++;
    n = 0;
  }

  //Verbose: Write the Lines array
  /* m = 0;
     n = 0;
     while (m < 10) {
     Serial.print("Line ");
     Serial.print(m);
     Serial.print(" - ");
     while (n < 10) {
       Serial.print(Lines[m][n]);
       Serial.print(" ");
       n++;
     }
     Serial.println();
     m++;
     n = 0;
     }*/

  //Fills the Lines array with the words number
  m = 0;
  n = 0;
  k = 0;
  int lineLength = 0;
  while (words[k].length() != 0) {
    if (words[k].length() + lineLength + 1  <= 17) {
      Lines[m][n] = k;
      n++;
      lineLength = lineLength + words[k].length() + 1;
      k++;
    }
    else {
      m++;
      n = 0;
      lineLength = 0;
    }
  }


  //Verbose: Write back the Lines array
  /* m = 0;
    n = 0;
    while (m < 10) {
     Serial.print("Line ");
     Serial.print(m);
     Serial.print(" - ");
     while (n < 10) {
       Serial.print(Lines[m][n]);
       Serial.print(" ");
       n++;
     }
     Serial.println();
     m++;
     n = 0;
    }*/

  //Display of the compliment
  String string1 = "";
  String string2 = "";
  m = 0;
  n = 0;
  boolean nextIsEmpty = false;


  while (m < 10 && nextIsEmpty != true) {
    Serial.print("Line ");
    Serial.print(m);
    Serial.print(" - ");
    while (n < 10 && nextIsEmpty != true) {
      if (m % 2 == 0) {
        string1 += words[Lines[m][n]];
        string1 += " ";
      }
      else {
        string2 += words[Lines[m][n]];
        string2 += " ";
      }
      Serial.print(words[Lines[m][n]]);
      Serial.print(" ");
      if (Lines[m][n + 1] == 0) {
        nextIsEmpty = true;
      }
      n++;
    }
    Serial.println();
    m++;
    n = 0;
    if (Lines[m][n] != 0) {
      nextIsEmpty = false;
    }
  }

  Serial.print("string1: ");
  Serial.println(string1);
  Serial.print("string2: ");
  Serial.println(string2);

  m = 0;

  lcd.clear();
  while (m < 10) {
    lcd.print(string1);
    lcd.setCursor(0, 1);
    lcd.print(string2);
    delay(1000);
    m++;
  }

}

void displayDummyCompliment() { //For POC purposes only, display an unique static compliment
  //Dummy static compliment
  lcd.clear();
  lcd.print("T'fait plaiz com");
  lcd.setCursor(0, 1);
  lcd.print("1kebab a 5du mat");
}

void idleScreen() { //Display the default screen when the system is waiting for a user to press the button.
  lcd.clear();
  lcd.print("Eh toi !!!");
  lcd.setCursor(0, 1);
  lcd.print("Tu sais quoi...");
}

void playMusic() { //Play a gratifying music to cheer you up!
  // notes of the moledy followed by the duration.
  // a 4 means a quarter note, 8 an eighteenth , 16 sixteenth, so on
  // !!negative numbers are used to represent dotted notes,
  // so -4 means a dotted quarter note, that is, a quarter plus an eighteenth!!
  int melody[] = {

    REST, 1,
    REST, 1,
    NOTE_C4, 4, NOTE_E4, 4, NOTE_G4, 4, NOTE_E4, 4,
    NOTE_C4, 4, NOTE_E4, 8, NOTE_G4, -4, NOTE_E4, 4,
    NOTE_A3, 4, NOTE_C4, 4, NOTE_E4, 4, NOTE_C4, 4,
    NOTE_A3, 4, NOTE_C4, 8, NOTE_E4, -4, NOTE_C4, 4,
    NOTE_G3, 4, NOTE_B3, 4, NOTE_D4, 4, NOTE_B3, 4,
    NOTE_G3, 4, NOTE_B3, 8, NOTE_D4, -4, NOTE_B3, 4,

    NOTE_G3, 4, NOTE_G3, 8, NOTE_G3, -4, NOTE_G3, 8, NOTE_G3, 4,
    NOTE_G3, 4, NOTE_G3, 4, NOTE_G3, 8, NOTE_G3, 4,
    NOTE_C4, 4, NOTE_E4, 4, NOTE_G4, 4, NOTE_E4, 4,
    NOTE_C4, 4, NOTE_E4, 8, NOTE_G4, -4, NOTE_E4, 4,
    NOTE_A3, 4, NOTE_C4, 4, NOTE_E4, 4, NOTE_C4, 4,
    NOTE_A3, 4, NOTE_C4, 8, NOTE_E4, -4, NOTE_C4, 4,
    NOTE_G3, 4, NOTE_B3, 4, NOTE_D4, 4, NOTE_B3, 4,
    NOTE_G3, 4, NOTE_B3, 8, NOTE_D4, -4, NOTE_B3, 4,

    NOTE_G3, -1,

  };
  // sizeof gives the number of bytes, each int value is composed of two bytes (16 bits)
  // there are two values per note (pitch and duration), so for each note there are four bytes
  int notes = sizeof(melody) / sizeof(melody[0]) / 2;

  // this calculates the duration of a whole note in ms
  int wholenote = (60000 * 4) / tempo;

  int divider = 0, noteDuration = 0;

  // iterate over the notes of the melody.
  // Remember, the array is twice the number of notes (notes + durations)
  for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {

    // calculates the duration of each note
    divider = melody[thisNote + 1];
    if (divider > 0) {
      // regular note, just proceed
      noteDuration = (wholenote) / divider;
    } else if (divider < 0) {
      // dotted notes are represented with negative durations!!
      noteDuration = (wholenote) / abs(divider);
      noteDuration *= 1.5; // increases the duration in half for dotted notes
    }

    // we only play the note for 90% of the duration, leaving 10% as a pause
    tone(buzzerPin, melody[thisNote], noteDuration * 0.9);

    // Wait for the specief duration before playing the next note.
    delay(noteDuration);

    // stop the waveform generation before the next note.
    noTone(buzzerPin);
  }
}

boolean energySaver() { //Allow theCompliment Generator to go into energy saving mode (v1 feature).


}

void printCompliment(String selectedCompliment) {//Print the compliment given in parameter (v2 feature).
}

void testPringt() { //Test the printer

}
