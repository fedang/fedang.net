+++
date = 2025-08-22T14:36:29+02:00
title = 'Use memfrob anywhere'
category = ["tool"]
tags = ["memfrob", "calculator", "tool"]
custom_js = ["memfrob.js"]
+++

Have you ever felt the need to frobnicate some memory on the go?
This is the perfect tool for that!

<!--more-->

## Online calculator

<noscript>
Javascript support is required by this tool
</noscript>

Enter what you want to frobnicate below.

<div class="app">
    <textarea id="input" rows="8"></textarea>
    <div>
        <label><input type="radio" value="hex" name="mode"> Hex bytes</label>
        <label><input type="radio" value="str" name="mode"> String</label>
        <label><input type="radio" value="esc" name="mode" checked> Escaped string</label>
        <button id="start">Frobnicate</button>
    </div>
    <textarea id="result" rows="8" readonly></textarea>
</div>

<style>
.app {
    display: flex;
    justify-content: center;
    align-items: center;
    flex-direction: column;
    gap: 0.5em;
}

.app div {
    display: flex;
    justify-content: center;
    flex-direction: row;
    gap: 2em;
}

@media only screen and (max-width: 576px) {
    .app div {
        display: flex;
        flex-direction: column;
        gap: 4px;
    }
}
</style>

## What is `memfrob`?

This glibc function does only one thing: xor the input bytes with `42`.
Here's its [manpage](https://man7.org/linux/man-pages/man3/memfrob.3.html).

It essentially boils down to:

```c
void *memfrob(void *mem, size_t n) {
    char *ptr = mem;
    for (size_t i = 0; i < n; i++)
        ptr[i] ^= 42;
    return mem;
}
```

## Bonus: CUDA memfrob

What if you need to memfrob gigabytes of stuff?
The perfect problem to parallelize, isn't?

Well, here's a small CUDA implementation of `memfrob`.
Take it if you want :wink:

```cpp
#include <cuda_runtime.h>

__global__ void frobnicator(unsigned char *dev, int n) {
    int tid = blockIdx.x * blockDim.x + threadIdx.x;
    if (tid < n)
        dev[tid] ^= 42;
}

void *cuda_memfrob(void *mem, size_t n)
{
    unsigned char *dev;
    cudaMalloc(&dev, n);
    cudaMemcpy(dev, mem, n, cudaMemcpyHostToDevice);

    int threads = 256;
    int blocks  = (n + threads - 1) / threads;
    frobnicator<<<blocks, threads>>>(dev, n);

    cudaDeviceSynchronize();
    cudaMemcpy(mem, dev, n, cudaMemcpyDeviceToHost);
    cudaFree(dev);
    return mem;
}
```

Also, note that I didn't run a benchmark...
