// MyClass_Wrapper.h
#ifndef MYCLASS_WRAPPER_H
#define MYCLASS_WRAPPER_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct MyClass MyClass;

MyClass* MyClass_Create();
void MyClass_Destroy(MyClass* myClass);
void MyClass_DoSomething(MyClass* myClass);
int MyClass_GetValue(const MyClass* myClass);
void MyClass_SetValue(MyClass* myClass, int value);
const char* MyClass_GetString(const MyClass* myClass);


#ifdef __cplusplus
}
#endif

#endif // MYCLASS_WRAPPER_H