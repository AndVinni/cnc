#ifndef __cplusplus
#error Must use C++ for the type iostream.
#endif

#ifndef __SERSTREAM_H
#define __SERSTREAM_H

#if !defined(__IOSTREAM_H)
#include <iostream.h>
#endif

#if !defined(__CHCONF_H)
#include <chconfig.h>
#endif

_CLASSDEF(serstream)

class _CLASSTYPE serstream::public iostream
   {
   public:
   serstream( streambuf _FAR *, chanConfig& );

   // Init default stream
   serstream( streambuf _FAR * );
   virtual ~serstream();

   };

