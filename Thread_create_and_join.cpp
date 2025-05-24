#include <iostream>
#include <thread>

void printMessage(int id, const std::string& message) {
    std::cout << "Thread " << id << ": " << message << std::endl;
}

int main() {
    std::thread t1(printMessage, 1, "Hello from thread 1");
    std::thread t2(printMessage, 2, "Hello from thread 2");

    
    t1.join();
    t2.join();

    std::cout << "Main thread finished." << std::endl;
    return 0;
}
