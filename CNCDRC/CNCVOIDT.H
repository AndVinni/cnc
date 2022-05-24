#ifdef __cplusplus
  void interrupt far taim(...);  /* программа обработки таймера */
#else
  void interrupt taim(void);
#endif
  void	       cnctmm(void),  /* обработка движения от кнопок */
	       cnctsm(void),  /* обработка останова движ. по +/- */
	       cnctstp(void), /* обработка стопового кольца таймера */
	       cnctbgmn(void), /* фор. задания для про-м интерп.*/
	       cnctcmm(void),  /* формирование пром.данных останова */
	       cnctbgn(void), /* обработка признака задания */
	       cnctio(void),  /* обработка задания с интерфейса */
	       cnctend(void), /* обработка конца кадра */
	       cnctcm(void),  /* продолжение движения */
	       cnctres(void), /* сброс задания */
	       cnctszr(void), /* обнуление буфера */
	       cnctnext(void),/* переход на следующий кадр */
	       cnctrpr();     /* связь по IRPR  */
    void      cnctcom2(void), /* связь с COM2 */
	      cnctirps(void), /* обработка ввода-вывода */
	      cnctinit(void), /* программа начальной инициализации */
	      cnctcbf(void),  /* чтение COM2 */
	      cnctcbff(void); /* формирование буфера ввода с COM2 */
    void      cnctmfun(),  /*  формирование М-функций  */
	      cnctcom1(void), /* программа передачи NC-PC */
	      cnctinfm(void); /* информационный блок */
    void      cnctrc2(),/* проверка готовности канала COM2 */
	      cnctrc1();  /*  проверка готовности канала COM1 */
