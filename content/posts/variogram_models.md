---
title: "Variogram Models"
author: "Wenbo Lyu"
date: "2026-10-22"
description: "Variogram models and covariance kernels for spatial dependence"
tags: ["geostatistics", "spatial-statistics", "statistics", "r"]
type: post
weight: 25
showTableOfContents: true
---

## Variogram models

The variogram describes how spatial dissimilarity changes with the separation distance between locations. The theoretical semivariogram is defined as

$$
\gamma(h) = \frac{1}{2}
\operatorname{Var}\left[Z(\mathbf{s})-Z(\mathbf{s}+\mathbf{h})\right],
$$

where $Z(\mathbf{s})$ is a spatial random field, $\mathbf{h}$ is a spatial lag vector, and $h=\|\mathbf{h}\|$ is the lag distance. Under second-order stationarity, the semivariogram is related to the covariance function by

$$
\gamma(h)=C(0)-C(h).
$$

A common variogram model with a nugget effect is written as

$$
\gamma(h)=
\begin{cases}
0, & h=0,\\
c_0+c\,g(h), & h>0,
\end{cases}
$$

where $c_0$ is the nugget variance, $c$ is the partial sill, and $g(h)$ is a normalized variogram function. The total sill is $c_0+c$ when $g(h)$ approaches one.

### Spherical model

The spherical model reaches its sill at a finite range and is commonly used to represent spatial dependence with a clearly defined correlation distance.

$$
\gamma(h)=
\begin{cases}
c_0+c\left[
\frac{3h}{2a}-\frac{h^3}{2a^3}
\right], & 0<h\leq a,\\
c_0+c, & h>a,\\
0, & h=0,
\end{cases}
$$

where $a$ is the range parameter. The semivariogram increases approximately linearly at short distances and flattens to the sill at $h=a$.

### Exponential model

The exponential model describes spatial dependence that decreases rapidly at short distances and approaches the sill asymptotically.

$$
\gamma(h)=
\begin{cases}
0, & h=0,\\
c_0+c\left[1-\exp\left(-\frac{h}{a}\right)\right],
& h>0.
\end{cases}
$$

The parameter $a$ controls the decay rate. Unlike the spherical model, the exponential model does not reach its sill at a finite distance. Under this parameterization, the correlation range is often approximated by $3a$.

### Gaussian model

The Gaussian model represents highly smooth spatial variation, with a gradual increase in semivariance near the origin.

$$
\gamma(h)=
\begin{cases}
0, & h=0,\\
c_0+c\left[1-\exp\left(-\frac{h^2}{a^2}\right)\right],
& h>0.
\end{cases}
$$

The parameter $a$ controls the spatial scale. The Gaussian model approaches its sill asymptotically, and its smooth behavior near the origin makes it suitable for spatial fields with strong local continuity. Under this parameterization, the practical range is approximately $\sqrt{3}a$ when 95% of the structured sill is used as the threshold.

### Power model

The power model is an unbounded variogram model that can represent spatial processes without a finite sill.

$$
\gamma(h)=
\begin{cases}
0, & h=0,\\
c h^\alpha, & h>0,
\end{cases}
$$

where `\(c>0\)` is a scale parameter and `\(0<\alpha<2\)`. The power model does not have a finite sill or range and is useful when spatial variability continues to increase over the observed distance scale.

## Covariance kernels

Covariance kernels describe the covariance between observations as a function of their spatial separation. For a stationary and isotropic random field, a covariance function can be written as

$$
C(h)=\sigma^2 K(h),
$$

where `\(\sigma^2\)` is the structured variance and `\(K(h)\)` is a normalized covariance kernel satisfying `\(K(0)=1\)`. When a nugget effect is included, the covariance between distinct locations remains governed by the structured component, while the nugget contributes to the variance at an individual location.

### Exponential kernel

$$
K(h)=\exp\left(-\frac{h}{a}\right).
$$

