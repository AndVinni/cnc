/*
   cncpard.h

   Опpеделение стpуктуpы Q - паpаметpов.

   Copyright (c) ELMIS Ltd 1993.

*/

#if !defined( __CNCPARD_H )
 #define __CNCPARD_H

 #if !defined( __OBJECT_H )
  #include <Object.h>
 #endif

 #if !defined( __CNCHARD_H )
  #include "cncHard.h"
 #endif

 #if !defined( __CNCRAZ_H )
  #include "cncRaz.h"
 #endif

 #if !defined( __CNCCLASS_H )
  #include "cncClass.h"
 #endif

#if !defined( __CHCONFIG_H )
 #include"chConfig.h"
#endif

enum Paralel
{
 LPT1, LPT2, LPT3, LPT4
};

struct Serial;

class ComPortsData
{
private:
 unsigned short numPort;
 unsigned short bits;
 unsigned short stopBit;
 unsigned short parity;
 unsigned short boud;

public:

 ComPortsData();
 Serial& operator=( Serial& src );

 eNumCom  	getNumPort(){ return (eNumCom)numPort; }
 eBits		getBits()   { return (eBits)bits; }
 eStopBit 	getStopBit(){ return convertStopBit[stopBit]; }
 eParity  	getParity() { return convertParity[parity]; }
 unsigned long 	getBoud()   { return convertBoud[boud]; }

 void  	putNumPort( eNumCom np);
 void	putBits( eBits );
 void 	putStopBit( eStopBit );
 void  	putParity( eParity );
 void 	putBoud( unsigned long );

private:

  static eStopBit convertStopBit[2];
  static eParity convertParity[5];
  static unsigned long convertBoud[12];
};

struct Serial : public sPhisic
{
 ComPortsData& operator=( ComPortsData& src );
 Serial& operator=( Serial& src );
};

/* 		Класс паpаметpов, котоpый необходим
		для pаботы пpиводов подач.
*/

class AxisData
{
 public:
		/*   Q100   */

    WORD	AdrMup[KMUP];		/* Q110 */
    INT		LogToPhith[NUM];	/* Q120 */
    BYTE	AxForm[NUM];		/* Q130 */
    BYTE	AxType[NUM];		/* Q140 */
    INT		AxModul[NUM];		/* Q150 */
    LONG	StepDiscr[NUM];		/* Q160 */
    BYTE	AxParal[NUM];		/* ? */
    INT		NumImp[NUM];		/* Q170 */
    INT		MSimp[NUM];		/* Q180 */
    AXBIT	MSblock;		/* Q220 */
    AXBIT	BlockSleg;		/* Q225 */
    AXBIT	MSdir;			/* Q230 */
    AXBIT	Polar;			/* Q240 */
    INT 	Dreif[NUM];		/* Q250 */
    INT         Npoz[NUM];		/* _NPOZ */
    BYTE	NF;			/* _NF */
    BYTE	NP;			/* _NP */
    BYTE	NS;			/* _NS */
    BYTE	NAX;			/* _NAX */
    BYTE	NAXM;			/* _NAXM */
    INT		exp[NUM];		/* _exp */
    AXBIT	maskF;			/* _MASKF */
    AXBIT	maskP;			/* _MASKP */
    AXBIT	maskS;			/* _MASDKS */
    AXBIT	AxStep;			/* _AXSTEP */
    AXBIT	maskR;			/* _MASKR */
    AXBIT	maskE;			/* _MASKE */
    REAL	KF2[NUM];		/* _KF2 */
    BYTE	IS[NUMS];		/* _IS */
    BYTE	ISC[NUMS];		/* _ISC */
    BYTE	kMup;			/* _KMUP */

			/*    Q500  */

    INT		MaxFeed[NUM];		/* Q500 */
    INT		VG00[NUM];		/* Q510 */
    INT		Vnull[NUM];		/* Q520 */
    INT		Vsing[NUM];		/* Q530 */
    INT		VNkul[NUM];		/* Q540 */
    INT		AvRas[NUM];		/* Q600 */
    INT		TimeAvRas[NUM];		/* Q610 */
    INT		Alimit[NUM];		/* Q620 */
    INT		Vlimit[NUM];		/* Q630 */

