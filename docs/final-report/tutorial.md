# Getting started: a tutorial to Animate++

__Wode "Nimo" Ni - wn2155@columbia.edu__
__Xuanyuan Zhang - xz2580@columbia.edu__

## Installation
### 1. Download required libraries
- [boost](https://www.boost.org/) is utilized in our project. To download boost, simply run
	brew install boost on MacOS or download boost from the [given URL](https://www.boost.org/users/history/version_1_66_0.html) if you are Windows or Linux user.
- [pugi](https://pugixml.org/) is the xml parser which supports all parsing tasks, helping us extract content from SVG files. Tutorial on downloading pugi can be followed through [this link](https://pugixml.org/). After library being downloaded, put the whole unzipped file under the same directory as the code files, and you are ready to go.

### 2. Compile and run with your own code
TODO. We have not decided whether we want a library or just let users to include our files.

## Basic shapes
### 1. Rectangle
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
### 2. Circle
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
### 3. Ellipse
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
### 4. Line
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
### 5. Polyline
- In SVG, polyline is called using `<polyline>`.
	Within the scope of `<polyline>`, we need to define a list of points, simply an array of pairs of numbers.
- An example shown in below as:
	`<polyline points="60 110 65 120"/>`
	Our c++ initialization is:
	```cpp
	Vector<Point> vec(Point(60, 110), Point(65, 120));
	Polyline p(vec);
	```
### 6. Polygon
- In SVG, polygon is called using `<polygon>`.
	Within the scope of `<polygon>`, we need to define a list of points, simply an array of pairs of numbers.
- An example shown in below as:
	`<polygon points="50 160 55 180"/>`
	Our c++ initialization is:
	```cpp
	Vector<Point> vec(Point(50, 160), Point(55, 180));
	Polygon p(vec);
	```
### 7. Path
- In SVG, path is called using `<path>`.
	Path, which essentially is a bezier curve, is the most complicated shape among all SVG basic shapes, but it is what makes SVG charming. There can be a large number of types of input bezier curve and they end up to be all valid. Due to the large number of samples covered, we will not enumerate all of them in the following. Our parser has covered most of the valid bezier curves. Any valid form of bezier curve can be taken as a string input to our constructor.
- An example shown in below as:
	`<path d="M20,230 Q40,205 50,230 T90,230"/>`
	Our c++ initialization is:
	```cpp
	string d="M20,230 Q40,205 50,230 T90,230";
	Path p(d);
	```

## Set external properties TODO
Other than basic properties of each shape, there are more external properties, including color, stroke, etc. Animate++ supports easy ways for users to add, modify, fetch and remove properties.
The general way to set attribute is:
```cpp
r.attr(string name, string value);
```
Given an example in below:
`<rect x="10" y="10" width="30" height="30" stroke="black" fill="transparent" stroke-width="5"/>`
This is a rectangle with three external properties, stroke, fill and stroke-width.
```cpp
r.attr();
```
## Complex shapes TODO
Of course, supporting only single type of object is not sufficient to accomplish all fancy functionalities that can potentially be achieved by SVGs. Animate++ also supports multiple shapes contained in one single file to be loaded all together.
```cpp
// load in svg from a path, which is a string of local file directory
ShapePtr g = load(in_path);
// output the object to an SVG file
g->save(out_path);
```

## Input and Output

### Load directly from external SVGs
Other than creating users' own objects, one can simply load the object given relative path of the svg file, creating a <span style="color:purple">ShapePtr</span> object, which is simply a pointer to a Shape object.
```cpp
string in_path = "sample.svg";
ShapePtr g = load(in_path);
```
Users can export the file simply by specifying the output directory, call <span style="color:blue">save</span> function.
```cpp
string out_path = "output.svg";
g -> save(out_path);
```

## Animation

## Examples
