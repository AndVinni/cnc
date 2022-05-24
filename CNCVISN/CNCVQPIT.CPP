/*
   cncvQpit.h

   Опpеделения методов классов создателей панелей диалога
   pедактиpования Q - паpаметpов.

   Copyright (c) ELMIS Ltd 1993.

*/

#pragma hdrfile "cncvqpit.sym"

#define Uses_TRadioButtons
#define Uses_TStaticText
#define Uses_TLabel
#define Uses_TCheckBoxes
#define Uses_TSItem
#define Uses_MsgBox

#include <Tv.h>

#if !defined( __STDIO_H )
 #include <Stdio.h>
#endif  // __STDIO_H

#if !defined( __STDLIB_H )
 #include <StdLib.h>
#endif  // __STDLIB_H

#if !defined( __CTYPE_H )
 #include <CType.h>
#endif  // __CTYPE_H

#if !defined( __STRING_H )
 #include <String.h>
#endif  // __STRING_H

#if !defined( __VALUES_H )
 #include <Values.h>
#endif  // __VALUES_H

#if !defined( __MATH_H )
 #include <Math.h>
#endif  // __MATH_H

#if !defined( __IOSTREAM_H )
 #include <IoStream.h>
#endif  // __IOSTREAM_H

#if !defined( __STRSTREAM_H )
 #include <StrStream.h>
#endif  // __STRSTREAM_H

#pragma hdrstop

#if !defined( __CNCPAR_H )
 #include "cncPar.h"
#endif

#if !defined( __CNCVCOM_H )
 #include "cncvCom.h"
#endif

#if !defined( __CNCVETDT_H )
 #include "cncvTedt.h"
#endif

#if !defined( __CNCVQPIT_H )
 #include "cncvQpIt.h"
#endif

#if !defined( __CNCVUTIL_H )
 #include "cncvUtil.h"
#endif

#pragma warn -par

char * const Q100::title = "Q100";

void Q100::createDialog( QParameter& Par, QpDisplay& dsp )
{
 AxDialog( dsp, 2);
}

void Q100::getData( QParameter& Par, TGroup *dlg )
{
 getAxName( _AXADR, dlg );
}

void Q100::setData( QParameter& Par, TGroup *dlg )
{
 setAxName( _AXADR, dlg );
}

Boolean Q100::valueTest( TGroup *dlg )
{
 return testAxName( dlg );
}

char * const Q110::title = "Q110";

void Q110::createDialog( QParameter& Par, QpDisplay& dsp )
{
 char str[128];
 TRect r( 20, 6, 27, 7 );
 TView *il, *ptrIl;
 dsp.newSelect = True;

 for( register i = 0 ; i < KMUP; i++, r.a.y++, r.b.y++ )
 {
  il =  new TInputLine( r, 5 );
  dsp.insert( il );
  if( !i )
   ptrIl = il;
  sprintf( str,"%d МУП", i+1 );
  dsp.insert( new TStaticText( TRect( r.a.x-8, r.a.y, r.b.x-10, r.b.y ), str ));
 }
 dsp.insert( new TLabel( TRect( r.a.x-2, r.a.y-6, r.b.x+11, r.b.y-6 ),
		 "~А~дреса МУПов:" , ptrIl ) );
}

void Q110::getData( QParameter& Par, TGroup *dlg )
{
 char data[KMUP][5];
 dlg->TGroup::getData( data );
 for( register i = 0 ; i < KMUP; i++ )
  sscanf( data[i], "%X", &_ADRMUP[i] );
}

void Q110::setData( QParameter& Par, TGroup *dlg )
{
 char data[KMUP][5];
 for( register i = 0 ; i < KMUP; i++ )
  sprintf( data[i], "%X", _ADRMUP[i] );
 dlg->TGroup::setData( data );
}

Boolean Q110::valueTest( TGroup *dlg )
{
 return True;
}

char * const Q120::title = "Q120";

void Q120::createDialog( QParameter& Par, QpDisplay& dsp )
{
 FoolAxDialog( Par, dsp, 2);
}

void Q120::getData( QParameter& Par, TGroup *dlg )
{
 getAxData2( _NO, dlg );
 for(register i = 0; i < NUM ; i++ )
  if( _NO[i] )
   _NO[i]--;
}

void Q120::setData( QParameter& Par, TGroup *dlg )
{
 for( register i = 0; i < NUM ; i++ )
  if( isAx( (char*)&_AXADR[i] ) )
   _NO[i]++;
 setAxData2( _NO, dlg );
 for( i = 0; i < NUM ; i++ )
  if( _NO[i] ) _NO[i]--;
}

Boolean Q120::valueTest( TGroup *dlg )
{
 dlgData(NUM, 2) d;
 int data[NUM];
 dlg->TGroup::getData( &d );
 for( register i = 0; i < NUM; i++ )
 {
  data[i] = atoi( d.dat[i] );
  if( data[i] > NUM || ( isAx((char*)&_AXADR[i]) && !data[i] ) )
  {
   char msg[128];
   sprintf( msg, "\x003Непpавильный номеp физической оси для %u-й логической.", i+1);
   messageBox( mfError | mfOKButton , msg );
   return False;
  }
 }
 register j;
 for( i = 0; i < NUM ; i++)
  for( j = 0 ; j < NUM ; j++ )
  {
   if( i != j && data[i] && data[j] )
    if( data[i] == data[j] )
    {
     char msg[128];
     sprintf( msg, "\x003Логические оси %u и %u ссылаются на одну и туже физическую.", i+1, j+1 );
     messageBox( mfError | mfOKButton , msg );
     return False;
    }
  }
 return True;
}

char * const Q130::title = "Q130";

void Q130::createDialog( QParameter& Par, QpDisplay& dsp )
{
 FoolAxDialog( Par, dsp, 1);
}

void Q130::getData( QParameter& Par, TGroup *dlg )
{
 getAxData1( _AXF, dlg );
}

void Q130::setData( QParameter& Par, TGroup *dlg )
{
 setAxData1( _AXF, dlg );
}

Boolean Q130::valueTest( TGroup *dlg )
{
 dlgData(NUM,1) d;
 int data[NUM];

 dlg->TGroup::getData( &d );
 for( register i = 0; i < NUM; i++ )
 {
  data[i] = atoi( d.dat[i] );
  if( data[i] < 0 || data[i] > 3  || ( isAx((char*)&_AXADR[i]) && !isdigit(d.dat[i][0] )))
  {
   char msg[128];
   sprintf( msg, "\x003Непpавильный фоpмат %u оси.", i+1);
   messageBox( mfError | mfOKButton , msg );
   return False;
  }
 }
 return True;
}

char * const Q140::title = "Q140";

void Q140::createDialog( QParameter& Par, QpDisplay& dsp )
{
 FoolAxDialog( Par, dsp, 1);
}

void Q140::getData( QParameter& Par, TGroup *dlg )
{
 getAxData1( _AXTYPE, dlg );
}

void Q140::setData( QParameter& Par, TGroup *dlg )
{
 setAxData1( _AXTYPE, dlg );
}

Boolean Q140::valueTest( TGroup *dlg )
{
 dlgData(NUM,1) d;
 int data[NUM];

 dlg->TGroup::getData( &d );
 for( register i = 0; i < NUM; i++ )
 {
  data[i] = atoi( d.dat[i] );
  if( ( isAx((char*)&_AXADR[i]) && data[i] <= atNoType )
      || data[i] > atShpindel )
  {
   char msg[128];
   sprintf( msg, "\x003Непpавильный тип %u оси.", i+1);
   messageBox( mfError | mfOKButton , msg );
   return False;
  }
 }
 return True;
}

char * const Q145::title = "Q145";

void Q145::createDialog( QParameter& Par, QpDisplay& dsp )
{
 LogAxDialog( Par, dsp );
}

void Q145::getData( QParameter& Par, TGroup *dlg )
{
 dlg->TGroup::getData( &_AXSYN );
}

void Q145::setData( QParameter& Par, TGroup *dlg )
{
 dlg->TGroup::setData( &_AXSYN );
}

Boolean Q145::valueTest( TGroup *dlg )
{
 return True;
}

char * const Q150::title = "Q150";

void Q150::createDialog( QParameter& Par, QpDisplay& dsp )
{
 FoolAxDialog( Par, dsp, 6 );
}

void Q150::getData( QParameter& Par, TGroup *dlg )
{
}

void Q150::setData( QParameter& Par, TGroup *dlg )
{
}

Boolean Q150::valueTest( TGroup *dlg )
{
 return True;
}

char * const Q160::title = "Q160";

void Q160::createDialog( QParameter& Par, QpDisplay& dsp )
{
 FoolAxDialog( Par, dsp, 7 );
}

void Q160::getData( QParameter& Par, TGroup *dlg )
{
 getAxData7( _STEPD, dlg );
}

void Q160::setData( QParameter& Par, TGroup *dlg )
{
 setAxData7( _STEPD, dlg );
}

Boolean Q160::valueTest( TGroup *dlg )
{
 dlgData(NUM,7) d;
 long data[NUM];

 dlg->TGroup::getData( &d );
 for( register i = 0; i < NUM; i++ )
 {
  data[i] = atol( d.dat[i] );
  if( data[i] < -1L || data[i] > 9999999L )
  {
   char msg[128];
   sprintf( msg, "\x003Непpавильно задан шаг %u оси.", i+1);
   messageBox( mfError | mfOKButton , msg );
   return False;
  }
 }
 return True;
}

char * const Q170::title = "Q170";

void Q170::createDialog( QParameter& Par, QpDisplay& dsp )
{
 FoolAxDialog( Par, dsp, 5 );
}

void Q170::getData( QParameter& Par, TGroup *dlg )
{
 getAxData5( _NIMP, dlg );
}

void Q170::setData( QParameter& Par, TGroup *dlg )
{
 setAxData5( _NIMP, dlg );
}

Boolean Q170::valueTest( TGroup *dlg )
{
 dlgData(NUM,5) d;
 int data[NUM];

 dlg->TGroup::getData( &d );
 for( register i = 0; i < NUM; i++ )
 {
  data[i] = atoi( d.dat[i] );
  if( data[i] < 0 )
  {
   char msg[128];
   sprintf( msg, "\x003Непpавильно задано количество импульсов %u оси.", i+1);
   messageBox( mfError | mfOKButton , msg );
   return False;
  }
 }
 return True;
}

char * const Q180::title = "Q180";

void Q180::createDialog( QParameter& Par, QpDisplay& dsp )
{
 FoolAxDialog( Par, dsp, 6 );
}

void Q180::getData( QParameter& Par, TGroup *dlg )
{
 getfAxData6( _MSIMP, dlg );
}

void Q180::setData( QParameter& Par, TGroup *dlg )
{
 setfAxData6( _MSIMP, dlg );
}

Boolean Q180::valueTest( TGroup *dlg )
{
 return True;
}

char * const Q190::title = "Q190";

void Q190::createDialog( QParameter& Par, QpDisplay& dsp )
{
 LogAxDialog( Par, dsp );
}

void Q190::getData( QParameter& Par, TGroup *dlg )
{
 dlg->TGroup::getData( &_INDAX );
}

