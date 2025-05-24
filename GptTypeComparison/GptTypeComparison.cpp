#include <iostream>
#include <string>
#include <vector>

using namespace std;

int VecToI(vector<char>& vec);
vector<char> ItoVec(int num);
string VecToStr(vector<char>& vec);
template<typename T> vector<T> Concat(vector<T>& first, vector<T>& last);

class GptNumber
{
public:
	int IntegerPart = 0;
	int FractionPart = -1;

	GptNumber(const char* num)
	{
		string n = string(num);
		Init(n);
	}

	GptNumber(string& num)
	{
		Init(num);
	}

	string ToString()
	{
		vector<char> integers = ItoVec(IntegerPart);

		if (FractionPart < 0)
		{
			return VecToStr(integers);
		}
		else
		{
			integers.push_back('.');

			vector<char> fractions = ItoVec(FractionPart);

			vector<char> result = Concat(integers, fractions);

			return VecToStr(result);
		}
	}

	int GetIntegerPart(string& num)
	{
		int result = 0;

		int numLength = num.length();
		for (int i = 0; i < numLength; ++i)
		{
			char cursor = num[i];

			if (cursor == '.')
			{
				return result;
			}

			result *= 10;
			result += cursor - '0';
		}

		return result;
	}

	int GetFractionPart(string& num)
	{
		int numLength = num.length();
		int fracStartIdx = 0;
		for (int i = 0; i < numLength; ++i)
		{
			char cursor = num[i];

			if (cursor == '.')
			{
				FractionPart = 0;
				fracStartIdx = i;
				break;
			}
		}

		if (FractionPart == -1)
		{
			return -1;
		}

		vector<char> fractionPartVec;

		for (int i = fracStartIdx+1; i < numLength; ++i)
		{
			char cursor = num[i];
			fractionPartVec.push_back(cursor);
		}

		int result = VecToI(fractionPartVec);

		return result;
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
			else //if (b.FractionPart == FractionPart)
			{
				return 0;
			}
		}

		throw out_of_range("Compare 실패");
	}

	private:
		void Init(string& num)
		{
			IntegerPart = GetIntegerPart(num);
			FractionPart = GetFractionPart(num);
		}
};

void PrintVec(vector<GptNumber>& data);


void QuickSort(vector<GptNumber>& source, int fromIdx, int toIdx);
GptNumber GetPivotValue(vector<GptNumber>& source, int from, int to);


void Solve()
{
	string input;
	cin >> input;

	int N = atoi(input.c_str());

	vector<GptNumber> data;
	data.reserve(N);

	for (int i = 0; i < N; ++i)
	{
		cin >> input;
		GptNumber d = GptNumber(input);
		data.push_back(d);
	}

	QuickSort(data, 0, N - 1);

	PrintVec(data);
}


void QuickSort(vector<GptNumber>& source, int fromIdx, int toIdx)
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

GptNumber GetPivotValue(vector<GptNumber>& source, int from, int to)
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



int VecToI(vector<char>& vec)
{
	int result = 0;

	int vecLength = vec.size();
	for (int i = 0; i < vecLength; ++i)
	{
		char cursor = vec[i];

		if (cursor == '.')
		{
			continue;
		}

		result *= 10;
		result += vec[i] - '0';
	}

	return result;
}

vector<char> ItoVec(int num)
{
	vector<char> reversed;

	if (num == 0)
	{
		reversed.push_back('0');

		return reversed;
	}

	while (num != 0)
	{
		int dec = num % 10;

		reversed.push_back(dec + '0');

		num = num / 10;
	}

	vector<char> result;

	int reversedSize = reversed.size();
	for (int i = 0; i < reversedSize; ++i)
	{
		result.push_back(reversed[reversedSize - i - 1]);
	}

	return result;
}

string VecToStr(vector<char>& vec)
{
	int vecLen = vec.size();

	char* data = new char[vecLen + 1];

	int i = 0;
	for (i = 0; i < vecLen; ++i)
	{
		data[i] = vec[i];
	}
	data[i] = 0;

	string resultString = string(data);
	return resultString;
}


template<typename T>
vector<T> Concat(vector<T>& first, vector<T>& last)
{
	int firstSize = first.size();
	int lastSize = last.size();

	vector<T> result;

	for (int i = 0; i < firstSize; ++i)
	{
		result.push_back(first[i]);
	}

	for (int i = 0; i < lastSize; ++i)
	{
		result.push_back(last[i]);
	}

	return result;
}

void PrintVec(vector<GptNumber>& data)
{
	for (int i = 0; i < data.size(); ++i)
	{
		GptNumber d = data[i];
		string output = d.ToString();
		cout << output << endl;
	}
}


int main(int argc, char** argv)
{
	Solve();
	//CompareTest();
	return 0;
}
