/*  	cncsfh.cpp v01.01

	Работа с файлами

	Подпроект: CNCSHOW
	Проект:    ELMIS CNC.

	Copyright (c) ELMIS, 1993
	Все права защищены.
*/



#ifdef __MSDOS__
#include <stdlib.h>
#include <dir.h>
#include <dos.h>
#include <bios.h>
#include <io.h>
#include <sys\stat.h>
#include <conio.h>
#endif
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "cnchard.h"
#include "cncshow.h"
#include "cncscr.h"
#include "cncdir.h"
#include "cncsfh.h"
#include "cncraz.h"
#include "cnccdef.h"
#include "cnccstat.h"
#include "cnccsti.h"
#include "cncint.h"
#include "cncsfspr.h"
#include "cncsfun.h"
#include "cncsgstr.h"




			/* Используемые функции */
     /* Вспомогательные */
BOOL ReqAccess(DEVICE*),                     /* Проверка доступности устр. */
     CopFile(STRING str);		     /* Копировать файл*/
void DelAll(void),  	 		     /* Удалить файлы */
     DelFile(void),     		     /* Удалить файл */
     RenFile(STRING),		             /* Переименовать файл */
     ProFile(void),      		     /* Защитить файл */
     SwapDev(void),
     CursMove(STRING header,CHAR simb),      /* Переместить курсор */
     NewCatalog(void),		             /* Создание каталога */
     ShowCatalog(STRING Header);             /* Распечатка каталога */

void WriteDir(struct ffblk *fb,FILE *fdir);  /* Запись элемента каталога */

     /* Основные */

/* Основная функция */
BOOL FileHanding(FILE_HAND_METHOD method,DWORD data)
{
 static STRING CurentHeader;
/* Начало */
switch (method)
   {
   case REQ_ACCESS: if(data) /* Запрос на доступ к устройству */
		       return ReqAccess(&OutDev);
		    else
		       return ReqAccess(&InDev);
   case SET_EXT:
      Extention=(STRING)(void far *)data; /* Установка расширения файлов */
      break;
   case SHOW_DIR:             /* Рисуем каталог */
      CurentHeader=(STRING)(void far *)data;
      ShowCatalog(CurentHeader);
      break;
   case NEW_DIR: NewCatalog();
      break;
   case SWAP_DEV: SwapDev();
      break;
   case IN_DRIVE_SET:
      InDev.Path=Config[(INT)data++];
      InDev.Stat=(StatDev)atoi(Config[(INT)data++]);
      InDev.Name=Config[(INT)data];
      break;
   case OUT_DRIVE_SET:
      OutDev.Path=Config[(INT)data++];
      OutDev.Stat=(StatDev)atoi(Config[(INT)data++]);
      OutDev.Name=Config[(INT)data];
      break;
   case COPY_FILE:    return CopFile((STRING)(void far *)data);
   case DELETE_ALL:   DelAll();
      break;
   case DELETE_FILE: DelFile();
      break;
   case RENAME_FILE: RenFile((STRING)(void far *)data);
      break;
   case PROTECT_FILE: ProFile();
      break;
   case RET_FILE_NAME:data=(DWORD)CurFile;break;
   case MOVE_CURSOR:  CursMove(CurentHeader,(BYTE)data);
   }
return TRUE;
}/* End FileHanding */

/* Функция определения возможности доступа к устройствам УЧПУ */
BOOL ReqAccess(DEVICE* Dev)
{
/* Если запрос не активен */
if(Not Fh.ReqActiv)
   {
   /* Если разрешен доступ к устройству при интерполяции */
   if(Not(Dev->Stat Ifset PROTECT_IN_AUTO))
      {
      if(Dev->Stat Ifset SWITCH_TIMER)
	 {            /* Изменить частоту таймера если необходимо */
	 OldTime();
	 Fh.OldTime=TRUE;
	 }
      return TRUE; /* Можно обращаться к устройству */
      }
   else   /* Если запрещен доступ к устройству */
      {
      /* Если не идет отработка интерполяции */
      if(STOP_INTERP)
	 {
	 /* Запрос к диспетчеру на отключение контроллеров */
	 Fh.ReqActiv=TRUE;
	 return FALSE; /* Еще пока низя */
	 }
      else
	 {
	 /* Запрос к оператору на стоп программы */
	 DrawWarning(Mesage[12]);
	 return FALSE; /* Пока нет доступа */
	 }
      }
   }
else
   {
   /* Контроллеры отключены? */
#ifdef DEBUG
   if(Dev)
#else
   if(Fh.CerActiv)
#endif
      {
      /* Контроллеры отключены, возможен доступ к устройству */
      if(Dev->Stat Ifset SWITCH_TIMER)
	 {            /* Изменить частоту таймера если необходимо */
	 OldTime();
	 Fh.OldTime=TRUE;
	 }
      return TRUE;
      }
   else
      /* Запрос пока не прошел */
      return (FALSE);
   }
} /* End ReqAccess*/


