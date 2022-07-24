#ifndef BUZZER_UTIL_H
#define BUZZER_UTIL_H

#include "buzzer.h"
#include <stdbool.h>

/**
 * @brief 初始化蜂鸣音乐播放器
 * 
 */
void initialize_music_player();

/**
 * @brief 开始蜂鸣器播放音乐Task
 * 
 * @param music tone_t* 音乐序列指针
 * @param len 音乐长度
 * @param loop 是否循环
 */
void start_play_music_task(tone_t* music, size_t len, bool loop);

/**
 * @brief 停止蜂鸣器播放音乐Task
 * 
 */
void stop_play_music_task();

#endif