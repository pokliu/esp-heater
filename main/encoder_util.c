/*
 * Copyright (c) 2019 David Antliff
 *
 * This program provides an example using the esp32-rotary-encoder component.
 * Events are received via an event queue and displayed on the serial console.
 * The task also polls the device position every second to show that the latest
 * event always matches the current position.
 *
 * esp32-rotary-encoder is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * esp32-rotary-encoder is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with esp32-rotary-encoder.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <stdbool.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "esp_system.h"
#include "esp_log.h"

#include "rotary_encoder.h"

#define TAG "app"

#define ROT_ENC_A_GPIO (CONFIG_ENC_A_GPIO)
#define ROT_ENC_B_GPIO (CONFIG_ENC_B_GPIO)
#define ROT_ENC_SW_GPIO (CONFIG_ENC_SW_GPIO)

#define ENABLE_HALF_STEPS false  // Set to true to enable tracking of rotary encoder at half step resolution
#define FLIP_DIRECTION    false  // Set to true to reverse the clockwise/counterclockwise sense

// Initialise the rotary encoder device with the GPIOs for A and B signals
rotary_encoder_info_t info = { 0 };

bool IRAM_ATTR sw_press()
{
    return gpio_get_level(ROT_ENC_SW_GPIO) == 0;
}

int32_t last_pos = 0;

int IRAM_ATTR enc_diff()
{
    int diff = last_pos - info.state.position;
    last_pos = info.state.position;
    return diff;
}

void initialize_encoder()
{
    // esp32-rotary-encoder requires that the GPIO ISR service is installed before calling rotary_encoder_register()
    ESP_ERROR_CHECK(gpio_install_isr_service(0));

    ESP_ERROR_CHECK(rotary_encoder_init(&info, ROT_ENC_A_GPIO, ROT_ENC_B_GPIO));
    ESP_ERROR_CHECK(rotary_encoder_enable_half_steps(&info, ENABLE_HALF_STEPS));
#ifdef FLIP_DIRECTION
    ESP_ERROR_CHECK(rotary_encoder_flip_direction(&info));
#endif

    gpio_config_t sw_btn = {
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_ENABLE,
        .pin_bit_mask = (1ull << ROT_ENC_SW_GPIO)
    };
    gpio_config(&sw_btn);
}
