#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <chrono>

std::vector<std::string> pckgs {
    // apps and compilers
    "gcc", "clang", "python3", "python3-pip", "rustup",
    "nasm", "fasm", "dotnet-sdk-9.0", "dotnet-sdk-8.0", "aspnetcore-runtime-9.0", "aspnetcore-runtime-8.0",
    "gimp",
        "vlc",
        "libreoffice",
        "git",
        "code",
        "slack",
        "krita",
        "transmission",
        "steam",
        "blender",
        "audacity",
        "thunderbird",
        "obs-studio",
        "wine",
        "ruby",
        "nodejs",
        "php",
        "perl",
        "swift",
        "rustc",
        "scala",
        "elixir",
    // python modules
    "python3-requests", "python3-lupa", "python3-pyinstaller", "python3-colorama",
    "python3-flask", "python3-toml", "python3-pygame",
    "python3-numpy",
"python3-pandas",
"python3-matplotlib",
"python3-seaborn",
"python3-django",
"python3-scrapy",
"python3-pillow",
"python3-sqlalchemy",
"python3-pytest",
"python3-plotly",
"python3-twisted",
"python3-celery",
"python3-pydantic",
"python3-fastapi",
"python3-tornado",
"python3-sqlmodel",
};
std::vector<std::string> failed_packages = {};

int main() {
    int choice, succ_instl = 0, faild_instl = 0;
    std::string installer, updater;

    // Запрос выбора у пользователя
    printf("Choose package manager (1-5):\n");
    printf("0. cancel\n");
    printf("1. apt-get\n");
    printf("2. pacman\n");
    printf("3. xbps\n");
    printf("4. dnf\n");
    printf("5. yum\n");
    printf(" >> ");
    std::cin >> choice;

    switch (choice) {
        case 0:
            printf("Cancel...\n");
            exit(0);
        case 1:
        installer = "sudo apt-get install -y ";
        updater = "sudo apt-get update ";
            break;
        case 2:
        installer = "sudo pacman -Sy --noconfirm ";
        updater = "sudo pacman -Syu ";
            break;
        case 3:
        installer = "sudo xbps-install -y ";
        updater = "sudo xbps-install -Su ";
            break;
        case 4:
        updater = "sudo dnf update ";
        installer = "sudo dnf install -y ";
            break;
        case 5:
        updater = "sudo yum update ";
        installer = "sudo yum install -y ";
                break;
        default:
            printf("Wrong choose. Please enter your package manager.\n");
            exit(-1);
    }
    char ch1 = '\0';
    
    std::cout << "Installer command: " << installer << "\n\n";
    printf("Installing %d packages, are you sure? (y|n): ", (int)pckgs.size());
    std::cin >> ch1;

    if (ch1 != 'y') {
        printf("Cancel...\n");
        exit(0);
    }

    printf("Update manager...\n");
    int r1 = system(updater.c_str()) >> 8;

    if (r1 != 0) {
        perror ("Error update manager\n");
        exit(-1);
    }

    printf("Start installing...\n");
    auto start = std::chrono::high_resolution_clock::now();
    
    for (size_t i = 0; i < pckgs.size(); i++)
    {
        int r = system((installer + pckgs[i]).c_str()) >> 8;

        if (r != 0) {
            std::cerr << "Error installing pkg: " << pckgs[i] << "\n";
            failed_packages.push_back(pckgs[i]);
            faild_instl++;
        }
        else {
            succ_instl ++;
        }
    }

    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> duration = end - start;

    double minutes = duration.count() / 60.0;
    
    printf("\nInstalling finished!\n");
    printf("Successful installed: %d\n", succ_instl);
    printf("Fail installed: %d\n", faild_instl);
    if (faild_instl > 0) {
        printf("Print failed packages? (y|n) - ");
        std::cin >> ch1;

        if (ch1 == 'y') {
            printf("{ ");
            for (auto pckf1: failed_packages)
            {
                std::cout << pckf1 << " ";
            }
            printf("}\n");
        }
    }
    printf("Installing time: %.2f minute\n", minutes);

    return 0;
}
