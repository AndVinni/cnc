/*            Проект   CNC++ V01.

  Программа проверки  готовности канала COM1
		   

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

void cnctrc1()
{ 

 	asm push cx      
	asm push dx      

	_DX=DatCOM1;                        
	asm add dx,5
	asm in al,dx                             
	asm test al,00011110B
	asm jnz error_1
	asm test al,00000001B
	asm jnz rec
	stat_in Clr PS_W;
	asm jmp kon
rec:    stat_in Set PS_W;
	asm jmp kon
error_1:stat_in Clr PS_W;
	stat_in Set PS_E;
kon:    asm pop dx
	asm pop cx

}/* End */


