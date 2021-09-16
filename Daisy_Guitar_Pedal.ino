#include "src/effect_modules/effects_rack.h"
#include "src/command.h"
#include "src/display.h"
#include "src/controls.h"
#include "src/memory.h"
#include "src/windows/msg_window.h"
#include "src/looper.h"
#include "src/tuner.h"
//#include "src/bluetooth.h"

DaisyHardware hw;

unsigned long last_frame_time;

void audio_callback(float **in, float **out, size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        float temp;
        // Mono only
        // [0] is main in/out,  [1] is for external effects loop
        // set outputs to zero first
        out[1][i] = 0;
        out[0][i] = 0;
        // if the tuner is acitve
        if (display.current_window->get_window_id() == TUNER_WINDOW)
        {
            tuner.process(in[0][i]);
        }
        else
        {
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
                        out[1][i] = in[0][i]; // send
                        temp = in[1][i];    // return
                    }
                    else // passthrough
                    {
                        temp = in[0][i];
                    }
                }
                else
                {
                    signal_chain[j]->process(in[0][i], temp);
                }
                in[0][i] = temp;
            }
            // Process IR cab sim
            IR_ins.process(in[0][i], temp);
            in[0][i] = temp;

            // Process EQ cab sim
            cab_ins.process(in[0][i], temp);
            in[0][i] = temp;

            // Process looper
            looper.process(in[0][i], temp);
            in[0][i] = temp;
        }

        // Assign output
        out[0][i] = in[0][i];
    }
}

void setup()
{
    // Wait for the power to be stable
    delay(500);
    //Serial.begin(9600);
    // Initialize Daisy seed at 48kHz
    hw = DAISY.init(DAISY_SEED, AUDIO_SR_48K);
    sample_rate = DAISY.get_samplerate();
    // Initialize controls
    command_init();
    controls.init();
    // Initialize display
    display.init();
    last_frame_time = millis();
    // Initialize bluetooth
    //bluetooth_init();
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
        //Serial.println("Memory inited");
        memory.reset_memory();
        memory.save_to_flash();
        //Serial.println("memory reset");
    }
    /*else if (!digitalRead(28))
    {
        while (!digitalRead(28))
        {
            delay(100);
        }
        //Serial.println("Dumping started.");
        memory.init();
        memory.read_from_flash();
        //Serial.println("Memory inited");
        for (int i = 0; i < MAX_USER_PRESET; i++)
        {
            for (int j = 0; j < MAX_EFFECTS_NUM; j++)
            {
                for (int k = 0; k < MAX_PARAM_NUM; k++)
                {
                    //Serial.print("effect param ");
                    //Serial.print(i);
                    //Serial.print(" ");
                    //Serial.print(j);
                    //Serial.print(" ");
                    //Serial.print(k);
                    //Serial.print(" : ");
                    //Serial.println(memory.effect_preset_mem[i].param[j][k]);
                }
                //Serial.print(i);
                //Serial.print(" ");
                //Serial.print(j);
                //Serial.print(" ");
                //Serial.print("id: ");
                //Serial.print(memory.effect_preset_mem[i].id[j]);
                //Serial.print(" / ");
                //Serial.println(memory.effect_preset_mem[i].enable[j]);
            }
        }
        //Serial.print("cur_preset: ");
        //Serial.println(memory.cur_preset_mem);
        //Serial.print(" / valid: ");
        //Serial.println(memory.memory_valid);
        for (int i = 0; i < OPTIONS_AMOUNT; i++)
        {
            //Serial.print("option ");
            //Serial.print(i);
            //Serial.print(" : ");
            //Serial.println(memory.options_mem[i]);
        }
    }*/
    memory.init();
    memory.read_from_flash();
    //Serial.println("memory inited");
    if (memory.memory_valid != 1)
    {
        memory.reset_memory();
    }
    // Initialize effects
    effects_rack.init();
    looper.init();
    tuner.init();
    IR_ins.init();
    cab_ins.init();
    // Read from memory
    effects_rack.read_cur_preset_num();
    effects_rack.read_preset(effects_rack.cur_preset);
    options_window_ins.read_options();
    looper.read_options();

    pinMode(LED_BUILTIN, OUTPUT);

    //Serial.println("Setup OK");

    // Begin audio callback
    DAISY.begin(audio_callback);

    //Serial.println("Audio started");

    show_msg(MSG_WARNING, 25, "v0.3 beta", "May be unstable!");
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
    //bluetooth_get_command();
    // Handle commands sent by interrupt and bluetooth
    command_handler();
    // draw the display with max fps at about 10 fps
    if (current_time - last_frame_time > 100)
    {
        display.draw();
        last_frame_time = current_time;
    }
}