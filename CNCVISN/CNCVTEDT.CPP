/*
   cncvTedt.h

   Редактоp таблиц

   Copyright (c) ELMIS Ltd 1993.

*/


#pragma hdrfile "cncvtedt.sym"

#define Uses_TKeys
#define Uses_MsgBox

#include<Tv.h>

#if !defined(__STDIO_H)
 #include <Stdio.h>
#endif

#if !defined(__STDLIB_H)
 #include <StdLib.h>
#endif

#if !defined(__STRING_H)
 #include <String.h>
#endif

#if !defined(__MATH_H)
 #include <Math.h>
#endif

#if !defined(__STRSTREAM_H)
 #include <StrStream.h>
#endif

#if !defined(__CTYPE_H)
 #include <cType.h>
#endif

#pragma hdrstop

#if !defined(__CNCVCOM_H)
 #include"cncvCom.h"
#endif

#if !defined(__CNCVTEDT_H)
 #include"cncvTedt.h"
#endif

#if !defined(__CNCVUTIL_H)
 #include"cncvUtil.h"
#endif

#if !defined(__CNCPAR_H)
 #include"cncPar.h"
#endif


void TablList::handleEvent( TEvent& event )
{
 TListViewer::handleEvent( event );
 if( event.what == evBroadcast && event.message.command &&
     event.message.infoPtr == this )
 {
  clearEvent( event );
  message( (TView*)owner, evBroadcast, cmMakeDefault, (void*)(Boolean( True )));
 }
}

TablInputLine::TablInputLine(const TRect& bounds, int aMin, int aMax,
			     int aMaxLen, ushort aCommand, TListViewer *aLink)
	      :TInputLine( bounds, aMaxLen)
{
 link = aLink;
 minData = aMin;
 maxData = aMax;
 previos = 0;
 command = aCommand ? aCommand : cmInputLineEntered;
 eventMask |= evBroadcast;
}

Boolean TablInputLine::valid( ushort aCommand )
{
 if( aCommand == command )
 {
  int inpData;
  if( strlen( data ) )
   inpData = atoi( data );
  else
   inpData = previos;
  if( inpData < minData || inpData > maxData )
  {
   char errStr[128];
   sprintf( errStr,"\003Данные должны бать в пределах от %i до %i!",
	    minData, maxData);
   messageBox( mfError | mfOKButton , errStr );
   selectAll( True );
   return False;
  }
 }
 return True;
}

int TablInputLine::handleData()
{
 if( strlen( data ) )
  previos = atoi( data );
 setData( "" );
 return previos;
}

void TablInputLine::handleEvent( TEvent& event )
{
 TInputLine::handleEvent( event );
 switch( event.what )
 {
  case evBroadcast:
   if(event.message.command == cmReceivedFocus && event.message.infoPtr == this )
   {
    clearEvent( event );
    message( (TView*)owner, evBroadcast, cmMakeDefault, (void*)(Boolean( False )));
   }
  break;
  case evKeyDown:
   if( event.keyDown.keyCode == kbEnter )
   {
    clearEvent( event );
    if( valid( command ) )
     message( (TView*)owner, evBroadcast, command, (void*)handleData() );
   }
  break;
 }
 if( event.what != evNothing )
  link->handleEvent( event );
}

PosInputLine::PosInputLine(const TRect& bounds, float aMin, float aMax,
			   int aMaxLen, ushort aCommand, TListViewer *aLink)
			   :TInputLine( bounds, aMaxLen)
{
 link = aLink;
 minData = aMin;
 maxData = aMax;
 previos = 0.;
 command = aCommand ? aCommand : cmInputLineEntered;
 eventMask |= evBroadcast;
}

Boolean PosInputLine::valid( ushort aCommand )
{
 if( aCommand == command )
 {
  float inpData;
  if( strlen( data ) )
   sscanf( data,"%f", &inpData );
  else
   inpData = previos;
  if( inpData < minData || inpData > maxData )
  {
   char errStr[128];
   sprintf( errStr,"\003Данные должны бать в пределах от %+4.3f до %+4.3f!",
	    minData, maxData);
   messageBox( mfError | mfOKButton , errStr );
   selectAll( True );
   return False;
  }
 }
 return True;
}

float PosInputLine::handleData()
{
 if( strlen( data ) )
  sscanf( data,"%f", &previos );
 setData( "" );
 return previos ;
}

void PosInputLine::handleEvent( TEvent& event )
{
 TInputLine::handleEvent( event );
 switch( event.what )
 {
  case evBroadcast:
   if(event.message.command == cmReceivedFocus && event.message.infoPtr == this )
   {
    clearEvent( event );
    message( (TView*)owner, evBroadcast, cmMakeDefault, (void*)(Boolean( False )));
   }
  break;
  case evKeyDown:
   if( event.keyDown.keyCode == kbEnter )
   {
    clearEvent( event );
    if( valid( command ) )
    {
     union { float fData; long lData; } conv;
     TEvent ev;
     ev.what = evBroadcast;
     ev.message.command = command;
     conv.fData = handleData();
     ev.message.infoLong = conv.lData;
     putEvent( ev );
    }
   }
  break;
 }
 if( event.what != evNothing )
  link->handleEvent( event );
}



