#include<iostream>
using namespace std;

class ShiftArray{
    int *arr, size;
public:
    ShiftArray(float* input, int n){
        size = n;
        arr = new int[size];
        for(int i=0; i<size; i++){
            arr[i] = (int)input[i];
        }
    }
    ShiftArray(const ShiftArray& s){
        size = s.size;
        arr = new int[size];
        for(int i=0; i<size; i++){
            arr[i] = s.arr[i];
        }
    }
    ShiftArray& operator=(const ShiftArray& s){
        if(this == &s) return *this;
        delete []arr;
        size = s.size;
        arr = new int[size];
        for(int i=0; i<size; i++){
            arr[i] = s.arr[i];
        }
        return *this;
    }
    ~ShiftArray(){
        delete []arr;
    }
    void Print() const{
        for(int i=0; i<size; i++){
            cout<<arr[i]<<" ";
        }
        cout<<endl;
    }
    ShiftArray& operator<<=(int x){
        if(size==0) return *this;
        x=x%size;
        int* temp=new int[size];
        for(int i=0; i<size; i++){
            temp[i] = arr[(i+x)%size];
        }
        delete []arr;
        arr = temp;
        return *this;
    }
    ShiftArray& operator>>=(int x){
        if(size==0) return *this;
        x=x%size;
        int* temp=new int[size];
        for(int i=0; i<size; i++){
            temp[i] = arr[(i+size-x)%size];
        }
        delete []arr;
        arr = temp;
        return *this;
    }
    ShiftArray operator<<(int x){
        if(size==0) return *this;
        x=x % size;
        return (*this <<= x);
    }
    ShiftArray operator>>(int x){
        if(size==0) return *this;
        x=x % size;
        return (*this >>= x);
    }
};

int main() {
 float init[] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f};
 ShiftArray arr(init, 5);
 // Left shift by 2 positions
 ShiftArray leftShifted = arr << 2;
 cout << "Left shifted by 2: " ;
 leftShifted.Print();
 cout << endl;
 // Right shift by 3 positions
 ShiftArray rightShifted = arr >> 3;
 cout << "Right shifted by 3: ";
 rightShifted.Print();
 cout << endl;
 // In-place shifting using compound operators
 arr <<= 1;
 cout << "After <<= 1: ";
 arr.Print();
 cout << endl;
 arr >>= 2;
 cout << "After >>= 2: ";
 arr.Print();
 cout << endl;
 return 0;
}