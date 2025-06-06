#include "esp_stub.h"
#include "../main/timer_switch.h"
#include <assert.h>
#include <stdio.h>

int main(void) {
    timer_switch_init();

    stop_call_count = 0;
    last_gpio_level = -1;
    start_continuous(true);
    assert(cycle_mode == false);
    assert(last_gpio_level == 1);
    assert(stop_call_count == 2);

    stop_call_count = 0;
    last_gpio_level = -1;
    last_timer_started = 0;
    start_cycle(1000, 2000);
    assert(cycle_mode == true);
    assert(on_duration_us == 1000);
    assert(off_duration_us == 2000);
    assert(last_gpio_level == 1);
    assert(last_timer_started == off_timer);
    assert(last_timer_duration == 1000);

    printf("All tests passed\n");
    return 0;
}
