/*  	cncsted.h v01.01

	Определения для работы с файлами

	Функция  : File handing
	Подпроект: CNCSHOW
	Проект:    ELMIS CNC.

	Copyright (c) ELMIS, 1993
	Все права защищены.
*/

/* Методы класса "обработчик файлов" FileHand(): */
typedef
enum    {
	REQ_ACCESS,    /* Запрос доступа к устройству по циклу */
	SET_EXT,       /* Установить  расширение файлов в каталоге */
	SHOW_DIR,      /* Отобразить каталог  */
	NEW_DIR,       /* Создать новый файл каталога */
	SWAP_DEV,      /* Заменить устройства в/в */
	IN_DRIVE_SET,  /* Запомнить новое входное устройство */
	OUT_DRIVE_SET, /* Запомнить новое выходное устройство */
	COPY_FILE,     /* Копировать файл по циклу */
	DELETE_FILE,   /* Удалить файл */
	DELETE_ALL,    /* Удалить все файлы */
	RENAME_FILE,   /* Переименовать файл */
	PROTECT_FILE,  /* Защитить/снять защиту */
	RET_FILE_NAME, /* Возвратить имя текущего файла */
	MOVE_CURSOR,   /* Переместить курсор */
	}
FILE_HAND_METHOD;

typedef
enum  StatDev{            /* Тип стстус устройства */
	NOT_FILE_STRUCT,  /* Статус устройстава без катал структ. */
	FILE_STRUCT,      /* Есть каталоговая структура */
	PROTECT_IN_AUTO=4,/* Запрещен доступ к устройству при интерп.*/
	SWITCH_TIMER=010  /* Требуется переключение частоты таймера */
	}
STAT_DEV;


typedef struct {     /* Тип устpойство */
	       STRING   Path;
	       STAT_DEV Stat;
	       STRING   Name;
	       } DEVICE;

struct FilHandFlag
{
 unsigned ReqActiv :1; /* Активен запрос доступа к устройствам в/в */
 unsigned CerActiv :1; /* Активно подтвеpждение */
 unsigned CopActiv :1; /* Активен процесс копирования */
 unsigned OldTime  :1; /* Включена системная частота таймера */
 unsigned EndDir   :1; /* Указатель файла каталога стоит на EOF */
 unsigned RedrawCat:1; /* Было предупреждение о запрете доступа к дискам */
};

extern struct FilHandFlag Fh;

	/* Определение последовательной конструкции языка */

#define defseq 	    static unsigned char multseq='\0'
#define seqrun(opc) if(opc) multseq='\1';      \
		     if(multseq)	       \
		     {		               \
		      switch(multseq)	       \
		      {			       
			
#define run(num)       case(num):
#define breakrun        multseq++;break	       

#define rerun(num)     case(num):if(	      
#define breakrerun 	)multseq++;break     
				
#define endseq 	       defoult: multseq='\0';}}  		       	

#define SetSeq(point) (multseq=(point))      /* Безусловный переход из вне */
#define GotoSeq(step) ((multseq=(step)-1),TRUE) /* Безусловный переход по */

/* 			 Пример:
 defseq; 		 Инициализация конструкции
 seqrun(<Выражение>)     Условие перезапуска конструкции - если выражение ис-
 {			 тинно управление будет передано на run(1)
  run(1) 		 Начало простого оператора - выполняется один раз,
   < Оператор >		 при следующем входе в конструкцию "seqrun" управле -
  breakrun;		 ние передаётся оператору rerun(2).
  rerun(2)               Начало условного оператора - оператор "rerun(2)"
   < Выражение >	 выполняется до тех пор, пока выражение не станет
  breakrerun;		 истинным.
  endseq;		 Конец конструкции
 }

									  */

#define STOP_INTERP 		(sstaim Ifset OST_O) /* Стоп интерполяции */
#define AccReset()    Fh.ReqActiv=FALSE

#define SUCCESS 0             /* Успех! */
#define IN  0  		      /* Намек на устройства в/в */
#define OUT 1
#define FDC 0x3F2             /* Номер порта управления флопиками */

/* Пртототип */

#define DOSerr() (error_a Ifset ERDOS)
extern BOOL FileHanding(FILE_HAND_METHOD method, DWORD data);
extern void IstSwitch(CHAR CodKey); /* Функции выбора устройств в/в */
extern void DestSwitch(CHAR CodKey);
extern void FlopOff(void);          /* Выключение флопиков */

extern void FhRoot(CHAR,STRING,STRING);   /* Корневая программа */
extern void FhCopFile(CHAR,WORD *,STRING);/* Копирование файла плное */
extern void FhSwapDir(CHAR,WORD *,STRING);/* Изм. направления операций */
extern void FhSwIst(CHAR,WORD *,STRING);  /* Выбрать диск источник */
extern void FhUnlink(CHAR,WORD *,STRING); /* Стереть один файл  */
extern void FhAllUnlink(CHAR,WORD *,STRING); /* Стереть все */
extern void FhRename(CHAR,WORD *,STRING); /* Переименовать файл  */
extern void FhProtect(CHAR,WORD *,STRING);/* Защитить файл */

/* Возвращает расширение для групповых операций */
// extern STRING GetExt(STRING);
extern STRING GetDirFileName(STRING ext); /* Вернуть полн. имя файла из д.*/

/* public: */
extern DEVICE InDev;         /* Входное устройство */
extern DEVICE OutDev;        /* Выходное --------- */
extern BYTE   FilePointer;   /* Номер первого файла в окне */
extern BYTE   CursPosition;  /* Смещение курсора относительно окна */
extern STRING Extention;     /* Расширение файлов по умолчанию */
extern CHAR   CurFile[MAXSTR];/* Файл на кторый указывает курсор */

     

