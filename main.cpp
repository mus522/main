#include <iostream>
#include <cstring>
#include <fstream>
#include <cstdlib>

using namespace std;

void readFile(const char* filename) {
    ifstream file(filename);
    if (!file) {
        cerr << "[!] Cannot open file: " << filename << endl;
        return;
    }
    
    char line[256];
    while (file.getline(line, sizeof(line))) {
        cout << line << endl;
    }
}

void vulnerableFunction(char* input) {
    char buffer[32];
    strcpy(buffer, input); // ❌ ثغرة buffer overflow
    cout << "[*] You entered: " << buffer << endl;
}

void createUser(const char* username) {
    string command = "mkdir users/";
    command += username; // ❌ ثغرة command injection ممكنة
    system(command.c_str());
    cout << "[*] Created folder for user: " << username << endl;
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        cerr << "Usage: " << argv[0] << " <username> <file_to_read>" << endl;
        return 1;
    }

    cout << "[*] Starting application..." << endl;

    vulnerableFunction(argv[1]);
    createUser(argv[1]);
    readFile(argv[2]);

    cout << "[*] Done." << endl;
    return 0;
}