			/*    Q1000    */

    INT		KV[NUM];		/* Q1000 */
    INT		KVokey[NUM];		/* Q1010 */
    INT		A[NUM];			/* Q1020 */
    INT		Vrazgon[NUM];		/* Q1030 */
    INT		Vtorm[NUM];		/* Q1040 */
    INT		Acomm[NUM];		/* Q1050 */
    INT		Vcomm[NUM];		/* Q1060 */
    REAL	Kdinam[NUM];		/* _KDIN */
    REAL	KdinamC[NUM];		/* _KDINC */
    REAL	Stormoz[NUM];		/* _STORM */
    LONG	MOplusX[NUM];		/* _MOPLUS */
    LONG	MOminusX[NUM];   	/* _MOMINUS */

			/* Q1500 */

    LONG	Xnull[NUM];		/* Q1500 */
    LONG	Snull[NUM];		/* Q1510 */
    AXBIT	blockMO;		/* Q1520 */
    REAL	MOplus[NUM];		/* Q1530 */
    REAL	MOminus[NUM];		/* Q1540 */
    INT		AvRasP[NUM];		/* Q600 */
    INT		TimeAvRasP[NUM];	/* Q610 */
    LONG	MO_plus[NUM];		/* Q? */
    LONG	MO_minus[NUM];		/* Q? */
    LONG	O_key[NUM];		/* Q1550 */
    REAL	IFG[QGF][NUM];          /* Q1580-Q1520 */

			/* Q2000 */

    INT		Luft[NUM];		/* Q2000 */
    AXBIT	AxCorr;			/* Q2010 */
    LONG	Tcorr[NUM];		/* Q2020 */
    INT		Step[NUM];		/* Q2030 */
    LONG	X0[NUM];		/* Q2040 */
    INT		Ncorr[NUM];		/* Q2050 */
    INT		Corr[KPARAM];		/* Q2060 */

			/* Q4000 */

    CHAR	NamePG[QGM][NAMEL];	/* Q4000 */
    WORD	NameFG[QGM];		/* Q4010 */
    CHAR	NamePM[QGM][NAMEL];	/* Q4020 */
    CHAR	NameFM[QGM][2];		/* Q4030 */
    INT		G90_G91;		/* Q4050 */
    INT		G68_G69;		/* Q4060 */
    BYTE	TablKs;			/* Q4070 */
    INT		Notvod[NUM];		/* Q4080 */
    BYTE	KgF;			/* _KGF */
    BYTE	KmF;			/* _KMF  */

			/* Q5000 */

    WORD	AxSw[MAXPOINT];		/* Q5000 */
    LONG	MinSw[MAXPOINT];	/* Q5000 */
    LONG	MaxSw[MAXPOINT];	/* Q5000 */
    REAL	IFP[NUM][MAXPOINT];	/* Q5020-Q5180 */

			/*  Q6000  */

    BYTE	Nstup[NUMS];		/* Q6020 */
    WORD	MinStup[NUMS][MAXST];   /* Q6030 */
    WORD	MaxStup[NUMS][MAXST];	/* Q6040 */
    WORD	Orient[NUMS][MAXST];	/* Q6050 */
    INT		Sperekl[NUMS][MAXST];	/* Q6090 */
    LONG	Sampl[NUMS];		/* Q6100 */
    REAL	Stemp[NUMS];		/* Q6110 */
    WORD	Sokey[NUMS];		/* Q6120 */
    BYTE	Morient[NUMS][2];	/* Q6130 */
    INT		SKV[NUMS][MAXST];	/* Q6140 */
    LONG	Srazgon[NUMS][MAXST];	/* Q6150 */
    INT		Sluft[NUMS][MAXST];	/* Q6160 */
    REAL	SNZNF[NUMS];		/* Q6170 */
    INT		SKVstop[NUMS][MAXST];	/* Q6180 */
    INT		SSKV[NUMS][MAXST];	/* Q6190 */
    REAL	SNmin[NUMS];		/* Q6200 */
    BYTE	MFS[NUMS][MAXST][2];	/* Q6210 */
    REAL	SKdin[NUMS];		/* _SKDIN */
    REAL	SA[NUMS];		/* _SA */
    WORD	SVlimit[NUMS][MAXST];	/* Q? */
    INT		Sdreif[NUMS][MAXST];	/* Q? */
    INT		SKcap[NUMS][MAXST];	/* коэфф. пересчета ЦАП */
    INT		SKcapa[NUMS][MAXST];	/* коэфф. пересчета ЦАП */