void Q190::setData( QParameter& Par, TGroup *dlg )
{
 dlg->TGroup::setData( &_INDAX );
}

Boolean Q190::valueTest( TGroup *dlg )
{
 return True;
}

char * const Q200::title = "Q200";

void Q200::createDialog( QParameter& Par, QpDisplay& dsp )
{
 LogAxDialog( Par, dsp );
}

void Q200::getData( QParameter& Par, TGroup *dlg )
{
 dlg->TGroup::getData( &_INDAXD );
}

void Q200::setData( QParameter& Par, TGroup *dlg )
{
 dlg->TGroup::setData( &_INDAXD );
}

Boolean Q200::valueTest( TGroup *dlg )
{
 return True;
}

char * const Q210::title = "Q210";

void Q210::createDialog( QParameter& Par, QpDisplay& dsp )
{
 LogAxDialog( Par, dsp );
}

void Q210::getData( QParameter& Par, TGroup *dlg )
{
 dlg->TGroup::getData( &_LKRUG );
}

void Q210::setData( QParameter& Par, TGroup *dlg )
{
 dlg->TGroup::setData( &_LKRUG );
}

Boolean Q210::valueTest( TGroup *dlg )
{
 return True;
}

char * const Q220::title = "Q200";

void Q220::createDialog( QParameter& Par, QpDisplay& dsp )
{
 LogAxDialog( Par, dsp );
}

void Q220::getData( QParameter& Par, TGroup *dlg )
{
 dlg->TGroup::getData( &_MSBLOK );
}

void Q220::setData( QParameter& Par, TGroup *dlg )
{
 dlg->TGroup::setData( &_MSBLOK );
}

Boolean Q220::valueTest( TGroup *dlg )
{
 return True;
}

char * const Q225::title = "Q225";

void Q225::createDialog( QParameter& Par, QpDisplay& dsp )
{
 LogAxDialog( Par, dsp );
}

void Q225::getData( QParameter& Par, TGroup *dlg )
{
 dlg->TGroup::getData( &_BLSLEG );
}

void Q225::setData( QParameter& Par, TGroup *dlg )
{
 dlg->TGroup::setData( &_BLSLEG );
}

Boolean Q225::valueTest( TGroup *dlg )
{
 return True;
}

char * const Q230::title = "Q230";

void Q230::createDialog( QParameter& Par, QpDisplay& dsp )
{
 LogAxDialog( Par, dsp );
}

void Q230::getData( QParameter& Par, TGroup *dlg )
{
 dlg->TGroup::getData( &_MSDIR );
}

void Q230::setData( QParameter& Par, TGroup *dlg )
{
 dlg->TGroup::setData( &_MSDIR );
}

Boolean Q230::valueTest( TGroup *dlg )
{
 return True;
}

char * const Q240::title = "Q240";

void Q240::createDialog( QParameter& Par, QpDisplay& dsp )
{
 LogAxDialog( Par, dsp );
}

void Q240::getData( QParameter& Par, TGroup *dlg )
{
 dlg->TGroup::getData( &_POLAR );
}

void Q240::setData( QParameter& Par, TGroup *dlg )
{
 dlg->TGroup::setData( &_POLAR );
}

Boolean Q240::valueTest( TGroup *dlg )
{
 return True;
}

char * const Q250::title = "Q250";

void Q250::createDialog( QParameter& Par, QpDisplay& dsp )
{
 FoolAxDialog( Par, dsp, 6 );
}

void Q250::getData( QParameter& Par, TGroup *dlg )
{
 getfAxData6( _DREIF, dlg );
}

void Q250::setData( QParameter& Par, TGroup *dlg )
{
 setfAxData6( _DREIF, dlg );
}

Boolean Q250::valueTest( TGroup *dlg )
{
 return True;
}

char * const Q500::title = "Q500";

void Q500::createDialog( QParameter& Par, QpDisplay& dsp )
{
 FoolAxDialog( Par, dsp, 5 );
}

void Q500::getData( QParameter& Par, TGroup *dlg )
{
 getuAxData5( _KCAP, dlg );
}

void Q500::setData( QParameter& Par, TGroup *dlg )
{
 setuAxData5( _KCAP, dlg );
}

Boolean Q500::valueTest( TGroup *dlg )
{
 return True;
}

char * const Q510::title = "Q510";

void Q510::createDialog( QParameter& Par, QpDisplay& dsp )
{
 FoolAxDialog( Par, dsp, 5 );
}

void Q510::getData( QParameter& Par, TGroup *dlg )
{
 getuAxData5( _VG00, dlg );
}

void Q510::setData( QParameter& Par, TGroup *dlg )
{
 setuAxData5( _VG00, dlg );
}

Boolean Q510::valueTest( TGroup *dlg )
{
 return True;
}

char * const Q520::title = "Q520";

void Q520::createDialog( QParameter& Par, QpDisplay& dsp )
{
 FoolAxDialog( Par, dsp, 5 );
}

void Q520::getData( QParameter& Par, TGroup *dlg )
{
 getuAxData5( _VNUL, dlg );
}

void Q520::setData( QParameter& Par, TGroup *dlg )
{
 setuAxData5( _VNUL, dlg );
}

Boolean Q520::valueTest( TGroup *dlg )
{
 return True;
}

char * const Q530::title = "Q530";

void Q530::createDialog( QParameter& Par, QpDisplay& dsp )
{
 FoolAxDialog( Par, dsp, 5 );
}

void Q530::getData( QParameter& Par, TGroup *dlg )
{
 getuAxData5( _VSNIG, dlg );
}

void Q530::setData( QParameter& Par, TGroup *dlg )
{
 setuAxData5( _VSNIG, dlg );
}

Boolean Q530::valueTest( TGroup *dlg )
{
 return True;
}

char * const Q540::title = "Q540";

void Q540::createDialog( QParameter& Par, QpDisplay& dsp )
{
 FoolAxDialog( Par, dsp, 5 );
}

void Q540::getData( QParameter& Par, TGroup *dlg )
{
 getuAxData5( _VNKUL, dlg );
}

void Q540::setData( QParameter& Par, TGroup *dlg )
{
 setuAxData5( _VNKUL, dlg );
}

Boolean Q540::valueTest( TGroup *dlg )
{
 return True;
}

char * const Q550::title = "Q550";

void Q550::createDialog( QParameter& Par, QpDisplay& dsp )
{
 FoolAxDialog( Par, dsp, 5 );
}

void Q550::getData( QParameter& Par, TGroup *dlg )
{
 getuAxData5( _HANDF1, dlg );
}

void Q550::setData( QParameter& Par, TGroup *dlg )
{
 setuAxData5( _HANDF1, dlg );
}

Boolean Q550::valueTest( TGroup *dlg )
{
 return True;
}

char * const Q560::title = "Q560";

void Q560::createDialog( QParameter& Par, QpDisplay& dsp )
{
 FoolAxDialog( Par, dsp, 5 );
}

void Q560::getData( QParameter& Par, TGroup *dlg )
{
 getuAxData5( _HANDF2, dlg );
}

void Q560::setData( QParameter& Par, TGroup *dlg )
{
 setuAxData5( _HANDF2, dlg );
}

Boolean Q560::valueTest( TGroup *dlg )
{
 return True;
}

char * const Q570::title = "Q570";

void Q570::createDialog( QParameter& Par, QpDisplay& dsp )
{
 FoolAxDialog( Par, dsp, 5 );
}

void Q570::getData( QParameter& Par, TGroup *dlg )
{
 getuAxData5( _HANDF3, dlg );
}

void Q570::setData( QParameter& Par, TGroup *dlg )
{
 setuAxData5( _HANDF3, dlg );
}

Boolean Q570::valueTest( TGroup *dlg )
{
 return True;
}

char * const Q580::title = "Q580";

void Q580::createDialog( QParameter& Par, QpDisplay& dsp )
{
 FoolAxDialog( Par, dsp, 5 );
}

void Q580::getData( QParameter& Par, TGroup *dlg )
{
 getuAxData5( _HANDG00, dlg );
}

void Q580::setData( QParameter& Par, TGroup *dlg )
{
 setuAxData5( _HANDG00, dlg );
}

Boolean Q580::valueTest( TGroup *dlg )
{
 return True;
}

char * const Q590::title = "Q590";

void Q590::createDialog( QParameter& Par, QpDisplay& dsp )
{
 TRect r = dsp.getExtent();
 r.a.x+=18;
 r.a.y+=6;
 r.b.x = r.a.x+9;
 r.b.y = r.a.y+1;
 TView *il = new TInputLine( r, 6 );

 r.a.x -= 10;
 r.b.x += 10;
 r.a.y -= 2;
 r.b.y -= 2;
 dsp.insert( new TLabel( r, "~М~аксимальная рабочая подача:", il ) );
 dsp.insert( il );
}

void Q590::getData( QParameter& Par, TGroup *dlg )
{
 char data[6];
 dlg->TGroup::getData( data );
 _MAXWORKF = atoi( data );
}

void Q590::setData( QParameter& Par, TGroup *dlg )
{
 char data[6];
 sprintf( data, "%u", _MAXWORKF );
 dlg->TGroup::setData( data );
}

Boolean Q590::valueTest( TGroup *dlg )
{
 return True;
}

char * const Q600::title = "Q600";

void Q600::createDialog( QParameter& Par, QpDisplay& dsp )
{
 FoolAxDialog( Par, dsp, 6 );
}

void Q600::getData( QParameter& Par, TGroup *dlg )
{
 getfAxData6( _RASSV, dlg );
}

void Q600::setData( QParameter& Par, TGroup *dlg )
{
 setfAxData6( _RASSV, dlg );
}

Boolean Q600::valueTest( TGroup *dlg )
{
 return True;
}

char * const Q610::title = "Q610";

void Q610::createDialog( QParameter& Par, QpDisplay& dsp )
{
 FoolAxDialog( Par, dsp, 5 );
}

void Q610::getData( QParameter& Par, TGroup *dlg )
{
 getuAxData5( _TIMERASSV, dlg );
}

void Q610::setData( QParameter& Par, TGroup *dlg )
{
 setuAxData5( _TIMERASSV, dlg );
}

Boolean Q610::valueTest( TGroup *dlg )
{
 return True;
}

char * const Q620::title = "Q620";

void Q620::createDialog( QParameter& Par, QpDisplay& dsp )
{
 FoolAxDialog( Par, dsp, 6 );
}

void Q620::getData( QParameter& Par, TGroup *dlg )
{
 getfAxData6( _ALIMIT, dlg );
}

void Q620::setData( QParameter& Par, TGroup *dlg )
{
 setfAxData6( _ALIMIT, dlg );
}

Boolean Q620::valueTest( TGroup *dlg )
{
 return True;
}

char * const Q1000::title = "Q1000";

void Q1000::createDialog( QParameter& Par, QpDisplay& dsp )
{
 FoolAxDialog( Par, dsp, 6 );
}

void Q1000::getData( QParameter& Par, TGroup *dlg )
{
 getfAxData6( _KV, dlg );
}

void Q1000::setData( QParameter& Par, TGroup *dlg )
{
 setfAxData6( _KV, dlg );
}

