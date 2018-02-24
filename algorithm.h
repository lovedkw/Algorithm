// ��  �������ļ���������ѧϰʹ�ã�����������ҵ��;��лл��
// �����ˣ������
// ʱ  �䣺2018 �� 2 �� 24 ��

#pragma once

class CAlgorithm
{
private:
	int  m_nCnt;
	int  m_nSize;
	int* m_pnSequence;

private:
	// ������У����ĸ�λ�ÿ�ʼ���������
	std::string PrintSequence(int* pnSequence, int nBegin, int nCnt);

	// ���ڽ���Ԫ��
	void Swap(int* pnSequence, int i, int j);

	// ����ĳ��ʹ���Ϊ�󶥶�
	void HeapAdjust(int* pnSequence, int nNode, int nCnt);

	// �� pnSequence �� nLow ~ nHigh �������й鲢���� pnTmp ��
	void MSort(int* pnSequence, int* pnTmp, int nLow, int nHigh);

	// �� pnSequence �� nLow ~ nMid��nMid + 1 ~ nHigh �������й鲢���� pnTmp ��
	void MMerge(int* pnSequence, int* pnTmp, int nLow, int nMid, int nHigh);

	// �� pnSequence �� nLow ~ nHigh �������н��п�������
	void QSort(int* pnSequence, int nLow, int nHigh);

	// ���� pnSequence �� nLow ~ nHigh �������и�Ԫ�أ��Լ�������ֵ
	int QPartition(int* pnSequence, int nLow, int nHigh);

public:
	CAlgorithm();

	// �ȵ��øú���ʵ����һ�� CAlgorithm �����ٵ�������ĺ�������
	CAlgorithm(int* pnSequence, int nCnt);

	~CAlgorithm();

public:
	// ˳������
	int SequentialSearch(int nKey);

	// ˳�����ң��Ż���ʹ���ڱ������Ա���ÿ��ѭ�����ж��±��Ƿ�Խ�磩
	int SequentialSearch2(int nKey);

	// �������� - �۰���ң����ֲ��ң�ʹ�õ��Ƕ���������˼�룩
	int BinarySearch(int nKey);

	// �������� - ��ֵ����
	int InterpolationSearch(int nKey);

	// ���������� - ð������
	std::string BubbleSort();

	// ���������� - ð�������Ż���ʹ�ñ�ǣ�����������������������ѭ������Ҳ����Ϊʲôð���������������µ�ʱ�临�Ӷ�Ϊ O(n)��
	std::string BubbleSort2();

	// ���������� - ��������
	std::string QuickSort();

	// ѡ�������� - ��ѡ������
	std::string SelectSort();

	// ѡ�������� - ������
	std::string HeapSort();

	// ���������� - ֱ�Ӳ�������
	std::string InsertSort();

	// ���������� - ֱ�Ӳ��������Ż���ʹ���ڱ������Ա���ÿ��ѭ�����ж��±��Ƿ�Խ�磩
	std::string InsertSort2();

	// ���������� - ϣ������
	std::string ShellSort();

	// �鲢������ - �鲢����
	std::string MergeSort();
};
