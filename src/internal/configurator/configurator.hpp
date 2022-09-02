
#pragma once

#include <Arduino.h>

#include "../../config/config.hpp"
#include <WiFi.h>
#include <WiFiClient.h>
#include <ESPmDNS.h>
#include <WebServer.h>
#include <Preferences.h>

void configurator_init();
void configurator_begin();

String get_ip();

WebServer::THandlerFunction index();

WebServer::THandlerFunction get_preferences();
WebServer::THandlerFunction post_preferences();

KEYMAP get_keymap_preferences();
LAYER_NAMES get_layer_name_preferences();
LAYER_COLORS get_layer_color_preferences();
