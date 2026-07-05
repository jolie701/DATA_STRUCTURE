// h34136091_hw4.cpp : 此檔案包含 'main' 函式。程式會於該處開始執行及結束執行。
//
/*
   This code is an example to show how we can measure the CPU time
   used for some specific procedures. The idea is to call the function
   mytimer() before and after excuting the procedure (in this example,
   I use a for loop), the difference of the float numbers returned
   represents the time spent for the procedures between these 2 calls
   of mytimer().


   to compile:
               g++ -o check_time check_time.c
   to run:
               check_time
           input k= 10000000
           k=10000000, totally takes time= 1156.000 (this number
               may differ depending on your CPU/OS..etc)
  !note: this code can compile/run under cygwin or SunOS using g++ or
         gcc. Whether it works in VC6.0 or not is unknown.
*/
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>
#include <chrono>
#include <vector>
using namespace std;

void printout_array(int A[],int a,int n)
{
    cout << "The array A is:" << endl;
    for (int i = 1; i <= n; i++)
    {
        cout << A[i] << " ";
    }
}
void duplicate_array(int A[], int B[],int a, int n)
{
    for (int i = 1; i <= n; i++)
    {
        B[i] = A[i];
    }
}
int is_A_desc(int A[],int n)
{
    for (int i = 1; i < n; i++) // 1到n-1
    {
        if (A[i] < A[i + 1]) // 如果前面比後面小 → 不降序
        {
            cout << "wrong sorted!" << endl;
            return -1;
        }
    }
    cout << "order OK!" << endl;
    return 1;
}

void IS(int A[], int n)//大到小 543216
{
    for (int i = 2; i <= n; i++)
    {
        int j = i - 1;
        int key = A[i];
        while (j >= 1 && key > A[j])
        {
            A[j + 1] = A[j];
            j--;
        }
        A[j + 1] = key;
    }
}

void MG(int A[], int left, int p, int right)
{
    int leftSize = p - left + 1;
    int rightSize = right - p;

    int* a = new int[leftSize + 1];
    int* b = new int[rightSize + 1];

    // 複製左半部
    for (int i = 1; i <= leftSize; i++)
    {
        a[i] = A[left + i - 1];
    }

    // 複製右半部
    for (int j = 1; j <= rightSize; j++)
    {
        b[j] = A[p + j];
    }

    int i = 1, j = 1;
    int l = left;

    // merge（大到小）
    while (i <= leftSize && j <= rightSize)
    {
        if (a[i] >= b[j])
            A[l++] = a[i++];
        else
            A[l++] = b[j++];
    }

    // 左邊剩下
    while (i <= leftSize)
        A[l++] = a[i++];

    // 右邊剩下
    while (j <= rightSize)
        A[l++] = b[j++];

    delete[] a;
    delete[] b;
}

void MS(int A[], int left, int right)
{
    if (left < right)
    {
        int p = (left + right) / 2;
        MS(A, left, p);
        MS(A, p + 1, right);
        MG(A, left ,p,right );

    }
}

void Heapify(int A[], int n, int i)
{
    int smallest= i;
    int left = 2 * i;
    int right = 2 * i + 1;

    if (left <= n && A[left] < A[smallest])
    {
        smallest = left;
    }
    if (right <= n && A[right] < A[smallest])
    {
        smallest = right;
    }
    if (smallest != i)
    {
        swap(A[i], A[smallest]);
        Heapify(A, n, smallest);
    }
}

void HS(int A[], int n)
{
    // 建堆
    for (int i = n / 2; i >= 1; i--)
        Heapify(A, n, i);

    // 排序
    for (int i = n; i > 1; i--)
    {
        swap(A[1], A[i]);
        Heapify(A, i - 1, 1);
    }
}

int partition(int A[], int left, int right)
{
    int pivot = A[right];
    int i = left - 1;
    for (int j = left; j < right; j++)
    {
        if (A[j] >= pivot)
        {
            i++;
            swap(A[i], A[j]);
        }
    }
    swap(A[i + 1], A[right]);
    return i + 1;
}

void QS(int A[], int left, int right)
{
    if (left < right)
    {
        int pi = partition(A, left, right);
        QS(A, left, pi - 1);
        QS(A, pi+1, right);
    }
}

void CS(int A[], int n, int k)//k是資料中的最大值
{
    k = A[1];
    for (int i = 1; i <= n; i++)
    {
        if (A[i] > k)
        {
            k = A[i];
        }
    }

    int* count = new int[k + 1]();

    for (int i = 1; i <= n; i++)
    {
        count[A[i]]++;
    }
    int index = 1;
    for (int value = k; value >= 0; value--)
    {
        while (count[value] > 0)
        {
            A[index] = value;
            index++;
            count[value]--;
        }
    }
    delete[] count;
}

void countingSort(int A[], int n, int exp)
{
    int* output = new int[n+1]();
    int count[10] = { 0 };
    for (int i = 1; i <= n; i++)
    {
        int index = (A[i] / exp) % 10;
        count[index]++;
    }
    for (int i = 8; i >= 0; i--)
    {
        count[i] += count[i + 1];
    }
    for (int i = n ; i >= 1; i--)
    {
        int digit = (A[i] / exp) % 10;
        output[count[digit]] = A[i];
        count[digit]--;
    }
    for (int i = 1; i <= n; i++)
    {
        A[i] = output[i];
    }
    delete[] output;
}

