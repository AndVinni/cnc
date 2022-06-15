/*   Программа формирования массива
кодов пояснений ошибки набора

	F_ERROR()
*/


#include <stdio.h>
#include "cnchard.h"
#include "cncraz.h"
#include "cnccdef.h"
#include "cncvoidu.h"
#include "cncun2.h"

void f_error(INT k_er)
{ INT i_dn = 0;

for (i_dn = 0; i_dn < ER_N; i_dn++)
{
	if (i_nab < i_dn  i_nab == 0)
	{
		err_nab[i_nab++] = k_er;
		break;
	}
	if (err_nab[i_dn] == k_er)
		break;
}
}
