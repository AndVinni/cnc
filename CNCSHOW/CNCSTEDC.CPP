/*  	cncstedc.cpp v01.01

	T������ ।����

	�㭪��  : Table Editor
	����஥��: CNCSHOW
	�஥��:    ELMIS CNC.

	Copyright (c) ELMIS, 1993
	�� �ࠢ� ���饭�.
*/

#include <string.h>
#include <ctype.h>
#include <math.h>
#include <mem.h>
#include <stdlib.h>
#include <alloc.h>
#include <dos.h>
#include <dir.h>
#include <conio.h>
#include "cnchard.h"
#include "cncshow.h"
#include "cncscr.h"
#include "cncstedi.h"
#include "cncstedc.h"
#include "cncsgstr.h"
#include "cncsfun.h"
#include "cncsfh.h"

/****************************   �����������  ******************************/

	/* ���ᮢ��� �� ��࠭� ⥪�饥 ���ﭨ� ⠡���� */
static void TedDraw(void);
	/* �⮡ࠧ��� ���� ��ப� ⠡���� */
static void DrawTedString(INT posy);
	/* �⮡ࠧ��� ᮤ�ন��� �祪� ⠡���� */
static void DrawCal(DRAWCALMODE dcm,INT xp,INT yp);
	/* �⮡ࠧ��� ��ਧ��⠫��� 誠�� ⠡���� */
static void HorisScale(INT left,INT right);
	/* �⮡ࠧ��� ���⨪����� 誠�� ⠡���� */
static void VertScale(void);
	/* ��ࠡ�⪠ ������ ।���� */
static void TedWork(TEDCHANGEMODE chm,CHAR key);
	/* �ਢ������ ���न���� X ⠡���� � ��࠭�� */
static INT Xcalculate(INT,INT,BOOL form);
	/* �ਢ������ ���न���� Y ⠡���� � ��࠭�� */
static INT Ycalculate(INT);
	/* ��⠢��� ��ப� ⠡���� */
static void ShiftDown(void);
	/* ������� ��ப� �� ⠡���� */
static void ShiftUp(void);
	/* �᪠�� ���⥪�� �� ⠡��� */
static BOOL FindContext(void);
	/* �������� ����� �� ⠡��� */
static void TedCursor(DIRECTION);
	/* ����� �� ��� ⠡����? */
static BOOL EndTedTable(DIRECTION,INT x, INT y);
	/* ����� �� ��� ��࠭�? */
static BOOL EndTedScreen(DIRECTION,INT x,INT y);
	/* ���⨣��� �࠭�� ���� ���᪠? */
static BOOL EndFindRegion(DIRECTION direction,INT x,INT y);
	/* ��६�饭�� ������� ������ �� ⠡��� */
static void TedMoveWindow (DIRECTION,INT distance);
	/* ��६�饭�� ����� �� ������� ������ ⠡���� */
static void MoveTedCursor(DIRECTION direction,INT distance);
static void LocateCursor(DIRECTION,INT distance);
	/* ��᮫�⭠� ������ ���� � ���न���� ⠡���� */
static void LocTedCursor(INT x,INT y);
	/* ���� ��������� ����� ��� ���짮��⥫�᪮�� ०��� */
static TABPOS* FindCursorPosition(DIRECTION direction,INT x,INT y);
	/* ���᫥��� ����������� ��६�饭�� �� ��࠭�栬 */
static INT CalcTedStep(DIRECTION direction);
	/* ���᫨�� 䠪��᪮� ��६�饭�� �� �窨 */
static INT CalcStep(INT x,INT y);
	/* ��।������ ���� � ��砫� ⠡���� */
static void TedTop(void);
	/* ��।������ ���� � ����� ⠡���� */
static void TedBottom(void);
	/* ������ �祩�� ⠡���� */
static void ClrCal(INT tx,INT ty);
	/* ������ ���⪠ �祪� */
static void FreeCal(INT tx,INT ty);
	/* ���⪠ �祪� �� ��� ०���� */
static void FullFreeCal(INT tx,INT ty);
	/* ������஢��� ⠡���� */
static void EditTable(CHAR);
	/* ��४��祭�� ०���� ⠡���� */
static void TedSwitchMode(void);
	/* ����樮��஢���� �� ��࠭� � ���न���� ⠡���� */
static void TedLocate(INT x,INT y);
	/* ������ ���祭�� � ⠡���� */
static void WriteValCal(void);
	/* ������ ���ଠ樨 � �祪� ⠡���� � �ଠ�  ⥪�� */
static void WriteTextCal(TABRECTYPE);
	/* ������ �ਭ� �祪� � ⠡���� */
static void WriteWidthCal(void);
	/* ������ ������⢠ ���� ��᫥ ����⮩ ��� �ᥫ. */
static void WriteQuDigit(void);
	/* ������ 梥� �祩��. */
static void WriteColor(void);
	/* ����� ������⢠ ������� � ⥪�饩 ������� ��ப� */
static INT ColInString(INT posy);
       /* ���� �祩�� � ��஭�  �� ���ࠢ����� */
static TABPOS* FindToFlang(DIRECTION,INT x,INT y, INT numstep);
       /* ����� ����⭮�� �窨 */
static void  CalcFlang(DIRECTION,INT x,INT y,INT amplituda,TABPOS*);
       /* �祩�� ⠡���� ����� �����? */
static BOOL Found(INT x,INT y);
       /* ���᫥��� ����� ����樨 �� ���᪥ */
void CalcNewPosition(DIRECTION,INT* x,INT* y);

/****************************************************************************/

/*	 		����� ������� ।���� ����� 			    */

void TedChange(TEDCHANGEMODE chm,CHAR key)
{
 if(Not Flag.DrawEnded)
 {
  TedDraw();
  Flag.DrawEnded=TRUE;
 }
 TedWork(chm,key);

} 			/* ����� TedChange */

	/* ���ᮢ��� �� ��࠭� ⥪�饥 ���ﭨ� ⠡���� */

