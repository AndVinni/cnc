/*  	cncstio.cpp v01.01

	�ணࠬ�� ����㧪� � ��࠭���� ⠡���

	�㭪��  : Table Editor
	����஥��: CNCSHOW
	�஥��:    ELMIS CNC.

	Copyright (c) ELMIS, 1993
	�� �ࠢ� ���饭�.
*/

#include <dir.h>
#include "cnchard.h"
#include "cncshow.h"
#include "cncsted.h"
#include "cncpard.h"
#include "cncpar.h"
#include "cncsfun.h"

STRING *CompilMesage;   /* �訡�� ��������஢ */

			/* ����㧪� ��ࠬ��஢ �ணࠬ� */

void LoadTehParam(void)
{
 FILE *in;

 if((in=fopen(Atab->TablName,"r"))==NULL)
 {
  SetError(1,5,1,4,NOBLOCKFID);
  return;
 }
 else
 {
  register i,j;
  INT col,str;
  float data;

  for(j=500,str=4;j>0;j--,str++)
   for(i=2,col=4;i>0;i--,col+=5)
   {
    fscanf(in,"%f",&data);
    if(feof(in))
     goto exitloop;
    (*Atab->tbl)[str][col]->dv.vreal=data;
   }
  exitloop:;
  fclose(in);
 }
}			/* ����� LoadTehPar */

BOOL CompTehParam(void)
{
 FILE *out;

 if((out=fopen(Atab->TablName,"w"))==NULL)
 {
  SetError(1,5,1,4,NOBLOCKFID);
  return FALSE;
 }
 else
 {
  register i,j;
  INT col,str;

  for(j=500,str=4;j>0;j--,str++)
   for(i=2,col=4;i>0;i--,col+=5)
    fprintf(out,"%4.3f ",(*Atab->tbl)[str][col]->dv.vreal);
  fclose(out);
  return TRUE;
 }
}

		/* ����㧪� ⠡���� ���४権 �����㬥�� */

void LoadTabKorr(void)
{
 FILE *in;

 if((in=fopen(Atab->TablName,"r"))==NULL)
 {
  SetError(1,5,1,4,NOBLOCKFID);
  return;
 }
 else
 {
  register i,j;
  INT str,col;
  float dataL, dataR;

  for(j=50,str=4;j>0;j--,str+=2)
   for(i=2,col=3;i>0;i--,col+=4)
   {
    fscanf(in,"%f",&dataL);
    fscanf(in,"%f",&dataR);
    if(feof(in))
     goto exitloop;
    (*Atab->tbl)[str][col]->dv.vreal=dataL;
    (*Atab->tbl)[str+1][col]->dv.vreal=dataR;
   }
  exitloop: fclose(in);
 }
}                        /* ����� LoadTabKorr  */

		/* ��������� � ��࠭���� ���४権 ����.*/

BOOL CompTabKorr(void)
{
 FILE *out;

 if((out=fopen(Atab->TablName,"w"))==NULL)
 {
  SetError(1,5,1,4,NOBLOCKFID);
  return FALSE;
 }
 else
 {
  register i,j;
  INT str,col;

  for(j=50,str=4;j>0;j--,str+=2)
   for(i=2,col=3;i>0;i--,col+=4)
   {
    fprintf(out,"%4.3f ",(*Atab->tbl)[str][col]->dv.vreal);
    fprintf(out,"%4.3f ",(*Atab->tbl)[str+1][col]->dv.vreal);
   }
  fclose(out);
  return TRUE;
 }
} 			  /* ����� CompTabKorr  */


		      /* ����㧪� ⠡���� ᬥ饭�� ��� */

void LoadTabNull(void)
{
 FILE *in;

 if((in=fopen(Atab->TablName,"r"))==NULL)
 {
  SetError(1,5,1,4,NOBLOCKFID);
  return;
 }
 else
 {
  register i,j,k;
  INT str,col,axn;
  float data;

  for(k=10,str=7;k>0;k--,str+=19)
   for(j=3,col=3;j>0;j--,col+=3)
    for(i=16,axn=0;i>0;i--,axn++)
    {
     fscanf(in,"%f",&data);
     if(feof(in))
      goto exitloop;
     (*Atab->tbl)[str+axn][col]->dv.vreal=data;
     (*Atab->tbl)[str+axn][col-2]->dv.vstr[0]=(CHAR)_AXADR[axn];
     (*Atab->tbl)[str+axn][col-2]->dv.vstr[1]=(CHAR)(_AXADR[axn]>>8);
    }
  exitloop: fclose(in);
 }
}			 /* ����� LoadTabNull */


		   /* ��������� � ��࠭���� ᬥ饭�� ��� */

BOOL CompTabNull(void)
{
 FILE *out;

 if((out=fopen(Atab->TablName,"w"))==NULL)
 {
  SetError(1,5,1,4,NOBLOCKFID);
  return FALSE;
 }
 else
 {
  register i,j,k;
  INT str,col,axn;

  for(k=10,str=7;k>0;k--,str+=19)
   for(j=3,col=3;j>0;j--,col+=3)
    for(i=16,axn=0;i>0;i--,axn++)
     fprintf(out,"%4.3f ",(*Atab->tbl)[str+axn][col]->dv.vreal);
  fclose(out);
  return TRUE;
 }
}			/* ����� CompTabNull */

 