Boolean Q1000::valueTest( TGroup *dlg )
{
 return True;
}

char * const Q1010::title = "Q1010";

void Q1010::createDialog( QParameter& Par, QpDisplay& dsp )
{
 FoolAxDialog( Par, dsp, 6 );
}

void Q1010::getData( QParameter& Par, TGroup *dlg )
{
 getfAxData6( _KVOKEY, dlg );
}

void Q1010::setData( QParameter& Par, TGroup *dlg )
{
 setfAxData6( _KVOKEY, dlg );
}

Boolean Q1010::valueTest( TGroup *dlg )
{
 return True;
}

char * const Q1020::title = "Q1020";

void Q1020::createDialog( QParameter& Par, QpDisplay& dsp )
{
 FoolAxDialog( Par, dsp, 6 );
}

void Q1020::getData( QParameter& Par, TGroup *dlg )
{
 getfAxData6( _A, dlg );
}

void Q1020::setData( QParameter& Par, TGroup *dlg )
{
 setfAxData6( _A, dlg );
}

Boolean Q1020::valueTest( TGroup *dlg )
{
 return True;
}

char * const Q1030::title = "Q1030";

void Q1030::createDialog( QParameter& Par, QpDisplay& dsp )
{
 FoolAxDialog( Par, dsp, 5 );
}

void Q1030::getData( QParameter& Par, TGroup *dlg )
{
 getuAxData5( _VRAZG, dlg );
}

void Q1030::setData( QParameter& Par, TGroup *dlg )
{
 setuAxData5( _VRAZG, dlg );
}

Boolean Q1030::valueTest( TGroup *dlg )
{
 return True;
}

char * const Q1040::title = "Q1040";

void Q1040::createDialog( QParameter& Par, QpDisplay& dsp )
{
 FoolAxDialog( Par, dsp, 5 );
}

void Q1040::getData( QParameter& Par, TGroup *dlg )
{
 getuAxData5( _VTORM, dlg );
}

void Q1040::setData( QParameter& Par, TGroup *dlg )
{
 setuAxData5( _VTORM, dlg );
}

Boolean Q1040::valueTest( TGroup *dlg )
{
 return True;
}

char * const Q1050::title = "Q1050";

void Q1050::createDialog( QParameter& Par, QpDisplay& dsp )
{
 FoolAxDialog( Par, dsp, 5 );
}

void Q1050::getData( QParameter& Par, TGroup *dlg )
{
 getuAxData5( _ACOMM, dlg );
}

void Q1050::setData( QParameter& Par, TGroup *dlg )
{
 setAxData5( _ACOMM, dlg );
}

Boolean Q1050::valueTest( TGroup *dlg )
{
 return True;
}

char * const Q1060::title = "Q1060";

void Q1060::createDialog( QParameter& Par, QpDisplay& dsp )
{
 FoolAxDialog( Par, dsp, 5 );
}

void Q1060::getData( QParameter& Par, TGroup *dlg )
{
 getuAxData5( _VCOMM, dlg );
}

void Q1060::setData( QParameter& Par, TGroup *dlg )
{
 setuAxData5( _VCOMM, dlg );
}

Boolean Q1060::valueTest( TGroup *dlg )
{
 return True;
}

char * const Q1070::title = "Q1070";

void Q1070::createDialog( QParameter& Par, QpDisplay& dsp )
{
 FoolAxDialog( Par, dsp, 5 );
}

void Q1070::getData( QParameter& Par, TGroup *dlg )
{
 getuAxData5( _PEREHODF, dlg );
}

void Q1070::setData( QParameter& Par, TGroup *dlg )
{
 setuAxData5( _PEREHODF, dlg );
}

Boolean Q1070::valueTest( TGroup *dlg )
{
 return True;
}

char * const Q1080::title = "Q1080";

void Q1080::createDialog( QParameter& Par, QpDisplay& dsp )
{
 FoolAxDialog( Par, dsp, 6 );
}

void Q1080::getData( QParameter& Par, TGroup *dlg )
{
 getdAxData6( _MIN_SLOP , dlg );
}

void Q1080::setData( QParameter& Par, TGroup *dlg )
{
 setdAxData6( _MIN_SLOP , dlg );
}

Boolean Q1080::valueTest( TGroup *dlg )
{
 return True;
}

char * const Q1090::title = "Q1090";

void Q1090::createDialog( QParameter& Par, QpDisplay& dsp )
{
 FoolAxDialog( Par, dsp, 6 );
}

void Q1090::getData( QParameter& Par, TGroup *dlg )
{
 getdAxData6( _MAX_SLOP , dlg );
}

void Q1090::setData( QParameter& Par, TGroup *dlg )
{
 setdAxData6( _MAX_SLOP , dlg );
}

Boolean Q1090::valueTest( TGroup *dlg )
{
 return True;
}

char * const Q1100::title = "Q1100";

void Q1100::createDialog( QParameter& Par, QpDisplay& dsp )
{
 FoolAxDialog( Par, dsp, 6 );
}

void Q1100::getData( QParameter& Par, TGroup *dlg )
{
 getdAxData6( _MIN_KV, dlg );
}

void Q1100::setData( QParameter& Par, TGroup *dlg )
{
 setdAxData6( _MIN_KV, dlg );
}

Boolean Q1100::valueTest( TGroup *dlg )
{
 return True;
}

char * const Q1110::title = "Q1110";

void Q1110::createDialog( QParameter& Par, QpDisplay& dsp )
{
 FoolAxDialog( Par, dsp, 6 );
}

void Q1110::getData( QParameter& Par, TGroup *dlg )
{
 getdAxData6( _MAX_KV, dlg );
}

void Q1110::setData( QParameter& Par, TGroup *dlg )
{
 setdAxData6( _MAX_KV, dlg );
}

Boolean Q1110::valueTest( TGroup *dlg )
{
 return True;
}

char * const Q1500::title = "Q1500";

void Q1500::createDialog( QParameter& Par, QpDisplay& dsp )
{
 FoolAxDialog( Par, dsp, 9 );
}

void Q1500::getData( QParameter& Par, TGroup *dlg )
{
 getlAxData9( _XNUL, dlg );
}

void Q1500::setData( QParameter& Par, TGroup *dlg )
{
 setlAxData9( _XNUL, dlg );
}

Boolean Q1500::valueTest( TGroup *dlg )
{
 return True;
}

char * const Q1510::title = "Q1510";

void Q1510::createDialog( QParameter& Par, QpDisplay& dsp )
{
 FoolAxDialog( Par, dsp, 9 );
}

void Q1510::getData( QParameter& Par, TGroup *dlg )
{
 getlAxData9( _SNUL, dlg );
}

void Q1510::setData( QParameter& Par, TGroup *dlg )
{
 setlAxData9( _SNUL, dlg );
}

Boolean Q1510::valueTest( TGroup *dlg )
{
 return True;
}

char * const Q1520::title = "Q1520";

void Q1520::createDialog( QParameter& Par, QpDisplay& dsp )
{
 LogAxDialog( Par, dsp );
}

void Q1520::getData( QParameter& Par, TGroup *dlg )
{
 dlg->TGroup::getData( &_BLOKMO );
}

void Q1520::setData( QParameter& Par, TGroup *dlg )
{
 dlg->TGroup::setData( &_BLOKMO );
}

Boolean Q1520::valueTest( TGroup *dlg )
{
 return True;
}

char * const Q1530::title = "Q1530";

void Q1530::createDialog( QParameter& Par, QpDisplay& dsp )
{
 FoolAxDialog( Par, dsp, 9 );
}

void Q1530::getData( QParameter& Par, TGroup *dlg )
{
 getdAxData9( _MOPLUS, dlg );
}

void Q1530::setData( QParameter& Par, TGroup *dlg )
{
 setdAxData9( _MOPLUS, dlg );
}

Boolean Q1530::valueTest( TGroup *dlg )
{
 return True;
}

char * const Q1540::title = "Q1540";

void Q1540::createDialog( QParameter& Par, QpDisplay& dsp )
{
 FoolAxDialog( Par, dsp, 9 );
}

void Q1540::getData( QParameter& Par, TGroup *dlg )
{
 getdAxData9( _MOMINUS, dlg );
}

void Q1540::setData( QParameter& Par, TGroup *dlg )
{
 setdAxData9( _MOMINUS, dlg );
}

Boolean Q1540::valueTest( TGroup *dlg )
{
 return True;
}

char * const Q1550::title = "Q1550";

void Q1550::createDialog( QParameter& Par, QpDisplay& dsp )
{
 FoolAxDialog( Par, dsp, 7 );
}

void Q1550::getData( QParameter& Par, TGroup *dlg )
{
 getAxData7( _OKEY, dlg );
}

void Q1550::setData( QParameter& Par, TGroup *dlg )
{
 setAxData7( _OKEY, dlg );
}

Boolean Q1550::valueTest( TGroup *dlg )
{
 return True;
}

char * const Q1560::title = "Q1560";

void Q1560::createDialog( QParameter& Par, QpDisplay& dsp )
{
 FoolAxDialog( Par, dsp, 6 );
}

void Q1560::getData( QParameter& Par, TGroup *dlg )
{
 getfAxData6( _RASS, dlg );
 for( register i = 0 ; i < NUM; i++ )
  _RASS[i] *= _MSIMP[i];
}

void Q1560::setData( QParameter& Par, TGroup *dlg )
{
 for( register i = 0; i < NUM; i++ )
  _RASS[i] /= _MSIMP[i] ? _MSIMP[i] : 1;
 setfAxData6( _RASS, dlg );
}

Boolean Q1560::valueTest( TGroup *dlg )
{
 return True;
}

char * const Q1570::title = "Q1570";

void Q1570::createDialog( QParameter& Par, QpDisplay& dsp )
{
 FoolAxDialog( Par, dsp, 5 );
}

void Q1570::getData( QParameter& Par, TGroup *dlg )
{
 getuAxData5( _TIMERASS, dlg );
}

void Q1570::setData( QParameter& Par, TGroup *dlg )
{
 setuAxData5( _TIMERASS, dlg );
}

Boolean Q1570::valueTest( TGroup *dlg )
{
 return True;
}


char * const Q1580::title = "Q1580";

void Q1580::createDialog( QParameter& Par, QpDisplay& dsp )
{
 FoolAxDialog( Par, dsp, 9 );
}

void Q1580::getData( QParameter& Par, TGroup *dlg )
{
 getdAxData9( _IFG(0), dlg );
}

void Q1580::setData( QParameter& Par, TGroup *dlg )
{
 setdAxData9( _IFG(0), dlg );
}

Boolean Q1580::valueTest( TGroup *dlg )
{
 return True;
}

char * const Q1590::title = "Q1590";

void Q1590::createDialog( QParameter& Par, QpDisplay& dsp )
{
 FoolAxDialog( Par, dsp, 9 );
}

void Q1590::getData( QParameter& Par, TGroup *dlg )
{
 getdAxData9( _IFG(1), dlg );
}

void Q1590::setData( QParameter& Par, TGroup *dlg )
{
 setdAxData9( _IFG(1), dlg );
}

