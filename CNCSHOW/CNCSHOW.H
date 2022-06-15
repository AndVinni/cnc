/*  	cncshow.h v01.01

	Глобальные определения индикации

	Подпроект: CNCSHOW
	Проект:    ELMIS CNC.

	Copyright (c) ELMIS, 1993
	Все права защищены.
*/

#if !defined(___DEFS_H)
#include<_defs.h>
#endif
/* Флаги условной компиляции */
// #define GRAPH   /* Есть графика */
#define PGRAPH Yes /* Есть коды псевдографики в знакогенераторе */
#define COLOR  Yes /* Есть цвет или градации яркости на B&W */
#define AT     Yes /* Машина IBM AT */
#define EGA    Yes /* Дисплей EGA */

typedef struct {
	unsigned StatShow : 1;  /* Ошибочное завершение программы */
	unsigned DrawEnded : 1;  /* Флаг завершения форм. картинки */
	unsigned MenuDrawed : 1;  /* Меню уже наpисовано */
	unsigned PromtDrawed : 1; /* Подсказка нарисована */
	unsigned NotWork : 1;  /* Не надо вызывать индикацию */
	unsigned NoSwitchMode : 1;/* Запрет переключения режимов */
	unsigned Warning : 1;  /* Активно предупреждение */
	unsigned NotCat : 1;  /* Активно предупреждение */
	unsigned StopEndK : 1;  /* Активен подрежим покадровый */
} SEMAFOR;

#define COMRESET   "cncreset.bat"	/* ммя ком. файла сброса УЧПУ */
#define POSTSEG    0xF000			/* Адресс перзапуска системы */
#define POSTOFS    0xFFF0			/* -"- */
#define QUANTWIND  '\5'				/* Количество окон управления */
#define VECTKEY    '\x09'			/* Вектор аппаратного прер. клавиатуры */
#define NEWVECTKEY '\x60'			/* Новый вектор прерывания клавиатуры */
#define NEWVECTIMER '\x61'			/* Новый вектор прерывания таймера */
#define ZF         '\x40'			/* Ноль флаг процессора */
#define KEYB       '\x16'			/* BIOS прерывание от клавиатуры - вектор */
#define ERRVECT    '\x24'			/* Номер вектора обработчика крит. ош. */
#define DOSERR     '\x59'			/* Номер функции ДОС информации об ошибках */
#define DOSVERS     '\0'			/* Номер версии ДОС для DOSERR */
#define VECTIMER   '\x08'			/* Номер вектора таймера */
#define DEL        '\x08'			/* Код клавиши забой */

#define MAXSTR      128  /* Максимальная длина обр. строки */

/* Станочные дела */
#define TAUTO    '\2'     /* Режимы станка */
#define TDIAGN   '\5'
#define TEDITPR  '\4'
#define TEDKORR  '\3'
#define TMANUAL  '\1'

/* Коды станочных клавиш передаваемых программе индикации */
#define MAUTO   '\6'   /* Код клавиши режима  "Aвтомат" */
#define MDIAGN  '\7'   /* -------------------- "Диагностика" */
#define MEDITPR '\27'  /* -------------------- "Редактор УП" */
#define MEDKORR '\12'  /* -------------------- "Редактор коррекций */
#define MMANUAL '\13'  /* -------------------- "Ручной" */
#define F1      '\1'   /* -------------------- меню  1 */
#define F2      '\2'   /* -------------------------- 2 */
#define F3      '\3'   /* -------------------------- 3 */
#define F4      '\4'   /* -------------------------- 4 */
#define F5      '\5'   /* -------------------------- 5 */
#define FBAK    '\33'  /* -------------------- назад в пред. меню */
#define CURUP   '\14'  /* -------------------- курсор вверх */
#define CURDOWN '\20'  /* --------------------------- вниз  */
#define CURLEFT '\21'  /* --------------------------- влево */
#define CURRIGHT '\22' /* --------------------------- вправо */
#define STOP    '\23'  /* --------------------- стоп программы */
#define PUSK    '\24'  /* --------------------- пуск --------- */
#define PLUS    '\25'  /* толчок в плюс */
#define MINUS   '\26'  /* -------- минус */

