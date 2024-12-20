---
title: "Pipes In R"
author: "Wenbo Lv & Yangyang Lei"
date: "2024-06-12"
description: "Useful pipes in baseR and magrittr"
tags: ["r","tidyverse","dplyr","magrittr"]
type: post
weight: 25
showTableOfContents: true
---



In this post,we will state the use of pipes in R, includes %>%, %$%, %T>%, %<>% and |>.

First let's construct some data for a demonstration of pipes usage in R
*(PS: The ideas and example data for this post came from [this dplyr github issue](https://github.com/tidyverse/dplyr/issues/7037))*:


``` r
packageVersion('magrittr')
```

```
## [1] '2.0.3'
```


``` r
library(magrittr)

exampledt = tibble::tibble(
  BP = c("-", "-", "A", "B"),
  CL = c("-", "C", "-", "D"),
  MF = c("-", "-", "-", "E")
) %>% 
  {. == '-'} %>% 
  tibble::as_tibble()
exampledt
```

```
## # A tibble: 4 × 3
##   BP    CL    MF   
##   <lgl> <lgl> <lgl>
## 1 TRUE  TRUE  TRUE 
## 2 TRUE  FALSE TRUE 
## 3 FALSE TRUE  TRUE 
## 4 FALSE FALSE FALSE
```

# Pipes in magrittr

## %>% most commonly used magrittr pipe

### Basic piping

- **x %>% f** is equivalent to **f(x)**
- **x %>% f(y)** is equivalent to **f(x, y)**
- **x %>% f %>% g %>% h** is equivalent to **h(g(f(x)))**

### Argument placeholder

(***Suppose **f** has only two parameters***)

- **x %>% f(y, .)** is equivalent to **f(y, x)**
- **x %>% f(y, z = .)** is equivalent to **f(y, z = x)**

### Re-using the placeholder for attributes

(***Suppose **f** has three parameters,and y and z are not its first parameter***)

- **x %>% f(y = nrow(.), z = ncol(.))** is equivalent to **f(x, y = nrow(x), z = ncol(x))**

- **x %>% {f(y = nrow(.), z = ncol(.))}** is equivalent to **f(y = nrow(x), z = ncol(x))**

### Building (unary) functions

**f = . %>% cos %>% sin** is equivalent to **f = function(.) sin(cos(.))**

### Usuage


``` r
exampledt %>% 
  dplyr::mutate(col3sum = rowSums(.))
```

```
## # A tibble: 4 × 4
##   BP    CL    MF    col3sum
##   <lgl> <lgl> <lgl>   <dbl>
## 1 TRUE  TRUE  TRUE        3
## 2 TRUE  FALSE TRUE        2
## 3 FALSE TRUE  TRUE        2
## 4 FALSE FALSE FALSE       0
```

``` r
exampledt %>% 
  dplyr::mutate(.,col3sum = rowSums(.))
```

```
## # A tibble: 4 × 4
##   BP    CL    MF    col3sum
##   <lgl> <lgl> <lgl>   <dbl>
## 1 TRUE  TRUE  TRUE        3
## 2 TRUE  FALSE TRUE        2
## 3 FALSE TRUE  TRUE        2
## 4 FALSE FALSE FALSE       0
```

``` r
exampledt %>% 
  dplyr::mutate({col3sum = rowSums(.)})
```

```
## # A tibble: 4 × 4
##   BP    CL    MF    `{ ... }`
##   <lgl> <lgl> <lgl>     <dbl>
## 1 TRUE  TRUE  TRUE          3
## 2 TRUE  FALSE TRUE          2
## 3 FALSE TRUE  TRUE          2
## 4 FALSE FALSE FALSE         0
```

``` r
exampledt %>% 
  dplyr::mutate(col3sum = {rowSums(.)})
```

```
## # A tibble: 4 × 4
##   BP    CL    MF    col3sum
##   <lgl> <lgl> <lgl>   <dbl>
## 1 TRUE  TRUE  TRUE        3
## 2 TRUE  FALSE TRUE        2
## 3 FALSE TRUE  TRUE        2
## 4 FALSE FALSE FALSE       0
```

``` r
exampledt %>% 
  rowSums() %>% 
  {. != 3} %>% 
  sum()
```

```
## [1] 3
```

``` r
exampledt %>% 
  rowSums() %>% 
  sum(. != 3)
```

```
## [1] 10
```

``` r
exampledt %>% 
  rowSums() %>% 
  sum({. != 3})
```

```
## [1] 10
```

``` r
exampledt %>% 
  rowSums() %>% 
  {sum(. != 3)}
```

```
## [1] 3
```


## %$% pipe with exposition of variables

The “exposition” pipe, %$% exposes the names within the *left-hand side object* to the *right-hand side expression*. Essentially, it is a short-hand for using the with functions (and the same left-hand side objects are accepted). This operator is handy when functions do not themselves have a data argument, as for example *lm* and *aggregate* do. Here are a few examples as illustration:


``` r
iris %>%
  dplyr::filter(Sepal.Length > mean(Sepal.Length)) %$%
  cor(Sepal.Length, Sepal.Width)
```

```
## [1] 0.3361992
```

## %T>% pipe returns the left-hand side value

The “tee” pipe, %T>% works like %>%, except it returns the *left-hand side value*, and *not the result of the right-hand side operation*. This is useful when a step in a pipeline is used for its side-effect (printing, plotting, logging, etc.). 


``` r
rnorm(200) %>%
matrix(ncol = 2) %T>%
plot %>% # plot usually does not return anything. 
colSums()
```

<img src="/posts/pipes_in_r_files/figure-html/unnamed-chunk-5-1.png" width="2100" style="display: block; margin: auto;" />

```
## [1] -0.449311 13.174459
```

## %<>% as the first pipe in a chain

The “assignment” pipe %<>% can be used as the first pipe in a chain. The effect will be that *the result of the pipeline* is *assigned* to the *left-hand side object*, rather than returning the result as usual.The %<>% can be used whenever *expr = ...* makes sense, e.g. 

- **foo = foo %>% bar %>% baz** boils down to **foo %<>% bar %>% baz**
- **x[1:10] %<>% foo %>% bar**
- **x$baz %<>% foo %>% bar**

# |> pipe in baseR

### Basic piping

- **x |> f()** is equivalent to **f(x)**
- **x |> f(y)** is equivalent to **f(x, y)**
- **x |> f() |> g() |> h()** is equivalent to **h(g(f(x)))**

### Argument placeholder
- must use the **_** placeholder with a named argument
- **x %>% f(y, z = _)** is equivalent to **f(y, z = x)**
- **x %>% f(y, _)** is not available

### Usage


``` r
exampledt |> 
  _$MF
```

```
## [1]  TRUE  TRUE  TRUE FALSE
```

``` r
exampledt |> 
  rowSums()
```

```
## [1] 3 2 2 0
```


``` r
exampledt |> 
  dplyr::mutate(col3sum = rowSums(x = _))
```

```
## Error: invalid use of pipe placeholder (<text>:2:0)
```

## Reference: 

1. https://magrittr.tidyverse.org/index.html