/* Копировать файл*/
BOOL CopFile(STRING str)
{
 static BOOL Prot=FALSE;
 static FILE *in,*out;
 static WORD ByteCounter=0, SizeProg=0;
 CHAR WorkStr[MAXPATH],StrWork[MAXSTR];

 if(Not Fh.CopActiv) /* Начало копирования */
   {
   /* Путь к входному файлу */
   sscanf(CurFile,"%s",StrWork);
   fnmerge(WorkStr,"",InDev.Path,StrWork,Extention);
   Prot=(access(WorkStr,2)!=SUCCESS)?TRUE:FALSE;
   in=fopen(WorkStr,"rb");
   /* Путь к выходному файлу */
   sscanf(str?str:CurFile,"%s",StrWork);
   fnmerge(WorkStr,"",OutDev.Path,StrWork,Extention);
   /* Если такой файл существует - блокировка операции */
   if(Not(access(WorkStr,0)==0))
   {
    out=fopen(WorkStr,"wb");
    /* Копирование началось */
    Fh.CopActiv=TRUE;
    /* Необходимые формальности для вывода шкалы */
    sscanf(CurFile,"%*s%u",&SizeProg);
    ByteCounter=0;
    /* Рисуем шкалу */
    Color(FBLACK,FLIGHTGREEN);
    gotoxy((MAXSZX/QUANTWIND)*2,MAXSZY-3);
    Scale(Mesage[35],ByteCounter,SizeProg);
   }
   else
   {
    fclose(in);
    DrawWarning(Mesage[25]);
    if(Fh.OldTime)      /* Переключение частоты РС на УЧПУ */
    {
     FlopOff();
     NewTime();
     Fh.OldTime=FALSE;
    }
    return TRUE;
   }
   /* Выход */
   return FALSE;
   }
else  /* Непосредственно процесс копирования */
   {
   register unsigned int i;
   for(i=16;i!=0;i--)  /* Копируем "пачками"*/
       {
       CHAR c;
       c=fgetc(in);
       ByteCounter++;
       if(feof(in) Or DOSerr())
	  {
	  /* Конец копирования копирования */
	  Color(FBLACK,FLIGHTGREEN);
	  gotoxy((MAXSZX/QUANTWIND)*2,(MAXSZY-3));
	  Scale(Mesage[35],ByteCounter,SizeProg);
	  fclose(in);
	  fclose(out);
	  if(Prot)             /* Защитить файл если надо */
	  {
	   /* Путь к выходному файлу */
	   fnmerge(WorkStr,"",OutDev.Path,StrWork,Extention);
	   chmod(WorkStr,S_IREAD);
	  }
	  Fh.CopActiv=FALSE;
	  /* Частота таймера УЧПУ */
	  if(Fh.OldTime)  /* Если включена системная частота */
	     {
	     FlopOff();
	     NewTime();       /* Включаем частоту УЧПУ */
	     Fh.OldTime=FALSE;/* Снимаем признак системной частоты */
	     }
	  EraseWarning();     /* Очистка строки предупреждений */
	  ByteCounter=0;
	  SizeProg=0;
	  return TRUE; /* Копирование завершилось */
	  }
       fputc(c,out); /* in -> out */
       }
   /* Отображаем процесс копирования */
   Color(FBLACK,FLIGHTGREEN);
   gotoxy((MAXSZX/QUANTWIND)*2,MAXSZY-3);
   Scale(Mesage[35],ByteCounter,SizeProg);
   return FALSE;       /* Еще не все */
   }
} 				/* End CopFile */

				/* Удалить файл */
