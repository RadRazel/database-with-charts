#include "Database.h"
#include "Charts.h"
#include <iostream>
#include <string>

void printMenu() {
    std::cout << "\n===== МЕНЮ =====\n"
              << "1. Показать все записи\n"
              << "2. Добавить запись\n"
              << "3. Удалить запись по индексу\n"
              << "4. Сортировка\n"
              << "5. Сохранить в файл\n"
              << "6. Загрузить из файла\n"
              << "7. Столбчатая диаграмма\n"
              << "8. Круговая диаграмма\n"
              << "0. Выход\n"
              << "================\n"
              << "Выбор: ";
}

int chooseField() {
    std::cout << "По какому полю? 1 — Возраст, 2 — GPA: ";
    int f;
    std::cin >> f;
    return f;
}

void sortMenu(Database& db) {
    std::cout << "Сортировать по: 1-Имя 2-Возраст 3-GPA: ";
    int field;
    std::cin >> field;

    std::cout << "1 — по возрастанию, 2 — по убыванию: ";
    int dir;
    std::cin >> dir;
    bool asc = (dir == 1);

    switch (field) {
        case 1: db.sortByName(asc); break;
        case 2: db.sortByAge(asc);  break;
        case 3: db.sortByGpa(asc);  break;
        default: std::cout << "Неверный выбор\n"; return;
    }
    std::cout << "Отсортировано!\n";
    db.print();
}

int main(int argc, char* argv[]) {
    Database db;

    // Параметр командной строки — файл
    if (argc > 1) {
        db.loadFromFile(argv[1]);
    }

    // Тестовые данные, если пусто
    if (db.empty()) {
        db.add({"Иванов", 20, 4.5});
        db.add({"Петрова", 19, 4.8});
        db.add({"Сидоров", 21, 3.9});
        db.add({"Козлова", 20, 4.2});
        db.add({"Морозов", 22, 3.5});
        std::cout << "Добавлены тестовые данные (5 студентов)\n";
    }

    int choice = -1;
    while (choice != 0) {
        printMenu();
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Некорректный ввод\n";
            continue;
        }

        switch (choice) {
        case 1:
            db.print();
            break;

        case 2: {
            Student s;
            std::cin.ignore();
            std::cout << "Имя: ";
            std::getline(std::cin, s.name);
            std::cout << "Возраст: ";
            std::cin >> s.age;
            std::cout << "GPA: ";
            std::cin >> s.gpa;
            db.add(s);
            std::cout << "Добавлено!\n";
            break;
        }

        case 3: {
            std::cout << "Индекс: ";
            size_t idx;
            std::cin >> idx;
            try {
                db.removeAt(idx);
                std::cout << "Удалено!\n";
            } catch (const std::out_of_range& e) {
                std::cout << "Ошибка: " << e.what() << "\n";
            }
            break;
        }

        case 4:
            sortMenu(db);
            break;

        case 5: {
            std::cin.ignore();
            std::cout << "Файл: ";
            std::string fn;
            std::getline(std::cin, fn);
            db.saveToFile(fn);
            break;
        }

        case 6: {
            std::cin.ignore();
            std::cout << "Файл: ";
            std::string fn;
            std::getline(std::cin, fn);
            db.loadFromFile(fn);
            break;
        }

        case 7:
            drawBarChart(db, chooseField());
            break;

        case 8:
            drawPieChart(db, chooseField());
            break;

        case 0:
            std::cout << "Выход\n";
            break;

        default:
            std::cout << "Неверный пункт\n";
        }
    }

    return 0;
}
