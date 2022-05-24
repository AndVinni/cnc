/*
   cncvisn.h

   Опpеделение CNCVISION

   Copyright (c) ELMIS ltd 1993.

*/

#if !defined(__CNCVISN_H)
 #define __CNCVISN_H

#define Uses_TObject
#define Uses_TApplication

#include <Tv.h>

#pragma option -po

#if !defined(__CNCVGRAP_H)
 #include"cncvGrap.h"
#endif

class WindowNumerator : public TObject
{
	Boolean activWindow[9];
 public:

	WindowNumerator();
	void reset();
	ushort operator()();
	inline _fastcall void unused( ushort wnum );
};

inline _fastcall void WindowNumerator::unused( ushort wnum)
{
 if( wnum >= 1 && wnum <= 9 )
  activWindow[--wnum] = False;
}

class EditorSet;

class CNCVision : public TApplication, public GraphObject
{
public:

 CNCVision();

 static TStatusLine*   initStatusLine( TRect r );
 static TMenuBar*	  initMenuBar( TRect r );

 virtual void getEvent( TEvent& event);
 virtual void handleEvent( TEvent& event);
 virtual ushort execute();
 virtual void idle();
 virtual void outOfMemory();

 virtual void drawGraph() {}
 virtual void plot() {}

 ushort operator ()(void) { return execute(); }
 WindowNumerator windowNumber;
 EditorSet *ncEditor;

private:

 ushort prevKeyFlag;
 TView * graphDeskTop;

 void tile();
 void cascade();
 void openGraphics();
 void closeGraphics();

 void status();
 void feed();
 void inputLine();
 void calculator();
 void editorQParam();
 void axCurent();
 void axEndPoint();
 void axCorrect();

};

extern CNCVision * cncVisionPtr;

inline ushort Cnc_show()
{
 return (*cncVisionPtr)();
}

inline _fastcall void initCnc_show( CNCVision * cnc )
{
 cncVisionPtr = cnc;
}

#pragma option -po.

#endif



