#ifndef LVGL_UTIL_H
#define LVGL_UTIL_H

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif
#include "lvgl_helpers.h"

#define LV_TICK_PERIOD_MS 1

void initialize_lvgl();

#endif