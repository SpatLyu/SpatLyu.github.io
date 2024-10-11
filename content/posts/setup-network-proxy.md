---
title: "Setting up a network proxy"
author: "Wenbo Lv"
date: "2024-06-05"
tags: ["network proxy","coding"]
type: post
weight: 25
showTableOfContents: true
---

Python

``` python
import os
os.environ["http_proxy"] = "http://127.0.0.1:7890"
os.environ["https_proxy"] = "http://127.0.0.1:7890" 
```

R

```r
Sys.setenv(https_proxy="http://127.0.0.1:7890")
Sys.setenv(http_proxy="http://127.0.0.1:7890") 
```

Julia

```julia
ENV["https_proxy"]="http://127.0.0.1:7890/" 
```

Git

```git
git config --global http.proxy 'http://127.0.0.1:7890'
git config --global https.proxy 'http://127.0.0.1:7890'
```

nodejs

```nodejs
npm config set https-proxy http://127.0.0.1:7890 
```

**Change the value from 7890 to the corresponding port number based on your network proxy port number.**