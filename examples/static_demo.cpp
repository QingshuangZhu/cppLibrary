#include "IMyClass.h"

using namespace MyLibrary;

int main(int argc, char* argv[]) {
    auto myClass = createIMyClass();
    myClass->doSomething("Hello, World!");
    return 0;
}