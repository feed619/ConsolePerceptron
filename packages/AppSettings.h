#ifndef APP_SETTINGS_H
#define APP_SETTINGS_H

#include <string>

namespace UI
{
    std::string pixel = "  ";
    std::string fill_pixel = "██";
    std::string bot_border_pixel = "‾‾";
    std::string top_border_pixel = "__";

    std::string minus = "█─█";
    std::string board = "─";
    std::string left_board = "    ";
    std::string str_btn = "";
    std::string top_board = "\n\n\n";

    std::string clear_btn = str_btn + "|" + "clear" + "| ";
    std::string start_btn = str_btn + "|" + "start" + "| ";
    std::string train_btn = str_btn + "|" + "train" + "| ";
    std::string test_btn = str_btn + "|" + "test " + "| ";
    std::string is_0_btn = str_btn + "|" + "is 0 " + "| ";
    std::string is_1_btn = str_btn + "|" + "is 1 " + "| ";
    std::string is_2_btn = str_btn + "|" + "is 2 " + "| ";
    std::string is_3_btn = str_btn + "|" + "is 3 " + "| ";
    std::string is_4_btn = str_btn + "|" + "is 4 " + "| ";
    std::string is_5_btn = str_btn + "|" + "is 5 " + "| ";
    std::string is_6_btn = str_btn + "|" + "is 6 " + "| ";
    std::string is_7_btn = str_btn + "|" + "is 7 " + "| ";
    std::string is_8_btn = str_btn + "|" + "is 8 " + "| ";
    std::string is_9_btn = str_btn + "|" + "is 9 " + "| ";
    std::string buttons = "\n" + left_board + " _____   _____   _____   _____   _____   _____   _____" + "\n" + left_board + clear_btn + start_btn + is_0_btn + is_1_btn + is_2_btn + is_3_btn + is_4_btn +

                          "\n" + left_board + train_btn + test_btn + is_5_btn + is_6_btn + is_7_btn + is_8_btn + is_9_btn + "\n" +
                          left_board + " ‾‾‾‾‾   ‾‾‾‾‾   ‾‾‾‾‾   ‾‾‾‾‾   ‾‾‾‾‾   ‾‾‾‾‾   ‾‾‾‾‾" + "\n";

    int width = 28;
    int height = 28;
    int width_pixle_x = 16;
    int height_pixle_y = 16;
    int width_btn_x = 12;

    int start_holst_x = 40;
    int end_holst_x = start_holst_x + width_pixle_x * width;

    int start_holst_y = 72;
    int end_holst_y = start_holst_y + width_pixle_x * height;

    int end_buttons_y = 5 * height_pixle_y;

    std::string bot_border = "";
    std::string top_border = "";
}

#endif