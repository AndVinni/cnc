
/*  ѕрограммы расчета конечной точки такта
   дл€ :
  круговой интерпол€ции - CNCIRFN();
  линейной интерп.бок.пов.цилиндра -
			  XLINCYL();
	 конической спирали      - XKONUSS();

	 круговой интерп.на бок.пов.цилиндра -
			  XKRUGCYL();
	 винтовой интерпол€ции    - XVINT();
	 нарезание резьбы резцом  - G33();

			  - G99();

*/



#include <cmath.h>
#include <stdio.h>
#include <dos.h>
#include "cncraz.h"
#include "cnchard.h"
#include "cnccdef.h"
#include "cnccstat.h"
#include "cncun1.h"
#include "cnccsti.h"
#include "cncint.h"
#include "cncintb.h"
#include "cncpar.h"


/*кругова€ интерпол€ци€*/

void cncicrfn(void)
{
	LONG x;
	static  LONG  RS;
	INT register  i, j;
	REAL znc,
		zns;
	static REAL  xc;
	REAL
		xsin,
		xcos,
		xs1,
		xs2,
		fi1,
		fi2;
	register BUF_STRUCT* byfv;
	byfv = ykz_byf[ik];
	if ((ptask & MASKI))
	{
		fi = byfv->FI1;
		RS = pow(byfv->RC, 2);
		ftakt = 0; ltorm1 = 0;
	}
	cncieok();
	if ((ktask Ifset MASKI
		ktasks Ifset MASKI)
		&& (!((ax_on & MASKI) ^ MASKI)
			wcnc Ifset TESTNM))
	{
		cncispd();
		if (ltorm1 Ifset MASKI)
			fi = byfv->FI2;
		else
			fi += ftakt * byfv->KF1;
		fi1 = fi;
		fi2 = ABS(fi1);
		while (fi2 > (2. * M_PI))
			fi2 = fi2 - (2. * M_PI);
		if (fi2 == M_PI_2)
		{
			xsin = 1.;
			xcos = 0.;
		}
		else
			if (fi2 == M_PI)
			{
				xcos = -1.;
				xsin = 0.;
			}
			else
				if (fi2 == (M_PI_2 + M_PI))
				{
					xcos = 0.;
					xsin = -1.;
				}
				else
					if (fi2 == (M_PI + M_PI)  fi2 == 0.)
					{
						xcos = 1.;
						xsin = 0.;
					}
					else
					{
						if (fi2 > 0. && fi2 < M_PI_2)
							znc = zns = 1;
						else
							if (fi2 > M_PI_2 && fi2 < M_PI)
							{
								znc = -1;
								zns = 1;
								fi2 = M_PI - fi2;
							}
							else
								if (fi2 > M_PI && fi2 < (M_PI + M_PI_2))
								{
									znc = zns = -1;
									fi2 = fi2 - M_PI;
								}
								else
									if (fi2 > (M_PI + M_PI_2) && fi2 < (M_PI + M_PI))
									{
										znc = 1;
										zns = -1;
										fi2 = M_PI + M_PI - fi2;
									}
						xs1 = ABS(tan(fi2));
						xs2 = 1.ћ(xs1, 2);
						xs2 = ABS(sqrt(xs2));
						if (xs2 != 0)
						{
							xcos = 1. / xs2;
							/*cos(fi);*/
							xsin = xs1 / xs2;
						}
						xcos = (znc == 1) ? xcos : -xcos;
						xsin = (zns == 1) ? xsin : -xsin;
					}
		xc = ((REAL)byfv->RC) * xsin + (REAL)byfv->AC;
		/*cos(fi);*/
		if (xc != 0.)
			xc = (xc > 0.) ? xc + 0.5 : xc - 0.5;
		x = (long)xc;

		if (ltorm1 Ifset MASKI && x != xkadr[xk1])
		{
			xtakt[xk1] = (int)(xkadr[xk1] - xtask[xk1]);
			xtask[xk1] = xkadr[xk1];
		}
		else
		{
			xtakt[xk1] = (int)(x - xtask[xk1]);                  /* */
			xtask[xk1] = x;
		}
		xc = ((REAL)byfv->RC) * xcos + (REAL)byfv->BC;/*sin(fi);*/
		if (xc != 0.)
			xc = (xc > 0.) ? xc + 0.5 : xc - 0.5;
		x = (long)xc;
		if (ltorm1 Ifset MASKI && x != xkadr[xk2])
		{
			xtakt[xk2] = (int)(xkadr[xk2] - xtask[xk2]);
			xtask[xk2] = xkadr[xk2];
		}
		else
		{
			xtakt[xk2] = (int)(x - xtask[xk2]);
			xtask[xk2] = x;
		}
		if (ltorm Ifset MASKI)
		{
			for (j = 0, i = nax[0]; j < nf; j++, i = nax[j])
			{
				if (ABS(fost[i]) < _OKEY[i])
					*okey Set BIT(i);
			}
		}
		else
		{
			if (ABS(fost[xk1]) > _OKEY[xk1])
				*okey Clr BIT(xk1);
			if (ABS(fost[xk2]) > _OKEY[xk2])
				*okey Clr  BIT(xk2);
		}

	}
}
/*линейна€ интерпол€ци€ 2 оси бок.пов.цилиндра*/

