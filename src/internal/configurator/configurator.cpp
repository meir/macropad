
#include "configurator.hpp"

Preferences preferences;
WebServer server(80);

bool wifi_connected = false;

void configurator_init() {
    WiFi.mode(WIFI_STA);
    WiFi.begin(NETWORK_SSID, NETWORK_PASS);

    uint8_t retries = 0;

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        retries++;
        if (retries > 10) {
            // Just continue and start up the keypad, disable the webserver
            return;
        }
    }

    wifi_connected = true;

    preferences.begin("config", false);
}

void configurator_begin() {
    if(!wifi_connected) return;
    server.on("/", HTTP_GET, index());
    server.on("/preferences", HTTP_GET, get_preferences());
    server.on("/preferences", HTTP_POST, post_preferences());
    server.onNotFound(index());
    server.begin();
}

String get_ip() {
    if(!wifi_connected) return "not connected";
    return WiFi.localIP().toString();
}

WebServer::THandlerFunction index() {
    return []() {
        server.send(200, "text/html", "Hello World!");
    };
}

WebServer::THandlerFunction get_preferences() {
    return []() {

    };
}

WebServer::THandlerFunction post_preferences() {
    return []() {
        
    };
}

KEYMAP get_keymap_preferences() {
    return {};
}

LAYER_NAMES get_layer_name_preferences() {
    return {};
}

LAYER_COLORS get_layer_color_preferences() {
    return {};
}
