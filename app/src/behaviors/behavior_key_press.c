/*
 * Copyright (c) 2020 Peter Johanson <peter@peterjohanson.com>
 *
 * SPDX-License-Identifier: MIT
 */

#define DT_DRV_COMPAT zmk_behavior_key_press

#include <device.h>
#include <drivers/behavior.h>
#include <logging/log.h>

#include <zmk/events.h>

LOG_MODULE_DECLARE(zmk, CONFIG_ZMK_LOG_LEVEL);

struct behavior_key_press_config { };
struct behavior_key_press_data { };

static int behavior_key_press_init(struct device *dev)
{
	return 0;
};


// They keycode is passed by the "keymap" based on the parameter created as part of the assignment.
// Other drivers instead might activate a layer, update the consumer page state, or update the RGB state, etc.
// Returns:
//  * > 0 -  indicate successful processing, and halt further handling,
//  * 0 - Indicate successful processing, and continue propagation.
//  * < 0 - Indicate error processing, report and halt further propagation.
static int on_keymap_binding_pressed(struct device *dev, u32_t position, u32_t keycode, u32_t _)
{
  LOG_DBG("position %d keycode %d", position, keycode);
  return zmk_events_keycode_pressed(keycode);
}


// They keycode is passed by the "keymap" based on the parameter created as part of the assignment.
static int on_keymap_binding_released(struct device *dev, u32_t position, u32_t keycode, u32_t _)
{
  LOG_DBG("position %d keycode %d", position, keycode);
  return zmk_events_keycode_released(keycode);
}

static const struct behavior_driver_api behavior_key_press_driver_api = {
  // These callbacks are all optional, and define which kinds of events the behavior can handle.
  // They can reference local functions defined here, or shared event handlers.
  .binding_pressed = on_keymap_binding_pressed,
  .binding_released = on_keymap_binding_released
  // Other optional callbacks a behavior can implement
  // .on_mouse_moved
  // .on_sensor_data - Any behaviour that wants to be linked to a censor can implement this behavior
};


static const struct behavior_key_press_config behavior_key_press_config = {};

static struct behavior_key_press_data behavior_key_press_data;

DEVICE_AND_API_INIT(behavior_key_press, DT_INST_LABEL(0), behavior_key_press_init,
                    &behavior_key_press_data,
                    &behavior_key_press_config,
                    APPLICATION, CONFIG_KERNEL_INIT_PRIORITY_DEFAULT,
                    &behavior_key_press_driver_api);
