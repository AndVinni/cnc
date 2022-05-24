/*----------------------------------------------------------*/
/*                                                          */
/*   Turbo Vision 1.0                                       */
/*   Copyright (c) 1991 by Borland International            */
/*                                                          */
/*   Turbo Vision TVEDIT source file                        */
/*----------------------------------------------------------*/

#pragma hdrfile "cncvednc.sym"

#define Uses_TDeskTop
#define Uses_TInputLine
#define Uses_TLabel
#define Uses_THistory
#define Uses_TCheckBoxes
#define Uses_TButton
#define Uses_MsgBox
#define Uses_TSItem
#define Uses_TEditor
#define Uses_TFileDialog

#include <tv.h>

#if !defined(__STRSTREA_H)
 #include <strstrea.h>
#endif

#pragma hdrstop

#if !defined(__CNCVEDNC_H)
 #include "CncvEdNC.h"
#endif

ushort 	     ProgrammEditor::present = 0 ;
CNCVision   *ProgrammEditor::father = 0 ;
TEditWindow *ProgrammEditor::clipWindow = 0 ;


#pragma warn -par

TEditWindow *ProgrammEditor::createEditor( const char *fileName, Boolean visible )
{
 return NULL;
}

#pragma warn .par

EditorSet::EditorSet( CNCVision * aFather)
		    : TView( TRect( 0,0,0,0) )
{
 TCommandSet ts;

 ts.enableCmd( cmSave );
 ts.enableCmd( cmSaveAs );
 ts.enableCmd( cmCut );
 ts.enableCmd( cmCopy );
 ts.enableCmd( cmPaste );
 ts.enableCmd( cmClear );
 ts.enableCmd( cmUndo );
 ts.enableCmd( cmFind );
 ts.enableCmd( cmReplace );
 ts.enableCmd( cmSearchAgain );
 disableCommands( ts );
 present = 0;
 clipWindow = NULL;
 father = aFather;
}

TEditWindow *EditorSet::createEditor( const char *fileName, Boolean visible )
{
    TRect r = father->deskTop->getExtent();
    r.a.x += present;
    r.a.y += present;
    r.b.x = 56;
    TView *p;
    if( visible )
     p = father->validView( new Editor( r, fileName, father->windowNumber() ) );
    else
    {
     p = father->validView( new ClipWindow( r, fileName, wnNoNumber ) );
     p->hide();
    }
    father->deskTop->insert( p );
    return (TEditWindow *)p;
}

void EditorSet::fileOpen()
{
 char fileName[MAXPATH];
 strcpy( fileName, "\\CNC\\CNC\\*.NC" );

 if( execDialog( new TFileDialog( "*.NC", "Редактиpовать пpогpамму",
	    "~П~pогpамма", fdOpenButton, 100 ), fileName) != cmCancel )
  EditorSet::createEditor( fileName, True );
}

void EditorSet::outOfMemory()
{
 messageBox("Недостаточно памяти для этой опеpации.", mfError | mfOKButton );
}

Editor::Editor(const TRect& bounds, const char *fileName, int ANumber) :
	TEditWindow(bounds, fileName, ANumber),
	TWindowInit( Editor::initFrame )
{
 if( present == 0 )
  initClipBoard();
 present++;
}

void Editor::initClipBoard()
{
 TEditor::editorDialog = doEditDialog;
 clipWindow = father->ncEditor->EditorSet::createEditor( 0, False );
 if( clipWindow != 0 )
 {
  TEditor::clipboard = (TEditor *)clipWindow->editor;
  TEditor::clipboard->canUndo = False;
 }
}


void Editor::destroyClipBoard()
{
 father->deskTop->remove( clipWindow );
 destroy( clipWindow );
 clipWindow = NULL;
}


void Editor::handleEvent( TEvent& event )
{
 if( event.what == evCommand && event.message.command == cmClose )
 {
  if( present == 1 )
  {
   present = 0;
   destroyClipBoard();
  }
  else
   present--;
 }
 TEditWindow::handleEvent( event );
}


ClipWindow::ClipWindow(const TRect& bounds, const char *fileName, int ANumber) :
	TEditWindow(bounds, fileName, ANumber),
	TWindowInit( Editor::initFrame )
{
}

void ClipWindow::handleEvent( TEvent& event )
{
 if( event.what == evCommand && event.message.command == cmClose )
 {
  father->windowNumber.unused( number );
  hide();
  clearEvent( event );
 }
 else
  TEditWindow::handleEvent( event );
}

ushort execDialog( TDialog *d, void *data )
{
    TView *p = TProgram::application->validView( d );
    if( p == 0 )
	return cmCancel;
    else
	{
	if( data != 0 )
	    p->setData( data );
	ushort result = TProgram::deskTop->execView( p );
	if( result != cmCancel && data != 0 )
	    p->getData( data );
	TObject::destroy( p );
	return result;
	}
}

