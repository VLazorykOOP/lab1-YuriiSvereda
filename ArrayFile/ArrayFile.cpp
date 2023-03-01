
#include <iostream>
#include <fstream>
#include <ios>
#include <vector>

#include <time.h>

using namespace std;
const int MAX_SIZE = 560;

typedef double* pDouble;
/*
*   ConsoleInputArrayDouble
*
*/
int ConsoleInputSizeArray(const int sizeMax)
{
    int size = 0;
    do {
        cout << " Input size Array ( 0< 1 < " << sizeMax << " ) ";
        cin >> size;
    } while (size <= 0 || size >= sizeMax);
    return size;
}
/*
*   ConsoleInputArrayDouble
*
*/
int ConsoleInputArray(int sizeMax, double A[])
{
    int size = ConsoleInputSizeArray(sizeMax);
    for (int i = 0; i < size; i++) {
        cout << " Array[ " << i << "] "; cin >> A[i];
    }
    return size;
}

/*
*   RndInputArrayDouble
*
*/
int RndInputArray(int sizeMax, double A[])
{
    int size = ConsoleInputSizeArray(sizeMax);
    int r1 = 0, r2 = 0;
    srand(size);

    for (int i = 0; i < size; i++) {
        r1 = rand();
        r2 = rand();
        A[i] = 100.0 * r1;
        A[i] = A[i] / (1.0 + r2);
        cout << A[i] << "   ";
    }
    return size;
}

int ConsoleInputDynamicArrayNew(int sizeMax, pDouble& pA)
{
    int size = ConsoleInputSizeArray(sizeMax);
    pA = new double[size];
    if (pA == nullptr) { return 0; }
    for (int i = 0; i < size; i++) {
        cout << " Array[ " << i << "] "; cin >> pA[i];
    }
    return size;
}

int ConsoleInputDynamicArray_calloc(int sizeMax, pDouble& pA)
{
    int size = ConsoleInputSizeArray(sizeMax);
    pA = (double*)calloc(size, sizeof(double));      // pA = (double*)malloc(size * sizeof(double)); 
    if (pA == nullptr) { return 0; }
    for (int i = 0; i < size; i++) {
        cout << " Array[ " << i << "] "; cin >> pA[i];
    }
    return size;
}

void ConsoleInputVector(int sizeMax, vector<double>& A)
{
    int size = ConsoleInputSizeArray(sizeMax);
    double d;
    for (int i = 0; i < size; i++) {
        cout << " Array[ " << i << "] "; cin >> d; A.push_back(d);
    }
    return;
}


/*
*  WriteArrayTextFile
*
*/

void WriteArrayTextFile(int n, double* arr, const char* fileName)
{
    ofstream fout(fileName);
    if (fout.fail()) return;
    fout << n << endl;
    for (int i = 0; i < n; i++)
        fout << arr[i] << "   ";
    fout.close(); //
}
/*
*  ReadArrayTextFile
*
*/


int ReadArrayTextFile(int n, double* arr, const char* fileName)
{
    int size;
    ifstream fin(fileName);
    if (fin.fail()) return 0;
    fin >> size;
    if (size <= 0) return 0;
    if (size > n)
    {
        size = n;
    }
    double d;
    for (int i = 0; i < size; i++)
    {
        fin >> d;
        arr[i] = d;
    }
    fin.close();
    return size;
}


void WriteArrayBinFile(int n, double* arr, const char* fileName)
{
    //ios_base
    ofstream bfout(fileName, ios_base::binary);
    if (bfout.fail()) return;
    bfout.write((const char*)&n, sizeof(int));
    std::streamsize  cn = static_cast<std::streamsize>(n) * sizeof(double);
    bfout.write((const char*)arr, cn);
    bfout.close();
}

int ReadArrayBinFile(int n, double* arr, const char* fileName)
{
    int size = 0;
    ifstream bfin(fileName, ios_base::binary);
    if (bfin.fail()) return 0;
    bfin.read((char*)&size, sizeof(int));
    if (size <= 0) return 0;
    if (size > n) size = n;
    bfin.read((char*)arr, static_cast<std::streamsize>(size) * sizeof(double));
    bfin.close();
    // ssdhs
    return size;
}

void WriteResultBinFile(double result, const char* fileName)
{
    //ios_base
    ofstream bfout(fileName, ios_base::binary);
    if (bfout.fail()) return;
    bfout.write((const char*)&result, sizeof(double));
    bfout.close();
}
void WriteResultTextFile(double result, const char* fileName)
{
    ofstream fout(fileName);
    if (!fout.is_open()) return;
    if (fout.fail()) return;
    fout << result;
    fout.close(); //
}

void ShowMainMenu()
{
    cout << "    Main Menu  \n";
    cout << "    1.  Task 1  \n";
    cout << "    2.  Task 2  \n";
    cout << "    3.  Task 3  \n";
}


