#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

mutex m;

class Counter {
private:
    int value;

public:
    Counter(int number) {
        value = number;
    }

    ~Counter() {
    }
    
    void Increment() {
        for (int i = 0; i < 100; i++) {
            m.lock();
            value++;
            cout << "made increment: " << i + 1 << "   result: " << value << "\n";
            m.unlock();
        }
    }

    void Decrement() {
        for (int i = 0; i < 10; i++) {
            m.lock();
            value--;
            cout << "made decrement: " << i + 1 << "   result: " << value << "\n";
            m.unlock();
        }
    }

    void Printing() {
        cout << value << "\n";
    }
};

Counter counter(0);

int main() {
    
    thread incrementing(&Counter::Increment, &counter);
    std::thread decrementing(&Counter::Decrement, &counter);

    incrementing.join();
    decrementing.join();

    return 0;
}