#include <zephyr/drivers/sensor.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

#include "our_driver.h"

LOG_MODULE_REGISTER(main, LOG_LEVEL_INF);

static const struct device *led_dev = DEVICE_DT_GET(DT_NODELABEL(our_driver0));

int main(void)
{
    if (!device_is_ready(led_dev)) {
        LOG_ERR("our_driver not ready");
        return -ENODEV;
    }

    /* Extension API: change blink_interval_ms in the driver's dynamic data */
    our_driver_set_blink_interval(led_dev, 500);

    struct sensor_value val;

    while (1) {
        /* sample_fetch turns the LED on */
        sensor_sample_fetch(led_dev);
        k_msleep(500);

        /* channel_get turns the LED off */
        sensor_channel_get(led_dev, SENSOR_CHAN_ALL, &val);
        k_msleep(500);
    }

    return 0;
}
