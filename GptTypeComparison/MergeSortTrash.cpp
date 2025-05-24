//
//void PrintVec(vector<GptNumber>& data);
//
//
//void QuickSort(vector<GptNumber>& source, int fromIdx, int toIdx);
//GptNumber GetPivotValue(vector<GptNumber>& source, int from, int to);
//
//
//void Solve()
//{
//	char strInput[8] = { 0,0,0,0,0,0,0,0 }; // 100.000 <- 7자리, + \0
//
//	cin >> strInput;
//
//	int N = atoi(strInput);
//
//	GptNumber* data = new GptNumber[N];
//
//	for (int i = 0; i < N; ++i)
//	{
//		cin >> input;
//		GptNumber d = GptNumber(input);
//		data.push_back(d);
//	}
//
//	QuickSort(data, 0, N - 1);
//
//	PrintVec(data);
//}
//
//
//void QuickSort(vector<GptNumber>& source, int fromIdx, int toIdx)
//{
//	if (fromIdx >= toIdx)
//	{
//		return;
//	}
//
//	GptNumber pivotValue = GetPivotValue(source, fromIdx, toIdx);
//
//	int headCursor = fromIdx;
//	int tailCursor = toIdx;
//
//	while (headCursor < tailCursor)
//	{
//		GptNumber headValue = source[headCursor];
//		GptNumber tailValue = source[tailCursor];
//
//		while (headValue.Compare(pivotValue) > 0
//			&& headCursor < toIdx)
//		{
//			// headValue가 작으면 headCursor 이동
//			++headCursor;
//			headValue = source[headCursor];
//		}
//
//		while (pivotValue.Compare(tailValue) > 0
//			&& tailCursor > fromIdx)
//		{
//			// tailValue가 크면 tailCursor 이동
//			--tailCursor;
//			tailValue = source[tailCursor];
//		}
//		
//		source[headCursor] = tailValue;
//		source[tailCursor] = headValue;
//	}
//
//	QuickSort(source, fromIdx, headCursor);
//	QuickSort(source, headCursor + 1, toIdx);
//}
//
//GptNumber GetPivotValue(vector<GptNumber>& source, int from, int to)
//{
//	int pivotIdx = (from + to) / 2;
//
//	GptNumber pivotCandidate1 = source[from];
//	GptNumber pivotCandidate2 = source[pivotIdx];
//	GptNumber pivotCandidate3 = source[to];
//
//	bool larger2than1 = pivotCandidate1.Compare(pivotCandidate2) > 0;
//	bool larger3than2 = pivotCandidate2.Compare(pivotCandidate3) > 0;
//	bool larger1than3 = pivotCandidate3.Compare(pivotCandidate1) > 0;
//
//	if (larger2than1) // 1 < 2
//	{
//		if (larger3than2) // 2 < 3
//		{
//			// 1 < 2 < 3
//			return pivotCandidate2;
//		}
//
//		// 1, 3 < 2
//		if (larger1than3) // 3 < 1
//		{
//			return pivotCandidate1;
//		}
//
//		return pivotCandidate3;
//	}
//	else // 2 < 1
//	{
//		if (larger3than2) // 2 < 3
//		{
//			// 2 < 1, 3
//			if (larger1than3) // 3 < 1
//			{
//				return pivotCandidate3;
//			}
//
//			return pivotCandidate1;
//		}
//
//		// 3 < 2 < 1
//		return pivotCandidate2;
//	}
//}
//
//
//
//int VecToI(vector<char>& vec)
//{
//	int result = 0;
//
//	int vecLength = vec.size();
//	for (int i = 0; i < vecLength; ++i)
//	{
//		char cursor = vec[i];
//
//		if (cursor == '.')
//		{
//			continue;
//		}
//
//		result *= 10;
//		result += vec[i] - '0';
//	}
//
//	return result;
//}
//
//vector<char> ItoVec(int num)
//{
//	vector<char> reversed;
//
//	if (num == 0)
//	{
//		reversed.push_back('0');
//
//		return reversed;
//	}
//
//	while (num != 0)
//	{
//		int dec = num % 10;
//
//		reversed.push_back(dec + '0');
//
//		num = num / 10;
//	}
//
//	vector<char> result;
//
//	int reversedSize = reversed.size();
//	for (int i = 0; i < reversedSize; ++i)
//	{
//		result.push_back(reversed[reversedSize - i - 1]);
//	}
//
//	return result;
//}
//
//string VecToStr(vector<char>& vec)
//{
//	int vecLen = vec.size();
//
//	char* data = new char[vecLen + 1];
//
//	int i = 0;
//	for (i = 0; i < vecLen; ++i)
//	{
//		data[i] = vec[i];
//	}
//	data[i] = 0;
//
//	string resultString = string(data);
//	return resultString;
//}
//
//
//template<typename T>
//vector<T> Concat(vector<T>& first, vector<T>& last)
//{
//	int firstSize = first.size();
//	int lastSize = last.size();
//
//	vector<T> result;
//
//	for (int i = 0; i < firstSize; ++i)
//	{
//		result.push_back(first[i]);
//	}
//
//	for (int i = 0; i < lastSize; ++i)
//	{
//		result.push_back(last[i]);
//	}
//
//	return result;
//}
//
//void PrintVec(vector<GptNumber>& data)
//{
//	for (int i = 0; i < data.size(); ++i)
//	{
//		GptNumber d = data[i];
//		string output = d.ToString();
//		cout << output << endl;
//	}
//}


