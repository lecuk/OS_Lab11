#ifndef PRETTY_CONSOLE_H
#define PRETTY_CONSOLE_H

#ifdef WIN32

#define C_BG_WHITE			"\033[48;5;255m"
#define C_BG_GRAY			"\033[48;5;243m"
#define C_BG_BLACK			"\033[48;5;232m"
#define C_BG_RED			"\033[48;5;196m"
#define C_BG_GREEN			"\033[48;5;46m"
#define C_BG_BLUE			"\033[48;5;27m"
#define C_BG_YELLOW			"\033[48;5;226m"
#define C_BG_PURPLE			"\033[48;5;91m"
#define C_BG_PINK			"\033[48;5;200m"
#define C_BG_ORANGE			"\033[48;5;202m"
#define C_BG_AQUA			"\033[48;5;51m"
#define C_BG_DARKRED		"\033[48;5;124m"
#define C_BG_DARKGREEN		"\033[48;5;22m"
#define C_BG_DARKBLUE		"\033[48;5;18m"

#define C_FG_WHITE			"\033[38;5;255m"
#define C_FG_GRAY			"\033[38;5;243m"
#define C_FG_BLACK			"\033[38;5;232m"
#define C_FG_RED			"\033[38;5;196m"
#define C_FG_GREEN			"\033[38;5;46m"
#define C_FG_BLUE			"\033[38;5;27m"
#define C_FG_YELLOW			"\033[38;5;226m"
#define C_FG_PURPLE			"\033[38;5;91m"
#define C_FG_PINK			"\033[38;5;200m"
#define C_FG_ORANGE			"\033[38;5;202m"
#define C_FG_AQUA			"\033[38;5;51m"
#define C_FG_DARKRED		"\033[38;5;124m"
#define C_FG_DARKGREEN		"\033[38;5;22m"
#define C_FG_DARKBLUE		"\033[38;5;18m"

#define C_RESET				"\033[0m"
#define C_UNDERSCORE		"\033[2m" //TODO: check code

#else

#define C_BG_WHITE			""
#define C_BG_GRAY			""
#define C_BG_BLACK			""
#define C_BG_RED			""
#define C_BG_GREEN			""
#define C_BG_BLUE			""
#define C_BG_YELLOW			""
#define C_BG_PURPLE			""
#define C_BG_PINK			""
#define C_BG_ORANGE			""
#define C_BG_AQUA			""
#define C_BG_DARKRED		""
#define C_BG_DARKGREEN		""
#define C_BG_DARKBLUE		""

#define C_FG_WHITE			""
#define C_FG_GRAY			""
#define C_FG_BLACK			""
#define C_FG_RED			""
#define C_FG_GREEN			""
#define C_FG_BLUE			""
#define C_FG_YELLOW			""
#define C_FG_PURPLE			""
#define C_FG_PINK			""
#define C_FG_ORANGE			""
#define C_FG_AQUA			""
#define C_FG_DARKRED		""
#define C_FG_DARKGREEN		""
#define C_FG_DARKBLUE		""

#define C_RESET				""
#define C_UNDERSCORE		""

#endif

#endif