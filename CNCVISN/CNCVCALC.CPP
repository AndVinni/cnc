/*------------------------------------------------------------*/
/*                                                            */
/*   Turbo Vision 1.0                                         */
/*   Copyright (c) 1991 by Borland International              */
/*                                                            */
/*   Calc.cpp:  TCalcDisplay member functions and TCalculator */
/*              constructor                                   */
/*------------------------------------------------------------*/

#pragma hdrfile "cncvcalc.sym"

#define Uses_TEvent
#define Uses_TButton
#define Uses_TStreamableClass

#include <tv.h>

#if !defined( __STRING_H  )
 #include <String.h>
#endif

#if !defined( __CTYPE_H  )
 #include <CType.h>
#endif

#if !defined( __STRSTREA_H  )
 #include <StrStrea.h>
#endif

#pragma hdrstop

#if !defined( __CNCVCALC_H  )
 #include "CncvCalc.h"
#endif

#if !defined( __CNCVCOM_H  )
 #include "CncvCom.h"
#endif

#define cpCalcPalette   "\x13"


//
// TCalcDisplay functions
//

const char * const TCalcDisplay::name = "TCalcDisplay";

void TCalcDisplay::write( opstream& os )
{
    TView::write( os );
    os.writeBytes(&status, sizeof(status));
    os.writeString(number);
    os.writeByte(sign);
    os.writeByte(operate);
    os.writeBytes(&operand, sizeof(operand));
}


void *TCalcDisplay::read( ipstream& is )
{
    TView::read( is );
    number = new char[DISPLAYLEN];
    is.readBytes(&status, sizeof(status));
    is.readString(number, DISPLAYLEN);
    sign = is.readByte();
    operate = is.readByte();
    is.readBytes(&operand, sizeof(operand));
    return this;
}


TStreamable *TCalcDisplay::build()
{
    return new TCalcDisplay( streamableInit );
}


TStreamableClass RCalcDisplay( TCalcDisplay::name,
                               TCalcDisplay::build,
                               __DELTA(TCalcDisplay)
                             );


TCalcDisplay::TCalcDisplay(TRect& r) : TView ( r )
{
    options |= (ofSelectable | ofFramed);
    eventMask = (evKeyboard | evBroadcast);
    number = new char[DISPLAYLEN];
    clear();

}

TCalcDisplay::~TCalcDisplay()
{
   delete number;
}

TPalette& TCalcDisplay::getPalette() const
{
    static TPalette palette( cpCalcPalette, sizeof(cpCalcPalette)-1 );
    return palette;
}


void TCalcDisplay::handleEvent(TEvent& event)
{
    TView::handleEvent(event);

    switch(event.what)
        {
        case evKeyboard:
            calcKey(event.keyDown.charScan.charCode);
	    clearEvent(event);
            break;
	case evBroadcast:
	    if(event.message.command == cmCalcButton)
		{
		calcKey( ((TButton *) event.message.infoPtr)->title[0]);
		clearEvent(event);
		}
	    break;
	}
}


void TCalcDisplay::draw()
{
    char color = getColor(1);
    int i;
    TDrawBuffer buf;

    i = size.x - strlen(number) - 2;
    buf.moveChar(0, ' ', color, size.x);
    buf.moveChar(i, sign, color, 1);
    buf.moveStr(i+1, number, color);
    writeLine(0, 0, size.x, 1, buf);
}


void TCalcDisplay::error()
{
    status = csError;
    strcpy(number, "Ошибка");
    sign = ' ';
}


void TCalcDisplay::clear()
{
    status = csFirst;
    strcpy(number, "0");
    sign = ' ';
    operate = '=';
}


void TCalcDisplay::setDisplay(double r)
{
    int  len;
    char str[64];
    ostrstream displayStr( str, sizeof str );

    if(r < 0.0)
        {
        sign = '-';
        displayStr << -r << ends;
        }
    else
        {
        displayStr << r << ends;
        sign = ' ';
        }

    len = strlen(str) - 1;          // Minus one so we can use as an index.

    if(len > DISPLAYLEN)
        error();
    else
        strcpy(number, str);
}


