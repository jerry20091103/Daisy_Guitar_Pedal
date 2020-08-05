#ifndef MSG_WINDOW_H
#define MSG_WINDOW_H

#include "windows.h"

#define MAX_MSG_LEN 20    // a max of 20 characters

enum _msg_type : byte
{
    MSG_INFO,
    MSG_WARNING,
    MSG_ERROR
};

// Message pop up window
class msg_window : public windows
{
public:
    virtual void draw() override;
    virtual void update() override;
    virtual all_windows get_window_id() override;
    virtual void on_btn_pressed(buttons id) override;
    virtual void on_btn_holded(buttons id) override;
    virtual void on_enc_turned(RotaryEncoder::Direction dir) override;
private:
    int time = 0;
};

// Function to show a message
void show_msg(_msg_type type, int time, char *data1, char *data2);

// create a single instance
extern msg_window msg_window_ins;

// The message to show
extern char msg1[MAX_MSG_LEN + 1];
extern char msg1[MAX_MSG_LEN + 1];
// The type of message to show
extern _msg_type msg_type;
// The message pop up time (frames)
extern int msg_popup_time;

#endif