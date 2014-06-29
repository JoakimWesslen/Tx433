/*
  Joakim Wesslen
  2012-06-26

  A library to handle the TX433 Proove/Anslut device.
  Version 1.0

  http://tech.jolowe.se/home-automation-rf-protocols/  
*/
#include "tx433.h"

extern "C" {
  // AVR LibC Includes
  #include <inttypes.h>
  #include <avr/interrupt.h>
#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
  #include <pins_arduino.h>
#endif
}

#define RETRANSMIT  5

const int Tx433::pulse_high = 250;
const int Tx433::pulse_one_low = 250;
const int Tx433::pulse_zero_low = 1250;
const int Tx433::pulse_sync_low = 2500;
const int Tx433::pulse_pause_low = 10000;

String Tx433::GrpOn="01";
String Tx433::GrpOff="10";
String Tx433::On="01";
String Tx433::Off="10";
String Tx433::Unit[] = {
		"0101",
		"0110",
		"1001",
		"0101"
	};

/* Public */

Tx433::Tx433(int digitalpin, String transmittercode, String channelcode)
{
	txpin = digitalpin;
	pinMode(txpin, OUTPUT);

	TxCode = transmittercode;
	ChCode = channelcode;
}

void Tx433::Device_On(int dev)
{
	if (dev >= 3) {
		sendPackets(GrpOn, Unit[3], On);
	} else
		sendPackets(GrpOff, Unit[dev], On);
}	  

void Tx433::Device_Off(int dev)
{
	if (dev >= 3) {
		sendPackets(GrpOn, Unit[3], Off);
	} else
		sendPackets(GrpOff, Unit[dev], Off);
}	  

int Tx433::Get_txpin(void)
{
	return txpin;
}

String Tx433::Get_TxCode(void)
{
		return TxCode;
}	  

String Tx433::Get_ChCode(void)
{
		return ChCode;
}	  

/* Private */

// Protocol layer
void Tx433::sendCode(String str, int len) {
  int i = 0;
  while (i <= len) {
    if (str.charAt(i) == '0') {
      sendZero();
    }
    if (str.charAt(i)== '1') {
      sendOne();
    }
    i++;
  }
}

void Tx433::sendPackets(String grp, String dev, String onoff) {
  for (int i = 0; i < RETRANSMIT; i++) {
	  sendSync();
	  sendCode(TxCode, TxCode.length());
	  sendCode(grp, grp.length());
	  sendCode(onoff, onoff.length());
	  sendCode(ChCode, ChCode.length());
	  sendCode(dev, dev.length());
	  sendPause();
  }
}

// Physical layer
void Tx433::sendZero() {
  digitalWrite(txpin, HIGH);
  delayMicroseconds(pulse_high);
  digitalWrite(txpin, LOW);
  delayMicroseconds(pulse_zero_low);
}

void Tx433::sendOne() {
  digitalWrite(txpin, HIGH);
  delayMicroseconds(pulse_high);
  digitalWrite(txpin, LOW);
  delayMicroseconds(pulse_one_low);
}

void Tx433::sendSync() {
  digitalWrite(txpin, HIGH);
  delayMicroseconds(pulse_high);
  digitalWrite(txpin, LOW);
  delayMicroseconds(pulse_sync_low);
}

void Tx433::sendPause() {
  digitalWrite(txpin, HIGH);
  delayMicroseconds(pulse_high);
  digitalWrite(txpin, LOW);
  delayMicroseconds(pulse_pause_low);
}
