/*Дана последовательность чисел.
Отсортировать и вывести последовательность чисел, определённым методом.*/
#include <iostream>
#include <algorithm>
//Функция для обмена элементов местами
void swap(int& a, int& b)
{
    int temp = a;
    a = b;
    b = temp;
}
class Sorting
{
private:
public:
    ///№4 Пузырёк
    void bubbleSort(int arr[], int n)
    {
        for (int i = 0; i < n - 1; i++) //Наружний цикл от 0 до n-1
        {
            for (int j = 0; j < n - i - 1; j++) //Внутренний цикл от 0 до n-i-1
            {
                if (arr[j] < arr[j + 1]) //Если элемент меньше последующего
                {
                    swap(arr[j], arr[j+1]); //Меняем их местами
                }
            }
        }
    }
    ///№5 Вставками
    //Проверяем между собой второй элемент с первым и, если надо, меняем местами.
    // Сравниваем следующую пару элементов и проверяем все пары до нее.
    void insertionSort(int arr[], int n)
    {
        for (int i = 1; i < n; i++)
        {
            int key = arr[i];
            int j = i - 1;
            while (j >= 0 && arr[j] < key)
            {
                arr[j + 1] = arr[j];
                j--;
            }
            arr[j + 1] = key;
        }
    }
    ///№6 Посредством выбора
    //Ищем наименьшее значение в массиве и ставим его на позицию,
    //откуда начали проход. Потом двигаемся на следующую позицию.
    void selectionSort(int arr[], int n)
    {
        for (int i = 0; i < n - 1; i++)
        {
            int minIndex = i;
            for (int j = i + 1; j < n; j++)
            {
                if (arr[j] > arr[minIndex])
                {
                    minIndex = j;
                }
            }
            swap(arr[i], arr[minIndex]);
        }
    }
    ///№7 Шелла
    //Исходный массив размером N разбивается на подмассивы с шагом N/2. Подмассивы сортируются вставками.
    //Затем вновь разбиваются, но уже с шагом равным N/4. Цикл повторяется.
    //Производим целочисленное деление шага на два каждую итерацию.
    //Когда шаг становится равен 1, массив просто сортируется вставками.
    void shellSort(int arr[], int n)
    {
        for (int step = n/2; step > 0; step /= 2) // Выбираем шаг
        {
            for (int i = step; i < n; i++) // Применяем сортировку вставками для каждого сегмента
            {
                int temp = arr[i];
                int j;
                for (j = i; j >= step && arr[j - step] > temp; j -= step) // Сравнивем, меняем
                 {
                     arr[j] = arr[j - step];
                 }
                arr[j] = temp;
            }
        }
    }
    ///№8 Корневая
    //Его вычислительная сложность O(k * n), где k количество проходов по массиву. Если n достаточно велико,
    // а k наоборот очень мало, то данный алгоритм выигрывает у O(n * Log n).
    //Максимальное число из массива
    int getMax(int arr[], int n)
    {
        int mx = arr[0];
        for (int i = 1; i < n; i++)
            if (arr[i] > mx)
                mx = arr[i];
        return mx;
    }
    //Считает появление той или иной цифры в каждом разряде и сортирует вспомогательный массив
    void countSort(int arr[], int n, int exp)
    {
        //Объявляем вспомогательный массив
        int output[n];
        int i, count[10] = { 0 };
        for (i = 0; i < n; i++)
            count[(arr[i] / exp) % 10]++;
        for (i = 1; i < 10; i++)
            count[i] += count[i - 1];
        //Заполняем вспомогательный массив
        for (i = n - 1; i >= 0; i--) {
            output[count[(arr[i] / exp) % 10] - 1] = arr[i];
            count[(arr[i] / exp) % 10]--;
        }
        //Запихиваем вспомогательный массив в изначальный
        for (i = 0; i < n; i++)
            arr[i] = output[i];
    }
    //Сама сортировка
    void radixSort(int arr[], int n)
    {
        int m = getMax(arr, n);
        for (int exp = 1; m / exp > 0; exp *= 10)
            countSort(arr, n, exp);
    }

    ///№9 Пирамидальная
    //Принцип работы пирамидальной сортировки заключается в построении кучи (heap) из заданного массива и последующем извлечении элементов из этой кучи.
    //Куча представляет собой бинарное дерево, у которого каждый узел имеет не более двух потомков.
    //В куче каждый родительский элемент больше или равен своим потомкам.
    // При построении кучи на каждом шаге выбирается наибольший элемент и помещается в корень дерева.
    // Затем корень меняется местами с последним элементом в массиве, и этот элемент удаляется из кучи.
    // Таким образом, на каждой итерации наибольший элемент перемещается в конец массива, а оставшиеся элементы снова формируют кучу.
    // Когда все элементы извлечены, массив будет отсортирован по возрастанию.

