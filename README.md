# ESP-AC_Power_Monitor

This code originally from an Arduino sketch has been converted using the SensESP tutorial found here https://signalk.org/SensESP/pages/tutorials/arduino_style/

The code was found in this video https://youtu.be/TITtBkoaQ_s?si=Sw5_bNB5xSPfIisY and calculates the amps drawn for an AC load. This uses an ESP32, a ADS1115 analog-to-digital converter and a 20amp ac clamp from YHDC which outputs 1v (ac) at 20amps.

This then connects to SignalK using the following path ac.current.amps

The code can be changed to support different clamp sensors by changing the factor value. Take care on the voltage output as the gain is set to four which is a maximum 1.024v on the ADS board.

Videos of my setup can be found on our YouTube channel - https://www.youtube.com/c/BoatingwiththeBaileys

Be careful when messing about with AC wiring!!