/* Расширенные коды IBM PC клавиш инидикации */
#define EAUTO    '\x41' /* Код клавиши режима  "Aвтомат" */
#define EDIAGN   '\x42' /* -------------------- "Диагностика" */
#define EEDITPR  '\x43' /* -------------------- "Редактор УП" */
#define EEDKORR  '\x44' /* -------------------- "Коррекция" */
#define EMANUAL  '\x40' /* -------------------- "Ручной" */
#define EF1      '\x3B' /* -------------------- меню  1 */
#define EF2      '\x3C' /* -------------------------- 2 */
#define EF3      '\x3D' /* -------------------------- 3 */
#define EF4      '\x3E' /* -------------------------- 4 */
#define EF5      '\x3F' /* -------------------------- 5 */
#define ECURUP    '\x48' /* -------------------- курсор вверх */
#define ECURDOWN  '\x50' /* --------------------------- вниз  */
#define ECURLEFT  '\x4B' /* --------------------------- влево */
#define ECURRIGHT '\x4D' /* --------------------------- вправо */
#define ESTOP     '\x52' /* -------------------- стоп программы */
#define EPUSK     '\x53' /* -------------------- пуск --------- */
#define EPLUS     '\x4E' /* -----------------Толчок в плюс */
#define EMINUS    '\x4A' /* ----------------------- минус  */

/* Scan-коды станочных клавиш реального времени */
#define SFLEFT   '\x47' /* -----------------Подача меньше */
#define SFRIGHT  '\x49' /* ----------------------- больше */
#define SSLEFT   '\x4F' /* -----------------Обороты меньше */
#define SSRIGHT  '\x51' /* ------------------------ больше */
#define STPLUS   '\x4E' /* -----------------Толчок в плюс */
#define STMINUS  '\x4A' /* ----------------------- минус  */
#define SSTOP    '\x52' /* ----------------- стоп --------- */
#define SPUSK    '\x53' /* ----------------- пуск --------- */
#define SS1_S2   '\x4C' /* ---------- переключение шпинделей */

#define RETURN '\15' 	/* Клавиша ввод */

/* Биты станочных клавиш реального времени */
#define RFLEFT   '\01'   /* -----------------Подача меньше */
#define RFRIGHT  '\02'   /* ----------------------- больше */
#define RSLEFT   '\04'   /* -----------------Обороты меньше */
#define RSRIGHT  '\010'  /* ------------------------ больше */

#define BEGCONTRX   MINSZX     /* Координаты строки сообщений о реж. индик. */
#define BEGCONTRY   MAXSZY-4   /* -------*/
#define DOS         '\x21'     /* Номер вектора сервиса ДОС */

/* Параметры переключателей % (начальные значения)*/
#define BIGSTEP    20   /* Шаг быстрого изменения подачи и оборотов */
#define LITLSTEP   10   /* --  медленнного ------ */
#define MAXF      140   /* Максимальный процент подачи */
#define MINF       10   /* Минимальный --------------- */
#define MAXS      180   /* Максимальный процент оборотов первого шпинделя */
#define MINS       40   /* Минимальный ---------------------------------- */


void StatWindow(void);			/* Вывести окно состояния CNC */
void CtrlWindows(WORD* modus);		/* Вывод окна управления CNC */
void zapic(void);			/* */
STRING FileName(BYTE mode, WORD* mod); 	/* Вычисление имени файла сообщений */
enum Invers { NORMAL, INVERS };		/* Вывод текста в одно окно */
void TextWind(BYTE numwin, const STRING txt, enum Invers invers);
void Windows(enum Invers color);	/* Вывод текста в окна управления */
void PrintNode(STRING string);		/* Вывод узла дерева индикации */
				  /* Вернуться назад по дереву на N шагов */
void BackTree(CHAR cod, BYTE step, WORD* modes);
void DistToGo(void);   			/* Вывод информации о рассогласовании */
					/* Функции ввода-вывода */
BYTE GetDNCcod(void);  			/* Ввод байта с ЭВМ высш. ранга */
CHAR GetSimb(void);    		/* Ввод символа с клавиатуры без ожидания */
//BOOL GetRusStatus(void);		/* Состояние клавиатуры РУС/LAT */
void Shell(void);      			/* Выход в ДОС */
void Boot(void);        		/* Перезагрузка */

			/* Обработка прерываний */
#ifdef __cplusplus
void interrupt _FAR Getscancod(...);/* Обработка "быстрых" кнопок по прер. */
void interrupt _FAR NullFun(...);   /* Пустая функция - заглушка прерываний */
void interrupt _FAR IbmError(...);  /* Обработка прер. по ош. ДОС */
#else
void interrupt _FAR Getscancod();	/* Обработка "быстрых" кнопок по прер. */
void interrupt _FAR NullFun();		/* Пустая функция - заглушка прерываний */
void interrupt _FAR IbmError();		/* Обработка прер. по ош. ДОС */
#endif
		/* Функции основных режимов индикации. */
