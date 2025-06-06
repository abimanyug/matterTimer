#include "esp_log.h"
#include "esp_timer.h"
#include "driver/gpio.h"
#include "esp_matter.h"
#include "app_priv.h"
#include "esp_event.h"

/* Start Matter commissioning and print the onboarding QR code */
void esp_matter_start_commissioning(esp_matter_node_t *node);



constexpr int GPIO_OUTPUT_PIN = 2;
static const char *TAG = "timer_switch";

#ifdef UNIT_TEST
esp_timer_handle_t on_timer;
esp_timer_handle_t off_timer;
bool cycle_mode = false;
int64_t on_duration_us = 1'000'000;  // default 1s
int64_t off_duration_us = 1'000'000; // default 1s
#else
static esp_timer_handle_t on_timer;
static esp_timer_handle_t off_timer;
static bool cycle_mode = false;
static int64_t on_duration_us = 1'000'000;  // default 1s
static int64_t off_duration_us = 1'000'000; // default 1s
#endif





void on_timer_callback(void* arg) {
    ESP_LOGI(TAG, "ON timer triggered");
    gpio_set_level(GPIO_OUTPUT_PIN, 1);
    if (cycle_mode) {
        esp_timer_start_once(off_timer, on_duration_us);
    }
}

void off_timer_callback(void* arg) {
    ESP_LOGI(TAG, "OFF timer triggered");
    gpio_set_level(GPIO_OUTPUT_PIN, 0);
    if (cycle_mode) {
        esp_timer_start_once(on_timer, off_duration_us);
    }
}

esp_err_t app_event_cb(void *arg, esp_event_base_t event_base,
                       int32_t event_id, void *event_data) {
    if (event_base == ESP_MATTER_EVENT && event_id == ESP_MATTER_EVENT_STARTED) {
        ESP_LOGI(TAG, "Matter stack started");
    }
    return ESP_OK;
}



extern "C" void timer_switch_init(void)
{
    gpio_reset_pin(GPIO_OUTPUT_PIN);
    gpio_set_direction(GPIO_OUTPUT_PIN, GPIO_MODE_OUTPUT);

    const esp_timer_create_args_t on_args = {
        .callback = &on_timer_callback,
        .name = "on_timer"};
    esp_timer_create(&on_args, &on_timer);

    const esp_timer_create_args_t off_args = {
        .callback = &off_timer_callback,
        .name = "off_timer"};
    esp_timer_create(&off_args, &off_timer);
}

extern "C" void start_continuous(bool on)
{
    cycle_mode = false;
    esp_timer_stop(on_timer);
    esp_timer_stop(off_timer);
    gpio_set_level(GPIO_OUTPUT_PIN, on ? 1 : 0);
}

extern "C" void start_cycle(int64_t on_us, int64_t off_us)
{
    on_duration_us = on_us;
    off_duration_us = off_us;
    cycle_mode = true;
    gpio_set_level(GPIO_OUTPUT_PIN, 1);
    esp_timer_start_once(off_timer, on_duration_us);
}

extern "C" void app_main(void)
{
    timer_switch_init();

    esp_matter_init();
    esp_event_handler_register(ESP_MATTER_EVENT, ESP_EVENT_ANY_ID, &app_event_cb, NULL);

    /* Matter node and endpoint initialization */
    esp_matter_node_t *node = esp_matter_node_create();
    esp_matter_endpoint_t *endpoint = esp_matter_endpoint_create(node, ESP_MATTER_ENDPOINT_PRIMARY, "TimerSwitch", NULL);
    esp_matter_switch_add(endpoint);

    /* Start commissioning so the user can provide Wi-Fi credentials */
    esp_matter_start_commissioning(node);

    esp_matter_start(node, NULL, 0, NULL);  // start matter stack

    // Example usage
    start_cycle(60'000'000, 30'000'000); // 60s ON, 30s OFF
}

