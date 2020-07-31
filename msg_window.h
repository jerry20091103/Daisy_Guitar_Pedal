#ifndef MSG_WINDOW_H
#define MSG_WINDOW_H

#include "windows.h"

#define MSG_POPUP_TIME 50 // Msg box will appear 50 frames
#define MAX_MSG_LEN 20    // a max of 20 characters

enum _msg_type
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
    virtual void on_btn_pressed(int id) override;
    virtual void on_btn_holded(int id) override;
private:
    int time = 0;
};

// create a single instance
extern msg_window msg_window_ins;

// The message to show
extern char msg[MAX_MSG_LEN + 1];
// The type of message to show
extern _msg_type msg_type;

#endif