FunInputLine::FunInputLine(const TRect& bounds,float aMin, float aMax,
			   int aMaxLen,	ushort aCommand, TListViewer *aLink)
	      :TInputLine( bounds, aMaxLen)
{
 link = aLink;
 minData = aMin;
 maxData = aMax;
 command = aCommand ? aCommand : cmInputLineEntered;
 eventMask |= evBroadcast;
}

Boolean FunInputLine::valid( ushort aCommand )
{
 if( aCommand == command )
 {
  float inpData;
  if( strlen( data ) )
   sscanf( data,"%f",&inpData);
  if( inpData < minData || inpData > maxData )
  {
   char errStr[128];
   sprintf( errStr,"\003Данные должны бать в пределах от %1.2f до %1.2f!",
	    minData, maxData);
   messageBox( mfError | mfOKButton , errStr );
   selectAll( True );
   return False;
  }
 }
 return True;
}

ushort FunInputLine::handleData()
{
 double inpData;
 ushort result;
 if( strlen( data ) )
  sscanf( data,"%lf",&inpData);
 setData( "" );
 result = ushort( ceil( inpData * 1000.)) / 10;
 return result;
}

void FunInputLine::handleEvent( TEvent& event )
{
 TInputLine::handleEvent( event );
 switch( event.what )
 {
  case evBroadcast:
   if(event.message.command == cmReceivedFocus && event.message.infoPtr == this )
   {
    clearEvent( event );
    message( (TView*)owner, evBroadcast, cmMakeDefault, (void*)(Boolean( False )));
   }
  break;
  case evKeyDown:
   if( event.keyDown.keyCode == kbEnter )
   {
    clearEvent( event );
    if( valid( command ) )
    {
     TEvent ev;
     ev.what = evBroadcast;
     ev.message.command = command;
     ev.message.infoWord = handleData();
     putEvent( ev );
    }
   }
  break;
 }
 if( event.what != evNothing )
  link->handleEvent( event );
}

DefaultButton::DefaultButton(const TRect& bounds,
	       const char *aTitle, ushort aCommand,ushort aFlags) :
	       TButton( bounds, aTitle, aCommand, aFlags)
{
 if( (aFlags & bfDefault) != 0 )
  state |= sfDefault;
}

void DefaultButton::handleEvent( TEvent& event)
{
 if( event.what == evBroadcast && event.message.command == cmMakeDefault )
 {
  Boolean makeDef = Boolean( event.message.infoPtr );
  if( makeDef && ((state & sfDefault) != 0 ) )
  {
   flags |= bfDefault;
   amDefault = True;
  }
  else
  {
   flags &= ~bfDefault;
   amDefault = False;
  }
  drawView();
  clearEvent( event );
 }
 else
  TButton::handleEvent( event );
}


AxInputLine::AxInputLine(const TRect& bounds, ushort aCommand, TListViewer *aLink)
	      :TInputLine( bounds, 3 )
{
 link = aLink;
 command = aCommand ? aCommand : cmInputLineEntered;
 eventMask |= evBroadcast;
}

Boolean AxInputLine::valid( ushort aCommand )
{
 if( aCommand == command )
  if( !isAx( data ) && strlen( data ) )
  {
   messageBox( mfError | mfOKButton , "\003Неверно задан адрес оси!" );
   selectAll( True );
   return False;
  }
 return True;
}

ushort AxInputLine::handleData()
{
 register ushort axName = 0;
 if( strlen( data ) )
 {
  axName  = toupper(data[0]);
  axName |= isdigit(data[1]) ? data[1] << 8 : ' ' << 8;
 }
 else
  axName = 0;
 setData( "" );
 return axName;
}

void AxInputLine::handleEvent( TEvent& event )
{
 TInputLine::handleEvent( event );
 switch( event.what )
 {
  case evBroadcast:
   if(event.message.command == cmReceivedFocus && event.message.infoPtr == this )
   {
    clearEvent( event );
    message( (TView*)owner, evBroadcast, cmMakeDefault, (void*)(Boolean( False )));
   }
  break;
  case evKeyDown:
   if( event.keyDown.keyCode == kbEnter )
   {
    clearEvent( event );
    if( valid( command ) )
    {
     TEvent ev;
     ev.what = evBroadcast;
     ev.message.command = command;
     ev.message.infoWord = handleData();
     putEvent( ev );
    }
   }
  break;
 }
 if( event.what != evNothing )
  link->handleEvent( event );
}

