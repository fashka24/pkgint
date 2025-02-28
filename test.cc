#include <iostream>

int main(int argc, char const *argv[])
{
    int r = system("sudo apt-get install nothing_pckg") >> 8;
    std::cout << r;
    return 0;
}
