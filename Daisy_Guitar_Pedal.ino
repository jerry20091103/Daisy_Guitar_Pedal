#include "effects_rack.h"
#include "display.h"

DaisyHardware hw;

unsigned long last_frame_time;
unsigned long test_time;

void audio_callback(float **in, float **out, size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        float signal, temp;
        // Mono only
        signal = in[0][i];
        // process all the effects in the chain
        for (uint8_t i = 0; i < MAX_EFFECTS_NUM; i++)
        {
            if (signal_chain[i] == nullptr)
                continue;
            signal_chain[i]->process(signal, temp);
            signal = temp;
        }
        // Assign output
        out[0][i] = signal;
    }
}

void setup()
{
    // Initialize for Daisy pod at 48kHz
    hw = DAISY.init(DAISY_SEED, AUDIO_SR_48K);
    sample_rate = DAISY.get_samplerate();
    // Initialize effects
    effects_rack.init();
    // Initialize display
    display.init();
    last_frame_time = millis();

    pinMode(LED_BUILTIN, OUTPUT);
    test_time = millis();

    Serial.begin(9600);

    // Begin audio callback
    DAISY.begin(audio_callback);

    Serial.println("Setup OK");
}

void loop()
{
    // draw the display at 10 fps
    if(millis() - last_frame_time > 100)
    {
        display.draw();
    }
    if (millis() - test_time > 5000)
    {
        if (signal_chain[0] == nullptr)
            signal_chain[0] = &effects_rack.reverb_mod01;
        else
            signal_chain[0] = nullptr;
    }
}