Boolean Q1590::valueTest( TGroup *dlg )
{
 return True;
}

char * const Q1600::title = "Q1600";

void Q1600::createDialog( QParameter& Par, QpDisplay& dsp )
{
 FoolAxDialog( Par, dsp, 9 );
}

void Q1600::getData( QParameter& Par, TGroup *dlg )
{
 getdAxData9( _IFG(2), dlg );
}

void Q1600::setData( QParameter& Par, TGroup *dlg )
{
 setdAxData9( _IFG(2), dlg );
}

Boolean Q1600::valueTest( TGroup *dlg )
{
 return True;
}

char * const Q1610::title = "Q1610";

void Q1610::createDialog( QParameter& Par, QpDisplay& dsp )
{
 FoolAxDialog( Par, dsp, 9 );
}

void Q1610::getData( QParameter& Par, TGroup *dlg )
{
 getdAxData9( _IFG(3), dlg );
}

void Q1610::setData( QParameter& Par, TGroup *dlg )
{
 setdAxData9( _IFG(3), dlg );
}

Boolean Q1610::valueTest( TGroup *dlg )
{
 return True;
}

char * const Q1620::title = "Q1620";

void Q1620::createDialog( QParameter& Par, QpDisplay& dsp )
{
 FoolAxDialog( Par, dsp, 9 );
}

void Q1620::getData( QParameter& Par, TGroup *dlg )
{
 getdAxData9( _IFG(4), dlg );
}

void Q1620::setData( QParameter& Par, TGroup *dlg )
{
 setdAxData9( _IFG(4), dlg );
}

Boolean Q1620::valueTest( TGroup *dlg )
{
 return True;
}

char * const Q2000::title = "Q2000";

void Q2000::createDialog( QParameter& Par, QpDisplay& dsp )
{
 FoolAxDialog( Par, dsp, 5 );
}

void Q2000::getData( QParameter& Par, TGroup *dlg )
{
 getuAxData5( _LUFT, dlg );
}

void Q2000::setData( QParameter& Par, TGroup *dlg )
{
 setuAxData5( _LUFT, dlg );
}

Boolean Q2000::valueTest( TGroup *dlg )
{
 return True;
}

char * const Q2010::title = "Q2010";

void Q2010::createDialog( QParameter& Par, QpDisplay& dsp )
{
 LogAxDialog( Par, dsp );
}

void Q2010::getData( QParameter& Par, TGroup *dlg )
{
 dlg->TGroup::getData( &_AXCORR );
}

void Q2010::setData( QParameter& Par, TGroup *dlg )
{
 dlg->TGroup::setData( &_AXCORR );
}

Boolean Q2010::valueTest( TGroup *dlg )
{
 return True;
}

char * const Q2020::title = "Q2020";

void Q2020::createDialog( QParameter& Par, QpDisplay& dsp )
{
 FoolAxDialog( Par, dsp, 7 );
}

void Q2020::getData( QParameter& Par, TGroup *dlg )
{
 getAxData7( _TCORR, dlg );
}

void Q2020::setData( QParameter& Par, TGroup *dlg )
{
 setAxData7( _TCORR, dlg );
}

Boolean Q2020::valueTest( TGroup *dlg )
{
 return True;
}

char * const Q2030::title = "Q2030";

void Q2030::createDialog( QParameter& Par, QpDisplay& dsp )
{
 FoolAxDialog( Par, dsp, 6 );
}

void Q2030::getData( QParameter& Par, TGroup *dlg )
{
 getsAxData6( _STEP, dlg );
}

void Q2030::setData( QParameter& Par, TGroup *dlg )
{
 setsAxData6( _STEP, dlg );
}

Boolean Q2030::valueTest( TGroup *dlg )
{
 return True;
}

char * const Q2040::title = "Q2040";

void Q2040::createDialog( QParameter& Par, QpDisplay& dsp )
{
 FoolAxDialog( Par, dsp, 9 );
}

void Q2040::getData( QParameter& Par, TGroup *dlg )
{
 getlAxData9( _X0, dlg );
}

void Q2040::setData( QParameter& Par, TGroup *dlg )
{
 setlAxData9( _X0, dlg );
}

Boolean Q2040::valueTest( TGroup *dlg )
{
 return True;
}

char * const Q2050::title = "Q2050";

void Q2050::createDialog( QParameter& Par, QpDisplay& dsp )
{
 FoolAxDialog( Par, dsp, 4 );
}

void Q2050::getData( QParameter& Par, TGroup *dlg )
{
 getAxData4( _NCOR, dlg );
}

void Q2050::setData( QParameter& Par, TGroup *dlg )
{
 setAxData4( _NCOR, dlg );
}

Boolean Q2050::valueTest( TGroup *dlg )
{
 return True;
}

char * const Q2060::title = "Q2060";

void Q2060::createDialog( QParameter& Par, QpDisplay& dsp )
{
 TRect r = dsp.getExtent();
 r.a.y += 3;
 r.b.y -= 6;
 r.b.x -= 3;
 r.a.x = r.b.x -1 ;
 TScrollBar *sb = new TScrollBar(r);
 dsp.insert( sb );

 r = dsp.getExtent();
 r.a.y += 3;
 r.b.y -= 6;
 r.b.x -= 4;
 r.a.x += 3 ;
 dsp.insert( new TStaticText( TRect(r.a.x,r.a.y-1,r.b.x,r.a.y),
		 "  №т  │  Координата  │коррекция+ │коррекция-") );
 VintCorrectorList *tl = new VintCorrectorList( r, sb, Par );
 dsp.insert( tl );

 r.a.y+=11;
 r.b.y+=2;
 r.b.x = r.a.x+7;
 TablInputLine *il = new TablInputLine( r, 1, KPARAM / 2, 5, cmFindTablIndex, tl );
 dsp.insert( il );

 r.a.x = r.b.x-1;
 r.b.x += 7;
 dsp.insert( new TLabel(r, "<-~П~оиск", il ) );

 r.a.x += 19;
 r.b.x += 20;
 il = new TablInputLine( r, -MAXINT, MAXINT, 7, cmInputFirstData, tl );
 dsp.insert( il );

 r.a.x -= 8;
 r.b.x -= 9;
 dsp.insert( new TLabel(r, "~В~вод->", il ) );

 r.a.x += 19;
 r.b.x += 20;
 il = new TablInputLine( r, -MAXINT, MAXINT, 7, cmInputSecondData, tl );
 dsp.insert( il );

 r.a.x = 2;
 r.b.x = 22;
 r.a.y = 1;
 r.b.y = 2;
 dsp.insert( new TLabel(r, "Значения ~к~оррекции", tl ) );
}

void Q2060::getData( QParameter& Par, TGroup *dlg )
{
}

void Q2060::setData( QParameter& Par, TGroup *dlg )
{
}

Boolean Q2060::valueTest( TGroup *dlg )
{
 return True;
}

char * const Q2500::title = "Q2500";

void Q2500::createDialog( QParameter& Par, QpDisplay& dsp )
{
 TRect r( 10, 6, 43, 9 );
 TView *b = new TRadioButtons( r, new TSItem( "на CNC и PLC",
				  new TSItem( "только на PLC",
				  new TSItem( "только на CNC", 0 ))) );
 TView *l = new TLabel( TRect(r.a.x, r.a.y-1, r.b.x, r.a.y ),
			"~Р~асположение органов управления", b );
 dsp.insert( b );
 dsp.insert( l );
}

void Q2500::getData( QParameter& Par, TGroup *dlg )
{
 int data = 0;
 dlg->TGroup::getData( &data );
 _CONTAL = (uchar)data;
}

void Q2500::setData( QParameter& Par, TGroup *dlg )
{
 int data = _CONTAL;
 dlg->TGroup::setData( &data );
}

Boolean Q2500::valueTest( TGroup *dlg )
{
 return True;
}

char * const Q2510::title = "Q2510";

void Q2510::createDialog( QParameter& Par, QpDisplay& dsp )
{
 TRect r( 20, 6, 26, 7 );
 TView *min = new TInputLine( r, 4 );
 TView *ln = new TLabel( TRect( r.a.x-8, r.a.y, r.b.x-8, r.b.y ), "Ми~н~.", min);
 r.a.y += 2;
 r.b.y += 2;
 TView *max = new TInputLine( r, 4 );
 TView *lx = new TLabel( TRect( r.a.x-8, r.a.y, r.b.x-8, r.b.y ), "Мак~с~.", max);
 TView *tx = new TStaticText( TRect( r.a.x-7, r.a.y-4, r.b.x+6, r.b.y-4 ),
		 "Потенциометр F" );
 dsp.insert( ln );
 dsp.insert( min );
 dsp.insert( lx );
 dsp.insert( max );
 dsp.insert( tx );
}

void Q2510::getData( QParameter& Par, TGroup *dlg )
{
 char data[2][4];
 dlg->TGroup::getData( data );
 _MINF = atoi( data[0] );
 _MAXF = atoi( data[1] );
}

void Q2510::setData( QParameter& Par, TGroup *dlg )
{
 char data[2][4];
 itoa( _MINF, data[0], 10 );
 itoa( _MAXF, data[1], 10 );
 dlg->TGroup::setData( data );
}

Boolean Q2510::valueTest( TGroup *dlg )
{
 return True;
}

char * const Q2520::title = "Q2520";

void Q2520::createDialog( QParameter& Par, QpDisplay& dsp )
{
 TRect r( 20, 6, 26, 7 );
 TView *min = new TInputLine( r, 4 );
 TView *ln = new TLabel( TRect( r.a.x-8, r.a.y, r.b.x-8, r.b.y ), "Ми~н~.", min);
 r.a.y += 2;
 r.b.y += 2;
 TView *max = new TInputLine( r, 4 );
 TView *lx = new TLabel( TRect( r.a.x-8, r.a.y, r.b.x-8, r.b.y ), "Мак~с~.", max);
 TView *tx = new TStaticText( TRect( r.a.x-7, r.a.y-4, r.b.x+6, r.b.y-4 ),
		 "Потенциометр S" );
 dsp.insert( ln );
 dsp.insert( min );
 dsp.insert( lx );
 dsp.insert( max );
 dsp.insert( tx );
}

void Q2520::getData( QParameter& Par, TGroup *dlg )
{
 char data[2][4];
 dlg->TGroup::getData( data );
 _MINS = atoi( data[0] );
 _MAXS = atoi( data[1] );
}

void Q2520::setData( QParameter& Par, TGroup *dlg )
{
 char data[2][4];
 itoa( _MINS, data[0], 10 );
 itoa( _MAXS, data[1], 10 );
 dlg->TGroup::setData( data );
}

Boolean Q2520::valueTest( TGroup *dlg )
{
 return True;
}

char * const Q2530::title = "Q2530";

void Q2530::createDialog( QParameter& Par, QpDisplay& dsp )
{
 TRect r( 20, 6, 26, 7 );
 TView *il = new TInputLine( r, 4 );
 TView *lb = new TLabel( TRect( r.a.x-6, r.a.y, r.b.x-6, r.b.y ), "~Ш~аг", il );
 TView *tx = new TStaticText( TRect( r.a.x-8, r.a.y-3, r.b.x+16, r.b.y-2 ),
		 "\003Ускоренное изменение" " потенциометров" );
 dsp.insert( il );
 dsp.insert( lb );
 dsp.insert( tx );
}