VintCorrectorList::VintCorrectorList
 ( const TRect& bounds, TScrollBar *aScrollBar, QParameter &Par ):
 TablList( bounds, 1, 0, aScrollBar)
{
 par = &Par;

 register curInd = 0;
 for( register i = 0 ; i < NUM ; i++ )
 {
  if( _AXCORR & AX(i) )
  {
   indCorr[i] = curInd;
   curInd += _NCOR[i];
  }
  else
   indCorr[i] = _AXCORR & AX(i-1) ? curInd : 0;
 }
 indCorr[i] = _AXCORR & AX(i-1) ? curInd : 0;
 setRange( curInd );
}

void VintCorrectorList::getText( char *dest, short item, short maxLen )
{
 char tabStr[80];
 char axName[3];
 register int  ind = 0;
 register int  locInd = 0;
 register int  corrPlus = 0;
 register int  corrMinus = 0;
 float curPos = 0.;
 QParameter &Par = *par;

 for( register i = 0 ; i < NUM ; i++ )
  if( _AXCORR & AX(i) )					// Включена коррекция?
   if( item >= indCorr[i] && item < indCorr[i+1] )
   {
    axName[0] = (char)_AXADR[i];
    axName[1] = (char)(_AXADR[i]>>8);
    axName[2] = '\0';
    ind = item + 1 ;
    locInd = item - indCorr[i] ;
    corrPlus  = _DCOR[ item << 1 ];
    corrMinus = _DCOR[ ( item << 1 ) + 1 ];
    float stp = _STEP[i] ?
		((float)_STEP[i])  / 1000.:
		((float)_TCORR[i]) / 1000.;
    float sm = (float)locInd * stp;
    curPos = (float)_X0[i] + sm;
    break;
   }

 char pnt[16];
 sprintf( pnt,"%++#4.3f", curPos);
 char rslt[16];
 setmem( rslt, 16, ' ');
 strcpy( rslt+(9-strlen(pnt)) , pnt );

 sprintf(tabStr,
	 "%4u │ %2s=%s │ %+2s %+6d │ %+2s %+6d ",
	 ind,   axName,
		rslt,     axName,
			  corrPlus,   axName, corrMinus );

 strncpy( dest, tabStr, maxLen );
}

void VintCorrectorList::handleEvent( TEvent& event )
{
 TablList::handleEvent( event );
 if( event.what == evBroadcast )
 {
  switch( event.message.command )
  {
   case cmFindTablIndex:
    focusItem( --event.message.infoWord );
    clearEvent( event );
   break;
   case cmInputFirstData:
    saveCorrPlus( event.message.infoInt );
    clearEvent( event );
   break;
   case cmInputSecondData:
    saveCorrMinus( event.message.infoInt );
    clearEvent( event );
   break;
  }
 }
}

void VintCorrectorList::saveCorrPlus( int aData )
{
 QParameter& Par = *par;
 _DCOR[ focused << 1 ] = aData;
 drawView();
}

void VintCorrectorList::saveCorrMinus( int aData )
{
 QParameter& Par = *par;
 _DCOR[ ( focused << 1 ) + 1 ] = aData;
 drawView();
}

MFunctionList::MFunctionList
 ( const TRect& bounds, TScrollBar *aScrollBar, QParameter &Par ):
 TablList( bounds, 1, 0, aScrollBar)
{
 par = &Par;
 setRange( QMF );
}

void MFunctionList::handleEvent( TEvent& event )
{
 TablList::handleEvent( event );
 if( event.what == evBroadcast )
 {
  switch( event.message.command )
  {
   case cmFindTablIndex:
    focusItem( --event.message.infoWord );
    clearEvent( event );
   break;
   case cmInputFirstData:
    saveFunction( event.message.infoWord );
    clearEvent( event );
   break;
  }
 }
}

void MFunctionList::getText( char *dest, short item, short maxLen )
{
 QParameter& Par = *par;
 char src[128];
 sprintf( src, "%3u   │                 M%u.%u", item+1,
	       _VVOSTM[item][0], _VVOSTM[item][1] );
 strncpy( dest, src, maxLen );
}

void MFunctionList::saveFunction( ushort funName )
{
 QParameter& Par = *par;
 _VVOSTM[ focused ][0] = funName / 100 ;
 _VVOSTM[ focused ][1] = funName % 100 ;
 drawView();
}

HardSwitchList::HardSwitchList
 ( const TRect& bounds, TScrollBar *aScrollBar, QParameter &Par ):
 TablList( bounds, 1, 0, aScrollBar)
{
 par = &Par;
 setRange( MAXPOINT );
}

