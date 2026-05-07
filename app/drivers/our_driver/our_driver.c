#define DT_DRV_COMPAT our_driver

#include <zephyr/drivers/sensor.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/device.h>
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(our_driver, LOG_LEVEL_INF);

struct our_driver_config {
	struct gpio_dt_spec led;
};

struct our_driver_data {
	int dummy; /* placeholder for dynamic data */
};

/* sample_fetch: turn the LED on */
static int our_driver_sample_fetch(const struct device *dev,
				   enum sensor_channel chan)
{
	const struct our_driver_config *cfg = dev->config;

	LOG_INF("%s: sample_fetch -> LED ON", dev->name);
	return gpio_pin_set_dt(&cfg->led, 1);
}

/* channel_get: turn the LED off */
static int our_driver_channel_get(const struct device *dev,
				  enum sensor_channel chan,
				  struct sensor_value *val)
{
	const struct our_driver_config *cfg = dev->config;

	LOG_INF("%s: channel_get -> LED OFF", dev->name);
	gpio_pin_set_dt(&cfg->led, 0);

	val->val1 = 0;
	val->val2 = 0;
	return 0;
}

static const DEVICE_API(sensor, our_driver_api) = {
	.sample_fetch = our_driver_sample_fetch,
	.channel_get  = our_driver_channel_get,
};

static int our_driver_init(const struct device *dev)
{
	const struct our_driver_config *cfg = dev->config;

	if (!gpio_is_ready_dt(&cfg->led)) {
		LOG_ERR("%s: GPIO not ready", dev->name);
		return -ENODEV;
	}

	int ret = gpio_pin_configure_dt(&cfg->led, GPIO_OUTPUT_INACTIVE);
	if (ret < 0) {
		LOG_ERR("%s: failed to configure GPIO (%d)", dev->name, ret);
		return ret;
	}

	LOG_INF("%s: init (GPIO%u)", dev->name, cfg->led.pin);
	return 0;
}

#define OUR_DRIVER_DEFINE(inst)						\
	static struct our_driver_data our_driver_data_##inst = {	\
		.dummy = 0,						\
	};								\
									\
	static const struct our_driver_config our_driver_cfg_##inst = {	\
		.led = GPIO_DT_SPEC_INST_GET(inst, gpios),		\
	};								\
									\
	DEVICE_DT_INST_DEFINE(inst,					\
			      our_driver_init,				\
			      NULL,					\
			      &our_driver_data_##inst,			\
			      &our_driver_cfg_##inst,			\
			      POST_KERNEL,				\
			      80,					\
			      &our_driver_api);

DT_INST_FOREACH_STATUS_OKAY(OUR_DRIVER_DEFINE)
