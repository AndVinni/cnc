/*  	cncsted.cpp v01.01

	����� � ⠡��楩

	�㭪��  : Table Editor
	����஥��: CNCSHOW
	�஥��:    ELMIS CNC.

	Copyright (c) ELMIS, 1993
	�� �ࠢ� ���饭�.
*/

#include <stdio.h>
#include <dos.h>
#include <dir.h>
#include <stdlib.h>
#include <string.h>
#include <alloc.h>
#include "cnchard.h"
#include "cncdir.h"
#include "cncshow.h"
#include "cncscr.h"
#include "cncstedi.h"
#include "cncstedc.h"
#include "cncsfun.h"
#include "cncsfh.h"
#include "cncsgstr.h"
#include "cncstio.h"

TABARR far *Atab;	  	/* ��⨢��� ⠡��� */
				/* ��६���� ��� ��� ⠡��� */
TABARR NulTabl= { FTABNUL, LoadTabNull, CompTabNull },
       KorTabl= { FTABKOR, LoadTabKorr, CompTabKorr },
       ParTabl= { FTEHPAR, LoadTehParam , CompTehParam },
       MparTabl={ FMPAR, NULL, CompQparam },
       ToolTabl={ FTABKS, };

static void TedInit(TABARR *tbl);  /* ���樠������ ⠡���� */
static void TedLoad(STRING extention); /* ����㧪� ⠡���� � ।���� */
static BOOL TedSave(void);	   /* ��������� ⠡���� � 䠩�� */
static void TedEnd(void);	   /* ����� ࠡ��� */
static BOOL TedSysMode(void);	   /* ����祭 �� ��⥬�� ०��? */
static void LoadForm(BOOL);	   /* �����稪 �� ⠡��� */
static void SaveForm(void);        /* ���࠭���� ��� ⠡���� */
void CalcRightMargin(INT posy);	   /* ������ ⥪�饩 �ࠢ�� �࠭��� ��ப� */
			
			/* ������� ।���� */

BOOL Ted(TEDMODE mod,DWORD data,CHAR key)
{
 switch(mod)
  {
  case EDIT: TedChange((TEDCHANGEMODE)data,key);
   break;
  case INIT: TedInit((TABARR*)(void far *)data);
   break;
  case LOAD: TedLoad((STRING)(void far *)data);
   break;
  case SAVE: TedSave();
   break;
  case END: TedEnd();
   break;
  case SYSMODE: return TedSysMode();
  }
 return TRUE;
} 			/* ����� Ted */



void TedInit(TABARR* tbl)
{
 Atab=tbl;
}			/* ����� TedInit */

void TedLoad(STRING extention)
{
 if(ShiftPresed()) 
   LoadForm(TRUE);
 else
 {
  CHAR WorkStr[MAXPATH];
  LoadForm(FALSE);
  if(Fh.EndDir)
  {
   fnmerge(WorkStr,"",InDev.Path,UNNAMED,extention);
   strcpy((CHAR*)Atab->TablName,WorkStr);
  }
  else
  {
   fnmerge(WorkStr,"",InDev.Path,GetDirFileName(extention),"");
   strcpy((CHAR*)Atab->TablName,WorkStr);
   if(Atab->Loader)
    (*Atab->Loader)();
  }
 }
}
			/* ����� TedLoad */


		    /*  �����稪 �� ⠡��� */

