/*  	cncpar.h v01.01

	��।������ ᨬ�����᪨� ���� ��ࠬ��஢ �⠭��

	�஥��:    CNC++.

	Copyright (c) ELMIS, 1993
	�� �ࠢ� ���饭�.
*/

#if !defined(__CNCPAR_H)
 #define __CNCPAR_H

 #if !defined(__CNCRAZ_H)
  #include "cncRaz.h"
 #endif

 #if !defined(__CNCPARD_H)
  #include "cncPard.h"
 #endif



/*  		� � � � � � � �   � � � � � � � � �

		       �100 ��������� ����
*/

#define _AXADR    Par.AxAdr	 /*Q100 ���� �ᥩ*/
#define _ADRMUP   Par.AdrMup	 /*Q110 ���� ����� */
#define _NO       Par.LogToPhith /*Q120 �����᪠� ��� -->  䨧��᪠� */
#define _AXF      Par.AxForm	 /*Q130 �ଠ� ��,ࠧ��� ��᫥ ����⮩*/
#define _AXTYPE   Par.AxType 	 /*Q140 ⨯ ��:���./���./��᪮���./诨�����*/
#define _AXSYN    Par.AxSyn	 /*Q145 ⨯ �� ᨭ�஭���/�ᨭ�஭���*/
#define _AXMOD    Par.AxModul	 /*Q150 ����� �� */
#define _STEPD    Par.StepDiscr  /*Q160 蠣 ����⭮� �� */
#define _AXPARAL  Par.Paral	 /*Q? ����� ����饩 ��(��� ��ࠫ.�ᥩ)*/
#define _NIMP     Par.NumImp	 /*Q170 ࠧ�. ᯮᮡ����� ���.��⥬�*/
#define _MSIMP    Par.MSimp	 /*Q180 ������⢮ �����ᮢ �� ���६���*/
#define _INDAX    Par.IndAx	 /*Q190 �ਧ��� ������樨 ��*/
#define _INDAXD   Par.IndAxD	 /*Q200 ��᪠ �ᥩ ��ᢥ�. �������᪨*/
#define _LKRUG    Par.CircleLog  /*Q210 ������ ���᪠ ��� ��㣮��� �ᥩ*/
#define _MSBLOK   Par.MSblock    /*Q220 �����஢�� �����.��⥬�       */
#define _BLSLEG   Par.BlockSleg  /*Q225 �����஢�� ᫥����� */
#define _MSDIR    Par.MSdir	 /*Q230 ���ࠢ����� �����.��⥬�      */
#define _POLAR    Par.Polar	 /*Q240 ����୮��� ���                 */
#define _DREIF    Par.Dreif	 /*Q250 ��������� �३�                */
#define _NPOZ     Par.Npoz	 /*������⢮ ����権 �� � ��६. 蠣��*/
#define _AXDISKRP Par.AxDiscr	 /*����� �ᥩ � ��६���� 蠣��*/
#define _NF       Par.NF	 /*�᫮ �ମ��ࠧ���� �ᥩ    */
#define _NP       Par.NP	 /*�᫮ ����樮���� �ᥩ        */
#define _NS       Par.NS	 /*�᫮ 诨������               */
#define _NAX      Par.NAX	 /*��饥 ���-�� �ᥩ             */
#define _NAXM     Par.NAXM	 /*���-�� �᭮���� �ᥩ(��� 诨������)*/
#define _exp      Par.exp	 /*��ନ���騩 �����⥫�*/
#define _MASKF    Par.maskF	 /*��᪠ �ମ��ࠧ����*/
#define _MASKP    Par.maskP	 /*��᪠ ����樮����*/
#define _MASKS    Par.maskS	 /*��᪠ 诨������*/
#define _AXSTEP   Par.AxStep	 /**/
#define _AXDISKR  Par.Ax_Diskr	 /**/
#define _MASKR    Par.maskR	 /*��᪠ ��㣮���*/
#define _MASKE    Par.maskE	 /**/
#define _KF2      Par.KF2	 /**/
#define _IS       Par.IS	 /* ����饭�� ������ 诨�����*/
#define _ISC      Par.ISC	 /* ����饭�� ������ 诨�����(�� )*/
#define _KMUP     Par.kMup	 /* ॠ�쭮� ������⢮ ����� */

			 /* P500 �������� */

