#include "stdafx.h"
#include "Algorithm.h"

// 输出序列，从哪个位置开始，输出几个
std::string CAlgorithm::PrintSequence(int* pnSequence, int nBegin, int nCnt)
{
	std::string strRet = "";
	for (int i = 0; i < nCnt; ++i)
	{
		strRet += std::to_string(pnSequence[nBegin + i]) + ", ";
	}

	return strRet.substr(0, strRet.length() - 2);
}

// 用于交换元素
void CAlgorithm::Swap(int* pnSequence, int i, int j)
{
	// 该方法在自己和自己进行交换时会发生问题，因为自己异或自己的结果是 0，请酌情使用
	// 形如：a = a ^ b; b = b ^ a; a = a ^ b;
// 	pnSequence[i] = pnSequence[i] ^ pnSequence[j];
// 	pnSequence[j] = pnSequence[j] ^ pnSequence[i];
// 	pnSequence[i] = pnSequence[i] ^ pnSequence[j];

	int nTmp = pnSequence[i];
	pnSequence[i] = pnSequence[j];
	pnSequence[j] = nTmp;

	return;
}

// 调整某堆使其成为大顶堆
void CAlgorithm::HeapAdjust(int* pnSequence, int nNode, int nCnt)
{
	// 保存该根结点的值
	int nTmp = pnSequence[nNode];
	
	// 循环遍历该根结点的孩子结点（孩子结点的孩子结点。。。）
	for (int i = 2 * nNode + 1; i < nCnt; i = 2 * i + 1)
	{
		// 若该孩子结点有兄弟结点，且兄弟结点的值更大，则定位到兄弟结点（其实就是定位到值较大的孩子结点）
		if (i < nCnt - 1 && pnSequence[i] < pnSequence[i + 1])
			++i;

		// 若该根结点的值大于等于其孩子结点中的较大值，则说明本身就已经满足要求，此时直接退出循环
		if (nTmp >= pnSequence[i])
			break;

		// 将较大孩子结点的值赋给该根结点
		pnSequence[nNode] = pnSequence[i];

		// 使该根结点指向较大孩子结点（注意这里不是用的 Swap，而是先留出个空位，到最后才重新赋值，这样可以提高效率）
		nNode = i;
	}

	// 将该根结点的值赋给最终的指定位置
	pnSequence[nNode] = nTmp;

	return;
}

// 将 pnSequence 中 nLow ~ nHigh 的子序列归并排序到 pnTmp 中
void CAlgorithm::MSort(int* pnSequence, int* pnTmp, int nLow, int nHigh)
{
	// nLow == nHigh 时，表示只有一个元素，此时子序列必然是有序的，因此不用调用该函数
	if (nLow < nHigh)
	{
		// 取 nLow 与 nHigh 的中间位置作为分割点
		int nMid = (nLow + nHigh) / 2;

		// 对左子序列进行归并排序
		MSort(pnSequence, pnTmp, nLow, nMid);

		// 对右子序列进行归并排序
		MSort(pnSequence, pnTmp, nMid + 1, nHigh);

		// 将 pnSequence 中 nLow ~ nMid、nMid + 1 ~ nHigh 的子序列归并排序到 pnTmp 中
		MMerge(pnSequence, pnTmp, nLow, nMid, nHigh);
	}

	return;
}

// 将 pnSequence 中 nLow ~ nMid、nMid + 1 ~ nHigh 的子序列归并排序到 pnTmp 中
void CAlgorithm::MMerge(int* pnSequence, int* pnTmp, int nLow, int nMid, int nHigh)
{
	// 左子序列指针
	int i = nLow;

	// 右子序列指针
	int j = nMid + 1;

	// pnTmp 指针，其实也就是本次调用该函数时所排序的元素个数
	int k = 0;
	
	// 将 pnSequence 中的元素归并排序到 pnTmp
	while (i <= nMid && j <= nHigh)
		if (pnSequence[i] <= pnSequence[j])
			pnTmp[k++] = pnSequence[i++];
		else
			pnTmp[k++] = pnSequence[j++];

	// 将左子序列中的剩余元素放入 pnTmp
	while (i <= nMid)
		pnTmp[k++] = pnSequence[i++];

	// 将右子序列中的剩余元素放入 pnTmp
	while (j <= nHigh)
		pnTmp[k++] = pnSequence[j++];

	// 将归并排序后的子序列放回 pnSequence，下次排序时会用到
	for (i = 0; i < k; ++i)
		pnSequence[nLow + i] = pnTmp[i];

	return;
}

