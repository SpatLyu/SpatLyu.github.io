---
title: "Legend in ggplot2 3.5.x"
author: "Wenbo Lv"
date: "2024-09-05"
tags: ["r","tidyverse","ggplot2","legend"]
type: post
weight: 25
showTableOfContents: true
---




``` r
library(tidyverse)
library(ggspatial)

road = sfnetworks::roxel %>% 
  dplyr::mutate(rn = rnorm(nrow(.)))

fig_g = ggplot(data = road) +
    geom_sf(aes(color = rn),
            lwd = 0.75) +
    scale_color_gradientn(colors = c("#4575B4","#91BFDB","#E0F3F8",
                                     "#FFFFBF","#FEE090","#FC8D59"),
                          name = "random number") +
    annotation_north_arrow(location = 'tl',
                           height = unit(1, "cm"),
                           width = unit(1, "cm"),) +
    annotation_scale(location = 'bl') +
    theme_bw() +
    theme(legend.justification = c('right','bottom'),
          legend.position = "inside",
          legend.background = element_rect(fill = 'transparent'),
          legend.direction = "horizontal",
          legend.key.width = unit(15, "pt"),
          legend.key.height = unit(5, "pt"))
fig_g
```

<img src="/posts/legend_in_ggplot2_3-5-x_files/figure-html/fig_road-1.png" width="1350" style="display: block; margin: auto;" />

注意以下几点:

- ggplot2使用连续色带时自定义颜色使用`scale_color_gradientn()`函数;

- 使用ggspatial添加指北针和比例尺时可以通过`location`参数指定相应在四角的位置;

- ggplot2图例放在图主体内需指定`legend.position = "inside"`,进而通过调整`legend.justification`来调整图例的具体位置;

- 图例宽和高(图例主体,不包括图例名字)分别使用`legend.key.width`和`legend.key.height`调节

- 图例背景透明使用`legend.background = element_rect(fill = 'transparent')`
