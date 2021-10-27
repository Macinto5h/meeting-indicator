//-----
// DEFINITIONS
//-----

// Row pin definitions
#define ROW_0_PIN 2
#define ROW_1_PIN 3
#define ROW_2_PIN 4
#define ROW_3_PIN 5
#define ROW_4_PIN 6
#define ROW_5_PIN 7
#define ROW_6_PIN 8
#define ROW_7_PIN 9

// Col pin definitions
#define COL_0_PIN 10
#define COL_1_PIN 11
#define COL_2_PIN 12
#define COL_3_PIN 13
#define COL_4_PIN A0
#define COL_5_PIN A1
#define COL_6_PIN A2
#define COL_7_PIN A3

// Sets the maximum length the message can be
#define MSG_MAX_LEN 48

//-----
// CONSTANTS
//-----

// Array used to easily access a row
const byte rows[] = {
  ROW_0_PIN,
  ROW_1_PIN,
  ROW_2_PIN,
  ROW_3_PIN,
  ROW_4_PIN,
  ROW_5_PIN,
  ROW_6_PIN,
  ROW_7_PIN
};

// Array used to easily access a column
const byte cols[] = {
  COL_0_PIN,
  COL_1_PIN,
  COL_2_PIN,
  COL_3_PIN,
  COL_4_PIN,
  COL_5_PIN,
  COL_6_PIN,
  COL_7_PIN
};

// Msg is a 2d array of 1 and 0 where 1 represents an LED to be in the on state. Spells out the word "BUSY"
const int msg[8][MSG_MAX_LEN] = {
  {0,0,0,0,0,0,0,0, 0,1,1,1,1,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0, 0,1,0,0,1,0,0,0, 0,1,0,0,0,0,1,0, 0,0,1,1,1,1,0,0, 0,1,0,0,0,1,0,0, 0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0, 0,1,0,0,1,0,0,0, 0,1,0,0,0,0,1,0, 0,0,1,0,0,0,0,0, 0,0,1,0,1,0,0,0, 0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0, 0,1,1,1,0,0,0,0, 0,1,0,0,0,0,1,0, 0,0,1,1,1,1,0,0, 0,0,0,1,0,0,0,0, 0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0, 0,1,0,0,1,0,0,0, 0,1,0,0,0,0,1,0, 0,0,0,0,0,1,0,0, 0,0,0,1,0,0,0,0, 0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0, 0,1,0,0,0,1,0,0, 0,0,1,0,0,1,0,0, 0,0,0,0,0,1,0,0, 0,0,0,1,0,0,0,0, 0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0, 0,1,0,0,0,1,0,0, 0,0,0,1,1,0,0,0, 0,0,1,1,1,1,0,0, 0,0,0,1,0,0,0,0, 0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0, 0,1,1,1,1,1,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0}
};

//-----
// VARIABLES
//-----

// Sets the position where in the message where a write to the LEDs should occur
int msgPos = 0;

//-----
// FUNCTIONS
//-----

void setup() {
  
  // Set row pins to OUTPUT and by default should be set to HIGH voltage
  for (int i = 0; i < 8; i++) {
    pinMode(rows[i], OUTPUT);
    digitalWrite(rows[i], HIGH);
  }
  
  // Set col pins to OUTPUT and by default should be set to LOW voltage
  for (int j = 0; j < 8; j++) {
    pinMode(cols[j], OUTPUT);
    digitalWrite(cols[j], LOW); 
  }
}

void loop() {
  
  // Paints same image to matrix 3 times to avoid flickering
  for (int x = 0; x < 5; x++) {
    
    // Paint image row by row
    for (int i = 0; i < 8; i++) {
      
      // Set all but the active row to HIGH
      for (int k = 0; k < 8; k++) {
        digitalWrite(rows[k], k != i);
      }
      
      // Write column values for the active row
      for (int j = 0; j < 8; j++) {
        digitalWrite(cols[j], msg[i][j + msgPos]);
      }
      
      // Slow down frame paint and scroll speed with delay
      delay(2);
    }
  }
  
  // Increment position or move back to 0 if end is reached
  msgPos = (msgPos == MSG_MAX_LEN - 8) ? 0 : (msgPos + 1);
}
