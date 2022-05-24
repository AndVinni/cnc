/*
   cncvUtil.h

   Опpеделения вспомогательных функций
   pедактоpа Q - паpаметpов.

   Copyright (c) ELMIS Ltd 1993.

*/

#ifndef __CNCVUTIL_H
 #define __CNCVUTIL_H

#if !defined(__STDIO_H)
 #include <StdIo.h>
#endif


#if !defined(__CNCVEQPR_H)
 #include "cncvEqPr.h"
#endif


#define dlgData(quant, size)	\
struct                  	\
{                       	\
 char dat[quant][size+1]; 	\
}

#define __getAxData( name, type, typet, func, size, kf )	\
								\
void name##size( type *data, TGroup *dlg );


#define _getAxData( name, type, typet, func, size, kf )		\
								\
void name##size( type *data, TGroup *dlg )       		\
{                                                       	\
 dlgData(NUM,size) d;                                        	\
 dlg->TGroup::getData( &d );					\
 for( register i = 0; i < NUM; i++ )                    	\
 {                                                      	\
  typet tmp = (typet)0;                                         \
  sscanf( d.dat[i], func, &tmp ) ;                      	\
  data[i] = (type)( tmp kf );                           	\
 }                                                      	\
}

#define __setAxData( name, type, typet, func, size, kf  )	\
								\
void  name##size( type *data, TGroup *dlg );

#define _setAxData( name, type, typet, func, size, kf  )	\
								\
void  name##size( type *data, TGroup *dlg )      		\
{								\
 dlgData(NUM,size) d;                                        	\
 for( register i = 0; i < NUM; i++ )				\
  sprintf( d.dat[i], func, ( ((typet)data[i]) kf) );    	\
 dlg->TGroup::setData( &d );                            	\
}


#define shData(size)						\
struct                  					\
{                       					\
 char dat[NUMS][MAXST][size+1];					\
}

#define __getShData( name, type, typet, func, size, kf )	\
								\
void name##size( type data[NUMS][MAXST], TGroup *dlg );

#define _getShData( name, type, typet, func, size, kf )         \
								\
void name##size( type data[NUMS][MAXST], TGroup *dlg )  	\
{                                                       	\
 shData(size) d;                                        	\
 dlg->TGroup::getData( &d );					\
 for( register i = 0; i < NUMS; i++ )                   	\
  for( register j = 0; j < MAXST; j++ )                 	\
  {                                                     	\
   typet tmp = (typet)0;                                        \
   sscanf( d.dat[i][j], func, &tmp ) ;                 	 	\
   data[i][j] = (type)( tmp kf );                       	\
  }                                                     	\
}

#define __setShData( name, type, typet, func, size, kf  )	\
								\
void  name##size( type data[NUMS][MAXST], TGroup *dlg );

#define _setShData( name, type, typet, func, size, kf  )	\
								\
void  name##size( type data[NUMS][MAXST], TGroup *dlg ) 	\
{								\
 shData(size) d;                                        	\
 for( register i = 0; i < NUMS; i++ )                   	\
  for( register j = 0; j < MAXST; j++ )                 	\
   sprintf( d.dat[i][j], func, ( ((typet)data[i][j]) kf) );	\
 dlg->TGroup::setData( &d );                            	\
}

extern void AxDialog	( QpDisplay&  dsp, ushort len );
extern void FoolAxDialog( QParameter& Par, QpDisplay& dsp, ushort len );
extern void LogAxDialog ( QParameter& Par, QpDisplay& dsp );
extern void LogShDialog ( QParameter& Par, QpDisplay& dsp );
extern void SpindelDialog( QParameter& Par, QpDisplay& dsp, ushort len, Boolean stup  );
extern void FoolLogShDialog( QParameter& Par, QpDisplay& dsp );
extern void FixedPointDialog( QParameter& Par, QpDisplay& dsp, ushort axIndex );
extern void NameProg( QpDisplay& dsp, ushort len );

extern Boolean isAx( char * name );
extern Boolean isShpindel( int name );
extern Boolean isNotUsed( char *name );
extern Boolean testAxName( TGroup *dlg );

extern void numPortDialog( char *header, QpDisplay& dsp );
extern void portDialog( char *header, QpDisplay& dsp );
extern void setAxName( int *data, TGroup *dlg );
extern void getAxName( int *data, TGroup *dlg );
extern void setShName( int *data, TGroup *dlg );
extern void getShName( int *data, TGroup *dlg );

extern  __setAxData( setAxData,  uchar, int,     "%u",    1, )
extern  __getAxData( getAxData,  uchar, int,     "%u",    1, )
extern  __setAxData( setAxData,  int, 	int,     "%i",    2, )
extern  __getAxData( getAxData,  int, 	int,     "%i",    2, )
extern  __setAxData( setAxData,  int, 	int,     "%i",    5, )
extern  __getAxData( getAxData,  int, 	int,     "%i",    5, )
extern  __setAxData( setuAxData, int,	unsigned,"%u",    5, )
extern  __getAxData( getuAxData, int, 	unsigned,"%u",    5, )
extern  __setAxData( setfAxData, int, 	float,   "%2.3f", 6, /1000. )
extern  __getAxData( getfAxData, int,	float,   "%f", 	  6, *1000. )
extern  __setAxData( setdAxData, double,float,   "%2.3f", 6, )
extern  __getAxData( getdAxData, double,float,   "%f",    6, )
extern  __setAxData( setlAxData, long,  float,   "%+4.3f",9, )
extern  __getAxData( getlAxData, long, 	float,   "%f",    9, )
extern  __setAxData( setdAxData, double,float,   "%+4.3f",9, )
extern  __getAxData( getdAxData, double,float,   "%f",    9, )
extern  __setAxData( setAxData,  long, 	long,    "%li",   7, )
extern  __getAxData( getAxData,  long, 	long,    "%li",   7, )
extern  __setAxData( setAxData,  int, 	int,     "%i",    4, )
extern  __getAxData( getAxData,  int, 	int,     "%i",    4, )
extern  __setAxData( setsAxData, int, 	int,     "%i",    6, )
extern  __getAxData( getsAxData, int, 	int,     "%i",    6, )

extern  __setShData( setuShData, unsigned,unsigned,"%u",  5, )
extern  __getShData( getuShData, unsigned,unsigned,"%u",  5, )
extern  __setShData( setShData,  int,   int,      "%i",   5, )
extern  __getShData( getShData,  int,   int,      "%i",   5, )
extern  __setShData( setfShData, int,   float,    "%2.3f",6, /1000. )
extern  __getShData( getfShData, int,   float,    "%f",   6, *1000. )
extern  __setShData( setfShData, long,  float,    "%3.3f",7, /1000. )
extern  __getShData( getfShData, long,  float,    "%f",   7, *1000. )
extern  __setShData( setiShData, int,   unsigned, "%u",   5, )
extern  __getShData( getiShData, int,   unsigned, "%u",   5, )



#endif
