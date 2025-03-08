#ifndef MYCLASS_H
#define MYCLASS_H

#include "IMyClass.h"

namespace MyLibrary {

// concrete implementation class, inherits from the interface class, using pImpl idiom to hide the implementation details
class MyClass : public IMyClass {
public:
    MyClass();
    ~MyClass();
    
    MyClass(const MyClass&);
    MyClass& operator=(const MyClass&);
    MyClass(MyClass&&) noexcept;
    MyClass& operator=(MyClass&&) noexcept;

    void doSomething(const std::string& message) override;

private:
    // forward declaration of the implementation class
    class Impl;
    // unique_ptr to the implementation class, using pImpl idiom to hide the implementation details
    std::unique_ptr<Impl> pImpl;
};

} // namespace MyLibrary

#endif // MYCLASS_H
