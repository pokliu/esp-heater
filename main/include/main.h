#ifndef _MAIN_H
#define _MAIN_H

#include "buzzer_util.h"
#include "lvgl_util.h"
#include "encoder_util.h"

// 可达鸭音乐
tone_t music_kdy[] = {
    {MSCM5, Q},
    {MSCM6, Q},
    {MSCH1, H},

    {MSCH1, E},
    {MSCM6, E},
    {MSCH1, E},
    {MSCH2, E},
    {MSCH2, H},

    {MSCH2, Q},
    {MSCH3, Q},
    {MSCH5, H},

    {MSCH5, E},
    {MSCH3, E},
    {MSCH5, E},
    {MSCH3, E},
    {MSCH3, H},

    {MSCH2, Q},
    {MSCH3, Q},
    {MSCH1, H},

    {MSCH1, E},
    {MSCM6, E},
    {MSCH1, E},
    {MSCH2, E},
    {MSCH2, H},

    {MSCH2, Q},
    {MSCH1, E},
    {MSCM6, E},
};

#endif