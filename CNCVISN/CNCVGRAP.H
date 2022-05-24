/*
   cncvgrap.h

   Отобpажение гpграфической инфоpмации станка

   Copyright (c) ELMIS Ltd 1993.

*/

#if !defined(__CNCVGRAP_H)
 #define __CNCVGRAP_H

#define Uses_TStaticText

#include <Tv.h>

#if !defined(__GRAPHICS_H)
 #include<Graphics.h>
#endif

#if !defined(__CNCVCOM_H)
 #include"cncvCom.h"
#endif


typedef void (*DriverPtrFunction)();
typedef void(*function)();

const MAXSIZE = 80;
const int lastDriver = 10;

class GraphObject
{

 static Boolean graphActive;
 static char  	emptyString[];
 static char *	bgiPath;
 static char driverName[lastDriver][10];
 static int mode;
 static int driver;

 DriverPtrFunction driverPtr;
 unsigned int 	   driverSize;
 int savedDriver;
 int savedMode;

 void graphAppDone(void);

 void freeDriverMem();
 Boolean graphAppLoadDriver( int driverNum );

protected:

 Boolean staticDrawed;
 Boolean graphicsStart(void);
 Boolean graphAppInit( Boolean loadAtInit );
 void graphicsStop(void);

public:

 GraphObject( const int aDriver = DETECT, const int aMode = 0 );
 ~GraphObject();
 Boolean graphicsActive(void);
 virtual void drawGraph() = 0;	// Программируются условие рисования
 virtual void plot() = 0;       // Непосредственно рисование
};

class GStaticText : public TStaticText, public GraphObject
{
public:
 GStaticText( const TRect& bounds, const char *aText,
	      const int aDriver, const int aMode);
  virtual void handleEvent( TEvent& event );
  virtual void drawGraph();
  virtual void plot();
};

#endif


