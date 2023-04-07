#ifndef DDS_DOT_NET_CONNECTOR_SRC_INTERNAL_INC_MACROS_H_
#define DDS_DOT_NET_CONNECTOR_SRC_INTERNAL_INC_MACROS_H_


#include <chrono>
#include <thread>


#define sleep_msec(msec)  { std::chrono::milliseconds ms(msec); std::this_thread::sleep_for(ms); }

#define CONSOLE_COLOR_FG_BLACK             "\033[0;30m"
#define CONSOLE_COLOR_FG_RED               "\033[0;31m"
#define CONSOLE_COLOR_FG_GREEN             "\033[0;32m"
#define CONSOLE_COLOR_FG_YELLOW            "\033[0;33m"
#define CONSOLE_COLOR_FG_BLUE              "\033[0;34m"
#define CONSOLE_COLOR_FG_MAGENTA           "\033[0;35m"
#define CONSOLE_COLOR_FG_CYAN              "\033[0;36m"
#define CONSOLE_COLOR_FG_WHITE             "\033[0;37m"

#define CONSOLE_COLOR_FG_BLACK_BOLD        "\033[1;30m"
#define CONSOLE_COLOR_FG_RED_BOLD          "\033[1;31m"
#define CONSOLE_COLOR_FG_GREEN_BOLD        "\033[1;32m"
#define CONSOLE_COLOR_FG_YELLOW_BOLD       "\033[1;33m"
#define CONSOLE_COLOR_FG_BLUE_BOLD         "\033[1;34m"
#define CONSOLE_COLOR_FG_MAGENTA_BOLD      "\033[1;35m"
#define CONSOLE_COLOR_FG_CYAN_BOLD         "\033[1;36m"
#define CONSOLE_COLOR_FG_WHITE_BOLD        "\033[1;37m"

#define CONSOLE_COLOR_FG_BLACK_BLINK       "\033[5;30m"
#define CONSOLE_COLOR_FG_RED_BLINK         "\033[5;31m"
#define CONSOLE_COLOR_FG_GREEN_BLINK       "\033[5;32m"
#define CONSOLE_COLOR_FG_YELLOW_BLINK      "\033[5;33m"
#define CONSOLE_COLOR_FG_BLUE_BLINK        "\033[5;34m"
#define CONSOLE_COLOR_FG_MAGENTA_BLINK     "\033[5;35m"
#define CONSOLE_COLOR_FG_CYAN_BLINK        "\033[5;36m"
#define CONSOLE_COLOR_FG_WHITE_BLINK       "\033[5;37m"

#define CONSOLE_COLOR_BG_BLACK             "\033[40m"
#define CONSOLE_COLOR_BG_RED               "\033[41m"
#define CONSOLE_COLOR_BG_GREEN             "\033[42m"
#define CONSOLE_COLOR_BG_YELLOW            "\033[43m"
#define CONSOLE_COLOR_BG_BLUE              "\033[44m"
#define CONSOLE_COLOR_BG_MAGENTA           "\033[45m"
#define CONSOLE_COLOR_BG_CYAN              "\033[46m"
#define CONSOLE_COLOR_BG_WHITE             "\033[47m"

#define MAX_USHORT_VALUE                   65535







#endif