void  DelFile(void)
{
 CHAR WorkStr[MAXSTR],StrWork[MAXSTR];
 
 sscanf(CurFile,"%s",StrWork);			/* Путь к входному файлу */
 fnmerge(WorkStr,"",InDev.Path,StrWork,Extention);
 if(unlink(WorkStr)!=SUCCESS)
  DrawWarning(Mesage[26]);
}				/* End DelFile */

/* Удалить файлы */
void  DelAll(void)
{
 struct ffblk FfBlk;         /* Информация о файле  */
 CHAR WorkStr [MAXSTR];

 /* Путь к входному файлу */
 fnmerge(WorkStr,"",InDev.Path,GROUPFILE,Extention);
 if((findfirst(WorkStr,&FfBlk,0))==SUCCESS)
 do
  {
   fnmerge(WorkStr,"",InDev.Path,FfBlk.ff_name,"");
   unlink(WorkStr);
  }
  while(findnext(&FfBlk)==SUCCESS);
} 				/* DelAll */

			/* Переименовать файл */
void RenFile(STRING newfile)
{
 CHAR OldName[MAXPATH],NewName[MAXPATH],WorkStr[MAXFILE];

 sscanf(CurFile,"%8s",WorkStr);
 fnmerge(OldName,"",InDev.Path,WorkStr,Extention);
 fnmerge(NewName,"",InDev.Path,newfile,Extention);
 if(access(OldName,2)!=SUCCESS)
 {
  DrawWarning(Mesage[26]); /* Файл защищен */
  return;
 }
 if(rename(OldName,NewName)!=SUCCESS)
  DrawWarning(Mesage[25]); /* Такая программа уже есть */
}			/* End RenFile */

			/* Защитить файл */
void  ProFile(void)
{
 CHAR WorkStr [MAXPATH],StrWork[MAXSTR];

 /* Путь к входному файлу */
 sscanf(CurFile,"%8s",StrWork);
 fnmerge(WorkStr,"",InDev.Path,StrWork,Extention);
 chmod(WorkStr,access(WorkStr,2)==SUCCESS?S_IREAD:S_IWRITE);
}			/* End ProFile */

			/* Переместить курсор */
void CursMove(STRING header,CHAR com)
{
 if(com==CURUP)				/* Курсор вверх? */
 {
  if(Not CursPosition)					/* Курсор вверху? */
  {
   if(FilePointer)				/* Это не начало каталога? */
    FilePointer--;
  }
  else
   CursPosition--;
  Fh.EndDir=FALSE;
  ShowCatalog(header);
 }
 
 if(com==CURDOWN)					   /* Курсор вниз? */
 {
  /* Если не конец директория */
  if(Not Fh.EndDir)
  {
   /* Курсор не внизу? */
   if(CursPosition<(DWINDENDY-DWINDBEGY-2))
    CursPosition++;
   else
    FilePointer++;
   ShowCatalog(header);
  }
  else 
   DrawWarning(Mesage[11]);
 }
} 				/* End CursMove */

                        /* Cоздание нового каталога */
void NewCatalog(void) 
{
struct ffblk FfBlk;  				/* Информация о файле  */
FILE *Fdir;          				/* Временной каталог   */
CHAR WorkStr[MAXPATH];

 FilePointer='\0';			          /* Сброс позиций каталога */
 CursPosition='\0';
				/* Получить путь к временному директорию    */
 fnmerge(WorkStr,"",Config[ED_SYS],TEMP_DIR,TEMP_FILE);
 if((Fdir=fopen(WorkStr,"w"))==NULL)	    /* Открыть временной директорий */
  SetError(5,9,2,5,NOBLOCKFID);
 else
 {
  /* Получаем путь к файлам устройства */
  fnmerge(WorkStr,"",InDev.Path,GROUPFILE,Extention);
  if((findfirst(WorkStr,&FfBlk,0))==SUCCESS)
   do
    WriteDir(&FfBlk,Fdir);
   while(findnext(&FfBlk)==SUCCESS);
  fputs("\32\n",Fdir);
  fclose(Fdir);
  if(Fh.OldTime)      			/* Переключение частоты РС на УЧПУ */
  {
   FlopOff();
   NewTime();
   Fh.OldTime=FALSE;
  }
  Fh.EndDir=FALSE;
 }
} 				/* End NewCatalog */

		/* Функция вывода каталога на экран */

