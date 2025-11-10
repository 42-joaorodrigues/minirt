
# miniRT Guide

**miniRT** is an introductory project to **Ray Tracing** that offers a first look into the world of Computer Graphics programming.  
By completing this project, you'll gain a solid understanding of **3D vector mathematics**, geometric transformations, and the fundamental principles behind the **Ray Tracing** protocol.

Before jumping into the "fun part", we'll need to understand how vectors work.

## Vector Mathematics

**3D Vectors** are used all across **ray tracing** to represent points, directions and colors.

A **Vector** is a quantity that as both **magnitude** (length) and **direction**.
In 3D space a vector is usually written like this:

```
v = (x, y, z)
```

In our code we will define vectors with the following structure:
```c
typedef struct s_vec3
{
	double	x;
	double	y;
	double	z;
}			t_vec3;
```

Let's now have a look into **basic vector operations**:

### Addition & Subtraction
```c
t_vec3 vec_add(t_vec3 a, t_vec3 b)
{
    return (t_vec3){a.x + b.x, a.y + b.y, a.z + b.z};
}

t_vec3 vec_sub(t_vec3 a, t_vec3 b)
{
    return (t_vec3){a.x - b.x, a.y - b.y, a.z - b.z};
}
```
This ones are pretty straight forward, if `vector a` is (1, 0, 0) and `vector b` is (0, 1, 0), the result of the **vec_add** will be (1, 1, 0) and the result of **vec_sub** will be (1, -1, 0).

---

### Scalar Multiplication
```c
t_vec3 vec_scale(t_vec3 v, double s)
{
    return (t_vec3){v.x * s, v.y * s, v.z * s};
}
```
Every axis of the `vector` is multiplied by the scaler `s`. A `vector a` (0, 1, 1) with an `s` of 3 would result in a vector (0, 3, 3)

---

### Dot Product

The **dot product** can be calculated in two different ways:

**Geometric Form**:

```
a · b = |a| |b| cos(θ)
```

Where `|a|` = length of a, `|b|` = length of b, and `θ`  = angle between a and b.

**Component Form**:

```
a · b = a₁b₁ + a₂b₂ + a₃b₃
```
This is the one we will use in our program, since we already have all the required components.

```c
double vec_dot(t_vec3 a, t_vec3 b)
{
    return (a.x * b.x + a.y * b.y + a.z * b.z);
}
```

The result will be a value that measures how aligned `vector a` and `vector b` are:
- dot = 0: the vectors are **perpendicular**
- dot > 0: the vectors point to **similar directions**
- dot < 0: the vectors point to **opposite directions**

---

### Cross Product

```c
t_vec3 vec_cross(t_vec3 a, t_vec3 b)
{
    return (t_vec3){
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    };
}
```

Produces a vector **perpendicular** to both input vectors. If given a `vector a` (1, 0, 0) and a `vector b` (0, 1, 0), the result will be a vector (0, 0, 1).

---

### Normalization

Makes a vector`s **magnitude** (length) equal to one.

```c
double	vec3_magnitude(t_vec3 v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

t_vec3 vec_norm(t_vec3 v)
{
    double len = vec3_magnitude(v); // calculate length
	if (len == 0)
        return (t_vec3){0, 0, 0}; // exit early if 0, to stop division by 0 error
    return (t_vec3){v.x / len, v.y / len, v.z / len}; // divides all the axis by length
}
```

Formula used for **magnitude** calculation:
```
|v| = √(x² + y² + z²)
```

---
Now that we understand the main **vector** operations, we can move to building the parsing.

## Program Arguments

The program accepts one argument of type .rt, this file includes all the necessary configurations for our scene.

## Parsing

In this part, we will have to parse the given .rt file to our programs memory.

Example of a scene with all the **mandatory** requirements:

```
A 0.2 255,255,255 // Ambient Lighting
C 0,0,0 0,0,1 70 // Camera
L -60,60,0 0.7 255,0,0 // Light

sp -10,0,40 13 0,0,255 // Sphere
pl 0,-10,0 0,1,0.1 0,255,0 // Plane
cy 10,0,40 0,1,0 10 20 255,0,0 // Cylinder
```
In my case, I used a `struct s_scene` that stores all the data with individual **structures** for each **element** of the scene:

```c
typedef struct s_scene
{
	t_ambient	ambient;
	t_camera	camera;
	t_light		light;
	t_object	objects[MAX_OBJECTS];
	int			obj_count;
}				t_scene;
```

Now we'll go more into detail about each element of this struct one by one.

### Ambient Lighting

This is the indirect light that is present throughout the whole *scene*.

Ex: ```A 0.2 255,255,255```
- **A** is the element`s identifier.
- **0.2** stands for the ratio (brightness), this value ranges from `0.0 to 1.0`
- **255,255,255** are the *RGB* values..

Based on this example, the **ambient lighting** for the *scene* will be a *soft white light*.

---

### Camera

The camera values will determine it's location, direction and the *FOV* (Field of View).

Ex: ```C 0,0,0 0,0,1 70```
- **C** is the element`s identifier.
- **0,0,0** is the ratio camera's position.
- **0,0,1** is the direction the camera is facing.
- **70** is the horizontal *FOV*.

In this example, we'll have the **camera** at the position 0, facing the `Z` axis with a *FOV* of 70.

---

### Light

This is the *external light*, for the **bonus part**, 