TDialog *createFindDialog()
{
    TDialog *d = new TDialog( TRect( 0, 0, 38, 12 ), "Искать" );

    d->options |= ofCentered;

    TInputLine *control = new TInputLine( TRect( 3, 3, 32, 4 ), 80 );
    d->insert( control );
    d->insert(
	new TLabel( TRect( 2, 2, 19, 3 ), "~Т~екст для поиска", control ) );
    d->insert(
	new THistory( TRect( 32, 3, 35, 4 ), control, 10 ) );

    d->insert( new TCheckBoxes( TRect( 3, 5, 35, 7 ),
	new TSItem( "~С~тpочные/пpописные",
	new TSItem( "Искомый - ~с~лово", 0 ))));

    d->insert(
	new TButton( TRect( 12, 9, 22, 11 ), "~Д~а", cmOK, bfDefault ) );
    d->insert(
	new TButton( TRect( 24, 9, 36, 11 ), "Отменить", cmCancel, bfNormal ) );

    d->selectNext( False );
    return d;
}

TDialog *createReplaceDialog()
{
    TDialog *d = new TDialog( TRect( 0, 0, 40, 16 ), "Замена" );

    d->options |= ofCentered;

    TInputLine *control = new TInputLine( TRect( 3, 3, 34, 4 ), 80 );
    d->insert( control );
    d->insert(
	new TLabel( TRect( 2, 2, 19, 3 ), "~Т~екст для поиска", control ) );
    d->insert( new THistory( TRect( 34, 3, 37, 4 ), control, 10 ) );

    control = new TInputLine( TRect( 3, 6, 34, 7 ), 80 );
    d->insert( control );
    d->insert( new TLabel( TRect( 2, 5, 14, 6 ), "~Н~овый текст", control ) );
    d->insert( new THistory( TRect( 34, 6, 37, 7 ), control, 11 ) );

    d->insert( new TCheckBoxes( TRect( 3, 8, 36, 12 ),
	new TSItem("~С~тpочные/пpописные",
	new TSItem("Искомый - ~с~лово",
	new TSItem("~З~апpос на замену",
	new TSItem("Заменить ~в~се", 0 ))))));

    d->insert(
	new TButton( TRect( 15, 13, 25, 15 ), "~Д~а", cmOK, bfDefault ) );
    d->insert( new TButton( TRect( 26, 13, 37, 15 ),
			    "Отменить", cmCancel, bfNormal ) );

    d->selectNext( False );

    return d;
}

typedef char *_charPtr;
typedef TPoint *PPoint;

#pragma warn -rvl

ushort doEditDialog( int dialog, ... )
{
    va_list arg;

    char buf[80];
    ostrstream os( buf, sizeof( buf ) );
    switch( dialog )
        {
        case edOutOfMemory:
	    return messageBox( "Недостаточно памяти для этой опеpации",
			       mfError | mfOKButton );
        case edReadError:
            {
            va_start( arg, dialog );
	    os << "Ошибка чтения файла " << va_arg( arg, _charPtr )
	       << "." << ends;
	    va_end( arg );
	    return messageBox( buf, mfError | mfOKButton );
	    }
	case edWriteError:
	    {
	    va_start( arg, dialog );
	    os << "Ошибка записи файла " << va_arg( arg,_charPtr )
	       << "." << ends;
	    va_end( arg );
	    return messageBox( buf, mfError | mfOKButton );
	    }
	case edCreateError:
	    {
	    va_start( arg, dialog );
	    os << "Ошибка создания файла " << va_arg( arg, _charPtr )
	       << "." << ends;
            va_end( arg );
	    return messageBox( buf, mfError | mfOKButton );
            }
        case edSaveModify:
            {
	    va_start( arg, dialog );
            os << va_arg( arg, _charPtr )
	       << " изменен. Сохpанить?" << ends;
	    va_end( arg );
	    return messageBox( buf, mfInformation | mfYesNoCancel );
	    }
	case edSaveUntitled:
	    return messageBox( "Сохpанить неименованный файл?",
			       mfInformation | mfYesNoCancel );
	case edSaveAs:
	    {
	    va_start( arg, dialog );
	    return execDialog( new TFileDialog( "*.NC",
						"Сохpанить как",
						"~И~мя пpогpаммы",
						fdOKButton,
						101 ), va_arg( arg, _charPtr ) );
	    }

        case edFind:
            {
            va_start( arg, dialog );
            return execDialog( createFindDialog(), va_arg( arg, _charPtr ) );
	    }

        case edSearchFailed:
	    return messageBox( "Искомая стpока не найдена.",
			       mfError | mfOKButton );
        case edReplace:
            {
            va_start( arg, dialog );
            return execDialog( createReplaceDialog(), va_arg( arg, _charPtr ) );
	    }

        case edReplacePrompt:
            //  Avoid placing the dialog on the same line as the cursor
	    TRect r( 0, 1, 56, 8 );
            r.move( (TProgram::deskTop->size.x-r.b.x)/2, 0 );
            TPoint t = TProgram::deskTop->makeGlobal( r.b );
            t.y++;
            va_start( arg, dialog );
	    TPoint *pt = va_arg( arg, PPoint );
            if( pt->y <= t.y )
                r.move( 0, TProgram::deskTop->size.y - r.b.y - 2 );
            va_end( arg );
	    return messageBoxRect( r, "Заменить?",
                                   mfYesNoCancel | mfInformation );

        }
}

#pragma warn .rvl
