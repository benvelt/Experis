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

#define RESET					"\033[0m"

/* colors */
#define BLACK					"\033[30m"					/* Black */
#define RED						"\033[31m"					/* Red */
#define GREEN					"\033[32m"					/* Green */
#define YELLOW				"\033[33m"					/* Yellow */
#define BLUE					"\033[34m"					/* Blue */
#define MAGENTA				"\033[35m"					/* Magenta */
#define CYAN					"\033[36m"					/* Cyan */
#define WHITE					"\033[37m"					/* White */

/* bold colors */
#define BOLDBLACK			"\033[1m\033[30m"		/* Bold Black */
#define BOLDRED				"\033[1m\033[31m"		/* Bold Red */
#define BOLDGREEN			"\033[1m\033[32m"		/* Bold Green */
#define BOLDYELLOW		"\033[1m\033[33m"		/* Bold Yellow */
#define BOLDBLUE			"\033[1m\033[34m"		/* Bold Blue */
#define BOLDMAGENTA		"\033[1m\033[35m"		/* Bold Magenta */
#define BOLDCYAN			"\033[1m\033[36m"		/* Bold Cyan */
#define BOLDWHITE			"\033[1m\033[37m"		/* Bold White */

/* cards suites symbols */
#define SPADE_SIGN			"\xE2\x99\xA0"
#define CLUB_SIGN			"\xE2\x99\xA3"
#define HEART_SIGN			"\xE2\x99\xA5"
#define DIAMOND_SIGN		"\xE2\x99\xA6"

#endif /*__COLOR_H__*/