void ShowCatalog(STRING Header)
{
 register WORD i;   /* Для циклов */
 FILE *Fdir;                	/* Файл каталога */
 CHAR WorkStr[MAXSTR];      	/* Рабочий массив */
 BOOL EndOfDir;             	/* Достигли конца директория */

 Color(FGREEN,FYELLOW);		/* Формирование "шапки" */	
 gotoxy(DWINDBEGX+2,DWINDBEGY);
 cputs(Header);
 NormColor();
 clreol();
 Color(FBLUE,FYELLOW);
 gotoxy(DWINDBEGX+2,DWINDBEGY+1);
 cputs(Mesage[14]);
 gotoxy(DWINDBEGX+37,DWINDBEGY+1);
 cputs(Mesage[15]);
 Color(FGREEN,FWHITE);
 gotoxy(DWINDENDX-20,DWINDBEGY+1);
 cputs(InDev.Name);
 cputs(" ");
 cputs(OutDev.Name);
 NormColor();
 clreol();

 /* Получаем путь доступа к временному каталогу */
 fnmerge(WorkStr,"",Config[ED_SYS],TEMP_DIR,TEMP_FILE);
 if((Fdir=fopen(WorkStr,"r"))==NULL)
  SetError(1,5,1,4,NOBLOCKFID);
 else
 {
  for(i=FilePointer;i!=0;i--)             /* Позиционирование окна */
   fgets(WorkStr,MAXSTR,Fdir);
  i=0;
  do {
   if((EndOfDir=(fgets(WorkStr,MAXSTR,Fdir)==NULL)?TRUE:FALSE)==TRUE)
   {
    if(i==CursPosition)
    {
     Fh.EndDir=TRUE;
     DrawWarning(Mesage[11]);
     CurFile[0]='\0';
    }
    break;
   }
   else
   {
    WorkStr[strlen(WorkStr)-1]='\0';
    if(i==CursPosition)
     {
      strcpy(CurFile,WorkStr);
      LightColor();
     }
     else
      NormColor();
     gotoxy(DWINDBEGX+2,i+DWINDBEGY+2);
     cputs(WorkStr);
    }
    i++;
   } while((Not EndOfDir)And(i<DWINDENDY-(DWINDBEGY+1)));
   NormColor();
   for(i=i+DWINDBEGY+2;i<=DWINDENDY;i++)
   {
    gotoxy(DWINDBEGX,i);
    clreol();
   }
   }
 fclose(Fdir);
} 			/* End ShowCatalog */



void WriteDir(struct ffblk *fb,FILE *fdir)
{
register i;

for(i=0;fb->ff_name[i]!='.';i++)
 fputc(fb->ff_name[i],fdir);
for(;i<MAXFILE;i++)
 fputc(BLANK,fdir);
fprintf(fdir," %7ld    %2u.%2u.%4u    %2u:%2u:%2u    %c \n",
	     (fb->ff_fsize),                            /* Размер */
	     (fb->ff_fdate & 0x001F),                   /* День   */
	     (fb->ff_fdate & 0x01E0) >> 5,              /* Месяц  */
	     ((fb->ff_fdate& 0xF800) >> 9)+1980,        /* Год    */
	     (fb->ff_ftime & 0xF800) >> 11,             /* Часы   */
	     (fb->ff_ftime & 0x07E0) >> 5,              /* Минуты */
	     (fb->ff_ftime & 0x001F) *  2,              /* Секунды*/
	     (fb->ff_attrib Ifset FA_RDONLY)?'P':' ');  /* Доступ */
} 			/* End WriteDir */

/* Выбор устройства источника */
void IstSwitch(CHAR CodKey)
{
switch(CodKey)
   {
   case F1: FileHanding(IN_DRIVE_SET,HD_CNC);
      break;
   case F2: FileHanding(IN_DRIVE_SET,FD_CNC);
      break;
/* case F3: FileHanding(IN_DRIVE_SET,PRF);
      break;
   case F4: FileHanding(IN_DRIVE_SET,DNC);
      break; */
   }
} /* End IstSwitch */

