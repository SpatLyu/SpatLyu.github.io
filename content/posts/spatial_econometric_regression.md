---
title: "Spatial Econometrics Regression"
author: "Wenbo Lv"
date: "2024-10-25"
description: "Spatial linear regression (spatial econometric regression) model description"
tags: ["econometrics","statistics","geoinformatics","r"]
type: post
weight: 25
showTableOfContents: true
---

## Generalized Nested Spatial Model (GSNM)

$$
y = \rho_{Lag} W y + X\beta + WX\gamma + \mu,
\mu = \rho_{Err} W \mu + \xi
$$

where $y$ is an $(N \times 1)$ vector of observations on a response variable taken at each of $N$ locations,$W$ is a spatial weight matrix, which is a non-negative matrix of size $N \times N$, $X$ is an $(N \times k)$ matrix of covariates, $\beta$ is a $(k \times 1)$ vector of parameters, $\mu$ is an $(N \times 1)$ spatially autocorrelated disturbance vector, $\xi$ is an $(N \times 1)$ vector of independent and identically distributed disturbances, $\rho_{Lag}$ and $\rho_{Err}$ is a scalar spatial parameter. $\gamma$ is a $(k' \times 1)$ vector of parameters. $k'$ defines the subset of the intercept and covariates, often $k' = k-1$ when using row standardised spatial weights and omitting the spatially lagged intercept.

This may be constrained to the double spatial coefficient model SAC/SARAR by setting ${\mathbf \gamma} = 0$, to the spatial Durbin (SDM) by setting $\rho_{\mathrm{Err}} = 0$, and to the error Durbin model (SDEM) by setting $\rho_{\mathrm{Lag}} = 0$. Imposing more conditions gives the spatial lag model (SLM) with ${\mathbf \gamma} = 0$ and $\rho_{\mathrm{Err}} = 0$, the SEM with ${\mathbf \gamma} = 0$ and $\rho_{\mathrm{Lag}} = 0$, and the SLX with $\rho_{\mathrm{Lag}} = 0$ and $\rho_{\mathrm{Err}} = 0$.

## Maximum likelihood estimation in **spatialreg**

For models with single spatial coefficients (SEM and SDEM using `errorsarlm()`, SLM and SDM using `lagsarlm()`), the methods initially described by Ord are used. The following table shows the functions that can be used to estimate the models described above using maximum likelihood.

| model | model name                      | maximum likelihood estimation function |
|-------|---------------------------------|----------------------------------------|
| SEM   | spatial error                   | `errorsarlm(..., Durbin=FALSE)`        |
| SEM   | spatial error                   | `spautolm(..., family="SAR")`          |
| SDEM  | spatial Durbin error            | `errorsarlm(..., Durbin=TRUE)`         |
| SLM   | spatial lag                     | `lagsarlm(..., Durbin=FALSE)`          |
| SDM   | spatial Durbin                  | `lagsarlm(..., Durbin=TRUE)`           |
| SAC   | spatial autoregressive combined | `sacsarlm(..., Durbin=FALSE)`          |
| GNM   | general nested                  | `sacsarlm(..., Durbin=TRUE)`           |

[Spatial Econometrics Models](https://r-spatial.org/book/17-Econometrics.html)

[Review of spatial regression models](https://xishansnow.github.io/posts/e35ae3a.html)
