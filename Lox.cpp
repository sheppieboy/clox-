#include <iostream>

int main(int argc, char *argv[])
{
    std::cout << argc << " files pasted" << "\n";
    std::cout << argv[1] << " : is a file, and was passed\n";
    std::cout << argv[0] << " : executeable passed\n";

    return 0;
}