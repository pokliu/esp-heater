#include <stdio.h>
#include <stdbool.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include <string.h>

#include "driver/ledc.h"
#include "mini_pid_wrapper.h"

#include "main.h"
#include "ws2812.h"


extern int enc_diff;

extern lv_group_t *group;

extern float temperature;


typedef struct
{
  tone_t* scores;
  size_t len;
  char txt[16];  
} album_music_t;

static album_music_t album[3] = {
        {
            .scores = music_kdy,
            .len = sizeof(music_xyz) / sizeof(tone_t),
            .txt = "KFC psyduck"
        },
        {
            .scores = music_twotiger,
            .len = sizeof(music_twotiger) / sizeof(tone_t),
            .txt = "Two tiger"
        },
        {
            .scores = music_xyz,
            .len = sizeof(music_xyz) / sizeof(tone_t),
            .txt = "Young swallow"
        },
    };

// static void event_handler(lv_event_t * e)
// {
//     lv_event_code_t code = lv_event_get_code(e);
//     size_t index = (size_t)lv_event_get_user_data(e);

//     if(code == LV_EVENT_CLICKED) {
//         ESP_LOGI("LV", "CLICKED: %d", index);

//         stop_play_music_task();
//         start_play_music_task(album[index].scores, album[index].len, false);
//     }
//     else if(code == LV_EVENT_FOCUSED) {
//         ESP_LOGI("LV", "FOCUSED: %d", index);
//         stop_play_music_task();
//     }
// }

#define delay_ms(ms) vTaskDelay((ms) / portTICK_RATE_MS)

void rainbow(void *pvParameters)
{
  const uint8_t anim_step = 10;
  const uint8_t anim_max = 100;
  const uint8_t pixel_count = 16; // Number of your "pixels"
  const uint8_t delay = 25; // duration between color changes
  rgbVal color = makeRGBVal(anim_max, 0, 0);
  uint8_t step = 0;
  rgbVal color2 = makeRGBVal(anim_max, 0, 0);
  uint8_t step2 = 0;
  rgbVal *pixels;


  pixels = malloc(sizeof(rgbVal) * pixel_count);

  while (1) {
    color = color2;
    step = step2;

    for (uint8_t i = 0; i < pixel_count; i++) {
      pixels[i] = color;

      if (i == 1) {
        color2 = color;
        step2 = step;
      }

      switch (step) {
      case 0:
        color.g += anim_step;
        if (color.g >= anim_max)
          step++;
        break;
      case 1:
        color.r -= anim_step;
        if (color.r == 0)
          step++;
        break;
      case 2:
        color.b += anim_step;
        if (color.b >= anim_max)
          step++;
        break;
      case 3:
        color.g -= anim_step;
        if (color.g == 0)
          step++;
        break;
      case 4:
        color.r += anim_step;
        if (color.r >= anim_max)
          step++;
        break;
      case 5:
        color.b -= anim_step;
        if (color.b == 0)
          step = 0;
        break;
      }
    }

    ws2812_setColors(pixel_count, pixels);

    delay_ms(delay);
  }
}

void app_main(void)
{
    ws2812_init(27);
    xTaskCreate(rainbow, "ws2812 rainbow demo", 4096, NULL, 10, NULL);

    initialize_lvgl();
    initialize_music_player();
    initialize_encoder();
    initialize_temperature();

    static lv_style_t style;
    lv_style_set_text_font(&style, &lv_font_montserrat_32);
    // lv_style_set_text_color(&style, lv_color_black());

    lv_obj_t * scr = lv_disp_get_scr_act(NULL);

    lv_obj_t *label = lv_label_create(scr);
    lv_obj_add_style(label, &style, 0);
    lv_label_set_text(label, "init");
    lv_obj_center(label);

    // start_play_music_task(album[0].scores, album[0].len, true);

    // lv_obj_t * btn;
    // lv_obj_t * label;

    // const int width = 38;

    // for (size_t i = 0; i < 3; i++)
    // {
    //     album_music_t music =album[i];
    //     btn = lv_btn_create(scr);
    //     lv_obj_add_event_cb(btn, event_handler, LV_EVENT_ALL, i);
    //     lv_obj_set_size(btn, width, 50);
    //     lv_obj_align(btn, LV_ALIGN_LEFT_MID, i * (width + 4) + 4, 0);

    //     label = lv_label_create(btn);
    //     lv_label_set_text(label, music.txt);
    //     lv_obj_set_width(label, width);
    //     lv_label_set_long_mode(label, LV_LABEL_LONG_SCROLL_CIRCULAR);
    //     lv_obj_add_style(label, &style, 0);
    //     lv_obj_center(label);
    // }

    #define PIN_FAN   GPIO_NUM_33

    #define PIN_HEAT  GPIO_NUM_26

    ledc_timer_config_t heater_timer = {
      .duty_resolution = LEDC_TIMER_13_BIT, // resolution of PWM duty
      .freq_hz = 100,               // frequency of PWM signal
      .speed_mode = LEDC_LOW_SPEED_MODE,      // timer mode
      .timer_num = LEDC_TIMER_0       // timer index
    };
    ledc_timer_config(&heater_timer);

    ledc_channel_config_t heater_channel = {
      .channel = LEDC_CHANNEL_0,
      .duty = 0,
      .gpio_num = PIN_HEAT,
      .speed_mode = LEDC_LOW_SPEED_MODE,
      .timer_sel = LEDC_TIMER_0
    };
    ledc_channel_config(&heater_channel);


    ledc_timer_config_t fan_timer = {
      .duty_resolution = LEDC_TIMER_12_BIT, // resolution of PWM duty
      .freq_hz = 10000,               // frequency of PWM signal
      .speed_mode = LEDC_LOW_SPEED_MODE,      // timer mode
      .timer_num = LEDC_TIMER_1       // timer index
    };
    ledc_timer_config(&fan_timer);

    ledc_channel_config_t fan_channel = {
      .channel = LEDC_CHANNEL_1,
      .duty = 0,
      .gpio_num = PIN_FAN,
      .speed_mode = LEDC_LOW_SPEED_MODE,
      .timer_sel = LEDC_TIMER_1
    };
    ledc_channel_config(&fan_channel);

    
    void* mini_pid = MiniPIDInit(250, 0.2, 25);
    MiniPIDsetOutputLimitsMN(mini_pid, -4095, 8191);


    double target = 110;

    while(true)
    {
      char temp[6] = {0};
      sprintf(temp, "%.1f", temperature); 
      lv_label_set_text(label, temp);
      
      
      double output=MiniPIDgetOutputAS(mini_pid, temperature, target);
      if (output >= 0)
      {
        ledc_set_duty(fan_channel.speed_mode, fan_channel.channel, 0);
        ledc_update_duty(fan_channel.speed_mode, fan_channel.channel);

        ledc_set_duty(heater_channel.speed_mode, heater_channel.channel, output);
        ledc_update_duty(heater_channel.speed_mode, heater_channel.channel);
      } else {
        ledc_set_duty(fan_channel.speed_mode, fan_channel.channel, -output);
        ledc_update_duty(fan_channel.speed_mode, fan_channel.channel);
        
        ledc_set_duty(heater_channel.speed_mode, heater_channel.channel, 0);
        ledc_update_duty(heater_channel.speed_mode, heater_channel.channel);
      }
      

      ESP_LOGI("PID", "target: %.1f, sensor: %.1f, output: %.1f", target, temperature, output);

      vTaskDelay(100 /portTICK_PERIOD_MS);
    }
}