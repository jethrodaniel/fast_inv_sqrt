# fast inverse square root

The famed _evil floating point bit level hacking_, explained.

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