void LoadForm(BOOL newt)
{
 FILE *in;
 WORD tmp1,tmp2;
 TABTYPEPTR ptr;

 if(newt)		 		    /* ��������� ����� ⠡��� */
 {
  Atab->tbl=(TABTYPEARRPTR)farcalloc(SZTABX*SZTABY+SZTABX,sizeof(TABTYPEPTR));
  if(Not Atab->tbl)				/* ��� ����� ��� ⠡���� */
  {
   SetError(8,1,5,5,NOBLOCKFID);
   return ;
  }                /* ��砫�� ��⠭���� */
  Atab->sz.x=SZTABX;  		 Atab->sz.y=SZTABY;
  Atab->cur.x=Atab->cur.y=0;     Atab->sysm=TRUE;
  Atab->page=FALSE;		 Atab->eds[0]='\0';
  Atab->wn.lu.x=Atab->wn.lu.y=0; Atab->wn.rd.x=SZWINDX-1;
  Atab->wn.rd.y=SZWINDY-1;       Atab->wn.cr=SZWINDX-1;
 } /* end if newname true */
 else
 {
  CHAR WorkStr[MAXPATH];
  fnmerge(WorkStr,"",Config[HD_RSC],Atab->FormName,"");
  if((in=fopen(WorkStr,"rb"))==NULL)   /* ����⨥ 䠩�� ⠡���� */
  {
   SetError(1,5,1,4,NOBLOCKFID);
   return ;
  }
  else
  {
   register WORD i,j,c;

   tmp1=fgetc(in);		          /* �뭨���� ࠧ��� ⠡���� X */
   tmp2=fgetc(in);
   tmp2<<=8;
   tmp1|=tmp2;
   Atab->sz.x=tmp1;
   tmp1=fgetc(in);		          /* �뭨���� ࠧ��� ⠡���� Y */
   tmp2=fgetc(in);
   tmp2<<=8;
   tmp1|=tmp2;
   Atab->sz.y=tmp1;
					     /* �����塞 ������ ��� ⠡���� */
   Atab->tbl=(TABTYPEARRPTR)farcalloc(Atab->sz.y*SZTABX+SZTABX*SZSCRY,sizeof(TABTYPEPTR));
   if(Atab->tbl==NULL)			          /* ��� ����� ��� ⠡���� */
   {
    SetError(8,1,5,5,NOBLOCKFID);
    return ;
   }
   for(i=0;i<Atab->sz.y;i++)
   {
    for(j=0;j<Atab->sz.x;j++)
    {
     if(feof(in))
     {
      SetError(11,4,2,4,NOBLOCKFID);
      goto exit_loop;
     }
     if((c=fgetc(in))!=0)
     {
      DESTYPE tmpdata;
      ptr=(TABTYPEPTR)farcalloc(1,sizeof(TABTYPE));    /* �뤥����� ����� ��� ������ */
      if(ptr==NULL)
      {
       SetError(8,1,5,5,NOBLOCKFID);
       return ;
      }                            
      tmpdata.dw.lowbyte=c;
      tmpdata.dw.higbyte=fgetc(in);
      ptr->dt.dtype =tmpdata.dt.dtype; 		/* ��� ������ */
      ptr->dt.quandg=tmpdata.dt.quandg;		/* ���-�� ����� ��᫥ �. */
      ptr->dt.widcol=tmpdata.dt.widcol; 	/* ��ਭ� ������� */
      ptr->dt.color =tmpdata.dt.color;	 	/* ���� */
      if(ptr->dt.dtype==VAL)
      {
       register k;
       TRANTYPE tmpval;
       for(k=0;k<sizeof(float);k++)
	tmpval.vstr[k]=(BYTE)fgetc(in);
       ptr->dv.vreal=tmpval.vreal;
      }
      else
      {
       register k=0; CHAR wstr[MAXSTR];
       do
	wstr[k]=fgetc(in);
       while(wstr[k++]);
       ptr->dv.vstr=(STRING)farmalloc(strlen(wstr));
       if(ptr->dv.vstr==NULL)
       {
	SetError(8,1,5,5,NOBLOCKFID);
	return ;
       }
       strcpy((CHAR*)ptr->dv.vstr,wstr);
      } /* end if type value */
      (*Atab->tbl)[i][j]=ptr;
     } /* end if non zero cal */
    } /* end for j */
   } /* end for i */
  } /* end if file open true */
  exit_loop: if(in) fclose(in);
  Atab->cur.x=Atab->cur.y=0;                         /* ��砫�� ��⠭���� */
  Atab->sysm=FALSE;
  Atab->page=FALSE;
  Atab->eds[0]='\0';
  Atab->wn.lu.x=Atab->wn.lu.y=0;
  Atab->wn.rd.x=SZWINDX-1;
  Atab->wn.rd.y=SZWINDY-1;
  CalcRightMargin(0);
 } /* end if newname false */
}   			/* ����� LoadForm */

		   /* ��������� ⠡���� � 䠩�� */

BOOL TedSave(void)                                 
{
 if(ShiftPresed())
 {
  SaveForm();
  return TRUE;
 }
 else
  if(Atab->Compiller)
   return (*Atab->Compiller)();
 return TRUE;
}

			/* ��������� ��� ⠡���� */
