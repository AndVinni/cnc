/*
   cncvUtil.cpp

   Опpеделения вспомогательных функций
   pедактоpа Q - паpаметpов.

   Copyright (c) ELMIS Ltd 1993.

*/

#pragma hdrfile "cncvutil.sym"

#define Uses_TView
#define Uses_TLabel
#define Uses_TStaticText
#define Uses_TInputLine
#define Uses_TRadioButtons
#define Uses_TSItem
#define Uses_TCheckBoxes
#define Uses_MsgBox

#include <Tv.h>

#if !defined(__CTYPE_H)
 #include <cType.h>
#endif

#if !defined(__STDLIB_H)
 #include <StdLib.h>
#endif

#if !defined(__STRING_H)
 #include <String.h>
#endif

#pragma hdrstop

#if !defined(__CNCVUTIL_H)
 #include "cncvUtil.h"
#endif

#if !defined(__CNCPAR_H)
 #include "cncPar.h"
#endif

#if !defined(__CNCVTEDT_H)
 #include "cncvTedt.h"
#endif

#if !defined(__CNCVCOM_H)
 #include "cncvCom.h"
#endif

 _setAxData( setAxData,  uchar, int,     "%u",    1, )
 _getAxData( getAxData,  uchar, int,     "%u",    1, )
 _setAxData( setAxData,  int, 	int,     "%i",    2, )
 _getAxData( getAxData,  int, 	int,     "%i",    2, )
 _setAxData( setAxData,  int, 	int,     "%i",    5, )
 _getAxData( getAxData,  int, 	int,     "%i",    5, )
 _setAxData( setuAxData, int,	unsigned,"%u",    5, )
 _getAxData( getuAxData, int, 	unsigned,"%u",    5, )
 _setAxData( setfAxData, int, 	float,   "%2.3f", 6, /1000. )
 _getAxData( getfAxData, int,	float,   "%f", 	  6, *1000. )
 _setAxData( setdAxData, double,float,   "%2.3f", 6, )
 _getAxData( getdAxData, double,float,   "%f",    6, )
 _setAxData( setlAxData, long,  float,   "%+4.3f",9, )
 _getAxData( getlAxData, long, 	float,   "%f",    9, )
 _setAxData( setdAxData, double,float,   "%+4.3f",9, )
 _getAxData( getdAxData, double,float,   "%f",    9, )
 _setAxData( setAxData,  long, 	long,    "%li",   7, )
 _getAxData( getAxData,  long, 	long,    "%li",   7, )
 _setAxData( setAxData,  int, 	int,     "%i",    4, )
 _getAxData( getAxData,  int, 	int,     "%i",    4, )
 _setAxData( setsAxData, int, 	int,     "%i",    6, )
 _getAxData( getsAxData, int, 	int,     "%i",    6, )

 _setShData( setuShData, unsigned,unsigned,"%u",  5, )
 _getShData( getuShData, unsigned,unsigned,"%u",  5, )
 _setShData( setShData,  int,   int,      "%i",   5, )
 _getShData( getShData,  int,   int,      "%i",   5, )
 _setShData( setfShData, int,   float,    "%2.3f",6, /1000. )
 _getShData( getfShData, int,   float,    "%f",   6, *1000. )
 _setShData( setfShData, long,  float,    "%3.3f",7, /1000. )
 _getShData( getfShData, long,  float,    "%f",   7, *1000. )
 _setShData( setiShData, int,   unsigned, "%u",   5, )
 _getShData( getiShData, int,   unsigned, "%u",   5, )

void AxDialog(  QpDisplay& dsp, ushort len )
{
 char txt[128];

 dsp.newSelect = True;
 TRect r( 12-len, 4, 19-len, 5);
 for( register i = 0; i < NUM ; i++, r.a.y++, r.b.y++ )
 {
  if( i == ( NUM/2 ) )
  {
   r.a.x += 16+len; r.b.x += 16+len;
   r.a.y = 4;  r.b.y = 5;
  }
  sprintf( txt, "%u ось", i+1 );
  dsp.insert( new TStaticText(r, txt ));
  dsp.insert( new TInputLine(TRect( r.b.x,r.a.y,r.b.x+len+3,r.b.y),len+1));
 }
}

void FoolAxDialog( QParameter& Par, QpDisplay& dsp, ushort len )
{
 char txt[128];
 dsp.newSelect = True;
 TRect r( 12-len, 4, 19-len, 5);
 char nm[3];

 for( register i = 0; i < NUM ; i++, r.a.y++, r.b.y++ )
 {
  if( i == ( NUM/2 ) )
  {
   r.a.x += 16+len; r.b.x += 16+len;
   r.a.y = 4;  r.b.y = 5;
  }
  nm[0] = (char)_AXADR[i];
  nm[1] = (char)(_AXADR[i] >> 8);
  nm[2] = '\0';
  if( isAx( nm ) )
   sprintf( txt, "Oсь %s", nm );
  else
   sprintf( txt, "%u ось", i+1 );
  dsp.insert( new TStaticText(r, txt ));
  dsp.insert( new TInputLine(TRect( r.b.x,r.a.y,r.b.x+len+3,r.b.y),len+1));
 }
}

