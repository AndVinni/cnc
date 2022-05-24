@echo	‘®åp ­¥­¨¥ ¯p®£p ¬¬ CNC
	pkzip -P -r -x@filnosav.lst c:\cnc.zip c:\cnc\*.*
	del %1:\cnc.zip
        copy c:\cnc.zip %1:\cnc.zip
	del c:\cnc.zip
