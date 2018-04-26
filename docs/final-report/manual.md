# Animate++: Complete Reference Manual

## 1. Overall
Animate++ is a light-weighted SVG processing library used in C++, which is in pursuit of standardized SVG formatting utilizing C++ features as well as easy-to-call API.
The functionalities of Animate++ are listed in below:
1. Loading and exporting SVG files.
2. Creating all fundamental shapes.
3. Adding external attributes to shapes.
4. Basic animations including rotation, translation, scaling.
5. Allowing objects to move along a Bezier curve.

## 2. Background TODO

- SVG
    - `<canvas>`
- SMIL

## 3. ChangeLog

- `0.5`
  - XML parsing under the support of pugi library
- `0.8`
  - SVG loader supports all common shapes individually including
      - Rectangle
      - Circle
      - Ellipse
      - Line
      - Polyline
      - Path
      - Bezier curve
  - Compound shape with any number of individual objects can also be loaded
  (a code snippet of how we load any type of shape is shown in below).
  ```cpp
  // load SVG
  ShapePtr g = load(in_path);
  // output the object to an SVG file
  g->save(out_path);
  ```
  - Valid SVG file can be generated.
  ```xml
  <?xml version="1.0"?>
  <svg version="1.1" xmlns="http://www.w3.org/2000/svg">
    <g>
      <rect x="10" y="10" rx="0" ry="0" width="30" height="30" fill="transparent" stroke="black" stroke-width="5" />
      <rect x="60" y="10" rx="10" ry="10" width="30" height="30" fill="transparent" stroke="black" stroke-width="5" />
      <circle cx="25" cy="75" r="20" fill="transparent" stroke="red" stroke-width="5" />
      <ellipse cx="75" cy="75" rx="20" ry="5" fill="transparent" stroke="red" stroke-width="5" />
      <line x1="10" y1="110" x2="50" y2="150" stroke="orange" stroke-width="5" />
      <polyline points="60 110 65 120 70 115 75 130 80 125 85 140 90 135 95 150 100 145" fill="transparent" stroke="orange" stroke-width="5" />
      <polygon points="50 160 55 180 70 180 60 190 65 205 50 195 35 205 40 190 30 180 45 180" fill="transparent" stroke="green" stroke-width="5" />
      <path d="M 20 230 Q 40 205 50 230 T 90 230 " fill="none" stroke="blue" stroke-width="5" />
    </g>
  </svg>
  ```
  - Basic animations including rotation, scaling and translation of all basic objects have been accomplished. Users are free to manipulate the existing objects in their ways of favor. (An example of how we edit our circle animation is shown by the c++ code snippet in below)

  Here is the SVG before editing
  ```xml
  <circle cx="100" cy="100" r="100" fill="yellow" opacity="0.5">
  </circle>
  ```
  Our code to modify animation
  ```cpp
  c.animate.translate(Point(100, 100), Point(0, 200), true)
           .duration("2.5s")
           .loop(true);
  ```
  The SVG after editing
  ```xml
  <circle cx="100" cy="100" r="100" fill="yellow" opacity="0.5">
      <animateTransform attributeName="transform" type="translate" dur="2.5s" from="100 100" repeatCount="indefinite" to="0 200" />
  </circle>
  ```
- `1.0`
  - Fonts, fills and strokes are all completed(shown in the code snippet in below)
  ```cpp
  Circle c(100, 100, 100);
  c.attr({
      {"fill", "yellow"},
      {"opacity", "0.5"}
  });
  ```
  - Gradients and patterns are special entities in SVG standards, which require building and referring to xml references. We have utilized it in our logo, but up to now there is no general support for these features.
  - Complicated animation has also been accomplished. In the example given below, we load a tiger SVG as a combination of more than 200 beizer curves with over 700 lines of code. The whole tiger head can rotate and translate.

  ![tiger](../assets/final-report/tiger.png)

- `1.2`

## 4. API Reference

## Classes

