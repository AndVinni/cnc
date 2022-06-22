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
typedef void interrupt _FAR( InterSerDevice:: *VInt)(...);

typedef void interrupt _FAR( *OldVInt)(...);

typedef void _FAR( *VoidFunVoid)(void);
typedef void _FAR(SerDevice:: *FunSerDev)(void);
typedef void _FAR(InterSerDevice:: *FunIntDevVoid)(void);
typedef void _FAR(DevProRes:: *voPointFunDP)(void);
typedef void _FAR(DevProTra:: *voPointFunDPT)(void);

#endif

















