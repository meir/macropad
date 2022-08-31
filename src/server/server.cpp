
#include "server.hpp"

#ifdef WEBSITE_ENABLE

#define GET (HTTPMethod)(1)
#define POST (HTTPMethod)(3)

WebServer server(80);

std::function<void(void)> index() {
    return []() {
        server.send(200, "text/html", "Hello World!");
    };
}

std::function<void(void)> get_keymap() {
    return []() {
        server.send(200, "text/plain", "");
    };
}

void start_server() {
    WiFi.begin(NETWORK_SSID, NETWORK_PASS);
    uint8_t retries = 0;
    while (WiFi.status() != WL_CONNECTED) {
        if(retries > 10) {
            return;
        }
        delay(500);
        retries++;
    }

    webserver_status = true;
    server.on("/", index());

    server.on("/api/keymap", GET, get_keymap());
    server.on("/api/layer_names", GET, get_layer_names());
    server.on("/api/layer_colors", GET, get_layer_colors());

    server.on("/api/keymap", POST, post_keymap());
    server.on("/api/layer_names", POST, post_layer_names());
    server.on("/api/layer_colors", POST, post_layer_colors());

    server.onNotFound(index());
    local_ip = WiFi.localIP().toString();
}
#endif