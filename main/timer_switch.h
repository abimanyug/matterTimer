#pragma once
#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

void timer_switch_init(void);
void start_continuous(bool on);
void start_cycle(int64_t on_us, int64_t off_us);

#ifdef __cplusplus
}
#endif

#ifdef UNIT_TEST
extern bool cycle_mode;
extern int64_t on_duration_us;
extern int64_t off_duration_us;
extern esp_timer_handle_t on_timer;
extern esp_timer_handle_t off_timer;
#endif
