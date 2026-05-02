#include <chrono>
#include <iostream>

int main(int argc, char *argv[])
{
   auto start_time = std::chrono::steady_clock::now();
   auto current_time = std::chrono::steady_clock::now();
   int count = 0;
   std::chrono::microseconds duration(16667);
   std::chrono::duration<double> elapsed = current_time - start_time;
    while(count < 100) {
        if(elapsed >= duration) {
            std::cout << count << " intervals passed" << std::endl;
            ++count;
            start_time = std::chrono::steady_clock::now();
        }
        current_time = std::chrono::steady_clock::now();
        elapsed = current_time - start_time;
    }
   return 0;
}
