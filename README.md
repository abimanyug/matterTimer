# Matter Timer Switch for ESP32-C6

This project provides a simple example of a timer controlled GPIO switch implemented using the Matter protocol. The switch supports two modes:

1. **Continuous On/Off** – drive the GPIO high or low without a timer.
2. **Cycle Mode** – keep the GPIO on for `X` seconds/minutes and then off for `X` seconds/minutes in a loop.

The example uses the ESP‑Matter SDK and targets the ESP32‑C6.

## File Structure

- `CMakeLists.txt` – project definition for ESP‑IDF.
- `main/timer_switch.c` – application source implementing the timer logic and Matter endpoint.

## Usage

1. Set up [ESP‑IDF](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/index.html) and the [ESP‑Matter](https://github.com/espressif/esp-matter) SDK.
2. Configure the project using `idf.py menuconfig` to select your Wi‑Fi credentials and other parameters.
3. Build and flash with `idf.py -p PORT flash monitor`.

The `app_main` function in `timer_switch.c` shows an example that cycles the GPIO on for 60 s and off for 30 s. Modify the call to `start_cycle` or use `start_continuous` to change behaviour as needed.