// 对 pnSequence 中 nLow ~ nHigh 的子序列进行快速排序
void CAlgorithm::QSort(int* pnSequence, int nLow, int nHigh)
{
// 	if (nLow < nHigh)
// 	{
// 		// 计算枢轴值
// 		int nPivot = QPartition(pnSequence, nLow, nHigh);
// 
// 		// 对左子序列进行快速排序
// 		QSort(pnSequence, nLow, nPivot - 1);
// 
// 		// 对右子序列进行快速排序
// 		QSort(pnSequence, nPivot + 1, nHigh);
// 	}

	// 该算法是尾递归形式，因此可以进行优化
	while (nLow < nHigh)
	{
		// 计算枢轴值
		int nPivot = QPartition(pnSequence, nLow, nHigh);

		// 对左子序列进行快速排序
		QSort(pnSequence, nLow, nPivot - 1);

		// 尾递归的优化形式
		nLow = nPivot + 1;
	}

	return;
}

// 交换 pnSequence 中 nLow ~ nHigh 的子序列各元素，以计算枢轴值
int CAlgorithm::QPartition(int* pnSequence, int nLow, int nHigh)
{
	// 选取 nLow 位置的值作为枢轴
	int nPivotKey = pnSequence[nLow];

	// 当 nLow < nHigh 时，开始循环
	while (nLow < nHigh)
	{
		while (nLow < nHigh && pnSequence[nHigh] >= nPivotKey)
			--nHigh;

		pnSequence[nLow] = pnSequence[nHigh];

		while (nLow < nHigh && pnSequence[nLow] <= nPivotKey)
			++nLow;

		pnSequence[nHigh] = pnSequence[nLow];
	}

	// 将枢轴放回去
	pnSequence[nLow] = nPivotKey;

	// 此处返回 nHigh 也是一样的
	return nLow;
}

CAlgorithm::CAlgorithm()
{

}

CAlgorithm::CAlgorithm(int* pnSequence, int nCnt)
{
	m_nCnt = nCnt;
	m_nSize = sizeof(int) * nCnt;
	m_pnSequence = pnSequence;
}

CAlgorithm::~CAlgorithm()
{

}

// 顺序表查找
int CAlgorithm::SequentialSearch(int nKey)
{
	for (int i = 0; i < m_nCnt; ++i)
		if (nKey == m_pnSequence[i])
			return i;

	return -1;
}

// 顺序表查找（优化：使用哨兵，可以避免每次循环都判断下标是否越界）
int CAlgorithm::SequentialSearch2(int nKey)
{
	int* p = new int[m_nCnt + 1];
	ZeroMemory(p, m_nSize + sizeof(int)); // 等价于 (m_nCnt + 1) * sizeof(int)
	CopyMemory(p + 1, m_pnSequence, m_nSize);

	p[0] = nKey;
	int i = m_nCnt;
	for (; nKey != p[i]; --i);
// 	while (nKey != p[i])
// 		--i;

	delete[] p;

	return --i;
}

