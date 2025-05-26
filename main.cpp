#include "Utils.hpp"
#include <iostream>
#include <complex>
#include <functional>
#include "Queue.hpp"
#include "ArraySequence.hpp"
#include "DataTypes.hpp"

void PrintIntSeq(Sequence<int>* seq) {
    for (size_t i = 0; i < seq->GetSize(); ++i)
        std::cout << seq->Get(i) << " ";
    std::cout << "\n";
}
void PrintDoubleSeq(Sequence<double>* seq) {
    for (size_t i = 0; i < seq->GetSize(); ++i)
        std::cout << seq->Get(i) << " ";
    std::cout << "\n";
}
void PrintStringSeq(Sequence<std::string>* seq) {
    for (size_t i = 0; i < seq->GetSize(); ++i)
        std::cout << seq->Get(i) << " ";
    std::cout << "\n";
}
void PrintComplexSeq(Sequence<std::complex<double>>* seq) {
    for (size_t i = 0; i < seq->GetSize(); ++i)
        std::cout << "(" << seq->Get(i).real() << "," << seq->Get(i).imag() << ") ";
    std::cout << "\n";
}
void PrintStudentQueue(Queue<Student>& q) {
    while (!q.IsEmpty()) {
        Student s = q.Dequeue();
        std::cout << s.firstName << " " << s.lastName << "\n";
    }
}
void PrintTeacherQueue(Queue<Teacher>& q) {
    while (!q.IsEmpty()) {
        Teacher t = q.Dequeue();
        std::cout << t.firstName << " " << t.lastName << " - " << t.department << "\n";
    }
}

void TestAllForInt() {
    std::cout << "\n=== INT ===\n";
    Queue<int> q(new ArraySequence<int>());
    q.Enqueue(1); q.Enqueue(2); q.Enqueue(3);

    Queue<int> sub = q.SubQueue(1, 2);
    std::cout << "SubQueue (1,2): "; PrintIntSeq(sub.GetSequence());

    Queue<int> pattern(new ArraySequence<int>());
    pattern.Enqueue(2);
    std::cout << "ContainsSubQueue: " << (q.ContainsSubQueue(pattern) ? "yes" : "no") << "\n";

    auto split = q.Split([](int x) { return x < 3; });
    std::cout << "Split <3: left: "; PrintIntSeq(split.first.GetSequence());
    std::cout << "right: "; PrintIntSeq(split.second.GetSequence());

    Sequence<int>* m = map(q.GetSequence(), [](int x) { return x * 10; });
    std::cout << "Map (*10): "; PrintIntSeq(m);
    delete m;

    Sequence<int>* w = where(q.GetSequence(), [](int x) { return x % 2 == 1; });
    std::cout << "Where (odd): "; PrintIntSeq(w);
    delete w;

    int r = reduce(q.GetSequence(), [](int a, int b) { return a + b; }, 0);
    std::cout << "Reduce (sum): " << r << "\n";
}

void TestAllForDouble() {
    std::cout << "\n=== DOUBLE ===\n";
    Queue<double> q(new ArraySequence<double>());
    q.Enqueue(1.1); q.Enqueue(2.2); q.Enqueue(3.3);

    Queue<double> sub = q.SubQueue(0, 2);
    std::cout << "SubQueue (0,2): "; PrintDoubleSeq(sub.GetSequence());

    Queue<double> pattern(new ArraySequence<double>());
    pattern.Enqueue(2.2);
    std::cout << "ContainsSubQueue: " << (q.ContainsSubQueue(pattern) ? "yes" : "no") << "\n";

    auto split = q.Split([](double x) { return x > 2.0; });
    std::cout << "Split >2.0: left: "; PrintDoubleSeq(split.first.GetSequence());
    std::cout << "right: "; PrintDoubleSeq(split.second.GetSequence());

    Sequence<double>* m = map(q.GetSequence(), [](double x) { return x / 2; });
    std::cout << "Map (/2): "; PrintDoubleSeq(m);
    delete m;

    Sequence<double>* w = where(q.GetSequence(), [](double x) { return x > 2.0; });
    std::cout << "Where (>2.0): "; PrintDoubleSeq(w);
    delete w;

    double r = reduce(q.GetSequence(), [](double a, double b) { return a + b; }, 0.0);
    std::cout << "Reduce (sum): " << r << "\n";
}

void TestAllForString() {
    std::cout << "\n=== STRING ===\n";
    Queue<std::string> q(new ArraySequence<std::string>());
    q.Enqueue("one"); q.Enqueue("two"); q.Enqueue("three");

    Queue<std::string> sub = q.SubQueue(1, 3);
    std::cout << "SubQueue (1,3): "; PrintStringSeq(sub.GetSequence());

    Queue<std::string> pattern(new ArraySequence<std::string>());
    pattern.Enqueue("two");
    std::cout << "ContainsSubQueue: " << (q.ContainsSubQueue(pattern) ? "yes" : "no") << "\n";

    auto split = q.Split([](const std::string& s) { return s.size() == 3; });
    std::cout << "Split size==3: left: "; PrintStringSeq(split.first.GetSequence());
    std::cout << "right: "; PrintStringSeq(split.second.GetSequence());

    Sequence<std::string>* m = map(q.GetSequence(), [](std::string s) { return s + "_mod"; });
    std::cout << "Map (+_mod): "; PrintStringSeq(m);
    delete m;

    Sequence<std::string>* w = where(q.GetSequence(), [](const std::string& s) { return s[0] == 't'; });
    std::cout << "Where (starts with t): "; PrintStringSeq(w);
    delete w;

    std::string r = reduce(q.GetSequence(), [](std::string a, std::string b) { return a + b; }, std::string());
    std::cout << "Reduce (concat): " << r << "\n";
}

