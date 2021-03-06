/*
   cncveqpr.cpp

   ������p Q - ��p����p��

   Copyright (c) ELMIS Ltd 1993.

*/


#pragma hdrfile "cncveqpr.sym"

#define Uses_TKeys
#define Uses_TLabel
#define Uses_MsgBox

#include <tv.h>

#pragma hdrstop

#if !defined( __CNCVCOM_H )
 #include "CncvCom.h"
#endif

#if !defined( __CNCVEQPR_H )
 #include "CncveQpr.h"
#endif

#if !defined( __CNCVQPHC_H )
 #include "CncvQpHc.h"
#endif

#if !defined( __CNCVEDNC_H )
 #include "CncvEdNc.h"
#endif

#if !defined( __CNCVQPIT_H )
 #include "CncvQpIt.h"
#endif

EditorQParam::EditorQParam( ushort wnum, TRect& bounds, QpGroup *aGroups) :
	      TDialog( bounds , "������p Q-��p����p��" ),
	      TWindowInit( EditorQParam::initFrame )
{
 number = wnum;
 disableCommand( cmEditQParam );
 flags = ( wfMove | wfClose );
 notMemory   =
 parNotFound =
 parNotWrite =
 parDeffect  =
 changed     = False;

 TRect r = getExtent();
 r.a.x +=2;
 r.a.y = r.b.y - 3;
 r.b.x = r.a.x + 17;
 r.b.y--;
 insert(new TButton(r, "�~�~����p�����", cmEditQpItem, bfDefault));
 r.a.x += 19;
 r.b.x += 19;
 insert(new TButton(r, "���p�~�~���", cmSave, bfNormal));
 r.a.x += 19;
 r.b.x += 19;
 insert(new TButton(r, "�~�~⨢�p�����", cmAktivateQp, bfNormal));
 r.a.x += 19;
 r.b.x += 19;
 insert(new TButton(r, "�~�~室", cmClose, bfNormal));
 r.a.x = 2;
 r.a.y = 2 ;
 r.b.x = r.a.x + 23;
 r.b.y -= 3;
 TScrollBar *sb = new TScrollBar( TRect( r.b.x, r.a.y, r.b.x+1, r.b.y) );
 insert( sb );
 groups = new QpGroupList( r , sb, aGroups);
 insert( groups );
 insert( new TLabel( TRect(r.a.x,1,r.b.x,2),"~�~p㯯� ��p����p��", groups ));

 r.a.x += 25;
 r.b.x += 25;

 sb = new TScrollBar( TRect( r.b.x, r.a.y, r.b.x+1, r.b.y) );
 insert( sb );
 TView *p = new QpItemList( r , sb, aGroups->items );
 insert( p );
 insert( new TLabel( TRect(r.a.x,1,r.b.x,2),"�~�~p����p�", p ));

 r.a.x += 25;
 r.b.x += 28;

 fpstream *helpStrm = new fpstream( "CNCVQPHC.HLP", ios::in|ios::binary);
 THelpFile *helpFile =  new THelpFile(*helpStrm);
 QpHelpViewer *helpViewer = new QpHelpViewer (r, 0, 0, helpFile, hcQ100 );
 helpViewer->setState( sfShadow, False );
 helpViewer->options &= ~ofSelectable;
 insert( helpViewer );
 insert( new TStaticText( TRect( r.a.x+1, 1, r.b.x, 2 ), "���p����"));

 setCurrent( groups, normalSelect );
 groups->focusItem( 0 );

 allocateParameters();
 if( !notMemory )
  loadData();
}

EditorQParam::~EditorQParam()
{
 enableCommand( cmEditQParam );
 if( par )
  delete par;
}

