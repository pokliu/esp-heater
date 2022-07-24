#include <stdio.h>
#include <stdbool.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include <string.h>

#include "main.h"


extern int enc_diff;
void app_main(void)
{
    initialize_lvgl();
    initialize_music_player();
    initialize_encoder();

    start_play_music_task(music_kdy, sizeof(music_kdy) / sizeof(tone_t), false);
    // vTaskDelay(15000 / portTICK_PERIOD_MS);
    // stop_play_music_task();

    lv_obj_t * scr = lv_disp_get_scr_act(NULL);
    lv_obj_t * label1 =  lv_label_create(scr);
    lv_obj_align(label1, LV_ALIGN_CENTER, enc_diff, enc_diff);
    static lv_style_t style;
    lv_style_set_text_font(&style, &lv_font_montserrat_48);
    lv_obj_add_style(label1, &style, 0);
    
    static char label1Text[10] = {0};
    while(true)
    {
        sprintf(label1Text, "%d", enc_diff);
        lv_label_set_text(label1, label1Text);
        vTaskDelay(100 /portTICK_PERIOD_MS);
    }
}