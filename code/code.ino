#define IP 7 // Input pin

#define WAIT 0 // Waiting for start condition
#define LISTEN 1 // Listening for first byte
#define STOP 2 // Message recorded, sending


unsigned long t; // Valeur de  temps

int res = 0; /// valeur de l'écart

///ascii tableau de caratère ascii caractère ASCII
byte currentByte = 0;
char currentBit = 0;
unsigned int sum;
int timeStore[8];

char finalBytes[20]; /// tabelau final pour les caractères
char finalCount = 0;

int i = 0;

int j= 0;
int k= 0;
int count =0;

char val = 0;
char prev=0;

char updt=0;

unsigned long lastUpdtTime=0;
unsigned long updtTime=0;

char state = WAIT;

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
      // Serial.print(timeStore[currentBit] < sum, BIN);
      // Serial.print(" ");
      // Serial.println(timeStore[currentBit]);
    }
    // Serial.println((char)currentByte);
    // Serial.println(" ");
    //delay(277);
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
Serial.begin(115200);
}

void loop() {

  val = digitalRead(IP); // Getting the state of input pin
  
  if(val && !prev){ // If IP state changed from 0 to 1
    prev = 1; // Update the current state (future PREVious state)
    t = micros(); // Take time measure
  }
  if(!val && prev) // If it switched back from 1 to 0
  {
    prev = 0; // Update current state
    res = micros() - t; // Store the "HIGH" duration
    updt=1; // Tell the rest of the program that a new info has arrived
    lastUpdtTime = millis();
  }

  if((0 != lastUpdtTime) && (WAIT != state)){
      updtTime = millis() - lastUpdtTime;
  }

  if (updtTime > 6) {
    state = STOP;
  }

  if (updt || (STOP == state)) { // Start processing

    if( (res > 280) && (res < 420) ){ // Start condition
      state = LISTEN;
      updt = 0;
    }

    if ((LISTEN == state) && (1 == updt)){
      if(timeToByte(res)){
        finalBytes[finalCount] = currentByte;
        finalCount++;
      }
    }

    if(STOP == state) {

      finalBytes[finalCount] = '\0';
      Serial.print("Message is : ");
      Serial.println(finalBytes);
      Serial.println("");
      finalCount = 0;

      updtTime = 0;
      state = WAIT;
    }

    updt = 0;
  }

}