void EditorQParam::allocateParameters()
{
 if( lowMemory() )
   notMemory = True;
 else
 {
  unsigned size = sizeof( QParameter );
  unsigned cikl = size / 4096;
  uchar *tmpBuff = 0;

  for( unsigned i = 0 ; cikl != 0 ; cikl-- )
  {
   i += 4096;
   tmpBuff = new uchar[ i ];
   if( tmpBuff )
   {
    if( lowMemory() )
     notMemory = True;
    delete tmpBuff;
   }
   else
    notMemory = True;
  }
  if( !notMemory )
  {
   par = new QParameter;
   if( lowMemory() )
   {
    notMemory = True;
    delete par;
   }
  }
 }
}

void EditorQParam::getData( QParameter& rec)
{
 rec = *par ;
}

void EditorQParam::setData( QParameter& rec)
{
 *par = rec;
}

void EditorQParam::saveData( )
{
 par->calcConst();
 ofstream out( "\\CNC\\CNCRSC\\QPARAMET.DAT", ios::binary );
 if( !out || !par->valid )
  parNotWrite = True;
 else
 {
  out.write( par->headerPar, strlen( par->headerPar )+1 );
  out << *par;
 }
}

void EditorQParam::loadData( )
{
 ifstream in( "\\CNC\\CNCRSC\\QPARAMET.DAT", ios::binary );
 if( !in )
 {
  parNotFound = True;
  disableCommand( cmAktivateQp );
 }
 else
 {
  ushort size =  strlen( par->headerPar )+1;
  char *buff = new char[ size ];
  in.read( buff, size );
  if( strcmp( buff, par->headerPar ) != 0 )
  {
   parDeffect = True;
   disableCommand( cmAktivateQp );
   par->clear();
  }
  else
  {
   in >> *par;
   if( !par->valid )
   {
    parDeffect = True;
    disableCommand( cmAktivateQp );
    par->clear();
   }
  }
  delete buff;
 }
}

void EditorQParam::handleEvent( TEvent& event )
{
 TDialog::handleEvent( event );

 switch( event.what )
 {
  case evBroadcast:

   switch( event.message.command )
   {
    case cmNewQpHelpCtxt:
     item = ( QpItem *)event.message.infoPtr;
    break;
   }
  break;

  case evCommand:

   switch( event.message.command )
   {
    case cmEditQpItem:
     createQpEditor();
    break;

    case cmSave:
     if( valid( cmSave ) )
     {
      saveData();
      if( valid( cmSave ) )
      {
       changed = False;
       disableCommand( cmSave );
      }
     }
    break;

    case cmAktivateQp:
     if( valid( cmAktivateQp ) )
     {
      saveData();
      if( valid( cmSave ) )
      {
       changed = False;
       disableCommand( cmSave );
       getData( Par );
//       activateQp();
      }
     }
    break;

    case cmClose:
     message( this, evCommand, cmClose, this );
    break;
   }
  break;
 }
}

Boolean EditorQParam::valid( ushort command )
{
 Boolean control = TDialog::valid( command );

 switch( command )
 {
  case cmValid:
   if( notMemory )
   {
    outOfMemory();
    return False;
   }
   if( parNotFound )
   {
    messageBox( "\x003���������� ���p㧨�� ��p����p�!", mfError | mfYesButton );
    parNotFound = False;
    return True;
   }
   if( parDeffect )
   {
    messageBox( "\x003���� ��p����p�� �ᯮp祭! "
		"��९��� 䠩� \"qparam.dat\" � "
		"���᭮�� ��᪠ ��� ������ ������.", mfError | mfYesButton );
    return True;
   }
  break;

  case cmClose:
   if( changed )
   {
    ushort cm = messageBox( mfWarning | mfYesNoCancel,"\x003���p����� ���������?" );
    switch( cm )
    {
     case cmYes:
      message( this, evCommand, cmSave, 0);
      return False;
     case cmNo:
      disableCommand( cmSave );
      return control;
     case cmCancel:
      return False;
    }
   }
  break;

  case cmAktivateQp:
  case cmSave:
   if( parNotWrite )
   {
    messageBox( "\x003���������� ��p����� ��p����p�!", mfError | mfYesButton );
    parNotWrite = False;
    return False;
   }
  break;

 }
 return control;
}

