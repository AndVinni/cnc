   BOOL       cncrrdp(void);  /* чтение параметров */

	 /* п/п программ распаковки УП */

	  /* п/п диспетчера - CNCCAMP  */
    void       main(void),   /* CNCCAMP */
	       cnccmemv(void);

    void       cnccman(void),/* формирование задания по к. +/- */
	       cnccfbt(INT ), /* форм.буфера без задания строки */
	       cnccauto(void),/* форм. задания в авто-ом  режиме */
	       cncctok(void),/* выход на эквидистанту */
	       cnccstr(void),/* форм.задания в преднаборе */
	       cnccvost(void),
	       cnccoutk(void),/* форм.задания отвода от эквид.контура*/
	       cnccref(void), /* выход в исходное */
	       cnccrm(void),  /* восстановление работы */
	       cnccfrs(INT); /* форм.данных интерполяции */