    // Функция для создания кучи (heap) заданного размера
    void heapCreation (int arr[], int n, int i)
    {
        int largest = i; //Наибольший элемент кучи - корень дерева
        int left = 2 * i + 1; //Левый потомок
        int right = 2 * i + 2; //Правый потомок
        //Если левый потомок больше корня, он становится корнем
        if (left < n && arr[left] > arr[largest])
        {
            largest = left;
        }
        // Если правый потомок больше, чем самый большой элемент на данный момент, он становится им
        if (right < n && arr[right] > arr[largest])
        {
            largest = right;
        }
        // Если наибольший элемент не корень, делаем, чтоб это было так
        if (largest != i)
        {
            swap(arr[i], arr[largest]);
            // Рекурсивно строим кучу для поддерева
            (arr, n, largest);
        }
    }
    //Сама функция пирамидальной сортировки (сортировки с использованием хипа
    void heapSort(int arr[], int n)
    {
    //Построение кучи (по-сути, уже перегруппировка массива)
    for (int i = n / 2 - 1; i >= 0; i--)
    {
        heapCreation(arr, n, i);
    }
        // Извлекаем элементы по одному из кучи
        for (int i = n - 1; i >= 0; i--)
        {
            // Перемещаем текущий корень в конец
            swap(arr[0], arr[i]);
            // Вызываем ту же процедуру на уменьшенной куче
            heapCreation(arr, i, 0);
        }
    }
    ///№10 Слиянием
    //Cортировка слиянием делит большой массив на два меньших подмассива, а затем рекурсивно сортирует подмассивы.

    ///№11 Быстрая
    //Массив разделяется на подмассивы, которые сортируются и затем сливаются в один.
    //Выбераем элемент, Все значения больше него элемента ставятся после него, остальные — перед. И так много раз)
    /*1. Выбираем опорный элемент из массива. Обычно это средний элемент.
    2. Разделяем массив на две части: элементы, меньшие опорного элемента, и элементы, большие опорного элемента.
    3. Рекурсивно сортируем каждую из двух частей.
    4. Объединяем отсортированные части в один массив.*/
    //Сложность дщ
    void quickSort(int arr[], int left, int right, int n)
{
    int i = left ; //Первый элемент массива
    int j = right; //Последний элемент массива
    int pivot = arr[(left + right) / 2]; //Средний элемент массива
    while (i <= j)
    {
        while (arr[i] < pivot) //Пока элемент из правой части меньше среднего, идём дальше
        {
            i++;
        }
        while (arr[j] > pivot) //Пока элемент из левой части больше среднего, идём дальше
        {
            j--;
        }
        if (i <= j) //Mеняем местами элементы, которые не прошли проверку))
        {
            swap(arr[i], arr[j]);
            i++;
            j--;
        }
    }//Потом функция вызывает саму себя для каждой из двух частей
    if (left < j)
    {
        quickSort(arr, left, j, n);
    }
    if (i < right)
    {
        quickSort(arr, i, right, n);
    }
}
    ///№12 Внешняя многофазная
    /*// Программа реализует внешнюю многофазную сортировку
// Функция для разделения входного массива на подмассивы и их сортировки
void externalMultiwayMergeSort(std::vector<int>& arr, int chunkSize) {
    int n = arr.size();
    int numChunks = (n + chunkSize - 1) / chunkSize; // Вычисляем количество подмассивов
    for (int i = 0; i < numChunks; i++) {
        int start = i * chunkSize;
        int end = std::min((i + 1) * chunkSize, n);
        std::sort(arr.begin() + start, arr.begin() + end); // Сортируем каждый подмассив
    }

    std::vector<int> result(n);
    std::vector<int> index(numChunks, 0); // Создаем вспомогательный массив для отслеживания текущего элемента в каждом подмассиве

    for (int i = 0; i < n; i++) {
        int minIndex = -1;
        for (int j = 0; j < numChunks; j++) {
            if (index[j] < (j + 1) * chunkSize && (minIndex == -1 || arr[index[j]] < arr[index[minIndex]])) {
                minIndex = j; // Находим индекс минимального элемента среди текущих элементов каждого подмассива
            }
        }
        result[i] = arr[index[minIndex]]; // Записываем минимальный элемент в результирующий массив
        index[minIndex]++; // Увеличиваем индекс текущего элемента в подмассиве, из которого был выбран минимальный элемент
    }

    arr = result; // Заменяем исходный массив отсортированным
}

int main() {
    std::vector<int> arr = {5, 2, 7, 3, 9, 8, 1, 4, 6}; // Исходный массив
    int chunkSize = 3; // Размер подмассива

    externalMultiwayMergeSort(arr, chunkSize); // Вызываем функцию для внешней многофазной сортировки

    std::cout << "Sorted array: ";
    for (int num : arr) {
        std::cout << num << " "; // Выводим отсортированный массив
    }

    return 0;
}*/
};


int main()
{
    int sizeOfYou;
    std::cout << "What number of elements do you want?" << std::endl;
    std::cin >> sizeOfYou;
    const int size = sizeOfYou;
    int mass[size];
    std::cout << "Enter your lovely " << size << " character array." << std::endl;
    for (int i = 0; i < size; i++)
    {
        std::cin >> mass[i];
    }
    Sorting test;
    //test.bubbleSort(mass, size);
    //test.insertionSort(mass, size);
    //test.selectionSort(mass, size);
    //test.shellSort(mass, size);
    test.radixSort();
    //test.heapSort(mass, size);
    test.quickSort(mass, 0, size-1, size);
    std::cout << "Here is your delicious sorted array:" << std::endl;
    for (int i = 0; i < size; i++)
    {
        std::cout << mass[i] << " ";
    }
    return 0;
}
