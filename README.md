# Animate++

Animate++ is a C++ library that lets you rapidly compose beautiful vector graphics animation.

## Getting started

- To build the project: `make`
- To build tests: `make test`

## Dependencies

- pugixml: `1.9`

## Examples

__Sample program__: outputs a synoptically correct SVG file that yields to the same visual output
```cpp
#include <iostream>
#include <animate.h>
using namespace anipp;

int main() {
    Rect r(20, 20, 100, 100, 3, 3);
    r.attr({
        {"fill", "red"},
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

<p align="center">
    <img src="examples/rect_rotate.svg" width=100%/>
</p>
