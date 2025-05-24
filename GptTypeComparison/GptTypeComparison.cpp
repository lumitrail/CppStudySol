#include <iostream>

using namespace std;

class GptNumber
{
public:
	int IntegerPart = 0;
	/// <summary>
	/// 소수점 없을 때 -1
	/// </summary>
	int FractionPart = -1;
	char StringVal[8] = { '0',0,0,0,0,0,0,0 };

	GptNumber()
	{ }

	GptNumber(const char* num)
	{
		int i = 0;
		while (i < 8)
		{
			if (num[i] == 0)
			{
				break;
			}
			else if (num[i] == '.')
			{
				FractionPart = 0;
			}

			StringVal[i] = num[i];
			++i;
		}

		Init();
	}

	/// <summary>
	/// 내가 크면 -1, 같으면 0, b가 크면 1
	/// </summary>
	/// <param name="b"></param>
	/// <returns></returns>
	int Compare(GptNumber& b)
	{
		if (b.IntegerPart > IntegerPart)
		{
			return 1;
		}
		else if (b.IntegerPart < IntegerPart)
		{
			return -1;
		}
		else // if (b.IntegerPart == IntegerPart)
		{
			if (b.FractionPart > FractionPart)
			{
				return 1;
			}
			else if (b.FractionPart <FractionPart)
			{
				return -1;
			}
		}

		return 0;
	}

	private:
		void Init()
		{
			int fractionPartStart = SetIntegerPart();

			if (FractionPart == 0)
			{
				FractionPart = atoi(&StringVal[fractionPartStart]);
			}
		}
		
		int SetIntegerPart()
		{
			int i = 0;
			for (; i < 3; ++i)
			{
				char cursor = StringVal[i];

				if (cursor == '.'
					|| cursor == 0)
				{
					return i + 1;
				}

				IntegerPart *= 10;
				IntegerPart += cursor - '0';
			}

			return i + 1;
		}
};


///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////


GptNumber GetPivotValue(GptNumber* source, int from, int to)
{
	int pivotIdx = (from + to) / 2;

	GptNumber pivotCandidate1 = source[from];
	GptNumber pivotCandidate2 = source[pivotIdx];
	GptNumber pivotCandidate3 = source[to];

	bool larger2than1 = pivotCandidate1.Compare(pivotCandidate2) > 0;
	bool larger3than2 = pivotCandidate2.Compare(pivotCandidate3) > 0;
	bool larger1than3 = pivotCandidate3.Compare(pivotCandidate1) > 0;

	if (larger2than1) // 1 < 2
	{
		if (larger3than2) // 2 < 3
		{
			// 1 < 2 < 3
			return pivotCandidate2;
		}

		// 1, 3 < 2
		if (larger1than3) // 3 < 1
		{
			return pivotCandidate1;
		}

		return pivotCandidate3;
	}
	else // 2 < 1
	{
		if (larger3than2) // 2 < 3
		{
			// 2 < 1, 3
			if (larger1than3) // 3 < 1
			{
				return pivotCandidate3;
			}

			return pivotCandidate1;
		}

		// 3 < 2 < 1
		return pivotCandidate2;
	}
}

void QuickSort(GptNumber* source, int fromIdx, int toIdx)
{
	if (fromIdx >= toIdx)
	{
		return;
	}

	GptNumber pivotValue = GetPivotValue(source, fromIdx, toIdx);

	int headCursor = fromIdx;
	int tailCursor = toIdx;

	while (headCursor < tailCursor)
	{
		GptNumber headValue = source[headCursor];
		GptNumber tailValue = source[tailCursor];

		while (headValue.Compare(pivotValue) > 0
			&& headCursor < toIdx)
		{
			// headValue가 작으면 headCursor 이동
			++headCursor;
			headValue = source[headCursor];
		}

		while (pivotValue.Compare(tailValue) > 0
			&& tailCursor > fromIdx)
		{
			// tailValue가 크면 tailCursor 이동
			--tailCursor;
			tailValue = source[tailCursor];
		}
		
		source[headCursor] = tailValue;
		source[tailCursor] = headValue;
	}

	QuickSort(source, fromIdx, headCursor);
	QuickSort(source, headCursor + 1, toIdx);
}


///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////


void PrintValuesDebug(GptNumber* data, int N)
{
	cout << endl;

	for (int i = 0; i < N; ++i)
	{
		cout << data[i].IntegerPart;
		if (data[i].FractionPart >= 0)
		{
			cout << "." << data[i].FractionPart;
		}

		cout << " " << data[i].StringVal << endl;
	}
}

void PrintValues(GptNumber* data, int N)
{
	for (int i = 0; i < N; ++i)
	{
		cout << data[i].StringVal << endl;
	}
}

int InputN()
{
	char inputStr[5];
	cin >> inputStr;

	int result = atoi(inputStr);
	return result;
}

GptNumber* InputGptNumbers(int N)
{
	GptNumber* data = new GptNumber[N];

	char strInput[8] = { 0,0,0,0,0,0,0,0 }; // 100.000 <- 7자리, + \0

	for (int i = 0; i < N; ++i)
	{
		cin >> strInput;
		GptNumber d = GptNumber(strInput);
		data[i] = d;
	}

	return data;
}

int main(int argc, char** argv)
{
	int N = InputN();
	
	GptNumber* data = InputGptNumbers(N);

	QuickSort(data, 0, N - 1);

	PrintValues(data, N);

	return 0;
}