#define _KCAP     Par.MaxFeed  	 /*Q500 ���ᨬ��쭠� ����� */
#define _VG00     Par.VG00	 /*Q510 �᪮७�� 室*/
#define _VNUL     Par.Vnull	 /*Q520 ᪮���� ��室� � ����*/
#define _VSNIG    Par.Vsing      /*Q530 ���������� ᪮����*/
#define _VNKUL    Par.VNkul	 /*Q540 ᪮���� �� �㫥��� �㫠窥*/
#define _HANDF1   Par.HandF1	 /*Q550 ����. ��筠� �����   */
#define _HANDF2   Par.HandF2     /*Q560 �।�.��筠� �����   */
#define _HANDF3   Par.HandF3     /*Q570 �����.��筠� �����  */
#define _HANDG00  Par.HandG00    /*Q580 G00 ��筠� �����   */
#define _MAXWORKF Par.MaxWorkF   /*Q590 ���ᨬ��쭠� ����� �ࠥ��ਨ */
#define _RASSV    Par.AvRas	 /*Q600 ���਩��� ��ᮣ��ᮢ���� �� ᪮���*/
#define _TIMERASSV Par.TimeAvRas /*Q610 �६� �� ���������� ���. �� ᪮���*/
#define _ALIMIT   Par.Alimit     /*Q620 �।��쭮 �����⨬�� �᪮७��*/
#define _VLIMIT   Par.Vlimit     /*Q630 �।��쭮 �����⨬�� ᪮����*/

		     /*Q1000 �������� ����*/

#define _KV       Par.KV	  /*Q1000 �����.�ᨫ����*/
#define _KVOKEY   Par.KVokey      /*Q1010 �����.�ᨫ���� � ���� OKEY*/
#define _A        Par.A		  /*Q1020 �᪮७�� � ��ࢮ� ����*/
#define _VRAZG    Par.Vrazgon	  /*Q1030 ᪮���� ��㯥�쪨 �� ࠧ����*/
#define _VTORM    Par.Vtorm	  /*Q1040 ᪮���� ��㯥�쪨 �� �ମ�����*/
#define _ACOMM    Par.Acomm	  /*Q1050 ������樮���� �᪮७��*/
#define _VCOMM    Par.Vcomm	  /*Q1060 ������樮���� �窠*/
#define _PEREHODF Par.perehodF	  /*Q1070 ���室��� ᯫ�ᮡ����� �ᥩ*/
#define _MIN_SLOP Par.MinSlop     /*Q1080 �������쭮 �ணࠬ���. �᪮७��*/
#define _MAX_SLOP Par.MaxSlop     /*Q1090 ���ᨬ��쭮 �ணࠬ�. �᪮७��*/
#define _MIN_KV   Par.MinKV	  /*Q1100 �������쭮 �ணࠬ�. KV*/
#define _MAX_KV   Par.MaxKV	  /*Q1110 ���ᨬ��쭮 �ணࠬ�. KV*/
#define _KDIN     Par.Kdinam	  /*�������᪨� �����樥��*/
#define _KDINC    Par.KdinamC	  /*������樮��� �����樥��*/
#define _STORM    Par.Stormoz     /*���� �ମ����� � 1 ����*/
#define _MOPLUSX  Par.MOplusX	  /**/
#define _MOMINUSX Par.MOninusX    /**/

		      /* P1500 ������� */

#define _XNUL     Par.Xnull   	  /*Q1500 ���஢�� ��� */
#define _SNUL     Par.Snull   	  /*Q1510 ᬥ饭�� ���   */
#define _BLOKMO   Par.blockMO	  /*Q1520 �����஢�� ���.��࠭�祭�� */
#define _MOPLUS   Par.MOplus      /*Q1530 ���.��࠭�祭�� ���� */
#define _MOMINUS  Par.MOminus     /*Q1540 ���.��࠭�祭�� ����� */
#define _MOPL     Par.MO_plus	  /*? ���.��࠭�祭�� ���� */
#define _MOMN     Par.MO_minus    /*? ���.��࠭�祭�� ����� */
#define _OKEY     Par.O_key	  /*Q1550 ����"OKEY"     */
#define _RASS     Par.AvRasP	  /*Q1560 ���਩��� ��ᮣ��ᮢ���� �� */
#define _TIMERASS Par.TimeAvRasP  /*Q1570 �६� �� ���������� ���. �� */
#define _IFG(i)   Par.IFG[(i)]	  /*Q1580-P1620 ᬥ饭�� ���(5)*/

		  /* P2000 ��������� */

#define _LUFT     Par.Luft   	  /*Q2000 ����稭� ����*/
#define _AXCORR   Par.AxCorr	  /*Q2010 ����� ��*/
#define _TCORR    Par.Tcorr	  /*Q2020 ��ਮ� ���४樨*/
#define _STEP     Par.Step	  /*Q2030 蠣 ���४樨*/
#define _X0       Par.X0	  /*Q2040 ���न��� ��砫쭮� �窨*/
#define _NCOR     Par.Ncorr       /*Q2050 ������⢮ �祪 ���४樨*/
#define _DCOR	  Par.Corr	  /*Q2060 ���祭�� ���४樨 */

		/* P2500 ������������� */

