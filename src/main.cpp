#include "USB.h"
#include "USBHIDConsumerControl.h"
#include <Arduino.h>

#include "config.h"
#include "manager.h"

Manager manager();

void loop() {
  manager.run();
}