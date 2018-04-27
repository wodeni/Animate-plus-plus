<p align="center">
    <img src="http://wodenimoni.com/images/anipp-logo.svg" width=100%/>
</p>

# Animate++

Animate++ is a C++ library that lets you rapidly compose beautiful vector graphics animation.

__COMS 4995 Grading: please refer to [The directory of our project structure](#directory-structure) for information about where each deliverable is in the folder__

## Dependencies

- C++17
- clang: macOS version
```
clang version 6.0.0 (tags/RELEASE_600/final)
```
- pugixml: `1.9`
- boost: `1.66.0`
- ar: command line tool

## Getting started

- To build the project: type `make`
    - compiles the library and archive it using `ar`
    - generates `libAnipp.a` in `build` directory
- To build tests: type `make test`
    - generates `test-driver` in `build` directory
    - run `./build/test-driver` to run all the tests
    - all outputs of the tests are contained in `test/output`
- To build an `tar` file that contains all headers and the library archive to use Animate++ elsewhere, type `make release`, which generates a tar file in same directory.
    - To use the library, you need to have `boost` on your machine
        - For macOS, you can use `brew` to install `boost` by running `brew install boost`
    - To compile a test file that calls functions from Animate++, suppose we have a test file `main.cpp`
    ```cpp
    #include "animate.hpp"
    #include <iostream>
    int main() {
        anipp::Circle c(10, 10,1);
        std::cout << c << '\n';
    }
    ```
    - You can write a Makefile or just use the following commands to compile  `main.cpp` (assuming `boost` is located at `/usr/local/Cellar/boost/1.66.0/`).
    ```shell
    $ g++ -c main.cpp -o main.o  -I./src -I./include/pugixml-1.9/src -I/usr/local/Cellar/boost/1.66.0/include  -std=c++1z

    $ g++ main.o -o main -I./src  -I/usr/local/Cellar/boost/1.66.0/include -L/usr/local/Cellar/boost/1.66.0/lib -lboost_regex-mt -L. -lAnipp
    ```
    - If you have a newer version of Clang, please use `std=c++17` instead of `std=c++1z`.

## Hello World example

__Sample program__: outputs a synoptically correct SVG file that yields to the same visual output
```cpp
#include <iostream>
#include <animate.h>
using namespace anipp;

int main() {
    Rect r(20, 20, 100, 100, 3, 3);
    r.attr({ {"fill", "red"},
        {"stroke", "black"},
        {"stroke-width", "5"}
    });
    Point center(70, 70);
    r.animate.rotate(center, 0, center, 360)
             .duration("10s")
             .loop(true);
    r.save("./output.svg");
}
```

__Exported SVG__:
```xml
<?xml version="1.0"?>
<svg version="1.1" xmlns="http://www.w3.org/2000/svg">
	<rect x="20" y="20" rx="3" ry="3" width="100" height="100" fill="red" stroke="black" stroke-width="5">
		<animateTransform
            attributeName="transform"
            type="rotate"
            dur="10s"
            from="0 70 70"
            repeatCount="indefinite"
            to="360 70 70" />
	</rect>
</svg>
```

Click to show animation:
<p align="center">
    <img src="examples/rect_rotate.svg" width=100%/>
</p>

## Directory structure

├── Makefile
├── README.md
├── docs
│   ├── assets
│   ├── final-report
│   ├── notes
│   ├── progress-report
│   ├── proposal
│   └── talk
├── examples
│   └── rect_rotate.svg
├── include
│   └── pugixml-1.9
├── src
│   ├── animate.hpp
│   ├── parser.cpp
│   ├── parser.hpp
│   ├── shapes.cpp
│   ├── shapes.hpp
│   ├── utils.cpp
│   └── utils.hpp
└── test
    ├── src
    └── svgs

- `src` contains all the original source code of Animate++
- `include` contains third-party library files
- `talks` contains the pdf and reveal.js versions of our presentation
- `docs` contains most of the past and current deliverables for the course project, which also contains the following:
    - `design.pdf`: contains the design considerations of the library   
    - `manual.pdf`: contains the complete user manual for the library, which includes an API reference as well
    - `metrics.pdf`: contains our methodology of testing the implementation and the design of our test suite
    - `status.pdf`: reports on the progress of the library implementation as a course project, and compare our progress with the proposed timeline.
    - `tutorial.pdf`: contains an accessible hand-on, illustrated, example-driven tutorial to our library. __Welcome to Animate++!__

## Authors

__Wode "Nimo" Ni - wn2155@columbia.edu__
__Xuanyuan Zhang - xz2580@columbia.edu__