void TedDraw(void)
{
 INT i,orm;

 orm=Atab->wn.cr;
 for(i=Atab->wn.lu.y;i<=Atab->wn.rd.y;i++)	 /* ���� �� ������� ������*/
 {
  CalcRightMargin(i);
  DrawTedString(i);
 }
 Atab->wn.cr=orm;
 VertScale();
}			/* ����� TedDraw */


		/* �⮡ࠦ���� ����� ��ப� ⠡���� */

void DrawTedString(INT posy)
{
 INT i,j;

 TedLocate(Atab->wn.lu.x,posy);
 for(i=Atab->wn.lu.x,j=FALSE;i<=Atab->wn.cr;i++)
 {
  if(i==Atab->cur.x And posy==Atab->cur.y)
  {
   DrawCal(CURSOR,i,posy);
   j=TRUE;
  }
  else 
   DrawCal(TABL,i,posy);
 }
 if(j)
  HorisScale(Atab->wn.lu.x,Atab->wn.cr);
}			/* ����� DrawTedString */


	/* ����� ��࠭��� ����樨 X �� ��������� ��������� � ⠡��� */

INT Xcalculate(INT xtab,INT ytab,BOOL form)
{
 register i,ts,w;
 TABTYPEPTR ptr;
				     /* C㬬��㥬 �ਭ� ������� �� ����樨 */
 for(ts=0,i=form?0:Atab->wn.lu.x;i<xtab;i++)
 {
  ptr=(*Atab->tbl)[ytab][i];
  if(ptr)
   w=ptr->dt.widcol?ptr->dt.widcol:DEFAULTCOLWIDTH;
  else w=DEFAULTCOLWIDTH;
  ts+=w;
 }
 ts+=(DWINDBEGX+LMARGIN);
 return ts;
}		/* ����� Xcalculate */

	/* ����� ��࠭��� ����樨 Y �� ��������� ��������� � ⠡��� */

INT Ycalculate(INT y)
{
 register ty;
 ty=y-Atab->wn.lu.y;
 ty+=DWINDBEGY+UMARGIN;
 return ty;
}		/* ����� Ycalculate */

		/* �⮡ࠧ��� ᮤ�ন��� �祩�� �� ��࠭� */

void DrawCal(DRAWCALMODE dcm,INT xp,INT yp)
{
 register x;
 TABTYPEPTR ptr;
 STRING tmpstr;
 CHAR   strtmp[MAXSTR];
 CHAR formdg[5][5]={ "%.0f","%.1f","%.2f","%.3f","%.4f"};

 ptr=(*Atab->tbl)[yp][xp];
			/* �롨ࠥ� 梥� */
 switch(dcm)
 {
  case CURSOR:LightColor(); break;		/* ०� �뢮�� ����� */
  case TABL  :                                  /* ��ଠ��� ०�� */
   if(ptr)
   {
    if(ptr->dt.color)
    {
     switch(ptr->dt.color-1)
     {
      case BLACK: 	Color(FBLUE,FBLACK);		break;
      case BLUE:  	Color(FBLUE,FBLUE);		break;
      case GREEN: 	Color(FBLUE,FGREEN);		break;
      case CYAN:  	Color(FBLUE,FCYAN);		break;
      case RED:   	Color(FBLUE,FRED);		break;
      case MAGENTA: 	Color(FBLUE,FMAGENTA);		break;
      case BROWN: 	Color(FBLUE,FBROWN);		break;
      case LIGHTGRAY: 	Color(FBLUE,FLIGHTGRAY);	break;
      case DARKGRAY: 	Color(FBLUE,FDARKGRAY);		break;
      case LIGHTBLUE: 	Color(FBLUE,FLIGHTBLUE);	break;
      case LIGHTGREEN: 	Color(FBLUE,FLIGHTGREEN);	break;
      case LIGHTCYAN: 	Color(FBLUE,FLIGHTCYAN);	break;
      case LIGHTRED: 	Color(FBLUE,FLIGHTRED);		break;
      case LIGHTMAGENTA:Color(FBLUE,FLIGHTMAGENTA);	break;
      case YELLOW: 	Color(FBLUE,FYELLOW);		break;
      case WHITE: 	Color(FBLUE,FWHITE);
     }
    }
    else
     switch(ptr->dt.dtype)
     {
      case VAL:
      case TXTVAL: Color(FBLUE,FYELLOW);
       break;
      case TXT:NormColor(); break;
      default: NormColor();
     }
   }
  else NormColor();				/* ���� �� 㬮�砭�� */
 }
			/* ��ନ�㥬 ��ப� ��� �뢮�� */
 if(ptr)
 {
  register lendef;
  if(ptr->dt.widcol)
  {
   setmem(strtmp,ptr->dt.widcol,BLANK);
   strtmp[ptr->dt.widcol]='\0';
   lendef=ptr->dt.widcol;
  }
  else
  {
   setmem(strtmp,DEFAULTCOLWIDTH,BLANK);
   strtmp[DEFAULTCOLWIDTH]='\0';
   lendef=DEFAULTCOLWIDTH; 
  }
  switch(ptr->dt.dtype)
  {
   register len;
   case VAL:
   {
    sprintf(strtmp,formdg[ptr->dt.quandg],ptr->dv.vreal);
    len=strlen(strtmp);
    if(len<lendef)
     strtmp[len]=BLANK;
    if(len>lendef)
     strtmp[lendef]='\0';
    tmpstr=strtmp;
   }
   break;
   case TXTVAL:
   case TXT:
   {
    len=strlen(ptr->dv.vstr);
    if(len>lendef)
     strncpy(strtmp,ptr->dv.vstr,lendef);
    else
     strncpy(strtmp,ptr->dv.vstr,len);
    tmpstr=strtmp;
   }
  }
 }
 else					/* �⮡ࠦ���� �祪� ��  㬮�砭�� */
 {
  setmem(strtmp,DEFAULTCOLWIDTH,BLANK);
  strtmp[DEFAULTCOLWIDTH]='\0';
  tmpstr=strtmp;
 }
 x=wherex();
 tmpstr[DWINDENDX-x]='\0';		/* ���祭�� �� ��� ��࠭� */
 cputs(tmpstr);
}			/* ����� DrawCal */

		/* ���ᮢ��� 誠�� ⠡���� */

