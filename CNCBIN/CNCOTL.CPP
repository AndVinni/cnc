#include <conio.h>
#include "cnchard.h"
#include "cncshow.h"
#include "cncscr.h"
#include "cncraz.h"
#include "cnccdef.h"
#include "cnccstat.h"
#include "cnccsti.h"
#include "cncint.h"
#include "cncintb.h"
#include "cncun1.h"
#include "cncun2.h"
#include "cncun3.h"
#include "cncpar.h"
#include "cncsgeom.h"
#include "cncsfspr.h"
#include "cncsjog.h"
#include "cncsfh.h"
#include "cncplc.h"
#ifdef __MSDOS__
#include <string.h>
#include <stdlib.h>
#include <math.h>
#else
#endif

void Otl(CHAR cod,WORD *modes) /* п/п индикации режима "толчок" */
{ 
ResetWind(cod,F2);
ResetMenu(cod,F2);
if(Not Flag.DrawEnded)
   {
   EraseWind();
   CtrlWindows(modes);
   }
/* Установка G90 по умолчанию */
if(ReqQuKey.G91)
   {
   /* Гасим окно с G90 */
   TextWind(F1-1,CurentMsg[F1-1],NORMAL);
   /* Включаем окно с G91 */
   TextWind(F2-1,CurentMsg[F2-1],INVERS);
   }
else
   {
   /* Гасим окно с G91 */
   TextWind(F2-1,CurentMsg[F2-1],NORMAL);
   /* Включаем окно с G90 */
   TextWind(F1-1,CurentMsg[F1-1],INVERS);
   }
if(cod==F4)
   /* Установить признак режима "выход в исходное"*/
   wwtaim Set PYSK_ID;
if(cod==F5)
   {
   /* Снять признак выхода в исходное*/
   wwtaim Clr PYSK_ID;
   EraseWarning();
   }
/* Ввод команды */
Jog(cod);
// Сюда вставлять отладочную программу.
   /* индикация ошибок   */
gotoxy(1,4);
NormColor();
cprintf(" err[0] =%d ",err[0]);
cprintf(" error_a =%o ",error_a);
cprintf(" cont =%o ",cont);
cprintf(" mir =%o ",mir);
cprintf(" rcrug[nomn] =%d ",(WORD)rcrug[nomn]);
cprintf(" nomn =%d ",nomn);
cprintf(" nomf =%d ",nomf);
//cprintf(" sum.par_c[0] =%o ",sum.par_c[0]);
//cprintf("fi =%d ",vtakt[5]*exp_s);
//cprintf("fi1 =%d ",ykz_byf[tzbv]->FI1*exp_s);
//cprintf("fi2 =%d ",ykz_byf[tzbv]->FI2*exp_s);
//cprintf("klin =%d ",ykz_byf[tzbv]->klin[0]*exp_s);
gotoxy(1,5);
//cprintf("enext1=%d ",ykz_byf[tzbv]->KF1*exp_s);
//cprintf("enext2==%d ",enext[nomf][ik2]);
//cprintf("enext3=%d ",elast[nomf][ik1]);
cprintf("wms=%o ",*wms);
cprintf("msstat=%o ",msstat);
cprintf("Fh.ReqActiv=%d ",Fh.ReqActiv);
cprintf("Fh.Ceractiv=%d ",Fh.CerActiv);
cprintf("stdrc=%o ",*stdrc);
/*cprintf("I_S=%d ",I_S[0]);
cprintf("st_ds=%d ",st_ds[0]);
//cprintf("mo2[4]=%o ",mo2[4]);
cprintf("I_P=%d ",I_P);
cprintf("KO=%d ",KO);
//cprintf("sost1=%d ",sost1);
clreol();        */
gotoxy(1,6);                       
//cprintf("ssprr=%o ",ssprr);
//cprintf("SpeedS=%ld ",SpeedS[0]);
//cprintf("rassz[3]=%ld ",(*(rass+3)));
//cprintf("_NIMP[0]=%ld ",_NIMP[0]);
//cprintf("refst[0]=%d ",refst[0]);
//cprintf("refst[1]=%d ",refst[1]);
//cprintf("REF_POINT=%d ",REF_POINT);
//cprintf("xdir=%o ",xdir);
//cprintf("xdirs=%o ",xdirs);
cprintf("tekv1=%d ",tekv[ik1]*exp_s);
//cprintf("REFSTS=%d ",refsts[0]);
cprintf("tekv2=%d ",tekv[ik2]*exp_s);
cprintf("SNSTUP[0]=%d ",_SNSTUP[0]);
cprintf("SpeedS=%d ",SpeedS[0]);
clreol();
/*gotoxy(1,6);
cprintf("zdrive =%o ",zdrive);
cprintf("pdrive =%o ",pdrive);
cprintf("msstat1 =%o ",msstat1);
cprintf("msstat =%o ",msstat);
clreol();*/
gotoxy(1,7);
cprintf("_ptask =%o ",_ptask);
cprintf("ktask =%o ",ktask);
cprintf("ktasks =%o ",ktasks);
cprintf("wcnc =%o ",wcnc);
cprintf("blmove =%o ",blmove);
cprintf("findex =%d ",ykz_byf[ik]->findex);
clreol();
/*gotoxy(1,8);
cprintf("sleg =%o ",sleg);
cprintf("ax_on =%o ",ax_on);
cprintf("*xquit=%o ",*xquit);
cprintf("*stdrc =%o ",*stdrc);
cprintf("*stdrc0 =%o ",*stdrc0);
cprintf("statk =%o ",statk);
//cprintf("FT[0] =%d ",(ykz_byf[tzbv]->FT[0]));
clreol();*/
/*gotoxy(1,9);
//cprintf("refsts[0] =%d ",refsts[0]);
cprintf("vkadr[4] =%d ",vkadr[4]*exp_s);
cprintf("vkadr[5] =%d ",vkadr[5]*exp_s);
//cprintf("ik1 =%d ",ik1);
//cprintf("ik2 =%d ",ik2);
//cprintf("Spr =%o ",*Spr);
//cprintf("Spr1 =%o ",*Spr1);

clreol();
gotoxy(1,10);  */
/*cprintf("stask =%o ",ykz_byf[tzbv]->stask);
cprintf("_MASKF =%o ",_MASKF);
cprintf("OKEY =%o ",OKEY);
cprintf("task[tzbv] =%o ",ykz_byf[tzbv]->task);
cprintf("xref =%o ",xref);
//cprintf("rfr =%d ",(INT)rfr);
clreol();*/
/*gotoxy(1,11);
cprintf("wkadr =%o ",ykz_byf[tzbv]->wkadr);
cprintf("*prxr =%o ",*prxr);
cprintf("*prxq =%o ",*prxq);
cprintf("*prxz =%o ",*prxz);
cprintf("*prxv =%o ",*prxv);
cprintf("*prxk =%o ",*prxk);
cprintf("*wms =%o ",*wms);
clreol();*/
gotoxy(1,12);
//cprintf("xtakt[0] =%i ",xtakt[0]);
//cprintf("xtakt[1] =%i ",xtakt[1]);
cprintf("sp_chan =%o ",sp_chan[0]);
cprintf("ssw_sh =%o ",ssw_sh);
cprintf("bnzvk1 =%o ",ykz_byf[tzbv]->bnzvk1);
//cprintf("ltorm1 =%o ",ltorm1);
//cprintf("sindex =%d ",_sindex[0]);
//cprintf("_stask =%d ",_stask);
//cprintf("staskp =%d ",staskp);
//cprintf("stasks =%d ",stasks);


clreol();
/*gotoxy(1,13);
cprintf("tzbv =%d ",tzbv);
cprintf("tzbz =%d ",tzbz);
cprintf("bnzvk[tzbv] =%o ",ykz_byf[tzbv]->bnzvk);
cprintf("KCAP[0] =%d ",_KCAP[0]);
clreol();
gotoxy(1,14);
//cprintf("FT[0] =%d ",ykz_byf[tzbv]->FT[0]);
cprintf("wwtaim =%o ",wwtaim);
cprintf("sscp =%o ",sscp);
cprintf("sstaim1 =%o ",sstaim1);
cprintf("sstaim =%o ",sstaim);
cprintf("statk1 =%o ",statk1);

clreol();
gotoxy(1,15);
cprintf("timer =%o ",timer);
cprintf("xcntin =%o ",xcntin);
cprintf("xnin =%o ",xnin);
cprintf("shet =%o ",shet);
cprintf("lwp =%d ",lwp);
cprintf("strk =%o ",strk);
clreol();
gotoxy(1,16);
//cprintf("frazg  =%d ",ykz_byf[ik]->frazg);
//cprintf("fkdin  =%d ",ykz_byf[ik]->fkdin);
//cprintf("ftorm =%d ",ykz_byf[ik]->ftorm);
//cprintf("klin =%d ",ykz_byf[ik]->klin[XIK1]);
//cprintf("fa =%d ",ykz_byf[ik]->fa);
cprintf("nax0  =%o ",nax[0]);
cprintf("nf =%d ",nf);
gotoxy(0,17);
//cprintf("FI1  =%d ",(ykz_byf[tzbv]->FI1*exp_s));
//cprintf("KF1 =%d ",(ykz_byf[tzbv]->KF1*exp_s));
cprintf("fek  =%d ",fek);
//cprintf("fi =%d ",(fi*10000.));
cprintf("storm =%d ",storm);
cprintf("fost[0] =%d ",fost[0]);

gotoxy(0,18);
cprintf("ip1 =%d ",ip1);
cprintf("ip2 =%d ",ip2);
//cprintf("AC =%d ",ykz_byf[tzbv]->AC);
//cprintf("BC =%d ",ykz_byf[tzbv]->BC);
//cprintf("RC =%d ",ykz_byf[tzbv]->RC);

gotoxy(0,19);
//cprintf("vtakt4 =%d ",(vtakt[4]*10000.));
//cprintf("vtakt5 =%d ",(vtakt[5]*10000.));
//cprintf("vtakt6 =%d ",(vtakt[6]));
cprintf("msstat =%o ",msstat);
cprintf("msstat1 =%o ",msstat1);
*/
Flag.DrawEnded=TRUE;
/* Если команда идти назад или программа отрабатывается то идем */
BackTree(cod,1,modes);
ResetWind(cod,FBAK);
ResetMenu(cod,FBAK);
if(Not Flag.DrawEnded)           
   EraseWind();
}/* End Otl */

