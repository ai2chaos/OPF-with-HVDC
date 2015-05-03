#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "PowerFlow.h"

void ImportData (RawData_Type * RawData)
{
	FILE * fpin, * fptmp;
	int ch;
	if ( (fpin = fopen (DataName, "r")) == NULL )
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
	return;
}