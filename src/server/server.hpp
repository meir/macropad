
#include "../config/config.hpp"

#include <Arduino.h>
#include <String>

#include <Wifi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <HTTP_Method.h>

void start_server() __attribute__ ((weak));
String local_ip;
bool webserver_status = false;

std::function<void(void)> index() __attribute__ ((weak));

std::function<void(void)> get_keymap() __attribute__ ((weak));
std::function<void(void)> get_layer_names() __attribute__ ((weak));
std::function<void(void)> get_layer_colors() __attribute__ ((weak));

std::function<void(void)> post_keymap() __attribute__ ((weak));
std::function<void(void)> post_layer_names() __attribute__ ((weak));
std::function<void(void)> post_layer_colors() __attribute__ ((weak));
