#include <fstream>
#include <cstdlib>
#include <ctime>

int main() {
    std::srand(std::time(0));
    std::ofstream out("addresses.txt");

    for (int i = 0; i < 1000; ++i) {
        int logical_address = std::rand() % 65536;
        out << logical_address << "\n";
    }

    return 0;
}
