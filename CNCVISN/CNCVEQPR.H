/*
   cncveqpr.h

   Редактоp Q - паpаметpов

   Copyright (c) ELMIS Ltd 1993.

*/
#if !defined( __CNCVEQPR_H )
 #define __CNCVEQPR_H

#define Uses_TEvent
#define Uses_TDialog
#define Uses_THelpFile
#define Uses_fpstream
#define Uses_TRect
#define Uses_TScrollBar
#define Uses_TListViewer

#include <Tv.h>

#if !defined( __CNCVISN_H )
 #include "cncVisn.h"
#endif

#if !defined( __CNCPARD_H )
 #include "cncPard.h"
#endif

class QpGroup;
class QpGroupList;
class QpItem;
class QpDisplay;

class EditorQParam : public TDialog
{
 public:

  EditorQParam( ushort wnum, TRect& bounds, QpGroup *aGroups );
  ~EditorQParam( );

 virtual void handleEvent( TEvent& event );
 virtual Boolean valid( ushort command );
 void outOfMemory() { (( CNCVision* )owner)->outOfMemory(); }

 QParameter *par;
 Boolean changed;

private:

 QpGroupList *groups;
 QpItem *item;
 QpDisplay *display;
 Boolean notMemory;
 Boolean parNotFound;
 Boolean parNotWrite;
 Boolean parDeffect;

 void createQpEditor();
 void allocateParameters();
 void getData( QParameter& rec );
 void setData( QParameter& rec );
 void saveData( );
 void loadData( );

};

extern QpGroup *initQpGroup( void );

class InitQpDisplay;

class QpItem
{
public:

 QpItem( const char *nm, int hc, InitQpDisplay *dsp = 0, QpItem *nxt = 0 );
 virtual ~QpItem();

 const char *name;
 int helpCtxt;
 QpItem *next;
 InitQpDisplay *initDisplay;

 friend QpGroup& operator + ( QpGroup&, QpItem& );
 friend QpItem& operator + ( QpItem& i1, QpItem& i2);

};

class QpGroup
{
public:

 QpGroup( const char *nm, QpItem *itm = 0, QpGroup *nxt = 0 );
 virtual ~QpGroup();

 const char *name;
 QpItem *items;
 QpGroup *next;

 friend QpGroup& operator + ( QpGroup&, QpItem&);
 friend QpGroup& operator + ( QpGroup& g1, QpGroup& g2);

};

class QpGroupList : public TListViewer
{
public:

 QpGroupList( const TRect& bounds, TScrollBar *aScrollBar, QpGroup *aGroups);
 virtual ~QpGroupList();

 virtual void focusItem( short item);
 virtual void getText( char *dest, short item, short maxLen );

protected:

 QpGroup *groups;

};

class QpItemList : public TListViewer
{

public:

 QpItemList( const TRect& bounds, TScrollBar *aScrollbar, QpItem *aItems );
 virtual void focusItem( short item );
 virtual void getText( char *dest, short item, short maxLen );
 virtual void handleEvent( TEvent& event );

protected:

 QpItem *items;

};

#if !defined( __CNCVHELP_H )
 #include "cncvHelp.h"
#endif

class QpHelpViewer : public THelpViewer
{
public:
 QpHelpViewer( const TRect& bounds, TScrollBar* b1,
	       TScrollBar* b2, THelpFile* hf, int hCtxt ) :
	       THelpViewer( bounds, b1, b2, hf, hCtxt ) { }
 virtual void handleEvent( TEvent& event );
};

class InitQpDisplay
{
 public:

  virtual char *getTitle() = 0;
  virtual void createDialog( QParameter& Par, QpDisplay& dsp ) = 0;
  virtual void getData( QParameter& Par, TGroup *dlg ) = 0;
  virtual void setData( QParameter& Par, TGroup *dlg ) = 0;
  virtual Boolean valueTest( TGroup* dlg ) = 0;
};

class QpDisplay : public TDialog
{
 InitQpDisplay * initDisplay;
 Boolean changed;
public:

 QpDisplay( TRect bounds, InitQpDisplay *dsp );

 virtual void handleEvent( TEvent& event );
 virtual Boolean valid( ushort command );

 Boolean valueTest();
 void getData(void *rec);
 void setData(void *rec);

 Boolean newSelect;
};

#endif      // __CNCVEQPR_H
