#ifndef OUR_DRIVER_H
#define OUR_DRIVER_H

#include <zephyr/device.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Extension API: update the blink interval stored in the driver's dynamic data. */
int our_driver_set_blink_interval(const struct device *dev, uint32_t interval_ms);

#ifdef __cplusplus
}
#endif

#endif /* OUR_DRIVER_H */
