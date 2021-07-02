#include "looper.h"

uint16_t DSY_SDRAM_BSS looper_mem[28800000];
_looper looper;

void _looper::init()
{
    clear();
    loop_level = 0.9;
    enable = false;
    recording = false;
}

void _looper::process(float in, float &out)
{
    if (!enable)
    {
        out = in;
    }
    else
    {
        int top_layer = cur_layer;
        // write sample into buffer
        if (recording)
        {
            // write input into new layer
            if(first_loop)
            {
                looper_mem[(cur_layer - 1) * loop_size + cur_pos] = f2s16(in);
            }
            else
            {
                looper_mem[(cur_layer - 1) * loop_size + cur_pos] += f2s16(in);
            }            
            top_layer--; // minus 1 since cur_layer is still in recording
        }

        // mix each layer
        uint16_t loop_mix = 0;
        for (int i = 0; i < top_layer; i++)
        {
            loop_mix += looper_mem[i * loop_size + cur_pos];
        }
        // write output
        out = in + s162f(loop_mix) * loop_level;
        // increment cur_pos by 1
        cur_pos = (cur_pos + 1) % loop_size;
    }
}

// recording button pressed
void _looper::record()
{
    // stop recording
    if (recording)
    {
        recording = false;
        if (first_loop)
        {
            first_loop = false;
            loop_size = cur_pos + 1;
        }
    }
    // start recording
    else
    {
        // if memory is full
        if ((cur_layer + 1) * loop_size > LOOPER_MEM_SIZE)
        {
            memory_full = true;
            return;
        }
        // start recording
        if(!first_loop)
            memset(&looper_mem[cur_layer * loop_size], 0, loop_size * 2);
        cur_layer++;
        layer_count = cur_layer;
        enable = true;
        recording = true;
    }
}

// play/stop button pressed
void _looper::stop()
{
    // stop
    if (enable)
    {
        enable = false;
        // stop recording if needed
        if (recording)
        {
            record();
        }
    }
    // play
    else if(layer_count > 0)
    {
        enable = true;
    }
}

void _looper::undo()
{
    if(recording)
    {
        return;
    }
    // clear all loops if looper is in "stop"
    else if(!enable)
    {
        clear();
    }
    // take out current layer (but still keep it for future redos)
    else
    {
        cur_layer = cur_layer <= 0 ? 0 : cur_layer-1;
    }
}

void _looper::redo()
{
    if(recording)
    {
        return;
    }
    else if(layer_count > cur_layer)
    {
        cur_layer++;
    }
}

// delete all loops
void _looper::clear()
{
    memset(looper_mem, 0, sizeof(looper_mem));
    layer_count = 0;
    cur_layer = 0;
    cur_pos = 0;
    loop_size = LOOPER_MEM_SIZE;
    first_loop = true;
    memory_full = false;
}

void _looper::loop_level_inc()
{
    if(loop_level + 0.1 < 1)
        loop_level += 0.1;
    else
        loop_level = 1;
}

void _looper::loop_level_dec()
{
    if(loop_level - 0.1 > 0)
        loop_level -= 0.1;
    else
        loop_level = 0;
}

float _looper::get_loop_pos()
{
    return cur_pos / (float)loop_size;
}

float _looper::get_meory_usage()
{
    return (layer_count * loop_size) / (float)LOOPER_MEM_SIZE;
}