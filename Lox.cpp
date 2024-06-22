#include <fstream>
#include <sstream>
#include <iostream>

void readFromFile(const std::string& path)
{
    const std::ifstream input_stream(path, std::ios::binary);
    std::stringstream buffer;
    buffer << input_stream.rdbuf();

    std::cout << buffer.str() << '\n';
}

int main(int argc, char *argv[])
{
    std::cout << argc << " files pasted" << "\n";
    std::cout << argv[1] << " : is a file, and was passed\n";
    std::cout << argv[0] << " : executeable passed\n";

    readFromFile(argv[1]);

    return 0;
}
