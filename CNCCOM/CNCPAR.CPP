/*
   cncPar.cpp

   ОБЪЯВЛЕНИЕ КЛАССА ПАРАМЕТРОВ CNC

   Веpсия для фpезеpно-свеpлильно-pасточных станков
   имеющих до 16 упpавляемых осей, из них 4 шпинделя.

   Copyright (c) ELMIS Ltd 1994.

*/

#pragma hdrfile "cncPar.sym"

#if !defined( __IOSTREAM_H )
#include <fStream.h>
#endif

#if !defined( __STRING_H )
#include <String.h>
#endif

#pragma hdrstop

#if !defined( __CNCPAR_H )
#include "cncPar.h"
#endif

QParameter Par("\\CNC\\CNCRSC\\QPARAMET.DAT"); /* Класс параметов */

             /* Дополнительные переменные для обработки параметров */
BYTE date;
BYTE bitmap[125];

union rpar_v rpar;
union namex namex1;
INT full;
union scom_v scom;
INT dop_ykz[KPARAM];
INT nstrpar, nword, e, xint1, c;
union sum_v sum;
BYTE* adr_b;
INT ind_b,
ind_b1;
union sumo_v sumo;

// Методы класса параметров

AxisData::AxisData()
{
    clear();
}

void AxisData::clear()
{
    memset((char*)((AxisData*)this), 0, sizeof(AxisData));
}

void QParameter::calcQ100()
{
    QParameter& Par = *this;
    _NF =			 /*число формообразующих осей    */
        _NP = 			 /*число позиционных осей        */
        _NS =		 	 /*число шпинделей               */
        _NAX = 			 /*общее кол-во осей             */
        _KMUP =			 /* кол-во МУПов */
        _NAXM =    	 		 /*кол-во основных осей(без шпинделей)*/
        _MASKF =	 		 /*маска формообразующих*/
        _MASKP =	 		 /*маска позиционных*/
        _MASKR =			 /*маска круговых*/
        _MASKS = 0;	 		 /*маска шпинделей*/


    for (register i = 0; i < NUMS; i++)
        _IS[i] = ISC[i] = 0;

    register s;
    for (register i = 0, s = 0; i < NUM; i++)
    {
        if (_AXTYPE[i] != atNoType)
        {
            if (_AXTYPE[i] < atShpindel && _AXSYN & AX(i))
            {
                _NF++;
                _MASKF = AX(i);
            }
            if (_AXTYPE[i] < atShpindel && !(_AXSYN & AX(i)))
            {
                _NP++;
                _MASKP = AX(i);
            }
            if (_AXTYPE[i] == atClosedRound  _AXTYPE[i] == atRound
            (_AXTYPE[i] == atShpindel && _AXSYN & AX(i)))
                _MASKR = AX(i);
            if (_AXTYPE[i] == atShpindel)
            {
                _NS++;
                _MASKS = AX(i);
                _IS[s] = i;
                _ISC[s++] = _AXSYN & AX(i) ? i : 0;
            }
        }
    }
    _NAX = _NF + _NP + _NS;
    _NAXM = _NAX - _NS;

    for (register i = 0; i < KMUP; i++)
        if (_ADRMUP[i])
            _KMUP++;
}

void QParameter::calcQ1000()
{
}

void QParameter::calcQ4000()
{
    QParameter& Par = *this;

    _KGF = _KMF = 0; 	// Количество групп M и G функций определенных
               // пользователем

    for (register i = 0; i < QGM; i++)
    {
        if (strlen(_P_NOMP[i]) && _P_NOMG[i])
            _KGF++;
        if (strlen(_P_NOMMP[i]) && _P_NOMM[i])
            _KMF++;
    }
}

void QParameter::calcQ6000()
{
}

void QParameter::calcConst()
{
    calcQ100();
    calcQ1000();
    calcQ4000();
    calcQ6000();
}

char* ParAxis::nameOf() const
{
    return  "ParAxis";
}

void ParAxis::printOn(ostream& out) const
{
    out << nameOf();
}

classType ParAxis::isA() const
{
    return ParAxisClass;
}

hashValueType ParAxis::hashValue() const
{
    return 0;
}

int ParAxis::isEqual(const Object& testObject) const
{
    return testObject.isA() == isA();
}

ParData::ParData()
{
    clear();
}

void ParData::clear()
{
    memset((char*)((ParData*)this), 0, sizeof(ParData));
}

char* QParameter::headerPar = "ELMIS CNC Machine-Tool Parameters V01. 1994";

QParameter::QParameter()
{
    clear();
    valid = 0;
}

QParameter::QParameter(const char* path)
{
    clear();
    if (!load(path))
        valid = 0;
}

