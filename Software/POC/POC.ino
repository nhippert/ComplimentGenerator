#include <LiquidCrystal.h>
#include "pitches.h"
#include <Adafruit_Thermal.h>

/*ComplimentGenerator
   POC
   by Nicolas Hippert
   nhippert@gmail.com
   https://github.com/nhippert/ComplimentGenerator
*/

//Pins
#define backlightPin A3   //Screen backlight pin
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
#define TX_PIN 1          //Tx pin
#define RX_PIN 0          //Rx pin


//Global constants
const int tempo = 140;              //Tempo of the music played: change this to make the song slower or faster.
int thisIsLongEnough = 2000;        //Determines in milliseconds what is a long press on the button.
long timeBeforeSavingMode = 60000;  //Determines in milliseconds the time before entering energy saving mode.

//Variables
int buttonPushCounter = 0;   //Counter for the number of button presses
int buttonState = 0;         //Current state of the button
int lastButtonState = 0;     //Previous state of the button
long timeToFallAsleep = 0;
bool movementDetected = false;

//SETUP
LiquidCrystal lcd(rs, enable, d4, d5, d6, d7);

void setup() {
  //LCD
  lcd.begin(16, 2);  //Set up the LCD's number of columns and rows
  pinMode(backlightPin, OUTPUT);
  digitalWrite(backlightPin, HIGH);
  lcd.clear();       //Clear the screen

  //LOADING SCREEN
  lcd.print("Eh toi !!!");
  lcd.setCursor(0, 1);
  lcd.print("Tu sais quoi...");
  delay(50);

  //BUTTON
  //Initialize the pushbutton pin as an input
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
  //testLEDs();
  //displayCompliment("Tu es beau comme un jour ferie un lundi.");
  //displayDummyCompliment();
  //idleScreen();
  //playMusic();
  //buttonIsPressed();
  //buttonIsPressedLongEnough(thisIsLongEnough);
  //randomCompliment();
  //printCompliment();
  //testPrinter();
  //energySaver(1);


  //ROUTINE
  /*energySaver(1);
    idleScreen();
    if (buttonIsPressedLongEnough(3000)) {
    displayCompliment(randomCompliment());
    playMusic();
    idleScreen();
    }*/
  /*
    idleScreen();
    //Defines the times at wich the system will go asleep
    timeToFallAsleep = millis() + timeBeforeSavingMode;
    movementDetected = false;
    int previousValue = readUltrasonicSensor();
    int currentValue = 0;

    //Pushes the Compliment Generator asleep if there's no movement
    while (millis() < timeToFallAsleep) {
      currentValue = readUltrasonicSensor();
      if (currentValue > previousValue * 1.20 || currentValue < previousValue * 0.80) {
        timeToFallAsleep = millis() + timeBeforeSavingMode;
      }
      else if (buttonIsPressedLongEnough(thisIsLongEnough)) {
        routine();
      }
      /*Serial.print("Actual:");
        Serial.print(currentValue);
        Serial.print(" - Previous:");
        Serial.println(previousValue);*/
  /*  delay(100);
    previousValue = currentValue;
    }

    Serial.println("Compliment Generator going asleeeeeeeep... zzZzzzZzzz");
    lcd.clear();
    lcd.write("En veille...");
    delay(100);
    digitalWrite(backlightPin, LOW);

    //Reactivate if requires
    while (movementDetected == false) {
    currentValue = readUltrasonicSensor();
    if (currentValue > previousValue * 1.20 || currentValue < previousValue * 0.80) {
      movementDetected = true;
      Serial.println("Movement detected... Compliment Generator going full power agaaaaaaaain !!! Ready to conquer ze Werld !!!");
      digitalWrite(backlightPin, HIGH);
      idleScreen();
    }
    else if (buttonIsPressedLongEnough(thisIsLongEnough)) {
      routine();
      movementDetected = true;
    }
    delay(100);
    }*/
}

void routine() {
  digitalWrite(backlightPin, HIGH);
  displayCompliment(randomCompliment());
  playMusic();
  idleScreen();
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
  turnOnAllLeds();
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
    Serial.println("button pressed");
    turnOnAllLeds();
    while (digitalRead(buttonPin) != LOW) {
    }
    Serial.println("button released");
    turnOffAllLeds();
    delay(50);
    return true;
  }
}

