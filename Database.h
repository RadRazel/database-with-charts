#ifndef DATABASE_H
#define DATABASE_H

#include "Student.h"
#include <vector>
#include <string>

class Database {
private:
    std::vector<Student> data;

public:
    Student& operator[](size_t index);
    const Student& operator[](size_t index) const;

    size_t size() const;
    bool empty() const;

    void add(const Student& s);
    void removeAt(size_t index);

    void sortByName(bool ascending = true);
    void sortByAge(bool ascending = true);
    void sortByGpa(bool ascending = true);

    void print() const;

    void saveToFile(const std::string& filename) const;
    void loadFromFile(const std::string& filename);

    const std::vector<Student>& getData() const;
};

#endif // DATABASE_H
