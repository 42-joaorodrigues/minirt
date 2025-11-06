
# miniRT Walk-through

**miniRT** is an introductory project to **Ray Tracing** that offers a first look into the world of Computer Graphics programming.  
By completing this project, you'll gain a solid understanding of **3D vector mathematics**, geometric transformations, and the fundamental principles behind the **Ray Tracing** protocol.

Before jumping into the "fun part" (parsing and rendering), we'll need to understand how vectors work.

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