void EditorQParam::createQpEditor()
{
 TRect r = getExtent();
 r.b.x -= 28;
 display = new QpDisplay( r, item->initDisplay );
 display->flags = wfClose;
 if( item->initDisplay )
  item->initDisplay->createDialog( *par, *display );
 display->insert( new DefaultButton(
  TRect(r.a.x+1, r.b.y-3, r.a.x+14, r.b.y-1 ), "~�~��������", cmDefault, bfDefault));
 display->insert( new TButton(
  TRect(r.a.x+15, r.b.y-3, r.a.x+27, r.b.y-1 ), "~�~⬥����", cmCancel, bfNormal));
 if( execDialog( display , par ) != cmCancel )
 {
  changed = True;
  par->valid = True;
  enableCommand( cmSave );
  enableCommand( cmAktivateQp );
 }
}

QpGroup *initQpGroup( void )
{
 QpGroup &group100 =
  *new QpGroup("��p����p� �ᥩ") +
   *new QpItem("��p�� �ᥩ", 		hcQ100, new Q100 )+
   *new QpItem("��p�� �����", 		hcQ110, new Q110 )+
   *new QpItem("���⢥�ᢨ� �ᥩ", 	hcQ120, new Q120 )+
   *new QpItem("��p��� �ᥩ", 		hcQ130, new Q130 )+
   *new QpItem("��� �ᥩ",	 	hcQ140, new Q140 )+
   *new QpItem("����஭�� ��", 	hcQ145, new Q145 )+
   *new QpItem("������ ����樥��", 	hcQ150, new Q150 )+
   *new QpItem("��� ���p�⭮� ��", 	hcQ160, new Q160 )+
   *new QpItem("���p����. ᯮᮡ�����",hcQ170, new Q170 )+
   *new QpItem("�����ᮢ �� ���p�����",hcQ180, new Q180 )+
   *new QpItem("�������� �ᥩ", 	hcQ190, new Q190 )+
   *new QpItem("�������᪠� ��������",hcQ200, new Q200 )+
   *new QpItem("������ �p㣮���", 	hcQ210, new Q210 )+
   *new QpItem("�����p���� MS", 	hcQ220, new Q220 )+
   *new QpItem("�����p���� ᫥�����", 	hcQ225, new Q225 )+
   *new QpItem("���p���. ����p�⥫쭮�",hcQ230, new Q230 )+
   *new QpItem("����p����� ���", 	hcQ240, new Q240 )+
   *new QpItem("��������� �p���", 	hcQ250, new Q250 );

 QpGroup &group500 =
  *new QpGroup("��p����p� ᪮p���") +
   *new QpItem("���ᨬ��쭠� �����", 	hcQ500, new Q500 )+
   *new QpItem("�᪮p���� 室",	hcQ510, new Q510 )+
   *new QpItem("���p���� ��室����", 	hcQ520, new Q520 )+
   *new QpItem("���������� ᪮p����", 	hcQ530, new Q530 )+
   *new QpItem("���p���� � ���p���",  	hcQ540, new Q540 )+
   *new QpItem("��������� p�筠�", 	hcQ550, new Q550 )+
   *new QpItem("�p����� p�筠�", 	hcQ560, new Q560 )+
   *new QpItem("����p�� p�筠�", 	hcQ570, new Q570 )+
   *new QpItem("�᪮p����� p�筠�", 	hcQ580, new Q580 )+
   *new QpItem("���ᨬ. �� �p����p��", hcQ590, new Q590 )+
   *new QpItem("���p����� p��ᮣ���.",  hcQ600, new Q600 )+
   *new QpItem("�p��� ����������", 	hcQ610, new Q610 )+
   *new QpItem("�p����쭮� �᪮p����", 	hcQ620, new Q620 );

 QpGroup &group1000 =
  *new QpGroup("�������� �ᥩ") +
   *new QpItem("����樥�� �ᨫ����", 	hcQ1000, new Q1000 )+
   *new QpItem("����樥�� � �`key", 	hcQ1010, new Q1010 )+
   *new QpItem("�᪮p���� p���./�p�.",	hcQ1020, new Q1020 )+
   *new QpItem("��窠 p������", 	hcQ1030, new Q1030 )+
   *new QpItem("��窠 �p�������", 	hcQ1040, new Q1040 )+
   *new QpItem("�����樮���� �᪮p��.", hcQ1050, new Q1050 )+
   *new QpItem("�����樮���� �窠",   hcQ1060, new Q1060 )+
   *new QpItem("��p�室��� ᯮᮡ�����",hcQ1070, new Q1070 )+
   *new QpItem("���. �p��p. �᪮p����",	hcQ1080, new Q1080 )+
   *new QpItem("����. �p��p. �᪮p����",hcQ1090, new Q1090 )+
   *new QpItem("���. �p��p. KV", 	hcQ1100, new Q1100 )+
   *new QpItem("����. �p��p. KV", 	hcQ1110, new Q1110 );

 QpGroup &group1500 =
  *new QpGroup("����樨") +
   *new QpItem("���p���� �㫥���", 	hcQ1500, new Q1500 )+
   *new QpItem("���饭�� ���p���", 	hcQ1510, new Q1510 )+
   *new QpItem("�����p���� ��p���祭��",hcQ1520, new Q1520 )+
   *new QpItem("��p���祭�� � \"+\"", 	hcQ1530, new Q1530 )+
   *new QpItem("��p���祭�� � \"-\"", 	hcQ1540, new Q1540 )+
   *new QpItem("���� O`key", 		hcQ1550, new Q1550 )+
   *new QpItem("���p����� p��ᮣ���.", 	hcQ1560, new Q1560 )+
   *new QpItem("���������� p��ᮣ���.",	hcQ1570, new Q1570 )+
   *new QpItem("G28", 			hcQ1580, new Q1580 )+
   *new QpItem("G128", 			hcQ1590, new Q1590 )+
   *new QpItem("G228", 			hcQ1600, new Q1600 )+
   *new QpItem("G328", 			hcQ1610, new Q1610 )+
   *new QpItem("G428", 			hcQ1620, new Q1620 );

 QpGroup &group2000 =
  *new QpGroup("��pp��樨") +
   *new QpItem("����", 			hcQ2000, new Q2000 )+
   *new QpItem("��pp���� ����",	hcQ2010, new Q2010 )+
   *new QpItem("��p��� ��pp��樨", 	hcQ2020, new Q2020 )+
   *new QpItem("��� ��pp��樨",		hcQ2030, new Q2030 )+
   *new QpItem("��砫쭠� �窠",	hcQ2040, new Q2040 )+
   *new QpItem("������⢮ �祪", 	hcQ2050, new Q2050 )+
   *new QpItem("����稭� ��pp��樨", 	hcQ2060, new Q2060 );

 QpGroup &group2500 =
  *new QpGroup("��⥭樮���p�") +
   *new QpItem("�p���� �p�������", 	hcQ2500, new Q2500 )+
   *new QpItem("��⥭樮���p� F",	hcQ2510, new Q2510 )+
   *new QpItem("��⥭樮���p� S",	hcQ2520, new Q2520 )+
   *new QpItem("��� �᪮p������", 	hcQ2530, new Q2530 )+
   *new QpItem("��� ��p���쭮��",	hcQ2540, new Q2540 );

 QpGroup &group3000 =
  *new QpGroup("�ᯮ�����. �㭪樨") +
   *new QpItem("������⢮ �p㯯",	hcQ3000, new Q3000 )+
   *new QpItem("�㭪樨 � V-��⠭����", hcQ3010, new Q3010 );

 QpGroup &group4000 =
  *new QpGroup("��孮�����") +
   *new QpItem("�p��p���� �� G",	hcQ4000, new Q4000 )+
   *new QpItem("G ��� �p��p���",	hcQ4010, new Q4010 )+
   *new QpItem("�p��p���� �� M",	hcQ4020, new Q4020 )+
   *new QpItem("M ��� �p��p���",	hcQ4030, new Q4030 )+
   *new QpItem("G90/G91",		hcQ4050, new Q4050 )+
   *new QpItem("G68/G69",		hcQ4060, new Q4060 )+
   *new QpItem("G145/G146",		hcQ4070, new Q4070 )+
   *new QpItem("�⢮�",			hcQ4080, new Q4080 );

 QpGroup &group4500 =
  *new QpGroup("��p��p��") +
   *new QpItem("��p� PLC", 		hcQ4500, new Q4500 )+
   *new QpItem("��p� DRC", 		hcQ4510, new Q4510 )+
   *new QpItem("��p� DNC", 		hcQ4520, new Q4520 )+
   *new QpItem("��p� ��p�p��p�", 	hcQ4530, new Q4530 )+
   *new QpItem("��p� ����", 		hcQ4540, new Q4540 );

 QpGroup &group5000 =
  *new QpGroup("������ �몫��⥫�") +
   *new QpItem("������ �몫��⥫�", 	hcQ5000, new Q5000 )+
   *new QpItem("����p. �窨 1 - ��",	hcQ5020, new Q5020 )+
   *new QpItem("����p. �窨 2 - ��",	hcQ5030, new Q5030 )+
   *new QpItem("����p. �窨 3 - ��",	hcQ5040, new Q5040 )+
   *new QpItem("����p. �窨 4 - ��",	hcQ5050, new Q5050 )+
   *new QpItem("����p. �窨 5 - ��",	hcQ5060, new Q5060 )+
   *new QpItem("����p. �窨 6 - ��",	hcQ5070, new Q5070 )+
   *new QpItem("����p. �窨 7 - ��",	hcQ5080, new Q5080 )+
   *new QpItem("����p. �窨 8 - ��",	hcQ5090, new Q5090 )+
   *new QpItem("����p. �窨 9 - ��",	hcQ5100, new Q5100 )+
   *new QpItem("����p. �窨 10 - ��",hcQ5110, new Q5110 )+
   *new QpItem("����p. �窨 11 - ��",hcQ5120, new Q5120 )+
   *new QpItem("����p. �窨 12 - ��",hcQ5130, new Q5130 )+
   *new QpItem("����p. �窨 13 - ��",hcQ5140, new Q5140 )+
   *new QpItem("����p. �窨 14 - ��",hcQ5150, new Q5150 )+
   *new QpItem("����p. �窨 15 - ��",hcQ5160, new Q5160 )+
   *new QpItem("����p. �窨 16 - ��",hcQ5170, new Q5170 );

 QpGroup &group6000 =
  *new QpGroup("��p����p� 诨�����") +
   *new QpItem("���� 诨������",	hcQ6000, new Q6000 )+
   *new QpItem("��p�⭠� ���",	hcQ6005, new Q6005 )+
   *new QpItem("���몠��� �����p�",	hcQ6010, new Q6010 )+
   *new QpItem("��㯥��",		hcQ6020, new Q6020 )+
   *new QpItem("��������� ���p���",	hcQ6030, new Q6030 )+
   *new QpItem("���ᨬ���� ���p���",	hcQ6040, new Q6040 )+
   *new QpItem("���p���� �p����樨",	hcQ6050, new Q6050 )+
   *new QpItem("����p����� M3",		hcQ6070, new Q6070 )+
   *new QpItem("����p����� M4",		hcQ6080, new Q6080 )+
   *new QpItem("���p��� ��� ��p�����.", hcQ6090, new Q6090 )+
   *new QpItem("������㤠 ��砭��",	hcQ6100, new Q6100 )+
   *new QpItem("����� ��砭��",	hcQ6110, new Q6110 )+
   *new QpItem("���� O`key",		hcQ6120, new Q6120 )+
   *new QpItem("��� �p����樨",	hcQ6130, new Q6130 )+
   *new QpItem("KV",			hcQ6140, new Q6140 )+
   *new QpItem("�᪮p���� p���./�p�.",	hcQ6150, new Q6150 )+
   *new QpItem("����",			hcQ6160, new Q6160 )+
   *new QpItem("���ᨬ���. �⪫������",hcQ6170, new Q6170 )+
   *new QpItem("KV ᫥�����",		hcQ6180, new Q6180 )+
   *new QpItem("���p��� ᫥�����",	hcQ6190, new Q6190 )+
   *new QpItem("�㫥�� ���p���",	hcQ6200, new Q6200 )+
   *new QpItem("��� ��p����祭��",	hcQ6210, new Q6210 )+
   *new QpItem("���窮��� ᪮p����",	hcQ6220, new Q6220 )+
   *new QpItem("��� ��⠭���",		hcQ6230, new Q6230 )+
   *new QpItem("��� ������",		hcQ6240, new Q6240 )+
   *new QpItem("��� �p�����",		hcQ6250, new Q6250 );

 QpGroup &group6500 =
  *new QpGroup("��p����p� DNC") +
   *new QpItem("��p��",			hcQ6500, new Q6500 );

 QpGroup &group7000 =
  *new QpGroup("��p����p� ��⥬�") +
   *new QpItem("���稪 ��ᠭ��",	hcQ7000, new Q7000 );

 QpGroup& qParList = group100 + group500 + group1000 + group1500 +
		     group2000 + group2500 + group3000 + group4000 +
		     group4500 + group5000 + group6000 + group6500 +
		     group7000;
 return &qParList;
}

