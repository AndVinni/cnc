/*  	cncsrmsg.cpp v01.01

	��ନ஢���� ���ᨢ�� ᮮ�饭��

	����஥��: CNCSHOW
	�஥��:    ELMIS CNC.

	Copyright (c) ELMIS, 1993
	�� �ࠢ� ���饭�.
*/

#include <stdio.h>
#include <io.h>
#include <alloc.h>
#include <string.h>
#include "cnchard.h"
#include "cncshow.h"   
#include "cncscr.h"
#include "cncraz.h"
#include "cnccdef.h"
#include "cnccstat.h"
#include "cncsfun.h"

static WORD StrInFile(const STRING path);

		     /* �㭪�� ���������� ���ᨢ�� ᮮ�饭�� */

void ReadMsg(STRING** array,const STRING dfile)
{
 register i;
 register strinfil=0;	 			/* ����� 䠩�� */
 FILE *fpointer;
 
 if((strinfil=StrInFile(dfile))==NULL)
  SetError(0,0,0,0,BLOCKFID);
 else
 {
  fpointer=fopen(dfile,"r");             /* �᫨ 䠩� ᮮ�饭�� ������� */
  if(fpointer==NULL)
   SetError(1,5,1,4,NOBLOCKFID);
  else
  {
   CHAR tmps[MAXSTR];			/* ���� �⥭�� � ���������� ���ᨢ� */
   register leng;
   if(Not *array)
   {
    if((*array=(STRING*)farcalloc(++strinfil,sizeof(STRING)))==NULL)
    {
     SetError(8,1,5,5,NOBLOCKFID);
     return;
    }
   }
   for(i=0;(fgets(tmps,MAXSTR,fpointer))!=NULL;i++)
   {
    leng=strlen(tmps);
    if(Not (*array)[i])
     if(((*array)[i]=(STRING)farmalloc(leng))==NULL)
     {
      SetError(8,1,5,5,NOBLOCKFID);
      FreeMesage(array);
      return;
     }
    strcpy((*array)[i],tmps);
    (*array)[i][--leng]='\0';
   }
  }  
 }
 fclose(fpointer);
}				/* end ReadMsg */

		/* �㭪�� ������� ��ப � ⥪�⮢�� 䠩�� */

WORD StrInFile(const STRING path)
{
 FILE *fp;
 if(access(path,0)!=0)               /* �����㫨 ���������騩 䠩� */
  SetError(0,0,0,0,BLOCKFID);
 else
 {
  if((fp=fopen(path,"r"))==NULL)
   SetError(1,5,1,4,NOBLOCKFID);
  else
  {
   register WORD i;
   CHAR nulstr[MAXSTR];
   for(i=0;Not feof(fp);i++)
   {
    fgets(nulstr,MAXSTR,fp);
    if(ferror(fp))
    {
     SetError(0,0,0,0,BLOCKFID);
     fclose(fp);
     return 0U;
    }
   }
   fclose(fp);
   return i;
  }
 }
 fclose(fp);
 return 0U;
}  			/* ����� StrInFile */

			/* �᢮�������� ���ᨢ� */

void FreeMesage(STRING** arraymesage)
{
 while(**arraymesage)
  farfree((**arraymesage)++);
 farfree(*arraymesage);
}       		/* ����� FreeMesage */

