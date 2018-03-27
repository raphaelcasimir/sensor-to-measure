#define IP 7 // Input pin

#define WAIT 0 // Waiting for start condition
#define LISTEN 1 // Listening for first byte
#define NEW_BYTE 2 // Next byte contition heard
#define STOP 3 // Message recorded, sending


unsigned long t; // Valeur de  temps

int res = 0; /// valeur de l'écart

///ascii tableau de caratère ascii caractère ASCII
byte currentByte = 0;
char currentBit = 0;
unsigned int sum;
int timeStore[8];

char finalBytes[9]; /// tabelau final pour les caractères
char finalCount = 0;

int i = 0;

int j= 0;
int k= 0;
int count =0;

char val = 0;
char prev=0;

char updt=0;
unsigned long lastUpdtTime=0;
unsigned int updtTime=0;

char state = WAIT;

unsigned int store[56];

bool timeToByte(unsigned int time) {

  timeStore[currentBit] = time; // Storing current time for translation
  currentBit++;

  sum += time;

  if(currentBit == 8) {
    
    currentByte = 0;
    sum = sum/8;

    for(currentBit = 0; currentBit < 8; currentBit++) {
      // Remark : no ASCII character is all 0 or all 1
      if(timeStore[currentBit] < sum) { // HIGH
        currentByte = currentByte << 1;
        currentByte = currentByte | B00000001;
      }
      else { // LOW
        currentByte = currentByte << 1;
      }
      Serial.print(timeStore[currentBit] < sum, BIN);
      Serial.print(" ");
      Serial.println(timeStore[currentBit]);
    }
    Serial.println((char)currentByte);
    Serial.println(" ");
    delay(277);
    currentBit = 0;
    sum = 0;
    return 1;
  }
  else
    return 0;
}

void setup() {
// Input mode for the pin which will receive the signal Inpin
pinMode(IP, INPUT);
Serial.begin(9600);
}

void loop() {

  val = digitalRead(IP);
  
  if(val && !prev){
    prev = 1;
    t = micros();
  }
  if(!val && prev)
  {
    prev = 0;
    res = micros() - t;
    updt=1;
    lastUpdtTime = micros();
  }

  if (updt == 1) {
    if( (res > 300) && (res < 400) ){
      state = LISTEN;
      updt = 0;
    }

    // if( (updtTime > 400) && (updtTime < 600) ){
    //   state = NEW_BYTE;
    //   updt = 0;
    // }

    // if( (updtTime > 15000) && (updtTime < 25000) ){
    //   state = STOP;
    //   updt = 0;
    // }

    if (((state == LISTEN) || (state = NEW_BYTE) ) && (updt == 1)){
      if(timeToByte(res)){
        finalBytes[finalCount] = currentByte;
        finalCount++;
      }
    }

    if((state == STOP) && (finalCount == 8)) {
      finalBytes[9] = '\0';
      for(currentBit = 0; currentBit<9; currentBit++)
        Serial.println(finalBytes[currentBit], HEX);
      finalCount = 0;
    }

    updt = 0;
    updtTime = lastUpdtTime - micros();
  }

  
}
