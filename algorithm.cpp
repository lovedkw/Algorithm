#include "stdafx.h"
#include "Algorithm.h"

// ������У����ĸ�λ�ÿ�ʼ���������
std::string CAlgorithm::PrintSequence(int* pnSequence, int nBegin, int nCnt)
{
	std::string strRet = "";
	for (int i = 0; i < nCnt; ++i)
	{
		strRet += std::to_string(pnSequence[nBegin + i]) + ", ";
	}

	return strRet.substr(0, strRet.length() - 2);
}

// ���ڽ���Ԫ��
void CAlgorithm::Swap(int* pnSequence, int i, int j)
{
	// �÷������Լ����Լ����н���ʱ�ᷢ�����⣬��Ϊ�Լ�����Լ��Ľ���� 0��������ʹ��
	// ���磺a = a ^ b; b = b ^ a; a = a ^ b;
// 	pnSequence[i] = pnSequence[i] ^ pnSequence[j];
// 	pnSequence[j] = pnSequence[j] ^ pnSequence[i];
// 	pnSequence[i] = pnSequence[i] ^ pnSequence[j];

	int nTmp = pnSequence[i];
	pnSequence[i] = pnSequence[j];
	pnSequence[j] = nTmp;

	return;
}

// ����ĳ��ʹ���Ϊ�󶥶�
void CAlgorithm::HeapAdjust(int* pnSequence, int nNode, int nCnt)
{
	// ����ø�����ֵ
	int nTmp = pnSequence[nNode];
	
	// ѭ�������ø����ĺ��ӽ�㣨���ӽ��ĺ��ӽ�㡣������
	for (int i = 2 * nNode + 1; i < nCnt; i = 2 * i + 1)
	{
		// ���ú��ӽ�����ֵܽ�㣬���ֵܽ���ֵ������λ���ֵܽ�㣨��ʵ���Ƕ�λ��ֵ�ϴ�ĺ��ӽ�㣩
		if (i < nCnt - 1 && pnSequence[i] < pnSequence[i + 1])
			++i;

		// ���ø�����ֵ���ڵ����亢�ӽ���еĽϴ�ֵ����˵��������Ѿ�����Ҫ�󣬴�ʱֱ���˳�ѭ��
		if (nTmp >= pnSequence[i])
			break;

		// ���ϴ��ӽ���ֵ�����ø����
		pnSequence[nNode] = pnSequence[i];

		// ʹ�ø����ָ��ϴ��ӽ�㣨ע�����ﲻ���õ� Swap����������������λ�����������¸�ֵ�������������Ч�ʣ�
		nNode = i;
	}

	// ���ø�����ֵ�������յ�ָ��λ��
	pnSequence[nNode] = nTmp;

	return;
}

// �� pnSequence �� nLow ~ nHigh �������й鲢���� pnTmp ��
void CAlgorithm::MSort(int* pnSequence, int* pnTmp, int nLow, int nHigh)
{
	// nLow == nHigh ʱ����ʾֻ��һ��Ԫ�أ���ʱ�����б�Ȼ������ģ���˲��õ��øú���
	if (nLow < nHigh)
	{
		// ȡ nLow �� nHigh ���м�λ����Ϊ�ָ��
		int nMid = (nLow + nHigh) / 2;

		// ���������н��й鲢����
		MSort(pnSequence, pnTmp, nLow, nMid);

		// ���������н��й鲢����
		MSort(pnSequence, pnTmp, nMid + 1, nHigh);

		// �� pnSequence �� nLow ~ nMid��nMid + 1 ~ nHigh �������й鲢���� pnTmp ��
		MMerge(pnSequence, pnTmp, nLow, nMid, nHigh);
	}

	return;
}

// �� pnSequence �� nLow ~ nMid��nMid + 1 ~ nHigh �������й鲢���� pnTmp ��
void CAlgorithm::MMerge(int* pnSequence, int* pnTmp, int nLow, int nMid, int nHigh)
{
	// ��������ָ��
	int i = nLow;

	// ��������ָ��
	int j = nMid + 1;

	// pnTmp ָ�룬��ʵҲ���Ǳ��ε��øú���ʱ�������Ԫ�ظ���
	int k = 0;
	
	// �� pnSequence �е�Ԫ�ع鲢���� pnTmp
	while (i <= nMid && j <= nHigh)
		if (pnSequence[i] <= pnSequence[j])
			pnTmp[k++] = pnSequence[i++];
		else
			pnTmp[k++] = pnSequence[j++];

	// �����������е�ʣ��Ԫ�ط��� pnTmp
	while (i <= nMid)
		pnTmp[k++] = pnSequence[i++];

	// �����������е�ʣ��Ԫ�ط��� pnTmp
	while (j <= nHigh)
		pnTmp[k++] = pnSequence[j++];

	// ���鲢�����������зŻ� pnSequence���´�����ʱ���õ�
	for (i = 0; i < k; ++i)
		pnSequence[nLow + i] = pnTmp[i];

	return;
}

