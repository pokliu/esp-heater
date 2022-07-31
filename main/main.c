#include <stdio.h>
#include <stdbool.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include <string.h>

#include "main.h"


extern int enc_diff;

extern lv_group_t *group;

static void event_handler(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);

    if(code == LV_EVENT_CLICKED) {
        ESP_LOGI("LV", "CLICKED");
    }
    else if(code == LV_EVENT_VALUE_CHANGED) {
        ESP_LOGI("LV", "CHANGED");
    }
}

void app_main(void)
{
    initialize_lvgl();
    initialize_music_player();
    initialize_encoder();

    // start_play_music_task(music_kdy, sizeof(music_kdy) / sizeof(tone_t), false);
    // vTaskDelay(15000 / portTICK_PERIOD_MS);
    // stop_play_music_task();

    static lv_style_t style;
    lv_style_set_text_font(&style, &lv_font_montserrat_16);
    lv_style_set_text_color(&style, lv_color_black());

    lv_obj_t * scr = lv_disp_get_scr_act(NULL);
    
    lv_obj_t * label;

    lv_obj_t * btn1 = lv_btn_create(scr);
    lv_obj_add_event_cb(btn1, event_handler, LV_EVENT_ALL, NULL);
    lv_obj_set_size(btn1, 40, 50);
    lv_obj_align(btn1, LV_ALIGN_CENTER, -40, 0);

    label = lv_label_create(btn1);
    lv_label_set_text(label, "A");
    lv_obj_add_style(label, &style, 0);
    lv_obj_center(label);

    lv_obj_t * btn2 = lv_btn_create(scr);
    lv_obj_add_event_cb(btn2, event_handler, LV_EVENT_ALL, NULL);
    lv_obj_set_size(btn2, 40, 50);
    lv_obj_align(btn2, LV_ALIGN_CENTER, 40, 0);

    label = lv_label_create(btn2);
    lv_label_set_text(label, "B");
    lv_obj_add_style(label, &style, 0);
    lv_obj_center(label);

    lv_group_add_obj(group, btn1);
    lv_group_add_obj(group, btn2);

    while(true)
    {
        vTaskDelay(100 /portTICK_PERIOD_MS);
    }
}