void HorisScale(INT left,INT right)
{
 register x,i;
 INT midlwidth,widthcolumn;
 CHAR workstring[MAXSTR];
 TABTYPEPTR ptr;

 /* ���ᮢ��� ��ਧ��⠫��� 誠�� */
 Color(FGREEN,FWHITE);
 gotoxy(DWINDBEGX+LMARGIN,DWINDBEGY);
 if(Atab->sysm)
 {
  for(i=left;i<=right;i++)
  {
   ptr=(*Atab->tbl)[Atab->cur.y][i];
   if(ptr)
    widthcolumn=ptr->dt.widcol?ptr->dt.widcol:DEFAULTCOLWIDTH;
   else
    widthcolumn=DEFAULTCOLWIDTH;
   setmem(workstring,widthcolumn,BLANK);
   workstring[widthcolumn]='\0';
   midlwidth=widthcolumn>>1;
   if(++i>9 And widthcolumn<=1)
   {
    sprintf(workstring,"%-1d",i%10);
    i--;
   }
   else
   {
    if(widthcolumn>=2)
    {
     if(i>9)
      sprintf(workstring+midlwidth,"%-2d",i--);
     else
      sprintf(workstring+midlwidth,"%-1d",i--);
     if(widthcolumn>=3)
      workstring[strlen(workstring)]=BLANK;
    }
    else
     sprintf(workstring,"%-1d",i--);
   }
   x=wherex();
   workstring[DWINDENDX-x]='\0';
   cputs(workstring);
  }
 }
 else					/* ����� ���짮��⥫� */
 {
  CHAR ts[MAXSTR];
  CHAR tn[MAXFILE];
  setmem(workstring,SZSCRX,BLANK);
  workstring[SZSCRX]='\0';
  fnsplit(Atab->TablName,NULL,NULL,tn,NULL);
  sprintf(ts,"%s \"%s\"",Mesage[36],tn);
  strcpy(workstring+2,ts);
  workstring[strlen(ts)+2]=BLANK;
  cputs(workstring);
 }
}			/* ����� HorisScale */


 /* ���ᮢ���  ���⨪����� 誠�� */

void VertScale(void)
{
 INT i;
 Color(FGREEN,FWHITE);
 for(i=Atab->wn.lu.y;i<Atab->wn.rd.y+1;i++)
 {
  gotoxy(DWINDBEGX,Ycalculate(i));
  cprintf("%4d",i+1);
 }
}			/* ����� VertScale */

		/* �᭮��� ࠡ�稥 ०��� ।���� */

void TedWork(TEDCHANGEMODE chm,CHAR key)
{
 Atab->page = ShiftPresed() ? TRUE : FALSE;
 switch(chm)
 {
				/* ���� ����� �� ��࠭�栬 ���./�몫. */
  case TEDSTRED:    EditTable(key); break;	/* ������஢��� ⠡���� */
  case TSHIFTD: ShiftDown(); break; 		/* ���� ��⠢��� ��ப� */
  case TSHIFTU: ShiftUp(); break;		/* ���� ������� ��ப� */
  case TSWITCHMODE: TedSwitchMode();break;	/* ���� ��४����� ०�� */
  case TFIND:   FindContext(); break;		/* ����  ���� ���⥪�� */
  case TTOP:	TedTop(); break;	        /* � ��砫� ⠡���� */
  case TBOTTOM:	TedBottom();  break;	        /* � ��砫� ⠡���� */
  default:      if(key==RETURN) break;		/* ���� ��⠢��� ⥪�� */
 //   GetsScr(key,Atab->eds,128,PrntEds);
 }
}			/* ����� TedWork */


		  /* ������� ��������� ������ */

		/* ��६�饭�� �����  �� ���� */

void TedCursor(DIRECTION direction)
{
 MoveTedCursor(direction,Atab->page ? CalcTedStep(direction) : 1);
}			/* ����� TedCursor */


		/* ��।������ ����� � ���ࠢ����� */

void MoveTedCursor(DIRECTION direction,INT distance)
{

 if(EndTedTable(direction,Atab->cur.x,Atab->cur.y))
  return;			

 if(Atab->sysm)				/* �᫨ ०�� ��⥬�� */
 {
  if(distance > 1)			/* ��६�饭�� �� ��࠭�栬 */
   TedMoveWindow(direction,distance);
  else
   if(EndTedScreen(direction,Atab->cur.x,Atab->cur.y))
    TedMoveWindow(direction,distance);
  LocateCursor(direction,distance);
 }
 else
 {
  TABPOS* tmppos;
  if(distance>1)			/* ��६�饭�� �� ��࠭�栬 */
  {
   TedMoveWindow(direction,distance);
   LocateCursor(direction,distance);
  }
  if((tmppos=FindCursorPosition(direction,Atab->cur.x,Atab->cur.y))!=NULL)
  {
   if(EndFindRegion(direction,tmppos->x,tmppos->y))
    return;
   if(EndTedScreen(direction,tmppos->x,tmppos->y))
   {                          		/* �᫨ ����� �� �ࠥ� ��࠭� */
    register distance;
    distance=tmppos->y < Atab->wn.lu.y ? 
	     Atab->wn.lu.y - tmppos->y:
	     tmppos->y > Atab->wn.rd.y ?
	     tmppos->y - Atab->wn.rd.y : 0;
    TedMoveWindow(direction,distance);  /* ��।���. ������� ������� ��࠭� */
   }
   LocTedCursor(tmppos->x,tmppos->y);
  }
 }
}		/* ����� MoveTedCursor */

	/* ����樮��஢���� ����� � ���न���� ⠡���� */

