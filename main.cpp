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

//  GÜNCELLEME: strcpy yerine strncpy kullanıldı, böylece taşma riski ortadan kalktı.
// Ayrıca hedef arabelleğin son karakterinin '\0' olduğundan emin olundu.
void vulnerableFunction(const char* input) {
    char buffer[32];
    strncpy(buffer, input, sizeof(buffer) - 1);
    buffer[sizeof(buffer) - 1] = '\0'; // güvenli bitiş karakteri
    cout << "[*] You entered: " << buffer << endl;
}

//  GÜNCELLEME: Kullanıcı ismi sistem komutuna doğrudan eklenmek yerine doğrulama yapılmalı
void createUser(const char* username) {
    // Güvenlik için klasör ismi sadece harf ve rakam içersin
    for (int i = 0; username[i]; ++i) {
        if (!isalnum(username[i])) {
            cerr << "[!] Invalid characters in username." << endl;
            return;
        }
    }

    string command = "mkdir users/";
    command += username;
    system(command.c_str());
    cout << "[*] Created folder for user: " << username << endl;
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        cerr << "Usage: " << argv[0] << " <username> <file_to_read>" << endl;
        return 1;
    }

    cout << "[*] Starting application..." << endl;

    //  GÜNCELLEME: vulnerableFunction fonksiyonu const char* ile çağrıldı, strncpy kullanımı ile birlikte güvenli hale getirildi
    vulnerableFunction(argv[1]);

    // GÜNCELLEME: createUser fonksiyonu içerisinde kullanıcı adı doğrulaması eklendi (alphanumeric kontrolü)
    createUser(argv[1]);

    readFile(argv[2]);

    cout << "[*] Done." << endl;
    return 0;
}
