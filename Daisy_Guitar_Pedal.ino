#include "effects_rack.h"
#include "command.h"
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
            if (signal_chain[j] == effects_rack.effects_arr[ANALOG_ID])
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
    // Initialize Daisy seed at 48kHz
    hw = DAISY.init(DAISY_SEED, AUDIO_SR_48K);
    sample_rate = DAISY.get_samplerate();
    // Initialize effects
    effects_rack.init();
    // Initialize controls
    command_init();
    controls.init();
    // Initialize display
    display.init();
    last_frame_time = millis();
    // Initialize bluetooth
    bluetooth_init();
    // Initialize memory
    // add option to reset memory or dump memory to serial
    //  hold and release btn OK to reset flash memory
    //  hold and release btn UP to dump flash memory
    if (!digitalRead(30))
    {
        while (!digitalRead(30))
        {
            delay(100);
        }
        memory.init();
        Serial.println("Memory inited");
        memory.reset_memory();
        memory.save_to_flash();
        Serial.println("memory reset");
    }
    else if (!digitalRead(28))
    {
        while (!digitalRead(28))
        {
            delay(100);
        }
        Serial.println("Dumping started.");
        memory.init();
        memory.read_from_flash();
        Serial.println("Memory inited");
        for (int i = 0; i < MAX_USER_PRESET; i++)
        {
            for (int j = 0; j < MAX_EFFECTS_NUM; j++)
            {
                for (int k = 0; k < MAX_PARAM_NUM; k++)
                {
                    Serial.print("effect param ");
                    Serial.print(i);
                    Serial.print(" ");
                    Serial.print(j);
                    Serial.print(" ");
                    Serial.print(k);
                    Serial.print(" : ");
                    Serial.println(memory.effect_param_mem[i][j][k]);
                }
                Serial.print(i);
                Serial.print(" ");
                Serial.print(j);
                Serial.print(" ");
                Serial.print("id: ");
                Serial.print(memory.effect_id_mem[i][j]);
                Serial.print(" / ");
                Serial.println(memory.effect_enable_mem[i][j]);
            }
        }
        Serial.print("cur_preset: ");
        Serial.println(memory.cur_preset_mem);
        Serial.print(" / valid: ");
        Serial.println(memory.memory_valid);
        for (int i = 0; i < OPTIONS_AMOUNT; i++)
        {
            Serial.print("option ");
            Serial.print(i);
            Serial.print(" : ");
            Serial.println(memory.options_mem[i]);
        }
    }
    memory.init();
    memory.read_from_flash();
    Serial.println("memory inited");
    if (memory.memory_valid != 1)
    {
        memory.reset_memory();
    }
    // Read from memory
    effects_rack.read_cur_preset_num();
    effects_rack.read_preset(effects_rack.cur_preset);
    options_window_ins.read_options();

    pinMode(LED_BUILTIN, OUTPUT);

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
    // draw the display when a new command happens with max fps about 10 fps
    if (current_time - last_frame_time > 100)
    {
        display.draw();
        last_frame_time = current_time;
    }
}