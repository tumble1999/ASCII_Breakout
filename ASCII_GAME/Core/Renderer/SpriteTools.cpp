#include "SpriteTools.h"


//fixes Linker Tools Error LNK2005 : https://docs.microsoft.com/en-us/cpp/error-messages/tool-errors/linker-tools-error-lnk2005?f1url=https%3A%2F%2Fmsdn.microsoft.com%2Fquery%2Fdev15.query%3FappId%3DDev15IDEF1%26l%3DEN-US%26k%3Dk(LNK2005)%26rd%3Dtrue
const CHAR_INFO PIXEL = PIXEL_COLORED(BACKGROUND_WHITE);
const CHAR_INFO& PIXEL_ON = PIXEL;
const CHAR_INFO PIXEL_OFF = PIXEL_COLORED(BACKGROUND_BLACK);
