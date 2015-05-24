#include <stdio.h>
#include <math.h>
#include <stdlib.h>		//提供malloc()原型函数
#include <malloc.h>
#include <stdbool.h>

typedef struct Element
{
	double VA;			//稀疏矩阵中非0元素aij
	int IA;				//元素aij所在行
	int JA;				//元素aij所在列
	struct Element * NEXT;	//下一个元素的地址，最后一个元素的下一个元素地址为NULL
}Elem;

typedef struct SparseMatix
{
	struct Element * HEAD;	//稀疏矩阵第一个元素地址
	int Ni;			//稀疏矩阵行数
	int Nj;			//稀疏矩阵列数
	int NElement;	//非0元素个数
}SparseMat;

typedef SparseMat * Mat; //Mat类型指向一个稀疏矩阵链表

typedef struct LDUFactorTable	//LDU因子表
{
	Mat matL;
	Mat matD;
	Mat matU;
}matLDU;

typedef matLDU * LDU;	
//LDU类型指向一个含有三个稀疏矩阵指针的结构体
/*
Mat类型是指向稀疏矩阵类型的指针
函数调用稀疏矩阵时默认传递进函数的为指向稀疏矩阵指针的指针
新建稀疏矩阵:
1）声明稀疏矩阵指针 --> Mat newMat;
2）初始化稀疏矩阵   --> InitMat (&newMat, n, m);
   此处传入InitMat的是newMat的地址
*/

/*操作：  创建并初始化稀疏矩阵并且需要指定矩阵的行数n与列数n
 *操作前：PMat稀疏矩阵指针
 *操作后：该列表初始化为0值
 */
void InitMat (Mat * pMat, int n, int m);

/*操作：	  创建并初始化新元素
 *操作前：pElem为新元素指针
 *操作后：该元素及相关信息初始化为0值
 */
void InitElem (Elem * pElem);

/*操作：  确定列表是否为空
 *操作前：PMat指向一个已经初始化的矩阵
 *操作后：如果矩阵为空返回ture，否则返回false
 */
bool MatIsEmpty (const Mat * pMat);

/*操作：  为矩阵中新元素分配内存，并对其赋值
 *操作前：添加double类型的元素，pMat指向已经初始化后的指针
 *操作后：把新元素添加到链表的末尾
 */
bool addElement (double aij, int i, int j, Mat * pMat);

/*操作：  向链表添加新元素
 *操作前：传入新元素的值与行、列号，并且完成对新元素指针的初始化
 *操作后：把对新元素进行赋值，同时给定其行号与列号，并插入矩阵中
 */
bool addList (double aij, int i, int j, Mat * pMat, Elem * pNew);

/*操作：  移除矩阵中的元素Aij，但是不改变矩阵的大小
 *操作前：pMat是已经初始化的矩阵
 *操作后：在矩阵中移除元素Aij
 */
bool removeElement (Mat * pMat, int i, int j);

/*操作：	 检测删除元素是否成功
 *操作前：删除元素的Mat类型矩阵，但是没有更改Ni，Nj，NElement
 *操作后：重新计算Ni，Nj，NElement，并验证是否删除元素
 */
bool IsRomved (const Mat * pMat);

/*操作： 更改矩阵中的元素Aij，但是不改变矩阵的大小
*操作前：pMat是已经初始化的矩阵
*操作后：在矩阵中移除元素Aij
*/
bool updateElement (double aij, int i, int j, Mat * pMat);

/*操作：	 按行列查找元素，并返回double类型数值
*操作前：指向元素所在矩阵的指针pMat，元素的行号与列号i，j
*操作后：返回元素的值，元素在稀疏矩阵中不存在时返回0
*/
double findElemValue (const Mat * pMat, int i, int j);

/*操作：  计算稀疏矩阵的转置
*操作前：pMatA为稀疏矩阵
*操作后：返回A矩阵的转置矩阵的指针
*/
Mat TransposeMat (const Mat * pMatA);

/*操作：  计算稀疏矩阵与常数相乘
*操作前：pMatA为稀疏矩阵，K为常数
*操作后：返回A矩阵与K的乘积的稀疏矩阵的指针
*/
Mat productK (const Mat * pMatA, double K);

/*操作：  计算两个稀疏矩阵乘积
 *操作前：pMatA、pMatB为稀疏矩阵
 *操作后：返回A、B矩阵乘积的稀疏矩阵的指针
 */
Mat productMat (const Mat * pMatA, const Mat * pMatB);

/*操作：  计算两个稀疏矩阵相加
*操作前：pMatA、pMatB为稀疏矩阵
*操作后：返回A、B矩阵相加后的稀疏矩阵的指针
*/
Mat addMat (const Mat * pMatA, const Mat * pMatB);

/*操作：  计算两个稀疏矩阵相减
*操作前：pMatA、pMatB为稀疏矩阵
*操作后：返回A、B矩阵相减后的稀疏矩阵的指针
*/
Mat minusMat (const Mat * pMatA, const Mat * pMatB);

/*操作：  打印稀疏矩阵
 *操作前：pMat为初始化并含有元素的矩阵
 *操作后：向标准输出中打印稀疏矩阵
 */
void showMat (const Mat * pMat);

/*操作： 计算稀疏矩阵的LDU因子表
 *操作前：已经初始化的稀疏矩阵pMat
 *操作后：返回LDU因子表LDU类型指针
 */
LDU CalFactorT (Mat * pMat);

/*操作：  求解factorTable*x=pMat方程组的解
 *操作前：factorTalbe是因子表指针的指针，pMat是稀疏矩阵指针的指针
 *操作后：返回稀疏矩阵Mat类型指针
 */
Mat solveEqs (LDU * factorTable, Mat * pMat);