QpItem::QpItem( const char *nm, int hc, InitQpDisplay *dsp, QpItem *nxt)
{
 helpCtxt = hc;
 next = nxt;
 name = newStr( nm );
 initDisplay = dsp;
}

QpItem::~QpItem()
{
 delete (char *)name;
 if( initDisplay )
  delete initDisplay;
}

QpGroup::QpGroup( const char *nm, QpItem *itm, QpGroup *nxt )
{
 items = itm;
 next = nxt;
 name = newStr( nm );
}

QpGroup::~QpGroup()
{
 delete (char *)name;
}

QpItem& operator + ( QpItem& i1, QpItem& i2 )
{
 QpItem *cur = &i1;
 while( cur->next != 0 )
  cur = cur->next;
 cur->next = &i2;
 return i1;
}

QpGroup& operator + ( QpGroup& g, QpItem& i)
{
 QpGroup *grp = &g;
 while( grp->next != 0 )
  grp = grp->next;
 if( grp->items == 0 )
  grp->items = &i;
 else
 {
  QpItem *cur = grp->items;
  while( cur->next != 0 )
   cur = cur->next;
  cur->next = &i;
 }
 return g;
}

QpGroup& operator + ( QpGroup& g1, QpGroup& g2 )
{
 QpGroup *cur = &g1;
 while( cur->next != 0 )
  cur = cur->next;
 cur->next = &g2;
 return g1;
}

