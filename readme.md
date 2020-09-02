# fast inverse square root

![](https://github.com/jethrodaniel/fast_inv_sqrt/workflows/ci/badge.svg)
![](https://img.shields.io/github/license/jethrodaniel/fast_inv_sqrt.svg)

The famed _evil floating point bit level hacking_..

## run locally

```
git clone --recursive https://github.com/jethrodaniel/fast_inv_sqrt
cd fast_inv_sqrt
make
```

## todo

- [ ] x86 version via `rsqrtss`, etc [link](https://stackoverflow.com/a/1528751/7132678)
  - [ ] ~~compare output to hand-written assembly?~~
- [ ] `sqrt` version
- [ ] profiling

## credit

- https://medium.com/hard-mode/the-legendary-fast-inverse-square-root-e51fee3b49d9
