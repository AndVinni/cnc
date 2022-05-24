/*            Проект   CNC++ V01.

  Программа проверки готовности канала COM2 

		Гомель. 1991 г.
*/

#include <stdio.h>
#include <dos.h>
#include "cnchard.h"
#include "cncraz.h"
#include "cnccdef.h"
#include "cnccstat.h"
#include "cnccsti.h"
#include "cncint.h"

void cnctrc2()
{ 

 	asm push cx       
	asm push dx      

	_DX=DataRPS;                        
	asm add dx,5
	asm in al,dx                             
	asm test al,00011110B
	asm jnz error_1
	asm test al,00000001B
	asm jnz rec
	stat_in Clr G_DAN;
	asm jmp kon
rec:    stat_in Set G_DAN;
	asm jmp kon
error_1:stat_in Set E_DAN;
kon:    asm pop dx
	asm pop cx

}