/* Выбор устройства приемника */
void DestSwitch(CHAR CodKey)
{
switch(CodKey)
   {
   case F1: FileHanding(OUT_DRIVE_SET,HD_CNC);
      break;
   case F2: FileHanding(OUT_DRIVE_SET,FD_CNC);
      break;
/* case F3: FileHanding(OUT_DRIVE_SET,PRF);
      break;
   case F4: FileHanding(OUT_DRIVE_SET,DNC);
      break; */
   }
} /* End DestSwitch */

void SwapDev(void)
{
DEVICE TmpDev;
TmpDev.Path=OutDev.Path;
TmpDev.Stat=OutDev.Stat;
TmpDev.Name=OutDev.Name;
OutDev.Path=InDev.Path;
OutDev.Stat=InDev.Stat;
OutDev.Name=InDev.Name;
InDev.Path=TmpDev.Path;
InDev.Stat=TmpDev.Stat;
InDev.Name=TmpDev.Name;
}/* End  SwapDev */


void FlopOff(void)
{
 INT i;
 for(i=07000;i!=0;i--) 			/* Ждем пока моторы не остановятся */
  geninterrupt(NEWVECTIMER);
}/* End FlopOff */

			/* Корневая программа */

void FhRoot(CHAR cod,STRING exten,STRING header)
{
 static BOOL CreateRootActive=FALSE;
 defseq;

 if(Fh.RedrawCat And STOP_INTERP)
  Flag.DrawEnded=FALSE;
 seqrun( Not Flag.DrawEnded  And CreateRootActive==FALSE )
 {
  run(1)
   CreateRootActive=TRUE;
   if(Not Flag.DrawEnded)
   {
    Fh.RedrawCat=FALSE;
    Flag.DrawEnded = TRUE;
   }
   Flag.NoSwitchMode = TRUE;
   if(Not Flag.NotCat)
    SetSeq(3);
  breakrun;
  rerun(2)
   ( FileHanding(REQ_ACCESS,IN)
   ? TRUE
   : Flag.Warning ? GotoSeq(5):FALSE )
  breakrerun;
  run(3)
   FileHanding(SET_EXT,(DWORD)exten);
   FileHanding(NEW_DIR,0);
   Flag.NotCat = FALSE;
  breakrun;
  run(4)
   EraseWind();
   FileHanding(SHOW_DIR,(DWORD)header);
  breakrun;
  run(5)
   if(Flag.Warning And (Not STOP_INTERP))
    Fh.RedrawCat=TRUE;
   Flag.NoSwitchMode = FALSE;
   AccReset();                               /* Снять запpос */
   CreateRootActive=FALSE;
  breakrun;
  endseq;
 }
 if(cod)
  FileHanding(MOVE_CURSOR,(DWORD)cod);
}			/* End FhRoot */

		/* Основныя функция копирования файла */
