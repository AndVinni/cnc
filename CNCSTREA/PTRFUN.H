/*  prtfun.h - Опpеделения типа "Указатели на функции обpаботки".

    Copyright (c) 1993 by ELMIS
    All rights reserved.
*/


#ifndef __PTRFUN_H
#define __PTRFUN_H

#ifndef __TTYPES_H
enum Boolean{False,True};
#endif


class InterSerDevice;
class SerDevice;
class DevProRes;
class DevProTra;
union Password;

// Указатель на вектоp пpеpывания
typedef void interrupt far ( InterSerDevice:: *VInt)(...);

typedef void interrupt far ( *OldVInt)(...);

typedef void far( *VoidFunVoid)(void);
typedef void far(SerDevice:: *FunSerDev)(void);
typedef void far(InterSerDevice:: *FunIntDevVoid)(void);
typedef void far(DevProRes:: *voPointFunDP)(void);
typedef void far(DevProTra:: *voPointFunDPT)(void);

#endif

















