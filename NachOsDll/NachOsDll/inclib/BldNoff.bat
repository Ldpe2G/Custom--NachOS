:BldNoff
:  ���Ӳ�����������Դ�ļ�ֱ�ӱ���Ϊnoff��ʽ�ļ�
:  �磺BldNoff halt����Դ����halt.c������ļ�halt.noff
:-----------------------------------------------------

:���±���start.s
IF EXIST strt.s del strt.s
IF EXIST start.o del start.o
cpp0.exe -I../  start.s > strt.s
decstation-ultrix-as.exe -mips2 -o start.o strt.s

:�����Ŀ���ļ�
decstation-ultrix-gcc.exe -G 0 -O3 -ggdb -c -I ../  MergeSort.c -o MergeSort.o

:�����coff�ļ�
decstation-ultrix-ld.exe -T script -N start.o MergeSort.o -o MergeSort.coff


:��coff�ļ�ת��Ϊnoff�ļ�
decstation-ultrix-strip.exe MergeSort.coff
coff2noff.exe MergeSort.coff MergeSort.noff


:ɾ���м��ļ�
del strt.s MergeSort.o MergeSort.coff




