// https://softeer.ai/practice/11004

#include <iostream>
#include <string>
#include <cassert>

using namespace std;

class Board
{
public:
    int** table;


    int N = 0;

    int reduceRow_min;
    int reduceRow_max;

    int doubleColumn_min;
    int doubleColumn_max;

    /// <summary>
    /// cin 대기 있음
    /// </summary>
    Board()
    {
        string currentLine;
        cin >> currentLine;
        N = atoi(currentLine.c_str());

        assert(N > 0);

        table = new int* [N];

        for (int i = 0; i < N; ++i)
        {
            table[i] = new int[N];

            FillRow(table[i]);
        }
    }

    Board(const Board& b)
    {
        N = b.N;

        table = new int* [N];
        for (int i = 0; i < N; ++i)
        {
            table[i] = new int[N];
            for (int j = 0; j < N; ++j)
            {
                table[i][j] = b.table[i][j];
            }
        }
    }


    /// <summary>
    /// 
    /// </summary>
    /// <param name="fromRow">0~N</param>
    /// <param name="toRow">0~N</param>
    void LaserA(int fromRow, int toRow)
    {
        assert(fromRow >= 0);
        assert(fromRow < N);
        assert(toRow >= 0);
        assert(toRow < N);

        reduceRow_min = fromRow < toRow ?
            fromRow : toRow;
        reduceRow_max = fromRow < toRow ?
            toRow : fromRow;

        ++reduceRow_max;

        for (int i = reduceRow_min; i < reduceRow_max; ++i)
        {
            for (int j = 0; j < N; ++j)
            {
                table[i][j] = 1;
            }
        }
    }

    /// <summary>
    /// 
    /// </summary>
    /// <param name="fromColumn">0~N</param>
    /// <param name="toColumn">0~N</param>
    void LaserB(int fromColumn, int toColumn)
    {
        assert(fromColumn >= 0);
        assert(fromColumn < N);
        assert(toColumn >= 0);
        assert(toColumn < N);

        doubleColumn_min = fromColumn < toColumn ?
            fromColumn : toColumn;
        doubleColumn_max = fromColumn < toColumn ?
            toColumn : fromColumn;

        ++doubleColumn_max;

        for (int i = 0; i < N; ++i)
        {
            for (int j = doubleColumn_min; j < doubleColumn_max; ++j)
            {
                table[i][j] *= 2;
            }
        }
    }

    void LaserBStart(int fromColumn)
    {
        doubleColumn_min = fromColumn;
        doubleColumn_max = fromColumn;
        for (int i = 0; i < N; ++i)
        {
            table[i][doubleColumn_max] *= 2;
        }
    }

    void LaserBNext()
    {
        doubleColumn_max += 1;
        for (int i = 0; i < N; ++i)
        {
            table[i][doubleColumn_max] *= 2;
        }
    }


    int GetSum(int x1, int y1, int x2, int y2)
    {
        int fromX = x1 < x2 ? x1 : x2;
        int toX = x1 < x2 ? x2 : x1;

        assert(fromX >= reduceRow_min);
        assert(toX < reduceRow_max);

        int fromY = y1 < y2 ? y1 : y2;
        int toY = y1 < y2 ? y2 : y1;

        assert(fromY >= doubleColumn_min);
        assert(toY < doubleColumn_max);

        int sum = 0;

        for (int i = fromX; i < toX; ++i)
        {
            for (int j = fromY; j < toY; ++j)
            {
                sum += table[i][j];
            }
        }

        return sum;
    }

    ~Board()
    {
        for (int i = 0; i < N; ++i)
        {
            delete[] table[i];
        }

        delete[] table;
    }


    void Print()
    {
        cout << endl;
        for (int i = 0; i < N; ++i)
        {
            for (int j = 0; j < N; ++j)
            {
                cout << table[i][j] << ' ';
            }
            cout << endl;
        }
    }


private:
    void FillRow(int* row)
    {
        for (int i = 0; i < N; ++i)
        {
            string currentVal;
            cin >> currentVal;
            row[i] = atoi(currentVal.c_str());
        }
    }
};

int GetMaxSum(Board& b);
int MultiRowMax(int** data, int rows, int N);
int MultiColumnMax(int** data, int startColumn, int endColumnPlus, int N);

int** CreateTable(int N);
int** CopyTable(int** table, int N);
void CopyTable(int** source, int** targetAllocated, int N);
void DeleteTable(int** table, int N);
void PrintTable(int** table, int N);


