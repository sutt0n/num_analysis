Lab One
========

Bisection Method - https://en.wikipedia.org/wiki/Bisection_method

Horner's Algorithm/method - https://en.wikipedia.org/wiki/Horner%27s_method

Bisection Rules
===============

* c = a+b/2
* f(x) must be continuous (i.e. a polynomial minimum of degree one; e.g. f(x) = x + 2 or something like that)
* [not implemented, oopsies] neither a or b can be zero; doing so results in an estimated root: 0 < c < 1, which is not allowed
* other basic mathematical ailments (i.e. no dividing by zero [typically try not to divide by any variable that doesn't have `varName != 0` declared beforehand])
