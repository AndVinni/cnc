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

void Otl(CHAR cod,WORD *modes) /* п/п индикации режима "толчок" */
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
/* Установка G90 по умолчанию */
if(_ReqQuKey Ifset FUN_G91)
   {
   /* Гасим окно с G90 */
   TextWind(F1-1,CurentMsg[F1-1],COLOR_OFF);
   /* Включаем окно с G91 */
   TextWind(F2-1,CurentMsg[F2-1],COLOR_ON);
   }
else
   {
   /* Гасим окно с G91 */
   TextWind(F2-1,CurentMsg[F2-1],COLOR_OFF);
   /* Включаем окно с G90 */
   TextWind(F1-1,CurentMsg[F1-1],COLOR_ON);
   }
/* Ввод команды */
Jog(cod);
// Сюда вставлять отладочную программу.
   /* индикация ошибок   */
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
/* Если команда идти назад или программа отрабатывается то идем */
BackTree(cod,1,modes);
ResetWind(cod,FBAK);
ResetMenu(cod,FBAK);
if(Not Flag.DrawEnded)
   EraseWind();
}/* End Otl */