QpGroupList::QpGroupList( const TRect& bounds, TScrollBar *aScrollBar,
			  QpGroup *aGroups ) :
	     TListViewer( bounds, 1, 0, aScrollBar ),
	     groups( aGroups )
{
 int i = 0;
 while( aGroups != 0 )
 {
  aGroups = aGroups->next;
  i++;
 }
 setRange( i );
}

static void freeItems( QpItem *curItem )
{
 while( curItem != 0 )
 {
  QpItem *p = curItem;
  curItem = curItem->next;
  delete p;
 }
}

static void freeGroups( QpGroup *curGroup )
{
 while( curGroup != 0 )
 {
  QpGroup *p = curGroup;
  freeItems( curGroup->items );
  curGroup = curGroup->next;
  delete p;
 }
}

QpGroupList::~QpGroupList()
{
 freeGroups( groups );
}

void QpGroupList::focusItem( short item )
{
 TListViewer::focusItem( item );
 QpGroup *curGroup = groups;
 while( item-- > 0 )
  curGroup = curGroup->next;
 message( owner, evBroadcast, cmNewQpItem, curGroup->items );
}

void QpGroupList::getText( char *dest, short item, short)
{
 QpGroup *curGroup = groups;
 while( item-- > 0 )
  curGroup = curGroup->next;
 strcpy( dest, curGroup->name );
}