void FhCopFile(CHAR cod,WORD* modes,STRING exten)
{
 static CHAR Str[MAXPATH];
 static BOOL CopyActive=FALSE;
 defseq;

 /* Если команда идти назад то идем */
 if(cod==FBAK)						 /* Команда назад */
 {
  SetSeq(9);
  EraseWarning();
 }
 if(Fh.EndDir And cod)				 /* Если нет имени файла */
 {
  DrawWarning(Mesage[11]);
  cod='\0';
  BackTree(FBAK,1,modes);
 }
 if(Not Flag.MenuDrawed)
  SetSeq(9);
 seqrun( cod==F1 And CopyActive==FALSE )
 {
  run(1)
   Flag.NoSwitchMode=CopyActive=TRUE;	/* Блокировать переключение режимов */
   TextWind(F1-1,CurentMsg[F1-1],INVERS);		 /* Включить кнопку */
   FileHanding(SET_EXT,(DWORD)exten);
   Str[0]='\0';
//   SetLatKey();
  breakrun;
  rerun(2) 				/* Запрос доступа к диску источнику */
   FileHanding(REQ_ACCESS,IN) ? TRUE
   : Flag.Warning ? GotoSeq(9) : FALSE
  breakrerun;
  run(3)
   AccReset();	/* Устройство доступно - можно запросить новое имя */
   Flag.NoSwitchMode=FALSE;
  breakrun;
  rerun(4) 				    /* Ввод нового имени оператором */
   (
    (cod=isalpha(cod) Or iscntrl(cod) Or isdigit(cod) ? toupper(cod) :'?'),
    (GetsScr(cod,Mesage[29],Str,MAXFILE-1,PrntEds)!=0) Or (cod==RETURN)
   )
  breakrerun;
  rerun(5) 				/* Запрос доступа к диску источнику */
   FileHanding(REQ_ACCESS,IN) ? TRUE
   : Flag.Warning ? GotoSeq(9) : FALSE
  breakrerun;
  rerun(6)      			      /* Запрос доступа к приемнику */
   FileHanding(REQ_ACCESS,OUT)
  breakrerun;
  run(7)
   Flag.NoSwitchMode=TRUE;		/* Блокировать переключение режимов */
  breakrun;
  rerun(8) 	 			     /* Непосредственно копирование */
   FileHanding(COPY_FILE,Str[0]?(DWORD)Str:NULL)
  breakrerun;
  run(9)
   if(strcmp(InDev.Name,OutDev.Name)==SUCCESS)
    Flag.NotCat=TRUE;
   TextWind(0,CurentMsg[0],NORMAL);	       /* Выкл. кнопки */
   Flag.DrawEnded=FALSE;		       /* Все перерисовать */
   BackTree(FBAK,1,modes);		       /* Вернуться назад */
   AccReset();                                 /* Снять запpос */
   Flag.NoSwitchMode=CopyActive=FALSE;	       /* Разрешение пер. режим. */
  breakrun;
  endseq;
 }
}				/* End FhCopFile */

		/* Замена направления операций */

void FhSwapDir(CHAR cod,WORD* modes,STRING exten)
{
 static BOOL SwapActiv=FALSE;
 defseq;
 seqrun( cod==F2 And SwapActiv==FALSE )
   {
   run(1) /* Включить кнопку */
      SwapActiv=TRUE;
      Flag.NoSwitchMode=FALSE;			/* Разрешение пер. режим. */
      TextWind(F2-1,CurentMsg[F2-1],INVERS);
      FileHanding(SET_EXT,(DWORD)exten);
      /* Заменить устройства в/в */
      FileHanding(SWAP_DEV,0);
   breakrun;
   rerun(2)  /* Запросить доступ  */
       FileHanding(REQ_ACCESS,IN)
       ? TRUE
       : Flag.Warning ? TRUE : FALSE
   breakrerun;
   run(3)  /* Новый каталог   */
      FileHanding(NEW_DIR,0);
      AccReset();                               /* Снять запpос */
      TextWind(F2-1,CurentMsg[F2-1],NORMAL); /* Выкл. кнопки */
      Flag.DrawEnded=FALSE;			/* Все перерисовать */
      BackTree(FBAK,1,modes);
      SwapActiv=FALSE;
   breakrun;
   endseq;
   }
}				/* End FhSwapDir */

			/* Выбрать диск источник */

void FhSwIst(CHAR cod,WORD* modes,STRING exten)
{
 static BOOL SwitchActiv=FALSE;
 defseq;

 seqrun( (cod==F1 Or cod==F2 ) And SwitchActiv==FALSE)
   {
   run(1)
      Flag.NoSwitchMode=SwitchActiv=TRUE;
      FileHanding(SET_EXT,(DWORD)exten);
      IstSwitch(cod);
   breakrun;
   rerun(2)             /* Запросить доступ к утройству */
      FileHanding(REQ_ACCESS,IN)
      ? TRUE
      : Flag.Warning? GotoSeq(3) : FALSE
   breakrerun;
   run(3)
      FileHanding(NEW_DIR,0);
      AccReset();                               /* Снять запpос */
      Flag.DrawEnded=FALSE;
      ResetMenu(FBAK,FBAK);
      BackTree(FBAK,1,modes);
      Flag.NoSwitchMode=SwitchActiv=FALSE;
   breakrun;
   endseq;
   }
}				/* End FhSwIst */


			/* Удалить файл */

