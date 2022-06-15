
#include <dos.h>
#include <math.h>
#include <stdio.h>
#include "cncraz.h"
#include "cnccdef.h"
#include "cnchard.h"
#include "cnccstat.h"
#include "cnccsti.h"
#include "cncintb.h"
#include "cncint.h"
#include "cncplc.h"
#include "cncpar.h"
#include "cncun1.h"
#include "cncvoidt.h"
#include "cncshow.h"
#include "cncsfh.h"
#include "cncsfun.h"
#include "cncsfspr.h"


void interrupt _FAR taim(...)
{
	static WORD ss_time = 0;
	/* Буффер для сохранения сост. мат. прц. */
//    static BYTE fbuf[94];

	disable();
	outportb(0x21, '\2');       /* Запрет прерывания от клавиатуры */
	TrapEnable();  		/* Подтверждение аппаратного прерывания */
//    asm fsave fbuf
//    asm fwait
	enable();			/* Разрешение прерываний */
	i_time += 10;
	timer++;
	//  timer1++;
	//  if (timer>=4 )
	//    if (timer>=CIKL_T )
	{      /* 10 млс */
		if (timer > 1)
		{
			error_1 Set  ERDOS1;
			statk Set(ALARM_O | ALARM_N);
		}
		timer = 0;
		if (//wwtaim Ifset PR_PR 
			ss_time == 1
			|| error_1 Ifset ERDOS1)
		{
			register i_1;
			if (~error_1 Ifset ERDOS1)
				error_1 Set ERDOS1;
			statk Set(ALARM_O | ALARM_N);
			/*   0  ->ЦАП */
			*cap0 = MASK1;
			*wms Clr WORK_CNC;
			MODE_WORK Clr BIT0;
			for (i_1 = 0; i_1 < NUM; i_1++)
				*(xcap + i_1) = 0;
		}
		else
		{
			wwtaim Set PR_PR;
			ss_time = 1;
			if (Fh.ReqActiv)
			{
				if (wcnc Ifset TESTNM)
					Fh.CerActiv = TRUE;
				else
				{
					if (!Fh.CerActiv)
					{
						*wms Set ABLIO;
						MODE_WORK Set BIT2;
						if ((msstat Ifset QBLIO
							|| error_a Ifset MSINT_2)
							&& (stat_ea Ifset QBLCOM1
								|| error_a Ifset MSINT_1))
							Fh.CerActiv = TRUE;
					}
				}
			}
			else
				if (Fh.CerActiv)
				{
					*wms Clr ABLIO;
					msstat Clr QBLIO;
					stat_ea Clr QBLCOM1;
					MODE_WORK Clr BIT2;
					date = MASK1;
					BLK_BUT Clr BIT1;
					xcntin = 0;
					Fh.CerActiv = FALSE;
				}
			if (sscp Ifset N_ZAG
				|| error_1 Ifset N_PARAM)        /* начальная загрузка */
			{
				sost = BEGIN_T;
				ss_time = 0;
				cnctirps();
			}
			else           /* ошибка цикла или ошибка измер. системы */
			{
				if ((~stat_in Ifset FIRST_PR)
					&& (~error_1 Ifset ER_IRPR)
					&& (~error_1 Ifset ERDOS1)
					&& !(Fh.CerActiv)
					&& (~wcnc Ifset TESTNM))
					cnctrpr();
				cnctirps();
				if (~error_1 Ifset ERDOS1)
				{
					if (error_a Ifset MSINT_2
						|| error_a Ifset ERDOS
						|| error_a Ifset MSINT_1
						|| error_1 Ifset ER_IRPR)
					{
						MODE_WORK Clr BIT0;
						*wms Clr WORK_CNC;
						if (~sstaim Ifset OST_O)
							wwtaim Set STOP_TT;
						wcnc Set STOPF;
					}
					else
						if (~sscp Ifset RESET_O
							&& statk Ifset ALARM_N)
						{
							if (error_a Ifset MSAVAR)
							{
								MODE_WORK Clr BIT0;
								*wms Clr WORK_CNC;
								//		     wcnc Set CAVAR ;
								if (!(sstaim Ifset OST_O))
									wwtaim Set STOP_TT;
							}
							else
							{
								if (msavr Ifset TBREAK && !(move & _MASKF))
								{
									error_a Set ER_MO;
									wwtaim Set STOP_TT;
									wcnc Set STOPF;
									statk Set(ALARM_O | ALARM_N);
									msavr Clr TBREAK;
								}
								if (error_a Ifset ER_MO)
									if (!(sstaim Ifset OST_O))
									{
										wwtaim Set STOP_TT;
										wcnc Set STOPF;
									}
							}

						}
					/* интерполяция */
					if (_NAX)
						cnciax();
					else
						*cap0 = MASK1;
					if (sscp Ifset RESET_O)   /*  сброс */
					{
						if (wcnc Ifset RESET && msstat Ifset QRESET)
						{
							if (sscp Ifset ST_DISP)
							{
								cnctres();
								sscp Clr RESET_O;
								wcnc Clr(RESET | TRESET);
								msstat Clr QRESET;
								sost = READY_S;
								MODE_CNC Clr BIT5;
								wwtaim Set STOP_TT;
							}
							else
								sost = SBROS_O;
						}
						else
						{
							wcnc Set RESET;
							sost = SBROS_O;
						}
					}
					else
					{
						if (sscp Ifset MEM_P || sscp Ifset MEM_M)
							cnctmm();
						else
						{
							if ((statk Ifset ALARM_N
								|| STOP_P Ifset BIT0
								|| STOP_P Ifset BIT1)
								&& ~sstaim Ifset OST_O)  /* авария  */
								wwtaim Set STOP_TT;
							/* останов по кнопкe или аварии */
							if ((wwtaim Ifset STOP_PR || wwtaim Ifset STOP_TT)
								&& ~statk Ifset P_RESET)
								cnctstp();
							else  /* существует задание после останова */
								if (wwtaim Ifset BEG_O && sstaim Ifset OST_O
									&& ~statk Ifset P_RESET)
									cnctcm();
								else     /* режим останова */
									if (sstaim Ifset OST_O)
										cnctstp();
									else         /* существует задание */

										if (sstaim Ifset BEGIN_O)
											cnctbgn();  /* задано движение */
						}
						if (sstaim Ifset P_EOK
							|| ((sleg ^ ax_on) & _MASKF))
						{
							if ((msstat Ifset EOK
								//	       && sscp Ifset EOKK
								&& ~msstat Ifset WEOK))
								cnctend();
							else
								if (msstat Ifset WEOK)
								{
									wcnc Set STOPF;
									wwtaim Set STOP_TT;
									cnctend();
								}
								else /* существует задание с интерфейса до K\K  */
								{
									if (TEHNOLOG Ifset BIT1 &&
										~STROB_SHOW Ifset BIT0)
									{
										cnctio();
										ik = tzbv;
										_ptask = ykz_byf[tzbv]->task;
									}
								}
						}
						/* разрешение ввода показаний потенциометра */
						if (!(ykz_byf[tzbv]->bnzvk Ifset PP100))
						{
							if (~SPEED_PR Ifset BIT4)
							{
								if (ReqQuKey.changef)
								{
									Fpri = (REAL)FCur / 100.;
									ReqQuKey.changef = 0;
								}
								Fproc = Fpri;
							}
							else
								Fproc = (REAL)(EXT_SPEED);
							/*		 if (~SPEED_PR Ifset BIT6)
									   {
							  Kb.S=0 |1 |2 |3
										 if ((ReqQuKey.changes) && Kb.S))
										   { S1pri=(REAL)S2Cur/100.;
										 ReqQuKey.changes=0;
										   }
										 Sproc[0]=S1pri;
									   }
									 else
										Sproc[0]=(REAL)(EXT_SHP1);
									 if (~SPEED_PR Ifset BIT7)
									   { if ((ReqQuKey.changes) && (Kb.S2) )
										   { S2pri=(REAL)S1Cur/100.;
										 ReqQuKey.changes=0;
										   }
										   Sproc[1]=S2pri;
									   }
									 else
									   Sproc[1]=(REAL)(EXT_SHP2); */
						}
						else
						{
							Fproc = 100.;
							Sproc[0] = Sproc[1] = 100.;
						}
						Sproc[0] = 1;
					}
				}
			}
			wwtaim Clr PR_PR;
			ss_time = 0;
		}
	}
	// asm {
	//	  frstor fbuf		     /* Вос. сост. математич. процессора */
	//	  fwait
	// }
	outportb(0x21, '\0');	     	     /* Разрешение прерывания от клавиатуры */
	geninterrupt(NEWVECTIMER);
} 			/* Конец taim */

void cnctirps(void)

{
	static er_com1 = 0;
	if ((~error_a Ifset MSINT_2)
		&& !(Fh.CerActiv)
		&& (~wcnc Ifset TESTNM))
	{
		sstaim1 Set IO_COM2;
		cnctcom2();
		if (~stat_in Ifset G_DAN)
		{
			switch (tim_rps)
			{
			case 3:
				error_a Set MSINT_2;
				statk Set(ALARM_O | ALARM_N);
			}
			tim_rps++;
		}
		else
			tim_rps = 0;
		sstaim1 Clr IO_COM2;
	}
	if (~error_a Ifset MSINT_1
		&& !(Fh.CerActiv)
		&& ~wcnc Ifset TESTNM)
	{
		sstaim1 Set IO_COM1;
		cnctcom1();
		if (~stat_in Ifset PS_W)
		{
			switch (er_com1)
			{
			case 3:
				error_a Set MSINT_1;
				statk Set(ALARM_O | ALARM_N);
			}
			er_com1++;
		}
		else
			er_com1 = 0;
		sstaim1 Clr IO_COM1;
	}
	timer1 = 0;
}



