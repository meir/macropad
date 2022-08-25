
#include <Arduino.h>
#include "manager/manager.hpp"
#include "config/config.hpp"

Manager manager;

void setup() {

}

void loop() {
  manager.run();
}