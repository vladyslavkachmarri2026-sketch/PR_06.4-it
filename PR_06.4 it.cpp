// Динамічний масив з n дійсних елементів:
//   1.1 номер максимального за модулем елемента
//   1.2 сума елементів після першого додатного
//   2   перестановка: спочатку елементи, ціла частина яких лежить в [a, b],
//       потім усі інші; відносний порядок зберігається

#include <iostream>   
#include <iomanip>    
#include <cmath>      
#include <cstdlib>    
#include <ctime>      
using namespace std;  

// Заповнює масив випадковими дійсними числами з діапазону [Low; High]
void Create(double* a, const int size, const double Low, const double High)
{
    for (int i = 0; i < size; i++)                      
        a[i] = Low + (High - Low) * rand() / RAND_MAX;  // rand()/RAND_MAX лежить в [0; 1],
    // масштабуємо до [Low; High]
}

// Виводить масив в один рядок, усі елементи в однаковому форматі
void Print(double* a, const int size)
{
    for (int i = 0; i < size; i++)                     
        cout << setw(8) << fixed << setprecision(2) << a[i]; // ширина 8, 2 знаки після коми
    cout << endl;                                       
}

// 1.1 Повертає НОМЕР (індекс) елемента з найбільшим модулем
int IndexMaxAbs(double* a, const int size)
{
    int imax = 0;                          
    for (int i = 1; i < size; i++)         
        if (fabs(a[i]) > fabs(a[imax]))    // модуль поточного більший за найкращий?
            imax = i;                      // так - запам'ятовую новий індекс
    return imax;                           // повертаю результат у місце виклику
}

// Повертає індекс першого додатного елемента, або -1, якщо його немає
int IndexFirstPositive(double* a, const int size)
{
    for (int i = 0; i < size; i++)         // скануємо з початку
        if (a[i] > 0)                      // елемент додатний?
            return i;                      // так - одразу виходимо і повертаємо індекс
    return -1;                             
}

// 1.2 Повертає суму елементів, розташованих після елемента з індексом ifirst
double SumAfter(double* a, const int size, const int ifirst)
{
    double s = 0;                           // сума починається з нуля
    for (int i = ifirst + 1; i < size; i++) // починаємо одразу після ifirst і йдемо до кінця
        s += a[i];                          // додаємо поточний елемент
    return s;                               // повертаємо результат
}

// Повертає true, якщо ціла частина x лежить в інтервалі [A; B]
bool IntPartInRange(const double x, const double A, const double B)
{
    double ip = floor(x);                  // ціла частина (floor(-4.27) = -5)
    return ip >= A && ip <= B;             // обидві межі входять в інтервал
}

// 2. Стабільна перестановка: спочатку елементи з цілою частиною в [A; B],
//    потім усі інші; відносний порядок у кожній групі зберігається
void MoveByIntPart(double* a, const int size, const double A, const double B)
{
    double* tmp = new double[size]();            // допоміжний динамічний масив (() - обнулення)
    int k = 0;                                   // наступна вільна позиція в tmp

    for (int i = 0; i < size; i++)                   // 1-й прохід: елементи, що задовольняють умову
        if (k < size && IntPartInRange(a[i], A, B))  // k < size - захист від виходу за межі
            tmp[k++] = a[i];                         // копіюємо в tmp і зсуваємо k

    for (int i = 0; i < size; i++)         // 2-й прохід: усі інші елементи
        if (k < size && !IntPartInRange(a[i], A, B))
            tmp[k++] = a[i];               // дописуємо після першої групи

    for (int i = 0; i < size; i++)         // копіюємо результат назад в оригінальний масив
        a[i] = tmp[i];

    delete[] tmp;                          // звільняємо допоміжний масив (дужки [] обов'язкові)
}

int main()
{
    srand((unsigned)time(NULL));           // початкове значення генератора: щоразу новий масив

    int n;                                 // кількість елементів
    double A, B;                           // межі інтервалу [A; B]
    cout << "n = "; cin >> n;              // вводимо n з клавіатури
    if (n <= 0)                            // масив має містити хоча б один елемент
    {
        cout << "n must be positive" << endl;
        return 1;                          // завершуємо з кодом помилки
    }
    cout << "a = "; cin >> A;              // нижня межа інтервалу
    cout << "b = "; cin >> B;              // верхня межа інтервалу

    double* a = new double[n];             // створюємо динамічний масив з n елементів

    Create(a, n, -10, 10);                 // заповнюємо випадковими числами з [-10; 10]
    cout << "Initial array:" << endl;
    Print(a, n);                           // виводимо початковий масив

    // Завдання 1.1
    int imax = IndexMaxAbs(a, n);          // індекс максимального за модулем
    cout << "Index of the element with the maximum absolute value: " << imax
        << " (value " << a[imax] << ")" << endl;

    // Завдання 1.2
    int ifirst = IndexFirstPositive(a, n); // індекс першого додатного елемента
    if (ifirst == -1)                      // додатних елементів немає
        cout << "There are no positive elements - the sum cannot be calculated" << endl;
    else
        cout << "Sum of the elements after the first positive one: "
        << SumAfter(a, n, ifirst) << endl;

    // Завдання 2
    MoveByIntPart(a, n, A, B);             // перетворюємо масив на місці
    cout << "Transformed array:" << endl;
    Print(a, n);                           // виводимо результат в тому ж форматі

    delete[] a;                            // знищуємо динамічний масив
    return 0;                              // успішне завершення програми
}