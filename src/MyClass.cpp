#include "MyClass.h"
#include <iostream>

namespace MyLibrary {

// internal implementation class, hide the implementation details
class MyClass::Impl {
public:
    Impl() {
        std::cout << "MyClass::Impl constructed." << std::endl;
    }
    ~Impl() {
        std::cout << "MyClass::Impl destroyed." << std::endl;
    }
    // business logic implementation
    void doSomethingImpl(const std::string& message) {
        std::cout << "MyClass::Impl is doing something." << std::endl;
        std::cout << "Message: " << message << std::endl;
    }
};

/* MyClass memeber functions implementation */

// constructor
MyClass::MyClass() : pImpl(std::make_unique<Impl>()) {
    std::cout << "MyClass constructed." << std::endl;
}

// destructor
MyClass::~MyClass() {
    std::cout << "MyClass destroyed." << std::endl;
}

// copy constructor
MyClass::MyClass(const MyClass& other) : pImpl(std::make_unique<Impl>(*other.pImpl)) {
    std::cout << "MyClass copy constructed." << std::endl;
}

// copy assignment operator
MyClass& MyClass::operator=(const MyClass& other) {
    if (this != &other) {
        pImpl = std::make_unique<Impl>(*other.pImpl);
    }
    std::cout << "MyClass copy assignment operator." << std::endl;
    return *this;
}

// move constructor
MyClass::MyClass(MyClass&&) noexcept = default;

// move assignment operator
MyClass& MyClass::operator=(MyClass&&) noexcept = default;

// business logic implementation
void MyClass::doSomething(const std::string& message) {
    pImpl->doSomethingImpl(message);
}

// factory method to create an instance of IMyClass
extern "C" MYLIB_API std::unique_ptr<IMyClass> createIMyClass() {
    return std::make_unique<MyClass>();
}

} // namespace MyLibrary
