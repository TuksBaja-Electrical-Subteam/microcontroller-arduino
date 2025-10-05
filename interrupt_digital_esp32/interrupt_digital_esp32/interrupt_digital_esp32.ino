#include <Arduino.h>

const int r_rad = 0.3;
const int MIC_PIN = 34;         //used other code for a basis, this is the hall pin
const int SAMPLE_RATE = 10000;   // sampling at 10kHz
const int N = 200;               

float circumference;
float wheelspeed;

hw_timer_t *timer = NULL;
volatile int sampleIndex = 0;
volatile bool bufferReady = false;


int16_t samples[N];
volatile bool wasHigh = false;

void IRAM_ATTR onTimer() {
  if (!bufferReady) {
    samples[sampleIndex++ ] = analogRead( MIC_PIN);

    if (sampleIndex >= N) {
      sampleIndex = 0;
      bufferReady = true;
    }
  }
}

void setup() {
  Serial.begin(115200);
  delay(1000);

  // Setup timer interrupt
  timer = timerBegin(0, 80, true);                    // choosing timer 0, prescaler 80 means 1 tick = 1 µs
  timerAttachInterrupt(timer, &onTimer, true);        // triggered = magnet passed
  timerAlarmWrite(timer, 100, true);                  
  timerAlarmEnable(timer);                            

  circumference = 2 * PI * r_rad;
}

void loop() {
  if (bufferReady) {
    bufferReady = false;

    int countHigh = 0;
    for (int i = 0; i < N; i++) {
      if (samples[i] > 1638) {       // 2V meaning (2/5 * 4095 ≈ 1638)
        countHigh++;
      }
    }

    Serial.print("High samples in block: ");
    Serial.println(countHigh);
  }
}