void SpindelDialog( QParameter& Par, QpDisplay& dsp, ushort len, Boolean stup )
{
 char txt[128];
 dsp.newSelect = True;
 TRect r = dsp.getExtent();
 int dx = ( r.b.x-r.a.x-2 ) >> 2 ;

 r.a.x += 2;
 r.b.x = r.a.x + len + 3;
 r.a.y += 3;
 r.b.y = r.a.y +1;
 int y = r.a.y;

 char nms[3];

 for( register i = 0; i< NUMS; i++,r.a.x+= dx,r.b.x+=dx,r.a.y=y,r.b.y=y+1 )
 {
  if( isShpindel(_SHADR[i]) )
  {
   nms[0] = (char)_SHADR[i];
   nms[1] = (char)(_SHADR[i]>>8);
   nms[2] = '\0';
  }
  else
   itoa( i+1, nms, 10 );

  if( i == 0 && stup )
   sprintf( txt, "№с %s", nms );
  else
   sprintf( txt, " %s", nms );
  dsp.insert( new TStaticText(r, txt ));
  r.a.y++; r.b.y++;
  for( register j = 0; j < MAXST ; j++, r.a.y++, r.b.y++ )
  {
   if( i == 0 && stup )
   {
    itoa( j+1, txt, 10 );
    dsp.insert( new TStaticText( TRect(r.a.x,r.a.y,r.b.x-len,r.b.y), txt ) );
   }
   TView *il = new TInputLine( TRect(r.a.x+1,r.a.y,r.b.x+1,r.b.y), len+1 );
   if( stup && j+1 > _SNSTUP[i] )
    il->hide();
   if( !stup && j )
    il->hide();
   dsp.insert( il );
  }
 }
}

void LogAxDialog( QParameter& Par, QpDisplay& dsp )
{
 char txt[128];
 TRect r( 30, 1, 46, 1+NUM );
 TSItem *itm = 0;
 char nm[3];

 for( register i = NUM-1 ; i >= 0 ; i-- )
 {
  nm[0] = (char)_AXADR[i];
  nm[1] = (char)(_AXADR[i] >> 8);
  nm[2] = '\0';
  if( isAx( nm ) )
   sprintf( txt, "Oсь %s", nm );
  else
   sprintf( txt, "%u ось", i+1 );
  itm = new TSItem( txt , itm );
 }
 dsp.insert( new TCheckBoxes( r, itm ));
}

void LogShDialog( QParameter& Par, QpDisplay& dsp )
{
 char txt[128];
 TRect r( 20, 5, 36, 5+NUMS );
 TSItem *itm = 0;

 for( register i = NUMS-1 ; i >= 0 ; i-- )
 {
  if( isShpindel( _SHADR[i] ) )
    sprintf( txt, "шпинд.%c%c", (char)(_SHADR[i]), (char)(_SHADR[i]>>8) );
  else
    sprintf( txt, "%u шпинд.", i+1 );

  itm = new TSItem( txt , itm );
 }
 dsp.insert( new TCheckBoxes( r, itm ));
}

void FoolLogShDialog( QParameter& Par, QpDisplay& dsp )
{
 char txt[128];
 ushort len = 8;
 char nms[3];

 TRect r = dsp.getExtent();
 int dx = ( r.b.x-r.a.x-2 ) >> 2 ;
 r.a.x += 2;
 r.b.x = r.a.x + len + 3;
 r.a.y += 3;
 r.b.y = r.a.y +1;
 int y = r.a.y;

 for( register i = 0; i< NUMS; i++,r.a.x+= dx,r.b.x+=dx,r.a.y=y,r.b.y=y+1 )
 {
  TSItem *itm = 0;
  if( isShpindel(_SHADR[i]) )
  {
   nms[0] = (char)_SHADR[i];
   nms[1] = (char)(_SHADR[i]>>8);
   nms[2] = '\0';
  }
  else
   itoa( i+1, nms, 10 );
  sprintf( txt, " %s", nms );
  dsp.insert( new TStaticText(r, txt ));
  r.a.y++; r.b.y++;
  for( register j = MAXST-1; j >= 0 ; j-- )
  {
   if( j+1 > _SNSTUP[i] )
    strcpy( txt, "      " );
   else
    sprintf( txt,"%u ст. ", j+1 );
   itm = new TSItem( txt , itm );
  }
  dsp.insert( new TCheckBoxes( TRect(r.a.x,y+1,r.b.x,y+1+MAXST ), itm ));
 }
}

