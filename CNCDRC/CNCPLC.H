/*
                  CNCPLC.H V01.01
              Определения для протокола
                    обмена с PLC

    Продукция экспериментально-исследовательского
 отдела специального конструкторского бюро обрабатывающих
                       центров

                    Гомель 1992 г.
*/

     
/* Определения индексов массива PCNC */

#define _PCNC(x)      pcnc[(x)]
#define DRIVE_ON      pcnc[0] /* Привод оси N включен  */
#define FEED_ENABLE   pcnc[1] /* Разрешение подачи   */
#define REF_POINT     pcnc[2] /* Опорная точка   */
#define DIR_REFER     pcnc[3] /* Направление выезда в ноль*/
#define REDUC_FEED    pcnc[4] /* Снижение скорости  по оси N */
#define BLK_Q_STOP    pcnc[5] /* Блокировка быстрого стопа */
#define QUIT_STP_SP   pcnc[6] /* Подтверждение  N ступени для 1&2 шпинд.  */
#define MAN_FEED1     pcnc[7] /* Толчковыя  перемещения    1:+,-;...;4:+,- */
#define MAN_FEED5     pcnc[8] /* Толчковыи  перемещения    5:+,-;...;8:+,- */
#define SPEED_PR      pcnc[9] /* Признаки скорости */
#define EXT_SPEED    pcnc[10] /* Значение внешнего потенц. подач    */
#define EXT_SHP1     pcnc[11] /* Значение внешнего потенцю   1 шпинделя*/
#define EXT_SHP2     pcnc[12] /*           ----#-----        2   --#-- */
#define AX_PR        pcnc[13] /* Осевыя признаки */
#define STOP_P       pcnc[14] /* Признаки стопов и блокировок */
#define NUM_AX       pcnc[15] /* Номера осей и точек заданных параметрами  */
#define TOOLS1       pcnc[16] /* Параметры  1-го магазина            */
#define TOOLS2       pcnc[17] /* Параметры  2-го магазина            */
#define TEHNOLOG     pcnc[18] /* Параметры технологии */
#define SHPIND1      pcnc[19] /* Параметры 1-го шпинделя*/
#define SHPIND2      pcnc[20] /*   -#-     2-го        */
#define COD_BUT      pcnc[21] /* Код кнопки  */
#define BLK_BUT      pcnc[22] /* Блокировка кнопок системного пульта*/
#define UNISED1      pcnc[23] /* Динамнч индикац памяти 'PC'*/
//#define UNISED2    pcnc[24] /* ----------- #---------------*/
//#define UNISED3    pcnc[25] /* Номер группы ошибок  */
#define DIN_SHOW1    pcnc[24] /* Байт ошибок */
#define DIN_SHOW2    pcnc[25] /* */
#define ERRORS       pcnc[27] /* Резерв */
#define NUM_ERROR    pcnc[26] /*         */
#define CHEK_SUM     pcnc[39] /* Контрольная сумма */

/* Определение индексов массива NCPC */

#define _NCPC(x)      ncpc[(x)]
#define OKEY          ncpc[0] /* Ось в позиции*/
#define QUIT_REF      ncpc[1] /* Подтверждение выезда в ноль */
#define PR_SHPIND1    ncpc[2] /* Некоторые признаки шпинделя   1 */
#define PR_SHPIND2    ncpc[3] /* -----------------------------  2 */
#define COM_FEED1     ncpc[4] /* Команда перемещ.   1:+,-...4:+.- OSJM */
#define COM_FEED5     ncpc[5] /* ------------------ 5------ 8 -------- */
#define MODE_WORK     ncpc[6] /* Режим работы   */
#define MODE_CNC      ncpc[7] /* ------- УЧПУ  */
#define MODE_TEHN     ncpc[8] /* ------- технологии */
#define COD_FUNK1     ncpc[9] /* Код вспомогательной функции*/
#define COD_FUNK2     ncpc[10] /*Код вспом функций          */
#define FUNK11        ncpc[12] /* Значение вспомогательной функции M1 */
#define FUNK12        ncpc[13] /* ---------------------- 2-ой байт */
#define MFUNK21       ncpc[14] /* ------------#---------функции М2    */
#define MFUNK22       ncpc[15] /* ------------#-----------2-ой байт  */
#define MFUNK31       ncpc[16] /* ------------#---------функции M3   */
#define MFUNK32       ncpc[17] /* ------------#----------@-ой байт  */
#define TFUNK11       ncpc[18]/* Значение вспомогат функции Т1     */
#define TFUNK12       ncpc[19] /*------------------------2-ой байт */
#define TFUNK21       ncpc[20]/*---------------------- Т2         */
#define TFUNK22       ncpc[21] /*-----------------------2-ой байт */
#define SFUNK11       ncpc[22] /*Значение функции     S1          */
#define SFUNK12       ncpc[23] /*------------------------2-ой байт*/
#define SFUNK13       ncpc[24] /*-----------------------3-ий байт */
#define SFUNK14       ncpc[25] /*-----------------------4-ый байт */
#define SFUNK21       ncpc[26]  /* ------------функции  S2        */
#define SFUNK22       ncpc[27] /*--------------------------2 б---*/
#define SFUNK23       ncpc[28] /*---------------------------3 б--*/
#define SFUNK24       ncpc[29] /*--------------------------4 б--*/
#define BUT_COD       ncpc[30] /* Код кнопки */
#define STROB_SHOW    ncpc[31] /* Признаки передаваемых адресов */
#define ADR_SHOW1     ncpc[32] /* Адрес переменной для индикации  1 байт */
#define ADR_SHOW2     ncpc[33] /* ------------------------------- 2 ---- */
#define END_SWICH1    ncpc[34] /* Конечники 1 байт */
#define END_SWICH2    ncpc[35] /* --------- 2 ---- */
#define DNC1          ncpc[36] /* Сигналы DNC 1 байт */
#define DNC2          ncpc[37] /* ----------- 2 байт */
#define SUM_CHEK      ncpc[39] /* Контрольная сумма */

extern BYTE  pcnc[SIZE_EXCHANGE];/* Буфер обмена 'сюда'из PC */
extern BYTE  ncpc[SIZE_EXCHANGE];/* ------------- "туда" ---- */
     
                               
     
