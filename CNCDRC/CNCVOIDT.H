#if !defined(___DEFS_H)
#include <_defs.h>
#endif

#ifdef __cplusplus
  void interrupt _FAR taim(...);  /* �ணࠬ�� ��ࠡ�⪨ ⠩��� */
#else
  void interrupt taim(void);
#endif
  void	   cnctmm(void),  /* ��ࠡ�⪠ �������� �� ������ */
	       cnctsm(void),  /* ��ࠡ�⪠ ��⠭��� ����. �� +/- */
	       cnctstp(void), /* ��ࠡ�⪠ �⮯����� ����� ⠩��� */
	       cnctbgmn(void), /* ��. ������� ��� ��-� ����.*/
	       cnctcmm(void),  /* �ନ஢���� �஬.������ ��⠭��� */
	       cnctbgn(void), /* ��ࠡ�⪠ �ਧ���� ������� */
	       cnctio(void),  /* ��ࠡ�⪠ ������� � ����䥩� */
	       cnctend(void), /* ��ࠡ�⪠ ���� ���� */
	       cnctcm(void),  /* �த������� �������� */
	       cnctres(void), /* ��� ������� */
	       cnctszr(void), /* ���㫥��� ���� */
	       cnctnext(void),/* ���室 �� ᫥���騩 ���� */
	       cnctrpr();     /* ��� �� IRPR  */
    void      cnctcom2(void), /* ��� � COM2 */
	      cnctirps(void), /* ��ࠡ�⪠ �����-�뢮�� */
	      cnctinit(void), /* �ணࠬ�� ��砫쭮� ���樠����樨 */
	      cnctcbf(void),  /* �⥭�� COM2 */
	      cnctcbff(void); /* �ନ஢���� ���� ����� � COM2 */
    void      cnctmfun(),  /*  �ନ஢���� �-�㭪権  */
	      cnctcom1(void), /* �ணࠬ�� ��।�� NC-PC */
	      cnctinfm(void); /* ���ଠ樮��� ���� */
    void      cnctrc2(),/* �஢�ઠ ��⮢���� ������ COM2 */
	      cnctrc1();  /*  �஢�ઠ ��⮢���� ������ COM1 */