// 有序表查找 - 折半查找（二分查找，使用的是二叉排序树思想）
int CAlgorithm::BinarySearch(int nKey)
{
	int nLow = 0, nMid = 0, nHigh = m_nCnt - 1;

	// 注意此处是小于等于，一定不能写小于
	while (nLow <= nHigh)
	{
		// 取 nLow 与 nHigh 的中间位置作为首次查找的位置
		nMid = (nLow + nHigh) / 2;

		if (nKey < m_pnSequence[nMid]) // 若待查找的值小于 nMid 所在位置的值，则继续查找左子序列
			nHigh = nMid - 1;
		else if (nKey > m_pnSequence[nMid]) // 若待查找的值大于 nMid 所在位置的值，则继续查找右子序列
			nLow = nMid + 1;
		else // 若待查找的值等于 nMid 所在位置的值，则直接返回 nMid
			return nMid;
	}

	// 若未查找到待查找的值，则返回 -1
	return -1;
}

// 有序表查找 - 插值查找
int CAlgorithm::InterpolationSearch(int nKey)
{
	int nLow = 0, nMid = 0, nHigh = m_nCnt - 1;
	while (nLow <= nHigh)
	{
		// 关键就是这个插值公式的系数：(nKey - m_pnSequence[nLow]) / (m_pnSequence[nHigh] - m_pnSequence[nLow])
		nMid = nLow + (nKey - m_pnSequence[nLow]) / (m_pnSequence[nHigh] - m_pnSequence[nLow]) * (nHigh - nLow);
		if (nKey < m_pnSequence[nMid])
			nHigh = nMid - 1;
		else if (nKey > m_pnSequence[nMid])
			nLow = nMid + 1;
		else
			return nMid;
	}

	return -1;
}

// 交换排序类 - 冒泡排序
std::string CAlgorithm::BubbleSort()
{
	int* p = new int[m_nCnt];
	ZeroMemory(p, m_nSize);
	CopyMemory(p, m_pnSequence, m_nSize);

// 	// 优先确定最大值
// 	for (int i = 0; i < m_nCnt - 1; ++i)
// 		for (int j = 0; j < m_nCnt - 1 - i; ++j)
// 			if (p[j] > p[j + 1])
// 				Swap(p, j, j + 1);

	// 优先确定最小值
	for (int i = 0; i < m_nCnt - 1; ++i)
		for (int j = m_nCnt - 2; j >= i; --j)
			if (p[j] > p[j + 1])
				Swap(p, j, j + 1);

	// 输出序列
	std::string strRet = PrintSequence(p, 0, m_nCnt);

	delete[] p;

	return strRet;
}

// 交换排序类 - 冒泡排序（优化：使用标记，可以跳过序列有序后的所有循环，这也就是为什么冒泡排序在最好情况下的时间复杂度为 O(n)）
std::string CAlgorithm::BubbleSort2()
{
	int* p = new int[m_nCnt];
	ZeroMemory(p, m_nSize);
	CopyMemory(p, m_pnSequence, m_nSize);

	bool bFlag = true;
	for (int i = 0; i < m_nCnt - 1 && bFlag; ++i)
	{
		bFlag = false;
		for (int j = m_nCnt - 2; j >= i; --j)
			if (p[j] > p[j + 1])
			{
				Swap(p, j, j + 1);
				bFlag = true;
			}
	}

	// 输出序列
	std::string strRet = PrintSequence(p, 0, m_nCnt);

	delete[] p;

	return strRet;
}

// 交换排序类 - 快速排序
std::string CAlgorithm::QuickSort()
{
	int* p = new int[m_nCnt];
	ZeroMemory(p, m_nSize);
	CopyMemory(p, m_pnSequence, m_nSize);

	// 快速排序
	QSort(p, 0, m_nCnt - 1);

	// 输出序列
	std::string strRet = PrintSequence(p, 0, m_nCnt);

	delete[] p;

	return strRet;
}

// 选择排序类 - 简单选择排序
std::string CAlgorithm::SelectSort()
{
	int* p = new int[m_nCnt];
	ZeroMemory(p, m_nSize);
	CopyMemory(p, m_pnSequence, m_nSize);

	int nMin = 0;
	for (int i = 0; i < m_nCnt - 1; ++i)
	{
		nMin = i;
		for (int j = i + 1; j < m_nCnt; ++j)
			if (p[nMin] > p[j])
				nMin = j;

		if (nMin != i)
			Swap(p, i, nMin);
	}

	// 输出序列
	std::string strRet = PrintSequence(p, 0, m_nCnt);

	delete[] p;

	return strRet;
}