void RS(int A[], int n,int k)
{
    k = A[1];
    for (int i = 2; i <= n; i++)
    {
        if (A[i] > k)
            k = A[i];
    }

    for (int exp = 1; k / exp > 0; exp *= 10)
    {
        countingSort(A, n, exp);
    }
}


void BS(int A[], int n)
{
    int maxVal = A[1];
    for (int i = 2; i <= n; i++)
        if (A[i] > maxVal)
            maxVal = A[i];

    vector<vector<int>> bucket(n);

    for (int i = 1; i <= n; i++)
    {
        int idx = (long long)A[i] * n / (maxVal + 1);
        if (idx >= n) idx = n - 1;
        bucket[idx].push_back(A[i]);
    }

    int index = 1;

    for (int i = n - 1; i >= 0; i--)
    {
        for (int j = 1; j < (int)bucket[i].size(); j++)
        {
            int key = bucket[i][j];
            int k = j - 1;
            while (k >= 0 && bucket[i][k] < key)
            {
                bucket[i][k + 1] = bucket[i][k];
                k--;
            }
            bucket[i][k + 1] = key;
        }

        for (int v : bucket[i])
            A[index++] = v;
    }
}


float mytimer();
int main()
{
    int is_p,n,a_min,a_max,rs,k;
    float t1 = 0., t2 = 0.;
    t1 = mytimer();//取得CPU time
    cout<<"If you want to print out array A ?(yes:1;no:2)"<<endl;
    cin >> is_p;
    cout << "Input size of array,min,max and random seed." << endl;
    cin >> n >> a_min >> a_max >> rs;
    if (a_min >= a_max || n <= 0)
    {
        cout << "Input error!" << endl;
        return -1;
    }
    srand(rs);
    int* A = new int[n+1]();
    int* B = new int[n+1]();
    for (int i = 1; i <= n; i++)
    {  A[i] = rand() % (a_max - a_min + 1) + a_min; }
    if (is_p == 1)
    {
        printout_array(A, 1, n);
        cout << endl;
    }
    duplicate_array(A, B, 1, n);//恢復原本亂數用

    cout << endl;
    cout << endl;
    t1 = mytimer();//紀錄時間開始
    IS(A, n);
    t2 = mytimer();//紀錄結束時間
    float t_is = t2 - t1;//結束減掉開始
    is_A_desc(A, n);

    duplicate_array(B, A, 1, n);//恢復原本亂數用

    t1 = mytimer();
    MS(A,1, n);
    t2 = mytimer();
    float  t_ms = t2 - t1;
    is_A_desc(A, n);

    duplicate_array(B, A, 1, n);

    t1 = mytimer();
    HS(A, n);
    t2 = mytimer();
    float  t_hs = t2 - t1;
    is_A_desc(A, n);

    duplicate_array(B, A, 1, n);

    t1 = mytimer();
    QS(A, 1, n);
    t2 = mytimer();
    float  t_qs = t2 - t1;
    is_A_desc(A, n);

    duplicate_array(B, A, 1, n);

    t1 = mytimer();
    k = 0;
    CS(A, n, k);
    t2 = mytimer();
    float t_cs = t2 - t1;
    is_A_desc(A, n);

    duplicate_array(B, A, 1, n);

    t1 = mytimer();
    k = 0;
    RS(A, n, k);
    t2 = mytimer();
    float  t_rs = t2 - t1;
    is_A_desc(A, n);

    duplicate_array(B, A, 1, n);

    t1 = mytimer();
    BS(A, n);
    t2 = mytimer();
    float t_bs = t2 - t1;
    is_A_desc(A, n);
    cout << endl;

    cout << endl;
    cout << n << " " << a_min << " " << a_max << " " << rs << " "
        << t_is << " " << t_ms << " " << t_hs << " "
        << t_qs << " " << t_cs << " " << t_rs << " " << t_bs << endl;



    delete []A;
    delete []B;
    return 0;

}
/*----------------------------------------------*/
float mytimer() {
    static auto start = chrono::high_resolution_clock::now();
    auto now = chrono::high_resolution_clock::now();
    chrono::duration<float> diff = now - start;
    return diff.count();
}



// 執行程式: Ctrl + F5 或 [偵錯] > [啟動但不偵錯] 功能表
// 偵錯程式: F5 或 [偵錯] > [啟動偵錯] 功能表

// 開始使用的提示:
//   1. 使用 [方案總管] 視窗，新增/管理檔案
//   2. 使用 [Team Explorer] 視窗，連線到原始檔控制
//   3. 使用 [輸出] 視窗，參閱組建輸出與其他訊息
//   4. 使用 [錯誤清單] 視窗，檢視錯誤
//   5. 前往 [專案] > [新增項目]，建立新的程式碼檔案，或是前往 [專案] > [新增現有項目]，將現有程式碼檔案新增至專案
//   6. 之後要再次開啟此專案時，請前往 [檔案] > [開啟] > [專案]，然後選取 .sln 檔案
