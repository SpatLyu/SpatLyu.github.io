---
title: "Increment operator in cpp"
author: "Wenbo Lv"
date: "2024-07-06"
tags: ["cpp","rcpp","r"]
type: post
weight: 25
showTableOfContents: true
---



In cpp, **i++** and **++i** are two different increment operators, known as **post-increment** and **pre-increment**, respectively. The main difference between them lies in *the order of operations* and *the return value*.

### **i++** (Post-Increment)

The post-increment operator **i++** returns the current value of the variable before incrementing it. Specifically:

1. It returns the current value of the variable.
2. Then, it increments the variable's value by 1.

Example:
```cpp
int i = 1;
int a = i++;  // a = 1, i = 2
```
In this example, `a` is assigned the current value of `i` (1), and then `i` is incremented to 2.

### **++i** (Pre-Increment)

The pre-increment operator **++i** increments the variable's value by 1 before returning the new value. Specifically:

1. It increments the variable's value by 1.
2. Then, it returns the incremented value.

Example:
```cpp
int i = 1;
int a = ++i;  // a = 2, i = 2
```
In this example, `i` is first incremented to 2, and then `a` is assigned the new value of `i` (2).

### Summary

- **i++**: Returns the original value, then increments. The operation sequence is: return value -> increment.
- **++i**: Increments first, then returns the new value. The operation sequence is: increment -> return value.

### Performance Considerations

In certain situations, especially in loops, using pre-increment (**++i**) can be more efficient than post-increment (**i++**), particularly for complex iterator objects. This is because post-increment needs to save the object's original state to return the original value, whereas pre-increment does not. However, for basic types like `int`, modern compilers typically optimize away the differences, making the performance impact negligible.

### Usage Recommendations

1. If you simply need to increment a variable without using its old value, prefer pre-increment (**++i**).
2. If you need to use the value of the variable before incrementing, use post-increment (**i++**).

### A small example

construct the following cpp code: 


``` r
src = '
#include <Rcpp.h>

// [[Rcpp::export]]
void test_increment(){
  const int n = 5;
  
  // use i++
  for(int i = 0; i < n; i++){
    Rcpp::Rcout << "using post increment: " << i << "---" << i++ << "\\n";
  }
  
  // use ++i
  for(int i = 0; i < n; ++i){
    Rcpp::Rcout << "using pre increment: " << i << "---" << ++i << "\\n";
  }
}
'
Rcpp::sourceCpp(code = src)
test_increment()
```

```
## using post increment: 0---0
## using post increment: 2---2
## using post increment: 4---4
## using pre increment: 0---1
## using pre increment: 2---3
## using pre increment: 4---5
```

