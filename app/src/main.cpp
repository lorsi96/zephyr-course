#include <zephyr/drivers/gpio.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/drivers/led_strip.h>
#include <zephyr/device.h>

/* The devicetree node identifier for the "led0" alias. */
#define LED_NODE DT_ALIAS(app_led)

static const struct device *strip = DEVICE_DT_GET(LED_NODE);

struct led_rgb red[] = { {.r = 255, .g = 0, .b = 0} };  /* red */
struct led_rgb blue[] = { {.r = 0, .g = 0, .b = 255} };  /* red */


LOG_MODULE_REGISTER(main, LOG_LEVEL_INF);

int main(void)
{
    bool led_state = true;

    while (1) {

        led_state = !led_state;

        if (led_strip_update_rgb(strip, led_state ? red : blue, ARRAY_SIZE(red)) < 0) {
            return 0;
        };
        LOG_INF("LED state: %s", led_state ? "ON" : "OFF");
        k_msleep(CONFIG_APP_HEARTBEAT_PERIOD_MS);
    }
    return 0;
}
