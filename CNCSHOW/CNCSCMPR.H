/*  	cncscmpr.h v01.01

	Определения для компиляции и сохранения параметров станка

	Подпроект: CNCSHOW
	Проект:    ELMIS CNC.

	Copyright (c) ELMIS, 1993
	Все права защищены.
*/

typedef BOOL (*QPARAMCOMPILLER)(void);
typedef QPARAMCOMPILLER COMPILLERARRAY[];