void Q2530::getData( QParameter& Par, TGroup *dlg )
{
 char data[4];
 dlg->TGroup::getData( data );
 _BIGSTEP = atoi( data );
}

void Q2530::setData( QParameter& Par, TGroup *dlg )
{
 char data[4];
 itoa( _BIGSTEP, data, 10 );
 dlg->TGroup::setData( data );
}

Boolean Q2530::valueTest( TGroup *dlg )
{
 return True;
}

char * const Q2540::title = "Q2540";

void Q2540::createDialog( QParameter& Par, QpDisplay& dsp )
{
 TRect r( 20, 6, 26, 7 );
 TView *il = new TInputLine( r, 4 );
 TView *lb = new TLabel( TRect( r.a.x-6, r.a.y, r.b.x-6, r.b.y ), "~Ш~аг", il );
 TView *tx = new TStaticText( TRect( r.a.x-8, r.a.y-3, r.b.x+16, r.b.y-2 ),
		 "\003Ускоренное изменение" " потенциометров" );
 dsp.insert( il );
 dsp.insert( lb );
 dsp.insert( tx );
}

void Q2540::getData( QParameter& Par, TGroup *dlg )
{
 char data[4];
 dlg->TGroup::getData( data );
 _LITLSTEP = atoi( data );
}

void Q2540::setData( QParameter& Par, TGroup *dlg )
{
 char data[4];
 itoa( _LITLSTEP, data, 10 );
 dlg->TGroup::setData( data );
}

Boolean Q2540::valueTest( TGroup *dlg )
{
 return True;
}

char * const Q3000::title = "Q3000";

void Q3000::createDialog( QParameter& Par, QpDisplay& dsp )
{
 TRect r = dsp.getExtent();
 r.a.x+=30;
 r.a.y+=4;
 r.b.x = r.a.x+4;
 r.b.y = r.a.y+1;
 TView *il = new TInputLine( r, 2 );
 r.a.x -= 20;
 r.b.x -= 2;
 dsp.insert( new TLabel( r, "Количество групп ~M~:", il ) );
 dsp.insert( il );
 r.a.x += 20;
 r.b.x += 2;
 r.a.y += 2;
 r.b.y += 2;
 il = new TInputLine( r, 2 );
 r.a.x -= 20;
 r.b.x -= 2;
 dsp.insert( new TLabel( r, "Количество групп ~T~:", il ) );
 dsp.insert( il );
}

void Q3000::getData( QParameter& Par, TGroup *dlg )
{
 char data[2][2];
 dlg->TGroup::getData( data );
 _GRM = atoi( data[0] );
 _GRT = atoi( data[1] );
}

void Q3000::setData( QParameter& Par, TGroup *dlg )
{
 char data[2][2];
 itoa( _GRM, data[0], 10 );
 itoa( _GRT, data[1], 10 );
 dlg->TGroup::setData( data );
}

Boolean Q3000::valueTest( TGroup *dlg )
{
 return True;
}

char * const Q3010::title = "Q3010";

void Q3010::createDialog( QParameter& Par, QpDisplay& dsp )
{
 TRect r = dsp.getExtent();
 r.a.y += 3;
 r.b.y -= 6;
 r.b.x -= 3;
 r.a.x = r.b.x -1 ;
 TScrollBar *sb = new TScrollBar(r);
 dsp.insert( sb );

 r = dsp.getExtent();
 r.a.y += 3;
 r.b.y -= 6;
 r.b.x -= 4;
 r.a.x += 3 ;
 dsp.insert( new TStaticText( TRect(r.a.x,r.a.y-1,r.b.x,r.a.y),
		 "  № пп │                 Функция ") );
 MFunctionList *tl = new MFunctionList( r, sb, Par );
 dsp.insert( tl );

 r.a.y+=11;
 r.b.y+=2;
 r.b.x = r.a.x+7;
 TView *il = new TablInputLine( r, 5, 1, KPARAM / 2, cmFindTablIndex, tl );
 dsp.insert( il );

 r.a.x = r.b.x-1;
 r.b.x += 7;
 dsp.insert( new TLabel(r, "<-~П~оиск", il ) );

 r.a.x += 19;
 r.b.x += 18;
 il = new FunInputLine( r, 0.00, 9.99, 5, cmInputFirstData, tl );
 dsp.insert( il );

 r.a.x -= 8;
 r.b.x -= 8;
 dsp.insert( new TLabel(r, "~В~вод->", il ) );

 r.a.x = 2;
 r.b.x = 22;
 r.a.y = 1;
 r.b.y = 2;
 dsp.insert( new TLabel(r, "Значения ~к~оррекции", tl ) );
}

void Q3010::getData( QParameter& Par, TGroup *dlg )
{
}

void Q3010::setData( QParameter& Par, TGroup *dlg )
{
}

Boolean Q3010::valueTest( TGroup *dlg )
{
 return True;
}

char * const Q4000::title = "Q4000";

void Q4000::createDialog( QParameter& Par, QpDisplay& dsp )
{
 NameProg( dsp, NAMEL );
}

void Q4000::getData( QParameter& Par, TGroup *dlg )
{
 dlgData(QGM,NAMEL) data;
 dlg->TGroup::getData( &data );
 for( register i=0; i < QGM ; i++ )
  strncpy( _P_NOMP[i] , data.dat[i], NAMEL );
}

void Q4000::setData( QParameter& Par, TGroup *dlg )
{
 dlgData(QGM,NAMEL) data;
 for( register i=0; i < QGM ; i++ )
  strncpy( data.dat[i], _P_NOMP[i], NAMEL );
 dlg->TGroup::setData( &data );
}

Boolean Q4000::valueTest( TGroup *dlg )
{
 return True;
}

char * const Q4010::title = "Q4010";

void Q4010::createDialog( QParameter& Par, QpDisplay& dsp )
{
 NameProg( dsp, 3 );
}

void Q4010::getData( QParameter& Par, TGroup *dlg )
{
 dlgData(QGM,3) data;
 dlg->TGroup::getData( &data );
 for( register i=0; i < QGM ; i++ )
  _P_NOMG[i] = atoi( data.dat[i] );
}

void Q4010::setData( QParameter& Par, TGroup *dlg )
{
 dlgData(QGM,3) data;
 for( register i=0; i < QGM ; i++ )
  sprintf( data.dat[i], "%u", _P_NOMG[i] );
 dlg->TGroup::setData( &data );
}

Boolean Q4010::valueTest( TGroup *dlg )
{
 return True;
}

char * const Q4020::title = "Q4020";

void Q4020::createDialog( QParameter& Par, QpDisplay& dsp )
{
 NameProg( dsp, NAMEL );
}

void Q4020::getData( QParameter& Par, TGroup *dlg )
{
 dlgData(QGM,NAMEL) data;
 dlg->TGroup::getData( &data );
 for( register i=0; i < QGM ; i++ )
  strncpy( _P_NOMMP[i] , data.dat[i], NAMEL );
}

void Q4020::setData( QParameter& Par, TGroup *dlg )
{
 dlgData(QGM,NAMEL) data;
 for( register i=0; i < QGM ; i++ )
  strncpy( data.dat[i], _P_NOMMP[i], NAMEL );
 dlg->TGroup::setData( &data );
}

Boolean Q4020::valueTest( TGroup *dlg )
{
 return True;
}

char * const Q4030::title = "Q4030";

void Q4030::createDialog( QParameter& Par, QpDisplay& dsp )
{
 NameProg( dsp, 4 );
}

void Q4030::getData( QParameter& Par, TGroup *dlg )
{
 dlgData(QGM,4) data;
 dlg->TGroup::getData( &data );
 for( register i = 0 ; i < QGM; i++ )
 {
  double nf, fraction, integer;
  sscanf( data.dat[i],"%lf", &nf );
  fraction = modf( nf, &integer );
  _P_NOMM[i][0] = int(integer);
  _P_NOMM[i][1] = int(ceil(fraction*1000.) / 10.);
 }
}

void Q4030::setData( QParameter& Par, TGroup *dlg )
{
 dlgData(QGM,4) data;
 for( register i=0; i < QGM ; i++ )
 {
  double nf = (double)_P_NOMM[i][0] + ((double)_P_NOMM[i][1]/100.);
  sprintf( data.dat[i], "%1.2lf", nf );
 }
 dlg->TGroup::setData( &data );
}

Boolean Q4030::valueTest( TGroup *dlg )
{
 return True;
}

char * const Q4050::title = "Q4050";

void Q4050::createDialog( QParameter& Par, QpDisplay& dsp )
{
 TRect r( 25, 6, 38, 8 );
 TView *b = new TRadioButtons( r, new TSItem( "G90",
				  new TSItem( "G91", 0 )) );
 TView *l = new TLabel( TRect(r.a.x-22, r.a.y, r.b.x-13, r.a.y+1 ),
			"~Ф~ункция по включению:", b );
 dsp.insert( b );
 dsp.insert( l );
}

void Q4050::getData( QParameter& Par, TGroup *dlg )
{
 dlg->TGroup::getData( &_P_BAZ );
}

void Q4050::setData( QParameter& Par, TGroup *dlg )
{
 dlg->TGroup::setData( &_P_BAZ );
}

Boolean Q4050::valueTest( TGroup *dlg )
{
 return True;
}

char * const Q4060::title = "Q4060";

void Q4060::createDialog( QParameter& Par, QpDisplay& dsp )
{
 TRect r( 25, 6, 38, 8 );
 TView *b = new TRadioButtons( r, new TSItem( "G68",
				  new TSItem( "G69", 0 )) );
 TView *l = new TLabel( TRect(r.a.x-22, r.a.y, r.b.x-13, r.a.y+1 ),
			"~Ф~ункция по включению:", b );
 dsp.insert( b );
 dsp.insert( l );
}

void Q4060::getData( QParameter& Par, TGroup *dlg )
{
 dlg->TGroup::getData( &_P_YGL );
}

void Q4060::setData( QParameter& Par, TGroup *dlg )
{
 dlg->TGroup::setData( &_P_YGL );
}

Boolean Q4060::valueTest( TGroup *dlg )
{
 return True;
}

char * const Q4070::title = "Q4070";

void Q4070::createDialog( QParameter& Par, QpDisplay& dsp )
{
 TRect r( 25, 6, 38, 8 );
 TView *b = new TRadioButtons( r, new TSItem( "G145",
				  new TSItem( "G146", 0 )) );
 TView *l = new TLabel( TRect(r.a.x-22, r.a.y, r.b.x-13, r.a.y+1 ),
			"~Ф~ункция по включению:", b );
 dsp.insert( b );
 dsp.insert( l );
}

void Q4070::getData( QParameter& Par, TGroup *dlg )
{
 dlg->TGroup::getData( &_P_TABL );
}

void Q4070::setData( QParameter& Par, TGroup *dlg )
{
 dlg->TGroup::setData( &_P_TABL );
}

Boolean Q4070::valueTest( TGroup *dlg )
{
 return True;
}

