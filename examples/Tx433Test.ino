/*
  Example of using the Tx433 lib to control Home Automation power outlet sockets
*/

#include <tx433.h>

// Replace these string with appropriate code/pattern for your devices
String tx_proove = "1111111111111111111111111111111111111111111111111111";
String tx_anslut = "0000000000000000000000000000000000000000000000000000";

String ch_proove="0101";
String ch_anslut="0101";

Tx433 Anslut(11, tx_anslut, ch_anslut);
Tx433 Proove(11, tx_proove, ch_proove);


void setup() {
}

void loop() {
  Proove.Device_On(2);
  delay(700);
  Proove.Device_Off(2);
  delay(150);
  Anslut.Device_On(0);
  delay(700);
  Anslut.Device_Off(0);
  delay(150);
}
