#include "Charts.h"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <sstream>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// Столбчатая диаграмма

void drawBarChart(const Database& db, int field) {
    if (db.empty()) { std::cout << "Нет данных\n"; return; }

    const auto& data = db.getData();
    std::string title = (field == 1) ? "Возраст" : "GPA";
    std::cout << "\n=== Столбчатая диаграмма: " << title << " ===\n\n";

    // Максимум
    double maxVal = 0;
    for (auto& s : data) {
        double v = (field == 1) ? (double)s.age : s.gpa;
        if (v > maxVal) maxVal = v;
    }
    if (maxVal <= 0) { std::cout << "Все значения <= 0\n"; return; }

    const int barMaxWidth = 50;

    // Ширина столбца имён
    size_t nameW = 0;
    for (auto& s : data) if (s.name.size() > nameW) nameW = s.name.size();
    if (nameW < 4) nameW = 4;

    for (auto& s : data) {
        double v = (field == 1) ? (double)s.age : s.gpa;
        int barLen = (int)std::round(v / maxVal * barMaxWidth);
        if (barLen < 1 && v > 0) barLen = 1;

        std::cout << std::left << std::setw(nameW) << s.name << " |";
        for (int i = 0; i < barLen; ++i) std::cout << "█";
        std::cout << " ";
        if (field == 1)
            std::cout << s.age;
        else
            std::cout << std::fixed << std::setprecision(2) << s.gpa;
        std::cout << "\n";
    }

    // Ось
    std::cout << std::string(nameW, ' ') << " +";
    for (int i = 0; i < barMaxWidth + 1; ++i) std::cout << "-";
    std::cout << "\n";

    std::cout << std::string(nameW, ' ') << " 0";
    std::string maxStr;
    if (field == 1) {
        maxStr = std::to_string((int)maxVal);
    } else {
        std::ostringstream o;
        o << std::fixed << std::setprecision(2) << maxVal;
        maxStr = o.str();
    }
    std::cout << std::string(barMaxWidth - (int)maxStr.size(), ' ') << maxStr << "\n\n";
}

//  Круговая диаграмма

void drawPieChart(const Database& db, int field) {
    if (db.empty()) { std::cout << "Нет данных\n"; return; }

    const auto& data = db.getData();
    std::string title = (field == 1) ? "Возраст" : "GPA";
    std::cout << "\n=== Круговая диаграмма: " << title << " ===\n\n";

    // Сумма
    double total = 0;
    for (auto& s : data) {
        double v = (field == 1) ? (double)s.age : s.gpa;
        total += v;
    }
    if (total <= 0) { std::cout << "Сумма <= 0\n"; return; }

    // Символы секторов
    const char symbols[] = "#@*+%&=~^$!?><ABCDEFGHIJ";
    int numSymbols = sizeof(symbols) - 1;

    // Кумулятивные углы
    std::vector<double> cumAngles;
    cumAngles.push_back(0.0);
    for (size_t i = 0; i < data.size(); ++i) {
        double v = (field == 1) ? (double)data[i].age : data[i].gpa;
        cumAngles.push_back(cumAngles.back() + v / total * 2.0 * M_PI);
    }

    // Рисуем круг
    const int R = 12;
    const double aspect = 2.0;

    for (int y = -R; y <= R; ++y) {
        for (int x = (int)(-R * aspect); x <= (int)(R * aspect); ++x) {
            double dx = x / aspect;
            double dy = y;
            double dist = std::sqrt(dx * dx + dy * dy);

            if (dist <= R) {
                double angle = std::atan2(-dy, dx);
                if (angle < 0) angle += 2.0 * M_PI;

                char ch = '.';
                for (size_t i = 0; i < data.size(); ++i) {
                    if (angle >= cumAngles[i] && angle < cumAngles[i + 1]) {
                        ch = symbols[i % numSymbols];
                        break;
                    }
                }
                std::cout << ch;
            } else {
                std::cout << ' ';
            }
        }
        std::cout << "\n";
    }

    // Легенда
    std::cout << "\nЛегенда:\n";
    for (size_t i = 0; i < data.size(); ++i) {
        double v = (field == 1) ? (double)data[i].age : data[i].gpa;
        double pct = v / total * 100.0;
        std::cout << "  " << symbols[i % numSymbols] << "  "
                  << data[i].name << " — ";
        if (field == 1)
            std::cout << data[i].age;
        else
            std::cout << std::fixed << std::setprecision(2) << data[i].gpa;
        std::cout << " (" << std::fixed << std::setprecision(1) << pct << "%)\n";
    }
    std::cout << "\n";
}
