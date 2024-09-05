// MyClass.cpp
#include <iostream>
#include <raylib.h>
#include <string>
#include <cstring>
// C++ class definition
class MyClass {
public:
    MyClass() : value(0) {}
    ~MyClass() {}
    void doSomething() {
        std::cout << "Doing something! Value: " << value << std::endl;
    }
    int getValue() const {

        return value;
    }
  
    const char* getString() const {
        std::string str = "Hello from MyClass! Value: " + std::to_string(value);
        char* cstr = new char[str.length() + 1];
        std::strcpy(cstr, str.c_str());
        return cstr;
    }
    void setValue(int value) {
        this->value = value;
    }

private:
    int value;
};

// C-compatible wrapper
#ifdef __cplusplus
extern "C" {
#endif

typedef struct MyClass MyClass;

MyClass* MyClass_Create() {
    return new MyClass();
}

void MyClass_Destroy(MyClass* myClass) {
    delete myClass;
}

void MyClass_DoSomething(MyClass* myClass) {
    myClass->doSomething();
}

int MyClass_GetValue(const MyClass* myClass) {
    return myClass->getValue();
}

void MyClass_SetValue(MyClass* myClass, int value) {
    myClass->setValue(value);
}

const char* MyClass_GetString(const MyClass* myClass)
{
    return myClass->getString();
}
#ifdef __cplusplus
}
#endif