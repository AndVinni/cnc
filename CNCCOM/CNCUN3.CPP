#include "cnchard.h"
#include "cncraz.h"
#include "cnccdef.h"
   REAL *nt,      /*���-�� ����筮� �窨 ����*/
	elast[5][NUM],       /*���-��    -//-   -//-  �������⠭��*/
	walk[5][NUM],        /*�����樥��� ���.���௮��樨*/
	differ[NUM],         /*ࠧ���� ���-�*/
	tekv[NUM],
	rad,                 /*ࠤ��� �१� � ������*/
	rsm0[NUM],           /*१������饥 ᬥ饭�� ���*/
	sm0[5][NUM],         /*ᬥ饭�� ��� (��ப�)*/
	f_tz,           /*����� �� G01 � G00 */
	speed,
	c1,c2,/*����-�� �ࠢ����� �����*/
	x1,x2,y1,y2,         /*���-�� �祪 ����祭�� �����-�*/
	hf1,                 /*���� ���४�� �� �����*/
	ntc,
	*xko,
	polar[NUM],          /*����� �� G20*/
	polm[NUM],*pm,       /*����� ��ઠ�쭮� ��ࠡ�⪨*/
	polt[NUM],*pt,       /*����� ������ ���-�*/
	koef[NUM],*kf,       /*����-�� ���.���. � ����⠡��-�*/
	ka1,ka2,kb1,kb2,
	kx,ky,
	rsin,rcos,
	turn,gam,gam1;            /*㣫� ������ � ������� ��אַ�*/
   REAL delta;
   INT	com,
	num_kv,
	ind,
	*gg,*gk,
	acc1[5],acc2[5],acc,    /*�᪮७��*/
	fnomk[5];
   INT  n_ch;
