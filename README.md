# ArduinoLedStrip
Arduino PCB to control LED strip RGB, addressable or not, with 1 IR remote, 1 pot and 2 push buttons.

**Kicad information**
This project is made using KiCad Version: 4.0.7-e2-6376~58~ubuntu14.04.1.

**Arduino information**
You need the library "RobotIRremote" in your libraries folder. I also modified "TDK2" to "12" in my arduino-1.6.9/libraries/RobotIRremote/src/IRremoteTools.cpp file.

**Component list**
The Arduino used is an ATmega328P Nano V3.
The DC 12V connector is a 5.5mm×2.1mm DC Power Supply Female Jack Socket.
The 6 transistors used are IRFZ44N Transistor N-Channel.
The polarized power capacitor is a 10µF, with a diameter egal to 8.0mm, and a pitch of 3.5mm.
SW1 and SW2 are Push Button DIP P4.
The potentiometer is a PTV09A from Bourns.
The IR receiver is a TSOP4838.
All pin header used have a pitch of 2.54mm.
All resistors are 0603 handsoldering (1kΩ).