    AxisData();
    void clear();

};

class ParData
{
 public:
		     /*  Q100  */

    INT		AxAdr[NUM];		/* Q110 */
    AXBIT	AxSyn;			/* Q145 */
    AXBIT	IndAx;			/* Q190 */
    AXBIT	IndAxD;			/* Q200 */
    AXBIT	CircleLog;		/* Q210 */
    INT		AxDiskr[NUM]; 		/* _AXDISCKR */

			/* Q500 */

    INT		HandF1[NUM];		/* Q550 */
    INT		HandF2[NUM];		/* Q560 */
    INT		HandF3[NUM];		/* Q570 */
    INT		HandG00[NUM];		/* Q580 */
    INT		MaxWorkF;		/* Q590 */

			/* Q1000 */

    INT		perehodF[NUM];		/* Q1070 */
    REAL	MinSlop[NUM];		/* Q1080 */
    REAL	MaxSlop[NUM];		/* Q1090 */
    REAL	MinKV[NUM];		/* Q1100 */
    REAL	MaxKV[NUM];		/* Q1110 */

			/* Q2500 */

    BYTE   	ContAl;	        	/* Q2500 */
    BYTE        MinF; 	        	/* P2510 */
    BYTE        MaxF;                	/* Q2510 */
    BYTE        MinS;         		/* Q2520 */
    BYTE	MaxS;                	/* Q2520 */
    BYTE        BigStep;             	/* Q2530 */
    BYTE        LitlStep;     		/* Q2540 */

			/* Q3000 */

    BYTE	GroupM;			/* Q3000 */
    BYTE	GroupT;			/* Q3000 */
    BYTE	MVost[QMF][2];		/* Q3010 */

			/* Q4500 */

    eNumCom	nPLC;			/* Q4500 */
    eNumCom	nDRC;			/* Q4510 */
    eNumCom	nDNC;			/* Q4520 */
    Serial	pDNC;			/* Q4520 */
    eNumCom	nPRF;			/* Q4530 */
    Serial	pPRF;			/* Q4530 */
    Paralel	nPRN;			/* Q4540 */

			/* Q6000 */

    INT		ShAdr[NUMS];		/* Q6000 */
    AXBIT	OsSh;			/* Q6005 */
    REAL	Slimit[NUMS];		/* Q6010 */
    AXBIT	PolarM3[NUMS];		/* Q6070 */
    AXBIT	PolarM4[NUMS];		/* Q6080 */
    INT		Stolchok[NUMS][MAXST];	/* Q6220 */
    BYTE	Most[NUMS][2];		/* Q6230 */
    BYTE	Mleft[NUMS][2];		/* Q6240 */
    BYTE	Mright[NUMS][2];	/* Q6250 */

			/* Q6500 */

    char        adrCNC[9];       	/*Q6500 */

			/* Q7000 */

    int		TestEr;      		/*Q7000*/

   int valid;

  ParData();
  void clear();

};

class ParAxis : public AxisData, public Object
{
 public:

    virtual char _FAR * nameOf() const;
    virtual void printOn( ostream& out ) const ;
    virtual classType isA() const ;
    virtual hashValueType hashValue() const ;
    virtual int isEqual(const Object& testObject) const ;
};

class QParameter : public AxisData, public ParData
{
 public:

  QParameter();
  QParameter(const char * path);

  virtual char _FAR * nameOf() const ;
  virtual void printOn( ostream& out ) const ;
  virtual classType isA() const ;
  virtual hashValueType hashValue() const ;
  virtual int isEqual(const Object& testObject) const ;

  int load(const char * path);
  void clear();

  void calcQ100();
  void calcQ1000();
  void calcQ4000();
  void calcQ6000();
  void calcConst();

  static char * headerPar;
};

ostream& operator << ( ostream& os, QParameter& p );
istream& operator >> ( istream& is, QParameter& p );

extern QParameter Par;


#endif



