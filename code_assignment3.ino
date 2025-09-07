/* Assignemnt 2
 * Amirhossein Ansari
 * Hana Shamsaei
*/

#include <TimerOne.h>

#define PWMOUT 11
#define ADC_CHANNEL A0

int DUTYCYCLE;
int Sample;
long TimeStamp;
long Counter = 0;
int Sine_Freq = 15;
float Sine_Coeff = Sine_Freq*TWO_PI/1000.00;
const float Amp = 2.5/5.00*255;
const float Offset = 2.5/5.00*255;
const int Max_Freq = 100;


void setup() {
  TCCR2B = TCCR2B & B11111000 | B00000001;  // Sets Timer2 PWM frequency to 31 KHz
  pinMode(PWMOUT, OUTPUT);
  Serial.begin(57600);
  Timer1.initialize(1000); // 1000 us == 1 ms
  Timer1.attachInterrupt(PWM_DT);
}

void loop() {
  TimeStamp = micros()/100;
  Sample = analogRead(ADC_CHANNEL);

  Serial.print(TimeStamp);   Serial.print("\t");    Serial.println(Sample/1023.00*5);
}

void PWM_DT(){
  DUTYCYCLE = Amp*sin(Sine_Coeff*Counter) + Offset;
  analogWrite(PWMOUT, DUTYCYCLE);
  Counter++;
}