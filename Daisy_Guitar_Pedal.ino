#include "command.h"
#include "effects_rack.h"
#include "display.h"
#include "controls.h"
#include "memory.h"

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
    Serial.begin(9600);
    // Initialize for Daisy pod at 48kHz
    hw = DAISY.init(DAISY_SEED, AUDIO_SR_48K);
    sample_rate = DAISY.get_samplerate();
    // Initialize effects
    effects_rack.init();
    // Initialize controls
    controls.init();
    // Initialize display
    display.init();
    last_frame_time = millis();

    pinMode(LED_BUILTIN, OUTPUT);
    test_time = millis();


    // Begin audio callback
    DAISY.begin(audio_callback);

    Serial.println("Setup OK");
}

void loop()
{
    unsigned long current_time = millis();
    // Update buttons
    controls.btn_update();
    // Handle commands sent by interrupt
    command_handler();
    // draw the display at about 6.67 fps
    if (current_time - last_frame_time > 150)
    {
        display.draw();
        last_frame_time = current_time;
    }
    if (current_time - test_time > 5000)
    {
        if (signal_chain[0] == nullptr)
        {
            signal_chain[0] = &effects_rack.reverb_mod01;
            digitalWrite(LED_BUILTIN, HIGH);
            mcp.digitalWrite(LED_FS1_PIN, HIGH);
        }
        else
        {
            signal_chain[0] = nullptr;
            digitalWrite(LED_BUILTIN, LOW);
            mcp.digitalWrite(LED_FS1_PIN, LOW);
        }
        test_time = current_time;
    }
}