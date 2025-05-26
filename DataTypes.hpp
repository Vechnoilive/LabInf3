#pragma once
#include <string>
#include <ctime>

struct PersonID {
    int series;
    int number;
};

struct Student {
    PersonID id;
    std::string firstName;
    std::string lastName;
    std::time_t birthDate;
};

struct Teacher {
    PersonID id;
    std::string firstName;
    std::string lastName;
    std::string department;
};

inline bool operator==(const Student& a, const Student& b) {
    return a.id.series == b.id.series &&
        a.id.number == b.id.number &&
        a.firstName == b.firstName &&
        a.lastName == b.lastName &&
        a.birthDate == b.birthDate;
}

inline bool operator==(const Teacher& a, const Teacher& b) {
    return a.id.series == b.id.series &&
        a.id.number == b.id.number &&
        a.firstName == b.firstName &&
        a.lastName == b.lastName &&
        a.department == b.department;
}
