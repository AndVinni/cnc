#include "cnchard.h"
#include "cncraz.h"
#include "cnccdef.h"
#include "cnccstat.h"
   WORD	   nzvk[5],		 /*᫮�� ��ﭨ� ��.����*/
	   nzvk1[5],	         /* ᫮�� ���.��.���� ��᫥ 2-�� ��.*/ 
	   nzvk2[5],
	   nzvk3[5],
	   zvk=0,
	   ssw_sh=0,
	   stat_ea,		/* ᫮�� ���ﭨ� �� */
	   stat_sc=0,
	   error_a=0,		/* ᫮�� ���ﭨ� ���਩ */
	   error_1=0,
	   stat_in,
	   statk=0,		/*᫮�� ���ﭨ� ������ PCNC*/
	   statk1=0,
	   sscp=0,		/*᫮�� ���ﭨ� ��*/
	   sstaim=0,		/* ᫮�� ���ﭨ� ⠩��� */
	   sstaim1=0,
	   wwtaim=0,		/* ᫮�� ������� ��� ⠩��� */
	   wwtaims=0,		/* ��� ������� */
	   strk=0, 		/*SSP �� �ᯠ����� ����*/
	   ssrasp=0,		/* 2-�� ᫮�� ���.��-�� �ᯠ����� */
	   sswbyff=0,		/* ���ﭨ� ���� �ᯠ����� */
	   sp_chan[NUMS];	/* ���ﭨ� �-�㭪権 诨����� */
   BYTE    inform;
   Prr     prr=MANUAL;          /* ०��� ࠡ��� �⠭�� */
   Sost	   sost=OSTANOV,	            /* ���ﭨ� �⠭�� */
	   sost1=OSTANOV;
   INT     tzbv,		/*������ ���. ����� ����*/
	   tzbv1,		/* ������ ���. ��� ��室� �� �������⠭��*/
	   z_tzbv,		/* ������ ��⠭��� */
	   z_tzbr,
	   tzbv_z,
	   v_tzbv,
	   tzbv_r,
	   tzbr,
	   tzbz,                /*������ ������塞�� ����� ����*/
	   find_vk,
	   task_vk;
     LONG  z_kop[NUM],		/* ������ ��⠭��� */
	   tek_o[NUM],		/* ���न��� �।���.���� �⢮�� */ 
	   ztekos[NUM],		/* ������ tek_os �� ��⠭��� */	
	   tek_os[NUM],          /* �⢮� */
	   tek_vk[NUM];		/* ��x�� � ���� */
    REAL  tek[NUM],		/* ���न���� ����筮� �窨*/
	   f_6,
	   k_6;
      INT  st_s[NUMS],		/*����� ⥪�饩 ��㯥�� 1-�� �.*/
	   st_ds[NUMS];
    union  uu1 uu2;
    union  SSP SUP;
    union  SSN SUN;
    WORD   DataRPS=0,
	   DatCOM1=0;
    INT    tim_rps=0,  	/*   ⠩��� COM2 */
	   tim_com1=0;		/* ⠩��� COM1 */
    INT   timer,              /* ���稪 ⠩����� ���뢠��� */
	  timer1;  	   /* ����-�뢮� */	
    DWORD  i_time=0;	      /* �६� */	
    INT   par,
	  imf,
	  tm[KT],
	  tmp[KT],
	  ts[KT];
    INT   I_ER;         /* ������ ���ᨢ� �訡�� ��� ������樨  */
    CHAR  name_p[60];
    LONG ykz_beg; 