// 选择排序类 - 堆排序
std::string CAlgorithm::HeapSort()
{
	int* p = new int[m_nCnt];
	ZeroMemory(p, m_nSize);
	CopyMemory(p, m_pnSequence, m_nSize);

	// 建堆
	for (int i = m_nCnt / 2 - 1; i >= 0; --i)
		HeapAdjust(p, i, m_nCnt);

	// 循环交换堆顶元素与堆尾元素，并调整堆
	for (int i = m_nCnt - 1; i > 0; --i)
	{
		Swap(p, 0, i);
		HeapAdjust(p, 0, i);
	}

	// 输出序列
	std::string strRet = PrintSequence(p, 0, m_nCnt);

	delete[] p;

	return strRet;
}

// 插入排序类 - 直接插入排序
std::string CAlgorithm::InsertSort()
{
	int* p = new int[m_nCnt];
	ZeroMemory(p, m_nSize);
	CopyMemory(p, m_pnSequence, m_nSize);
	
	int j = 0, nTmp = 0;
	for (int i = 1; i < m_nCnt; ++i)
		if (p[i] < p[i - 1])
		{
			nTmp = p[i];
			for (j = i - 1; j >= 0 && p[j] > nTmp; --j)
				p[j + 1] = p[j];

			p[j + 1] = nTmp;
		}

	// 输出序列
	std::string strRet = PrintSequence(p, 0, m_nCnt);

	delete[] p;

	return strRet;
}

// 插入排序类 - 直接插入排序（优化：使用哨兵，可以避免每次循环都判断下标是否越界）
std::string CAlgorithm::InsertSort2()
{
	int* p = new int[m_nCnt + 1];
	ZeroMemory(p, m_nSize + sizeof(int)); // 等价于 (m_nCnt + 1) * sizeof(int)
	CopyMemory(p + 1, m_pnSequence, m_nSize);

	int j = 0;
	for (int i = 2; i < m_nCnt + 1; ++i)
		if (p[i] < p[i - 1])
		{
			p[0] = p[i];
			for (j = i - 1; p[j] > p[0]; --j)
				p[j + 1] = p[j];

			p[j + 1] = p[0];
		}

	// 输出序列
	std::string strRet = PrintSequence(p, 1, m_nCnt);

	delete[] p;

	return strRet;
}

// 插入排序类 - 希尔排序
std::string CAlgorithm::ShellSort()
{
	int* p = new int[m_nCnt];
	ZeroMemory(p, m_nSize);
	CopyMemory(p, m_pnSequence, m_nSize);

	int j = 0, nInc = m_nCnt, nTmp = 0;
	do 
	{
		nInc = nInc / 3 + 1;
		for (int i = nInc; i < m_nCnt; ++i)
			if (p[i] < p[i - nInc])
			{
				nTmp = p[i];
				for (j = i - nInc; j >= 0 && p[j] > nTmp; j -= nInc)
					p[j + nInc] = p[j];

				p[j + nInc] = nTmp;
			}
	} while (nInc > 1);

	// 输出序列
	std::string strRet = PrintSequence(p, 0, m_nCnt);

	delete[] p;

	return strRet;
}

// 归并排序类 - 归并排序
std::string CAlgorithm::MergeSort()
{
	int* p = new int[m_nCnt];
	ZeroMemory(p, m_nSize);
	CopyMemory(p, m_pnSequence, m_nSize);

	int* pTmp = new int[m_nCnt];
	ZeroMemory(pTmp, m_nSize);

	// 归并排序
	MSort(p, pTmp, 0, m_nCnt - 1);

	// 输出序列
	std::string strRet = PrintSequence(p, 0, m_nCnt);

	delete[] p;
	delete[] pTmp;

	return strRet;
}