void SaveForm(void)
{
 CHAR WorkStr[MAXPATH];
 FILE *out;

 fnmerge(WorkStr,"",Config[HD_RSC],Atab->FormName,"");
 if((out=fopen(WorkStr,"wb"))==NULL)
 {
  SetError(1,5,1,4,NOBLOCKFID);
  return ;
 }
 else
 {
  register WORD i,j;    		/* ��।������ ���ᨬ��쭮�� */
  WORD tszx,tszy;
  WORD mary,marx;

  mary=Atab->sysm?SZTABY:Atab->sz.y;
  marx=Atab->sysm?SZTABX:Atab->sz.x;

  for(i=tszy=tszx=0;i<mary;i++)
   for(j=0;j<marx;j++)
   {
    TABTYPEPTR ptr;
    ptr=(*Atab->tbl)[i][j];
    if(ptr)
    {
     tszy=(i > tszy)?i:tszy;
     tszx=(j > tszx)?j:tszx;
    }
    else
     continue;
   }

  if(tszx Or tszy)         		/* ���࠭���� ࠧ��஢ ⠡���� */
  {
   Atab->sz.x =(tszx<SZWINDX)?SZWINDX:++tszx;
   Atab->sz.y =(tszy<SZWINDY)?SZWINDY:++tszy;
  }
  fputc(Atab->sz.x,out);
  fputc(Atab->sz.x>>8,out);
  fputc(Atab->sz.y,out);
  fputc(Atab->sz.y>>8,out);

  for(i=0;i<Atab->sz.y;i++)          /* �᭮���� 横� ��࠭���� ⠡���� */
   for(j=0;j<Atab->sz.x;j++)
   {
    register TABTYPEPTR ptr;
    ptr=(*Atab->tbl)[i][j];
    if(Not ptr)
     fputc(0,out);
    else
    {
     DESTYPE tmpdata;
     tmpdata.dt.dtype=ptr->dt.dtype;
     tmpdata.dt.quandg=ptr->dt.quandg;
     tmpdata.dt.widcol=ptr->dt.widcol;
     tmpdata.dt.color=ptr->dt.color;
     fputc(tmpdata.dw.lowbyte,out);
     fputc(tmpdata.dw.higbyte,out);
     if(ptr->dt.dtype==VAL)
     {
      register k;
      TRANTYPE tmpvar;
      tmpvar.vreal=ptr->dv.vreal;
      for(k=0;k<sizeof(float);k++)
       fputc(tmpvar.vstr[k],out);
     }
     else
     {
      register CHAR tmpc;
      register k=0;
      do
      {
       tmpc=ptr->dv.vstr[k++];
       fputc(tmpc,out);
      }
      while (tmpc);
     }
    }
   }
  fclose(out);
  return ;
 }
}			/* ����� TedSave */

	/* �������� ࠡ��� � ⠡��楩 */

void TedEnd(void)
{
 register i,j,sz;

 /* �᢮������ ࠭�� ������� ��� ⠡���� ������ */
 sz=Atab->sysm?SZTABY:Atab->sz.y+1;
 for(i=0;i<sz;i++)
  for(j=0;j<SZTABX;j++)
  {
   TABTYPEPTR ptr;
   ptr=(*Atab->tbl)[i][j];
   if(Not ptr)			   	/* �祪� ⠡���� ���뫠 �ᯮ��.*/
    continue;
   else
   {                                   /* �뫮  �뤥����  ���� ��� ��ப� */
    if((ptr->dt.dtype!=VAL) && ptr->dv.vstr)
    {
     farfree(ptr->dv.vstr);
     ptr->dv.vstr=NULL;
    }
    farfree(ptr);
    ptr=(*Atab->tbl)[i][j]=NULL;
    }
  }
 farfree(Atab->tbl);
 Atab->TablName[0]='\0';
 Atab->tbl=NULL;
 i=0;
 Atab->sz.x=Atab->sz.y=
 Atab->cur.x=Atab->cur.y=
 Atab->wn.lu.x=Atab->wn.lu.y=
 Atab->wn.rd.x=Atab->wn.rd.y=
 Atab->wn.cr=
 Atab->sysm=Atab->page=i;
 Atab=NULL;
 EraseWarning();
}			/* ����� TedEnd */

		/* �஢�ઠ ⥪�饣� ०��� ⠡��筮�� ।���� */

BOOL TedSysMode(void)
{
 if(Atab->sysm)
  return TRUE;
 else
  return FALSE;
}			/* ����� TedSysMode */



