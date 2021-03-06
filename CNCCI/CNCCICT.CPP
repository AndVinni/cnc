	 /*   circuit.c  */
#include <math.h>
#include <stdio.h>
#include "cncraz.h"
#include "cnccdef.h"
#include "cnchard.h"
#include "cnccstat.h"
#include "cncun2.h"
#include "cncvoidi.h"
#include "cnccsti.h"
#include "cncint.h"
#include "cncun1.h"

   #define EPS 4.  /*��ଠ �筮��*/

   void cnccict()/*�ਭ������� �� �������� �窠 ���㦭���?*/
   {

     REAL *pxend,
          *pxbeg,
	  point2,
          absdis,
          di,dj;

     pxend=x;
     pxbeg=tek;
		/*���᫥��� ����稭� R*2=I*2+J*2*/
     distan2=pow(*(pxend+ip1),2)+pow(*(pxend+ip2),2);
	       /*�ᯮ���� �ࠢ����� ���㦭���,
		���᫥��� ����稭� R*2 �� �������� � ⥪�饩
		�窠�*/
     if(nzvk[nomn] Ifset PRA || nzvk[nomn] Ifset PRK)
     {
       di=*(pxend+ik1)-(*(pxbeg+ik1)+*(pxend+ip1));
       dj=*(pxend+ik2)-(*(pxbeg+ik2)+*(pxend+ip2));
     }
     else
     {
       di=*(pxend+ik1)-*(pxend+ip1);
       dj=*(pxend+ik2)-*(pxend+ip2);
     }
     point2=pow(di,2)+pow(dj,2);
     absdis=fabs(distan2-point2);
     if(absdis>EPS)
       error(1);
    }

   void cnccirrr(REAL acent,REAL bcent)/*�ਭ������� �� �������� �窠 ���㦭���?*/
   {
     REAL dist,
	  *pxend,
	  point2,
	  absdis,
	  di,dj;


     pxend=x;
		/*���᫥��� ����稭� R*2 */
     dist=pow(*(pxend+I_R),2);
	       /*�ᯮ���� �ࠢ����� ���㦭���,
		���᫥��� ����稭� R*2 �� �������� � ⥪�饩
		�窠�*/
       di=*(pxend+ik1)-acent;
       dj=*(pxend+ik2)-bcent;
     point2=pow(di,2)+pow(dj,2);
     absdis=fabs(dist-point2);
     if(absdis>EPS)
       error(1);

    }