int QParameter::load(const char* path)
{
    ifstream in(path, ios::binary);
    if (!in)
        return 0;
    else
    {
        unsigned short size = strlen(headerPar) + 1;
        char* buff = new char[size];
        in.read(buff, size);
        if (strcmp(buff, headerPar) != 0)
            return 0;
        else
        {
            in >> Par;
            if (!Par.valid)
                return 0;
        }
        delete buff;
    }
    return 1;
}

void QParameter::clear()
{
    AxisData::clear();
    ParData::clear();
}

char* QParameter::nameOf() const
{
    return "QParameter";
}

void QParameter::printOn(ostream& out) const
{
    out << nameOf();
}

classType QParameter::isA() const
{
    return QParameterClass;
}

hashValueType QParameter::hashValue() const
{
    return 0;
}

int QParameter::isEqual(const Object& testObject) const
{
    return testObject.isA() == isA();
}

ostream& operator << (ostream& os, QParameter& p)
{
    if (os.rdstate()  ios::binary)
    {
        os << (int)p.isA();
        os.write((char*)((AxisData*)&p), sizeof(AxisData));
        os.write((char*)((ParData*)&p), sizeof(ParData));
    }
    else
        p.printOn(os);
    return os;
}

istream& operator >> (istream& is, QParameter& p)
{
    if (is.rdstate()  ios::binary)
    {
        int ident;
        is >> ident;
        if (ident == p.isA())
        {
            is.read((char*)((AxisData*)&p), sizeof(AxisData));
            is.read((char*)((ParData*)&p), sizeof(ParData));
            if (is.bad())
            {
                p.clear();
                p.valid = 0;
            }
        }
        else
        {
            p.clear();
            p.valid = 0;
        }
    }
    else
        p.valid = 0;
    return is;
}


eStopBit ComPortsData::convertStopBit[2] = { _1, _2 };

eParity ComPortsData::convertParity[5] =
{
 evenParity, notevenParity, Parity_1, Parity_0, noParity
};

unsigned long ComPortsData::convertBoud[12] =
{
 75ul, 110ul, 300ul, 600ul, 1200ul, 2400ul, 4800ul, 9600ul,
 19200ul, 38400ul, 57600ul, 115200ul
};


ComPortsData::ComPortsData()
{
    numPort = bits = stopBit = parity = boud = 0;
}

Serial& ComPortsData::operator=(Serial& src)
{
    putBoud(src.Baud);
    putParity(src.Parity);
    putStopBit(src.StopBit);
    putBits(src.Bits);
    return src;
}

void ComPortsData::putNumPort(eNumCom aPortNum)
{
    switch (aPortNum)
    {
    case COM1: numPort = 0; break;
    case COM2: numPort = 1; break;
    case COM3: numPort = 2; break;
    case COM4: numPort = 3; break;
    default:   numPort = 0;
    }
}

void ComPortsData::putBoud(unsigned long aBoud)
{
    switch (aBoud)
    {
    case 75ul:    boud = 0;  break;
    case 110ul:   boud = 1;  break;
    case 300ul:   boud = 2;  break;
    case 600ul:   boud = 3;  break;
    case 1200ul:  boud = 4;  break;
    case 2400ul:  boud = 5;  break;
    case 4800ul:  boud = 6;  break;
    case 9600ul:  boud = 7;  break;
    case 19200ul: boud = 8;  break;
    case 38400ul: boud = 9;  break;
    case 57600ul: boud = 10; break;
    case 115200ul:boud = 11; break;
    default:	boud = 11;
    }
}

void ComPortsData::putParity(eParity aParity)
{
    switch (aParity)
    {
    case evenParity:    parity = 0; break;
    case notevenParity: parity = 1; break;
    case Parity_1:      parity = 2; break;
    case Parity_0:      parity = 3; break;
    case noParity:      parity = 4; break;
    default:            parity = 4;
    }
}

void ComPortsData::putStopBit(eStopBit aStopBit)
{
    stopBit = aStopBit == _1 ? 0 : 1;
}

void ComPortsData::putBits(eBits aBits)
{
    switch (aBits)
    {
    case _5: bits = 0; break;
    case _6: bits = 1; break;
    case _7: bits = 2; break;
    case _8: bits = 3; break;
    default: bits = 3;
    }
}

ComPortsData& Serial::operator=(ComPortsData& src)
{
    Bits = src.getBits();
    StopBit = src.getStopBit();
    Parity = src.getParity();
    Baud = src.getBoud();
    return src;
}

Serial& Serial::operator=(Serial& src)
{
    Baud = src.Baud;
    Parity = src.Parity;
    StopBit = src.StopBit;
    Bits = src.Bits;
    return src;
}



// Конец cncPar.cpp