void Solve()
{
    Board root;

    int maxSum = 0;
    int N = root.N;

    // debug purpose
    int** maxTable = CreateTable(N);
    int laserAStart = 0;
    int laserAEnd = 0;
    int laserBStart = 0;
    int laserBEnd = 0;
    int laserBProgress = 0;
    // END debue purpose

    for (int xmin = 0; xmin < N; ++xmin)
    {
        for (int ymin = 0; ymin < N; ++ymin)
        {
            for (int xmax = xmin; xmax < N; ++xmax)
            {
                Board burned = Board(root);

                //burned.Print();

                burned.LaserA(xmin, xmax);

                laserAStart = xmin;
                laserAEnd = xmax;

                //burned.Print();

                burned.LaserBStart(ymin);

                laserBStart = ymin;
                laserBEnd = ymin;

                //burned.Print();

                int localMaxSum = GetMaxSum(burned);
                if (localMaxSum > maxSum)
                {
                    maxSum = localMaxSum;

                    CopyTable(burned.table, maxTable, N);
                }

                laserBProgress = laserBEnd;

                for (int ymax = ymin + 1; ymax < N; ++ymax)
                {
                    burned.LaserBNext();
                    localMaxSum = GetMaxSum(burned);

                    ++laserBProgress;

                    if (localMaxSum > maxSum)
                    {
                        maxSum = localMaxSum;

                        CopyTable(burned.table, maxTable, N);
                        laserBEnd = laserBProgress;
                    }
                }
            }
        }
    }

    PrintTable(maxTable, N);
    DeleteTable(maxTable, N);

    cout << maxSum;
}



int GetMaxSum(Board& b)
{
    int maxSum = 0;

    int startRow = b.reduceRow_min;
    int endRow = b.reduceRow_max;

    for (int i = startRow; i < endRow; ++i)
    {
        for (int j = i; j < endRow; ++j)
        {
            int rows = endRow - j;

            int localMax = MultiRowMax(&b.table[i], rows, b.N);

            if (localMax > maxSum)
            {
                maxSum = localMax;
            }
        }
    }

    int startColumn = b.doubleColumn_min;
    int endColumn = b.doubleColumn_max + 1;

    for (int i = startColumn; i < endColumn; ++i)
    {
        for (int e = i + 1; e < endColumn; ++e)
        {
            int localMax = MultiColumnMax(b.table, i, e, b.N);

            if (localMax > maxSum)
            {
                maxSum = localMax;
            }
        }
    }

    return maxSum;
}

int MultiRowMax(int** data, int rows, int N)
{
    int maxSum = 0;

    int allSum = 0;

    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            allSum += data[i][j];
        }
    }

    // 1은 이득이기 때문에, 앞에서부터/뒤에서부터 가운데 어딘가까지 더한 값이 최대임

    // 모든 줄에 대해, 앞에서부터 더함

    for (int idx = 0; idx < N; ++idx)
    {
        int headSum = 0;

        for (int row = 0; row < rows; ++row)
        {
            headSum += data[row][idx];
        }

        int tailSum = allSum - headSum;

        if (headSum > maxSum)
        {
            maxSum = headSum;
        }

        if (tailSum > maxSum)
        {
            maxSum = tailSum;
        }
    }

    return maxSum;
}


int MultiColumnMax(int** data, int startColumn, int endColumnPlus, int N)
{
    int maxSum = 0;

    //start row도 변함
    for (int startRow = 0; startRow < N; ++startRow)
    {
        for (int endRow = startRow + 1; endRow < N; ++endRow)
        {
            int localMax = 0;

            for (int row = startRow; row < endRow; ++row)
            {
                for (int i = startColumn; i < endColumnPlus; ++i)
                {
                    localMax += data[row][i];
                }
            }

            if (localMax > maxSum)
            {
                maxSum = localMax;
            }
        }
    }

    return maxSum;
}


int** CreateTable(int N)
{
    int** table = new int* [N];

    for (int i = 0; i < N; ++i)
    {
        table[i] = new int[N];
    }

    return table;
}

int** CopyTable(int** table, int N)
{
    int** output = new int* [N];

    for (int i = 0; i < N; ++i)
    {
        output[i] = new int[N];

        for (int j = 0; j < N; ++j)
        {
            output[i][j] = table[i][j];
        }
    }

    return output;
}

void CopyTable(int** source, int** targetAllocated, int N)
{
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            targetAllocated[i][j] = source[i][j];
        }
    }
}


void DeleteTable(int** table, int N)
{
    for (int i = 0; i < N; ++i)
    {
        delete[] table[i];
    }

    delete[] table;
}

void PrintTable(int** table, int N)
{
    cout << endl;
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            cout << table[i][j] << ' ';
        }
        cout << endl;
    }
}

int main()
{
    Solve();
    return 0;
}