void Cnc_show(void);    		/* мндикация ЧПУ */
void Cnc_auto(CHAR cod);		/* Автомат  - основная программа  */
void Cnc_diag(CHAR cod);		/* ---------------- Диагностика */
void Cnc_editpr(CHAR cod);		/* ---- Редактор программ */
void Cnc_edkorr(CHAR cod);		/* ---------------- Коррекция */
void Cnc_manual(CHAR cod);		/* --------- ручного режима */

			/* Функции общего назначения */
void Cnc_show(void);			/* Функция идикации */
BOOL Beginer(void);			/* мнициализация Cnc_show() */
BOOL Password(void);   			/* Ввод пароля */
void Setting(BYTE mode);       		/* Некторые установки */
CHAR Inkey(void);      			/* Прием кода клавиши с клавиатуры  */
void Swicher(CHAR cod);		   /* Переключение между режимами индикации */
void Swichcod(CHAR cod, WORD* mods);	/* Пререключение программ индикации */
//void SetRusKey(void);			/* Переключение режимов клавиатуры */
//void SetLatKey(void);

void ResetMenu(CHAR Cod, CHAR Simb);	/* Сброс Меню */
void ResetWind(CHAR Cod, CHAR Simb);     /* Сброс флага перерисовки */


#ifdef DEBUG		/* Чужие функции */
#define taim   NullFun
#else
void interrupt taim(void); 	    /* Оснвная п/п обработки таймерного пр. */
#endif
			/* Переменные CNCSHOW */
extern CHAR 	CodKey;			/* Код нажатой клавиши*/
extern BYTE 	Mode;  			/* Номер режима (5 - ручной) */
extern SEMAFOR 	Flag;  			/* Внутренние признаки */
extern STRING* Config;			/* Массив описания конфигурации системы */
extern STRING* ModeTool; 		/* Текстовый массив pежимов станака */
extern STRING* CurentMsg;		/* Текущий текстовый массив */
extern STRING* Mesage;			/* Основные тексты индикации */

#ifdef __cplusplus
extern void interrupt _FAR (*PtrNewVect)(...); /* Рабочая переменная */
extern void interrupt _FAR (*Ptroldvect)(...); /* Рабочая переменная */
extern void interrupt _FAR (*PtrIbmErr)(...);  /* Указатель на старую программу обр. ош. */
extern void interrupt _FAR (*PtrTimer)(...);   /* Указатель на старую программу обр. таймера */
extern void interrupt _FAR (*PtrNTimer)(...);  /* Указатель на новую программу обр. таймера */
#else
extern void interrupt _FAR(*PtrNewVect)(); /* Рабочая переменная */
extern void interrupt _FAR(*Ptroldvect)(); /* Рабочая переменная */
extern void interrupt _FAR(*PtrIbmErr)();  /* Указатель на старую программу обр. ош. */
extern void interrupt _FAR(*PtrTimer)();   /* Указатель на старую программу обр. таймера */
extern void interrupt _FAR(*PtrNTimer)();  /* Указатель на новую программу обр. таймера */
#endif

extern BYTE  NumError; 			/* Номер ошибки */
extern BYTE  KlsError; 			/* Класс ошибки */
extern BYTE  IstError; 			/* мсточник ошибки */
extern BYTE  RemError; 			/* Рекомендации ДОС к исправлению ошибки */

					/* Регистры парралельного порта */
extern WORD DataReg, StatReg, ContrReg;

extern WORD ModesM;  		/* Номер текущей функции РУЧНОГО режима  */
extern WORD ModesA;  		/* Номер текущей функции режима АВТОМАТ  */
extern WORD ModesD;  		/* Номер текущей функции режима ДмАГНОСТмКА */
extern WORD ModesE;  		/* Номер текущей функции редактора  */
extern WORD ModesK;  		/* Номер текущей функции редактора корректоров */
extern BYTE MulticM; 		/* Мультиплексор программ ручного режима */
extern BYTE MulticD; 		/* Мультиплексор программ режима ДмАГНОСТмКА */
extern BYTE MulticA; 		/* Мультиплексор программ режима АВТОМАТ */
extern WORD OldModus; 		/* Старый режим */

#ifndef __STDIO_H
#include <stdio.h>
#endif

