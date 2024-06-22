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

void runREPL()
{
    for(;;)
    {
        std::cout << "> ";
        std::string line;
        std::getline(std::cin, line);
        std::cout << line << ": read repl line from user and now break;" << std::endl;
        break;
    }
}

int main(int argc, char *argv[])
{
    std::cout << argc << " files pasted" << "\n";
    std::cout << argv[1] << " : is a file, and was passed\n";
    std::cout << argv[0] << " : executeable passed\n";

    readFromFile(argv[1]);

    runREPL();

    return 0;
}
