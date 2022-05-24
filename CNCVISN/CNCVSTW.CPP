/*
   cncvstw.cpp

   Окно состояния УЧПУ

   Copyright (c) ELMIS ltd 1993.

*/

#pragma hdrfile "cncvstw.sym"

#if! defined(__STRING_H)
 #include <String.h>
#endif

#if! defined(__STDIO_H)
 #include <StdIO.h>
#endif

#if! defined(__MEM_H)
 #include <Mem.h>
#endif

#pragma hdrstop

#if! defined(__CNCVSTW_H)
 #include "CncvStw.h"
#endif

#if! defined(__CNCVCLOC_H)
 #include "CncvCloc.h"
#endif

#if! defined(__CNCVCOM_H)
 #include "CncvCom.h"
#endif

#if !defined(__CNCCSTAT_H)
 #include "cnccStat.h"
#endif

#pragma option -po

StatusWindow::StatusWindow( ushort wnum ) :
	      TWindow( TRect(0,0,80,4), "СЧПУ", wnum ),
	      TWindowInit ( StatusWindow::initFrame )
{
 flags &= ~( wfMove | wfGrow | wfClose | wfZoom ) ;

 TRect e = getExtent();                      // Вставляем имя программы
 TRect r = e;
 r.a.x++;
 r.a.y++;
 r.b.x = r.a.x + 9;
 r.b.y = r.a.y + 1;
 insert(new ShowNameProg( r ));

 r.a.y++;
 r.b.y++;
 insert(new ShowNameSubr( r ));

 r = e;
 r.a.x += 11;
 r.b.x = r.a.x + 6;
 r.a.y++;
 r.b.y = r.a.y + 1;
 insert(new ShowNumStrProg( r ));

 r.a.y++;
 r.b.y++;
 insert(new ShowNumStrSubr( r ));

 r = e;
 r.a.x += 18;
 r.b.x = r.a.x + 8;
 r.a.y++;
 r.b.y = r.a.y + 1;
 insert(new ShowS( r ));

 r.a.y++;
 r.b.y++;
 r.b.x -= 3;
 insert(new ShowT( r ));

 r = e;
 r.a.x += 27;
 r.b.x = r.a.x + 6;
 r.a.y++;
 r.b.y = r.a.y + 1;
 insert(new ShowF( r ));

 r = e;
 r.a.x += 34;
 r.b.x = r.a.x + 16;
 r.a.y++;
 r.b.y = r.a.y + 1;
 insert(new ShowCNCMode( r ));

 r = e;
 r.a.x += 51;
 r.b.x = r.a.x + 16;
 r.a.y++;
 r.b.y = r.a.y + 1;
 insert(new ShowMToolStatus( r ));

 r = e;
 r.a.x += 24;
 r.b.x--;
 r.a.y += 2;
 r.b.y = r.a.y + 1;
 insert(new ShowError( r ));


 r = e;                      // Вставляем часики
 r.a.x = --r.b.x - 8;
 r.b.y = ++r.a.y + 1;
 insert(new TClockView( r ));
}


CNCParamText::CNCParamText( const TRect& bounds, const char *aParam,
			    const char aPatern ) : TView( bounds )
{
 eventMask = evCNCMessage;
 param = newStr( aParam );
 oldStr = new char[size.x<<1];
 setmem( oldStr, size.x, ' ');
 oldStr[size.x] = '\0';
 patern = aPatern ;
 dataVisiable = False;
}

CNCParamText::~CNCParamText()
{
 delete param;
 delete oldStr;
}

void CNCParamText::update()
{
 char tmp[128] = { 0 };

 if( param  )
  strcpy( tmp, param );
 char *buf = tmp + strlen( tmp );
 register unsigned remainder = size.x - cstrlen( tmp );
 getText( buf, remainder );
 buf = tmp + strlen( tmp );
 remainder = size.x - cstrlen( tmp );
 if( !dataVisiable )
 {
  setmem( buf , remainder, patern );
  buf[remainder] = '\0';
 }
 if( strcmp( oldStr, tmp ) != 0 )
 {
  strcpy( oldStr, tmp );
  drawView();
 }
}

