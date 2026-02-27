#include<iostream>
using namespace std;

class coord{
    int x,y;
public:
    coord(){}
    coord(int a, int b){
        x = a;
        y = b;
    }
    coord& operator <<=(int x){
        this->x = this->x << x;
        this->y = this->y << x;
        return *this;
    }
    coord& operator >>=(int x){
        this->x = this->x >> x;
        this->y = this->y >> x;
        return *this;
    }
    coord& operator <<=(coord c){
        this->x = this->x << c.x;
        this->y = this->y << c.y;
        return *this;
    }
    coord& operator >>=(coord c){
        this->x = this->x >> c.x;
        this->y = this->y >> c.y;
        return *this;
    }
    friend ostream& operator<<(ostream& os, const coord& c);
    friend istream& operator>>(istream& is, coord& c);
    void show(){
        cout<<x<<" "<<y<<endl;
    }
};

ostream& operator<<(ostream& os, const coord& c){
    os<<c.x<<" "<<c.y;
    return os;
}
istream& operator>>(istream& is, coord& c){
    is>>c.x>>c.y;
    return is;
}

int main(){
    coord c1(10,20), c2(2,3);
    c1.show();
    c1 <<= 1;
    c1.show();
    c1 >>= 1;
    c1.show();
    c1 <<= c2;
    c1.show();
    c1 >>= c2;
    c1.show();
    cin>>c1;
    cout<<c1;
    return 0;
}