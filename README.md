`fad` is a toy implementation of automatic differentiation, which I wrote for fun after reading [this paper](http://www.jmlr.org/papers/volume18/17-468/17-468.pdf) by Baydin et al.

`fad` reads a function and a point from `stdin`. It outputs the value and the derivative of the function at the given point:
```
echo "x^2 ; x = 4" | ./fad
```
```
Function value: 16
Derivative d/dx: 8
```

You can specify the function using the operators `+`, `-`, `*`, `/`, `^` and the functions `sin`, `cos`, `exp` and `ln`. Variables are specified using the characters `a-z`.

`fad` supports functions of several variables:
```
echo "y * cos(z * x) * ln(sin(x) + exp(y) + 3*z^3) ; x = 2, y = 3, z = 1.5" | ./fad
```
```
Function value: -10.2103
Derivative d/dx: -2.14345
Derivative d/dy: -5.32034
Derivative d/dz: -4.84349
```

`fad` also includes a simple optimizer. The optimizer uses gradient descent with momentum. You run the optimizer by specifying the `steps` argument, which specifies the number of steps that the gradient descent should run. `fad` outputs the result of the descent:
```
echo "x^2 + y^2 + z^2 + 10 ; x = 20, y = 50, z = 100" | ./fad -steps 500
```
```
Function value: 10
x: -1.1042e-11
y: -2.76051e-11
z: -5.52101e-11
```
