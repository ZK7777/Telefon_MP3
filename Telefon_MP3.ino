//#include <Keypad.h>

// Klávesnice   XXXXXXXXXXXXXXXXXXX
const byte n_rows = 4;
const byte n_cols = 4;
const int ledPin = 2; // Číslo LED pinu

char keys[n_rows][n_cols] = {
  { 'X', 'R', 'P', 'D' },
  { '3', '6', '9', '#' },
  { '2', '5', '8', '0' },
  { '1', '4', '7', '*' }
};
byte colPins[n_rows] = { 27, 14, 12, 13 };
byte rowPins[n_cols] = { 32, 33, 25, 26 };

//Keypad myKeypad = Keypad(makeKeymap(keys), rowPins, colPins, n_rows, n_cols);
int ledState = LOW;  // ledState použitý pro nastavení LED

// Serial2
#define RXD2 16
#define TXD2 17
// Proměnné pro práci s DY-SV5W
const int busyPin = 15; // Pin pro příjem busy signálu z DY-SV5W
byte commandLength;
byte command[6];
int16_t checkSum = 0;

// Proměnné pro demo sketch
int trackNum = 1;
int playStatus; // 0 - přehrává, 1 - zastaveno, 2 - čekání na spuštění další skladby
unsigned long lastCheckTime;
unsigned long previousMillis;
unsigned long currentMillis;
unsigned long interval = 1000;
unsigned long loop_counter;
bool blik;

int busyPinstate;

// Funkce pro přehrávání skladby
void playTrack(int soundTrack) {
  Serial.print("soundTrack: ");
  Serial.println(soundTrack);
  command[0] = 0xAA; // První byte říká, že jde o příkaz
  command[1] = 0x07;
  command[2] = 0x02;
  command[3] = (soundTrack >> 8) & 0xFF; // Snh...track HIGH bit
  command[4] = soundTrack & 0xFF; // SNL...track LOW bit
  checkSum = 0;
  for (int q = 0; q < 5; q++) {
    checkSum += command[q];
  }
  command[5] = (checkSum & 0xFF); // SM check bit...low bit of the sum of all previous values
  commandLength = 6;
  sendCommand();
}

void play() {
  command[0] = 0xAA; // První byte říká, že jde o příkaz
  command[1] = 0x02;
  command[2] = 0x00;
  command[3] = 0xAC;
  commandLength = 4;
  sendCommand();
}

// Volba náhodného režimu
void randomMode() {
  command[0] = 0xAA; // První byte říká, že jde o příkaz
  command[1] = 0x18;
  command[2] = 0x01;
  command[3] = 0x03; // Náhodný režim
  checkSum = 0;
  for (int q = 0; q < 4; q++) {
    checkSum += command[q];
  }
  command[4] = (checkSum & 0xFF); // SM check bit...low bit of the sum of all previous values
  commandLength = 5;
  sendCommand();

  // play() needs to be selected if you want the random tracks to start playing instantly
  play();
}

// Nastavení hlasitosti přehrávání...0 - 30
void playbackVolume(int vol) {
  if (vol > 30) { // Kontrola v mezích
    vol = 30;
  }
  command[0] = 0xAA; // První byte říká, že jde o příkaz
  command[1] = 0x13;
  command[2] = 0x01;
  command[3] = vol; // Hlasitost
  checkSum = 0;
  for (int q = 0; q < 4; q++) {
    checkSum += command[q];
  }
  command[4] = (checkSum & 0xFF); // SM check bit...low bit of the sum of all previous values
  commandLength = 5;
  sendCommand();
}

// Odeslání příkazu
void sendCommand() {
  for (int q = 0; q < commandLength; q++) {
    Serial2.write(command[q]);
    Serial.print(" ");
    Serial.print(command[q], HEX);
  }
  Serial.println(" End");
}

void setup() {
  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);
  Serial.println("ESP32DYSV5Wv7");

  pinMode(27, INPUT_PULLUP);
  pinMode(14, INPUT_PULLUP);
  pinMode(12, INPUT_PULLUP);
  pinMode(13, INPUT_PULLUP);

  pinMode(32, INPUT_PULLUP);
  pinMode(33, INPUT_PULLUP);
  pinMode(25, INPUT_PULLUP);
  pinMode(26, INPUT_PULLUP);

  pinMode(ledPin, OUTPUT);
  pinMode(busyPin, INPUT); // Pin pro čtení z DY-SV5W busyPin


  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(34, INPUT_PULLUP);


  playbackVolume(20); // Nastavení hlasitosti na úroveň 20
  playTrack(0);
}

void loop() {
  digitalWrite(5, digitalRead(34));
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);                       // wait for a second

  //digitalWrite(5, true);
  // Obsluha klávesnice
  // char myKey = myKeypad.getKey();

  // if (myKey != NULL) {
  //   if (myKey == '1') playTrack(1);
  //   else if (myKey == '2') playTrack(2);
  //   else if (myKey == '3') playTrack(3);
  //   else if (myKey == '4') playTrack(4);
  //   else if (myKey == '5') playTrack(5);
  //   else if (myKey == '6') playTrack(6);
  //   else if (myKey == '7') playTrack(7);
  //   else if (myKey == '8') playTrack(8);
  //   else if (myKey == '9') playTrack(9);
  //   else if (myKey == '0') playTrack(10);
  //   else playTrack(0);
  // }

  // // Kontrola stavu busyPin
  // busyPinstate = digitalRead(busyPin);
  // if (busyPinstate > 0) { // Nic nehraje
  //   if (playStatus < 1) {
  //     playStatus = 1;
  //     lastCheckTime = currentMillis; // Připravení systému na 2s zpoždění
  //   }
  // }
}
