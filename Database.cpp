#include "Database.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <stdexcept>

// operator[]

Student& Database::operator[](size_t index) {
    if (index >= data.size())
        throw std::out_of_range("Индекс за пределами массива");
    return data[index];
}

const Student& Database::operator[](size_t index) const {
    if (index >= data.size())
        throw std::out_of_range("Индекс за пределами массива");
    return data[index];
}

// Размер

size_t Database::size() const { return data.size(); }
bool Database::empty() const { return data.empty(); }

//  Вставка / Удаление

void Database::add(const Student& s) {
    data.push_back(s);
}

void Database::removeAt(size_t index) {
    if (index >= data.size())
        throw std::out_of_range("Индекс за пределами массива");
    data.erase(data.begin() + index);
}

//  Сортировки

void Database::sortByName(bool ascending) {
    std::sort(data.begin(), data.end(),
        [ascending](const Student& a, const Student& b) {
            return ascending ? a.name < b.name : a.name > b.name;
        });
}

void Database::sortByAge(bool ascending) {
    std::sort(data.begin(), data.end(),
        [ascending](const Student& a, const Student& b) {
            return ascending ? a.age < b.age : a.age > b.age;
        });
}

void Database::sortByGpa(bool ascending) {
    std::sort(data.begin(), data.end(),
        [ascending](const Student& a, const Student& b) {
            return ascending ? a.gpa < b.gpa : a.gpa > b.gpa;
        });
}

//  Вывод таблицы

void Database::print() const {
    if (data.empty()) {
        std::cout << "  (база пуста)\n";
        return;
    }

    size_t maxNameLen = 4;
    for (auto& s : data)
        if (s.name.size() > maxNameLen)
            maxNameLen = s.name.size();

    std::string sep(maxNameLen + 30, '-');

    std::cout << sep << "\n";
    std::cout << "| " << std::left << std::setw(4) << "#"
              << "| " << std::setw(maxNameLen) << "Имя"
              << " | " << std::setw(7) << "Возраст"
              << " | " << std::setw(6) << "GPA"
              << " |\n";
    std::cout << sep << "\n";

    for (size_t i = 0; i < data.size(); ++i) {
        std::cout << "| " << std::left << std::setw(4) << i
                  << "| " << std::setw(maxNameLen) << data[i].name
                  << " | " << std::setw(7) << data[i].age
                  << " | " << std::fixed << std::setprecision(2)
                  << std::setw(6) << data[i].gpa
                  << " |\n";
    }
    std::cout << sep << "\n";
}

//  Файловый ввод/вывод 

void Database::saveToFile(const std::string& filename) const {
    std::ofstream fout(filename);
    if (!fout.is_open()) {
        std::cerr << "Ошибка: не удалось открыть файл для записи: " << filename << "\n";
        return;
    }
    fout << data.size() << "\n";
    for (auto& s : data) {
        fout << s.name << "\n" << s.age << "\n" << s.gpa << "\n";
    }
    fout.close();
    std::cout << "Сохранено в " << filename << " (" << data.size() << " записей)\n";
}

void Database::loadFromFile(const std::string& filename) {
    std::ifstream fin(filename);
    if (!fin.is_open()) {
        std::cerr << "Ошибка: не удалось открыть файл для чтения: " << filename << "\n";
        return;
    }
    size_t count;
    fin >> count;
    fin.ignore();

    data.clear();
    for (size_t i = 0; i < count; ++i) {
        Student s;
        std::getline(fin, s.name);
        fin >> s.age >> s.gpa;
        fin.ignore();
        data.push_back(s);
    }
    fin.close();
    std::cout << "Загружено из " << filename << " (" << data.size() << " записей)\n";
}

const std::vector<Student>& Database::getData() const {
    return data;
}