### Point
Point is constructed by two doubles, which is the essential class for our SVG library.
#### print()
Print a point object.
```cpp
Point p(1, 2);
print(p); // -> 1 2;
```
### Shape
Shape is an abstract class extended by the following shapes.
#### 1. Rectangle
- In SVG, rectangle is called using `<rect>`.
	Within the scope of `<rect>`, we need to define <span style="color:red"> 4 </span> major properties to at least make the shape valid: <span style="color:blue">
	x : x-coordinate of top left corner
	y : y-coordinate of top left corner
	width : width of rectangle
	height : height of rectangle
	</span>
- An example shown in below as:
	`<rect x="10" y="10" width="30" height="30"/>`
	Our c++ initialization is:
	```cpp
	Rect r(10, 10, 30, 30);
	```
#### 2. Circle
- In SVG, rectangle is called using `<circle>`.
	Within the scope of `<rect>`, we need to define <span style="color:red"> 3 </span> major properties to at least make the shape valid: <span style="color:blue">
	cx : center coordinate on x-axis
	cy : center coordinate on y-axis
	r : radius
	</span>
- An example shown in below as:
	`<circle cx="25" cy="75" r="20"/>`
	Our c++ initialization is:
	```cpp
	Circle c(25, 75, 20);
	```
#### 3. Ellipse
- In SVG, ellipse is called using `<ellipse>`.
	Within the scope of `<ellipse>`, we need to define <span style="color:red"> 4 </span> major properties to at least make the shape valid: <span style="color:blue">
	cx : center coordinate on x-axis
	cy : center coordinate on y-axis
	rx : radius on x-axis
	ry : radius on y-axis
	</span>
- An example shown in below as:
	`<ellipse cx="75" cy="75" rx="20" ry="5"/>`
	Our c++ initialization is:
	```cpp
	Ellipse e(75, 75, 20, 5);
	```
#### 4. Line
- In SVG, line is called using `<line>`.
	Within the scope of `<line>`, we need to define <span style="color:red"> 4 </span> major properties to at least make the shape valid: <span style="color:blue">
	x1 : starting x-axis coordinate
	x2 : ending x-axis coordinate
	y1 : starting y-axis coordinate
	y2 : ending y-axis coordinate
- An example shown in below as:</span>
	`<line x1="10" x2="50" y1="110" y2="150"/>`
	Our c++ initialization is:
	```cpp
	Line l(10, 50, 110, 150);
	```
#### 5. Polyline
- In SVG, polyline is called using `<polyline>`.
	Within the scope of `<polyline>`, we need to define a list of points, simply an array of pairs of numbers.
- An example shown in below as:
	`<polyline points="60 110 65 120"/>`
	Our c++ initialization is:
	```cpp
	Vector<Point> vec(Point(60, 110), Point(65, 120));
	Polyline p(vec);
	```
#### 6. Polygon
- In SVG, polygon is called using `<polygon>`.
	Within the scope of `<polygon>`, we need to define a list of points, simply an array of pairs of numbers.
- An example shown in below as:
	`<polygon points="50 160 55 180"/>`
	Our c++ initialization is:
	```cpp
	Vector<Point> vec(Point(50, 160), Point(55, 180));
	Polygon p(vec);
	```
#### 7. Path
- In SVG, path is called using `<path>`.
	Path, which essentially is a bezier curve, is the most complicated shape among all SVG basic shapes, but it is what makes SVG charming. There can be a large number of types of input bezier curve and they end up to be all valid. Due to the large number of samples covered, we will not enumerate all of them in the following. Our parser has covered most of the valid bezier curves. Any valid form of bezier curve can be taken as a string input to our constructor.
- An example shown in below as:
	`<path d="M20,230 Q40,205 50,230 T90,230"/>`
	Our c++ initialization is:
	```cpp
	string d="M20,230 Q40,205 50,230 T90,230";
	Path p(d);
	```
### More functions for any shape object.

