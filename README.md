# 2D Graphics Editor

## Overview

The 2D Graphics Editor is a menu-driven graphics application developed in C language. The program allows users to create, edit, display, and manage basic geometric shapes on a virtual canvas. It demonstrates the implementation of fundamental computer graphics concepts using character-based rendering in the console environment.

The editor maintains a collection of graphical objects and provides operations to add, modify, delete, and redraw shapes dynamically.

---

## Objectives

* To understand the fundamentals of Computer Graphics.
* To implement graphical object manipulation using C programming.
* To demonstrate drawing algorithms for basic geometric shapes.
* To provide a simple text-based graphics editor for educational purposes.

---

## Features

### Shape Creation

The application supports creation of the following graphical objects:

* Line
* Circle
* Rectangle
* Triangle

### Object Management

Users can:

* Add new shapes
* Modify existing shapes
* Delete selected shapes
* Display all shapes on the canvas
* Clear the entire canvas

### Dynamic Redrawing

Whenever a shape is added, modified, or deleted, the canvas is automatically redrawn to maintain graphical consistency.

---

## Technologies Used

* Programming Language: C
* Compiler: GCC / MinGW GCC
* IDE: Visual Studio Code
* Version Control: Git & GitHub

---

## Canvas Specifications

| Parameter       | Value         |
| --------------- | ------------- |
| Canvas Width    | 80 Characters |
| Canvas Height   | 25 Characters |
| Maximum Objects | 100           |

The canvas is represented using a two-dimensional character array.

---

## Algorithms Implemented

### 1. Bresenham Line Drawing Algorithm

Used for drawing straight lines efficiently between two points.

Features:

* Integer arithmetic based
* Fast execution
* Accurate line rendering

### 2. Midpoint Circle Algorithm

Used for drawing circles.

Features:

* Efficient circle generation
* Uses symmetry of circle
* Reduces computational overhead

---

## Data Structures Used

### Shape Enumeration

The program categorizes objects using:

* EMPTY
* LINE
* CIRCLE
* RECTANGLE
* TRIANGLE

### Shape Structure

Each graphical object stores:

* Coordinates
* Radius (for circles)
* Shape type
* Active status

This structure enables efficient storage and manipulation of objects.

---

## Functional Modules

### Canvas Management

Functions:

* initialize_canvas()
* clear_canvas()
* display_canvas()

Responsibilities:

* Create canvas
* Clear canvas
* Display graphics

---

### Shape Drawing Functions

Functions:

* draw_line()
* draw_circle()
* draw_rectangle()
* draw_triangle()

Responsibilities:

* Render graphical objects on the canvas.
* Handle coordinate calculations.
* Maintain drawing boundaries.

---

### Object Operations

Functions:

* add_line()
* add_circle()
* add_rectangle()
* add_triangle()

Responsibilities:

* Accept user input.
* Create graphical objects.
* Store objects in memory.

---

### Editing Operations

Functions:

* modify_object()
* delete_object()

Responsibilities:

* Update existing shapes.
* Remove unwanted objects.
* Refresh the display automatically.

---

### Redraw Engine

Function:

* redraw_all()

Responsibilities:

* Reconstruct complete canvas.
* Display all active objects.
* Maintain consistency after editing.

---

## Program Menu

The application provides the following menu:

1. Add Line
2. Add Circle
3. Add Rectangle
4. Add Triangle
5. Delete Object
6. Modify Object
7. Display Canvas
8. Clear All
9. Exit

---

## Working Procedure

1. Start the application.
2. Select the desired operation from the menu.
3. Enter coordinates or dimensions.
4. The shape is rendered on the canvas.
5. Users may modify or delete objects.
6. The canvas updates automatically.
7. Continue editing until exit.

---

## Applications

* Educational graphics demonstrations
* Computer Graphics laboratory projects
* Understanding geometric algorithms
* Learning data structures in graphics systems
* Console-based graphical simulations

---

## Future Enhancements

* Color support
* Polygon drawing
* Shape filling algorithms
* Save and load projects
* Mouse-based interaction
* GUI implementation using graphics libraries
* Rotation, scaling, and translation transformations

---

## Author

**Mubashireen Gaffarmiya**

Department of Engineering

---

## Conclusion

The 2D Graphics Editor successfully demonstrates the implementation of basic computer graphics concepts using C programming. The project integrates shape creation, editing, deletion, and redrawing functionalities while utilizing efficient graphical algorithms such as Bresenham's Line Algorithm and Midpoint Circle Algorithm. It serves as an effective educational tool for understanding the fundamentals of computer graphics and object-oriented graphical manipulation.
