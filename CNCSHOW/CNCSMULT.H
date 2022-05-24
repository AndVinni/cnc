/*            Проект   CNC++ V01.
		 Тема Multic
		Файл CNCMULT.H

   Определения диспетчера процессов для CNC++

   Продукция Отдела исследований и внедрения
	   систем ЧПУ и электоприводов
	       СКБ ОЦ ГСПО Кирова

		Гомель. 1992 г.
*/

#define CNCMULTH

#ifndef DWORD
typedef unsigned long DWORD;
#endif

typedef void (*Process)(DWORD par1,DWORD par2,DWORD par3);

typedef struct descr		/* Дескриптор процесса */
{
 unsigned priopity;
 Process proc;
 struct descr *next;
} Descriptor;

typedef Descriptor *Signal;	/* Сигнал в смысле Модулы */
typedef Descriptor *Trap;	/* Сигнал преравания */

				/* Поставить процесс в очередь к сигналу */
void Launch(Signal signal,Process proc,DWORD par1,DWORD par2,DWORD par3);
				/* Послать сигнал ждущим его */
void Send(Signal signal);
				/* Уничтожить текущий пpоцесс */
#define Expire()	return
