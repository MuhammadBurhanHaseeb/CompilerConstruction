#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char* argv[]) {
    
    if (argc < 2) {
        std::cerr << "Usage: mycompiler <Burhan.txt>" << std::endl;
        return 1;
    }

    
    std::ifstream file(argv[1]);
    
    
    if (!file.is_open()) {
        std::cerr << "Could not open the file " << argv[1] << std::endl;
        return 1;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::cout <<"Hello " + line << std::endl;
    }


    file.close();
    
    return 0;
}