QpItemList::QpItemList( const TRect& bounds, TScrollBar *aScrollBar,
			QpItem *aItems ) :
	    TListViewer( bounds, 1, 0, aScrollBar ),
	    items( aItems )
{
 int i = 0;
 while( aItems != 0)
 {
  aItems = aItems->next;
  i++;
 }
 setRange( i );
}

void QpItemList::focusItem( short item )
{
 TListViewer::focusItem( item );
 QpItem *curItem = items;
 while( item-- > 0 )
  curItem = curItem->next;
 message( owner, evBroadcast, cmNewQpHelpCtxt, curItem );
}

void QpItemList::getText( char *dest, short item, short )
{
 QpItem *curItem = items;
 while( item-- > 0 )
  curItem = curItem->next;
 strcpy( dest, curItem->name );
}

void QpItemList::handleEvent( TEvent& event )
{
 TListViewer::handleEvent( event );
 if( event.what == evBroadcast && event.message.command == cmNewQpItem )
 {
  items = (QpItem*)event.message.infoPtr;
  QpItem *curItem = items;
  int i = 0;
  while( curItem != 0 )
  {
   curItem = curItem->next;
   i++;
  }
  setRange( i );
  focusItem( 0 );
  drawView();
 }
}

void QpHelpViewer::handleEvent( TEvent& event )
{
 THelpViewer::handleEvent( event );

 if( event.what == evBroadcast && event.message.command == cmNewQpHelpCtxt )
 {
  QpItem *item = ( QpItem * )event.message.infoPtr;
  switchToTopic( item->helpCtxt );
 }
}

