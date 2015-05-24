#include <stdio.h>
#include <math.h>
#include <stdlib.h>		//�ṩmalloc()ԭ�ͺ���
#include <malloc.h>
#include <stdbool.h>

typedef struct Element
{
	double VA;			//ϡ������з�0Ԫ��aij
	int IA;				//Ԫ��aij������
	int JA;				//Ԫ��aij������
	struct Element * NEXT;	//��һ��Ԫ�صĵ�ַ�����һ��Ԫ�ص���һ��Ԫ�ص�ַΪNULL
}Elem;

typedef struct SparseMatix
{
	struct Element * HEAD;	//ϡ������һ��Ԫ�ص�ַ
	int Ni;			//ϡ���������
	int Nj;			//ϡ���������
	int NElement;	//��0Ԫ�ظ���
}SparseMat;

typedef SparseMat * Mat; //Mat����ָ��һ��ϡ���������

typedef struct LDUFactorTable	//LDU���ӱ�
{
	Mat matL;
	Mat matD;
	Mat matU;
}matLDU;

typedef matLDU * LDU;	
//LDU����ָ��һ����������ϡ�����ָ��Ľṹ��
/*
Mat������ָ��ϡ��������͵�ָ��
��������ϡ�����ʱĬ�ϴ��ݽ�������Ϊָ��ϡ�����ָ���ָ��
�½�ϡ�����:
1������ϡ�����ָ�� --> Mat newMat;
2����ʼ��ϡ�����   --> InitMat (&newMat, n, m);
   �˴�����InitMat����newMat�ĵ�ַ
*/

/*������  ��������ʼ��ϡ���������Ҫָ�����������n������n
 *����ǰ��PMatϡ�����ָ��
 *�����󣺸��б��ʼ��Ϊ0ֵ
 */
void InitMat (Mat * pMat, int n, int m);

/*������	  ��������ʼ����Ԫ��
 *����ǰ��pElemΪ��Ԫ��ָ��
 *�����󣺸�Ԫ�ؼ������Ϣ��ʼ��Ϊ0ֵ
 */
void InitElem (Elem * pElem);

/*������  ȷ���б��Ƿ�Ϊ��
 *����ǰ��PMatָ��һ���Ѿ���ʼ���ľ���
 *�������������Ϊ�շ���ture�����򷵻�false
 */
bool MatIsEmpty (const Mat * pMat);

/*������  Ϊ��������Ԫ�ط����ڴ棬�����丳ֵ
 *����ǰ�����double���͵�Ԫ�أ�pMatָ���Ѿ���ʼ�����ָ��
 *�����󣺰���Ԫ����ӵ������ĩβ
 */
bool addElement (double aij, int i, int j, Mat * pMat);

/*������  �����������Ԫ��
 *����ǰ��������Ԫ�ص�ֵ���С��кţ�������ɶ���Ԫ��ָ��ĳ�ʼ��
 *�����󣺰Ѷ���Ԫ�ؽ��и�ֵ��ͬʱ�������к����кţ������������
 */
bool addList (double aij, int i, int j, Mat * pMat, Elem * pNew);

/*������  �Ƴ������е�Ԫ��Aij�����ǲ��ı����Ĵ�С
 *����ǰ��pMat���Ѿ���ʼ���ľ���
 *�������ھ������Ƴ�Ԫ��Aij
 */
bool removeElement (Mat * pMat, int i, int j);

/*������	 ���ɾ��Ԫ���Ƿ�ɹ�
 *����ǰ��ɾ��Ԫ�ص�Mat���;��󣬵���û�и���Ni��Nj��NElement
 *���������¼���Ni��Nj��NElement������֤�Ƿ�ɾ��Ԫ��
 */
bool IsRomved (const Mat * pMat);

/*������ ���ľ����е�Ԫ��Aij�����ǲ��ı����Ĵ�С
*����ǰ��pMat���Ѿ���ʼ���ľ���
*�������ھ������Ƴ�Ԫ��Aij
*/
bool updateElement (double aij, int i, int j, Mat * pMat);

/*������	 �����в���Ԫ�أ�������double������ֵ
*����ǰ��ָ��Ԫ�����ھ����ָ��pMat��Ԫ�ص��к����к�i��j
*�����󣺷���Ԫ�ص�ֵ��Ԫ����ϡ������в�����ʱ����0
*/
double findElemValue (const Mat * pMat, int i, int j);

/*������  ����ϡ������ת��
*����ǰ��pMatAΪϡ�����
*�����󣺷���A�����ת�þ����ָ��
*/
Mat TransposeMat (const Mat * pMatA);

/*������  ����ϡ������볣�����
*����ǰ��pMatAΪϡ�����KΪ����
*�����󣺷���A������K�ĳ˻���ϡ������ָ��
*/
Mat productK (const Mat * pMatA, double K);

/*������  ��������ϡ�����˻�
 *����ǰ��pMatA��pMatBΪϡ�����
 *�����󣺷���A��B����˻���ϡ������ָ��
 */
Mat productMat (const Mat * pMatA, const Mat * pMatB);

/*������  ��������ϡ��������
*����ǰ��pMatA��pMatBΪϡ�����
*�����󣺷���A��B������Ӻ��ϡ������ָ��
*/
Mat addMat (const Mat * pMatA, const Mat * pMatB);

/*������  ��������ϡ��������
*����ǰ��pMatA��pMatBΪϡ�����
*�����󣺷���A��B����������ϡ������ָ��
*/
Mat minusMat (const Mat * pMatA, const Mat * pMatB);

/*������  ��ӡϡ�����
 *����ǰ��pMatΪ��ʼ��������Ԫ�صľ���
 *���������׼����д�ӡϡ�����
 */
void showMat (const Mat * pMat);

/*������ ����ϡ������LDU���ӱ�
 *����ǰ���Ѿ���ʼ����ϡ�����pMat
 *�����󣺷���LDU���ӱ�LDU����ָ��
 */
LDU CalFactorT (Mat * pMat);

/*������  ���factorTable*x=pMat������Ľ�
 *����ǰ��factorTalbe�����ӱ�ָ���ָ�룬pMat��ϡ�����ָ���ָ��
 *�����󣺷���ϡ�����Mat����ָ��
 */
Mat solveEqs (LDU * factorTable, Mat * pMat);