Boolean isAx( char * name )
{
 const char * defName = "XYZABCUVWT";
 register i = 0;

 if( isalpha( name[0] ) )			// Стоит ли пpовеpять имя оси?
 {
  while( defName[i] != '\0' )
  {                                             // Пpовеpка имени на коppектность
   if( toupper( name[0] ) == defName[i] &&
       ( ( name[1] == ' ') || ( name[1] == '\0' ) || isdigit( name[1]) )
     )
    return True;
   i++;
  }
  return False;
 }
 else
  return False;
}

Boolean isShpindel( int name )
{
 if( isalpha( (char)name ) )			// Стоит ли пpовеpять имя оси?
 {
  char second = (char)( name >> 8 );
  if( toupper( (char)name ) == 'S' &&
     ((  second == ' ') || ( second == '\0' ) || isdigit( second ))
    )
   return True;
  else
   return False;
 }
 else
  return False;
}

 Boolean isNotUsed( char *name )
{
 if( ( name[0] == ' ' || name[0] == '\0' ) &&
     ( name[1] == ' ' || name[1] == '\0' )
   )
  return True;
 else
  return False;
}

Boolean testAxName( TGroup *dlg )
{
 dlgData(NUM,2) nm;
 Boolean control = True;

 dlg->TGroup::getData( &nm.dat );
 for( register ushort i = 0; i < NUM; i++ )
 {
  if( !isAx( nm.dat[i] ) && !isNotUsed( nm.dat[i] ) )
  {
   char msg[128];
   sprintf( msg, "\x003Невеpное имя %u оси.", i+1);
   messageBox( mfError | mfOKButton , msg );
   control =  False;
  }
 }
 register ushort j;
 for( i = 0; i < NUM ; i++)
  for( j = 0 ; j < NUM ; j++ )
  {
   if( i != j && isAx( nm.dat[i] ) && isAx( nm.dat[j] ) )
    if( !( isNotUsed( nm.dat[i] ) && isNotUsed( nm.dat[j] )) )
     if( strncmpi( nm.dat[i], nm.dat[j], 2 ) == 0 )
     {
      char msg[128];
      sprintf( msg, "\x003Совпадают адpеса %u и %u осей.", i+1, j+1 );
      messageBox( mfError | mfOKButton , msg );
      control =  False;
      goto end;
     }
  }
 end:
 return control;
}

void getAxName( int *data, TGroup *dlg )
{
 dlgData(NUM,2) nm;
 dlg->TGroup::getData( &nm );
 for( register i = 0; i < NUM; i++ )
 {
  if( !isdigit(nm.dat[i][1]) ) nm.dat[i][1]=' ';
  data[i] = toupper( nm.dat[i][0]) | ( nm.dat[i][1] << 8 );
 }
}

void setAxName( int *data, TGroup *dlg )
{
 dlgData(NUM,2) nm;
 for( register i = 0; i < NUM; i++ )
 {
  nm.dat[i][0] = ( char )data[i];
  nm.dat[i][1] = ( char )( ( data[i] == ' ' ? '\0' : data[i] ) >> 8);
  nm.dat[i][2] = '\0';
 }
 dlg->TGroup::setData( &nm );
}

void getShName( int *data, TGroup *dlg )
{
 shData(2) nm;
 dlg->TGroup::getData( &nm );
 for( register i = 0 ; i < NUMS; i++ )
 {
  if( !isdigit(nm.dat[i][0][1]) ) nm.dat[i][0][1] = ' ';
  data[i] = toupper( nm.dat[i][0][0]) | ( nm.dat[i][0][1] << 8 );
 }
}

void setShName( int *data, TGroup *dlg )
{
 shData(2) nm;
 for( register i = 0 ; i < NUMS; i++ )
 {
  nm.dat[i][0][0] = ( char )data[i];
  nm.dat[i][0][1] = ( char )( (data[i] == ' '? '\0': data[i] ) >> 8);
  nm.dat[i][0][2] = '\0';
 }
 dlg->TGroup::setData( &nm );
}

void numPortDialog( char *header, QpDisplay& dsp )
{
 TRect r( 19, 5, 26, 9 );
 TView *rb = new TRadioButtons( r, new TSItem( "1",
				   new TSItem( "2",
				   new TSItem( "3",
				   new TSItem( "4", 0 )))) );
 TView *lb = new TLabel( TRect( r.a.x-16, r.a.y, r.b.x-10, r.b.y-3 ), "~Н~омер порта", rb );
 TView *tx = new TStaticText( TRect( r.a.x-12, r.a.y-3, r.b.x+12, r.b.y-4 ),
		 header );
 dsp.insert( rb );
 dsp.insert( lb );
 dsp.insert( tx );
}