The exponential kernel produces relatively rough spatial fields and an exponential decay in correlation. It corresponds to the exponential variogram through `\(\gamma(h)=\sigma^2[1-K(h)]\)` when there is no nugget effect.

### Gaussian kernel

$$
K(h)=\exp\left(-\frac{h^2}{a^2}\right).
$$

The Gaussian kernel produces smooth spatial fields and a rapid decay in correlation as distance increases. Its behavior near the origin differs from the exponential kernel because its first derivative at zero is zero.

### Matérn kernel

The Matérn kernel provides a flexible family of covariance functions that controls spatial smoothness through an additional parameter.

$$
K(h)=
\frac{2^{1-\nu}}{\Gamma(\nu)}
\left(\frac{h}{a}\right)^\nu
K_\nu\left(\frac{h}{a}\right),
\qquad h>0,
$$

with `\(K(0)=1\)`, where `\(\nu>0\)` is the smoothness parameter, `\(\Gamma(\cdot)\)` is the gamma function, and `\(K_\nu(\cdot)\)` is the modified Bessel function of the second kind. Larger values of `\(\nu\)` generally produce smoother spatial fields. The Matérn family includes the exponential kernel as the special case `\(\nu=1/2\)` under this parameterization.

### Cauchy kernel

A commonly used generalized Cauchy kernel is

$$
K(h)=\left[1+\left(\frac{h}{a}\right)^2\right]^{-\beta},
\qquad \beta>0.
$$

The Cauchy kernel exhibits polynomial rather than exponential decay. It can therefore represent spatial dependence with relatively long tails. The parameter `\(a\)` controls the spatial scale, while `\(\beta\)` controls the decay rate.

### Stable kernel

A generalized stable kernel can be written as

$$
K(h)=\exp\left[-\left(\frac{h}{a}\right)^\alpha\right],
\qquad 0<\alpha\leq 2.
$$

The parameter `\(\alpha\)` controls the shape and smoothness of the kernel. The exponential kernel is recovered when `\(\alpha=1\)`, and the Gaussian kernel is recovered when `\(\alpha=2\)`.

## Model comparison

| Model | Mathematical behavior | Main characteristics |
|-------|------------------------|----------------------|
| Spherical | Finite range | Reaches the sill at a finite distance |
| Exponential | Exponential decay | Relatively rough fields and rapid short-distance increase |
| Gaussian | Gaussian decay | Smooth fields with gradual increase near the origin |
| Power | Unbounded growth | No finite sill or range |
| Matérn | Flexible covariance decay | Explicit control over smoothness |
| Cauchy | Polynomial decay | Long-tailed spatial dependence |
| Stable | Generalized exponential decay | Flexible behavior between exponential and Gaussian kernels |

## Practical considerations

The choice of a variogram model or covariance kernel should reflect the spatial structure of the data and the intended analysis.

- Use the spherical model when a finite practical range is appropriate.
- Use the exponential model when spatial dependence decays relatively rapidly and the field is not especially smooth.
- Use the Gaussian model when the underlying spatial field is expected to be smooth.
- Use the power model when the empirical semivariogram does not exhibit a clear sill over the observed distance range.
- Use the Matérn kernel when smoothness needs to be estimated or controlled explicitly.
- Consider the Cauchy kernel when long-tailed dependence is plausible.
- Use the stable kernel when a flexible decay profile is needed.

Model selection should also consider the nugget effect, anisotropy, stationarity assumptions, sampling design, and parameter estimation uncertainty. Variogram fitting and spatial cross-validation can help assess whether a candidate model adequately captures the observed spatial dependence.

## References

- [Ultimate Guide to Variogram Models in Geostatistics](https://www.numberanalytics.com/blog/ultimate-guide-variogram-models-geostatistics)
- [Ultimate Guide to the Spherical Model in Geostatistics](https://www.numberanalytics.com/blog/ultimate-guide-spherical-model-geostatistics)
