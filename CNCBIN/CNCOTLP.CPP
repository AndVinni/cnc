#include <stdio.h>
#include "cnchard.h"
#include "cncshow.h"
#include "cncscr.h"
#include "cncunpac.h"
#include "cncint.h"
#include "cncintb.h"
#include "cncpar.h"
#include "cncsgeom.h"
#include "cncsfspr.h"
#include "cncsjog.h"
#ifdef __MSDOS__
#include <string.h>
#include <stdlib.h>
#else
#endif

void Otl(CHAR cod,WORD *modes) /* �/� ������樨 ०��� "⮫箪" */
{
  INT ii_o,
       ii_o1;
ResetWind(cod,F2);
ResetMenu(cod,F2);
if(Not Flag.DrawEnded)
   {
   EraseWind();
   CtrlWindows(modes);
   }
/* ��⠭���� G90 �� 㬮�砭�� */
if(_ReqQuKey Ifset FUN_G91)
   {
   /* ��ᨬ ���� � G90 */
   TextWind(F1-1,CurentMsg[F1-1],COLOR_OFF);
   /* ����砥� ���� � G91 */
   TextWind(F2-1,CurentMsg[F2-1],COLOR_ON);
   }
else
   {
   /* ��ᨬ ���� � G91 */
   TextWind(F2-1,CurentMsg[F2-1],COLOR_OFF);
   /* ����砥� ���� � G90 */
   TextWind(F1-1,CurentMsg[F1-1],COLOR_ON);
   }
/* ���� ������� */
Jog(cod);
// � ��⠢���� �⫠����� �ணࠬ��.
   /* �������� �訡��   */
Locate(0,3);
ClrToEnd(COLOR_OFF);
for (ii_o1=3,ii_o=0;ii_o<=shet;ii_o++,ii_o1++)
   { Locate(0,ii_o1);
PrintScr(COLOR_OFF,"mpr.ykz_par[ii_o] =%d",mpr.ykz_par[ii_o++],0,0,0,0);
ii_o++;
PrintScr(COLOR_OFF," =%d",mpr.ykz_par[ii_o++],0,0,0,0);
ii_o++;
PrintScr(COLOR_OFF," =%d",mpr.ykz_par[ii_o++],0,0,0,0);
    }

Flag.DrawEnded=TRUE;
/* �᫨ ������� ��� ����� ��� �ணࠬ�� ��ࠡ��뢠���� � ���� */
BackTree(cod,1,modes);
ResetWind(cod,FBAK);
ResetMenu(cod,FBAK);
if(Not Flag.DrawEnded)
   EraseWind();
}/* End Otl */