#define MINFP     0                /* �������쭮 �����⨬� ��業� �����*/
#define MAXFP     140              /* ���ᨬ��쭮 �����⨬� ��業� �����*/
#define MINS      40               /* �������쭮 �����⨬� ��業� ����⮢ 诨�����*/
#define MAXS      180              /* ���ᨬ��쭮 �����⨬� ��業� ����⮢ 诨�����*/

#define _CONTAL   Par.ContAl	   /*Q2500 �ᯮ������� �࣠��� �ࠢ����� */
#define _MINF     Par.MinF         /*Q2510 ��������� ��業� �����*/
#define _MAXF     Par.MaxF         /*Q2510 ���ᨬ���� ��業� �����*/
#define _MINS     Par.MinS         /*Q2520 ��������� ��業� ����⮢ 诨�����*/
#define _MAXS     Par.MaxS         /*Q2520 ���ᨬ���� ��業� ����⮢ 诨�����*/
#define _BIGSTEP  Par.BigStep      /*Q2530 蠣 ����ண� ��������� ��業⮢*/
#define _LITLSTEP Par.LitlStep     /*Q2540 蠣 ����.��������� ��業⮢*/



	       /* P3000 ��������������� ������� */

#define _GRM      Par.GroupM	  /*Q3000 ������⢮ ��㯯 �-�㭪権*/
#define _GRT      Par.GroupT	  /*Q3000 ������⢮ ��㯯 �-�㭪権*/
#define _VVOSTM   Par.MVost	  /*Q3010 M-�㭪樨 � V-��⠭����*/

		/* P3500 ��१�ࢨ஢��� */

	       /* P4000 ��������� ���������� */

#define _P_NOMP	  Par.NamePG	  /*Q4000 �ணࠬ�� G, ���. ���짮��⥫��*/
#define _P_NOMG	  Par.NameFG	  /*Q4010 �㭪樨 G, ���.���짮��⥫��*/
#define _P_NOMMP  Par.NamePM      /*Q4020 �ணࠬ�� �,��।.���짮��⥫��*/
#define _P_NOMM	  Par.NameFM      /*Q4030 �㭪樨 �,���.���짮��⥫��*/
#define _P_BAZ	  Par.G90_G91     /*Q4050 ���ﭨ� ����祭�� G90/91 */
#define _P_YGL	  Par.G68_G69     /*Q4060 ���ﭨ� ����祭�� G68/69 */
#define _P_TABL	  Par.TablKs      /*Q4070 ���ﭨ� ����祭�� G145/G146*/
#define _NOTVOD   Par.Notvod      /*Q4080 ���ࠢ����� �⢮�� � ����. 横���*/
#define _KGF      Par.KgF	  /* ������⢮ �㭪樨 G, ���.���짮��⥫��*/
#define _KMF      Par.KmF         /* ������⢮ �㭪樨 M, ���.���짮��⥫��*/


		/* �4500 ��������� ��������� */

#define _NPLC 	  Par.nPLC 	  /* Q4500 ���� �裡 � PLC */
#define _NDRC 	  Par.nDRC	  /* Q4510 ���� �裡 � DRC */
#define _NDNC 	  Par.nDNC	  /* Q4520 ���� �裡 � DNC */
#define _PDNC 	  Par.pDNC	  /* Q4520 ��ࠬ���� �裡 � DNC */
#define _NPRF 	  Par.nPRF	  /* Q4530 ���� �裡 � �����⠭樥� */
#define _PPRF 	  Par.pPRF	  /* Q4530 ��ࠬ���� �裡 � �����⠭樥� */
#define _NPRN 	  Par.nPRN	  /* Q4540 ���� �裡 � �ਭ�஬*/

	  /*Q5000 ����������� �������� �����������  */

#define _AXSW     Par.AxSw    	  /*Q5000 ����� ��*/
#define _MINSW    Par.MinSw       /*Q5000 ����� �࠭��*/
#define _MAXSW    Par.MaxSw       /*Q5000 �ࠢ�� �࠭��*/
#define _IFP      Par.IFP         /*Q5020-P5180 ���न���� 䨪�. �祪*/

		  /*Q6000 ��������� �������� */

