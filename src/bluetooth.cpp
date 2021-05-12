// #include "bluetooth.h"
// #include "src/windows/msg_window.h"
// #include "command.h"

// HardwareSerial BT_mod(14, 13);

// void bluetooth_init()
// {
//     BT_mod.begin(9600);
//     BT_mod.setTimeout(500);
// }

// void bluetooth_get_command()
// {
//     if (BT_mod.available())
//     {
//         unsigned char bt_data[2] = {0};
//         if (BT_mod.readBytes(bt_data, 2) == 2)
//         {
//             //------------------------INT disabled
//             noInterrupts();
//             cmd_type[(cmd_pos + cmd_count) % MAX_COMMAND_BUF] = bt_data[0];
//             cmd_count++;
//             interrupts();
//             //------------------------INT enabled
//             //Serial.println(bt_data[0]);
//             //Serial.println(bt_data[1]);
//         }
//         else
//         {
//             show_msg(MSG_ERROR, 25, "Bluetooth read error", "WRONG FORMAT");
//         }
//     }
// }

// void bluetooth_sync()
// {
// }