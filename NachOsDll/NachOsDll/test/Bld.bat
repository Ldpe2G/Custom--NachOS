:Bld:
:  ���Ӳ�����������Դ�ļ�����Ϊcoff�ļ�
:  �磺Bld halt����halt.c����Ϊhalt.coff
:--------------------------------------------------------

:���±���start.s
IF EXIST strt.s del strt.s
IF EXIST start.o del start.o
cpp0.exe -I../userprog -I../lib start.s > strt.s
decstation-ultrix-as.exe -mips2 -o start.o strt.s

:�����Ŀ���ļ�
decstation-ultrix-gcc.exe -G 0 -O3 -ggdb -c -I ../lib -I ../userprog -I ../threads %1.c -o %1.o

decstation-ultrix-ld.exe -T script -N start.o %1.o -o %1.coff

:ɾ���м��ļ�
del strt.s %1.o

