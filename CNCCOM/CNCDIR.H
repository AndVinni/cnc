/*  	cncdir.h v01.01

	��।������ ��� ��⠫������ �������� CNC

	�����:    ELMIS CNC.

	Copyright (c) ELMIS, 1993
	�� �ࠢ� ���饭�.
*/

#define CNCDIRH

	/* ���饭�� � ���ᨢ� ���䨣��樨 �� ���ᠭ�� ��ࠡ�� ���ன��.*/

#define HD_BIN  9  /* ���⪨� ��� - ������ 䠩�� */
#define HD_CNC 16  /* ���⪨� ��� - �孮�����᪨� �ணࠬ��, ⠡���� */
#define HD_RSC 10  /* ���⪨� ��� - ���䨣����, ᮮ�饭��, ����� ...*/
#define ED_SYS  0  /* �����஭�� ��� - �६���� 䠩��, �訡��  */
#define ED_CNC 19  /* �����஭�� ��� - �孮�����᪨� �ணࠬ��, ⠡����,
            				 p���稥 䠩�� */
#define ED_RSC  8  /* �����஭�� ��� - ���䨣����, ⥪��� ᮮ�饭�� */
#define FD_CNC 22  /* ������ ��� - �孮�����᪨� �ணࠬ��  � ⠡����
		      ��� ��࠭. */
#define PRF    25  /* ���ன�⢮ � ��᫥�. ����㯮� */
#define DNC    28  /* ��� ���襣� ࠭�� */

		/* ����७�� ������� 䠩��� ⠡��� */

#define PROG_EXT    ".NC"
#define TABNUL_EXT  ".TNL"
#define TABKOR_EXT  ".TKR"
#define TEHPAR_EXT  ".TPR"
#define MPAR_EXT    ".PAR"
#define TABKS_EXT   ".TTL"

		/* ����� 䠩��� �� ⠡��� */

#define FTABNUL  "TABNULL.FRM"
#define FTABKOR  "TABKORR.FRM"
#define FTEHPAR  "TEHNPAR.FRM"
#define FMPAR    "MACHPAR.FRM"
#define FTABKS   "TABTOOL.FRM"

		/* ����७�� �������� 䠩��� */

#define RESORCE_EXT	".RSC"       /* ����� ���� */
#define F_ERR           ".ERR"       /* ����� �訡�� */
#define F_NUM           ".NUM"       /* ���� ���஢ �� */
#define F_WRK           ".WRK"       /* ����稩 䠩� */
#define NMP             ".NMP"       /* ���� ���� ��� �.� */
#define MESAGE_EXT	".MSG"       /* ����� ᮮ�饭�� */
#define TEMP_FILE	".TMP"	     /* �६��. 䠩�� (����室��� 㤠����) */	

	      /* ����� �������� 䠩��� */

#define TAB_KG          "KG"          /* ������ G �㭪権*/
#define TAB_FMS         "FMS"         /* ������ M �㭪権*/
#define TAB_GS          "GS"          /* ������ ��ᮢ���⨬�� G �㭪権*/
#define FO_YP           "UNPACK"      /* 䠩� �訡�� ��*/
 
#define TEMP_DIR  "CNCDIR" 	      /* �६������ ��४�਩ */
#define UNNAMED   "UNNAMED"           /* �६����� ��� ������ 䠩�� */
#define GROUPFILE "*"                 /* �p㯯���� ��� */