void FhUnlink(CHAR cod,WORD* modes,STRING exten)
{
 BYTE OldFp,OldCp;
 static BOOL DelActiv=FALSE;
 defseq;

 if(cod==FBAK) 					/* Команда назад */
  SetSeq(6);
 if(Fh.EndDir And cod) 				/* Нет имени файла */
 {
  DrawWarning(Mesage[11]);
  cod='\0';
  BackTree(FBAK,1,modes);
 }
 seqrun( cod==F1 And DelActiv==FALSE )
 {
  run(1)
   DelActiv=TRUE;
   TextWind(0,CurentMsg[0],INVERS);
   FileHanding(SET_EXT,(DWORD)exten);
  breakrun;
  rerun(2)			        /* Запрос доступа к диску источнику */
   FileHanding(REQ_ACCESS,IN) ? TRUE
   : Flag.Warning ? GotoSeq(6) : FALSE
  breakrerun;
  run(3) 			       /* Подтверждение стирания оператором */
   DrawWarning(Mesage[23]);
  breakrun;
  rerun(4)
   cod==F1 ? TRUE : cod!=F1 And cod!='\0' ? GotoSeq(6) : FALSE
  breakrerun;                   	
  run(5)
   Flag.NoSwitchMode=TRUE;
   FileHanding(DELETE_FILE,0);
  breakrun;
  run(6)
   OldFp=FilePointer;
   OldCp=CursPosition;
   FileHanding(SET_EXT,(DWORD)exten);
   FileHanding(NEW_DIR,0);
   FilePointer=OldFp;
   CursPosition=OldCp;
   AccReset();
   TextWind(0,CurentMsg[0],NORMAL);
   Flag.DrawEnded=Flag.NoSwitchMode=FALSE;
   BackTree(FBAK,1,modes);
   DelActiv=FALSE;
  breakrun;
  endseq;
 }
}			/* End FhUnlink */

			/* Стереть все файлы */

void FhAllUnlink(CHAR cod,WORD* modes,STRING exten)
{
 static BOOL AllUnlinkActive=FALSE;
 defseq;

 if(cod==FBAK)
  SetSeq(6);
 if(Fh.EndDir And cod) /* Если нет имени файла */
   {
   DrawWarning(Mesage[11]);
   cod='\0';
   BackTree(FBAK,1,modes);
   }
seqrun( cod==F2 And AllUnlinkActive==FALSE )
   {
   run(1)
      AllUnlinkActive=TRUE;
      TextWind(1,CurentMsg[1],INVERS);      /* Включить кнопку */
      FileHanding(SET_EXT,(DWORD)exten);
   breakrun;
   rerun(2)	 /* Запрос доступа к источнику */
       FileHanding(REQ_ACCESS,IN) ? TRUE
       : Flag.Warning? GotoSeq(6) : FALSE
   breakrerun;
   run(3)      /* Запрос оператору */
      DrawWarning(Mesage[23]);
   breakrun;
   rerun(4) 
      cod==F2 ? TRUE: cod!=F2 And cod!='\0' ? GotoSeq(6) : FALSE
   breakrerun;
   run(5)
      Flag.NoSwitchMode=TRUE;
      FileHanding(DELETE_ALL,0);
   breakrun;
   run(6)
      FileHanding(NEW_DIR,0);
      AccReset();
      TextWind(1,CurentMsg[1],NORMAL);
      Flag.DrawEnded=Flag.NoSwitchMode=AllUnlinkActive=FALSE;
      BackTree(FBAK,1,modes);
   breakrun;
   endseq;
   }
}			/* End FhAllUnlink */

			/* Переименовать файл */