void Task1()
{
    double* a, * b, * c; //pointers for dynamic arrays
    int m, n, size; // sizes of arrays 
    int c_index = 0; // counter for index of array C
    //input dynamic arrays
    cout << "Arrey A:" << endl;
    n = ConsoleInputDynamicArrayNew(MAX_SIZE, a);
    cout << "Arrey B:" << endl;
    m = ConsoleInputDynamicArrayNew(MAX_SIZE, b);
    size = n + m;
    c = new double[size];
    //sorting array elements
    for (int i = 0; i < n; i++) {
        if (a[i] > 0) {
            c[c_index] = a[i];
            c_index++;
        }
    }

    for (int i = 0; i < m; i++) {
        if (b[i] > 0) {
            c[c_index] = b[i];
            c_index++;
        }
    }

    for (int i = 0; i < n; i++) {
        if (a[i] < 0) {
            c[c_index] = a[i];
            c_index++;
        }
    }

    for (int i = 0; i < m; i++) {
        if (b[i] < 0) {
            c[c_index] = b[i];
            c_index++;
        }
    }
    //-----------output------------------------------
    WriteArrayTextFile(size, c, "Task1Result.txt");
    WriteArrayBinFile(size, c, "Task1Result.bin");
    cout << "Array C:" << endl;
    for (int i = 0; i < size; i++)
        cout << "C[" << i << "] = " << c[i] << "\t";

    delete[]a;
    delete[]b;
    delete[]c;
    return;
}

void Task2()
{
    int n = 0, i = 0, ak, bk;
    double* a;
    int first_positive_index, max;
    double first_max_index;
    a = new double[MAX_SIZE];
    ReadArrayTextFile(n, a, "forRead.txt");
    if (n == 0)
    {
        ReadArrayBinFile(n, a, "forRead.bin");   //if the file is not read, the input will be performed manually
        if (n == 0)
        {
            cout << "Input N:" << endl;
            cin >> n;
            a = new double[n];
            cout << "Input arr A:" << endl;
            for (i = 0; i < n; i++) {
                cout << "A[" << i << "]: ";
                cin >> *(a + i);
            }
        }
    }

    cout << "Input ak:" << endl;
    cin >> ak;
    cout << "Input bk:" << endl;
    cin >> bk;
    //looking for first positive element
    for (i = 0; i < n; i++) {
        if (*(a + i) > 0) {
            first_positive_index = i;
            break;
        }
    }
    //looking for first max when first positive is to the left of the range 
    if (ak > first_positive_index) {
        max = a[ak];
        for (i = ak; i <= bk; i++) {
            if (*(a + i) > max) {
                max = *(a + i);
                first_max_index = i;
            }
        }
        WriteResultTextFile(first_max_index, "Task2Result.txt");
        WriteResultBinFile(first_max_index, "Task2Result.bin");
        cout << "index of the first maximal element: " << first_max_index;
    }
    //looking for first max when first positive in the range 
    else if (ak <= first_positive_index && bk > first_positive_index) {
        max = a[first_positive_index + 1];
        for (i = first_positive_index + 1; i <= bk; i++) {
            if (*(a + i) > max) {
                max = *(a + i);
                first_max_index = i;
            }
        }
        WriteResultTextFile(first_max_index, "Task2Result.txt");
        WriteResultBinFile(first_max_index, "Task2Result.bin");
        cout << "index of the first maximal element: " << first_max_index;
    }
    else
        cout << "there is no way:(" << endl;

    delete[]a;

    return;
}

void Task3()
{
    int n, k;
    double  a[200], b[200];
    char sign_of_choice;
    cout << "if you want random input array press r, else just press random letter: ";
    cin >> sign_of_choice;
    if (sign_of_choice == 'r') {
        n = RndInputArray(MAX_SIZE, a);
        WriteArrayTextFile(200, a, "Task3WriteFile.txt");
        WriteArrayBinFile(200, a, "Task3WriteFile.bin");
    }
    else {
        cout << "Input arr A:" << endl;
        n = ConsoleInputArray(MAX_SIZE, a);
    }
    cout << endl;
    cout << "Input k: ";
    cin >> k;
    /*pin k values from the end of array
    to shift it on the start,
    after all elements, except the first k, are shifted */
    for (int i = 0; i < k; i++) {
        b[i] = a[i + n - k];
    }
    //shift all elements, except the first ones, by k values right
    for (int i = n; i > 0; i--) {
        if (i - k >= 0) {
            a[i] = a[i - k];
        }
    }
    //put values from the end to start
    for (int i = 0; i < k; i++) {
        a[i] = b[i];
    }
    //output
    WriteArrayTextFile(200, a, "Task3Result.txt");
    WriteArrayBinFile(200, a, "Task3Result.bin");
    for (int i = 0; i < n; i++) cout << a[i] << '\t';
    return;
}




int main()
{




    ShowMainMenu();
    int v;
    do {
        cin >> v;
    } while (v < 1 || v>3);
    system("CLS");
    switch (v)
    {
    case 1:
    {
        Task1();
    }
    break;
    case 2:
    {
        Task2();
    }
    break;
    case 3:
    {
        Task3();
    }
    break;
    default:
        break;
    }
    return 1;

}