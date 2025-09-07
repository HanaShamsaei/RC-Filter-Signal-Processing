#include <TimerOne.h> // Include the TimerOne library to use Timer1 interrupts

#define Push_Button 2      // Define pushbutton pin
#define PWMOUT 11          // Define PWM output pin
#define ADC_CHANNEL A0     // Define analog input pin for reading filtered output

int DUTYCYCLE;             // Variable to store PWM duty cycle
int Sample;                // Variable to store analog read sample
long TimeStamp;            // Variable to store timestamp in microseconds
long Counter = 0;          // Counter used to generate sine wave
int Sine_Freq;             // Current frequency of the sine wave
float Sine_Coeff;          // Coefficient used in sine generation formula
const float Amp = 2.5/5*255;     // Amplitude of sine wave scaled to 8-bit PWM
const float Offset = 2.5/5*255;  // Offset to center sine wave at mid-voltage
const int Max_Freq = 100;        // Maximum allowed frequency

void setup() {
  // Set Timer2 PWM frequency to ~31.37 kHz (faster and less audible)
  TCCR2B = TCCR2B & B11111000 | B00000001;

  // Set PWM output pin as OUTPUT
  pinMode(PWMOUT, OUTPUT);

  // Enable internal pull-up resistor for pushbutton pin
  pinMode(Push_Button, INPUT_PULLUP);

  // Begin serial communication at 57600 baud rate
  Serial.begin(57600);

  // Initialize Timer1 to call an interrupt every 1 millisecond
  Timer1.initialize(1000);

  // Attach the interrupt function PWM_DT to Timer1
  Timer1.attachInterrupt(PWM_DT);

  // Attach an interrupt to the pushbutton pin that triggers on rising edge
  attachInterrupt(digitalPinToInterrupt(Push_Button), Change_Freq, RISING);

  // Read initial frequency value from potentiometer connected to A1
  Sine_Freq = analogRead(A1) / 1023.00 * Max_Freq;

  // Calculate sine wave coefficient based on frequency
  Sine_Coeff = Sine_Freq * TWO_PI / 1000.00;
}

void loop() {
  // Get current time in microseconds
  TimeStamp = micros();

  // Read filtered analog output from the RC circuit
  Sample = analogRead(ADC_CHANNEL);

  // Send time, voltage (in volts), and frequency to serial monitor for MATLAB
  Serial.print(TimeStamp / 100);         // Divide to reduce data size
  Serial.print("\t");
  Serial.print(Sample / 1023.00 * 5);    // Convert ADC value to voltage
  Serial.print("\t");
  Serial.println(Sine_Freq);             // Print current frequency
}

// Interrupt function that updates the frequency when button is pressed
void Change_Freq() {
  // Read potentiometer value and convert to frequency
  Sine_Freq = analogRead(A1) / 1023.00 * Max_Freq;

  // Update sine coefficient for the new frequency
  Sine_Coeff = Sine_Freq * TWO_PI / 1000.00;
}

// Timer1 interrupt function to update PWM output
void PWM_DT() {
  // Generate sine wave and scale it to 8-bit PWM range (0–255)
  DUTYCYCLE = Amp * sin(Sine_Coeff * Counter) + Offset;

  // Output the calculated PWM value
  analogWrite(PWMOUT, DUTYCYCLE);

  // Move to next sample point
  Counter++;
}
