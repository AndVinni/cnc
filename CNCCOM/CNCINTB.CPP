#include "cnchard.h"
#include "cncraz.h"
#include "cnccdef.h"
#include "cnccsti.h"
#include "cncint.h"
#include "cncintb.h"



                       /*CNC-->CNCDR*/

REAL Fproc,                  /*procent podachi */
      Sproc[NUMS];               /*procent S1*/

BUF_STRUCT *ykz_byf[KBUF];
INT   _sindex[NUMS];
		     /*CNCDR-->CNC*/

void (*fway[NMOVEF])(); /*����� �ࠥ��ਨ ��������,ᨭ�� ��*/
void  (*sway[NMOVES])(INT i);  /*              诨����� */