void xlincyl(void)
{
	register BUF_STRUCT* byfv;
	byfv = ykz_byf[ik];
	cncieok();
	if (ktask Ifset MASKI)
	{
		cncispd();
		xtakt[xk1] = (int)(ftakt * byfv->klin[xk1]);
		if (ABS(xtakt[xk1]) > ABS(fost[xk1]))
			xtakt[xk1] = (int)fost[xk1];
		xtask[xk1] += xtakt[xk1];

		xtakt[xk2] = (int)(ftakt * byfv->klin[xk2] * _KF2[xk2]);
		if (ABS(xtakt[xk2]) > ABS(fost[xk2]))
			xtakt[xk2] = (int)fost[xk2];
		xtask[xk2] += xtakt[xk2];
	}
}

/*коническа€ спираль*/
void xkonuss(void)
{
	register BUF_STRUCT* byfv;
	byfv = ykz_byf[ik];
	cncieok();
	if (ktask Ifset MASKI)
	{
		cncispd();
		xtakt[xk1] = (int)(ftakt * byfv->klin[xk1]);
		if (ABS(xtakt[xk1]) > ABS(fost[xk1]))
			xtakt[xk1] = (int)fost[xk1];
		xtask[xk1] += xtakt[xk1];

		xtakt[xk2] = (int)(ftakt * byfv->klin[xk2]);
		if (ABS(xtakt[xk2]) > ABS(fost[xk2]))
			xtakt[xk2] = (int)fost[xk2];
		xtask[xk2] += xtakt[xk2];

		xtakt[xk3] = (int)(vtakt[xk3] * byfv->klin[xk3] * _KF2[xk3]);
		if (ABS(xtakt[xk3]) > ABS(fost[xk3]))
			xtakt[xk3] = (int)fost[xk3];
		xtask[xk3] += xtakt[xk3];
	}
}
/*кругова€ интерпол€ци€ на бок. поверхности цилиндра*/

void xkrugcyl(void)
{
	LONG x;
	register BUF_STRUCT* byfv;
	byfv = ykz_byf[ik];
	if (ptask Ifset MASKI)
		fi = byfv->FI1;
	cncieok();
	if (ktask Ifset MASKI)
	{
		cncispd();
		fi += (int)(ftakt * byfv->KF1);
		x = (long)(byfv->RC * cos(fi) + byfv->AC);
		xtakt[xk1] = (int)(x - xtask[xk1]);                  /* */
		if (ABS(xtakt[xk1]) > ABS(fost[xk1]))
			xtakt[xk1] = (int)fost[xk1];
		xtask[xk1] = x;
		x = (long)((byfv->RC * sin(fi) + byfv->BC) * _KF2[xk2]);
		xtakt[xk2] = (int)(x - xtask[xk2]);
		xtask[xk2] = x;
	}
}
/*винтова€ интерпол€ци€*/

void xvint(void)
{
	LONG x;
	register BUF_STRUCT* byfv;
	byfv = ykz_byf[ik];
	cncieok();
	if (ktask Ifset MASKI)
	{
		cncispd();
		if (xdir Ifset AX(xk1))
			xtakt[xk1] = (-ftakt);
		else
			xtakt[xk1] = ftakt;
		if (ABS(xtakt[xk1]) > ABS(fost[xk1]))
			xtakt[xk1] = (int)fost[xk1];
		xtask[xk1] += xtakt[xk1];

		fi += (int)(xtakt[xk1] * _KF2[xk1]);

		x = (long)(byfv->RC * cos(fi)'>AC);
			xtakt[xk2] = (int)(x - xtask[xk2]);                  /* */
		xtask[xk2] = x;

		x = (long)(byfv->RC * sin(fi) + byfv->BC);
		xtakt[xk3] = (int)(x - xtask[xk3]);
		xtask[xk3] = x;
	}
}
/*нарезание резьбы резцом G33*/
void xg33(void)
{
	register BUF_STRUCT* byfv;
	byfv = ykz_byf[ik];
	cncieoks(xk1);
	if (ktask Ifset MASKI)
	{
		cncispds(xk1);
		if (xdir Ifset AX(xk1))
			xtakt[xk1] = (-ftakt);
		else
			xtakt[xk1] = ftakt;
		if (ABS(xtakt[xk1]) > ABS(fost[xk1]))
			xtakt[xk1] = (int)fost[xk1];
		xtask[xk1] += xtakt[xk1];

		xtakt[xk2] = (int)(xtakt[xk1] * byfv->KF3);
		xtask[xk2] += xtakt[xk2];
		if (nf > 2)
		{
			xtakt[xk3] = xtakt[xk2];
			xtask[xk3] += xtakt[xk3];
		}
	}
}

/*нарезание резьбы  G?*/
void xg99(void)
{
	LONG x;
	register BUF_STRUCT* byfv;
	byfv = ykz_byf[ik];
	cncieok();
	if (ktask Ifset MASKI)
	{
		cncispd();
		if (xdir Ifset AX(xk1))
			xtakt[xk1] = -ftakt;
		else
			xtakt[xk1] = ftakt;
		if (ABS(xtakt[xk1]) > ABS(fost[xk1]))
			xtakt[xk1] = (int)fost[xk1];
		xtask[xk1] += xtakt[xk1];

		fi += (int)(xtakt[xk1] * _KF2[xk1]);

		x = (int)(byfv->RC * cos(fi)'>AC);
			xtakt[xk2] = (int)(x - xtask[xk2]);                  /* */
		xtask[xk2] = x;

		x = (int)(byfv->RC * sin(fi)'>BC);
			xtakt[xk3] = (int)(x - xtask[xk3]);
		xtask[xk3] = x;

		xtakt[xk4] = (int)(xtakt[xk1] * byfv->KF3);
		xtask[xk4] += xtakt[xk4];
		if (nf > 4)
		{
			xtakt[xk5] = xtakt[xk4];
			xtask[xk5] += xtakt[xk5];
		}
	}
}
