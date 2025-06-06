#ifndef ESP_STUB_H
#define ESP_STUB_H
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

typedef int esp_err_t;
#define ESP_OK 0

#define ESP_MATTER_EVENT ((esp_event_base_t)0x01)
#define ESP_EVENT_ANY_ID 0
#define ESP_MATTER_EVENT_STARTED 1
#define ESP_MATTER_ENDPOINT_PRIMARY 1

typedef const void* esp_event_base_t;

typedef int esp_timer_handle_t;
typedef struct {
    void (*callback)(void*);
    const char* name;
} esp_timer_create_args_t;

esp_err_t esp_timer_create(const esp_timer_create_args_t* args, esp_timer_handle_t* out);
esp_err_t esp_timer_start_once(esp_timer_handle_t timer, int64_t us);
esp_err_t esp_timer_stop(esp_timer_handle_t timer);

void gpio_set_level(int pin, int level);
void gpio_reset_pin(int pin);
void gpio_set_direction(int pin, int dir);

struct esp_matter_node {int dummy;};
typedef struct esp_matter_node esp_matter_node_t;
struct esp_matter_endpoint {int dummy;};
typedef struct esp_matter_endpoint esp_matter_endpoint_t;

esp_matter_node_t* esp_matter_node_create(void);
esp_matter_endpoint_t* esp_matter_endpoint_create(esp_matter_node_t*, int, const char*, void*);
void esp_matter_switch_add(esp_matter_endpoint_t*);
void esp_matter_init(void);
void esp_matter_start(esp_matter_node_t*, void*, int, void*);

esp_err_t esp_event_handler_register(esp_event_base_t base, int32_t id, esp_err_t (*cb)(void*, esp_event_base_t, int32_t, void*), void* arg);

#define ESP_LOGI(tag, fmt, ...)

extern int last_gpio_level;
extern esp_timer_handle_t last_timer_started;
extern int64_t last_timer_duration;
extern int stop_call_count;

#endif // ESP_STUB_H
