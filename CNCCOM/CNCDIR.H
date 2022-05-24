/*  	cncdir.h v01.01

	Определения для каталоговой структуры CNC

	Проэкт:    ELMIS CNC.

	Copyright (c) ELMIS, 1993
	Все права защищены.
*/

#define CNCDIRH

	/* Смещение в массиве конфигурации до описания обрабат устройств.*/

#define HD_BIN  9  /* Жесткий диск - двоичные файлы */
#define HD_CNC 16  /* Жесткий диск - технологические программы, таблицы */
#define HD_RSC 10  /* Жесткий диск - конфигурация, сообщения, шрифты ...*/
#define ED_SYS  0  /* Електронный диск - временные файлы, ошибки  */
#define ED_CNC 19  /* Електронный диск - технологические программы, таблицы,
            				 pабочие файлы */
#define ED_RSC  8  /* Електронный диск - конфигурация, тексты сообщений */
#define FD_CNC 22  /* Гибкий диск - технологические программы  и таблицы
		      для сохран. */
#define PRF    25  /* Устройство с послед. доступом */
#define DNC    28  /* ЭВМ высшего ранга */

		/* Расширения двоичных файлов таблиц */

#define PROG_EXT    ".NC"
#define TABNUL_EXT  ".TNL"
#define TABKOR_EXT  ".TKR"
#define TEHPAR_EXT  ".TPR"
#define MPAR_EXT    ".PAR"
#define TABKS_EXT   ".TTL"

		/* Имена файлов форм таблиц */

#define FTABNUL  "TABNULL.FRM"
#define FTABKOR  "TABKORR.FRM"
#define FTEHPAR  "TEHNPAR.FRM"
#define FMPAR    "MACHPAR.FRM"
#define FTABKS   "TABTOOL.FRM"

		/* Расширения некоторых файлов */

#define RESORCE_EXT	".RSC"       /* Файлы меню */
#define F_ERR           ".ERR"       /* Файлы ошибок */
#define F_NUM           ".NUM"       /* Адреса кадров УП */
#define F_WRK           ".WRK"       /* Рабочий файл */
#define NMP             ".NMP"       /* Файл имен всех п.п */
#define MESAGE_EXT	".MSG"       /* Файлы сообщений */
#define TEMP_FILE	".TMP"	     /* Времен. файлы (необходимо удалять) */	

	      /* Имена некоторых файлов */

#define TAB_KG          "KG"          /* Таблица G функций*/
#define TAB_FMS         "FMS"         /* Таблица M функций*/
#define TAB_GS          "GS"          /* Таблица несовместимых G функций*/
#define FO_YP           "UNPACK"      /* файл ошибок УП*/
 
#define TEMP_DIR  "CNCDIR" 	      /* Временнной директорий */
#define UNNAMED   "UNNAMED"           /* Временное имя нового файла */
#define GROUPFILE "*"                 /* Гpупповое имя */