char * const Q4080::title = "Q4080";

void Q4080::createDialog( QParameter& Par, QpDisplay& dsp )
{
 LogAxDialog( Par, dsp );
}

void Q4080::getData( QParameter& Par, TGroup *dlg )
{
 int data;
 dlg->TGroup::getData( &data );
 for( register i = 0 ; i < NUM; i++ )
  _NOTVOD[i] = data & ( 1 << i ) ? 1 : 0;
}

void Q4080::setData( QParameter& Par, TGroup *dlg )
{
 int data = 0;
 for( register i = 0 ; i < NUM; i++ )
  data |=  _NOTVOD[i] ? 1 << i : 0;
 dlg->TGroup::setData( &data );
}

Boolean Q4080::valueTest( TGroup *dlg )
{
 return True;
}

char * const Q4500::title = "Q4500";

void Q4500::createDialog( QParameter& Par, QpDisplay& dsp )
{
 numPortDialog( "\003Порт контроллера"" электроавтоматики", dsp );
}

void Q4500::getData( QParameter& Par, TGroup *dlg )
{
 dlg->TGroup::getData( &_NPLC );
}

void Q4500::setData( QParameter& Par, TGroup *dlg )
{
 dlg->TGroup::setData( &_NPLC );
}

Boolean Q4500::valueTest( TGroup *dlg )
{
 return True;
}

char * const Q4510::title = "Q4510";

void Q4510::createDialog( QParameter& Par, QpDisplay& dsp )
{
 numPortDialog( "\003Порт контроллера"" сервопривода", dsp );
}

void Q4510::getData( QParameter& Par, TGroup *dlg )
{
 dlg->TGroup::getData( &_NDRC );
}

void Q4510::setData( QParameter& Par, TGroup *dlg )
{
 dlg->TGroup::setData( &_NDRC );
}

Boolean Q4510::valueTest( TGroup *dlg )
{
 return True;
}

char * const Q4520::title = "Q4520";

void Q4520::createDialog( QParameter& Par, QpDisplay& dsp )
{
 portDialog( "\003Параметры порта ЭВМ" " высшего ранга", dsp );
}

void Q4520::getData( QParameter& Par, TGroup *dlg )
{
 ComPortsData data;
 dlg->TGroup::getData( &data );
 _NDNC = data.getNumPort();
 _PDNC = data;
}

void Q4520::setData( QParameter& Par, TGroup *dlg )
{
 ComPortsData data;
 data.putNumPort( _NDNC );
 data = _PDNC ;
 dlg->TGroup::setData( &data );
}

Boolean Q4520::valueTest( TGroup *dlg )
{
 return True;
}

char * const Q4530::title = "Q4530";

void Q4530::createDialog( QParameter& Par, QpDisplay& dsp )
{
 portDialog( "\003Параметры порта" " перфоратора", dsp );
}

void Q4530::getData( QParameter& Par, TGroup *dlg )
{
 ComPortsData data;
 dlg->TGroup::getData( &data );
 _NPRF = data.getNumPort();
 _PPRF = data;
}

void Q4530::setData( QParameter& Par, TGroup *dlg )
{
 ComPortsData data;
 data.putNumPort( _NPRF );
 data = _PPRF ;
 dlg->TGroup::setData( &data );
}

Boolean Q4530::valueTest( TGroup *dlg )
{
 return True;
}

char * const Q4540::title = "Q4540";

void Q4540::createDialog( QParameter& Par, QpDisplay& dsp )
{
 numPortDialog( "\003Порт печатающего" " устройства", dsp );
}

void Q4540::getData( QParameter& Par, TGroup *dlg )
{
 dlg->TGroup::getData( &_NPRN );
}

void Q4540::setData( QParameter& Par, TGroup *dlg )
{
 dlg->TGroup::setData( &_NPRN );
}

Boolean Q4540::valueTest( TGroup *dlg )
{
 return True;
}

char * const Q5000::title = "Q5000";

void Q5000::createDialog( QParameter& Par, QpDisplay& dsp )
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
		 "   №т  │  Ось  │ ограничение - │ ограничение +") );
 TListViewer *tl = new HardSwitchList( r, sb, Par );
 dsp.insert( tl );

 r.a.y += 11;
 r.b.y += 2;
 r.a.x += 3;
 r.b.x = r.a.x+6;
 TInputLine *il = new TablInputLine( r, 1, MAXPOINT, 3, cmFindTablIndex, tl );
 dsp.insert( il );

 r.a.y--; r.b.y--;
 dsp.insert( new TLabel(r, "~П~оиск", il ) );

 r.a.y++; r.b.y++;
 r.a.x = 13;
 r.b.x = 18;
 il = new AxInputLine( r, cmInputThirdData, tl );
 dsp.insert( il );

 r.a.y--; r.b.y--;
 dsp.insert( new TLabel(r, "О~с~ь", il ) );

 r.a.y++; r.b.y++;
 r.a.x = 21;
 r.b.x = 33;
 il = new PosInputLine( r, -9999.999, +9999.999, 10, cmInputFirstData, tl );
 dsp.insert( il );

 r.a.y--; r.b.y--;
 dsp.insert( new TLabel(r, "~Л~евая гр.", il ) );

 r.a.y++; r.b.y++;
 r.a.x = 37;
 r.b.x = 49;
 il = new PosInputLine( r, -9999.999, +9999.999, 10, cmInputSecondData, tl );
 dsp.insert( il );

 r.a.y--; r.b.y--;
 dsp.insert( new TLabel(r, "~П~равая гр.", il ) );

 r.a.y++; r.b.y++;
 r.a.x = 2;
 r.b.x = 24;
 r.a.y = 1;
 r.b.y = 2;
 dsp.insert( new TLabel(r, "~К~онечные выключатели", tl ) );
}

void Q5000::getData( QParameter& Par, TGroup *dlg )
{
}

void Q5000::setData( QParameter& Par, TGroup *dlg )
{
}

Boolean Q5000::valueTest( TGroup *dlg )
{
 return True;
}

char * const Q5020::title = "Q5020";

void Q5020::createDialog( QParameter& Par, QpDisplay& dsp )
{
 FixedPointDialog( Par, dsp , 0 );
}

void Q5020::getData( QParameter& Par, TGroup *dlg )
{
}

void Q5020::setData( QParameter& Par, TGroup *dlg )
{
}

Boolean Q5020::valueTest( TGroup *dlg )
{
 return True;
}

char * const Q5030::title = "Q5030";

void Q5030::createDialog( QParameter& Par, QpDisplay& dsp )
{
 FixedPointDialog( Par, dsp , 1 );
}

void Q5030::getData( QParameter& Par, TGroup *dlg )
{
}

void Q5030::setData( QParameter& Par, TGroup *dlg )
{
}

Boolean Q5030::valueTest( TGroup *dlg )
{
 return True;
}

char * const Q5040::title = "Q5040";

void Q5040::createDialog( QParameter& Par, QpDisplay& dsp )
{
 FixedPointDialog( Par, dsp , 2 );
}

void Q5040::getData( QParameter& Par, TGroup *dlg )
{
}

void Q5040::setData( QParameter& Par, TGroup *dlg )
{
}

Boolean Q5040::valueTest( TGroup *dlg )
{
 return True;
}

char * const Q5050::title = "Q5050";

void Q5050::createDialog( QParameter& Par, QpDisplay& dsp )
{
 FixedPointDialog( Par, dsp , 3 );
}

void Q5050::getData( QParameter& Par, TGroup *dlg )
{
}

void Q5050::setData( QParameter& Par, TGroup *dlg )
{
}

Boolean Q5050::valueTest( TGroup *dlg )
{
 return True;
}

char * const Q5060::title = "Q5060";

void Q5060::createDialog( QParameter& Par, QpDisplay& dsp )
{
 FixedPointDialog( Par, dsp , 4 );
}

void Q5060::getData( QParameter& Par, TGroup *dlg )
{
}

void Q5060::setData( QParameter& Par, TGroup *dlg )
{
}

Boolean Q5060::valueTest( TGroup *dlg )
{
 return True;
}

char * const Q5070::title = "Q5070";

void Q5070::createDialog( QParameter& Par, QpDisplay& dsp )
{
 FixedPointDialog( Par, dsp , 5 );
}

void Q5070::getData( QParameter& Par, TGroup *dlg )
{
}

void Q5070::setData( QParameter& Par, TGroup *dlg )
{
}

Boolean Q5070::valueTest( TGroup *dlg )
{
 return True;
}

char * const Q5080::title = "Q5080";

void Q5080::createDialog( QParameter& Par, QpDisplay& dsp )
{
 FixedPointDialog( Par, dsp , 6 );
}

void Q5080::getData( QParameter& Par, TGroup *dlg )
{
}

void Q5080::setData( QParameter& Par, TGroup *dlg )
{
}

Boolean Q5080::valueTest( TGroup *dlg )
{
 return True;
}

char * const Q5090::title = "Q5090";

void Q5090::createDialog( QParameter& Par, QpDisplay& dsp )
{
 FixedPointDialog( Par, dsp , 7 );
}

void Q5090::getData( QParameter& Par, TGroup *dlg )
{
}

void Q5090::setData( QParameter& Par, TGroup *dlg )
{
}

Boolean Q5090::valueTest( TGroup *dlg )
{
 return True;
}

char * const Q5100::title = "Q5100";

void Q5100::createDialog( QParameter& Par, QpDisplay& dsp )
{
 FixedPointDialog( Par, dsp , 8 );
}

void Q5100::getData( QParameter& Par, TGroup *dlg )
{
}

void Q5100::setData( QParameter& Par, TGroup *dlg )
{
}

Boolean Q5100::valueTest( TGroup *dlg )
{
 return True;
}

char * const Q5110::title = "Q5110";

void Q5110::createDialog( QParameter& Par, QpDisplay& dsp )
{
 FixedPointDialog( Par, dsp , 9 );
}

void Q5110::getData( QParameter& Par, TGroup *dlg )
{
}

void Q5110::setData( QParameter& Par, TGroup *dlg )
{
}

Boolean Q5110::valueTest( TGroup *dlg )
{
 return True;
}

char * const Q5120::title = "Q5120";

void Q5120::createDialog( QParameter& Par, QpDisplay& dsp )
{
 FixedPointDialog( Par, dsp , 10 );
}

void Q5120::getData( QParameter& Par, TGroup *dlg )
{
}

void Q5120::setData( QParameter& Par, TGroup *dlg )
{
}

Boolean Q5120::valueTest( TGroup *dlg )
{
 return True;
}

char * const Q5130::title = "Q5130";

void Q5130::createDialog( QParameter& Par, QpDisplay& dsp )
{
 FixedPointDialog( Par, dsp , 11 );
}

void Q5130::getData( QParameter& Par, TGroup *dlg )
{
}

void Q5130::setData( QParameter& Par, TGroup *dlg )
{
}

Boolean Q5130::valueTest( TGroup *dlg )
{
 return True;
}

char * const Q5140::title = "Q5140";

void Q5140::createDialog( QParameter& Par, QpDisplay& dsp )
{
 FixedPointDialog( Par, dsp , 12 );
}