void FhRename(CHAR cod,WORD* modes,STRING exten)
{
 BYTE OldFp,OldCp;
 static CHAR Str[MAXPATH];
 static BOOL RenameActive=FALSE;
 defseq;

 if(cod==FBAK) /* Команда назад */
 {
  SetSeq(7);
  EraseWarning();
 }
 if(Fh.EndDir And cod) 					/* Нет имени файла */
 {
  DrawWarning(Mesage[11]);
  cod='\0';
  BackTree(FBAK,1,modes);
 }
 if(Not Flag.MenuDrawed)
  SetSeq(7);
 seqrun( cod==F3 And RenameActive==FALSE )
   {
   run(1)
      RenameActive=TRUE;
      TextWind(2,CurentMsg[2],INVERS);
      FileHanding(SET_EXT,(DWORD)exten);
      Str[0]='\0';
//      SetLatKey();
   breakrun;
   rerun(2) /* Запрос доступа к диску источнику */
      FileHanding(REQ_ACCESS,IN) ? TRUE
      : Flag.Warning ? GotoSeq(7) : FALSE
   breakrerun;
   run(3)
      AccReset();
   breakrun;
   rerun(4) /* Ввод нового имени оператором */
      (
       (cod=isalpha(cod) Or iscntrl(cod) Or isdigit(cod)?toupper(cod):'?'),
       (GetsScr(cod,Mesage[30],Str,MAXFILE-1,PrntEds)!=0)
      )
   breakrerun;
   rerun(5) /* Запрос доступа к диску источнику */
      FileHanding(REQ_ACCESS,IN) ? TRUE
      : Flag.Warning ? GotoSeq(7) : FALSE
   breakrerun;
   run(6)
      FileHanding(RENAME_FILE,(DWORD)Str);
   breakrun;
   run(7)
      if(Not Flag.Warning)
       EraseWarning();
      OldFp=FilePointer;
      OldCp=CursPosition;
      FileHanding(SET_EXT,(DWORD)exten);
      FileHanding(NEW_DIR,0);
      FilePointer=OldFp;
      CursPosition=OldCp;
      AccReset();
      TextWind(2,CurentMsg[2],NORMAL);
      Flag.DrawEnded=Flag.NoSwitchMode=FALSE;
      if(Str[0]) memset(Str,0,strlen(Str)-1);
      BackTree(FBAK,1,modes);
      RenameActive=FALSE;
   breakrun;
   endseq;
   }
}				/* End FhRename */

void FhProtect(CHAR cod,WORD* modes,STRING exten)
{
 BYTE OldFp,OldCp;
 static BOOL ProtectActive=FALSE;
 defseq;

 if(Fh.EndDir And cod) /* Если нет имени файла */
 {
  DrawWarning(Mesage[11]);
  cod='\0';
  BackTree(FBAK,1,modes);
 }
 seqrun( cod==F4 And ProtectActive==FALSE )
 {
  run(1)			/* Блокировать переключение режимов */
      Flag.NoSwitchMode=ProtectActive=TRUE;
      TextWind(3,CurentMsg[3],INVERS);      /* Включить кнопку */
      FileHanding(SET_EXT,(DWORD)exten);
   breakrun;
   rerun(2)	 /* Запрос доступа к источнику */
       FileHanding(REQ_ACCESS,IN)
       ? TRUE
       : Flag.Warning? GotoSeq(4) :FALSE 
   breakrerun;
   run(3) 	 /* Изменение статуса */
      FileHanding(PROTECT_FILE,0);
   breakrun;
   run(4)
      OldFp=FilePointer;
      OldCp=CursPosition;
      FileHanding(SET_EXT,(DWORD)exten);
      FileHanding(NEW_DIR,0);
      FilePointer=OldFp;
      CursPosition=OldCp;
      AccReset();
      TextWind(3,CurentMsg[3],NORMAL);
      BackTree(FBAK,1,modes);
      Flag.DrawEnded=Flag.NoSwitchMode=ProtectActive=FALSE;
   breakrun;
   endseq;
   }
}			/* End FhProtect */

		/* Возвращает расширение для групповых операций */
/*
STRING GetExt(STRING str)
{
 static STRING StrExt="*.???";
 StrExt[0]='*';
 StrExt[1]='\0';
 return strcat(StrExt,str);
}			/* End GetExt */
*/
	 /* Вернуть полное имя файла из каталога на которое указывает*/
				/* курсор */
STRING GetDirFileName(STRING ext)
{
 static CHAR tmpstr[MAXPATH];
	CHAR wstr[MAXPATH];

 if(Fh.EndDir)
  strcpy(wstr,UNNAMED);
 else
  sscanf(CurFile,"%s",wstr);
 fnmerge(tmpstr,"","",wstr,ext);
 return tmpstr;
}		/* Конец GetDirFileName */



