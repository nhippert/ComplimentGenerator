#include <Array.h>

/*Compliment generator
   POC v1
   by Nicolas Hippert
   nhippert@gmail.com
*/

#include <LiquidCrystal.h>
#include "pitches.h"

//Constants
const int rs = 12;
const int enable = 11;
const int d4 = 5;
const int d5 = 4;
const int d6 = 3;
const int d7 = 2;
const int buttonPin = 7;
const int tempo = 140; // change this to make the song slower or faster
const int buzzer = 8; // change this to whichever pin you want to use

//Variables
int buttonPushCounter = 0;   // counter for the number of button presses
int buttonState = 0;         // current state of the button
int lastButtonState = 0;     // previous state of the button


//SETUP
LiquidCrystal lcd(rs, enable, d4, d5, d6, d7);
void setup() {

  //LCD
  // set up the LCD's number of columns and rows
  lcd.begin(16, 2);
  lcd.clear();

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

}

void loop() {

  //TESTS
  //displayCompliment();
  //idleScreen();
  //playMusic();
  //buttonIsPressedLongEnough();
  //delay(999999999999999);

  //ROUTINE
   if (buttonIsPressedLongEnough()) {
     displayCompliment();
     playMusic();
     idleScreen();
    }
}

bool buttonIsPressedLongEnough() {
  // read the pushbutton input pin
  buttonState = digitalRead(buttonPin);

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

void displayCompliment() {
  //List of compliments
  String compliments[] = {
    //"Tu fais du bien comme un kebab a 5h du mat",
    //"Tu es beau comme un jour ferie un lundi",
    "Sans toi, je suis comme Jul sans vocodeur : rien",
  };

  //Random compliment selector
  int nbCompliments = sizeof(compliments) / 6;
  int selectedCompliment = random(0, nbCompliments);

  //Preparation of the compliment

  //Monitor selected compliment
  Serial.print("Selected compliment: #");
  Serial.print(selectedCompliment);
  Serial.print(" - ");
  Serial.println(compliments[selectedCompliment]);

  String words[100];
  int previousIndexOf = 0;
  int k = 0;

  //Hashing the compliment into words
  //BUG : condition de fin pour avoir le dernier mot
  while (compliments[selectedCompliment].indexOf(' ', previousIndexOf) != -1) {
    /*Serial.print(k);
      Serial.print(" previousindexof: ");
      Serial.print(previousIndexOf);
      Serial.print(" compliments[selectedCompliment].indexOf(' ', previousIndexOf): ");
      Serial.print(compliments[selectedCompliment].indexOf(' ', previousIndexOf));
      Serial.print(" - ");*/

    words[k] = compliments[selectedCompliment].substring(previousIndexOf, compliments[selectedCompliment].indexOf(' ', previousIndexOf));
    previousIndexOf = compliments[selectedCompliment].indexOf(' ', previousIndexOf) + 1;
    //Serial.println(words[k]);
    k++;
  }

  //DEBUG Write the words array
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

  //DEBUG Write the Lines array
  /*m = 0;
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
  Serial.println(words[50].length());
  while (words[k].length() != 0) {

    if (words[k].length() + lineLength + 1  <= 17) {
      Lines[m][n] = k;
      n++;
      lineLength = lineLength + words[k].length() + 1;
    }
    else {
      m++;
      n = 0;
      lineLength = 0;
    }

    k++;
  }


  //DEBUG Write back the Lines array
  m = 0;
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
  }

  //Display of the compliment
  lcd.clear();


  //Removal of the compliment from the list



  //Dummy static compliment
  lcd.clear();
    lcd.print("Tu fait plaiz com");
    lcd.setCursor(0, 0);
    //lcd.print(compliments[selectedCompliment]);
    lcd.setCursor(0, 1);
    lcd.print("1kebab a 5du mat");
    delay(500);
}

void idleScreen() { //set the default screen when the system is waiting for a user to press the button.
  lcd.clear();
  lcd.print("Eh toi !!!");
  lcd.setCursor(0, 1);
  lcd.print("Tu sais quoi...");
}

void playMusic() {
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
    tone(buzzer, melody[thisNote], noteDuration * 0.9);

    // Wait for the specief duration before playing the next note.
    delay(noteDuration);

    // stop the waveform generation before the next note.
    noTone(buzzer);
  }

}
