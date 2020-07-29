#include "effects_rack.h"

DaisyHardware hw;

void audio_callback(float **in, float **out, size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        float signal, temp;
        // Mono only
        signal = in[0][i];
        // process all the effects in the chain
        for(uint8_t i=0; i<MAX_EFFECTS_NUM; i++)
        {
            if(signal_chain[i] == nullptr)
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

    pinMode(LED_BUILTIN, OUTPUT);

    Serial.begin(9600);

    // Begin audio callback
    DAISY.begin(audio_callback);

    Serial.println("Setup OK");
}

void loop() 
{
    delay(5000);
    signal_chain[0] = &effects_rack.reverb_mod01;
    digitalWrite(LED_BUILTIN, HIGH);
    delay(5000);
    signal_chain[0] = nullptr;
    digitalWrite(LED_BUILTIN, LOW);
}