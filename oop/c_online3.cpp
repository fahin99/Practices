#include <iostream>
using namespace std;

class ModArray
{
    float *arr;
    int size;

public:
    ModArray(float *input, int n)
    {
        if (n <= 0)
        {
            cout << "Invalid size. Array will be empty." << endl;
            arr = nullptr;
            size = 0;
            return;
        }
        size = n;
        arr = new float[size];
        for (int i = 0; i < size; i++)
        {
            arr[i] = input[i];
        }
    }
    ModArray(const ModArray &m)
    {
        size = m.size;
        arr = new float[size];
        for (int i = 0; i < size; i++)
        {
            arr[i] = m.arr[i];
        }
    }
    ~ModArray()
    {
        delete[] arr;
    }
    void Print() const
    {
        cout<<"[";
        for (int i = 0; i < size-1; i++)
        {
            cout << arr[i] << ", ";
        }
        cout << arr[size-1] << "]" << endl;
    }
    float operator[](float index) const
    {
        if (size == 0)
        {
            cout << "Array is empty." << endl;
            return 0.0f;
        }
        if (index < 0)
        {
            cout << "Negative index. Returning 0." << endl;
            return 0.0f;
        }
        int index_int = (int)index;
        float index_frac = index - index_int;
        if (index_frac == 0)
        {
            if (index_int >= size)
            {
                index_int = index_int % size;
                return arr[index_int];
            }
            else{
                return arr[index_int];
            }
        }
        else
        {
            int index_next = (index_int + 1) % size;
            return arr[index_int] * index_frac + arr[index_next] * (1 - index_frac);
        }
    }
};

int main()
{
    float init[] = {10.0f, 20.0f, 30.0f, 40.0f};
    ModArray arr(init, 4);
    cout << "arr[5] = " << arr[5] << endl;
    cout << "arr[1.5] = " << arr[1.5f] << endl;
    cout << "arr[3.7] = " << arr[3.7f] << endl;
    cout << "Array: ";
    arr.Print();
    return 0;
}