QpDisplay::QpDisplay( TRect bounds, InitQpDisplay *dsp ) :
	   TDialog( bounds, 0 ),
	   TWindowInit( QpDisplay::initFrame )
{
 initDisplay = dsp;
 if( initDisplay )
  title = newStr( initDisplay->getTitle() );
 changed = newSelect = False;
 options |= ofCenterY;
}

void QpDisplay::handleEvent( TEvent& event )
{
 if( event.what == evCommand && event.message.command == cmDefault )
 {
  if( !changed )
   message( this, evCommand, cmCancel, 0);
  else
   if( valueTest() )
    message( this, evCommand, cmOK, 0);
 }
 if( event.what == evKeyDown && newSelect )
 {
  if( event.keyDown.keyCode == kbUp )
   event.keyDown.keyCode = kbShiftTab;
  else
   if( event.keyDown.keyCode == kbDown )
    event.keyDown.keyCode = kbTab;
 }
 if( event.what == evBroadcast && event.message.command == cmReleasedFocus )
  changed = True;
 TDialog::handleEvent( event );
}

Boolean QpDisplay::valid( ushort command )
{
 Boolean result = TDialog::valid( command );
 if( command == cmCancel && changed == True )
  if( messageBox( mfWarning | mfYesButton | mfNoButton,
      "\x003���p����� ���������?" ) == cmYes )
  {
   if( changed && !valueTest() )
    return False;
   return True;
  }
 return result;
}

void QpDisplay::getData(void *rec)
{
 if( initDisplay )
  initDisplay->getData( *((QParameter *)rec), (TGroup*)this );
 (*((QParameter *)rec)).calcConst();
}

void QpDisplay::setData(void *rec)
{
 if( initDisplay )
  initDisplay->setData( *((QParameter *)rec), (TGroup*)this );
}

Boolean QpDisplay::valueTest()
{
 if( initDisplay )
  return initDisplay->valueTest( (TGroup*)this );
 else
  return True;
}





