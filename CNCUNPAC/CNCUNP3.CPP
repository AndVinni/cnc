
/*

		 ╧ЁюуЁрььр яюёыхфэхую яЁюїюфр Ёрёяръютъш

				 CNCUNPAC3()


*/






#define KKR 3
#define ND 99
#include <stdio.h>
#include <string.h>
#include <dir.h>
#include <stdlib.h>
#include "cnchard.h"
#include "cncshow.h"
#include "cncsfh.h"
#include "cncdir.h"
#include "cncraz.h"
#include "cnccdef.h"
#include "cnccstat.h"
#include "cncvoidu.h"
#include "cncvoidi.h"
#include "cncvoidc.h"
#include "cncpar.h"
#include "cncun1.h"
#include "cncun2.h"
#include "cncun3.h"
#include "cnccsti.h"
#include "cncint.h"
#include "cncintb.h"

void cncunp3(void)


{
	INT i_racp,
		i,
		j,
		rr,
		iio;

	static REAL* Tab_kord,//[99][ND],
		* Tab_korh;//[99][ND];
	static INT tab_kor_ds[99],
		tab_kor_hs[99];
	static INT e_point = 0;
	FILE* fd;
	unsigned size_b;
	CHAR  yp1[20],
		c_num[5],
		nmf[20];
	if (sstaim Ifset RR_MAN)
		cncuzcp();
	else
	{
		if (!(sscp Ifset W_EOKV))
		{
			if (~sswbyff Ifset STOP_PRK
				&& ~sscp Ifset EOKV)
			{
				cncuzcp();
				if (!(e_point))
				{
					size_b = 99 * ND;
					if ((Tab_kord = (REAL*)malloc(size_b)) == NULL)
						error(17);
					if ((Tab_korh = (REAL*)malloc(size_b)) == NULL)
						error(17);
					e_point = 1;
				}
				for (i = 0; i < 99; i++)
				{
					tab_kor_ds[i] = tab_kor_hs[i] = 0;
					for (j = 0; j < ND; j++)
						*(Tab_kord + i + j) = *(Tab_korh + i + j) = 0;
				}
			}
			//	       else
			//		  if (nzvk[nomn] Ifset CIKL
			//		      && mir Ifset R_ENT)
			//		    {  cnccrm();
			//		       cnccisvl();	 
			//		    }
			else
				if (sswbyff Ifset STOP_PRK)
				{
					cnccrm();
					if (tzbv <= tzbz)
					{
						if ((tzbz - tzbv) >= KKR)
							sstaim Set WORK_PR;
					}
					else
					{
						if (((KBYF - tzbv) + tzbz) >= KKR)
							sstaim Set WORK_PR;
					}
				}
			if (sstaim Ifset EX_B)
			{
				sstaim Set WORK_PR;
				cncuform();
			}
		}
		sswbyff Clr(STOP_PRK | EX_B);
	}
	sko = skz = is = 0;
	if (sscp Ifset EOKV)
	{
		sscp Clr EOKV;
		ssrasp Clr FIRST_BF;
	}
	while (err[0] == 0 && !(ykz_byf[tzbz]->bnzvk1 Ifset ER_K)
		&& (!(sstaim Ifset OST_O
			|| wwtaim Ifset STOP_TT
			|| wwtaim Ifset STOP_PR))
		&& !(sscp Ifset EOKP)
		&& !(sscp Ifset EOKV))
	{
		if (sswbyff Ifset END_BF)
		{
			if (!(nzvk1[nomn] Ifset END_PR))
				error(102);
			sscp Set EOKP;
			break;
		}
		if (nzvk1[nomn] Ifset END_PR)
		{
			sscp Set EOKP;
			break;
		}
		if (sstaim Ifset RR_MAN)
		{
			nzvk1[nomn] = zvk;
			strk Clr FKK;
			efnstr[nomn] = 0;
			enompb[nomn] = 0;
			Cnc_show();

		}
		else
		{
			Cnc_show();
			cncur_pr(yp);
			if (tab_kor_d != 99 && !(tab_kor_ds[tab_kor_d]))
			{
				yp1[0] = '\0';
				strcpy(yp1, yp);
				itoa(tab_kor_d, c_num, 10);
				strcat(yp1, c_num);
				fnmerge(nmf, "", Config[ED_CNC], yp1, ".rd");
				i = 0;
				if ((fd = fopen(nmf, "r")) == NULL)
					error(18);
				else
				{
					while ((rr = fscanf(fd, "%11lf ", (Tab_kord + tab_kor_d + i))) != EOF)
					{
						if (!(rr))
						{
							error(19);
							break;
						}
						i++;
						if (i > ND)
							break;
					}
					fclose(fd);
				}
				tab_kor_ds[tab_kor_d] = 1;
				fclose(fd);
			}
			if (tab_kor_h != 99 && !(tab_kor_hs[tab_kor_h]))
			{
				yp1[0] = '\0';
				strcpy(yp1, yp);
				itoa(tab_kor_h, c_num, 10);
				strcat(yp1, c_num);
				fnmerge(nmf, "", Config[ED_CNC], yp1, ".rh");
				i = 0;
				if ((fd = fopen(nmf, "r")) == NULL)
					error(18);
				else
				{
					while ((rr = fscanf(fd, "%11lf ", (Tab_korh + tab_kor_h + i))) != EOF)
					{
						if (!(rr))
						{
							error(19);
							break;
						}
						i++;
						if (i > ND)
							break;
					}
					fclose(fd);
				}
				tab_kor_hs[tab_kor_h] = 1;
				fclose(fd);
			}
			if (sswbyff Ifset END_BF)
			{
				error(102);
				break;
			}
			if (sscp Ifset EOKV)
				break;
		}
		if (!(nzvk1[nomn] Ifset NO_WRK))
		{
			if (g[G_CIKL] != MAGC && g[G_CIKL] != 80)
				ssrasp Set W_CIKL;
			else
				if (g[G_CIKL] == 80)
					ssrasp Clr W_CIKL;
			if (x[I_P] != MAG && ~ssrasp Ifset W_CIKL)
			{
				error(115);
				x[I_P] = MAG;
			}
			if (ssrasp Ifset W_CIKL)
			{
				if (g[1] != MAGC)
					error(124);
				nzvk1[nomn] Set EX_CIKL;
			}
			else
			{
				nzvk1[nomn] Clr EX_CIKL;
				ssrasp Clr W_CIKL;
			}
			if (nzvk1[nomn] Ifset CLTAB)
			{
				//	  if (kolc1>KOL_H || kolt1!=0
				//         || value<0)
				//           error(113);
				//	 else
				//	 if (x[I_H]==MAG && x[I_K]==MAG)
				//	   error(125);
				//	 else
				{ if (x[I_H] == MAG)
					tab_kor_h = x[I_H];
				if (x[I_K] == MAG)
					tab_kor_d = x[I_K];
				x[I_H] = MAG;
				x[I_K] = MAG;
				}
			}
			//      if (!(g[GINT]==2 || g[GINT]==3 || g[GINT]==12
			//	  || g[GINT]==13 || g[GINT]==5)
			//	   && x[I_K]!=MAG)
			//	 error(125);
			if (sswbyff Ifset ER_READ && nomn != 4)
				break;
			if (nzvk[nomn] Ifset MDV || vd_vr != 0l)
				strk Clr FKK;	       /*FEOK предыдущего кадра=0*/
			else
				strk Set FKK;
			if (g[22] == 22)
			{
				x[I_H] = MAG;
				x[I_K] = MAG;
			}
			if (x[I_H] != MAG)
			{
				if (x[I_H] != 0)
					hf = *(Tab_korh + tab_kor_h + (INT)(x[I_H]));
				else
					hf = 0;
				strk Set PRH;
				x[I_H] = MAG;
			}
			if (x[I_D] != MAG && g[8] == MAGC && g[9] == MAGC)    /*кор-ция на радиус*/
			{
				if ((gf[8] == 40 && gf[8] == MAGC) && (gf[9] == 140 && gf[9] == MAGC))
					error(22);
				else
				{
					if (gf[8] != 40
						&& gf[8] != MAGC)
					{
						if (x[I_D] != 0)
							rfr = *(Tab_kord + tab_kor_d + (INT)(x[I_D]));
						else
							strk Set OKT;
						if ((g[1] == 2 || g[1] == 12 || g[1] == 3
							|| g[1] == 13 || g[1] == 5
							|| (g[1] != 1 && g[1] != 0
								&& (gf[1] == 2 || gf[1] == 12 || gf[1] == 3
									|| gf[1] == 13 || gf[1] == 5)))
							|| (g[18] == MAGC && gf[18] != 80)
							|| g[18] == 80
							|| (g[18] != MAGC && g[18] != 80))
							error(23);
					}
					else
					{
						i_racp = gf[9] / 100;
						if (i_racp < _NF && i_racp>0)
						{
							if (x[I_D] != 0)
							{
								if ((gf[9] - (i_racp * 100)) == 44)
									kor_d[i_racp] = -*(Tab_kord + tab_kor_d + (INT)(x[I_D]));
								else
									kor_d[i_racp] = 0;
							}
							else
							{
								kor_d[i_racp] = 0;
								gf[9] = 140;
							}
						}
						else
						{
							gf[9] = 140;
							kor_d[i_racp] = 0;
							error(23);
						}
						if ((g[1] == 2 || g[1] == 12 || g[1] == 3
							|| g[1] == 13 || g[1] == 5
							|| (g[1] != 1 && g[1] != 0
								&& (gf[1] == 2 || gf[1] == 12 || gf[1] == 3
									|| gf[1] == 13 || gf[1] == 5)))
							|| (g[18] == MAGC && gf[18] != 80)
							|| g[18] == 80
							|| (g[18] != MAGC && g[18] != 80))
							error(23);
					}
				}
				x[I_D] = MAG;
			}
			x[I_N] = MAG;
			if (g[17] != MAGC)           /*задание подачи в мм/мин или мм/об*/
			{
				gf[17] = g[17];
				if (gf[17] == 94)
					nzvk2[nomn] Set G_94;
				else
					nzvk2[nomn] Clr G_94;
				g[17] = MAGC;
			}
			if (x[I_F] != MAG)         /*значение подачи*/
			{
				f_tz = x[I_F];
				x[I_F] = MAG;
			}
			if (g[16] != MAGC)            /*задание абс.-относит. расчета*/
			{
				gf[16] = g[16];
				g[16] = MAGC;
				if (gf[16] == 90)
					nzvk[nomn] Set PRA;
				else nzvk[nomn] Clr PRA;
			}

			if (g[14] != MAGC)           /*установка подачи на 100% */
			{
				gf[14] = g[14];
				g[14] = MAGC;
				if (gf[14] == 63)
					nzvk[nomn] Set PP100;
				else nzvk[nomn] Clr PP100;
			}
			if (g[23] != MAGC)           /*программирование KV*/
			{
				nzvk[nomn] Clr PKV;
				if (g[23] != 15)
				{
					for (iio = 0; iio < NUM; iio++)
					{
						if (x[iio] != MAG)
						{
							if (x[iio] > (_MIN_KV[iio] * V_TIME)
								&& x[iio] < (_MAX_KV[iio] * V_TIME))
							{
								eprkv Set BIT(iio);
								kv_x[iio] = x[iio] / V_TIME;
								nzvk[nomn] Set PKV;
							}
							else error(25);
							x[iio] = MAG;
						}
					}
					if (~nzvk[nomn] Ifset PKV)
						error(26);
				}
				else
					eprkv = 0;
				gf[23] = g[23];
				g[23] = MAGC;
			}
			if (g[8] != MAGC || g[9] != MAGC)     /*задание коррекции*/
			{
				if (g[8] == 40)
				{
					if (!(x[I_D] == MAG || x[I_D] == 0.))
						error(22);
					strk Set OKT;
					x[I_D] = MAG;
				}
				else
					if (x[I_D] != MAG)
					{
						if (x[I_D] == 0.) error(27);
						else
							rfr = *(Tab_kord + tab_kor_d + (INT)(x[I_D]));
					}
				if (g[9] == 140)
				{
					if (!(x[I_D] == MAG || x[I_D] == 0))
						error(22);
					for (i_racp = 0; i_racp < NUM; i_racp++)
						kor_d[i_racp] = 0;
					strk Set OKT;
					x[I_D] = MAG;
				}
				else
					if (x[I_D] != MAG)
					{
						if (x[I_D] == 0.) error(27);
						i_racp = gf[9] / 100;
						if (i_racp < _NF && i_racp>0)
						{
							if ((gf[9] - (i_racp * 100)) == 44)
								kor_d[i_racp] = -*(Tab_kord + tab_kor_d + (INT)(x[I_D]));
							else
								kor_d[i_racp] = 0;
							gf[9] = 140;
						}
						else
							rfr = *(Tab_kord + tab_kor_d + (INT)(x[I_D]));
					}
				if ((g[8] == 41 || g[8] == 42)
					&& !(gf[8] == 41 || gf[8] == 42))
					mir Set P164;
				if (g[8] != MAGC && g[8] != 40) gf[8] = g[8];
				if (g[9] != MAGC) gf[9] = g[9];
				if (gf[8] == 41)
				{
					nzvk2[nomn] Set G_41;
					nzvk2[nomn] Clr G_42;
				}
				else
				{
					nzvk2[nomn] Set G_42;
					nzvk2[nomn] Clr G_41;
				}
				g[8] = MAGC;
				g[9] = MAGC;
				x[I_D] = MAG;
			}
			if (g[4] != MAGC)                /*задание плоскости расчета*/
				cncugr4();
			if (g[10] != MAGC || g[11] != MAGC || g[12] != MAGC || g[13] != MAGC)
			{        /*задание значений смещения нуля*/
				if (!(g[5] == MAGC || g[5] == 27)
					||
					!(gf[5] == MAGC || gf[5] == 27))
					error(29);
				else
					cnccism0();
				strk Clr FKK;
				g[10] = g[11] = g[12] = g[13] = MAGC;
			}
			if (g[3] != MAGC)              /*программирование разгона*/
			{
				nzvk[nomn] Clr RZG;
				strk Clr FKK;
				if (g[3] == 6)
				{
					for (iio = 0; iio < NUM; iio++)
					{
						if (x[iio] != MAG)
						{
							if (x[iio] > (_MIN_SLOP[iio] * V_TIME) &&
								x[iio] < (_MAX_SLOP[iio] * V_TIME))
							{
								eprdin Set BIT(iio);
								prrazg[iio] = x[iio];
								nzvk[nomn] Set RZG;
							}
							else error(31);
							x[iio] = MAG;
						}
					}
					if (~nzvk[nomn] Ifset RZG)
						error(32);
				}
				else
					eprdin = 0;
				gf[3] = g[3];
				g[3] = MAGC;
			}
			if (g[5] != MAGC)         /*зона обработки*/
			{
				if (g[5] != 27)
				{
					strk Set OZON;
					for (iio = 0; iio < NUM; iio++)
					{
						if (x[iio] != MAG && _MASKF Ifset BIT(iio))
						{
							switch (g[5])
							{
							case 25:
								exl25[iio] = x[iio];
								if (nzvk[nomn] Ifset PRA)
									exl25[iio] += rsm0[iio];
								else
									exl25[iio] += tek[iio];
								ogr25 Set BIT(iio);
								break;
							case 125:
								exr25[iio] = x[iio];
								if (nzvk[nomn] Ifset PRA)
									exr25[iio] += rsm0[iio];
								else
									exr25[iio] += tek[iio];
								ogr25 Set BIT(iio);
								break;
							case 26:
								exl26[iio] = x[iio];
								if (nzvk[nomn] Ifset PRA)
									exl26[iio] += rsm0[iio];
								else
									exl26[iio] += tek[iio];
								ogr26 Set BIT(iio);
								break;
							case 126:
								exr26[iio] = x[iio];
								if (nzvk[nomn] Ifset PRA)
									exr26[iio] += rsm0[iio];
								else
									exr26[iio] += tek[iio];
								ogr26 Set BIT(iio);
							}
							x[iio] = MAG;
						}
					}
				}
				else
				{
					for (iio = 0; iio < NUM; iio++)
					{
						exl25[iio] = _MOPLUS[iio];
						exr25[iio] = _MOMINUS[iio];
						exl26[iio] = 0;
						exr26[iio] = 0;
					}
					ogr25 = 0;
					ogr26 = 0;
					strk Clr OZON;
				}
				gf[5] = g[5];
				g[5] = MAGC;
			}
			else
				if (strk Ifset OZON)
				{
					strk Clr OZON;
					for (iio = 0; iio < NUM; iio++)
						if (exl25[iio] > exr25[iio] ||
							exr26[iio] < exl26[iio])
							error(34);
				}
			if (g[6] != MAGC)            /*замедление на углах*/
			{
				gf[6] = g[6];
				if (g[6] == 29 || g[6] == 129)
				{
					nzvk[nomn] Set YGL;
					if (x[I_K] == MAG)
					{
						if (k_6 == MAG)
						{
							error(36);
							gf[6] = 30;
							nzvk[nomn] Clr YGL;
						}
					}
					else
					{ /* перевести в инкременты */
						k_6 = x[I_K];
						x[I_K] = MAG;
					}
					if (x[I_F] == MAG)
					{
						if (f_6 == MAG)
						{
							error(37);
							gf[6] = 30;
							nzvk[nomn] Clr YGL;
						}
					}
					else
					{
						f_6 = x[I_F];
						x[I_F] = MAG;
					}
				}
				else
					nzvk[nomn] Clr YGL;
				g[6] = MAGC;
			}
			else if (gf[6] == 129)
			{
				gf[6] = 30;
				nzvk[nomn] Clr YGL;
			}
			if (g[24] != MAGC)             /* G09 */
			{
				nzvk[nomn] Set TORM;
				g[24] = MAGC;
			}
			else nzvk[nomn] Clr TORM;
			if (g[25] != MAGC)          /*пауза*/
			{
				if (x[I_P] == MAG)
					error(39);
				else vd_vr = x[I_P];
				gf[25] = g[25];
				g[25] = MAGC;
				x[I_P] = MAG;
			}
			else
			{
				vd_vr = 0.;
				gf[25] = MAGC;
			}
			if (g[15] != MAGC)     /*обход углов*/
			{
				gf[15] = g[15];
				g[15] = MAGC;
			}
			if (g[19] != MAGC)     /* тип отвода в циклах*/
			{
				gf[19] = g[19];
				g[19] = MAGC;
			}
			cncunums();
			/*обработка интерполяции без задания G-функций*/
			for (iio = 0; iio < NUM; iio++)
			{
				if (x[iio] != MAG && _MASKF Ifset BIT(iio))
				{
					if (g[1] == MAGC && g[18] == MAGC && g[2] == MAGC)
					{
						if (gf[18] != 80)
							g[18] = gf[18];
						else
							if (g[1] == MAGC)
								g[1] = gf[1];

					}
					break;
				}
			}
			if (iio > NUM && (g[18] != MAGC || g[1] != MAGC || g[2] != MAGC))
				error(124);
			cncuintf();
		obrc:	if (g[18] != MAGC)    /*обработка циклов*/
		{
			gf[18] = g[18];
			if (f_tz == MAG)
				error(37);
			ef[nomn] = 0;
			strk Clr OOY;
			if (g[18] == 80)
			{
				nzvk[nomn] Clr CIKL;
			}
			else
			{
				switch (g[18])
				{
				case 83:
					gf[18] = g[18];
					break;
				case 75:
				case 84:
				case 76:
				case 81:
				case 82:
				case 85:
				case 86:
				case 87:
				case 88:
				case 89:   cnccisvl();
					break;
				}
			}
		}
		else
			obri:	if (g[1] != MAGC)     /*обработка интерполяции*/
		{
			gf[1] = g[1];
			switch (g[1])
			{
			case 0:
			case 1:
				Cnc_show();
				nzvk[nomn] Clr PRK;
				cnccilnr();
				gf[1] = g[1];
				break;
			case 10:
			case 11: cnccipol();
				cnccilnr();
				gf[1] = g[1];
				break;
			case 2:
			case 3:   nzvk[nomn] Clr PRK;
				gf[1] = g[1];
				cnccikrg();
				gf[1] = g[1];
				break;
			case 12:
			case 13: cnccipol();
				cnccikrg();
				gf[1] = g[1];
				break;
			case 5:  nzvk[nomn] Clr PRK;
				if (nomn == nomf)
				{
					error(46);
					break;
				}
				else
					cnccikrg();
				gf[1] = g[1];
				break;
			case 92:  nzvk[nomn] Clr PRK;
				cncuzsm();
				break;
			case  28:
			case 128:
			case 228:
			case 328:  nzvk[nomn] Clr PRK;
				cncufiks();
			}
		}
			else
			if (g[2] != MAGC)
			{
				if (g[2] == 31)
					mir Set P165;
				if (g[2] == 32)
					mir Set P166;
				if (g[2] == 31 || g[2] == 32)
					cncugekv();
				gf[2] = g[2];
				g[2] = MAGC;
			}
		if (nzvk1[nomn] Ifset END_PR)
		{
			if (gf[8] != 40)
				strk Set OKT;
			/* M05 !!! */
		}
		cncuform();
		Cnc_show();
		if (sstaim Ifset RR_MAN)
		{
			ykz_byf[tzbz]->bnzvk Set TORM;
			break;
		}

		}
	}
	if (((sstaim Ifset OST_O
		|| wwtaim Ifset STOP_PR || wwtaim Ifset STOP_TT)
		&& !(sswbyff Ifset STOP_PRK) && prr != MANUAL
		&& err[0] == 0 && !(ykz_byf[tzbz]->bnzvk1 Ifset END_PR))
		|| (sscp Ifset EOKV && ~sswbyff Ifset STOP_PRK))
	{
		cnccrm();
		sswbyff Set STOP_PRK;
	}
	if (err[0] != 0)
		ykz_byf[tzbz]->bnzvk1 Set ER_K;
	if (n_vk == 0l)
	{
		if (!(sstaim Ifset OST_O ||
			wwtaim Ifset STOP_PR || wwtaim Ifset STOP_TT))
			sstaim Set WORK_PR;
	}
	else
	{
		if (!(sscp Ifset EOKV))
		{
			error_a Set PROG_2;
			statk Set ALARM_O;
			wwtaim Set STOP_TT;
			sstaim Clr(ZAP_PRK | ZAP_PR | BEGIN_O);
			sscp Clr W_EOKV;
			error(47);
		}
	}
}

