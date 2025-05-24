#include <iostream>
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

void createFile(const std::string& filename) {
    std::ofstream file(filename);
    if (file) {
        file << "This is a sample file.\n";
        std::cout << "File created: " << filename << std::endl;
    } else {
        std::cerr << "Failed to create file.\n";
    }
}

void deleteFile(const std::string& filename) {
    if (fs::remove(filename)) {
        std::cout << "File deleted: " << filename << std::endl;
    } else {
        std::cerr << "File not found or couldn't delete.\n";
    }
}

void copyFile(const std::string& source, const std::string& destination) {
    try {
        fs::copy(source, destination, fs::copy_options::overwrite_existing);
        std::cout << "File copied from " << source << " to " << destination << std::endl;
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Copy failed: " << e.what() << std::endl;
    }
}

void moveFile(const std::string& source, const std::string& destination) {
    try {
        fs::rename(source, destination);
        std::cout << "File moved from " << source << " to " << destination << std::endl;
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Move failed: " << e.what() << std::endl;
    }
}

int main() {
    std::string filename = "example.txt";
    std::string copyname = "copy_example.txt";
    std::string movedname = "moved_example.txt";

    createFile(filename);          
    copyFile(filename, copyname);  
    moveFile(copyname, movedname); 
    deleteFile(filename);          
    deleteFile(movedname);         

    return 0;
}