void CNCParamText::draw()
{
 TDrawBuffer buf;
 ushort c = getColor(0x0201);
 buf.moveChar(0, ' ', c, size.x);
 buf.moveCStr(0, oldStr, c);
 writeLine(0, 0, size.x, 1, buf);
}

void CNCParamText::handleEvent(TEvent& event)
{
 if( event.what == evCNCMessage &&
     event.message.command == cmUpdate )
  update();
 else
  TView::handleEvent( event );
}

void ShowNameProg::getText( char *dst, ushort maxVisiable )
{
 if( !dataVisiable )
 {
  dataVisiable = True ;
  strncpy( dst, "12345678", maxVisiable );
 }
 else
  dataVisiable = False;
}

void ShowNameSubr::getText( char *dst, ushort maxVisiable )
{
 if( !dataVisiable )
 {
  dataVisiable = True ;
  strncpy( dst, "12345678", maxVisiable );
 }
 else
  dataVisiable = False;
}

void ShowNumStrProg::getText( char *dst, ushort maxVisiable )
{
 if( !dataVisiable )
 {
  dataVisiable = True ;
  strncpy( dst, "12345", maxVisiable );
 }
 else
  dataVisiable = False;
}

void ShowNumStrSubr::getText( char *dst, ushort maxVisiable )
{
 if( !dataVisiable )
 {
  dataVisiable = True ;
  strncpy( dst, "12345", maxVisiable );
 }
 else
  dataVisiable = False;
}

void ShowS::getText( char *dst, ushort maxVisiable )
{
 char tmp[81];
 if( !dataVisiable )
 {
  dataVisiable = True ;
  sprintf( tmp, "~%2s~123456", "S1" );
 }
 else
 {
  dataVisiable = False;
  sprintf( tmp, "~%2s~", "S1" );
 }
 strncpy( dst, tmp, maxVisiable+2);
}

void ShowT::getText( char *dst, ushort maxVisiable )
{
 char tmp[81];
 if( !dataVisiable )
 {
  dataVisiable = True ;
  sprintf( tmp, "~%2s~123", "T1" );
 }
 else
 {
  dataVisiable = False;
  sprintf( tmp, "~%2s~", "T1" );
 }
 strncpy( dst, tmp, maxVisiable+2);
}

void ShowF::getText( char *dst, ushort maxVisiable )
{
 if( !dataVisiable )
 {
  dataVisiable = True ;
  strncpy( dst, "12345", maxVisiable );
 }
 else
  dataVisiable = False;
}

void ShowTransporant::draw( )
{
 TDrawBuffer buf;
 ushort c = getColor(0x0507);
 buf.moveChar(0, ' ', c, size.x);
 buf.moveCStr(0, oldStr, c);
 writeLine(0, 0, size.x, 1, buf);
}

void ShowCNCMode::getText( char *dst, ushort maxVisiable )
{
 static char* textMode[]=
 {
  "",
  "Останов",
  "Ожидание",
  "Работа",
  "Связь",
  "Исполнено",
  "Конец УП",
  "Останов М00",
  "Останов К/К",
  "Нач. загрузка",
  "Фон. задача",
  "Останов М01",
  "Останов ЭА",
  "Останов цикла по К/К",
  "Загрузка",
  "Сброс"
 };

 sprintf( dst, "~ %s        ", textMode[sost] );
 dst[maxVisiable+1] = '~';
 dst[maxVisiable+2] = '\0';
}

void ShowMToolStatus::getText( char *dst, ushort maxVisiable )
{
 static char* textCNCMode[]=
 {
  "",
  " Ручной",
  " Автомат",
  " Коррекция",
  " Редактор",
  " Диагностика",
  " Покадровый",
  " Пропуск кадра /"
 };
 strncpy( dst, textCNCMode[prr], maxVisiable );
}

void ShowError::draw( )
{
 TDrawBuffer buf;
 unsigned char c = dataVisiable ? errorAttr : getColor(1);
 buf.moveChar(0, ' ', c, size.x);
 buf.moveStr(0, oldStr, c);
 writeLine(0, 0, size.x, 1, buf);
}

void ShowError::getText( char *dst, ushort maxVisiable )
{
 dataVisiable = True ;
 strncpy( dst, " Ошибка станка ", maxVisiable );
}

#pragma option -po.



