#ifndef LOOPER_H
#define LOOPER_H

#include "effect_modules/effects.h"
#define LOOPER_MEM_SIZE 28800000
#define LOOPER_OPTIONS_AMOUNT 1

// 10 mins of total loop time in SDRAM
extern int16_t DSY_SDRAM_BSS looper_mem[LOOPER_MEM_SIZE];

// the looper class for core looper functions
// memory is handled like a stack.
// GUIs are in looper_window.h / .cpp
class _looper
{
public:
    void init();
    void process(float in, float &out);
    void record();
    void stop();
    void undo();
    void redo();
    void clear();
    float loop_level;     // volume level of the loop
    float get_loop_pos(); // get current position / loop length (for GUI)
    float get_meory_usage();
    void loop_level_inc(); // increase loop level
    void loop_level_dec(); // decrease loop level
    bool memory_full;
    int layer_count;     // current layer count
    int cur_layer;       // current layer that is active (layers <= cur_layer are acitve)
    bool enable;
    bool recording;
    void read_options();
    void save_options();

private:
    bool first_loop;     // whether this is the first loop layer or not
    int loop_size;       // length of each loop (in samples)
    int cur_pos;         // current playing / recording position
    bool first_loop_full; // whether the first loop used the whole memory
};

extern _looper looper;

#endif