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
	//����ʱ�ļ�д��IEEE��׼��ʽ�ĳ�������
	while ( (ch = getc (fpin)) != EOF )
	{
		putc (ch, fptmp);
	}

	if ( fclose (fpin) != 0 )	//�ر������ļ����ж����Ƿ������ر�
	{
		printf ("Error in closing file %s\n", DataName);
		printf ("Press Enter to Quit!!");
		getchar ();
		getchar ();
		exit (2);
	}
	
	initialize_RawData (RawData, fptmp);	//��ʼ���������ݽṹ�岢��ֵ

	if ( fclose (fptmp) != 0 )	//�ر���ʱ�ļ����ж����Ƿ������ر�
	{
		printf ("Error in closing temporary file\n");
		printf ("Press Enter to Quit!!");
		getchar ();
		getchar ();
		exit (2);
	}
	return;
}