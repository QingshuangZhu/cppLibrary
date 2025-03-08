#ifndef IMYCLASS_H
#define IMYCLASS_H

#include <string>
#include <memory>

// define export/import macros for Windows/Linux
#if defined(_WIN32) || defined(_WIN64)
  #ifdef MYLIBRARY_EXPORTS
    #define MYLIB_API __declspec(dllexport)
  #else
    #define MYLIB_API __declspec(dllimport)
  #endif
#else
  #define MYLIB_API __attribute__((visibility("default")))
#endif

namespace MyLibrary {

// interface class
class MYLIB_API IMyClass {
public:
    virtual ~IMyClass() = default;

    virtual void doSomething(const std::string& message) = 0;
};

// factory method to create an instance of IMyClass
extern "C" MYLIB_API std::unique_ptr<IMyClass> createIMyClass(); 

} // namespace MyLibrary

#endif // IMYCLASS_H
