#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "PowerFlow.h"

void ImportData (RawData_Type * RawData)
{
	FILE * fpin, * fptmp;
	int ch;
	if ( (fpin = fopen (IEEE14, "r")) == NULL )
	{
		printf ("Can't open this file, Please check your Data Name!\n");
		printf ("Press Enter to Quit!!");
		getchar ();
		getchar ();
		exit (1);
	}
	fptmp = tmpfile ();		//������ʱ�ļ����ڴ���trim��������ļ�
	//char Line[303];
	//�򻺳��ļ���������
	/*
	//trim blank
	while ( (ch = getc (fpin)) != EOF )
	{
	if ( ch != ' ' )	//�����Ϊ�ո��ַ��ͻ����ַ�
	putc (ch, fptmp);
	else
	{
	//ֻ����һ���ո񣬺�����ַ�
	while ( (ch = getc (fpin)) == ' ' );
	putc (' ', fptmp);
	putc (ch, fptmp);
	}
	}
	*/
	while ( (ch = getc (fpin)) != EOF )
	{
		putc (ch, fptmp);
	}

	if ( fclose (fpin) != 0 )	//�ر������ļ����ж����Ƿ������ر�
	{
		printf ("Error in closing file\n");
		printf ("Press Enter to Quit!!");
		getchar ();
		getchar ();
		exit (2);
	}
	initialize_RawData (RawData, fptmp);
	/*
	rewind (fptmp);		//�ص��ļ�ͷ������������ļ�ָ�볬���ļ���Χ,�γ�����
	while ( (ch = getc (fptmp)) != EOF )
	{
	putc (ch, stdout);
	}
	rewind (fptmp);		//�ص��ļ�ͷ������������ļ�ָ�볬���ļ���Χ,�γ�����
	while ( fgets (Line, 303, fptmp ) != NULL )
	{
	//��ȡbus����
	if ( strncmp (Line, BUS, 16) == 0 )
	{
	for ( i = 0, fgets (Line, 303, fptmp); i < Nbus && (strncmp (Line, "-999", 4) !=0);	i++, fgets (Line, 303, fptmp))
	{
	printf ("%d,%s", i+1, Line);
	sscanf (Line, "%d %12[0-9A-Z-' ']s  %d", RawData->BusData[i].BusNum, RawData->BusData[i].Name,
	RawData->BusData[i].LFarea);
	sscanf (Line, "%4d %12[0-9-A-Z ]s %d %d %d %f %f %f %f %f %f %f %f %f %f %f %f %d",
	RawData->BusData[i].BusNum, RawData->BusData[i].Name, RawData->BusData[i].LFarea,
	RawData->BusData[i].LossZone, RawData->BusData[i].Type, RawData->BusData[i].Vol,
	RawData->BusData[i].Deg, RawData->BusData[i].PL, RawData->BusData[i].QL,
	RawData->BusData[i].PG, RawData->BusData[i].QG, RawData->BusData[i].BaseVol,
	RawData->BusData[i].DesiredVol, RawData->BusData[i].MaxVol,
	RawData->BusData[i].MinVol, RawData->BusData[i].ShuntG, RawData->BusData[i].ShuntB,
	RawData->BusData[i].RemoteCtrlBus);
	}
	}
	//��ȡBRANCH����
	if ( strncmp (Line, BRANCH, 19) == 0 )
	{
	for ( j = 0, fgets (Line, 303, fptmp); j < Nbranch && (strncmp (Line, "-999", 4) != 0); j++, fgets (Line, 303, fptmp))
	{
	printf ("%d,%s\n", j + 1, Line);
	}
	}
	}
	*/
	return;
}