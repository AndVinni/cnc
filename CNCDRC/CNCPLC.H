/*
                  CNCPLC.H V01.01
              ��।������ ��� ��⮪���
                    ������ � PLC

    �த��� ��ᯥਬ��⠫쭮-��᫥����⥫�᪮��
 �⤥�� ᯥ樠�쭮�� ���������᪮�� ��� ��ࠡ��뢠���
                       業�஢

                    ������ 1992 �.
*/

     
/* ��।������ �����ᮢ ���ᨢ� PCNC */

#define _PCNC(x)      pcnc[(x)]
#define DRIVE_ON      pcnc[0] /* �ਢ�� �� N ����祭  */
#define FEED_ENABLE   pcnc[1] /* ����襭�� �����   */
#define REF_POINT     pcnc[2] /* ���ୠ� �窠   */
#define DIR_REFER     pcnc[3] /* ���ࠢ����� �륧�� � ����*/
#define REDUC_FEED    pcnc[4] /* �������� ᪮���  �� �� N */
#define BLK_Q_STOP    pcnc[5] /* �����஢�� ����ண� �⮯� */
#define QUIT_STP_SP   pcnc[6] /* ���⢥ত����  N ��㯥�� ��� 1&2 诨��.  */
#define MAN_FEED1     pcnc[7] /* ���窮���  ��६�饭��    1:+,-;...;4:+,- */
#define MAN_FEED5     pcnc[8] /* ���窮��  ��६�饭��    5:+,-;...;8:+,- */
#define SPEED_PR      pcnc[9] /* �ਧ���� ᪮��� */
#define EXT_SPEED    pcnc[10] /* ���祭�� ���譥�� ��⥭�. �����    */
#define EXT_SHP1     pcnc[11] /* ���祭�� ���譥�� ��⥭��   1 诨�����*/
#define EXT_SHP2     pcnc[12] /*           ----#-----        2   --#-- */
#define AX_PR        pcnc[13] /* �ᥢ�� �ਧ���� */
#define STOP_P       pcnc[14] /* �ਧ���� �⮯�� � �����஢�� */
#define NUM_AX       pcnc[15] /* ����� �ᥩ � �祪 �������� ��ࠬ��ࠬ�  */
#define TOOLS1       pcnc[16] /* ��ࠬ����  1-�� ��������            */
#define TOOLS2       pcnc[17] /* ��ࠬ����  2-�� ��������            */
#define TEHNOLOG     pcnc[18] /* ��ࠬ���� �孮����� */
#define SHPIND1      pcnc[19] /* ��ࠬ���� 1-�� 诨�����*/
#define SHPIND2      pcnc[20] /*   -#-     2-��        */
#define COD_BUT      pcnc[21] /* ��� ������  */
#define BLK_BUT      pcnc[22] /* �����஢�� ������ ��⥬���� ����*/
#define UNISED1      pcnc[23] /* ������� ������� ����� 'PC'*/
//#define UNISED2    pcnc[24] /* ----------- #---------------*/
//#define UNISED3    pcnc[25] /* ����� ��㯯� �訡��  */
#define DIN_SHOW1    pcnc[24] /* ���� �訡�� */
#define DIN_SHOW2    pcnc[25] /* */
#define ERRORS       pcnc[27] /* ����� */
#define NUM_ERROR    pcnc[26] /*         */
#define CHEK_SUM     pcnc[39] /* ����஫쭠� �㬬� */

/* ��।������ �����ᮢ ���ᨢ� NCPC */

#define _NCPC(x)      ncpc[(x)]
#define OKEY          ncpc[0] /* ��� � ����樨*/
#define QUIT_REF      ncpc[1] /* ���⢥ত���� �륧�� � ���� */
#define PR_SHPIND1    ncpc[2] /* ������� �ਧ���� 诨�����   1 */
#define PR_SHPIND2    ncpc[3] /* -----------------------------  2 */
#define COM_FEED1     ncpc[4] /* ������� ��६��.   1:+,-...4:+.- OSJM */
#define COM_FEED5     ncpc[5] /* ------------------ 5------ 8 -------- */
#define MODE_WORK     ncpc[6] /* ����� ࠡ���   */
#define MODE_CNC      ncpc[7] /* ------- ����  */
#define MODE_TEHN     ncpc[8] /* ------- �孮����� */
#define COD_FUNK1     ncpc[9] /* ��� �ᯮ����⥫쭮� �㭪樨*/
#define COD_FUNK2     ncpc[10] /*��� �ᯮ� �㭪権          */
#define FUNK11        ncpc[12] /* ���祭�� �ᯮ����⥫쭮� �㭪樨 M1 */
#define FUNK12        ncpc[13] /* ---------------------- 2-�� ���� */
#define MFUNK21       ncpc[14] /* ------------#---------�㭪樨 �2    */
#define MFUNK22       ncpc[15] /* ------------#-----------2-�� ����  */
#define MFUNK31       ncpc[16] /* ------------#---------�㭪樨 M3   */
#define MFUNK32       ncpc[17] /* ------------#----------@-�� ����  */
#define TFUNK11       ncpc[18]/* ���祭�� �ᯮ����� �㭪樨 �1     */
#define TFUNK12       ncpc[19] /*------------------------2-�� ���� */
#define TFUNK21       ncpc[20]/*---------------------- �2         */
#define TFUNK22       ncpc[21] /*-----------------------2-�� ���� */
#define SFUNK11       ncpc[22] /*���祭�� �㭪樨     S1          */
#define SFUNK12       ncpc[23] /*------------------------2-�� ����*/
#define SFUNK13       ncpc[24] /*-----------------------3-�� ���� */
#define SFUNK14       ncpc[25] /*-----------------------4-� ���� */
#define SFUNK21       ncpc[26]  /* ------------�㭪樨  S2        */
#define SFUNK22       ncpc[27] /*--------------------------2 �---*/
#define SFUNK23       ncpc[28] /*---------------------------3 �--*/
#define SFUNK24       ncpc[29] /*--------------------------4 �--*/
#define BUT_COD       ncpc[30] /* ��� ������ */
#define STROB_SHOW    ncpc[31] /* �ਧ���� ��।������� ���ᮢ */
#define ADR_SHOW1     ncpc[32] /* ���� ��६����� ��� ������樨  1 ���� */
#define ADR_SHOW2     ncpc[33] /* ------------------------------- 2 ---- */
#define END_SWICH1    ncpc[34] /* ����筨�� 1 ���� */
#define END_SWICH2    ncpc[35] /* --------- 2 ---- */
#define DNC1          ncpc[36] /* ������� DNC 1 ���� */
#define DNC2          ncpc[37] /* ----------- 2 ���� */
#define SUM_CHEK      ncpc[39] /* ����஫쭠� �㬬� */

extern BYTE  pcnc[SIZE_EXCHANGE];/* ���� ������ '�'�� PC */
extern BYTE  ncpc[SIZE_EXCHANGE];/* ------------- "�㤠" ---- */
     
                               
     
