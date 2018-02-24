// 声  明：该文件仅供交流学习使用，请勿用于商业用途，谢谢！
// 制作人：丁可炜
// 时  间：2018 年 2 月 24 日

#pragma once

class CAlgorithm
{
private:
	int  m_nCnt;
	int  m_nSize;
	int* m_pnSequence;

private:
	// 输出序列，从哪个位置开始，输出几个
	std::string PrintSequence(int* pnSequence, int nBegin, int nCnt);

	// 用于交换元素
	void Swap(int* pnSequence, int i, int j);

	// 调整某堆使其成为大顶堆
	void HeapAdjust(int* pnSequence, int nNode, int nCnt);

	// 将 pnSequence 中 nLow ~ nHigh 的子序列归并排序到 pnTmp 中
	void MSort(int* pnSequence, int* pnTmp, int nLow, int nHigh);

	// 将 pnSequence 中 nLow ~ nMid、nMid + 1 ~ nHigh 的子序列归并排序到 pnTmp 中
	void MMerge(int* pnSequence, int* pnTmp, int nLow, int nMid, int nHigh);

	// 对 pnSequence 中 nLow ~ nHigh 的子序列进行快速排序
	void QSort(int* pnSequence, int nLow, int nHigh);

	// 交换 pnSequence 中 nLow ~ nHigh 的子序列各元素，以计算枢轴值
	int QPartition(int* pnSequence, int nLow, int nHigh);

public:
	CAlgorithm();

	// 先调用该函数实例化一个 CAlgorithm 对象，再调用下面的函数即可
	CAlgorithm(int* pnSequence, int nCnt);

	~CAlgorithm();

public:
	// 顺序表查找
	int SequentialSearch(int nKey);

	// 顺序表查找（优化：使用哨兵，可以避免每次循环都判断下标是否越界）
	int SequentialSearch2(int nKey);

	// 有序表查找 - 折半查找（二分查找，使用的是二叉排序树思想）
	int BinarySearch(int nKey);

	// 有序表查找 - 插值查找
	int InterpolationSearch(int nKey);

	// 交换排序类 - 冒泡排序
	std::string BubbleSort();

	// 交换排序类 - 冒泡排序（优化：使用标记，可以跳过序列有序后的所有循环，这也就是为什么冒泡排序在最好情况下的时间复杂度为 O(n)）
	std::string BubbleSort2();

	// 交换排序类 - 快速排序
	std::string QuickSort();

	// 选择排序类 - 简单选择排序
	std::string SelectSort();

	// 选择排序类 - 堆排序
	std::string HeapSort();

	// 插入排序类 - 直接插入排序
	std::string InsertSort();

	// 插入排序类 - 直接插入排序（优化：使用哨兵，可以避免每次循环都判断下标是否越界）
	std::string InsertSort2();

	// 插入排序类 - 希尔排序
	std::string ShellSort();

	// 归并排序类 - 归并排序
	std::string MergeSort();
};
