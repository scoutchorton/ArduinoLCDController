/**
 * Macros
 */

#define VO 53 //
#define VO_INSTRUCTION LOW
#define VO_DATA HIGH

#define RW 52
#define RW_READ HIGH
#define RW_WRITE LOW

#define ENABLE 51

#define DATA_PIN(PIN_NUM) 30 + PIN_NUM

#define DISPLAY_STRING "Hello, world!"

typedef unsigned char uint8;

void writeToDataPins(uint8 data) {
    for(uint8 p_index = 0; p_index < 8; p_index++) {
      digitalWrite(DATA_PIN(p_index), data & (0b1 << p_index));
    }
    digitalWrite(ENABLE, HIGH);
    delay(1);
    digitalWrite(ENABLE, LOW);
}

void setup() {
  pinMode(VO, OUTPUT);
  digitalWrite(VO, VO_INSTRUCTION);
  
  pinMode(RW, OUTPUT);
  digitalWrite(RW, RW_WRITE);

  pinMode(ENABLE, OUTPUT);
  digitalWrite(ENABLE, LOW);

  for(uint8 p_index = 0; p_index < 8; p_index++) 
    pinMode(DATA_PIN(p_index), OUTPUT);
}

void loop() {
  //Move to beginning
  digitalWrite(VO, VO_INSTRUCTION);
  writeToDataPins(0b00000001);

  /*
  //Write string data
  digitalWrite(VO, VO_DATA);
  for(uint8 index = 0; index < sizeof(DISPLAY_STRING); index++) {
    writeToDataPins(DISPLAY_STRING[index]);
  }
  */
}
