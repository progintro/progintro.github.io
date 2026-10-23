# Κώδικας Διαλέξεων

<!-- TODO(2026-27) -->

_Ο κώδικας των διαλέξεων θα προστίθεται εδώ καθώς προχωρά το μάθημα._
_Ο κώδικας του περασμένου έτους είναι [εδώ](/past/2025/assets/code.md)._

## lec03

```c
#include <stdio.h>
#include <math.h>

/* A program for computing the area of a square triangle.
   Credit: Konstantinos
*/

float embadon(float a, float b){
        return a*b/2;
}

float hypotenuse(float a, float b) {
  return sqrt(a * a + b * b);
}


int main() {
  float result = embadon(3.5,4.8937489);
  printf("The area of a triangle with sides %d and %d is %f\n", 3, 4, result);
  return 0;
}
```
