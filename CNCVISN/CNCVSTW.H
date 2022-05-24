/*
   cncvstw.h

   Окно состояния УЧПУ

   Copyright (c) ELMIS ltd 1993.

*/

#if !defined(__CNCVSTW_H)
 #define __CNCVSTW_H

#define Uses_TView
#define Uses_TWindow
#define Uses_TParamText

#include <Tv.h>

#pragma option -po

class StatusWindow : public TWindow
{
 public:

   StatusWindow( ushort wnum );
};

class CNCParamText : public TView
{
 char *param;
 char patern;

 virtual void getText( char *dst, ushort maxVisiable ) = 0;

protected:

 Boolean dataVisiable;
 char *oldStr;

public:

 CNCParamText( const TRect& bounds, const char *aParam ,
	       const char aPatern );
 ~CNCParamText();
 void update();
 virtual void handleEvent(TEvent& event);
 virtual void draw();
};

class ShowNameProg : public CNCParamText
{
  virtual void getText( char *dst, ushort maxVisiable );

 public:

  ShowNameProg( const TRect& bounds ) :
		CNCParamText( bounds, "~%~", '*' ) {}
};

class ShowNameSubr : public CNCParamText
{
  virtual void getText( char *dst, ushort maxVisiable );

 public:

  ShowNameSubr( const TRect& bounds ) :
		CNCParamText( bounds, "~L~", '*' ) {}
};

class ShowNumStrProg : public CNCParamText
{
  virtual void getText( char *dst, ushort maxVisiable );

 public:

  ShowNumStrProg( const TRect& bounds ) :
	      CNCParamText( bounds, "~N~", '*' ) {}
};

class ShowNumStrSubr : public CNCParamText
{
  virtual void getText( char *dst, ushort maxVisiable );

 public:

  ShowNumStrSubr( const TRect& bounds ) :
	      CNCParamText( bounds, "~N~", '*' ) {}
};

class ShowS : public CNCParamText
{
  virtual void getText( char *dst, ushort maxVisiable );

 public:

  ShowS( const TRect& bounds ) :
	 CNCParamText( bounds, NULL, '*' ) {}
};

class ShowT : public CNCParamText
{
  virtual void getText( char *dst, ushort maxVisiable );

 public:

  ShowT( const TRect& bounds ) :
	 CNCParamText( bounds, NULL, '*' ) {}
};

class ShowF : public CNCParamText
{
  virtual void getText( char *dst, ushort maxVisiable );

 public:

  ShowF( const TRect& bounds ) :
	 CNCParamText( bounds, "~F~", '*' ) {}
};

class ShowTransporant : public CNCParamText
{
 public:

  ShowTransporant( TRect& bounds ) : CNCParamText( bounds, NULL, ' ' )
  { dataVisiable = True; }
  virtual void draw();
};

class ShowCNCMode : public ShowTransporant
{
  virtual void getText( char *dst, ushort maxVisiable );

 public:

  ShowCNCMode( TRect& bounds ) : ShowTransporant( bounds ) {}
};

class ShowMToolStatus : public ShowTransporant
{
  virtual void getText( char *dst, ushort maxVisiable );

 public:

  ShowMToolStatus( TRect& bounds ) : ShowTransporant( bounds ) {}
};

class ShowError : public ShowTransporant
{
  virtual void getText( char *dst, ushort maxVisiable );
  ushort topError;

 public:

  ShowError( TRect& bounds ) : ShowTransporant( bounds )
  {
   topError = 0; dataVisiable = False;
  }
  virtual void draw();
};

#pragma option -po.

#endif



