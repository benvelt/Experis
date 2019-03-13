/**
 * @file color.h
 * @brief Defines all of the ANSI terminal escape codes that modify the color of text.
 */
 
/*
#define NORMAL          "\x1B[0m"
#define BLACK           "\x1b[30m"
#define RED             "\x1B[31m"
#define GREEN           "\x1B[32m"
#define YELLOW          "\x1B[33m"
#define BLUE            "\x1B[34m"
#define MAGENTA         "\x1B[35m"
#define CYAN            "\x1B[36m"
#define WHITE           "\x1B[37m"
#define GRAY            "\x1b[90m"
*/

#ifndef __COLOR_H__
#define __COLOR_H__

#define CLEAR_SCREEN			"\033[H\033[J"

#define RESET					"\033[0m"
#define UNDER_LINE				"\033[04m"
#define BLINK					"\033[05m"
#define REVERSE					"\033[07m"
#define HIDDEN					"\033[08m"
#define DIM						"\033[02m"
#define BOLD					"\033[1m"

/* colors */
#define BLACK					"\033[30m"					/* Black */
#define RED						"\033[31m"					/* Red */
#define GREEN					"\033[32m"					/* Green */
#define YELLOW					"\033[33m"					/* Yellow */
#define BLUE					"\033[34m"					/* Blue */
#define MAGENTA					"\033[35m"					/* Magenta */
#define CYAN					"\033[36m"					/* Cyan */
#define WHITE					"\033[37m"					/* White */

/* bold colors */
#define BOLDBLACK			"\033[1m\033[30m"		/* Bold Black */
#define BOLDRED				"\033[1m\033[31m"		/* Bold Red */
#define BOLDGREEN			"\033[1m\033[32m"		/* Bold Green */
#define BOLDYELLOW			"\033[1m\033[33m"		/* Bold Yellow */
#define BOLDBLUE			"\033[1m\033[34m"		/* Bold Blue */
#define BOLDMAGENTA			"\033[1m\033[35m"		/* Bold Magenta */
#define BOLDCYAN			"\033[1m\033[36m"		/* Bold Cyan */
#define BOLDWHITE			"\033[1m\033[37m"		/* Bold White */

#define BG_BLACK			"\033[40m"
#define BG_RED				"\033[41m"
#define BG_GREEN			"\033[42m"
#define BG_YELLO			"\033[43m"
#define BG_BLUE				"\033[44m"
#define BP_PURPLE			"\033[45m"
#define BG_CYAN				"\033[46m"
#define BG_WHITE			"\033[47m"
#define BG_BOLD_BLACK		"\033[40;01m"
#define BG_BOLD_RED			"\033[41;01m"
#define BG_BOLD_GREEN		"\033[42;01m"
#define BG_BOLD_YELLOW		"\033[43;01m"
#define BG_BOLD_BLUE		"\033[44;01m"
#define BG_BOLD_PURPLE		"\033[45;01m"
#define BG_BOLD_CYAN		"\033[46;01m"
#define BG_BOLD_WHITE		"\033[47;01m"

#define BG_DIM_BLACK		"\033[40;02m"
#define BG_DIM_RED			"\033[41;02m"
#define BG_DIM_GREEN		"\033[42;02m"
#define BG_DIM_YELLOW		"\033[43;02m"
#define BG_DIM_BLUE		"\033[44;02m"
#define BG_DIM_PURPLE		"\033[45;02m"
#define BG_DIM_CYAN		"\033[46;02m"
#define BG_DIM_WHITE		"\033[47;02m"


/* cards suites symbols */
#define SPADE_SIGN			"\xE2\x99\xA0"
#define CLUB_SIGN			"\xE2\x99\xA3"
#define HEART_SIGN			"\xE2\x99\xA5"
#define DIAMOND_SIGN		"\xE2\x99\xA6"

#endif /*__COLOR_H__*/