void LocateCursor(DIRECTION direction,INT distance)
{
 switch(direction)		/* ����樮��஢��� ����� � <���ࢫ����> */
 {
  case TCURUP: 
   LocTedCursor(Atab->cur.x,Atab->cur.y-distance);
   break;
  case TCURDOWN:
   LocTedCursor(Atab->cur.x,Atab->cur.y+distance);
   break;
  case TCURLEFT:
   LocTedCursor(Atab->cur.x-distance,Atab->cur.y);
   break;
  case TCURRIGHT:
  {
   INT np;                 /* �� �⮨� ��������� ����� �� �ࠩ ��࠭� */
   np=Atab->cur.x+distance;
   if(np>Atab->wn.cr)
    break;
   else
    LocTedCursor(np,Atab->cur.y);
  }
 }
}			/* ����� LocateCursor */

void LocTedCursor(INT x,INT y)
{
 if(Atab->cur.y!=y)			/* ����� ������ ᢮� ��������� */
 {
  register oldy;
  oldy=Atab->cur.y;
  Atab->cur.y=y;
  if(oldy <= Atab->wn.rd.y And oldy >= Atab->wn.lu.y)
   DrawTedString(oldy);
 }
 Atab->cur.x=x;		      /* ���������  ����� ��������� ����� */
 Atab->cur.y=y;
 CalcRightMargin(Atab->cur.y);
 DrawTedString(y);
}			/* ����� LocTedCursor */


	/* �஢���� ��������� ����� �� �࠭�� ⠡���� */

BOOL EndTedTable(DIRECTION direction,INT x,INT y)
{

 switch(direction)			/* �᫨ <���ࠢ�����> */
 {

  /* ���� �����: */
  case TCURUP:
   if(y <= 0)   		/* �᫨ ⥪. �����. ����. ������ */
    return TRUE;
   else
    return FALSE;

  /* ���� �����: */
  case TCURLEFT:
   if(x <= 0) 		/* �᫨ ⥪. �����. ����. ᫥�� */
    return TRUE;
   else
    return FALSE;

  /* ���� ��ࠢ�: */
  case TCURRIGHT:
   if(Not Atab->sysm)		/* �᫨ ०�� ���짮��⥫� */
   {
    if(x >= Atab->sz.x-1) /* �᫨ ⥪. �����. ����. �ࠢ�*/
     return TRUE;
    else
     return FALSE;
   }
   else
   {
    if(x >= SZTABX-1)  /* �᫨ ⥪. ����. ���ᨬ��쭮 �ࠢ� */
     return TRUE;
    else
     return FALSE;
   }

  /* ���� ����: */
  case TCURDOWN:
   if(Not Atab->sysm)		/* �᫨ ०�� ���짮��⥫� */
   {
    if(y >= Atab->sz.y-1) /* �᫨ ��������� ����� ����� */
     return TRUE;
    else
     return FALSE;
   }
   else					/* ���� (०�� ��⥬��) */
   {
    if(y >= SZTABY-1)	/* �᫨ ⥪. ����. ����. ����� */
     return TRUE;
    else
     return FALSE;
   }
  default: return TRUE; /* �᫨ � ������ - ���ࠢ��쭮 ���ࠣࠬ�஢���!*/
 }
}		/* ����� EndTedTable */

	/* �஢���� ��������� ����� �� �࠭�� ���� ���᪠ */

BOOL EndFindRegion(DIRECTION direction,INT x,INT y)
{

 switch(direction)			/* �᫨ <���ࠢ�����> */
 {
  case TCURUP:
   if(y < 0)   		/* �᫨ ⥪. �����. ����. ������ */
    return TRUE;
   else
    return FALSE;

  case TCURLEFT:
   if(x < 0) 		/* �᫨ ⥪. �����. ����. ᫥�� */
    return TRUE;
   else
    return FALSE;

  case TCURRIGHT:
   if(x > SZTABX-1)  /* �᫨ ⥪. ����. ���ᨬ��쭮 �ࠢ� */
    return TRUE;
   else
    return FALSE;

  case TCURDOWN:
   if(Atab->sysm)
   {
   if(y > SZTABY-1)	/* �᫨ ⥪. ����. ����. ����� */
    return TRUE;
   else
    return FALSE;
   }
   else
   {
   if(y > Atab->sz.y-1)	/* �᫨ ⥪. ����. ����. ����� */
    return TRUE;
   else
    return FALSE;
   }
  default: return TRUE; /* �᫨ � ������ - ���ࠢ��쭮 ���ࠣࠬ�஢���!*/
 }
}			/* ����� EndFindRegion */

			/* ����� �� ��� ��࠭�? */

BOOL EndTedScreen(DIRECTION direction,INT x,INT y)
{
 switch(direction)
 {
  case TCURUP: return y <= Atab->wn.lu.y ? TRUE : FALSE;
  case TCURDOWN: return y >= Atab->wn.rd.y ? TRUE : FALSE;
  case TCURLEFT: return x <= Atab->wn.lu.x ? TRUE : FALSE;
  case TCURRIGHT: return x >= Atab->wn.cr ? TRUE : FALSE;
 }
 return TRUE;		/* ���ࠢ��쭮� �ᯮ�짮����� �㭪樨 */
}		/* ����� EndTedScreen */

		/* ��४��祭�� ०���� ।���� */

void TedSwitchMode(void)
{
 Atab->sysm^=TRUE;
 if(Atab->sysm)
 {
  if(Not(Atab->sz.x==SZTABX And Atab->sz.y==SZTABY))
  {
   TABTYPEARRPTR oldptr;
   oldptr=Atab->tbl;
   Atab->tbl=(TABTYPEARRPTR)farcalloc(SZTABX*SZTABY+SZTABX*SZSCRY,sizeof(TABTYPEPTR));
   if(Not Atab->tbl)				/* ��� ����� ��� ⠡���� */
   {
    SetError(8,1,5,5,NOBLOCKFID);
    return;
   }
   else
   {
    memcpy(Atab->tbl,oldptr,Atab->sz.y*SZTABX*sizeof(TABTYPEPTR));
    farfree(oldptr);
    Atab->sz.x=SZTABX;
    Atab->sz.y=SZTABY;
   }
  }
 }
 HorisScale(Atab->wn.lu.x,Atab->wn.cr);
}			/* ����� TedSwitchMode */

		/* ��६�饭�� ������� ������ ⠡���� */

