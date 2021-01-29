

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
const int rs = 12;
const int enable = 11;
const int d4 = 5;
const int d5 = 4;
const int d6 = 3;
const int d7 = 2;
const int buttonPin = 7;
const int buzzer = 8;
#define TX_PIN 1 // Arduino transmit  YELLOW WIRE  labeled RX on printer
#define RX_PIN 0 // Arduino receive   GREEN WIRE   labeled TX on printer

//Global constants
const int tempo = 140; // change this to make the song slower or faster

//Variables
int buttonPushCounter = 0;   // counter for the number of button presses
int buttonState = 0;         // current state of the button
int lastButtonState = 0;     // previous state of the button

//SETUP
LiquidCrystal lcd(rs, enable, d4, d5, d6, d7);
void setup() {
  //LCD
  lcd.begin(16, 2);  // set up the LCD's number of columns and rows
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

  //PRINTER
    printer.begin();  
}

void loop() {

  //TESTS
  displayCompliment(randomCompliment());
  //displayDummyCompliment();
  //idleScreen();
  //playMusic();
  //buttonIsPressedLongEnough(3);
  //randomCompliment();
  //printCompliment();
  delay(999999999999);


  //ROUTINE
  /*if (buttonIsPressedLongEnough(5)) {
    displayCompliment(randomCompliment());
    //playMusic();
    idleScreen();
    }*/
}

bool buttonIsPressedLongEnough(int thatIsLongEnough) { //Listen for a long press of the main button.
  //thatIsLongEnough is the time required to press the button in seconds.
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

String randomCompliment() { //Select a compliment (almost) randomly from a list
  //List of compliments
  String compliments[] = {
    "Tu fais du bien comme un kebab a 5h du mat",
    "Tu es beau comme un jour ferie un lundi",
    "Sans toi, je suis comme Jul sans vocodeur : rien",
  };

  //Random compliment selector
  int nbCompliments = sizeof(compliments) / 6;
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
    tone(buzzer, melody[thisNote], noteDuration * 0.9);

    // Wait for the specief duration before playing the next note.
    delay(noteDuration);

    // stop the waveform generation before the next note.
    noTone(buzzer);
  }

void printCompliment(){
  
}

}
