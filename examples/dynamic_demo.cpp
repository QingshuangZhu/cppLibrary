#include <iostream>
#include <dlfcn.h>

#include "IMyClass.h"

using namespace MyLibrary;

int main(int argc, char* argv[]) {
    void *handle;
    std::unique_ptr<IMyClass> (*func)();

    // load the shared library
    handle = dlopen("libmylib.so", RTLD_LAZY);
    if (!handle) {
        std::cerr << "Cannot open library: " << dlerror() << std::endl;
        return 1;
    }

    // clear any existing error
    dlerror();

    // get the address of the function createIMyClass
    func = (std::unique_ptr<IMyClass>(*)())dlsym(handle, "createIMyClass");
    if (dlerror() != NULL)  {
        std::cerr << "Cannot load symbol 'createIMyClass': " << dlerror() << std::endl;
        dlclose(handle);
        return 1;
    }

    // use the function to create an instance of IMyClass
    auto myClass = func();
    myClass->doSomething("Hello, World!");

    // reset the unique_ptr to release the resource
    myClass.reset();  

    // unload the shared library
    dlclose(handle);
    return 0;
}