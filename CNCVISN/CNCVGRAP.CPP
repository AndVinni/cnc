/*
   cncvgeom.cpp

   Отобpажение гpафической инфоpмации станка

   Copyright (c) ELMIS Ltd 1993.
*/

#pragma hdrfile "cncvGrap.sym"

#define Uses_TEvent

#include <Tv.h>


#if !defined( __STRING_H )
#include <string.h>
#endif  // __STRING_H

#if !defined( __FSTREAM_H )
#include <fstream.h>
#endif  // __FSTREAM_H

#if !defined( __STRSTREA_H )
#include <strstrea.h>
#endif  // __STRSTREA_H

#if !defined( __IO_H )
#include <io.h>
#endif  // __IO_H

#if !defined(__GRAPHICS_H)
 #include <Graphics.h>
#endif

#pragma hdrstop

#if !defined(__CNCVGRAP_H)
 #include "cncvGrap.h"
#endif

#if !defined(__CNCVCOM_H)
 #include "cncvCom.h"
#endif


Boolean GraphObject::graphActive = False;
char  GraphObject::emptyString[] = "C:\\BC\\BGI\\";
char *GraphObject::bgiPath = emptyString;
int GraphObject::mode = 0;
int GraphObject::driver = DETECT;


GraphObject::GraphObject( const int aDriver, const int aMode )
{
 driverPtr = NULL;
 driverSize = 0;
 staticDrawed = False;
 savedDriver = driver;
 savedMode = mode;
 driver = aDriver;
 mode = aMode;
}

GraphObject::~GraphObject( )
{
 driver = savedDriver;
 mode = savedMode;
}

char GraphObject::driverName[lastDriver][10] =
{
 "CGA",                //  1. CGA
 "CGA",                //  2. MCGA
 "EGAVGA",             //  3. EGA
 "EGAVGA",             //  4. EGA64
 "EGAVGA",             //  5. EGAMONO
 "IBM8514",            //  6. IBM8514
 "HERC",               //  7. HercMono
 "ATT",                //  8. ATT400
 "EGAVGA",             //  9. VGA
 "PC3270"              // 10. PC3270
};

void GraphObject::freeDriverMem()
{
 if (driverPtr != 0)
  delete (char *)driverPtr;
 driverPtr = NULL;
 driverSize = 0;
}

Boolean GraphObject::graphAppLoadDriver( int driverNum )
{
    char fileName[MAXSIZE];
    int handle, ccode;
    ostrstream ss(fileName, MAXSIZE);

    if (driverNum <= lastDriver)
	{
        if (bgiPath[strlen(bgiPath)-1] != '\\')
            strcat(bgiPath,"\\");
        ss << bgiPath << driverName[driver-1] << ".BGI" << ends;

        ifstream f(ss.str(), ios::in|ios::binary);
        if (f)
            {
            handle = f.rdbuf()->fd();
            driverSize = (unsigned int)filelength(handle);
            f.seekg( 0L, ios::beg);
	    if (driverSize < (64 * 1024L - 0xF))
                {
                driverPtr = NULL;
                driverPtr = (DriverPtrFunction) new char[driverSize];
                f.read((char *)driverPtr, ushort(driverSize));
                if (f)
                    {
                    ccode = registerfarbgidriver(driverPtr);
                    if (ccode >= 0)
                        return True;
                    else
                        freeDriverMem();
                    }
                    f.close();
                }
            }
        }
    return False;
}

//------------------------------------------------------------------//
// Init BGI. If loadAtInit is true, try to locate and load driver.  //
// Returns true if LoadAtInit succeeds or is set to False. Does     //
// not "own" bgiPath, but instead is passed a pointer to a string   //
// that is allocated elsewhere. Does not de-allocate bgiPath when   //
// done.                                                            //
//------------------------------------------------------------------//

Boolean GraphObject::graphAppInit( Boolean loadAtInit )
{
 freeDriverMem();
 if ( loadAtInit == True )
 {
  if ( driver == 0 )
   detectgraph(&driver, &mode);
  if ( driver > 0 )
   return graphAppLoadDriver(driver);
  else
   return False;
 }
 return True;
}

void GraphObject::graphAppDone()
{
    if ( graphActive == True )
	closegraph();
    freeDriverMem();
    graphActive = False;
    bgiPath = emptyString;
    driver = DETECT;
    mode = 0;
}

Boolean GraphObject::graphicsStart(void)
{
 if ( graphActive == True )
  return(True);

 initgraph( &driver, &mode, bgiPath );

 if ( driver < 0 )
 {
  graphicsStop();
  return False;
 }
 else
  graphActive = True;
 return True;
}

Boolean GraphObject::graphicsActive(void)
{
 if ( graphActive == True )
  return True;
 else
  return False;
}

void GraphObject::graphicsStop(void)
{
 if ( graphActive == True )
  closegraph();
 graphActive = False;
}

GStaticText::GStaticText( const TRect& bounds, const char *aText,
			  const int aDriver, const int aMode ) :
	     TStaticText( bounds, aText ),
	     GraphObject( aDriver, aMode )
{
 options |= ofPreProcess ;
 eventMask |= evCNCMessage;
}

void GStaticText::handleEvent( TEvent& event )
{
 if( event.what == evCNCMessage )
  switch( event.message.command )
  {
   case cmUpdate:   	drawView(); break;
   case cmUpdateGraph:  drawGraph();break;
   case cmCloseGraphics: staticDrawed = False;
  }
 TStaticText::handleEvent( event );
}

void GStaticText::drawGraph()
{
 if( getState( sfActive ) == True && staticDrawed == False )
 {
  plot();
  staticDrawed = True;
 }
}

void GStaticText::plot()
{
 Boolean center;
 int i, j, l, p, y;
 char s[256];
 char b[256];

 setcolor( getColor(1));
 getText(s);
 l = strlen(s);
 p = 0; y = 0;
 center = False;
 while (y < size.y)
 {
  memset(b,' ',size.x);
  b[size.x]='\0';
  if (p < l)
  {
   if (s[p] == 3)
   {
    center = True;
    ++p;
   }
   i = p;
   do
   {
    j = p;
    while ((p < l) && (s[p] == ' '))
     ++p;
    while ((p < l) && (s[p] != ' ') && (s[p] != '\n'))
     ++p;
   } while ((p < l) && (p < i + size.x) && (s[p] != '\n'));
   if (p > i + size.x)
    if (j > i)
     p = j;
    else
     p = i + size.x;
   if (center == True)
    j = (size.x - p + i) / 2 ;
   else
    j = 0;
   strncpy( b+j, s+i, (p-i));
   while ((p < l) && (s[p] == ' '))
    p++;
   if ((p < l) && (s[p] == '\n'))
   {
    center = False;
    p++;
    if ((p < l) && (s[p] == 10))
     p++;
   }
  }
  outtextxy(0,y++,b);
 }
}


