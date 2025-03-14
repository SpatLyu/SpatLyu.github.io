---
title: Rmarkdown Setup
author: Wenbo Lv
date: '2024-06-05'
description: "Frequently used rmarkdown configuration Settings"
tags: ["r","rmarkdown"]
type: post
weight: 25
showTableOfContents: true
---

### 常用的 knitr 设置

``````r
```{r setup, include = FALSE}
knitr::opts_chunk$set(echo = TRUE,
                      dpi = 300,
                      warning = FALSE,
                      message = FALSE,
                      out.width = "100%",
                      out.height = "100%",
                      fig.align = 'center',
                      comment = "##")
```
``````

### 灰白背景rmarkdown模板

``````r
---
title: "xxx"
author: "xxx"
date: "`r Sys.Date()`"
output: #latex_document
  prettydoc::html_pretty:
    theme: tactile
    highlight: github
---

```{r setup, include = FALSE}
knitr::opts_chunk$set(echo = TRUE,
                      dpi = 300,
                      warning = FALSE,
                      message = FALSE,
                      out.width = "100%",
                      out.height = "100%",
                      fig.align = 'center',
                      comment = "##",
                      htmltools.dir.version = FALSE)
```
``````

### 导出word文档友好

``````r
---
title: "xxxxxxx"
author: "xxxxx"
output: 
  officedown::rdocx_document:
    mapstyles:
      Normal: ['First Paragraph']
---

```{r setup, include = FALSE}
knitr::opts_chunk$set(echo = TRUE,
                      dpi = 300,
                      warning = FALSE,
                      message = FALSE,
                      out.width = "100%",
                      out.height = "100%",
                      fig.align = 'center',
                      comment = "##")
```
``````