bool buttonIsPressedLongEnough(int thatIsLongEnough) { //Listen for a long press of the main button.
  //thatIsLongEnough is the time required to press the button in milliseconds.
  digitalWrite(backlightPin, HIGH);
  buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH) {
    Serial.println("button is being pressed");
    while (buttonState != LOW) {
      digitalWrite(led1Pin, HIGH);
      delay(thatIsLongEnough / 3);
      if (digitalRead(buttonPin) == LOW)
        goto breakout;
      digitalWrite(led2Pin, HIGH);
      delay(thatIsLongEnough / 3);
      if (digitalRead(buttonPin) == LOW)
        goto breakout;
      digitalWrite(led3Pin, HIGH);
      delay(thatIsLongEnough / 3);
      if (digitalRead(buttonPin) == LOW)
        goto breakout;
      digitalWrite(led4Pin, HIGH);
      Serial.println("button was successfully pressed long enough time !!");
      delay(200);
      turnOffAllLeds();
      delay(200);
      turnOnAllLeds();
      delay(200);
      turnOffAllLeds();
      delay(200);
      turnOnAllLeds();
      delay(200);
      turnOffAllLeds();
      delay(200);
      return true;
    }
breakout:
    turnOffAllLeds();
    Serial.println("button released too early");
    delay(50);
    return false;
  }
  else {
    delay(50);
    return false;
  }
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

void displayCompliment(String selectedCompliment) {
  Serial.print("Selected compliment: ");
  Serial.println(selectedCompliment);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Eh bien...");
  lcd.setCursor(0, 1); //Move the cursor to row 2.
  char inputArray[selectedCompliment.length() + 1];
  selectedCompliment.toCharArray(inputArray, selectedCompliment.length() + 1); //Convert the string stored in "input" into a character array.
  for (int i = 0; i <= 16; i++) { //For the first 16 characters, simply print them to the LCD screen.
    lcd.write(inputArray[i]);
  }
  delay(1500); //Delay for 1.5 seconds so the user has time to read.
  for (int j = 17; j <= selectedCompliment.length() + 1; j++) { //Now we begin printing from character 17 onward...
    lcd.write(inputArray[j]); //Write the j-th character (for now it will be off-screen).
    lcd.scrollDisplayLeft(); //Scroll the text left one character-space.

    //This is where things get tricky, because both rows will be scrolled. But we want row 1 to remain stationary!
    lcd.setCursor(j - 16, 0); //Set the cursor to the first character space on the first row [visually].
    // cursor space (0,0) has been scrolled off-screen!
    lcd.print("Eh bien...."); //Re-print the row 1 message.
    lcd.setCursor(j + 1, 1); //Set the cursor one character space to the right of the last printed character on row 2.
    //  Which is visually one character space off-screen, in preparation for the next iteration.
    delay(350); //delay for 0.4 seconds so the user has time to read.
  }
  delay(1500);
}

void ArchivedDisplayCompliment(String selectedCompliment) { //Write a random compliment
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
  delay(1000);
}

void idleScreen() { //Display the default screen when the system is waiting for a user to press the button.
  digitalWrite(backlightPin, HIGH);
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

    /*NOTE_G3, 4, NOTE_G3, 8, NOTE_G3, -4, NOTE_G3, 8, NOTE_G3, 4,
      NOTE_G3, 4, NOTE_G3, 4, NOTE_G3, 8, NOTE_G3, 4,
      NOTE_C4, 4, NOTE_E4, 4, NOTE_G4, 4, NOTE_E4, 4,
      NOTE_C4, 4, NOTE_E4, 8, NOTE_G4, -4, NOTE_E4, 4,
      NOTE_A3, 4, NOTE_C4, 4, NOTE_E4, 4, NOTE_C4, 4,
      NOTE_A3, 4, NOTE_C4, 8, NOTE_E4, -4, NOTE_C4, 4,
      NOTE_G3, 4, NOTE_B3, 4, NOTE_D4, 4, NOTE_B3, 4,
      NOTE_G3, 4, NOTE_B3, 8, NOTE_D4, -4, NOTE_B3, 4,

      NOTE_G3, -1,*/

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

int readUltrasonicSensor() {
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(pingPin, LOW);
  return pulseIn(echoPin, HIGH);
}

boolean energySaver(long timeBeforeSavingMode) { //Allow theCompliment Generator to go into energy saving mode (v1 feature).

}

void printCompliment(String selectedCompliment) {//Print the compliment given in parameter (v2 feature).
}

void testPrinter() { //Test the printer

}
