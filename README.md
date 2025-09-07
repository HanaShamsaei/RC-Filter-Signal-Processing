# RC Filter – Signal Analysis and Frequency Response

This project demonstrates the use of **first-order RC filters** for analog signal processing and frequency response analysis.  
Signals are generated using **Arduino Uno** and analyzed in **MATLAB**, with comparisons to theoretical models of filtering and attenuation.

---

## Project Overview
- **Signal Generation**:  
  A sinusoidal signal is generated with Arduino PWM, smoothed by an RC filter, and visualized in MATLAB. Signal frequency can be adjusted using a potentiometer and confirmed via pushbutton input.

- **Composite Signal Filtering**:  
  A combined low- and high-frequency signal is generated and passed through RC filters with different cutoff frequencies. Experimental results are compared with theoretical responses to evaluate attenuation.

- **Frequency Response Measurement**:  
  The RC filter is tested across multiple frequencies, and attenuation is measured experimentally. MATLAB is used to create Bode plots and compare measured data with theoretical calculations.

---

## How to Run

### Arduino
1. Open the Arduino sketches in the `arduino/` folder.  
2. Connect the RC filter circuit as shown in the provided diagrams.  
3. Upload the appropriate sketch to the Arduino Uno.  
4. Open the Serial Monitor or Serial Plotter (baud rate 57600) to verify data transmission.  

### MATLAB
1. Open the MATLAB scripts in the `matlab/` folder.  
2. Run the scripts to:  
   - Plot generated signals against theoretical models.  
   - Analyze filtered signals and calculate attenuation.  
   - Generate Bode plots and compare experimental vs. theoretical responses.  



## Repository Structure
