/*
 * Header file for Animate++ library
 * @author: Wode "Nimo" Ni, Xuanyuan Zhang
 * @version: 04/04/2018
 */

#include <iostream>

namespace anipp {
    void test() { std::cout << "Hello World" << '\n'; }

    class Animator {
    // private:
    // public:
    };

    /*
     * Top level abstract class for all shapes
     */
    class Shape {
    private:
        Animator animate;
    public:
        virtual ostream& operator<< (ostream& out) const;
    };

    class Circle : public Shape {
    private:
        int r;
    public:
        ostream& operator<< (ostream& out) const;
    };

}
