//16667 microseconds for each update

#include <chrono>
#include <iostream>

int main(int argc, char *argv[])
{
   auto start_time = std::chrono::high_resolution_clock::now();
   auto current_time = std::chrono::high_resolution_clock::now();
   std::chrono::seconds finish(10);
   std::chrono::seconds count(0);
   std::chrono::duration<double> elapsed = current_time - start_time;
    while(count < finish) {
        if(elapsed >= count) {
            std::cout << "Program has been running for " << std::chrono::duration_cast<std::chrono::seconds>(current_time - start_time).count() << " seconds" << std::endl;
            ++count;
        }
        current_time = std::chrono::high_resolution_clock::now();
        elapsed = current_time - start_time;
    }
   return 0;
}
