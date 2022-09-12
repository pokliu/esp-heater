#ifndef _BUZZER_H_
#define _BUZZER_H_


#define MSCL1 261.63
#define MSCL2 293.67
#define MSCL3 329.63
#define MSCL4 349.23
#define MSCL5 391.99
#define MSCL6 440
#define MSCL7 493.88
#define MSCM1 532.25
#define MSCM2 587.33
#define MSCM3 659.25
#define MSCM4 698.46
#define MSCM5 783.99
#define MSCM6 880
#define MSCM7 987.76
#define MSCH1 1046.50
#define MSCH2 1174.66
#define MSCH3 1318.51
#define MSCH4 1396.92
#define MSCH5 1567.98
#define MSCH6 1760
#define MSCH7 1975.52

// DURATION OF THE NOTES 
#define BPM 120 //  you can change this value changing all the others
// I think tecnically BPM supposed to be 104, but original 120
// from instructable sounds good.  180 sounds speedy, 240 sounds mario, 300 sounds
// middle eastern, 400 middle eastern techno pop?
#define Q 60000/BPM //quarter 1/4 
#define H 2*Q //half 2/4
#define E Q/2   //eighth 1/8
#define S Q/4 // sixteenth 1/16
#define W 4*Q // whole 4/4

typedef struct{
    double freq;
    int dur;
}tone_t;

void app_buzzer_cfg();
void bz_tone(int freq, int duration);


#endif