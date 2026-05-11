#ifndef CHARTS_H
#define CHARTS_H

#include "Database.h"

// Столбчатая диаграмма в консоли
// field: 1 = age, 2 = gpa
void drawBarChart(const Database& db, int field);

// Круговая диаграмма в консоли (символами)
// field: 1 = age, 2 = gpa
void drawPieChart(const Database& db, int field);

#endif // CHARTS_H
