#include "command.h"
#include "effects_rack.h"
#include "display.h"
#include "controls.h"
#include "memory.h"
#include "msg_window.h"
#include "bluetooth.h"

DaisyHardware hw;

unsigned long last_frame_time;
unsigned long test_time;
bool test_state = false;

void audio_callback(float **in, float **out, size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        float signal, temp;
        // Mono only
        // [0] is main in/out,  [1] is for external effects loop
        signal = in[0][i];
        // process all the effects in the chain
        for (uint8_t j = 0; j < MAX_EFFECTS_NUM; j++)
        {
            // if effect is empty
            if (signal_chain[j] == nullptr)
                continue;
            // if the effect is the external analog module
            if (signal_chain[j] == &effects_rack.analog)
            {
                if (signal_chain[j]->enable)
                {
                    out[1][i] = signal; // send
                    temp = in[1][i];    // return
                }
                else // passthrough
                {
                    temp = signal;
                }
            }
            else
            {
                signal_chain[j]->process(signal, temp);
            }
            signal = temp;
        }
        // Assign output
        out[0][i] = signal;
    }
}

void setup()
{
    // Wait for the power to be stable
    delay(500);
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
    // Initialize bluetooth
    bluetooth_init();
    // Initialize memory
    memory.init();
    Serial.println("memory inited");
    if (memory.memory_valid != 1)
        memory.reset_memory();
    // Read from memory
    effects_rack.read_cur_preset_num();
    effects_rack.read_preset(effects_rack.cur_preset);
    options_window_ins.read_options();

    pinMode(LED_BUILTIN, OUTPUT);
    test_time = millis();

    Serial.println("Setup OK");

    // Begin audio callback
    DAISY.begin(audio_callback);

    Serial.println("Audio started");

    show_msg(MSG_WARNING, 25, "v0.1 alpha", "May be unstable!");
    mcp.digitalWrite(LED_FS0_PIN, HIGH);
    mcp.digitalWrite(LED_FS1_PIN, HIGH);
    mcp.digitalWrite(LED_FS2_PIN, HIGH);
    mcp.digitalWrite(LED_FS3_PIN, HIGH);
}

void loop()
{
    unsigned long current_time = millis();
    // Update buttons
    controls.btn_update();
    // get bluetooth commands
    bluetooth_get_command();
    // Handle commands sent by interrupt and bluetooth
    command_handler();
    // draw the display at about 6.67 fps
    if (current_time - last_frame_time > 150)
    {
        display.draw();
        last_frame_time = current_time;
    }
    if (current_time - test_time > 5000)
    {
        if (test_state)
        {
            digitalWrite(LED_BUILTIN, HIGH);
        }
        else
        {
            digitalWrite(LED_BUILTIN, LOW);
        }
        test_time = current_time;
        test_state = !test_state;
    }
}