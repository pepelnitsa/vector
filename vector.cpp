#include <iostream>
#include <windows.h>
using namespace std;

class Vector
{
    unsigned int size = 0; // количество действительно присутствующих элементов в контейнере
    unsigned int capacity = 10; // ёмкость (вместительность, запас памяти)
    int* data = nullptr; // указатель на динамический массив целых чисел

public:
    Vector() : Vector(10)
    {
        // cout << "C-TOR WITHOUT PARAMS!\n";
    }

    Vector(unsigned int capacity)
    {
        if (capacity < 10)
        {
            capacity = 10;
        }
        this->capacity = capacity;
        data = new int[capacity];
        // cout << "C-TOR WITH PARAMS!\n";
    }

    Vector(const Vector& other)
    {
        size = other.size;
        capacity = other.capacity;
        data = new int[capacity];

        for (unsigned int i = 0; i < size; ++i)
        {
            data[i] = other.data[i];
        }
    }

    ~Vector()
    {
        // cout << "DESTRUCTOR!\n";
        if (data != nullptr)
        {
            delete[] data;
            data = nullptr;
        }
    }

private:
    void EnsureCapacity()
    {
        if (size < capacity)
        {
            return;
        }

        capacity *= 2;

        int* temp = new int[capacity];
        for (int i = 0; i < size; i++)
        {
            temp[i] = data[i];
        }
        delete[] data;
        data = temp;
    }

    void QuickSortDesc(int low, int high)
    {
        if (low < high)
        {
            int index = PartitionDesc(low, high);
            QuickSortDesc(low, index - 1);
            QuickSortDesc(index + 1, high);
        }
    }

    int PartitionDesc(int low, int high)
    {
        int pivot = data[high];
        int i = low - 1;

        for (int j = low; j <= high - 1; j++)
        {
            if (data[j] >= pivot)
            {
                i++;
                Swap(data[i], data[j]);
            }
        }

        Swap(data[i + 1], data[high]);
        return i + 1;
    }

    void Swap(int& a, int& b)
    {
        int temp = a;
        a = b;
        b = temp;
    }

public:

    void TrimToSize()
    {
        if (size == capacity) return;

        int* temp = new int[size];
        for (int i = 0; i < size; i++)
        {
            temp[i] = data[i];
        }
        delete[] data;
        capacity = size;
        data = temp;
    }

    unsigned int getSize() const
    {
        return size;
    }
    unsigned int getCapacity() const
    {
        return capacity;
    }

    void RandomFill()
    {
        for (int i = 0; i < 5; i++)
        {
            PushBack(rand() % 100);
        }
    }

    int LastIndexOf(int value) const
    {
        for (int i = size - 1; i >= 0; i--)
        {
            if (data[i] == value)
            {
                return i;
            }
        }
        return -1;
    }

    void SortDesc()
    {
        QuickSortDesc(0, size - 1);
    }

    void Shuffle()
    {
        srand(static_cast<unsigned int>(time(nullptr)));
        for (int i = size - 1; i > 0; i--)
        {
            int j = rand() % (i + 1);
            Swap(data[i], data[j]);
        }
    }

    bool GetElementAt(unsigned int index, int& element) const
    {
        if (index < size)
        {
            element = data[index];
            return true;
        }
        else
        {
            cout << "Index out of bounds.\n";
            return false;
        }
    }


    void RemoveByIndex(unsigned int index)
    {
        if (index < size)
        {
            for (int i = index; i < size - 1; i++)
            {
                data[i] = data[i + 1];
            }
            size--;
        }
    }
    void RemoveByValue(int value)
    {
        for (int i = 0; i < size; i++)
        {
            if (data[i] == value)
            {
                for (int j = i; j < size - 1; j++)
                {
                    data[j] = data[j + 1];
                }
                size--;
                i--;
            }
        }
    }
    void PopFront()
    {
        if (size > 0)
        {
            for (int i = 0; i < size - 1; i++)
            {
                data[i] = data[i + 1];
            }
            size--;
        }
    }
    void PopBack()
    {
        if (size > 0)
        {
            size--;
        }
    }

    void PushBack(int value)
    {
        EnsureCapacity(); // проверка, хватит ли места для нового элемента
        data[size] = value;
        size++;
        // cout << capacity << "\n";
    }

    void PushFront(int value)
    {
        EnsureCapacity();
        for (int i = size; i > 0; i--) // i = 1
        {
            data[i] = data[i - 1]; // data[1] = data[0]
        }
        data[0] = value;
        size++;
    }

    void Clear()
    {
        size = 0;
    }

    bool IsEmpty() const
    {
        return size == 0;
    }

    void Print() const
    {
        if (IsEmpty())
        {
            cout << "Vector is empty.\n";
            return;
        }

        for (int i = 0; i < size; i++)
        {
            cout << data[i] << " ";
        }
        cout << "\n";
    }

    Vector& operator = (const Vector& other)
    {
        if (this != &other)
        {
            delete[] data;
            size = other.size;
            capacity = other.capacity;
            data = new int[capacity];

            for (unsigned int i = 0; i < size; ++i)
            {
                data[i] = other.data[i];
            }
        }
        return *this;
    }

    int& operator [] (unsigned int index)
    {
        if (index < size)
        {
            return data[index];
        }
        else
        {
            cout << "Index out of bounds.\n";

        }
    }

    bool operator == (const Vector& other) const
    {
        if (size != other.size)
        {
            return false;
        }

        for (unsigned int i = 0; i < size; ++i)
        {
            if (data[i] != other.data[i])
            {
                return false;
            }
        }

        return true;
    }

    friend ostream& operator << (ostream& output, const Vector& vector)
    {
        output << "Vector (size: " << vector.size << "): ";
        for (unsigned int i = 0; i < vector.size; ++i)
        {
            output << vector.data[i] << " ";
        }
        output << "\n";

        return output;
    }

    friend istream& operator >> (istream& input, Vector& vector)
    {
        unsigned int newSize;
        cout << "Enter new size: ";
        input >> newSize;

        if (newSize < 0)
        {
            cerr << "Error: Invalid size.\n";
            return input;
        }

        vector.size = newSize;

        delete[] vector.data;
        vector.data = new int[vector.size];

        for (unsigned int i = 0; i < vector.size; ++i)
        {
            cout << "Enter element " << i + 1 << ": ";
            input >> vector.data[i];
        }

        return input;
    }

};

int main()
{
    Vector ar;

    Vector vector1;
    Vector vector2;

    srand(time(0));

    ar.RandomFill();
    ar.Print();

    int value_find = ar.LastIndexOf(3);
    cout << value_find << "\n";

    ar.Print();
    ar.SortDesc();
    ar.Print();

    ar.Print();
    ar.Shuffle();
    ar.Print();

    int element;
    if (ar.GetElementAt(0, element))
    {
        cout << "Element at index : " << element << "\n";
    }
    ar.GetElementAt(10, element);

    if (vector1 == vector2)
    {
        cout << "Vectors equal.\n";
    }
    else
    {
        cout << "Vectors not equal.\n";
    }

    Vector ar2;

    cin >> ar2;

    cout << "Vector elements: " << ar2 << "\n";

}