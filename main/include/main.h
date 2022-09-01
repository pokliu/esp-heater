#ifndef _MAIN_H
#define _MAIN_H

#include "buzzer_util.h"
#include "lvgl_util.h"
#include "encoder_util.h"
#include "temperature.h"

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

// 两只老虎
tone_t music_twotiger[] = {
    {MSCM1, Q},
    {MSCM2, Q},
    {MSCM3, Q},
    {MSCM1, Q},

    {MSCM1, Q},
    {MSCM2, Q},
    {MSCM3, Q},
    {MSCM1, Q},

    {MSCM3, Q},
    {MSCM4, Q},
    {MSCM5, H},

    {MSCM3, Q},
    {MSCM4, Q},
    {MSCM5, H},

    {MSCM5, E},
    {MSCM6, E},
    {MSCM5, E},
    {MSCM4, E},
    {MSCM3, Q},
    {MSCM1, Q},

    {MSCM5, E},
    {MSCM6, E},
    {MSCM5, E},
    {MSCM4, E},
    {MSCM3, Q},
    {MSCM1, Q},

    {MSCM3, Q},
    {MSCL5, Q},
    {MSCM1, H},

    {MSCM3, Q},
    {MSCL5, Q},
    {MSCM1, H},
};

// 小燕子
tone_t music_xyz[] = {
    {MSCM3, E},
    {MSCM5, E},
    {MSCH1, E},
    {MSCM6, E},
    {MSCM5, H},

    {MSCM3, E},
    {MSCM5, E},
    {MSCM6, E},
    {MSCH1, E},
    {MSCM5, H},

    {MSCH1, Q+E},
    {MSCH3, E},
    {MSCH2, Q},
    {MSCH1, Q},

    {MSCH2, E},
    {MSCH1, E},
    {MSCM6, E},
    {MSCH1, E},
    {MSCM5, H},

    {MSCM3, Q+E},
    {MSCM5, E},
    {MSCM6, Q},
    {MSCM5, E},
    {MSCM6, E},

    {MSCH1, Q},
    {MSCH2, E},
    {MSCM5, E},
    {MSCM6, H},

    {MSCM3, E},
    {MSCM2, E},
    {MSCM1, Q},
    {MSCM2, H},

    {MSCM2, Q},
    {MSCM2, E},
    {MSCM3, E},
    {MSCM5, Q},
    {MSCM5, Q},

    {MSCH1, Q},
    {MSCM2, E},
    {MSCM3, E},
    {MSCM5, H},
};

#endif