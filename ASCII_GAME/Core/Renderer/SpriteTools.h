#ifndef _SPRITE_TOOLS_H_
#define _SPRITE_TOOLS_H_

#include "ConsoleColours.h"

//const CHAR_INFO PIXEL = { 0 ,BACKGROUND_WHITE };
//const CHAR_INFO& PIXEL_ON = PIXEL;
//const CHAR_INFO PIXEL_OFF = { 0 ,BACKGROUND_BLACK };

inline CHAR_INFO PIXEL_COLORED(unsigned short color)
{
	return { 0, color };
}

extern const CHAR_INFO PIXEL;
extern const CHAR_INFO& PIXEL_ON;
extern const CHAR_INFO PIXEL_OFF;


#endif // !_SPRITE_TOOLS_H_