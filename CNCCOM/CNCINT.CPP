

#include "cnchard.h"
#include "cncraz.h"
#include "cnccdef.h"
#include "cnccsti.h"
#include "cncint.h"


/*ДАННЫЕ CNCDR*/
LONG  xkasan[NUM];       /*koordinata kasanija*/

           /*рабочие переменные*/
WORD  xk1,
xk2,
xk3,
xk4,
xk5;
INT   f_ind;		/* контурная подача */
REAL  fi;
REAL  vkadr[NUM];               /*заданная скорость*/
LONG  xtask[NUM],               /*текущая рассчетная координата*/
xkadr[NUM],               /*заданная координата*/
xtest[NUM],
_xzad[NUM],              /*копия задания для асинхронных осей*/
dxpoz[NUM],               /*координата пройденной позиции*/
dxmod[NUM],               /*пройденное расстояние по модулю*/
dluft[NUM],               /*приращение люфта*/
fost[NUM],                /*остатки пути*/
slowtorm,
storm0,
slowost;
REAL ftakt,                    /*скорость интерполяции в такте*/
ftask,                    /*заданная контурная скорость*/
fek,                      /*скорость конца кадра*/
maxsost,                  /*максимальный остаток пути*/
storm,                    /*путь торможения*/
vtakt[NUM],               /*tekuschay raschetnay skorost v takte*/
vtask[NUM];               /*okonchat.skorost*/
INT  xtakt[NUM],               /*тактовая выдача*/
endin,                    /*конец ввода*/
slovo,                    /*рабочая ячейка*/
feks,		       /*скорость конца кадра по C */
fslow,
refst[NUM],               /*состояние выезда в ноль*/
refsts[NUMS],
ik,                       /*индекс буфера кадра*/
xtimein,                  /*контроль времени ввода*/
xcntq,                    /*счетчмк быстрых стопов*/
xcntin,                   /*счетчик введенных байт*/
xnin,                     /*кол-во вводимых байт*/
xnout,
xsumin,                   /*контр сумма ввода*/
xendin,                   /*признак конца цикла ввода*/
nax[NUM],                 /*номера осей интерполяции*/
naxp[NUM],
nf,                       /*количество осей интерполяции*/
nfp,
ns[NUMS],                 /*ступень шпинделя*/
dxnum[NUM],               /*номер позиции дискретной оси*/
msdrive[NUM * (NAVX + NINFX)], /*аварии и сообщения по приводам*/
msnax[NUM * (NAVX + NINFX)],   /*номер оси с ошибкой*/
mshard[NAVDRC + NAVMS],      /*аварии CNCAX и DRC*/
idr, inax, ird;              /*индексы пред.массивов*/

                /*характеристики приводов*/
AXBIT sleg,     /*regim slegenia*/
move,     /*regim dvigenia*/
ltorm,    /*poslednee tormogenie*/
ltorm1,
sltorm,
xdir,     /*направление*/
xdirs,
ax_on,    /*привод взят на слежение*/
blmove,   /*блокировка движения*/
ptask,               /*пер фр задания*/
pptask,
ktask, 	       /*копия задания*/
ktasks,
pktask,
z_ktask = 0,
z_ktasks = 0,
z_ptask = 0,
stasks,
staskp = 0,
blokMO,
MASKI,
MASKP,
kprkv,
rkalibr,
xref,
MQUIT,
pdrive,                /*пер фр включения приводов*/
zdrive,                /*задн фронт вкл приводов*/
drives,                /*предыд сост приводов*/
_ptask,		      /* копия задания текущего кадра */
_stask,		      /* копия задания S текущего кадра */
xquit_z,
qdron;                 /*взятие привода на слежение*/
REAL sfi[NUMS];             /*фаза качания*/
BYTE                           /*запрос информации*/
* (*win),                /*рабочая копия буфера ввода*/
* (*wout),              /*буфер вывода*/
k_sum = '\125',	     /* контрольная сумма wout */
* xbufin,             /*буфер ввода*/
* (*pout);


/*DRC-->CNCDR*/

BYTE* Spr,
* Spr1,
qstop;           /*быстрый стоп*/
LONG* rass,           /*рассогласование*/
* rassd;
INT* nstr,           /*количество плохих страниц*/
* fstr;           /*адреса плохих страниц*/
LONG* xabs,           /*абсолютная координата*/
* xabsd;
/*CNCDR-->DRC*/
AXBIT* okey,         /*зона океу*/
* xquit,          /*квитирующие сигналы*/
* cap0,          /*ноль на ЦАП*/
* prxr,            /*признаки осей*/
* prxq,
* prxz,
* prxk,
* prxv;
BYTE* stup;       /*ступень шпинделя*/
INT* xcap;     /*тактовая выдача*/
INT* PROGKV;     /*программир.KV*/
AXBIT xavar_z[NUM];         /*авария приводов*/
BYTE Spr_z[NUM],
Spr1_z[NUM];
WORD stdrc_z,          /*слово статуса DRC*/
stdrcz;
LONG  rass_z[NUM],           /*рассогласование*/
rass_zd[NUM];
INT  nstr_z,           /*количество плохих страниц*/
fstr_z;           /*адреса плохих страниц*/
LONG xabs_z[NUM],           /*абсолютная координата*/
xabs_zd[NUM];
/*CNCDR-->DRC*/
AXBIT okey_z,         /*зона океу*/
cap0_z,          /*ноль на ЦАП*/
prx_zr,            /*признаки осей*/
prx_zq,
prx_zz,
prx_zk,
prx_zv;
BYTE stup_z;       /*ступень шпинделя*/
INT  xcap_z[NUM];     /*тактовая выдача*/
INT PROGKV_z[NUM];     /*программир.KV*/