#define _SHADR    Par.ShAdr	  /*Q6000 ���� 诨����� */
#define _OSSH     Par.OsSh	  /*Q6005 ����稥 ���⭮� �裡 */
#define _SLIMIT   Par.Slimit      /*Q6010 ������ �� ������ ���몠-
				    ���� ������ ॣ-��� ��������� */
#define _SNSTUP   Par.Nstup       /*Q6020 ������⢮ ��㯥��� */
#define _SMINSTUP Par.MinStup     /*Q6030 min ������ �� ��㯥��*/
#define _SMAXSTUP Par.MaxStup     /*Q6040 max ����. �� ���.��� ��४�.*/
#define _SORIENT  Par.Orient      /*Q6050 ᪮���� �ਥ��樨*/
#define _SPOLM3   Par.PolarM3     /*Q6070 ����୮��� ��⠢�� ��� �3*/
#define _SPOLM4   Par.PolarM4     /*Q6080 ����୮��� ��⠢�� ��� �4*/
#define _SPEREKL  Par.Sperekl     /*Q6090 ᪮���� ��४��祭�� ��㯥���*/
#define _SAMPL    Par.Sampl       /*Q6100 ������㤠 ����������� �᫠ ����⮢ */
#define _STEMP    Par.Stemp       /*Q6110 ���� -----------------------------*/
#define _SOKEY    Par.Sokey       /*Q6120 ���� "OKEY"    */
#define _MORI     Par.Morient     /*Q6130 ��� M-�㭪樨 ��� �ਥ��樨     */
#define _SKV      Par.SKV	  /*Q6140 �����.�ᨫ���� */
#define _SARAZG   Par.Srazgon     /*Q6150 ����ﭭ�� ࠧ����-�ମ�����*/
#define _SLUFT    Par.Sluft	  /*Q6160 ����*/
#define _SNZNF    Par.SNZNF       /*Q6170 ����.�⪫������ �᫠ ����⮢*/
#define _SKVSTOP  Par.SKVstop     /*Q6180 KV �� ��⠭����*/
#define _SSKV     Par.SSKV        /*Q6190 ���祭�� ����⮢ ��� �6180*/
#define _SNMIN    Par.SNmin       /*Q6200 ������ ���  N=0*/
#define _MFS      Par.MFS	  /*Q6210 ��� M-�㭪樨 ��� ��४�.��㯥��� */
#define _STOLCHOK Par.Stolchok    /*Q6220 ⮫窮��� ᪮���� */
#define _MOST     Par.Most        /*Q6230 ��� �-�㭪樨 ��� ��⠭��� 诨�����*/
#define _MLEFT    Par.Mleft       /*Q6240 ��� �-�㭪樨 ��� ������ ��饭��*/
#define _MRIGHT   Par.Mright      /*Q6250 ��� �-�㭪樨 ��� �ࠢ��� ��饭��*/
#define _SKDIN    Par.SKdin       /* �������᪨� �����樥��*/
#define _SA       Par.SA	  /* �������᪨� �����樥��*/
#define _SVLIMIT  Par.SVlimit	  /* */
#define _SDREIF   Par.Sdreif      /* P? �३� 設���� */
#define _SKCAP    Par.SKcap	  /* �����. ������ ���    */
#define _SKCAPA   Par.SKcapa      /* �����. ������ ���    */

	     /*Q6500 ���������    DNC   */

#define _ADRCNC     Par.adrCNC       /*Q6500 ���� CNC*/

		 /*Q7000 ��������� CNC*/

#define _TESTER     Par.TestEr      /*Q7000 ������ ᨣ���� ������.���稪�*/

enum			// ���� �ᥩ
{
 atNoType,
 atLine,
 atClosedRound,
 atRound,
 atShpindel
};

enum			// ����஫� ���稪� Renishow
{
 rcNotControl,
 rcFlip,
 rcFlop,
 rcFlipFlop
};

extern  BYTE date;
extern  BYTE bitmap[125];

extern INT nstrpar,nword,e,xint1,c;

union rpar_v
  {
  INT date1;
  BYTE date_c[2];
  };

union sum_v
  {
  WORD s_par;
  BYTE par_c[2];
  };

union scom_v
  {
  WORD xsum;
  BYTE xsum_c[2];
  };

extern union scom_v scom;
extern union sum_v sum;
extern INT dop_ykz[KPARAM];
extern union rpar_v rpar;
extern BYTE *adr_b;
extern INT  ind_b,
	   ind_b1;
union namex
	   {   WORD inam[8];
	       CHAR nameos[8][2];
	    } ;
extern union namex namex1;
extern union sumo_v sumo;
union sumo_v
     { WORD i_sum;
       BYTE c_sum[2];
     };

#endif