#ifdef KKKKK


template<typename T>
vector<vector<T>> Split(vector<T>& source)
{
	int sourceSize = source.size();

	if (sourceSize < 2)
	{
		vector<T> sourceCopy;

		for (int i = 0; i < sourceSize; ++i)
		{
			sourceCopy.push_back(source[i]);
		}

		vector<vector<T>> result;
		result.push_back(sourceCopy);
		vector<T> empty;
		result.push_back(empty);
		return result;
	}

	int splitSize = (sourceSize / 2);

	vector<T> a;
	vector<T> b;
	a.reserve(splitSize + 1);
	b.reserve(splitSize + 1);

	int i = 0;
	for (i = 0; i < splitSize; ++i)
	{
		a.push_back(source[i]);
	}

	for (; i < sourceSize; ++i)
	{
		b.push_back(source[i]);
	}

	vector<vector<T>> result = { a,b };

	return result;
}



vector<GptNumber> Sort(vector<GptNumber>& source)
{
	vector<vector<GptNumber>> sp = Split(source);

	return Sort(sp[0], sp[1]);
}

vector<GptNumber> Sort(vector<GptNumber>& a, vector<GptNumber>& b)
{
	if (a.size() < 2 && b.size() < 2)
	{
		return MergeSortIncreasing(a, b);
	}
	else
	{
		vector<vector<GptNumber>> spA = Split(a);
		vector<vector<GptNumber>> spB = Split(b);

		vector<GptNumber> rA = Sort(spA[0], spA[1]);
		vector<GptNumber> rB = Sort(spB[0], spB[1]);

		return Sort(rA, rB);
	}
}

vector<GptNumber> MergeSortIncreasing(vector<GptNumber>& a,
	vector<GptNumber>& b)
{
	cout << "comparing:" << endl;
	PrintVec(a);
	cout << endl;
	PrintVec(b);
	cout << endl;

	int aLength = a.size();
	int bLength = b.size();

	vector<GptNumber> result;
	result.reserve(aLength + bLength);

	int aCursor = 0;
	int bCursor = 0;

	while (true)
	{
		if (aCursor >= aLength) // a를 다 봤을 때
		{
			for (int i = bCursor; i < bLength; ++i)
			{
				result.push_back(b[i]);
			}

			cout << "a dep" << endl;
			PrintVec(result);

			return result;
		}
		else if (bCursor >= bLength) // b를 다 봤을 때
		{
			for (int i = aCursor; i < aLength; ++i)
			{
				result.push_back(a[i]);
			}

			cout << "b dep" << endl;
			PrintVec(result);

			return result;
		}
		else
		{
			if (a[aCursor].Compare(b[bCursor]) > 0)
			{
				result.push_back(a[aCursor]);
				++aCursor;
			}
			else
			{
				result.push_back(b[bCursor]);
				++bCursor;
			}
		}
	}

	throw out_of_range("sort 실패");
}


vector<GptNumber> MergeSort(vector<GptNumber>& a, vector<GptNumber>& b)
{
	if (a.size() < 2 && b.size() < 2)
	{
		return MergeSortSmallResult(a, b);
	}


}

vector<GptNumber> MergeSortSmallResult(vector<GptNumber>& a,
	vector<GptNumber>& b)
{
	vector<GptNumber> smallResult;

	int aSize = a.size();
	int bSize = b.size();

	assert(aSize < 2);
	assert(bSize < 2);

	if (aSize != 0 && bSize != 0)
	{
		if (a[0].Compare(b[0]) > 0)
		{
			smallResult.push_back(a[0]);
			smallResult.push_back(b[0]);
		}
		else
		{
			smallResult.push_back(b[0]);
			smallResult.push_back(a[0]);
		}
	}
	else if (aSize != 0)
	{
		smallResult.push_back(a[0]);
	}
	else if (bSize != 0)
	{
		smallResult.push_back(b[0]);
	}

	return smallResult;
}

#endif // KKKKK
