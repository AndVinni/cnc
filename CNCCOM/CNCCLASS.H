/*
   cncclass.h

   Опpеделения уникальных констант классов CNC

   Copyright (c) ELMIS Ltd 1993.

*/

#if !defined( __CNCCLASS_H )
 #define __CNCCLASS_H

 #if !defined( __CLSTYPES_H )
  #include <ClsTypes.h>
 #endif



 const ParAxisClass    	= __firstUserClass;
 const QParameterClass 	= ParAxisClass + 1;


#endif
