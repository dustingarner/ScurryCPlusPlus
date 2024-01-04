#include <iostream>

using std::cout;
using std::endl;

class Box{
    public:
    Box(int a, int b, int c){volume = a * b * c;}
    int volume;
};

int main(){
    Box* ptr1;
    Box* ptr2;

    auto start = std::chrono::system_clock::now();
    int counter = 0;
    while(counter < 100000000){
        counter++;
    }
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed = end-start;
    auto a = elapsed.count();
    int b= 5;

}