void HardSwitchList::getText( char *dest, short item, short maxLen )
{
 QParameter &Par = *par;
 register int ind = 0;
 char tabStr    [80];
 char axName    [3];
 char PointPlus [10];
 char PointMinus[10];
 char strBuf    [10];
 strBuf[0] = '\0';

 if( _AXSW[item] )
 {
  axName[0] = (char)_AXADR[_AXSW[item]-1];
  axName[1] = (char)(_AXADR[_AXSW[item]-1]>>8);
  axName[2] = '\0';
 }
 else
 {
  axName[0] = ' ';
  axName[1] = ' ';
  axName[2] = '\0';
 }

 ind = item + 1 ;

 strstream str( strBuf, 10, ios::ate );
 str.fill(' ');
 str.width( 9 );
 str.setf( ios::right | ios::showpoint | ios::unitbuf );
 str.setf( ios::fixed, ios::floatfield );
 str.precision(3);

 str << ceil(double(_MINSW[item]))/1000. << ends;
 strcpy( PointMinus, strBuf );

 str.seekp( 0L );
 str.width( 9 );

 str << ceil(double(_MAXSW[item]))/1000. << ends;
 strcpy( PointPlus, strBuf );

 sprintf( tabStr,
	  "  %3u │   %2s  │   %s   │   %s ",
	    ind,  axName,PointMinus,PointPlus );

 strncpy( dest, tabStr, maxLen );
}

void HardSwitchList::handleEvent( TEvent& event )
{
 TablList::handleEvent( event );
 if( event.what == evBroadcast )
 {
  union { float fData; long lData; } conv;
  long res;
  switch( event.message.command )
  {
  case cmFindTablIndex:
   focusItem( --event.message.infoWord );
   clearEvent( event );
  break;
  case cmInputThirdData:
   saveAxName( event.message.infoWord );
   clearEvent( event );
  break;
  case cmInputFirstData:
   conv.lData = event.message.infoLong;
   res = long(conv.fData * 1000.);
   savePointMinus( res );
   clearEvent( event );
  break;
  case cmInputSecondData:
   conv.lData = event.message.infoLong;
   res = long(conv.fData * 1000.);
   savePointPlus( res );
   clearEvent( event );
  }
 }
}

void HardSwitchList::saveAxName( ushort aName)
{
 QParameter& Par = *par;
 for( register i = 0; i < NUM; i++ )
 {
  if( _AXADR[i] == aName )
  {
   _AXSW[ focused ] = i+1;
   drawView();
   return;
  }
  if( !aName )
  {
   _AXSW[ focused ] = 0;
   drawView();
   return;
  }
 }
 messageBox( mfError | mfOKButton , "\003Задан адрес несуществующей оси!" );
}

void HardSwitchList::savePointPlus( long aData )
{
 QParameter& Par = *par;
 _MAXSW[ focused ] = aData;
 drawView();
}

void HardSwitchList::savePointMinus( long aData )
{
 QParameter& Par = *par;
 _MINSW[ focused ] = aData;
 drawView();
}

FixedPointList::FixedPointList
 ( const TRect& bounds, TScrollBar *aScrollBar, QParameter &Par, ushort axInd):
 TablList( bounds, 1, 0, aScrollBar)
{
 par = &Par;
 axIndex = axInd;
 setRange( MAXPOINT );
}

void FixedPointList::getText( char *dest, short item, short maxLen )
{
 QParameter &Par = *par;
 register int ind = 0;
 char tabStr[80];
 char axName[3];
 char Point [10];
 Point[0] = '\0';

 if( _AXADR[axIndex] )
 {
  axName[0] = (char)_AXADR[axIndex];
  axName[1] = (char)(_AXADR[axIndex]>>8);
  axName[2] = '\0';
 }
 else
 {
  axName[0] = ' ';
  axName[1] = ' ';
  axName[2] = '\0';
 }

 ind = item + 1 ;

 strstream str( Point, 10, ios::ate );
 str.fill(' ');
 str.width( 9 );
 str.setf( ios::right | ios::showpoint | ios::unitbuf );
 str.setf( ios::fixed, ios::floatfield );
 str.precision(3);

 str << _IFP[axIndex][item] << ends;

 sprintf( tabStr, " %3u точка оси %2s  │   %s ",
		    ind,            axName,  Point );

 strncpy( dest, tabStr, maxLen );
}

void FixedPointList::handleEvent( TEvent& event )
{
 TablList::handleEvent( event );
 if( event.what == evBroadcast )
 {
  switch( event.message.command )
  {
   case cmFindTablIndex:
    focusItem( --event.message.infoWord );
    clearEvent( event );
   break;
   case cmInputFirstData:
    union { float fData; long lData; } conv;
    conv.lData = event.message.infoLong;
    savePoint( conv.fData );
    clearEvent( event );
   break;
  }
 }
}

void FixedPointList::savePoint( double aData )
{
 QParameter& Par = *par;
 _IFP[axIndex][focused] = aData;
 drawView();
}


