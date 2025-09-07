/* Assignment 2
 * Amirhossein Ansari
 * Hana Shamsaei
*/

#include <TimerOne.h>  // Include TimerOne library to use hardware Timer1 for precise timing

#define PWMOUT 11          // Define pin 11 as the PWM output pin
#define ADC_CHANNEL A0     // Define analog pin A0 as the input to read the filtered signal

int DUTYCYCLE;             // Variable to store the current PWM duty cycle
int Sample;                // Variable to store the analog value read from the filter output
long TimeStamp;            // Variable to store the time in microseconds (divided for efficiency)
long Counter = 0;          // Counter used to calculate time progression in sine wave generation

// Define frequencies of low and high sine wave components
int Sine_Freq_Low = 6;     // Low-frequency sine wave (Hz)
int Sine_Freq_High = 84;   // High-frequency sine wave (Hz)

// Convert frequencies to angular velocity in rad/ms (TWO_PI = 2π)
float Sine_Coeff_Low = Sine_Freq_Low * TWO_PI / 1000.00;
float Sine_Coeff_High = Sine_Freq_High * TWO_PI / 1000.00;

// Scale amplitude (0.5V over 5V full scale, converted to 8-bit PWM range)
const float Amp = 0.5 / 5.00 * 255;

// Offset to center the signal around 2.5V in 8-bit PWM range
const float Offset = 2.5 / 5.00 * 255;

const int Max_Freq = 100;  // Maximum frequency placeholder (not used in this code)

void setup() {
  // Change Timer2 prescaler to set PWM frequency to ~31.37 kHz
  TCCR2B = TCCR2B & B11111000 | B00000001;

  pinMode(PWMOUT, OUTPUT);       // Set the PWM pin as output

  Serial.begin(57600);           // Initialize serial communication at 57600 baud rate

  Timer1.initialize(1000);       // Configure Timer1 to trigger every 1 millisecond (1000 microseconds)

  Timer1.attachInterrupt(PWM_DT); // Attach PWM_DT function to Timer1 interrupt
}

void loop() {
  TimeStamp = micros() / 100;         // Read current time and scale down for compact output
  Sample = analogRead(ADC_CHANNEL);   // Read the filtered analog signal from the RC filter

  // Send timestamp and voltage value (scaled to 0–5V range) to serial output
  Serial.print(TimeStamp);   
  Serial.print("\t");    
  Serial.println(Sample / 1023.00 * 5);
}

void PWM_DT() {
  // Generate two sine waves (low and high frequency), sum them, apply scaling and offset
  DUTYCYCLE = Amp * sin(Sine_Coeff_Low * Counter) + 
              Amp * sin(Sine_Coeff_High * Counter) + 
              Offset;

  analogWrite(PWMOUT, DUTYCYCLE); // Output the composite signal as PWM

  Counter++; // Increment counter to progress time in sine calculations
}
