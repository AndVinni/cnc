/*
   cncvQpit.h

   Опpеделения классов создателей панелей диалога
   pедактиpования Q - паpаметpов.

   Copyright (c) ELMIS Ltd 1993.

*/

#ifndef __CNCVQPIT_H
 #define __CNCVQPIT_H


#define Uses_TRect
#define Uses_TScrollBar

#include <Tv.h>

#ifndef __CNCVEQPR_H
 #include "CncveQpr.h"
#endif

#if !defined( __CNCVTEDT_H )
 #include "CncvTedt.h"
#endif

#define defQpItem( suf,name )					\
								\
    class suf##name : public InitQpDisplay			\
    {      							\
    public:							\
     static char * const title;					\
     virtual char *getTitle() { return title; }			\
     virtual void createDialog( QParameter& Par, QpDisplay& dsp ); \
     virtual void getData( QParameter& Par, TGroup *dlg );      \
     virtual void setData( QParameter& Par, TGroup *dlg );      \
     virtual Boolean valueTest( TGroup* dlg );			\
    }								\

 defQpItem( Q,100 ); defQpItem( Q,110 ); defQpItem( Q,120 ); defQpItem( Q,130 );
 defQpItem( Q,140 ); defQpItem( Q,145 ); defQpItem( Q,150 ); defQpItem( Q,160 );
 defQpItem( Q,170 ); defQpItem( Q,180 ); defQpItem( Q,190 ); defQpItem( Q,200 );
 defQpItem( Q,210 ); defQpItem( Q,220 ); defQpItem( Q,225 ); defQpItem( Q,230 );
 defQpItem( Q,240 ); defQpItem( Q,250 );

 defQpItem( Q,500 ); defQpItem( Q,510 );
 defQpItem( Q,520 ); defQpItem( Q,530 ); defQpItem( Q,540 ); defQpItem( Q,550 );
 defQpItem( Q,560 ); defQpItem( Q,570 ); defQpItem( Q,580 ); defQpItem( Q,590 );
 defQpItem( Q,600 ); defQpItem( Q,610 ); defQpItem( Q,620 ); defQpItem( Q,1000 );
 defQpItem( Q,1010 ); defQpItem( Q,1020 ); defQpItem( Q,1030 ); defQpItem( Q,1040 );
 defQpItem( Q,1050 ); defQpItem( Q,1060 ); defQpItem( Q,1070 ); defQpItem( Q,1080 );
 defQpItem( Q,1090 ); defQpItem( Q,1100 ); defQpItem( Q,1110 ); defQpItem( Q,1500 );
 defQpItem( Q,1510 ); defQpItem( Q,1520 ); defQpItem( Q,1530 ); defQpItem( Q,1540 );
 defQpItem( Q,1550 ); defQpItem( Q,1560 ); defQpItem( Q,1570 ); defQpItem( Q,1580 );
 defQpItem( Q,1590 ); defQpItem( Q,1600 ); defQpItem( Q,1610 ); defQpItem( Q,1620 );
 defQpItem( Q,2000 ); defQpItem( Q,2010 ); defQpItem( Q,2020 ); defQpItem( Q,2030 );
 defQpItem( Q,2040 ); defQpItem( Q,2050 ); defQpItem( Q,2060 ); defQpItem( Q,2500 );
 defQpItem( Q,2510 ); defQpItem( Q,2520 ); defQpItem( Q,2530 ); defQpItem( Q,2540 );
 defQpItem( Q,3000 ); defQpItem( Q,3010 );
 defQpItem( Q,4000 );
 defQpItem( Q,4010 ); defQpItem( Q,4020 ); defQpItem( Q,4030 ); defQpItem( Q,4050 );
 defQpItem( Q,4060 ); defQpItem( Q,4070 ); defQpItem( Q,4080 );
 defQpItem( Q,4500 ); defQpItem( Q,4510 ); defQpItem( Q,4520 ); defQpItem( Q,4530 );
 defQpItem( Q,4540 );
 defQpItem( Q,5000 ); defQpItem( Q,5020 ); defQpItem( Q,5030 );
 defQpItem( Q,5040 ); defQpItem( Q,5050 ); defQpItem( Q,5060 ); defQpItem( Q,5070 );
 defQpItem( Q,5080 ); defQpItem( Q,5090 ); defQpItem( Q,5100 ); defQpItem( Q,5110 );
 defQpItem( Q,5120 ); defQpItem( Q,5130 ); defQpItem( Q,5140 ); defQpItem( Q,5150 );
 defQpItem( Q,5160 ); defQpItem( Q,5170 );
 defQpItem( Q,6000 ); defQpItem( Q,6005 ); defQpItem( Q,6010 );
 defQpItem( Q,6020 ); defQpItem( Q,6030 ); defQpItem( Q,6040 ); defQpItem( Q,6050 );
 defQpItem( Q,6070 ); defQpItem( Q,6080 ); defQpItem( Q,6090 );
 defQpItem( Q,6100 ); defQpItem( Q,6110 ); defQpItem( Q,6120 ); defQpItem( Q,6130 );
 defQpItem( Q,6140 ); defQpItem( Q,6150 ); defQpItem( Q,6160 ); defQpItem( Q,6170 );
 defQpItem( Q,6180 ); defQpItem( Q,6190 ); defQpItem( Q,6200 ); defQpItem( Q,6210 );
 defQpItem( Q,6220 ); defQpItem( Q,6230 ); defQpItem( Q,6240 ); defQpItem( Q,6250 );
 defQpItem( Q,6500 );
 defQpItem( Q,7000 );

#endif
