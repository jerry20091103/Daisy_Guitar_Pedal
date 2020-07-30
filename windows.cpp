#include "windows.h"
#include "display.h"

void windows::change_window(all_windows window)
{
    display.current_window = display.windows_arr[window];
}