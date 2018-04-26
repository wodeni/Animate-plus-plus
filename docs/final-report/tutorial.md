# Getting started: a tutorial to Animate++

__Wode "Nimo" Ni - wn2155@columbia.edu__
__Xuanyuan Zhang - xz2580@columbia.edu__

## Installation
### Download required libraries
- [boost](https://www.boost.org/) is utilized in our project. To download boost, simply run
	brew install boost on MacOS or download boost from the [given URL](https://www.boost.org/users/history/version_1_66_0.html) if you are Windows or Linux user.
- [pugi](https://pugixml.org/) is the xml parser which supports all parsing tasks, helping us extract content from SVG files. Tutorial on downloading pugi can be followed through [this link](https://pugixml.org/). After library being downloaded, put the whole unzipped file under the same directory as the code files, and you are ready to go.

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

## Set external properties
Other than basic properties of each shape, there are more external properties, including color, stroke, etc. Animate++ supports easy ways for users to add properties.
The general way to set attribute is:
```cpp
r.attr(string name, string value);
```
Given an example in below.
Before we set up stroke, fill and stroke-width:
<?xml version="1.0"?>
<svg version="1.1" xmlns="http://www.w3.org/2000/svg">
	<rect x="20" y="20" rx="3" ry="3" width="30" height="30">
	</rect>
</svg>

`<rect x="10" y="10" width="30" height="30" stroke="black" fill="transparent" stroke-width="5"/>`
This is a rectangle with three external properties, stroke, fill and stroke-width.
```cpp
r.attr({
		{"stroke", "black"},
		{"fill", "transparent"},
		{"stroke-width", "5"},
});
```
After setting up attributes, that's how it looks like.
<?xml version="1.0"?>
<svg version="1.1" xmlns="http://www.w3.org/2000/svg">
	<rect x="20" y="20" rx="3" ry="3" width="30" height="30" fill="red" stroke="black" stroke-width="5">
	</rect>
</svg>

## Complex shapes
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
In SVGs, objects can have animations, which are defined in the tag `<animateTransform>`.
Animate++ also supports animation editing. Each shape object has an <span style="color:purple">animator</span> named <span style="color:blue">animate</span>. When user wants to edit the animation, simply call the [object_name].animate.[function] to set up the animation. Here are examples in detail.
### Translation
In translation, user needs to define the initial and ending position on x and y axis. An example of translation is shown in below, from "100 100" to "0 200" entails that the object transforms from (100, 100) to (0, 200).
`<animateTransform attributeName="transform" type="translate" dur="2.5s" from="100 100" repeatCount="indefinite" to="0 200" />`
And that's how we use animate++ to rewrite the translation.
```cpp
c.animate.translate(Point(100, 100), Point(0, 200))
	 .duration("2.5s")
	 .loop(true);
```
<?xml version="1.0"?>
<svg version="1.1" xmlns="http://www.w3.org/2000/svg" width=300 height=400>
	<circle cx="100" cy="100" r="100" fill="yellow" opacity="0.5">
		<animateTransform attributeName="transform" type="translate" dur="2.5s" from="100 100" repeatCount="indefinite" to="0 200" />
	</circle>
</svg>

Or instead, given the amount an object is translated from current position instead of its destination using keyword <span style="color:red">by</span>, which we referred to as relative translation. An example is shown in below.
`<animateTransform attributeName="transform" type="translate" by="0 200" dur="2.5s" from="100 100" repeatCount="indefinite" />`
This is also simple to achieve in animate++, for we only give a true boolean value as the third argument taken by translate function, which is by default false.
```cpp
c.animate.translate(Point(100, 100), Point(0, 200), true)
	 .duration("2.5s")
	 .loop(true);
```
<?xml version="1.0"?>
<svg version="1.1" xmlns="http://www.w3.org/2000/svg" width=400 height=600>
	<circle cx="100" cy="100" r="100" fill="yellow" opacity="0.5">
		<animateTransform attributeName="transform" type="translate" dur="2.5s" from="100 100" repeatCount="indefinite" by="0 200" />
	</circle>
</svg>

### Rotation
In rotation, the from and to are in the form "n1 n2 n3", where "n1" entails the degree of rotation, and (n2, n3) indicates the center position of rotation. An example shown in below.
`		<animateTransform attributeName="transform" type="rotate" dur="10s" from="0 100 100" repeatCount="indefinite" to="360 100 100" />
`
That's how animate++ implements such rotation.
```cpp
Point center(100, 100);
r.animate.rotate(center, 0, center, 360)
	 .duration("10s")
	 .loop(true);
```
<?xml version="1.0"?>
<svg version="1.1" xmlns="http://www.w3.org/2000/svg" width=250 height=200>
	<rect x="20" y="20" rx="3" ry="3" width="100" height="100" fill="red" stroke="black" stroke-width="5">
		<animateTransform attributeName="transform" type="rotate" dur="10s" from="0 100 100" repeatCount="indefinite" to="360 100 100" />
	</rect>
</svg>

### Scaling
In scaling, the initial and ending scaling on x and y axis are both required. An example of scaling animation in SVG is shown in below, from "0 0" to "1 1" entails that the object's scale transforms from (0*x, 0*y) to (1*x, 1*y).
`		<animateTransform attributeName="transform" type="scale" dur="2.5s" from="0 0" repeatCount="indefinite" to="1 1" />`
And that's how we use animate++ to rewrite the scaling.
```cpp
c.animate.scale(Point(0, 0), Point(1, 1)) // from="0 0" to="1 1"
	 .duration("2.5s") // dur="2.5s"
	 .loop(true); // repeatCount="indefinite"
```
<?xml version="1.0"?>
<svg version="1.1" xmlns="http://www.w3.org/2000/svg">
	<circle cx="100" cy="100" r="100" fill="aqua" opacity="0.5">
		<animateTransform attributeName="transform" type="scale" dur="2.5s" from="0 0" repeatCount="indefinite" to="1 1" />
	</circle>
</svg>