void Q5140::getData( QParameter& Par, TGroup *dlg )
{
}

void Q5140::setData( QParameter& Par, TGroup *dlg )
{
}

Boolean Q5140::valueTest( TGroup *dlg )
{
 return True;
}

char * const Q5150::title = "Q5150";

void Q5150::createDialog( QParameter& Par, QpDisplay& dsp )
{
 FixedPointDialog( Par, dsp , 13 );
}

void Q5150::getData( QParameter& Par, TGroup *dlg )
{
}

void Q5150::setData( QParameter& Par, TGroup *dlg )
{
}

Boolean Q5150::valueTest( TGroup *dlg )
{
 return True;
}

char * const Q5160::title = "Q5160";

void Q5160::createDialog( QParameter& Par, QpDisplay& dsp )
{
 FixedPointDialog( Par, dsp , 14 );
}

void Q5160::getData( QParameter& Par, TGroup *dlg )
{
}

void Q5160::setData( QParameter& Par, TGroup *dlg )
{
}

Boolean Q5160::valueTest( TGroup *dlg )
{
 return True;
}

char * const Q5170::title = "Q5170";

void Q5170::createDialog( QParameter& Par, QpDisplay& dsp )
{
 FixedPointDialog( Par, dsp , 15 );
}

void Q5170::getData( QParameter& Par, TGroup *dlg )
{
}

void Q5170::setData( QParameter& Par, TGroup *dlg )
{
}

Boolean Q5170::valueTest( TGroup *dlg )
{
 return True;
}

char * const Q6000::title = "Q6000";

void Q6000::createDialog( QParameter& Par, QpDisplay& dsp )
{
 SpindelDialog( Par, dsp, 2, False );
}

void Q6000::getData( QParameter& Par, TGroup *dlg )
{
 getShName( _SHADR, dlg );
}

void Q6000::setData( QParameter& Par, TGroup *dlg )
{
 setShName( _SHADR, dlg );
}

Boolean Q6000::valueTest( TGroup *dlg )
{
 return True;
}

char * const Q6005::title = "Q6005";

void Q6005::createDialog( QParameter& Par, QpDisplay& dsp )
{
 LogShDialog( Par, dsp );
}

void Q6005::getData( QParameter& Par, TGroup *dlg )
{
 ushort data = 0;
 dlg->TGroup::getData( &data );
 _OSSH = 0;
 for( register i = 0; i < NUMS ; i++ )
  if( data & AX(i) )
   _OSSH |= AX( _IS[i] );
}

void Q6005::setData( QParameter& Par, TGroup *dlg )
{
 ushort data = 0;
 for( register i = 0 ; i < NUMS ; i++ )
  if( _OSSH & AX( _IS[i] ) )
   data |= AX(i);
 dlg->TGroup::setData( &data );
}

Boolean Q6005::valueTest( TGroup *dlg )
{
 return True;
}

char * const Q6010::title = "Q6010";

void Q6010::createDialog( QParameter& Par, QpDisplay& dsp )
{
 SpindelDialog( Par, dsp, 5, False );
}

void Q6010::getData( QParameter& Par, TGroup *dlg )
{
 shData(5) data;
 float tmp;
 dlg->TGroup::getData( &data );
 for( register i = 0 ; i < NUMS; i++ )
 {
  sscanf( data.dat[i][0], "%f", &tmp );
  _SLIMIT[i] = (double)tmp;
 }
}

void Q6010::setData( QParameter& Par, TGroup *dlg )
{
 shData(5) data;
 for( register i = 0 ; i < NUMS; i++ )
  sprintf( data.dat[i][0], "%5.0f",_SLIMIT[i] );
 dlg->TGroup::setData( &data );
}

Boolean Q6010::valueTest( TGroup *dlg )
{
 return True;
}

char * const Q6020::title = "Q6020";

void Q6020::createDialog( QParameter& Par, QpDisplay& dsp )
{
 SpindelDialog( Par, dsp, 1, False );
}

void Q6020::getData( QParameter& Par, TGroup *dlg )
{
 shData(1) data;
 dlg->TGroup::getData( &data );
 for( register i = 0 ; i < NUMS; i++ )
  _SNSTUP[i]= atoi( data.dat[i][0] );
}

void Q6020::setData( QParameter& Par, TGroup *dlg )
{
 shData(1) data;
 for( register i = 0 ; i < NUMS; i++ )
  itoa( _SNSTUP[i], data.dat[i][0], 10 );
 dlg->TGroup::setData( &data );
}

Boolean Q6020::valueTest( TGroup *dlg )
{
 return True;
}

char * const Q6030::title = "Q6030";

void Q6030::createDialog( QParameter& Par, QpDisplay& dsp )
{
 SpindelDialog( Par, dsp, 5, True );
}

void Q6030::getData( QParameter& Par, TGroup *dlg )
{
 getuShData5( _SMINSTUP, dlg);
}

void Q6030::setData( QParameter& Par, TGroup *dlg )
{
 setuShData5( _SMINSTUP, dlg);
}

Boolean Q6030::valueTest( TGroup *dlg )
{
 return True;
}

char * const Q6040::title = "Q6040";

void Q6040::createDialog( QParameter& Par, QpDisplay& dsp )
{
 SpindelDialog( Par, dsp, 5, True );
}

void Q6040::getData( QParameter& Par, TGroup *dlg )
{
 getuShData5( _SMAXSTUP, dlg);
}

void Q6040::setData( QParameter& Par, TGroup *dlg )
{
 setuShData5( _SMAXSTUP, dlg);
}

Boolean Q6040::valueTest( TGroup *dlg )
{
 return True;
}

char * const Q6050::title = "Q6050";

void Q6050::createDialog( QParameter& Par, QpDisplay& dsp )
{
 SpindelDialog( Par, dsp, 5, True );
}

void Q6050::getData( QParameter& Par, TGroup *dlg )
{
 getuShData5( _SORIENT, dlg);
}

void Q6050::setData( QParameter& Par, TGroup *dlg )
{
 setuShData5( _SORIENT, dlg);
}

Boolean Q6050::valueTest( TGroup *dlg )
{
 return True;
}


char * const Q6070::title = "Q6070";

void Q6070::createDialog( QParameter& Par, QpDisplay& dsp )
{
 FoolLogShDialog( Par, dsp );
}

void Q6070::getData( QParameter& Par, TGroup *dlg )
{
 dlg->TGroup::getData( _SPOLM3 );
}

void Q6070::setData( QParameter& Par, TGroup *dlg )
{
 dlg->TGroup::setData( _SPOLM3 );
}

Boolean Q6070::valueTest( TGroup *dlg )
{
 return True;
}

char * const Q6080::title = "Q6080";

void Q6080::createDialog( QParameter& Par, QpDisplay& dsp )
{
 FoolLogShDialog( Par, dsp );
}

void Q6080::getData( QParameter& Par, TGroup *dlg )
{
 dlg->TGroup::getData( _SPOLM4 );
}

void Q6080::setData( QParameter& Par, TGroup *dlg )
{
 dlg->TGroup::setData( _SPOLM4 );
}

Boolean Q6080::valueTest( TGroup *dlg )
{
 return True;
}

char * const Q6090::title = "Q6090";

void Q6090::createDialog( QParameter& Par, QpDisplay& dsp )
{
 SpindelDialog( Par, dsp, 5, True );
}

void Q6090::getData( QParameter& Par, TGroup *dlg )
{
 getShData5( _SPEREKL, dlg);
}

void Q6090::setData( QParameter& Par, TGroup *dlg )
{
 setShData5( _SPEREKL, dlg);
}

Boolean Q6090::valueTest( TGroup *dlg )
{
 return True;
}

char * const Q6100::title = "Q6100";

void Q6100::createDialog( QParameter& Par, QpDisplay& dsp )
{
 SpindelDialog( Par, dsp, 5, False );
}

void Q6100::getData( QParameter& Par, TGroup *dlg )
{
 shData(5) data;
 long tmp;
 dlg->TGroup::getData( &data );
 for( register i = 0 ; i < NUMS; i++ )
 {
  sscanf( data.dat[i][0], "%li", &tmp );
  _SAMPL[i] = tmp;
 }
}

void Q6100::setData( QParameter& Par, TGroup *dlg )
{
 shData(5) data;
 for( register i = 0 ; i < NUMS; i++ )
  sprintf( data.dat[i][0], "%li", _SAMPL[i] );
 dlg->TGroup::setData( &data );
}

Boolean Q6100::valueTest( TGroup *dlg )
{
 return True;
}

char * const Q6110::title = "Q6110";

void Q6110::createDialog( QParameter& Par, QpDisplay& dsp )
{
 SpindelDialog( Par, dsp, 2, False );
}

void Q6110::getData( QParameter& Par, TGroup *dlg )
{
 shData(2) data;
 float tmp;
 dlg->TGroup::getData( &data );
 for( register i = 0 ; i < NUMS; i++ )
 {
  sscanf( data.dat[i][0], "%f", &tmp );
  _STEMP[i] = (double)tmp;
 }
}

void Q6110::setData( QParameter& Par, TGroup *dlg )
{
 shData(2) data;
 for( register i = 0 ; i < NUMS; i++ )
  sprintf( data.dat[i][0], "%f", _STEMP[i] );
 dlg->TGroup::setData( &data );
}

Boolean Q6110::valueTest( TGroup *dlg )
{
 return True;
}

char * const Q6120::title = "Q6120";

void Q6120::createDialog( QParameter& Par, QpDisplay& dsp )
{
 SpindelDialog( Par, dsp, 5, False );
}

void Q6120::getData( QParameter& Par, TGroup *dlg )
{
 shData(5) data;
 dlg->TGroup::getData( &data );
 for( register i = 0 ; i < NUMS; i++ )
  _SOKEY[i]= atoi( data.dat[i][0] );
}

void Q6120::setData( QParameter& Par, TGroup *dlg )
{
 shData(5) data;
 for( register i = 0 ; i < NUMS; i++ )
  itoa( _SOKEY[i], data.dat[i][0], 10 );
 dlg->TGroup::setData( &data );
}

Boolean Q6120::valueTest( TGroup *dlg )
{
 return True;
}

char * const Q6130::title = "Q6130";

void Q6130::createDialog( QParameter& Par, QpDisplay& dsp )
{
 SpindelDialog( Par, dsp, 4, False );
}

void Q6130::getData( QParameter& Par, TGroup *dlg )
{
 shData(4) data;
 dlg->TGroup::getData( &data );
 for( register i = 0 ; i < NUMS; i++ )
 {
  double nf, fraction, integer;
  sscanf( data.dat[i][0],"%lf", &nf );
  fraction = modf( nf, &integer );
  _MORI[i][0] = (int)integer;
  _MORI[i][1] = ceil(fraction*100.);
 }
}

void Q6130::setData( QParameter& Par, TGroup *dlg )
{
 shData(4) data;
 for( register i = 0 ; i < NUMS; i++ )
 {
  double nf = (double)_MORI[i][0] + ((double)_MORI[i][1]/100.);
  sprintf( data.dat[i][0], "%1.2lf", nf );
 }
 dlg->TGroup::setData( &data );
}

