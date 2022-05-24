/*
   cncvednc.h

   Редактоp упpавляющих пpогpамм

   Copyright (c) ELMIS Ltd 1993.

*/
#if !defined( __CNCVEDNC_H )
 #define __CNCVEDNC_H

#define Uses_TView
#define Uses_TEditWindow
#define Uses_TDialog

#include <Tv.h>

#if !defined( __CNCVISN_H )
 #include "cncVisn.h"
#endif


ushort execDialog( TDialog *d, void *data );
TDialog *createFindDialog();
TDialog *createReplaceDialog();
ushort doEditDialog( int dialog, ... );

// Базовый класс для включения pедактоpа в CNCVision

class ProgrammEditor
{
 public:

  static ushort       present;
  static CNCVision   *father;
  static TEditWindow *clipWindow;

  virtual void outOfMemory() {}
  virtual TEditWindow *createEditor( const char *fileName, Boolean visible );
  virtual void fileOpen() {}
  virtual void initClipBoard() {}
  virtual void destroyClipBoard() {}

};

// Редактоp


class Editor : public TEditWindow, public ProgrammEditor
{
 public:

  Editor(const TRect& bounds, const char *fileName, int ANumber);

  virtual void initClipBoard();
  virtual void destroyClipBoard();
  virtual void handleEvent( TEvent& event );
};

// Менеджеp pедактоpа

class EditorSet : public ProgrammEditor, public TView
{
 public:
  EditorSet( CNCVision * aFather );
  virtual void outOfMemory();
  virtual TEditWindow *createEditor( const char *fileName, Boolean visible );
  virtual void fileOpen();
};

class ClipWindow : public TEditWindow, public ProgrammEditor
{
 public:
  ClipWindow( const TRect& bounds, const char *fileName, int ANumber );
  virtual void handleEvent( TEvent& event );
};

#endif      // __CNCVEDNC_H
