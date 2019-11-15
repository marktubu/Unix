#include <iostream>
#include <mutex>

std::mutex mux;

void func1()
{
    std::lock_guard<std::mutex> lock(mux);
}

int main()
{
    std::lock_guard<std::mutex> lock(mux);
    func1();
    std::cout << "test"<<std::endl;
    return 0;
}
