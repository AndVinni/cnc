/*
   cncvslin.h

   Новый тип стpоки состояния с pеакцией на Shift, Alt, Ctrl.

   Copyright (c) ELMIS ltd 1993.

*/

#ifndef __CNCVSLIN_H
 #define __CNCVSLIN_H

#define Uses_TStatusLine
#define Uses_TStatusDef

#include <Tv.h>

class CNCStatusLine : public TStatusLine
{
 public:

  CNCStatusLine(const TRect& bounds);
  CNCStatusLine(StreamableInit streamableInit);
 ~CNCStatusLine();

  void setShiftStatus() ;
  void setAltStatus();
  void setCtrlStatus();
  void setNormalStatus();

 private:

  TStatusDef *defsShift;
  TStatusDef *defsAlt;
  TStatusDef *defsCtrl;
  TStatusDef *defsNormal;
  TStatusDef& initCNCStatusLine();
  void findItems();
};

inline void CNCStatusLine::setShiftStatus()
{
 defs = defsShift;
 findItems();
 drawView();
}

inline void CNCStatusLine::setCtrlStatus()
{
 defs = defsCtrl;
 findItems();
 drawView();
}

inline void CNCStatusLine::setAltStatus()
{
 defs = defsAlt;
 findItems();
 drawView();
}

inline void CNCStatusLine::setNormalStatus()
{
 defs = defsNormal;
 findItems();
 drawView();
}


#endif