void TedMoveWindow (DIRECTION direction,INT distance)
{
		       /* ���᫨�� ���祭�� ⥪�饣� ������ ���孥��  㣫� */
 Atab->wn.lu.x+=(direction==TCURLEFT)?-distance:
		    (direction==TCURRIGHT)?distance:0;
 Atab->wn.lu.y+=(direction==TCURUP)?-distance:
		    (direction==TCURDOWN)?distance:0;

			/* ���᫨�� ���祭�� ⥪�饣� �ࠢ��� ������� 㣫� */
 Atab->wn.rd.x+=(direction==TCURLEFT)?-distance:
		    (direction==TCURRIGHT)?distance:0;
 Atab->wn.rd.y+=(direction==TCURUP)?-distance:
		    (direction==TCURDOWN)?distance:0;

 CalcRightMargin(Atab->cur.y);

 /* �����஢��� ⥪�饥 ���ﭨ� ⠡���� */
 if(direction==TCURUP And (abs(distance)==1))
 {
  NormColor();
  RolWind(DWINDBEGX+LMARGIN,DWINDBEGY+UMARGIN,DWINDENDX-1,DWINDENDY-1,DOWN);
  VertScale();
 }
 else
  if(direction==TCURDOWN And (abs(distance)==1))
  {
   NormColor();
   RolWind(DWINDBEGX+LMARGIN,DWINDBEGY+UMARGIN,DWINDENDX-1,DWINDENDY-1,UP);
   VertScale();
  }
  else
   TedDraw();
}		/* ����� TedMoveWindow */


	/* ���᫨�� ��������� ��६�饭�� �� ��࠭�栬 */

INT CalcTedStep(DIRECTION direction)
{
 switch(direction)				/* �᫨ <���ࠢ�����> */
 {
  case TCURUP:					/* ���� �����: */
   /* ������ ���᫥���� ��६�饭�� � ��� X=0, Y=ࠧ��� ���. �� Y */
   return abs(CalcStep(0,-SZWINDY));

  case TCURDOWN:				/* ���� �����: */
   /* ������ ���᫥���� ��६�饭�� � ��� X=0, Y=����� ࠧ��� ���. �� Y */
   return abs(CalcStep(0,SZWINDY));

  case TCURLEFT:				/* ���� �����: */
   /* ������ ���᫥���� ��६�饭�� � ��� Y=0, X=����� ࠧ��� ���. �� X */
   return abs(CalcStep(-SZWINDX,0));

  case TCURRIGHT:				/* ���� �����: */
   /* ������ ���᫥���� ��६�饭�� � ��� Y=0, X=ࠧ��� ���. �� X */
   return abs(CalcStep(SZWINDX,0));
  default: return FALSE;
 }
}		/* ����� CalcTedStep */

	/* ���᫨�� 䠪��᪮� ��६�饭�� �� �窨 */

INT CalcStep(INT x,INT y)
{
 INT distance;

 if(x<0)
 {
  /* �᫨ ⥪��� ����� ������� �࠭�� ����� ��᮫�⭮�� x */
  if(Atab->wn.lu.x <= abs(x))
   return Atab->wn.lu.x;		/* ������ ⥪���� ������� �࠭��� */
  else 						       	/* ���� ������ x */
   return x;
 }

 if(x>0)
 {
  /* �᫨ ���ᨬ��쭮 �ࠢ�� ⠡���� ����� ⥪��� �ࠢ�� ����� x */
  if((distance=SZTABX - Atab->wn.rd.x) <= x)
   return distance;
  else
   return x;
 }

 if(y < 0)
 {
  /* �᫨ ⥪��� ����. �࠭�� ����� ��᮫�⭮�� Y */
  if(Atab->wn.lu.y <= abs(y))
   /* ������ ���祭�� ⥪�饩 ���孥� �࠭��� � ����ᮬ */
   return Atab->wn.lu.y;
  else
   return y;
 }

 if(y > 0)
 {
  /* �᫨ ���ᨬ��쭮 ������ ⠡���� ����� ⥪��� ������ ⠡���� ����� Y */
  if((distance=Atab->sz.y - Atab->wn.rd.y) < y)
   return distance;
  else
   return y;
 }
 return 0;
}             	/* ����� CalcStep */

	/* ���� ��������� ����� � ���짮��⥫�᪮� ०��� */

TABPOS* FindCursorPosition(DIRECTION direction,INT x,INT y)
{
 static TABPOS* tmppos;
 register INT numstep;
				/* ���� ���᪠ */
 
 for(numstep=0; Not EndFindRegion(direction,x,y) ;numstep++)
 {
  if((tmppos=FindToFlang(direction,x,y,numstep))!=NULL)
   return tmppos;
  else
   CalcNewPosition(direction,&x,&y);
 }
 return NULL;
}			/* ����� FindTedPosition */

		/* ���᫥��� ����� ����樨 �� ���᪥ */

void CalcNewPosition(DIRECTION direction,INT* x,INT* y)
{
 switch(direction)
 {
  case TCURUP:    (*y)--;   break;
  case TCURDOWN:  (*y)++;   break;
  case TCURLEFT:  (*x)--;   break;
  case TCURRIGHT: (*x)++;
 }
}		/* ����� CalcNewPosition */

	/* ����  �� ��஭�� �� ⥪�饣� ���ࠢ����� */

