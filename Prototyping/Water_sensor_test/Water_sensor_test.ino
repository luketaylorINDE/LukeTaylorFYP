int nTapIn = A0;
int nTapDigitalIn = 2;
int nTapVal;
boolean bIsTapOn = false;
String strTap;
float usage = 0;

void setup() {
Serial.begin(9600);
pinMode(2, INPUT);
}

void loop() {
nTapVal = analogRead(nTapIn);
bIsTapOn = ! (digitalRead (nTapDigitalIn));

if (bIsTapOn) {
  strTap = "Tap On";
  usage = usage + 0.25;
} else {
  strTap = "Tap Off";
}


  Serial.print("Is Tap Running?: ");
  Serial.print(strTap);
  Serial.print(" | Water Usage: ");
  Serial.print(usage);
  Serial.println(" Liters");

  delay(1000);

}
