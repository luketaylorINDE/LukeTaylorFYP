const int sampleWindow = 50;
unsigned int sample;

int peakMin;
int peakMax;

void setup() {
  Serial.begin(9600);
}
void loop() {
  unsigned long startMillis = millis();
  unsigned int peakToPeak = 0;

  unsigned int signalMax = 0;
  unsigned int signalMin = 1024;

  while (millis() - startMillis < sampleWindow) {
    sample = analogRead(0);
    if (sample < 1024) {
      if (sample > signalMax) {
        signalMax = sample;
      }
      else if (sample < signalMin) {
        signalMin = sample;
      }
    }
  }
  peakToPeak = signalMax - signalMin;
  double volts = (peakToPeak * 5.0) / 1024;
  
  //Serial.println(volts);
  //Serial.println (peakToPeak);

 if (peakToPeak < 25) {
  Serial.println("normal");
 } else if (peakToPeak > 24 && peakToPeak < 60) {
  Serial.println("Shower Running");
 }

  
}


