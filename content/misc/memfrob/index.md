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

## What is `memfrob`?

This function is included in glibc and does only one thing: xor the input bytes with `42`.

See the [manpage](https://man7.org/linux/man-pages/man3/memfrob.3.html).

## Online calculator

<noscript>
Javascript support is required by this tool
</noscript>

Enter what you want to frobnicate below.

<div class="app">
    <textarea id="input" rows="6"></textarea>
    <div>
        <label><input type="radio" value="hex" name="mode"> Hex bytes</label>
        <label><input type="radio" value="str" name="mode"> String</label>
        <label><input type="radio" value="esc" name="mode" checked> Escaped string</label>
        <button id="start">Frobnicate</button>
    </div>
    <textarea id="result" rows="6" readonly></textarea>
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
