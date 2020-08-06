#ifndef BLUETOOTH_H
#define BLUETOOTH_H

#include "HardwareSerial.h"

extern HardwareSerial BT_mod;

void bluetooth_init();
void bluetooth_get_command();
void bluetooth_sync();

#endif