void TestAllForComplex() {
    std::cout << "\n=== COMPLEX ===\n";
    using cplx = std::complex<double>;
    Queue<cplx> q(new ArraySequence<cplx>());
    q.Enqueue(cplx(1, 2)); q.Enqueue(cplx(3, 4)); q.Enqueue(cplx(5, 6));

    Queue<cplx> sub = q.SubQueue(0, 2);
    std::cout << "SubQueue (0,2): "; PrintComplexSeq(sub.GetSequence());

    Queue<cplx> pattern(new ArraySequence<cplx>());
    pattern.Enqueue(cplx(3, 4));
    std::cout << "ContainsSubQueue: " << (q.ContainsSubQueue(pattern) ? "yes" : "no") << "\n";

    auto split = q.Split([](cplx x) { return x.real() > 2; });
    std::cout << "Split real>2: left: "; PrintComplexSeq(split.first.GetSequence());
    std::cout << "right: "; PrintComplexSeq(split.second.GetSequence());

    Sequence<cplx>* m = map(q.GetSequence(), [](cplx x) { return x * cplx(2, 0); });
    std::cout << "Map (*2): "; PrintComplexSeq(m);
    delete m;

    Sequence<cplx>* w = where(q.GetSequence(), [](cplx x) { return x.imag() > 2; });
    std::cout << "Where (imag>2): "; PrintComplexSeq(w);
    delete w;

    cplx r = reduce(q.GetSequence(), [](cplx a, cplx b) { return a + b; }, cplx(0, 0));
    std::cout << "Reduce (sum): (" << r.real() << "," << r.imag() << ")\n";
}

void TestAllForStudent() {
    std::cout << "\n=== STUDENT ===\n";
    Student s1 = { {123, 456}, "Ivan", "Ivanov", time(nullptr) };
    Student s2 = { {789, 101}, "Petr", "Petrov", time(nullptr) };

    Queue<Student> q(new ArraySequence<Student>());
    q.Enqueue(s1); q.Enqueue(s2);

    Queue<Student> pattern(new ArraySequence<Student>());
    pattern.Enqueue(s2);

    Queue<Student> sub = q.SubQueue(1, 2);
    std::cout << "SubQueue (1,2):\n";
    PrintStudentQueue(sub);

    std::cout << "ContainsSubQueue: " << (q.ContainsSubQueue(pattern) ? "yes" : "no") << "\n";

    auto split = q.Split([](Student s) { return s.id.series < 500; });
    std::cout << "Split <500: left:\n"; PrintStudentQueue(split.first);
    std::cout << "Right:\n"; PrintStudentQueue(split.second);

    Sequence<Student>* m = map(q.GetSequence(), [](Student s) { s.lastName += "_mod"; return s; });
    std::cout << "Map (+_mod):\n";
    for (size_t i = 0; i < m->GetSize(); ++i)
        std::cout << m->Get(i).lastName << " ";
    std::cout << "\n";
    delete m;
}

void TestAllForTeacher() {
    std::cout << "\n=== TEACHER ===\n";
    Teacher t1 = { {101, 202}, "Anna", "Ivanova", "Math" };
    Teacher t2 = { {303, 404}, "Elena", "Smirnova", "Physics" };

    Queue<Teacher> q(new ArraySequence<Teacher>());
    q.Enqueue(t1); q.Enqueue(t2);

    Queue<Teacher> sub = q.SubQueue(0, 1);
    std::cout << "SubQueue (0,1):\n";
    PrintTeacherQueue(sub);

    Queue<Teacher> pattern(new ArraySequence<Teacher>());
    pattern.Enqueue(t2);
    std::cout << "ContainsSubQueue: " << (q.ContainsSubQueue(pattern) ? "yes" : "no") << "\n";

    auto split = q.Split([](Teacher t) { return t.department == "Math"; });
    std::cout << "Split Math: left:\n"; PrintTeacherQueue(split.first);
    std::cout << "Right:\n"; PrintTeacherQueue(split.second);

    Sequence<Teacher>* m = map(q.GetSequence(), [](Teacher t) { t.department += " Dept"; return t; });
    std::cout << "Map (+Dept):\n";
    for (size_t i = 0; i < m->GetSize(); ++i)
        std::cout << m->Get(i).department << " ";
    std::cout << "\n";
    delete m;
}

int main() {
    TestAllForInt();
    TestAllForDouble();
    TestAllForString();
    TestAllForComplex();
    TestAllForStudent();
    TestAllForTeacher();
    return 0;
}