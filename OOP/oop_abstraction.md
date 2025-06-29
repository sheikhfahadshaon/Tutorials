# Object-Oriented Programming Concepts in C++

This document provides an overview of key Object-Oriented Programming (OOP) concepts in C++, including abstraction, virtual functions, binding, copying, destructors, polymorphism, and other essential OOP principles. Below is a detailed explanation of each concept, including code examples where applicable.

## Abstraction in OOP

Abstraction in Object-Oriented Programming (OOP) involves hiding implementation details and exposing only essential features to reduce complexity. In C++, abstraction is achieved using abstract classes and interfaces, typically through virtual functions.

### Virtual Functions

A virtual function is a member function in a base class that can be overridden in derived classes to achieve runtime polymorphism.

```cpp
class Animal {
public:
    virtual void sound() {
        std::cout << "Animal makes sound" << std::endl;
    }
};
```

### Pure Virtual Functions

A pure virtual function has no implementation in the base class and must be overridden in derived classes, making the class abstract.

```cpp
class Animal {
public:
    virtual void sound() = 0; // Pure virtual function
};
```

### Abstract Classes

A class with at least one pure virtual function is an abstract class and cannot be instantiated directly. It serves as a base class for inheritance.

```cpp
class Animal {
public:
    virtual void sound() = 0;
};

class Dog : public Animal {
public:
    void sound() override {
        std::cout << "Woof!" << std::endl;
    }
};

int main() {
    // Animal a; // Error: cannot instantiate abstract class
    Dog d;
    d.sound(); // Output: Woof!
}
```

### Key Differences

| Concept               | Description                                           |
|-----------------------|-------------------------------------------------------|
| Virtual Function      | Has a base implementation, can be overridden.          |
| Pure Virtual Function | No implementation, forces derived classes to override. |
| Abstract Class        | Contains at least one pure virtual function, cannot be instantiated. |

### Runtime Polymorphism Example

```cpp
class Shape {
public:
    virtual void draw() {
        std::cout << "Drawing Shape" << std::endl;
    }
};

class Circle : public Shape {
public:
    void draw() override {
        std::cout << "Drawing Circle" << std::endl;
    }
};
```

## Vtable and Vptr

### How Vtable and Vptr Work

The document includes a placeholder for explaining how vtables (virtual tables) and vptr (virtual pointers) work in C++ to manage virtual function calls. However, the specific details are missing from the provided content. In general, a vtable is a table of function pointers used to resolve virtual function calls at runtime, and vptr is a pointer in each object that points to its class's vtable.

### Example with Multiple Virtual Functions

The document references an example with multiple virtual functions but does not provide the code. Typically, such an example would demonstrate a base class with multiple virtual functions and derived classes overriding them, showcasing how the vtable stores pointers to the overridden functions.

## Static vs. Dynamic Binding

### Static Binding (Early Binding)

Function calls are resolved at compile time. Used for non-virtual functions, function overloading, and operator overloading.

```cpp
class Animal {
public:
    void sound() {
        std::cout << "Animal sound" << std::endl;
    }
};

int main() {
    Animal a;
    a.sound(); // Compile-time binding
}
```

### Dynamic Binding (Late Binding)

Function calls are resolved at runtime using virtual functions and base class pointers/references.

```cpp
class Animal {
public:
    virtual void sound() {
        std::cout << "Animal sound" << std::endl;
    }
};

int main() {
    Animal a;
    a.sound(); // Compile-time binding (Note: This example in the document should demonstrate runtime binding with a pointer/reference)
}
```

## Deep Copy vs. Shallow Copy

### Shallow Copy

A shallow copy copies all member variables as-is, including pointers, which can lead to multiple objects pointing to the same memory location.

### Deep Copy

A deep copy creates a new copy of all dynamically allocated memory, ensuring that each object has its own independent copy of the data.

## Virtual Destructors

Virtual destructors ensure proper cleanup of derived class objects when deleted through a base class pointer. This is critical to prevent memory leaks in polymorphic hierarchies.

## Polymorphism

### Compile-Time Polymorphism

Achieved through function overloading and operator overloading, resolved at compile time.

### Run-Time Polymorphism

Achieved through virtual functions and inheritance, resolved at runtime using vtables.

## Other OOP Concepts

### Encapsulation

Encapsulation involves bundling data and methods that operate on that data within a class, restricting direct access to some of an object's components.

### Inheritance

Inheritance allows a class to inherit properties and behavior from another class, promoting code reuse.

### Constructor and Destructor

Constructors initialize objects, while destructors clean up resources when objects are destroyed.

### Operator Overloading

Operator overloading allows custom behavior for operators (e.g., `+`, `==`) when used with user-defined types.

### Friend Functions

Friend functions can access private and protected members of a class, providing controlled access to class internals.

### This Pointer

The `this` pointer refers to the current object instance, used to access members of the object within its methods.

### Virtual Inheritance

Virtual inheritance prevents multiple copies of a base class in a derived class during multiple inheritance, avoiding the "diamond problem."

## Static Variables and Members

Static variables and members belong to the class rather than any specific object, shared across all instances.

## Library Management System

The document includes a partial implementation of a Library Management System, demonstrating OOP concepts in C++.

### LibraryItem Class

