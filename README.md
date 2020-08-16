# RC-Robot-Car
Code for an arduino controlled RC robot car.
On my IR remote:
Button 2 moves robot forward
Button 6 moves robot right
Button 8 moves robot backward
Button 4 moves robot left
^
(Since those buttons form a circle relative to each other in those directions)

Uses IRremote library and Adafruit Motor Shield library

**Note:
  timer1 (pin 9) must be used by the IRremote in order not to conflict with the Motor Shield.
