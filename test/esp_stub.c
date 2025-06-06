#include "esp_stub.h"
#include <stdlib.h>

int last_gpio_level = -1;
esp_timer_handle_t last_timer_started = 0;
int64_t last_timer_duration = 0;
int stop_call_count = 0;

esp_err_t esp_timer_create(const esp_timer_create_args_t* args, esp_timer_handle_t* out) {
    static int next = 1;
    *out = next++;
    return ESP_OK;
}

esp_err_t esp_timer_start_once(esp_timer_handle_t timer, int64_t us) {
    last_timer_started = timer;
    last_timer_duration = us;
    return ESP_OK;
}

esp_err_t esp_timer_stop(esp_timer_handle_t timer) {
    stop_call_count++;
    return ESP_OK;
}

void gpio_set_level(int pin, int level) {
    last_gpio_level = level;
}

void gpio_reset_pin(int pin) {}

void gpio_set_direction(int pin, int dir) {}

esp_matter_node_t* esp_matter_node_create(void) { return NULL; }
esp_matter_endpoint_t* esp_matter_endpoint_create(esp_matter_node_t* n, int id, const char* name, void* data) { return NULL; }
void esp_matter_switch_add(esp_matter_endpoint_t* e) {}
void esp_matter_init(void) {}
void esp_matter_start(esp_matter_node_t* n, void* a, int b, void* c) {}
void esp_matter_start_commissioning(esp_matter_node_t* n) {}

esp_err_t esp_event_handler_register(esp_event_base_t base, int32_t id, esp_err_t (*cb)(void*, esp_event_base_t, int32_t, void*), void* arg) { return ESP_OK; }