TABPOS* FindToFlang(DIRECTION direction,INT x,INT y,INT numstep)
{
 static TABPOS  curentpos;

 if(numstep==0)			  /* ���� � ���ன ��砫� ���� ����ਬ */
  return NULL;
  
 if(Found(x,y))                   /* � �������� ����樨 �᪮��� �祩��? */
 {
  curentpos.x=x;
  curentpos.y=y;
  return &curentpos;
 }
 else			 /* ��� - �㤥� �᪠�� � ����⭮���� �窨 (x,y) */
 {
  register amplituda;
  for
  (
   amplituda=0,curentpos.x=x,curentpos.y=y;
   abs(amplituda) <= numstep;
   amplituda = amplituda>=0 ? -(amplituda+1) : -amplituda
  )
  {
   CalcFlang(direction,x,y,amplituda,&curentpos);
   if(Found(curentpos.x,curentpos.y))
    return &curentpos;
  }
  return NULL;
 }
}			/* ����� FindToFlang */


	       /* �祩�� ⠡���� ����� �����? */

BOOL Found(INT x,INT y)
{
 TABTYPEPTR tmpcal;

 if((tmpcal=(*Atab->tbl)[y][x])==NULL)
  return FALSE;
 else
 {
  if(tmpcal->dt.dtype==VAL Or tmpcal->dt.dtype==TXTVAL)
   return TRUE;
  else
   return FALSE;
 }
}        		/* ����� Found */

	       /* ����� ����⭮�� �窨 */

void  CalcFlang(DIRECTION direction,INT x,INT y,INT amplituda,TABPOS* newpos)
{
 switch(direction)
 {
  case TCURUP:
  case TCURDOWN:
   newpos->x =  x + amplituda;
				    /* ���祭�� ���� ���᪠ �� ࠧ�. ⠡. */
   newpos->x = newpos->x < 0 ? 0 :  
	       newpos->x > (Atab->sz.x-1) ? (Atab->sz.x-1) : newpos->x;
   break;
  case TCURLEFT:
  case TCURRIGHT:
   newpos->y = y + amplituda;
   newpos->y = newpos->y < 0 ? 0 :
	       newpos->y > (Atab->sz.y-1) ? (Atab->sz.y-1) : newpos->y;
 }
}                      	/* ����� CalcFlang */

		/* ���������� ⠡���� �� ��ਧ��⠫� */

void ShiftDown(void)
{
 register i,j;

 if(Atab->sysm)
 {
			     /* ������ ��᫥���� �ᯮ��㥬� �� ⠡���� */
  for(i=0,j=SZTABY-1;i<SZTABX;i++)
   FreeCal(i,j);
  for(i=SZTABY-1;i>Atab->cur.y;i--)       /* �������� 㪠��⥫� �� �� ���� */
   for(j=0;j<SZTABX;j++)
    (*Atab->tbl)[i][j]=(*Atab->tbl)[i-1][j];
  for(j=0,i=Atab->cur.y;j<SZTABX;j++)   /* ���㫨�� 㪠��⥫� ⥪�饣� �鸞 */
   (*Atab->tbl)[i][j]=NULL;
  TedDraw();			        	    /* ����ᮢ��� ⠡���� */
 }
}			/* ����� ShiftDown */


		/* �������� ⠡���� �� ��ਧ��⠫� */

void ShiftUp(void)
{
 register i,j;

 if(Atab->sysm)
 {
  for(i=0,j=Atab->cur.y;i<SZTABX;i++)  	  	    /* ������ ⥪�騩 �� */
   FreeCal(i,j);
  for(i=Atab->cur.y;i<SZTABY;i++)         /* �������� 㪠��⥫� �� �� ��� */
   for(j=0;j<SZTABX;j++)
    (*Atab->tbl)[i][j]=(*Atab->tbl)[i+1][j];
  for(j=0,i=SZTABY;j<SZTABX;j++)      /* ���㫨�� 㪠��⥫� ��᫥����� �鸞 */
   (*Atab->tbl)[i][j]=NULL;
  TedDraw();					    /* ����ᮢ��� ⠡���� */
 }
}			/* ����� ShiftUp */

		/* ���⪠ �祩�� �� ��� ०���� */

void FullFreeCal(INT tx,INT ty)
{
 if(Atab->sysm)
 {
  FreeCal(tx,ty);
  CalcRightMargin(Atab->cur.y);
  DrawTedString(Atab->cur.y);
  Atab->eds[0]='\0';
 }
}			/* ����� FullFreeCal */


		/* ������ ���⪠ �祪� */

void FreeCal(INT tx,INT ty)
{
 TABTYPEPTR ot;

 if((ot=(*Atab->tbl)[ty][tx])!=NULL)
 {
  if(ot->dt.dtype!=VAL)
   if(ot->dv.vstr)
    free(ot->dv.vstr);
  ClrCal(tx,ty);
 }
}			/* ����� FreeCal */

	     /* ���⪠ �祩���  ⠡���� ��� �ᮡ������� �����
		�� ⥪�⮢�� ���祭��  */

void ClrCal(INT tx,INT ty)
{
 register TABTYPEPTR ot;

 if((ot=(*Atab->tbl)[ty][tx])!=NULL)
 {
  ot->dt.dtype=ot->dt.widcol=ot->dt.quandg=ot->dt.color=0;
  ot->dv.vstr=NULL;
  free(ot);
  (*Atab->tbl)[ty][tx]=NULL;
 }
} 			/* ����� ClrCal */


		/* ���� ���⥪�� �� ⠡��� */

