Life clock

Arduino, 2 led matrices, a chronodot, all coming together to make an interesting looking clock.

Now working although not particularly interesting.

Setup:

- The Chronodot and HT1632 libraries must be manually added to the Arduino IDE to make them work.
- The J5 connection on the back of the matrices must be jumped
- Chronodot communicates throught the wire library
  - SDA goes to A4
  - SCL goes to A5
- The matrix pins are defined at the top of life_clock.ino

To do: 
- Solder it up and put it into a project box
- Diagrams and pictures for the setup
- Figure out how to get a more lasting game of life setup when the numbers display.
- Right now, the time is only settable by recompiling the code
  - Consider adding a rotary encoder to change the time
- Dimmer switch
