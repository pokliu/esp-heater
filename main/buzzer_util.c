#include <stdio.h>
#include <stdbool.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "buzzer_util.h"
#include "esp_log.h"

typedef struct
{
    tone_t* music;
    size_t len;
    bool loop;
} music_play_t;

static music_play_t mpt;

TaskHandle_t music_task_handler;

// 停止音乐
static void stop_music()
{
    bz_tone(3000, 100);
}

// 播放音乐
static void play_music(const void *parameter)
{
    music_play_t* mpt = (music_play_t*)parameter;
    while(true)
    {
        for(size_t i = 0; i < mpt->len; i++)
        {
            tone_t tone = mpt->music[i];
            bz_tone(tone.freq, tone.dur);
        }
        if (!mpt->loop)
        {
            stop_music();
            vTaskDelete(NULL);
        }       
    }
}



void initialize_music_player()
{
    app_buzzer_cfg();
}

void start_play_music_task(tone_t* music, size_t len, bool loop)
{
    mpt.music = music;
    mpt.len = len;
    mpt.loop = loop;
    
    xTaskCreate(
        (TaskFunction_t)play_music,
        "music",
        1024 * 8,
        (void*)&mpt,
        0,
        &music_task_handler
    );
}

void stop_play_music_task()
{
    stop_music();
    vTaskDelete(music_task_handler);
}