// �� pnSequence �� nLow ~ nHigh �������н��п�������
void CAlgorithm::QSort(int* pnSequence, int nLow, int nHigh)
{
// 	if (nLow < nHigh)
// 	{
// 		// ��������ֵ
// 		int nPivot = QPartition(pnSequence, nLow, nHigh);
// 
// 		// ���������н��п�������
// 		QSort(pnSequence, nLow, nPivot - 1);
// 
// 		// ���������н��п�������
// 		QSort(pnSequence, nPivot + 1, nHigh);
// 	}

	// ���㷨��β�ݹ���ʽ����˿��Խ����Ż�
	while (nLow < nHigh)
	{
		// ��������ֵ
		int nPivot = QPartition(pnSequence, nLow, nHigh);

		// ���������н��п�������
		QSort(pnSequence, nLow, nPivot - 1);

		// β�ݹ���Ż���ʽ
		nLow = nPivot + 1;
	}

	return;
}

// ���� pnSequence �� nLow ~ nHigh �������и�Ԫ�أ��Լ�������ֵ
int CAlgorithm::QPartition(int* pnSequence, int nLow, int nHigh)
{
	// ѡȡ nLow λ�õ�ֵ��Ϊ����
	int nPivotKey = pnSequence[nLow];

	// �� nLow < nHigh ʱ����ʼѭ��
	while (nLow < nHigh)
	{
		while (nLow < nHigh && pnSequence[nHigh] >= nPivotKey)
			--nHigh;

		pnSequence[nLow] = pnSequence[nHigh];

		while (nLow < nHigh && pnSequence[nLow] <= nPivotKey)
			++nLow;

		pnSequence[nHigh] = pnSequence[nLow];
	}

	// ������Ż�ȥ
	pnSequence[nLow] = nPivotKey;

	// �˴����� nHigh Ҳ��һ����
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

// ˳������
int CAlgorithm::SequentialSearch(int nKey)
{
	for (int i = 0; i < m_nCnt; ++i)
		if (nKey == m_pnSequence[i])
			return i;

	return -1;
}

// ˳�����ң��Ż���ʹ���ڱ������Ա���ÿ��ѭ�����ж��±��Ƿ�Խ�磩
int CAlgorithm::SequentialSearch2(int nKey)
{
	int* p = new int[m_nCnt + 1];
	ZeroMemory(p, m_nSize + sizeof(int)); // �ȼ��� (m_nCnt + 1) * sizeof(int)
	CopyMemory(p + 1, m_pnSequence, m_nSize);

	p[0] = nKey;
	int i = m_nCnt;
	for (; nKey != p[i]; --i);
// 	while (nKey != p[i])
// 		--i;

	delete[] p;

	return --i;
}

// �������� - �۰���ң����ֲ��ң�ʹ�õ��Ƕ���������˼�룩
int CAlgorithm::BinarySearch(int nKey)
{
	int nLow = 0, nMid = 0, nHigh = m_nCnt - 1;

	// ע��˴���С�ڵ��ڣ�һ������дС��
	while (nLow <= nHigh)
	{
		// ȡ nLow �� nHigh ���м�λ����Ϊ�״β��ҵ�λ��
		nMid = (nLow + nHigh) / 2;

		if (nKey < m_pnSequence[nMid]) // �������ҵ�ֵС�� nMid ����λ�õ�ֵ�������������������
			nHigh = nMid - 1;
		else if (nKey > m_pnSequence[nMid]) // �������ҵ�ֵ���� nMid ����λ�õ�ֵ�������������������
			nLow = nMid + 1;
		else // �������ҵ�ֵ���� nMid ����λ�õ�ֵ����ֱ�ӷ��� nMid
			return nMid;
	}

	// ��δ���ҵ������ҵ�ֵ���򷵻� -1
	return -1;
}

// �������� - ��ֵ����
int CAlgorithm::InterpolationSearch(int nKey)
{
	int nLow = 0, nMid = 0, nHigh = m_nCnt - 1;
	while (nLow <= nHigh)
	{
		// �ؼ����������ֵ��ʽ��ϵ����(nKey - m_pnSequence[nLow]) / (m_pnSequence[nHigh] - m_pnSequence[nLow])
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

// ���������� - ð������
std::string CAlgorithm::BubbleSort()
{
	int* p = new int[m_nCnt];
	ZeroMemory(p, m_nSize);
	CopyMemory(p, m_pnSequence, m_nSize);

// 	// ����ȷ�����ֵ
// 	for (int i = 0; i < m_nCnt - 1; ++i)
// 		for (int j = 0; j < m_nCnt - 1 - i; ++j)
// 			if (p[j] > p[j + 1])
// 				Swap(p, j, j + 1);

	// ����ȷ����Сֵ
	for (int i = 0; i < m_nCnt - 1; ++i)
		for (int j = m_nCnt - 2; j >= i; --j)
			if (p[j] > p[j + 1])
				Swap(p, j, j + 1);

	// �������
	std::string strRet = PrintSequence(p, 0, m_nCnt);

	delete[] p;

	return strRet;
}

// ���������� - ð�������Ż���ʹ�ñ�ǣ�����������������������ѭ������Ҳ����Ϊʲôð���������������µ�ʱ�临�Ӷ�Ϊ O(n)��
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

	// �������
	std::string strRet = PrintSequence(p, 0, m_nCnt);

	delete[] p;

	return strRet;
}

// ���������� - ��������
std::string CAlgorithm::QuickSort()
{
	int* p = new int[m_nCnt];
	ZeroMemory(p, m_nSize);
	CopyMemory(p, m_pnSequence, m_nSize);

	// ��������
	QSort(p, 0, m_nCnt - 1);

	// �������
	std::string strRet = PrintSequence(p, 0, m_nCnt);

	delete[] p;

	return strRet;
}

// ѡ�������� - ��ѡ������
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

	// �������
	std::string strRet = PrintSequence(p, 0, m_nCnt);

	delete[] p;

	return strRet;
}

// ѡ�������� - ������
std::string CAlgorithm::HeapSort()
{
	int* p = new int[m_nCnt];
	ZeroMemory(p, m_nSize);
	CopyMemory(p, m_pnSequence, m_nSize);

	// ����
	for (int i = m_nCnt / 2 - 1; i >= 0; --i)
		HeapAdjust(p, i, m_nCnt);

	// ѭ�������Ѷ�Ԫ�����βԪ�أ���������
	for (int i = m_nCnt - 1; i > 0; --i)
	{
		Swap(p, 0, i);
		HeapAdjust(p, 0, i);
	}

	// �������
	std::string strRet = PrintSequence(p, 0, m_nCnt);

	delete[] p;

	return strRet;
}

// ���������� - ֱ�Ӳ�������
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

	// �������
	std::string strRet = PrintSequence(p, 0, m_nCnt);

	delete[] p;

	return strRet;
}

// ���������� - ֱ�Ӳ��������Ż���ʹ���ڱ������Ա���ÿ��ѭ�����ж��±��Ƿ�Խ�磩
std::string CAlgorithm::InsertSort2()
{
	int* p = new int[m_nCnt + 1];
	ZeroMemory(p, m_nSize + sizeof(int)); // �ȼ��� (m_nCnt + 1) * sizeof(int)
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

	// �������
	std::string strRet = PrintSequence(p, 1, m_nCnt);

	delete[] p;

	return strRet;
}

// ���������� - ϣ������
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

	// �������
	std::string strRet = PrintSequence(p, 0, m_nCnt);

	delete[] p;

	return strRet;
}

// �鲢������ - �鲢����
std::string CAlgorithm::MergeSort()
{
	int* p = new int[m_nCnt];
	ZeroMemory(p, m_nSize);
	CopyMemory(p, m_pnSequence, m_nSize);

	int* pTmp = new int[m_nCnt];
	ZeroMemory(pTmp, m_nSize);

	// �鲢����
	MSort(p, pTmp, 0, m_nCnt - 1);

	// �������
	std::string strRet = PrintSequence(p, 0, m_nCnt);

	delete[] p;
	delete[] pTmp;

	return strRet;
}
