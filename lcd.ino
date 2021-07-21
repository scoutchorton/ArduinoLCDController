/**
 * Macros
 */

#define RS 53
#define RS_INSTRUCTION LOW
#define RS_DATA HIGH

#define RW 52
#define RW_READ HIGH
#define RW_WRITE LOW

#define ENABLE 51

#define DATA_PIN(PIN_NUM) 40 + PIN_NUM

//#define SW 50
#define SW A2
#define VRx A0
#define VRy A1

#define DISPLAY_STRING {'H', 'e', 'l', 'l', 'o', ',', ' ', 'w', 'o', 'r', 'l', 'd', '!'}


#define TOGGLE_ENABLE() \
    digitalWrite(ENABLE, HIGH); \
    delay(1); \
    digitalWrite(ENABLE, LOW);

/**
 * Defined types
 */

typedef unsigned char uint8;

/**
 * Code
 */

void writeToDataPins(uint8 data) {
    for(uint8 p_index = 0; p_index < 8; p_index++) {
      digitalWrite(DATA_PIN(p_index), data & (0b1 << p_index));
    }

    TOGGLE_ENABLE()
}

void setup() {
  char data[13] = DISPLAY_STRING;
  
  /**
   * Pin setup
   */
  
  pinMode(RS, OUTPUT);
  digitalWrite(RS, RS_INSTRUCTION);
  
  pinMode(RW, OUTPUT);
  digitalWrite(RW, RW_WRITE);

  pinMode(ENABLE, OUTPUT);
  digitalWrite(ENABLE, LOW);

  for(uint8 p_index = 0; p_index < 8; p_index++) 
    pinMode(DATA_PIN(p_index), OUTPUT);

  pinMode(SW, INPUT);
  pinMode(VRx, INPUT);
  pinMode(VRy, INPUT);

  /**
   * Serial data stuff
   */

  Serial.begin(9600);

  /**
   * Data writing
   */

  //Prepare for instructions
  digitalWrite(RS, RS_INSTRUCTION);
  digitalWrite(RW, RW_WRITE);
  
  //Initalize instruction set
  writeToDataPins(0b00111000);

  //Initalize display
  writeToDataPins(0b00001111);
  
  //Clear display and move to beginning
  writeToDataPins(0b00000001);

  //Write string data
  digitalWrite(RS, RS_DATA);
  for(uint8 index = 0; index < sizeof(data); index++) {
    delay(100);
    writeToDataPins(data[index]);
  }
}

void loop() {
  //Serial.print(digitalRead(SW) == HIGH ? "[X] " : "[ ] ");
  Serial.print(analogRead(SW) < 75 ? "[X] " : "[ ] ");
  //Serial.print(analogRead(SW));
  Serial.print(" : ");
  Serial.print(analogRead(VRx));
  Serial.print(", ");
  Serial.print(analogRead(VRy));
  Serial.print("\n");
}

/**
 * TODO:
 * Move cursor left/right based on VRx voltage
 *   Find how to move cursor
 *   Deadzone and repeating things
 * Increase/decrease character based on VRy voltage
 *   Find how to read character
 *   Increase ASCII value (`man ascii`)
 *   Actually write data
 * Switch reading
 *   Similar to moving cursor (turn that into a function)
 *   
 * Future:
 * Make a full on text editor
 * GVAGBASIC????
 */