BOOL FindContext(void)
{
 register INT tmpy,tmpx;
 BOOL exitloop,datafind,firstfind;
 LONG StepCounter;

	 /* ��������, ���� �� �ன��� ���  �� ⠡��� */

 for(
     exitloop=datafind=firstfind=FALSE,tmpy=Atab->cur.y,
     StepCounter=Atab->sz.x*Atab->sz.y;
     Not exitloop And StepCounter > 0L ;
     tmpy=tmpy==Atab->sz.y?0:tmpy+1 
    )
 {
  for(
      tmpx=firstfind?0:(firstfind=TRUE,Atab->cur.x+1);
      tmpx<SZTABX;tmpx++,StepCounter--
     )
  {
   TABTYPEPTR ptr;

   ptr=(*Atab->tbl)[tmpy][tmpx];		   /* C 祬 �ࠢ������ �? */
   if(ptr==NULL)
    continue;					   /* ��� ��祣� ������ */
						   /* �᫨ � �祪� ⥪�� */
   if(ptr->dt.dtype!=VAL)
   { 			      /* �᫨ �ࠢ����� ���⥪�� � �祩�� �ᯥ譮 */
    if(strstr(ptr->dv.vstr,Atab->eds))
      datafind=TRUE;
   }
   else				/* � �祪� �᫮��� ���祭�� */
   {
    CHAR tmpstr[MAXSTR];
    sprintf(tmpstr,"%f",ptr->dv.vreal);
    if(strstr(tmpstr,Atab->eds))
     datafind=TRUE;
   }
   if(datafind)
   {
    INT distance;
    DIRECTION direction;
    distance=Atab->cur.y-tmpy;
    direction=distance > 0 ? TCURUP : TCURDOWN;
    distance=abs(distance);
    if((direction==TCURUP) And ((Atab->wn.lu.y-distance) < 0))
     distance-=abs(Atab->wn.lu.y-distance);
    TedMoveWindow(direction,distance);
    LocTedCursor(tmpx,tmpy);
    Atab->eds[0]='\0';
    return TRUE;
   }
  }
 }
 return FALSE;	
}                 	/* ����� FindContext */

		/* ��६������� � ��砫� ⠡���� */

void TedTop(void)
{
 Atab->wn.lu.x=Atab->wn.lu.y=0;
 Atab->wn.rd.x=SZWINDX-1;
 Atab->wn.rd.y=SZSCRY;
 Atab->cur.x=Atab->cur.y=0;
 CalcRightMargin(0);
 TedDraw();
}		/* ����� TedTop */

void TedBottom(void)
{
 Atab->wn.rd.x=SZWINDX-1;
 Atab->wn.rd.y=Atab->sz.y-1;
 Atab->wn.lu.x=0;
 Atab->wn.lu.y=Atab->wn.rd.y-SZSCRY;
 Atab->cur.x=0;
 Atab->cur.y=Atab->wn.lu.y;
 CalcRightMargin(0);
 TedDraw();
}		/* ����� TedBottom */

void EditTable(CHAR key)
{
 static CHAR OldInputData[MAXSTR];
 if(key)
 {
  switch(key)
  {
  case CURUP:   TedCursor(TCURUP); break;
  case CURDOWN: TedCursor(TCURDOWN); break;
  case CURLEFT:
   if(Not Atab->eds[0])
   {
    TedCursor(TCURLEFT);
    key='\0';
   } break;
  case CURRIGHT:
   if(Not Atab->eds[0])
   {
    TedCursor(TCURRIGHT);
    key='\0';
   } break;
  }                                        /* ���짮��⥫� ���� �����*/
 }
 if(key==RETURN)
 {
  if(Atab->eds[0])
   strcpy(OldInputData,Atab->eds);
  else
  {
   register i;
   for(i=0;OldInputData[i];i++)
    GetsScr(OldInputData[i],Mesage[28],Atab->eds,MAXSTR,PrntEds);
  }
 }
 if(GetsScr(key,Mesage[28],Atab->eds,MAXSTR,PrntEds))
 {
  if(Atab->sysm)
  {
   switch(Atab->eds[0])
   {                                  /* �������� ��ப� ���� �᫮��� ����. */
    case '%':WriteValCal();
     break;
    case '@':WriteWidthCal(); break;  /* �������� ��ப� ���� �ਭ� �祪� */
    case '$':                         /* �������� ��ப� - ⥪�⮢�� ���祭��*/
     WriteTextCal(TXTVAL);    	     break;
    case '#':			     /* �������� ��ப� - ������� ��᪨ ��.*/
     FullFreeCal(Atab->cur.x,Atab->cur.y); break;
    case '&':			     /* �� ������� ���祭�� ���� ��᫥ ��*/
     WriteQuDigit();  break;
    case '^':			     /* �� ������� ���祭�� ���� ��᫥ ��*/
     WriteColor();    break;
    default:
     if(Not isdigit(Atab->eds[0]))
      WriteTextCal(TXT);		     /* �������� ���⮩ ⥪�� */
     else
      WriteValCal();
   }
  }
  else
  {
   if(isdigit(Atab->eds[0]) Or Atab->eds[0]=='.'Or Atab->eds[0]=='-')
    WriteValCal();
   else
    WriteTextCal(TXTVAL);		     /* �������� ���⮩ ⥪�� */
  }
 }
}			/* ����� EditTable */

		/* ����樮��஢���� ����� � ���न���� ⠡���� */

void TedLocate(INT x,INT y)
{
  gotoxy(Xcalculate(x,y,FALSE),Ycalculate(y));
}		/* ����� TedLocate */


/* ������ ������⢮ ������� � ��� ��ப� �������饩 � ������� ������� */

INT ColInString(INT posy)
{
  register i,tq,tmpw;
  register TABTYPEPTR ptr;
  
  for(i=Atab->wn.lu.x,tq=tmpw=0; ;i++)
  {
   ptr=(*Atab->tbl)[posy][i];
   if(ptr)
    tmpw+=(ptr->dt.widcol)?ptr->dt.widcol:DEFAULTCOLWIDTH;
   else
    tmpw+=DEFAULTCOLWIDTH;
   tq++;
   if(tmpw>=SZSCRX)
    break;                          
  }  	 
 return tq;
}			
			/* ����� ColInString */

		/* ������ � �祩�� ⠡���� �᫮���� ���祭�� */

