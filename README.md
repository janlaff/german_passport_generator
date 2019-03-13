# id_generator
Library to generate german passport serial

This is useful for several situations such as bypass age restrictions (which i don't recommend) or for staying anonymous when such information is needed.

# Example usage
*CMakeLists.txt*
```
cmake_minimum_required(VERSION 3.10)
project(example_project)

set(CMAKE_CXX_STANDARD 17)

add_executable(example_project example.cpp)
target_include_directories(example_project id_generator)
```

*example.cpp*
```
#include <iostream>

#include <id_generator.h>

int main(int argc, char* argv[]) {
    // Erika Mustermann example
    auto id = id_generator("T002", "640812", "201031");
    
    std::cout << "Generated id:\n" << id.to_string();
}
```

*Program output*
```
Generated id:
IDD<<T00207CEG6<<<<<<<<<<<<<<<
6408125<2010315D<<<<<<<<<<<<<8
```
