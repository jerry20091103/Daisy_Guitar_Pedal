#ifndef WINDOWS_H
#define WINDOWS_H

#define MAX_WINDOWS_NUM 2

enum all_windows
{
    MAIN_WINDOW,
    MSG_WINDOW
};

class windows
{
public:
    virtual void draw() = 0;
    virtual void update() = 0;
    virtual all_windows get_window_id() = 0;
    virtual void on_btn_pressed(int id) = 0; // TBD
    virtual void on_btn_holded(int id) = 0;  // TBD
private:

};


#endif