void WriteValCal(void)
{
 register TABTYPEPTR ptr;

 ptr=(*Atab->tbl)[Atab->cur.y][Atab->cur.x];
 if(Atab->sysm)
 {
  if(!ptr)
  {
   ptr=(*Atab->tbl)[Atab->cur.y][Atab->cur.x]=(TABTYPEPTR)calloc(1,sizeof(TABTYPEPTR));
   if(!ptr)
   {
    SetError(8,1,5,5,BLOCKFID);
    return;
   }
   if(isdigit(Atab->eds[1]) Or Atab->eds[1]=='.'Or Atab->eds[1]=='-')
   {
    ptr->dt.dtype=VAL;
    ptr->dv.vreal=atof(Atab->eds+1);
    Atab->eds[0]='\0';
    DrawTedString(Atab->cur.y);
   }
  }
 }
 else
 {
  if(ptr->dt.dtype!=VAL)
   return;
  if(isdigit(Atab->eds[0]) Or Atab->eds[0]=='.' Or Atab->eds[0]=='-')
  {
   ptr->dv.vreal=atof(Atab->eds);
   Atab->eds[0]='\0';
   DrawTedString(Atab->cur.y);
  }
 }
}			/* ����� WriteValCal */



void WriteQuDigit(void)
{
 register TABTYPEPTR ptr;
 register tmp;

 ptr=(*Atab->tbl)[Atab->cur.y][Atab->cur.x];
 if(ptr)
  if(Atab->sysm)
   if(ptr->dt.dtype==VAL)
    if(isdigit(Atab->eds[1]))
    {
     tmp=atoi(Atab->eds+1);
     if(tmp>4) tmp=4;
     ptr->dt.quandg=tmp;
     Atab->eds[0]='\0';
     CalcRightMargin(Atab->cur.y);
     DrawTedString(Atab->cur.y);
    }
}			/* ����� WriteQuDigit */



void WriteColor(void)
{
 register TABTYPEPTR ptr;
 register tmp;

 ptr=(*Atab->tbl)[Atab->cur.y][Atab->cur.x];
 if(ptr)
  if(Atab->sysm)
   if(isdigit(Atab->eds[1]))
   {
    tmp=atoi(Atab->eds+1);
    if(tmp>15) tmp=15;
    ptr->dt.color=++tmp;
    Atab->eds[0]='\0';
    DrawTedString(Atab->cur.y);
   }
}			/* ����� WriteColor */



void WriteWidthCal(void)
{
 register tmp;
 if((tmp=atoi(Atab->eds+1))>MAXCOLWIDTH)
  tmp=MAXCOLWIDTH;
 else
 {
 register TABTYPEPTR ptr;
 ptr=(*Atab->tbl)[Atab->cur.y][Atab->cur.x];
 if(Not ptr)
  if(Not(ptr=(TABTYPEPTR)calloc(1,sizeof(TABTYPE))))
  {
   SetError(8,1,5,5,NOBLOCKFID);
   return;
  }
 ptr->dt.widcol=tmp<MINCOLWIDTH?MINCOLWIDTH:tmp;
 Atab->eds[0]='\0';
 CalcRightMargin(Atab->cur.y);
 DrawTedString(Atab->cur.y);
 }
}		/* ����� WriteWidthCal */

	
		/* ������ ���ଠ樨 � �祪� ⠡���� � �ଠ� ⥪�� */

void WriteTextCal(TABRECTYPE type)
{
 register tsz;
 register TABTYPEPTR ptr;

 ptr=(*Atab->tbl)[Atab->cur.y][Atab->cur.x];

 if(Atab->sysm)
 {
  if(Not ptr)			      /* �᫨ �� �祪� ���뫠 �ᯮ�짮���� */
  {
   if(Not (ptr=(TABTYPEPTR)calloc(1,sizeof(TABTYPE))))
   {                                		  /* �뤥��� ��� ��� ������ */
    SetError(8,1,5,5,NOBLOCKFID);
    return;
   }
   else                                             /* �������� 㪠��⥫� */
    (*Atab->tbl)[Atab->cur.y][Atab->cur.x]=ptr;
  }
  if(Atab->eds[1])
  {
   if(Not ptr->dv.vstr)
    if(Not (ptr->dv.vstr=(STRING)calloc(1,strlen(Atab->eds+1))) )
    {
     SetError(8,1,5,5,NOBLOCKFID);    /* �᫨ ��� ���� ��� ��ப� - �訡�� */
     return;
    }
   tsz=strlen(Atab->eds+1);
   if(tsz!=strlen(ptr->dv.vstr))
    if(Not(ptr->dv.vstr=(STRING)realloc(ptr->dv.vstr,tsz)))
    {
     SetError(8,1,5,5,NOBLOCKFID);
     return;
    }
   strcpy(ptr->dv.vstr,Atab->eds+1);
   Atab->eds[0]='\0';
   ptr->dt.dtype=type;
   ptr->dt.widcol=tsz<MINCOLWIDTH?MINCOLWIDTH:tsz;
   CalcRightMargin(Atab->cur.y);
   DrawTedString(Atab->cur.y);
  }
 }
 else						      /* ����� ���짮��⥫� */
 {
  if(ptr->dt.dtype==TXTVAL)
  {
   register sl;
   sl=strlen(Atab->eds);
   if(ptr->dt.widcol+1 >= sl)
     strcpy(ptr->dv.vstr,Atab->eds);
   else
   {
    strncpy(ptr->dv.vstr,Atab->eds,ptr->dt.widcol);
    ptr->dv.vstr[ptr->dt.widcol]='\0';
   }
   Atab->eds[0]='\0';
   CalcRightMargin(Atab->cur.y);
   DrawTedString(Atab->cur.y);
  }
 }
}			/* ����� WriteTextCal */

void CalcRightMargin(INT posy)
{
 Atab->wn.cr=Atab->wn.lu.x+ColInString(posy)-1;
}			/* ����� CalcRightMargin */

/*
		   ���������� ����� ۲��������
									    */