void portDialog( char *header, QpDisplay& dsp )
{
 TView *tx = new TStaticText( TRect( 10, 1, 40, 3 ), header );
 dsp.insert( tx );
 TView *rb = new TRadioButtons( TRect( 2, 5, 10, 9 ),
				new TSItem( "1",
				new TSItem( "2",
				new TSItem( "3",
				new TSItem( "4", 0 )))) );
 TView *lb = new TLabel( TRect( 2, 4, 10, 5 ), "№ ~п~орта", rb );
 dsp.insert( rb );
 dsp.insert( lb );
 rb = new TRadioButtons( TRect( 11, 5, 18, 9 ),
			 new TSItem( "5",
			 new TSItem( "6",
			 new TSItem( "7",
			 new TSItem( "8", 0 )))) );
 lb = new TLabel( TRect( 11, 4, 18, 5 ), "Б~и~т", rb );
 dsp.insert( rb );
 dsp.insert( lb );
 rb = new TRadioButtons( TRect( 19, 5, 26, 7 ),
			 new TSItem( "1",
			 new TSItem( "2", 0 )) );
 lb = new TLabel( TRect( 19, 4, 26, 5 ), "С~т~оп", rb );
 dsp.insert( rb );
 dsp.insert( lb );
 rb = new TRadioButtons( TRect( 27, 5, 37, 10 ),
			 new TSItem( "Чет",
			 new TSItem( "Нечет",
			 new TSItem( "1",
			 new TSItem( "0",
			 new TSItem( "Нет", 0 ))))) );
 lb = new TLabel( TRect( 27, 4, 37, 5 ), "~К~онтроль", rb );
 dsp.insert( rb );
 dsp.insert( lb );
 rb = new TRadioButtons( TRect( 38, 5, 50, 17 ),
			 new TSItem( "75",
			 new TSItem( "110",
			 new TSItem( "300",
			 new TSItem( "600",
			 new TSItem( "1200",
			 new TSItem( "2400",
			 new TSItem( "4800",
			 new TSItem( "9600",
			 new TSItem( "19200",
			 new TSItem( "38400",
			 new TSItem( "57600",
			 new TSItem( "115200", 0 )))))))))))) );
 lb = new TLabel( TRect( 38, 4, 50, 5 ), "~С~корость", rb );
 dsp.insert( rb );
 dsp.insert( lb );
}

void NameProg( QpDisplay& dsp, ushort len )
{
 char txt[128];

 dsp.newSelect = True;
 TRect r( 12-len, 4, 14-len, 5);
 for( register i = 0; i < QGM ; i++, r.a.y++, r.b.y++ )
 {
  if( i == ( QGM/2 ) )
  {
   r.a.x += 16+len; r.b.x += 16+len;
   r.a.y = 4;  r.b.y = 5;
  }
  sprintf( txt, "%u", i+1 );
  dsp.insert( new TStaticText(r, txt ));
  dsp.insert( new TInputLine(TRect( r.b.x,r.a.y,r.b.x+len+3,r.b.y),len+1));
 }
}

void FixedPointDialog( QParameter& Par, QpDisplay& dsp, ushort axIndex )
{
 TRect r = dsp.getExtent();
 r.a.y += 3;
 r.b.y -= 6;
 r.b.x -= 2;
 r.a.x = r.b.x -1 ;
 TScrollBar *sb = new TScrollBar(r);
 dsp.insert( sb );

 r = dsp.getExtent();
 r.a.y += 3;
 r.b.y -= 6;
 r.b.x -= 3;
 r.a.x += 3 ;
 dsp.insert( new TStaticText( TRect(r.a.x,r.a.y-1,r.b.x,r.a.y),
		 "    № точки         │     Координата ") );
 TListViewer *tl = new FixedPointList( r, sb, Par, axIndex );
 dsp.insert( tl );

 r.a.y += 11;
 r.b.y += 2;
 r.a.x += 2;
 r.b.x = r.a.x+6;
 TInputLine *il = new TablInputLine( r, 1, MAXPOINT, 3, cmFindTablIndex, tl );
 dsp.insert( il );

 r.a.y--; r.b.y--;
 dsp.insert( new TLabel(r, "~П~оиск", il ) );

 r.a.y++; r.b.y++;
 r.a.x = 26;
 r.b.x = 38;
 il = new PosInputLine( r, -9999.999, +9999.999, 10, cmInputFirstData, tl );
 dsp.insert( il );

 r.a.y--; r.b.y--;
 dsp.insert( new TLabel(r, "~З~начение", il ) );

 r.a.y++; r.b.y++;
 r.a.x = 2;
 r.b.x = 24;
 r.a.y = 1;
 r.b.y = 2;
 dsp.insert( new TLabel(r, "~Ф~иксированные точки", tl ) );
}





