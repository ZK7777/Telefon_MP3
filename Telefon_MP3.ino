//#include <Keypad.h>

// Klávesnice   XXXXXXXXXXXXXXXXXXX
const byte n_rows = 4;
const byte n_cols = 4;

char keys[n_rows][n_cols] = {
  { 'X', 'R', 'P', 'D' },
  { '3', '6', '9', '#' },
  { '2', '5', '8', '0' },
  { '1', '4', '7', '*' }
};
byte colPins[n_cols] = { 27, 14, 12, 13 };
byte rowPins[n_rows] = { 32, 33, 25, 26 };

//Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, n_rows, n_cols );

// Serial2
#define RXD2 16
#define TXD2 17

// Proměnné pro práci s DY-SV5W
const int in_busyPin = 15; // Pin pro příjem busy signálu z DY-SV5W
const int out_LED_sluchatko = 5; // signalizace zvednuteho sluchatka
const int in_sluchatko_zvednuto = 23; // prepinac zvednuteho sluchatka 

int busyPinstate;


void setup() {
//  Serial.begin(115200);
//  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);
//  Serial.println("ESP32DYSV5Wv7");

//  pinMode(27, INPUT_PULLUP);
//  pinMode(14, INPUT_PULLUP);
//  pinMode(12, INPUT_PULLUP);
//  pinMode(13, INPUT_PULLUP);
//
//  pinMode(32, INPUT_PULLUP);
//  pinMode(33, INPUT_PULLUP);
//  pinMode(25, INPUT_PULLUP);
//  pinMode(26, INPUT_PULLUP);



  pinMode(out_LED_sluchatko, OUTPUT);
  pinMode(in_sluchatko_zvednuto, INPUT_PULLUP);
  pinMode(in_busyPin, INPUT_PULLUP);

}

void loop() {

  digitalWrite(out_LED_sluchatko, !digitalRead(in_sluchatko_zvednuto));

//  // Obsluha klávesnice
//  char key = keypad.getKey();
//  
//  if (key){
//    Serial.println(key);
//  }

}
