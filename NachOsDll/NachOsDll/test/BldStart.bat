:BldStart
:  ����start.sΪstart.o
:----------------------------------------------------

:����Ѵ��ڣ���ɾ��
IF EXIST strt.s del strt.s
IF EXIST start.o del start.o

:��start.s����Ԥ����,������м��ļ�strt.s
cpp0.exe -I../userprog -I../lib start.s > strt.s

:���м��ļ�strt.s���л��,�õ�Ŀ���ļ�start.o
decstation-ultrix-as.exe -mips2 -o start.o strt.s

:ɾ���м��ļ�
del strt.s




