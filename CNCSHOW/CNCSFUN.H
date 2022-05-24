/*  	cncsfun.h v01.01

	Определения некоторых функций

	Подпроект: CNCSHOW
	Проект:    ELMIS CNC.

	Copyright (c) ELMIS, 1993
	Все права защищены.
*/

#define CNCSFUNH

/* Таймер */
#define TIMRUS     '\x43'/* Регистр управляющего слова таймера */
#define TIMCANAL0  '\x40'/* Канал 0 таймера */
#define TIMNEWMOD  '\066'/* Режим 3 канала 0 таймера, 2 байта данных */
void Timer(WORD m);    /* Програмирование таймера */
#define TIMNEWDATA 11931  /* Делитеь частоты 1193180 Гц до 100 Гц (10 Ms)*/
#define TIMOLDDATA 0     /* Стандартная частота 18.2 Гц */
#define OldTime()   Timer(TIMOLDDATA) /* Включить старую частоту таймера */
#define NewTime()   Timer(TIMNEWDATA) /* -------- новую ---------- */

		/* Системные номера портов */
#define PLC      2      /* Последоватедьный порт PLC */
#define DRC      3      /* ---- DRC */

#define BIOSDATA 0x40    /* Сегмент области данных BIOS */
#define PRINTERPORT 0xA  /* Указатель номеpа порта принтера */
#define BiosCom1 0x4
#define BiosCom2 0x6

/* Биты установки портов */
#define BIT_8     0x03   /* 8 бит данных */
#define STOP2     0x04   /* 2 стоп-бита */
#define SPEED     0xE0   /* скорость передачи 9600 бод */
#define PAR       0      /* паpитета нету аще */

/* Биты состояния COM-портов */
#define DTR      0400    /* Готовность данных-байт данных получен */
#define OE      01000    /* Ошибка переполнения,вы не успели считать пред.данн.*/
#define PE      02000    /* Ошибка четности-шум в линии */
#define FE      04000    /* Передача не синхронизирована */
#define BD     010000    /* Запрос от устр. о конце передачи-длинн.серия еден.*/
#define TRE    020000    /* Передающий регистр данных пуст */
#define TSR    040000    /* Сдвиговый регистр передачи пуст,данн.перед. в лин.*/
#define TMT   0100000    /* Обрыв линии */

		/* Макросы работы с последовательными портами */
			/* Инициализация порта */
#define InitCom(PortNumber)  					  	\
	bioscom(0,_COM(PortNumber).Event | _COM(PortNumber).Bit | 	\
	_COM(PortNumber).Stop | _COM(PortNumber).Speed,PortNumber)

	/* Получить состояние последоательных портов в/в */
#define StatCom(PortNumber)  bioscom(3,0,PortNumber)
			/* Чтение */
#define ReadCom(PortNumber)  bioscom(2,0,PortNumber)
/* Запись байта */
#define WriteCom(byte,PortNumber)  bioscom(1,byte,PortNumber)

void outqup();

/* Вывод информации в быстрый канал связи с контроллером сервопривода*/
extern WORD DataReg;
extern WORD ContrReg;
extern WORD StatReg;/* Номера портов принтера */

/* Макросы */
/* Разрешение вложенности прерываний */
#define TrapEnable() \
outportb(0x20,inportb(0x20)|0x20)

typedef enum
{
 NOBLOCKFID,
 BLOCKFID
} StatFid;

void SetError(BYTE Num,BYTE Kls,BYTE Ist,BYTE Rem,StatFid BlockFid);
void PrintFreeMem(void);
/* Чтение файлов сообщений */
void ReadMsg(STRING **array,const STRING dfile);
/* освобождение памяти от файлов сообщений */
void FreeMesage(STRING** arraymesage);