```cpp
#ifndef LIBRARYITEM_H
#define LIBRARYITEM_H
#include <string>
using namespace std;

class LibraryItem {
private:
    string title;
    string author;
    int itemID;
    static int idCounter;
public:
    LibraryItem(string t, string a) : title(t), author(a) {
        itemID = ++idCounter;
    }
    virtual void displayInfo() const = 0;
    int getItemID() const { return itemID; }
    bool operator==(const LibraryItem& other) const {
        return title == other.title && author == other.author;
    }
    virtual ~LibraryItem() {
        cout << "Destroying LibraryItem ID: " << itemID << endl;
    }
};

int LibraryItem::idCounter = 0;
#endif
```

### Book and DVD Classes

```cpp
#ifndef BOOK_H
#define BOOK_H
#include "LibraryItem.h"

class Book : public LibraryItem {
private:
    int numPages;
public:
    Book(string t, string a, int pages) : LibraryItem(t, a), numPages(pages) {}
    void displayInfo() const override {
        cout << "Book ID: " << getItemID() << endl;
        cout << "Title: " << title << endl;
        cout << "Author: " << author << endl;
        cout << "Pages: " << numPages << endl;
    }
    ~Book() override {
        cout << "Destroying Book ID: " << getItemID() << endl;
    }
};
#endif

#ifndef DVD_H
#define DVD_H
#include "LibraryItem.h"

class DVD : public LibraryItem {
private:
    float duration;
public:
    DVD(string t, string a, float d) : LibraryItem(t, a), duration(d) {}
    void displayInfo() const override {
        cout << "DVD ID: " << getItemID() << endl;
        cout << "Title: " << title << endl;
        cout << "Director: " << author << endl;
        cout << "Duration: " << duration << " hours" << endl;
    }
    ~DVD() override {
        cout << "Destroying DVD ID: " << getItemID() << endl;
    }
};
#endif
```

### User Hierarchy

```cpp
#ifndef USER_H
#define USER_H
#include <iostream>
#include <string>
using namespace std;

class User {
protected:
    string name;
    int userID;
    static int userCounter;
public:
    User(string n) : name(n) { userID = ++userCounter; }
    void setName(string n) { name = n; }
    virtual void showProfile() const {
        cout << "User ID: " << userID << endl;
        cout << "Name: " << name << endl;
    }
    int getUserID() const { return userID; }
    virtual ~User() {
        cout << "Destroying User ID: " << userID << endl;
    }
};

int User::userCounter = 0;
#endif

#ifndef STUDENT_H
#define STUDENT_H
#include "User.h"

class Student : virtual public User {
private:
    int grade;
public:
    Student(string n, int g) : User(n), grade(g) {}
    void showProfile() const override {
        cout << "Student Profile" << endl;
        User::showProfile();
        cout << "Grade: " << grade << endl;
    }
};
#endif

#ifndef TEACHER_H
#define TEACHER_H
#include "User.h"

class Teacher : virtual public User {
private:
    string department;
public:
    Teacher(string n, string dept) : User(n), department(dept) {}
    void showProfile() const override {
        cout << "Teacher Profile" << endl;
        User::showProfile();
        cout << "Department: " << department << endl;
    }
};
#endif
```

### Main Menu System

```cpp
#include <iostream>
#include <vector>
#include "Book.h"
#include "DVD.h"
#include "Student.h"
#include "Teacher.h"
#include "BorrowRecord.h"

int main() {
    vector<LibraryItem*> items;
    vector<User*> users;
    vector<BorrowRecord> records;
    int choice;

    do {
        cout << "\n=== Library Menu ===\n";
        cout << "1. Add Book\n2. Add DVD\n3. Add Student\n4. Add Teacher\n5. Borrow Item\n6. Show Borrow History\n7. Exit\n\n";
        cout << "Choice: ";
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            string title, author;
            int pages;
            cout << "Enter title, author, pages: ";
            getline(cin, title);
            getline(cin, author);
            cin >> pages;
            items.push_back(new Book(title, author, pages));
        }
        else if (choice == 2) {
            string title, director;
            float duration;
            cout << "Enter title, director, duration: ";
            getline(cin, title);
            getline(cin, director);
            cin >> duration;
            items.push_back(new DVD(title, director, duration));
        }
        else if (choice == 3) {
            string name;
            int grade;
            cout << "Enter name and grade: ";
            getline(cin, name);
            cin >> grade;
            users.push_back(new Student(name, grade));
        }
        else if (choice == 4) {
            string name, dept;
            cout << "Enter name and department: ";
            getline(cin, name);
            getline(cin, dept);
            users.push_back(new Teacher(name, dept));
        }
        else if (choice == 5) {
            int uid, id;
            string date;
            cout << "Enter User ID, Item ID, and Date (YYYY-MM-DD): ";
            cin >> uid >> id;
            cin.ignore();
            getline(cin, date);
            User* u = nullptr;
            LibraryItem* it = nullptr;
            for (auto user : users) {
                if (user->getUserID() == uid) {
                    u = user;
                    break;
                }
            }
            for (auto item : items) {
                if (item->getItemID() == id) {
                    it = item;
                    break;
                }
            }
            if (u && it) {
                records.emplace_back(u, it, date);
                cout << "Borrow recorded\n";
            }
        }
    } while (choice != 7);

    // Cleanup
    for (auto item : items) delete item;
    for (auto user : users) delete user;
    return 0;
}
```

This document serves as a comprehensive guide to understanding and implementing OOP concepts in C++, with practical examples like the Library Management System to illustrate their application.