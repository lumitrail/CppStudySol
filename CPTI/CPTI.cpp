// https://softeer.ai/practice/11002

#include <iostream>
#include <bitset>

using namespace std;

/// <summary>
/// 사람 수, ~30000
/// </summary>
static int N = 0;
/// <summary>
/// 성격영역 수, ~30
/// </summary>
static int M = 0;


class CPTI
{
public:
    int Flag = 0;
    
    CPTI()
    { }

    /// <summary>
    /// 최적화 대상!
    /// </summary>
    /// <param name="c"></param>
    CPTI(char* c)
    {
        for (int i = 0; i < M; ++i)
        {
            Flag = Flag << 1;

            if (c[i] == '1')
            {
                Flag = Flag | 1;
            }
        }
    }

    void Print()
    {
        cout << bitset<30>(Flag) << endl;
    }

    /// <summary>
    /// 최적화 대상!
    /// </summary>
    /// <param name="b"></param>
    /// <returns></returns>
    bool IsFamiliar(CPTI b)
    {
        int masked = Flag ^ b.Flag;

        if (masked == 0)
        {
            return true;
        }

        int differences = 0;
        for (int i = 0; i < M; ++i)
        {
            int masked = masked >> 1;

            if (masked & 1)
            {
                ++differences;
            }

            if (differences > 2)
            {
                return false;
            }
        }

        return true;
    }
};


void PrintCPTIs(CPTI* data);
CPTI* GetCPTIs();
void GetNM();
void PrintNM();


int main()
{
    GetNM();

    CPTI* data = GetCPTIs();


    PrintNM();

    PrintCPTIs(data);
    
    return 0;
}

void PrintCPTIs(CPTI* data)
{
    cout << endl;
    for (int i = 0; i < N; ++i)
    {
        data[i].Print();
    }
    cout << endl;
}

CPTI* GetCPTIs()
{
    CPTI* data = new CPTI[N];

    char* cpti = new char[M];

    for (int i = 0; i < N; ++i)
    {
        cin >> cpti;
        data[i] = CPTI(cpti);
    }

    return data;
}

void GetNM()
{
    cin >> N;
    cin >> M;
}

void PrintNM()
{
    cout << endl << "N: " << N << endl << "M: " << M << endl;
}
