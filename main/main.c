#include <stdio.h>
#include <stdbool.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include <string.h>

#include "main.h"


extern int enc_diff;

extern lv_group_t *group;


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

static void event_handler(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    size_t index = (size_t)lv_event_get_user_data(e);

    if(code == LV_EVENT_CLICKED) {
        ESP_LOGI("LV", "CLICKED: %d", index);

        stop_play_music_task();
        start_play_music_task(album[index].scores, album[index].len, false);
    }
    else if(code == LV_EVENT_FOCUSED) {
        ESP_LOGI("LV", "FOCUSED: %d", index);
        stop_play_music_task();
    }
}



void app_main(void)
{
    initialize_lvgl();
    initialize_music_player();
    initialize_encoder();

    static lv_style_t style;
    lv_style_set_text_font(&style, &lv_font_montserrat_16);
    lv_style_set_text_color(&style, lv_color_black());

    lv_obj_t * scr = lv_disp_get_scr_act(NULL);

    lv_obj_t * btn;
    lv_obj_t * label;

    const int width = 38;

    for (size_t i = 0; i < 3; i++)
    {
        album_music_t music =album[i];
        btn = lv_btn_create(scr);
        lv_obj_add_event_cb(btn, event_handler, LV_EVENT_ALL, i);
        lv_obj_set_size(btn, width, 50);
        lv_obj_align(btn, LV_ALIGN_LEFT_MID, i * (width + 4) + 4, 0);

        label = lv_label_create(btn);
        lv_label_set_text(label, music.txt);
        lv_obj_set_width(label, width);
        lv_label_set_long_mode(label, LV_LABEL_LONG_SCROLL_CIRCULAR);
        lv_obj_add_style(label, &style, 0);
        lv_obj_center(label);
    }
    

    while(true)
    {
        vTaskDelay(100 /portTICK_PERIOD_MS);
    }
}