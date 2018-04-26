# Design Documentation

__Wode "Nimo" Ni - wn2155@columbia.edu__
__Xuanyuan Zhang - xz2580@columbia.edu__

## Motivation for the project
SVG stands for Scalable Vector Graphics, which is nowadays a "must" for fancy front-end in favored by both clients and front-end developers. However, the standardization of SVG has always been a big issue. Due to a lack of type-checking and other Object Oriented Programming features supported by Javascript, which have been used for over 90% of SVG libraries and editors, the syntax of SVG is expanding in a rampant manner and somehow, out of control. What we want to achieve in Animate++ is to utilize C++ features to create an easy-to-use library for both static and animated SVG in standardized manner, which can be interpreted by all major browsers. Since animation is the part with the most complicated syntax in our project, which is our major focus, we name our project as Animated++, standing for SVG Animation using C++. 
## Current output format

- Why SVG SMIL
    - debates about "SMIL is dead"
    - Standalone document
