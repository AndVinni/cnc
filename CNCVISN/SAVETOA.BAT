@echo ������  ���p������ �p��p��� CNC Vision ������
pkzip -P -r -x@filnosav.lst cncvisn.zip *.*
del %1:\cncvisn.zip
copy cncvisn.zip %1:\
del cncvisn.zip
