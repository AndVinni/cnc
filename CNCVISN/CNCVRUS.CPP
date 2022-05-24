/*
   cncvrus.cpp

   Руссификация пpогpамм с доpаботанным TVISION

   Copyright (c) ELMIS ltd 1993.
*/

#pragma hdrfile "cncvrus.sym"

#include <tv.h>

#pragma hdrstop

// Инициализация Alt-кодов доpаботанного под национальный алфавит TVISION

void initRusCodes(void)
{
 initNationalCodes("ЙЦУКЕНГШЩЗ\0\0\0\0ФЫВАПРОЛД\0\0\0\0\0ЯЧСМИТЬ");
}

