/*


		Программа второго прохода распаковки

				CNCUNPAC2()

*/




#include <string.h>
#include <stdio.h>
#include <dir.h>
#include "cnchard.h"
#include "cncshow.h"
#include "cncdir.h"
#include "cncraz.h"
#include "cnccdef.h"
#include "cnccstat.h"
#include "cnccsti.h"
#include "cncint.h"
#include "cncvoidu.h"
#include "cncun1.h"
#include "cncun2.h"


void cncunp2(void)


{
	INT iio,
		i_i1,
		i_i2,
		rab_po,
		flz = 0,
		dop;
	CHAR nmf[20],
		nmpp[20];
	static LONG ykz_pp = 0;
	for (iio = 0; iio < KO; iio++)
		x[iio] = MAG;
	for (iio = 0; iio < KM; iio++)
		m1[iio] = m2[iio] = MAGB;
	for (iio = 0; iio < KG; iio++)
		g[iio] = MAGC;
	for (iio = 0; iio < ER; iio++)
		pro[iio] = pros[iio] = 0;
	io = ib = ibfp = ibfp1 = noms1 = nomst = n_beg = lwp = noms = 0;
	ssrasp = ssprr = 0;
	tab_kor_d = tab_kor_hЩ;
	var_x = 0l;
	fnmerge(nmf, "", Config[ED_SYS], FO_YP, F_ERR);
	if ((fo = fopen(nmf, "w")) == NULL)
		erpac(1, 0);
	if (~sstaim Ifset RR_MAN)
	{
		fnmerge(nmf, "", Config[ED_CNC], yp, PROG_EXT);
		if ((fp = fopen(nmf, "r")) == NULL)
			erpac(86, 0);
		fnmerge(nmf, "", Config[ED_CNC], yp, F_NUM);
		if ((ftt = fopen(nmf, "w")) == NULL)
		{
			erpac(50, 0);
			ssrasp Set WAR_IO;
		}
		fnmerge(nmf, "", Config[ED_CNC], yp, F_WRK);
		if ((fpp = fopen(nmf, "w")) == NULL)
		{
			erpac(3, 0);
			ssrasp Set WAR_IO;
		}
		else
		{
			if (fprintf(fpp, "", 1) == EOF)
			{
				erpac(53, 0);
				ssrasp Set WAR_IO;
			}
		}
		name_pp[0] = '\0';
		fnmerge(name_pp, "", Config[ED_CNC], yp, NMP);
		if ((fpi = fopen(name_pp, "w")) == NULL)
			erpac(63, 0);
		fclose(fpi);
	}
	fnmerge(nmf, "", Config[ED_CNC], TAB_KG, TABKS_EXT);
	if ((fmg = fopen(nmf, "r")) == NULL)
		erpac(6, 0);
	fnmerge(nmf, "", Config[ED_CNC], TAB_GS, TABKS_EXT);
	if ((fgs = fopen(nmf, "r")) == NULL)
		erpac(82, 0);
	fnmerge(nmf, "", Config[ED_CNC], TAB_FMS, TABKS_EXT);
	if ((fmf = fopen(nmf, "r")) == NULL)
		erpac(66, 0);
	for (i_i1 = 0; i_i1 < KGF; i_i1++)
	{
		for (i_i2 = 0; i_i2 < 4; i_i2++)
		{
			if ((rab_po = fscanf(fmg, "d", (mg[i_i1] + i_i2))) == 0)
			{
				erpac(65, 0);
				mg[i_i1][0] = MAGC;
				break;
			}
			if (rab_po == EOF)
			{
				mg[i_i1][0] = MAGC;
				break;
			}
		}
		if (mg[i_i1][0] == MAGC) break;
	}
	//	    for (i_i1=0;i_i1<_NAX;i_i1++)
	//		 mr[i_i1][1]=_AXF[i_i1];
	for (i_i1 = 0; i_i1 < KGS; i_i1++)
	{
		for (i_i2 = 0; i_i2 < KS; i_i2++)
		{
			if ((rab_po = fscanf(fgs, "d", &dop)) == 0)
			{
				erpac(68, 0);
				gs[i_i1][i_i2] = MAGC;
				break;
			}
			if (rab_po == EOF)
			{
				gs[i_i1][i_i2] = MAGC;
				break;
			}
			gs[i_i1][i_i2] = dop;
		}
		if (gs[i_i1][i_i2] == MAGC) break;
	}
	for (i_i1 = 0; i_i1 < KM_DV; i_i1++)
	{
		if ((rab_po = fscanf(fmf, "%d %d ", &mf1[i_i1], &mf2[i_i1])) == 0)
		{
			erpac(70, 0);
			mf1[i_i1] = mf2[i_i1] = MAGB;
			break;
		}
		if (rab_po == EOF)
		{
			mf1[i_i1] = mf2[i_i1] = MAGB;
			break;
		}
	}
	if (!(io))
	{
		do
		{
			if ((sstaim Ifset OST_O)
				(wwtaim Ifset STOP_TT)
				(wwtaim Ifset STOP_PR))
			{
				erpac(73, 0);
				break;
			}
			Cnc_show();
			ssprr = 0;
			zvk = 0;
			nom_simv = 0;
			prz_nam = 1;
			name_fo[0] = '\0';
			if (!(ibfp))
				strcpy(name_fo, yp);
			else
				strcpy(name_fo, nmpp);
			noms = 0;
			cncuasim();
			Cnc_show();
			if (io)
				cncuwerr();
			else
				if (ssprr Ifset GOTO_W)
				{
					fclose(fpp);
					fclose(ftt);
					if (!(ibfp))
						cncufgo(yp);
					else
						cncufgo(nmpp);
				}
			if ((io))
				cncuwerr();
			Cnc_show();
			fclose(fpp);
			fclose(fp);
			fclose(fpi);
			fclose(ftt);
			if (!(sstaim Ifset RR_MAN))
			{
				fnmerge(nmf, "", Config[ED_CNC], yp, F_NUM);
				if ((ftt = fopen(nmf, "a")) == NULL)
				{
					erpac(50, 0);
					cncuwerr();
				}
				for (iio = 0; iio < KO; iio++)
					x[iio] = MAG;
				for (iio = 0; iio < KM; iio++)
					m1[iio] = m2[iio] = MAGB;
				for (iio = 0; iio < KG; iio++)
					g[iio] = MAGC;
				for (iio = 0; iio < ER; iio++)
					pro[iio] = pros[iio] = 0;
				io = 0;
				if ((fpi = fopen(name_pp, "r")) == NULL)
					ibfp = 0;
				else
				{
					if ((ibfp))
						fseek(fpi, ykz_pp, 0);
					flz = 1;
					while ((flz))
					{
						if ((fscanf(fpi, "%s", nmpp)) == EOF)
						{
							ibfp = 0;
							flz = 0;
							break;

						}
						ibfp = 1;
						flz = 0;
						ykz_pp = ftell(fpi);
						nmf[0] = '\0';
						fnmerge(nmf, "", Config[ED_CNC], nmpp, PROG_EXT);
						if ((fp = fopen(nmf, "r")) == NULL)
						{
							erpac(90, 0);
							ibfp = 0;
							break;
						}
						nmf[0] = '\0';
						fnmerge(nmf, "", Config[ED_CNC], nmpp, F_WRK);
						if ((fpp = fopen(nmf, "w")) == NULL)
						{
							ibfp = 0;
							erpac(91, 0);
							break;
						}
					}
				}
			}
			fclose(fpi);
			if ((io))
				cncuwerr();
		} while ((ibfp));
	}
V_KON:
	if ((io))
		cncuwerr();
	fclose(fp);
	fclose(fpp);
	fclose(fmf);
	fclose(fmg);
	fclose(fgs);
	fclose(ftt);
	fclose(fpi);
	if (~ssrasp Ifset ALARM_R
		&& ~ssrasp Ifset WAR_IO
		&& ~sstaim Ifset RR_MAN)
	{
		fnmerge(nmf, "", Config[ED_CNC], yp, F_WRK);
		if ((fpp = fopen(nmf, "r+")) == NULL)
		{
			erpac(3, 0);
			ssrasp Set WAR_IO;
			cncuwerr();
		}
		else
			if (fprintf(fpp, "", 0) == EOF)
			{
				ssrasp Set WAR_IO;
				erpac(53, 0);
				cncuwerr();
			}
	}
	fclose(fpp);
	fclose(fo);
	fclose(fpi);


}


void cncufgo(CHAR* name_yp)
{
	CHAR nmf[60];
	INT rab_po;
	fnmerge(nmf, "", Config[ED_CNC], yp, F_NUM);
	if ((ftt = fopen(nmf, "r")) == NULL)
		erpac(50, 0);
	fnmerge(nmf, "", Config[ED_CNC], name_yp, F_WRK);
	if ((fpp = fopen(nmf, "r")) == NULL)
		erpac(3, 0);
	if (!(io))
	{
		ssprr Set W_GOTO;
		if (!(ibfp))
		{
			if ((rab_po = fscanf(fpp, "", &prz_nam)) == EOF)
				ssprr Clr W_GOTO;
			else
				if (rab_po == 0)
					erpac(51, 0);
		}
		if (!(io) && ssprr Ifset W_GOTO)
		{
			lwp = 0;
			ppp[lwp] = fpp;
			cncur_pr(name_yp);
		}
		if (sswbyff Ifset ER_READ)
			erpac(3, 0);
	}
	ssprr Clr(W_GOTO  GOTO_W);
}
