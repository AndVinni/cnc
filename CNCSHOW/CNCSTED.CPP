/*  	cncsted.cpp v01.01

	Работа с таблицей

	Функция  : Table Editor
	Подпроект: CNCSHOW
	Проект:    ELMIS CNC.

	Copyright (c) ELMIS, 1993
	Все права защищены.
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

TABARR _FAR *Atab;	  	/* Активная таблица */
				/* Переменные для всех таблиц */
TABARR NulTabl= { FTABNUL, LoadTabNull, CompTabNull },
       KorTabl= { FTABKOR, LoadTabKorr, CompTabKorr },
       ParTabl= { FTEHPAR, LoadTehParam , CompTehParam },
       MparTabl={ FMPAR, NULL, CompQparam },
       ToolTabl={ FTABKS, };

static void TedInit(TABARR *tbl);  /* Инициализация таблицы */
static void TedLoad(STRING extention); /* Загрузка таблицы в редактор */
static BOOL TedSave(void);	   /* Запомнить таблицу в файле */
static void TedEnd(void);	   /* Конец работы */
static BOOL TedSysMode(void);	   /* Включен ли системный режим? */
static void LoadForm(BOOL);	   /* Загрузчик форм таблиц */
static void SaveForm(void);        /* Сохранение формы таблицы */
void CalcRightMargin(INT posy);	   /* Пересчет текущей правой границы строки */
			
			/* Табличный редактор */

BOOL Ted(TEDMODE mod,DWORD data,CHAR key)
{
 switch(mod)
  {
  case EDIT: TedChange((TEDCHANGEMODE)data,key);
   break;
  case INIT: TedInit((TABARR*)(void _FAR *)data);
   break;
  case LOAD: TedLoad((STRING)(void _FAR *)data);
   break;
  case SAVE: TedSave();
   break;
  case END: TedEnd();
   break;
  case SYSMODE: return TedSysMode();
  }
 return TRUE;
} 			/* Конец Ted */



void TedInit(TABARR* tbl)
{
 Atab=tbl;
}			/* Конец TedInit */

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
			/* Конец TedLoad */


		    /*  Загрузчик форм таблиц */

void LoadForm(BOOL newt)
{
 FILE *in;
 WORD tmp1,tmp2;
 TABTYPEPTR ptr;

 if(newt)		 		    /* Создается новая таблица */
 {
  Atab->tbl=(TABTYPEARRPTR)farcalloc(SZTABX*SZTABY+SZTABX,sizeof(TABTYPEPTR));
  if(Not Atab->tbl)				/* Нет памяти под таблицу */
  {
   SetError(8,1,5,5,NOBLOCKFID);
   return ;
  }                /* Начальные установки */
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
  if((in=fopen(WorkStr,"rb"))==NULL)   /* Вскрытие файла таблицы */
  {
   SetError(1,5,1,4,NOBLOCKFID);
   return ;
  }
  else
  {
   register WORD i,j,c;

   tmp1=fgetc(in);		          /* Вынимаем размер таблицы X */
   tmp2=fgetc(in);
   tmp2<<=8;
   tmp1|=tmp2;
   Atab->sz.x=tmp1;
   tmp1=fgetc(in);		          /* Вынимаем размер таблицы Y */
   tmp2=fgetc(in);
   tmp2<<=8;
   tmp1|=tmp2;
   Atab->sz.y=tmp1;
					     /* Веделяем память под таблицу */
   Atab->tbl=(TABTYPEARRPTR)farcalloc(Atab->sz.y*SZTABX+SZTABX*SZSCRY,sizeof(TABTYPEPTR));
   if(Atab->tbl==NULL)			          /* Нет памяти под таблицу */
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
      ptr=(TABTYPEPTR)farcalloc(1,sizeof(TABTYPE));    /* Выделение памяти под запись */
      if(ptr==NULL)
      {
       SetError(8,1,5,5,NOBLOCKFID);
       return ;
      }                            
      tmpdata.dw.lowbyte=c;
      tmpdata.dw.higbyte=fgetc(in);
      ptr->dt.dtype =tmpdata.dt.dtype; 		/* Тип данных */
      ptr->dt.quandg=tmpdata.dt.quandg;		/* Кол-во заков после з. */
      ptr->dt.widcol=tmpdata.dt.widcol; 	/* Ширина колонки */
      ptr->dt.color =tmpdata.dt.color;	 	/* Цвет */
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
  Atab->cur.x=Atab->cur.y=0;                         /* Начальные установки */
  Atab->sysm=FALSE;
  Atab->page=FALSE;
  Atab->eds[0]='\0';
  Atab->wn.lu.x=Atab->wn.lu.y=0;
  Atab->wn.rd.x=SZWINDX-1;
  Atab->wn.rd.y=SZWINDY-1;
  CalcRightMargin(0);
 } /* end if newname false */
}   			/* Конец LoadForm */

		   /* Запомнить таблицу в файле */

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

			/* Запомнить форму таблицы */
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
  register WORD i,j;    		/* Определение максимального */
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

  if(tszx Or tszy)         		/* Сохранение размеров таблицы */
  {
   Atab->sz.x =(tszx<SZWINDX)?SZWINDX:++tszx;
   Atab->sz.y =(tszy<SZWINDY)?SZWINDY:++tszy;
  }
  fputc(Atab->sz.x,out);
  fputc(Atab->sz.x>>8,out);
  fputc(Atab->sz.y,out);
  fputc(Atab->sz.y>>8,out);

  for(i=0;i<Atab->sz.y;i++)          /* Основной цикл сохранения таблицы */
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
}			/* Конец TedSave */

	/* Закончить работу с таблицей */

void TedEnd(void)
{
 register i,j,sz;

 /* Освободить ранее занятую под таблицу память */
 sz=Atab->sysm?SZTABY:Atab->sz.y+1;
 for(i=0;i<sz;i++)
  for(j=0;j<SZTABX;j++)
  {
   TABTYPEPTR ptr;
   ptr=(*Atab->tbl)[i][j];
   if(Not ptr)			   	/* Ячека таблицы небыла использ.*/
    continue;
   else
   {                                   /* Было  выделено  место под строку */
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
}			/* Конец TedEnd */

		/* Проверка текущего режима табличного редактора */

BOOL TedSysMode(void)
{
 if(Atab->sysm)
  return TRUE;
 else
  return FALSE;
}			/* Конец TedSysMode */