#### print()
Print any shape object.
```cpp
Rectangle r(30, 30, 20, 20);
print(r); // -> x=30, y=30, width=20, height=20
```
#### export_SVG()
Write the object to a SVG file.
```cpp
Rectangle r(30, 30, 20, 20);
auto node = r.export_SVG(doc); // aggregate code in doc and output it as a node
```
What we have just created is a node object. To save our modification into a file, we will do the following.
```cpp
out_path = "<some user defined directory>";
xml_document doc; // create an xml_document object
auto svg = SVG_header(doc); // create svg node in doc object
Rectangle r(30, 30, 20, 20);
auto node = r.export_SVG(doc);
svg.append_move(node); // append our node to the svg
doc.save_file(out_path.c_str()); // save the xml_document to the path
```
#### attr()
User can either add a single pair of attributes to the shape object or add multiple pairs of attributes inside a <span style="color:red">map</span> all into the object.
```cpp
Rect r(0, 0, 100, 100, 3, 3);
r.attr("fill", "blue"); // add one pair.
r.attr({
    {"stroke", "black"},
    {"stroke-width", "5"}
}); // add two pairs.
```
#### get_attributes()
Return a list of attributes contained by certain shape
```cpp
r.attr({
    {"fill", "blue"},
    {"stroke", "black"},
    {"stroke-width", "5"}
});
auto map = r.get_attributes();
// map ->
// {{"fill", "blue"},
//  {"stroke", "black"},
//  {"stroke-width", "5"}}
```
#### print_attributes()
Print all attributes contained within a Shape object.
```cpp
r.attr({
    {"fill", "blue"},
    {"stroke", "black"},
    {"stroke-width", "5"}
});
r.print_attributes();
// {{"fill", "blue"},
//  {"stroke", "black"},
//  {"stroke-width", "5"}}
```
#### export_attributes()
Export all attributes to an xml_node
```cpp
xml_document doc;
xml_node node = SVG_header(doc);
// Attributes inside the rectangle r are exported to node.
r.export_attributes(node);
```
#### add_animations()
Add animations to given node.
```cpp
Rectangle r(0, 0, 100, 100);
r.add_animations(pugi::xml_document&, pugi::xml_node);
```

#### save()
Save the Shape to the given path
```cpp
Rectangle r(0, 0, 100, 100);
string path = "rectangle.svg";
r.save(path);
```
### Complex shapes (How compound object has each component edited individually?)
Of course, supporting only single type of object is not sufficient to accomplish all fancy functionalities that can potentially be achieved by SVGs. Animate++ also supports multiple shapes contained in one single file to be loaded all together.
```cpp
// load in svg from a path, which is a string of local file directory
ShapePtr g = load(in_path);
// output the object to an SVG file
g->save(out_path);
```

### Animator
Each shape has an animator called <span style="color:red">animate</span> attached to it, which is in charge of the animation.

#### translate()
In translation, user needs to define the initial and ending position on x and y axis. An example of translation is shown in below, from "100 100" to "0 200" entails that the object transforms from (100, 100) to (0, 200).
```cpp
c = circle(25, 75, 20);
c.animate.translate(Point(100, 100), Point(0,200));
```
Or instead, given the amount an object is translated from current position instead of its destination, which we referred to as relative translation. An example is shown in below.
```cpp
c = circle(25, 75, 20);
c.animate.translate(Point(100, 100), Point(0, 200), true);
```

#### rotate()
In rotation, the from and to are in the form "n1 n2 n3", where "n1" entails the degree of rotation, and (n2, n3) indicates the center position of rotation. As what has been shown in below, rotation takes place from 0 to 360 degrees around the center (100, 100).
```cpp
Point center_begin(100, 100);
Point center_end(200, 200);
r.animate.rotate(center_begin, 0, center_end, 360);
```

#### scale()
In scaling, the initial and ending scaling on x and y axis are both required.
```cpp
c.animate.scale(Point(0, 0), Point(1, 1)); // the object's scale transforms from (0*x, 0*y) to (1*x, 1*y)
```

#### active()
Check whether given object has any animation with it.
```cpp
c.animate.active() // return true if c contains any animation.
```

#### duration()
<span style="color:red"> return </span> void
Set the duration for the animation.
```cpp
c.animate.duration("2.5s"); // set animation duration to 2.5 seconds.
```
#### loop()
Provide a boolean value determine the state of animation.
```cpp
c.animate.loop(true); // c will keep on animating.
```