void TCalcDisplay::checkFirst()
{
    if( status == csFirst)
        {
        status = csValid;
        strcpy(number, "0");
        sign = ' ';
        }
}


void TCalcDisplay::calcKey(unsigned char key)
{
    char stub[2] = " ";
    double r;

    key = toupper(key);
    if( status == csError && key != 'C')
        key = ' ';

    switch(key)
        {
        case '0':   case '1':   case '2':   case '3':   case '4':
        case '5':   case '6':   case '7':   case '8':   case '9':
            checkFirst();
            if (strlen(number) < 15) 
                {                       // 15 is max visible display length
                if (strcmp(number, "0") == NULL)
                    number[0] = '\0';
                stub[0] = key;
                strcat(number, stub);
                }
            break;

        case '.':
            checkFirst();
            if(strchr(number, '.') == NULL)
                {
                stub[0] = '.';
                strcat(number, stub);
                }
            break;

        case 8:
        case 27:
            int len;

            checkFirst();
            if( (len = strlen(number)) == 1 )
                strcpy(number, "0");
            else
                number[len-1] = '\0';
            break;

        case '_':                   // underscore (keyboard version of +/-)
        case 241:                   // +/- extended character.
            sign = (sign == ' ') ? '-' : ' ';
            break;

        case '+':   case '-':   case '*':   case '/':
        case '=':   case '%':   case 13:
            if(status == csValid)
                {
                status = csFirst;
                r = getDisplay() * ((sign == '-') ? -1.0 : 1.0);
                if( key == '%' )
                    {
                    if(operate == '+' || operate == '-')
                        r = (operand * r) / 100;
                    else
                        r /= 100;
                    }
                switch( operate )
                    {
                    case '+':
                        setDisplay(operand + r);
                        break;

                    case '-':
                        setDisplay(operand - r);
                        break;

                    case '*':
                        setDisplay(operand * r);
                        break;

                    case '/':
                        if(r == 0)
                            error();
                        else
                            setDisplay(operand / r);
                        break;

                    }
                }
            operate = key;
            operand = getDisplay() * ((sign == '-') ? -1.0 : 1.0);
            break;

        case 'C':
            clear();
            break;

        }
    drawView();
}



static char *keyChar[20] =
    {    "C", "\x1B",    "%", "_",   // 0x1B is escape, '_' is +/- char.
         "7",    "8",    "9",    "/",
         "4",    "5",    "6",    "*",
         "1",    "2",    "3",    "-",
         "0",    ".",    "=",    "+"
    };


//
// TCalculator functions
//

const char * const TCalculator::name = "TCalculator";

TStreamable *TCalculator::build()
{
    return new TCalculator( streamableInit );
}


TStreamableClass RCalculator( TCalculator::name,
                              TCalculator::build,
                              __DELTA(TCalculator)
                            );


TCalculator::TCalculator( ushort wnum ) :
	     TDialog( TRect(51, 3, 75, 18), "Калькулятоp" ),
	     TWindowInit( TCalculator::initFrame )
{
    TView *tv;
    TRect r;

    disableCommand( cmCalculator );

    options |= ofFirstClick;
    number = wnum;
    for(int i = 0; i <= 19; i++)
	{
        int x = (i%4)*5+2;
	int y = (i/4)*2+4;
        r = TRect( x, y, x+5, y+2 );

        tv = new TButton( r, keyChar[i], cmCalcButton, bfNormal | bfBroadcast );
        tv->options &= ~ofSelectable;
        insert( tv );
        }
    r = TRect( 3, 2, 21, 3 );
    insert( new TCalcDisplay(r) );
}

TCalculator::~TCalculator()
{
 enableCommand( cmCalculator );
}