/*
   cncvTedt.h

   Редактоp таблиц

   Copyright (c) ELMIS Ltd 1993.

*/
#if !defined( __CNCVTEDT_H )
 #define __CNCVTEDT_H

#define Uses_TListViewer
#define Uses_TEvent
#define Uses_TInputLine
#define Uses_TButton

#include <Tv.h>

#if !defined( __CNCPARD_H )
 #include "cncPard.h"
#endif


class TablList : public TListViewer
{
public:

 TablList::TablList(const TRect& bounds, ushort aNumCols,
		    TScrollBar *aHScrollBar, TScrollBar *aVScrollBar):
	   TListViewer( bounds, aNumCols, aHScrollBar, aVScrollBar ){}

 virtual void handleEvent( TEvent& event );
};

class TablInputLine : public TInputLine
{
 TListViewer *link;
 int minData;
 int maxData;
 int previos;
 ushort command;
public:

 TablInputLine(const TRect& bounds, int min, int max,
	       int aMaxLen, ushort aCoomand, TListViewer *aLink);

 virtual void handleEvent( TEvent& event );
 virtual Boolean valid( ushort aCommand );
 int handleData();
};

class PosInputLine : public TInputLine
{
 TListViewer *link;
 float minData;
 float maxData;
 float previos;
 ushort command;

public:

 PosInputLine(const TRect& bounds, float min, float max,
	      int aMaxLen, ushort aCoomand, TListViewer *aLink);

 virtual void handleEvent( TEvent& event );
 virtual Boolean valid( ushort aCommand );
 float handleData();
};


class FunInputLine : public TInputLine
{
 TListViewer *link;
 float minData;
 float maxData;
 ushort command;

public:

 FunInputLine(const TRect& bounds, float min, float max,
	       int aMaxLen, ushort aCoomand, TListViewer *aLink);

 virtual void handleEvent( TEvent& event );
 virtual Boolean valid( ushort aCommand );
 ushort handleData();
};

class AxInputLine : public TInputLine
{
 TListViewer *link;
 ushort command;
public:

 AxInputLine(const TRect& bounds, ushort aCoomand, TListViewer *aLink);

 virtual void handleEvent( TEvent& event );
 virtual Boolean valid( ushort aCommand );
 ushort handleData();
};

class DefaultButton : public TButton
{
 public:

 DefaultButton(const TRect& bounds, const char *aTitle, ushort aCommand,ushort aFlags);

 virtual void handleEvent( TEvent& event);
};

class VintCorrectorList : public TablList
{
 int indCorr[NUM+1];
 QParameter *par;

 void saveCorrPlus( int aData);
 void saveCorrMinus( int aData);

public:

 VintCorrectorList( const TRect& bounds, TScrollBar *aScrollbar, QParameter &Par );

 virtual void handleEvent( TEvent& event );
 virtual void getText( char *dest, short item, short maxLen );

};

class MFunctionList : public TablList
{
 QParameter *par;
 void saveFunction( ushort funName );

public:

 MFunctionList( const TRect& bounds, TScrollBar *aScrollbar, QParameter &Par );

 virtual void handleEvent( TEvent& event );
 virtual void getText( char *dest, short item, short maxLen );

};

class HardSwitchList : public TablList
{
 QParameter *par;
 void saveAxName( ushort aName);
 void savePointPlus( long aData);
 void savePointMinus( long aData);

public:

 HardSwitchList( const TRect& bounds, TScrollBar *aScrollbar, QParameter &Par );

 virtual void handleEvent( TEvent& event );
 virtual void getText( char *dest, short item, short maxLen );

};


class FixedPointList : public TablList
{
 QParameter *par;
 ushort axIndex;
 void savePoint( double aData);

public:

 FixedPointList( const TRect& bounds, TScrollBar *aScrollbar,
		 QParameter &Par, ushort axInd );

 virtual void handleEvent( TEvent& event );
 virtual void getText( char *dest, short item, short maxLen );

};


#endif