Boolean Q6130::valueTest( TGroup *dlg )
{
 return True;
}

char * const Q6140::title = "Q6140";

void Q6140::createDialog( QParameter& Par, QpDisplay& dsp )
{
 SpindelDialog( Par, dsp, 6, True );
}

void Q6140::getData( QParameter& Par, TGroup *dlg )
{
 getfShData6( _SKV, dlg );
}

void Q6140::setData( QParameter& Par, TGroup *dlg )
{
 setfShData6( _SKV, dlg );
}

Boolean Q6140::valueTest( TGroup *dlg )
{
 return True;
}

char * const Q6150::title = "Q6150";

void Q6150::createDialog( QParameter& Par, QpDisplay& dsp )
{
 SpindelDialog( Par, dsp, 7, True );
}

void Q6150::getData( QParameter& Par, TGroup *dlg )
{
 getfShData7( _SARAZG, dlg );
}

void Q6150::setData( QParameter& Par, TGroup *dlg )
{
 setfShData7( _SARAZG, dlg );
}

Boolean Q6150::valueTest( TGroup *dlg )
{
 return True;
}

char * const Q6160::title = "Q6160";

void Q6160::createDialog( QParameter& Par, QpDisplay& dsp )
{
 SpindelDialog( Par, dsp, 5, True );
}

void Q6160::getData( QParameter& Par, TGroup *dlg )
{
 getiShData5( _SLUFT, dlg );
}

void Q6160::setData( QParameter& Par, TGroup *dlg )
{
 setiShData5( _SLUFT, dlg );
}

Boolean Q6160::valueTest( TGroup *dlg )
{
 return True;
}

char * const Q6170::title = "Q6170";

void Q6170::createDialog( QParameter& Par, QpDisplay& dsp )
{
 SpindelDialog( Par, dsp, 5, False );
}

void Q6170::getData( QParameter& Par, TGroup *dlg )
{
 shData(5) data;
 dlg->TGroup::getData( &data );
 for( register i = 0 ; i < NUMS; i++ )
  sscanf( data.dat[i][0], "%lf", &_SNZNF[i] );
}

void Q6170::setData( QParameter& Par, TGroup *dlg )
{
 shData(5) data;
 for( register i = 0 ; i < NUMS; i++ )
  sprintf( data.dat[i][0], "%5.0lf", _SNZNF[i] );
 dlg->TGroup::setData( &data );
}

Boolean Q6170::valueTest( TGroup *dlg )
{
 return True;
}

char * const Q6180::title = "Q6180";

void Q6180::createDialog( QParameter& Par, QpDisplay& dsp )
{
 SpindelDialog( Par, dsp, 6, True );
}

void Q6180::getData( QParameter& Par, TGroup *dlg )
{
 getfShData6( _SKVSTOP, dlg );
}

void Q6180::setData( QParameter& Par, TGroup *dlg )
{
 setfShData6( _SKVSTOP, dlg );
}

Boolean Q6180::valueTest( TGroup *dlg )
{
 return True;
}

char * const Q6190::title = "Q6190";

void Q6190::createDialog( QParameter& Par, QpDisplay& dsp )
{
 SpindelDialog( Par, dsp, 5, True );
}

void Q6190::getData( QParameter& Par, TGroup *dlg )
{
 getShData5( _SSKV, dlg);
}

void Q6190::setData( QParameter& Par, TGroup *dlg )
{
 setShData5( _SSKV, dlg);
}

Boolean Q6190::valueTest( TGroup *dlg )
{
 return True;
}

char * const Q6200::title = "Q6200";

void Q6200::createDialog( QParameter& Par, QpDisplay& dsp )
{
 SpindelDialog( Par, dsp, 5, False );
}

void Q6200::getData( QParameter& Par, TGroup *dlg )
{
 shData(5) data;
 dlg->TGroup::getData( &data );
 for( register i = 0 ; i < NUMS; i++ )
  sscanf( data.dat[i][0], "%lf", &_SNMIN[i] );
}

void Q6200::setData( QParameter& Par, TGroup *dlg )
{
 shData(5) data;
 for( register i = 0 ; i < NUMS; i++ )
  sprintf( data.dat[i][0], "%5.0lf", _SNMIN[i] );
 dlg->TGroup::setData( &data );
}

Boolean Q6200::valueTest( TGroup *dlg )
{
 return True;
}

char * const Q6210::title = "Q6210";

void Q6210::createDialog( QParameter& Par, QpDisplay& dsp )
{
 SpindelDialog( Par, dsp, 4, True );
}

void Q6210::getData( QParameter& Par, TGroup *dlg )
{
 shData(4) data;
 dlg->TGroup::getData( &data );
 for( register i = 0 ; i < NUMS; i++ )
  for( register j = 0 ; j < MAXST; j++ )
  {
   double nf, fraction, integer;
   sscanf( data.dat[i][j],"%lf", &nf );
   fraction = modf( nf, &integer );
   _MFS[i][j][0] = (int)integer;
   _MFS[i][j][1] = ceil(fraction*100.);
  }
}

void Q6210::setData( QParameter& Par, TGroup *dlg )
{
 shData(4) data;
 for( register i = 0 ; i < NUMS; i++ )
  for( register j = 0 ; j < MAXST; j++ )
  {
   double nf = (double)_MFS[i][j][0] + ((double)_MFS[i][j][1]/100.);
   sprintf( data.dat[i][j], "%1.2lf", nf );
  }
 dlg->TGroup::setData( &data );
}

Boolean Q6210::valueTest( TGroup *dlg )
{
 return True;
}

char * const Q6220::title = "Q6220";

void Q6220::createDialog( QParameter& Par, QpDisplay& dsp )
{
 SpindelDialog( Par, dsp, 5, True );
}

void Q6220::getData( QParameter& Par, TGroup *dlg )
{
 getShData5( _STOLCHOK, dlg );
}

void Q6220::setData( QParameter& Par, TGroup *dlg )
{
 setShData5( _STOLCHOK, dlg );
}

Boolean Q6220::valueTest( TGroup *dlg )
{
 return True;
}

char * const Q6230::title = "Q6230";

void Q6230::createDialog( QParameter& Par, QpDisplay& dsp )
{
 SpindelDialog( Par, dsp, 4, False );
}

void Q6230::getData( QParameter& Par, TGroup *dlg )
{
 shData(4) data;
 dlg->TGroup::getData( &data );
 for( register i = 0 ; i < NUMS; i++ )
 {
  double nf, fraction, integer;
  sscanf( data.dat[i][0],"%lf", &nf );
  fraction = modf( nf, &integer );
  _MOST[i][0] = (int)integer;
  _MOST[i][1] = ceil(fraction*100.);
 }
}

void Q6230::setData( QParameter& Par, TGroup *dlg )
{
 shData(4) data;
 for( register i = 0 ; i < NUMS; i++ )
 {
  double nf = (double)_MOST[i][0] + ((double)_MOST[i][1]/100.);
  sprintf( data.dat[i][0], "%1.2lf", nf );
 }
 dlg->TGroup::setData( &data );
}

Boolean Q6230::valueTest( TGroup *dlg )
{
 return True;
}

char * const Q6240::title = "Q6240";

void Q6240::createDialog( QParameter& Par, QpDisplay& dsp )
{
 SpindelDialog( Par, dsp, 4, False );
}

void Q6240::getData( QParameter& Par, TGroup *dlg )
{
 shData(4) data;
 dlg->TGroup::getData( &data );
 for( register i = 0 ; i < NUMS; i++ )
 {
  double nf, fraction, integer;
  sscanf( data.dat[i][0],"%lf", &nf );
  fraction = modf( nf, &integer );
  _MLEFT[i][0] = (int)integer;
  _MLEFT[i][1] = ceil(fraction*100.);
 }
}

void Q6240::setData( QParameter& Par, TGroup *dlg )
{
 shData(4) data;
 for( register i = 0 ; i < NUMS; i++ )
 {
  double nf = (double)_MLEFT[i][0] + ((double)_MLEFT[i][1]/100.);
  sprintf( data.dat[i][0], "%1.2lf", nf );
 }
 dlg->TGroup::setData( &data );
}

Boolean Q6240::valueTest( TGroup *dlg )
{
 return True;
}

char * const Q6250::title = "Q6250";

void Q6250::createDialog( QParameter& Par, QpDisplay& dsp )
{
 SpindelDialog( Par, dsp, 4, False );
}

void Q6250::getData( QParameter& Par, TGroup *dlg )
{
 shData(4) data;
 dlg->TGroup::getData( &data );
 for( register i = 0 ; i < NUMS; i++ )
 {
  double nf, fraction, integer;
  sscanf( data.dat[i][0],"%lf", &nf );
  fraction = modf( nf, &integer );
  _MRIGHT[i][0] = (int)integer;
  _MRIGHT[i][1] = ceil(fraction*100.);
 }
}

void Q6250::setData( QParameter& Par, TGroup *dlg )
{
 shData(4) data;
 for( register i = 0 ; i < NUMS; i++ )
 {
  double nf = (double)_MRIGHT[i][0] + ((double)_MRIGHT[i][1]/100.);
  sprintf( data.dat[i][0], "%1.2lf", nf );
 }
 dlg->TGroup::setData( &data );
}

Boolean Q6250::valueTest( TGroup *dlg )
{
 return True;
}

char * const Q6500::title = "Q6500";

void Q6500::createDialog( QParameter& Par, QpDisplay& dsp )
{
 TRect r = dsp.getExtent();
 r.a.x+=18;
 r.a.y+=4;
 r.b.x = r.a.x+12;
 r.b.y = r.a.y+1;
 TView *il = new TInputLine( r, 9 );
 r.a.y--;
 r.b.y--;
 dsp.insert( new TLabel( r, "~А~дрес CNC", il ) );
 dsp.insert( il );
}

void Q6500::getData( QParameter& Par, TGroup *dlg )
{
 dlg->TGroup::getData( _ADRCNC );
}

void Q6500::setData( QParameter& Par, TGroup *dlg )
{
 dlg->TGroup::setData( _ADRCNC );
}

Boolean Q6500::valueTest( TGroup *dlg )
{
 return True;
}

char * const Q7000::title = "Q7000";

void Q7000::createDialog( QParameter& Par, QpDisplay& dsp )
{
 TRect r( 10, 6, 43, 10 );
 TView *b = new TRadioButtons( r, new TSItem( "Нет контроля",
				  new TSItem( "Передний фронт",
				  new TSItem( "Задний фронт",
				  new TSItem( "Передний и задний", 0 )))) );
 TView *l = new TLabel( TRect(r.a.x, r.a.y-1, r.b.x, r.a.y ),
			"~К~онтроль датчика касания", b );
 dsp.insert( b );
 dsp.insert( l );
}

void Q7000::getData( QParameter& Par, TGroup *dlg )
{
 dlg->TGroup::getData( &_TESTER );
}

void Q7000::setData( QParameter& Par, TGroup *dlg )
{
 dlg->TGroup::setData( &_TESTER );
}

Boolean Q7000::valueTest( TGroup *dlg )
{
 return True;
}


#pragma warn .par

