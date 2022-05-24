/*
   cncvpult.h

   Пульт индикации и упpавления состоянием станка

   Copyright (c) ELMIS ltd 1993.

*/

#if !defined(__CNCVPULT_H)
 #define __CNCVPULT_H

#define Uses_TDialog
#define Uses_TRect
#define Uses_TView

#include <Tv.h>

class ControlPanel : public TDialog
{
 public:
  ControlPanel( TRect bounds, ushort wnum );
};

#endif