/*
   cncvgeom.h

   Отобpажение геометpической инфоpмации станка

   Copyright (c) ELMIS Ltd 1993.

*/

#if !defined(__CNCVGEOM_H)
 #define __CNCVGEOM_H

#define Uses_TWindow
#define Uses_TRect
#define Uses_TEvent

#include <Tv.h>


#if !defined(__CNCRAZ_H)
 #include "cncRaz.h"
#endif

#if !defined(__CNCVGRAP_H)
 #include "cncvGrap.h"
#endif

/*
  CNCWindow обладает свойствами "подписываться" при приходе индивидуальной
  команды откррытия
  ...
*/

class CNCWindow : public TWindow, public GraphObject
{
  void calculateOneToOne();
  void setDefaultGraphics();

 public:

  CNCWindow( const TRect& bounds, const char *aTitle, short aNumber );
  virtual void handleEvent( TEvent& event );
  virtual void mark( TEvent& event )=0;
  virtual void plot() {}
  virtual void drawGraph() {}
  void setOneToOne( Boolean mode );
};

class Geometr : public CNCWindow
{
  long *data;
  long oldData[NUM];

 public:

  Geometr( const TRect& bounds, const char *aTitle,
	   short aNumber, long *geomData=0L );
  virtual const char* getTitle( short maxSize );

};

inline const char* Geometr::getTitle( short maxSize )
{
 return NULL;
}

class AxCurent : public Geometr
{
public:
  AxCurent( const TRect& bounds, const char *aTitle, short aNumber, long *geomData)
   : Geometr( bounds, aTitle, aNumber, geomData ),
     TWindowInit( TWindow::initFrame ) {}

  virtual void mark( TEvent& event );
};

class AxEndPoint : public Geometr
{
public:
  AxEndPoint( const TRect& bounds, const char *aTitle, short aNumber, long *geomData)
   : Geometr( bounds, aTitle, aNumber, geomData ),
     TWindowInit( TWindow::initFrame ) {}

  virtual void mark( TEvent& event );
};

class AxCorrect : public Geometr
{
public:
  AxCorrect( const TRect& bounds, const char *aTitle, short aNumber, long *geomData)
   : Geometr( bounds, aTitle, aNumber, geomData ),
     TWindowInit( TWindow::initFrame ) {}

  virtual void mark( TEvent& event );
};


#endif


