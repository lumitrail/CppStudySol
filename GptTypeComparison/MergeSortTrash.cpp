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
