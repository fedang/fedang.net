+++
title = 'Routh-Hurwitz Criterion'
date = 2025-04-08T15:46:03+02:00
draft = true
+++

A simple [Routh-Hourwitz criterion][crit] visual calculator.

<!--more-->

## Calculator

Enter the characteristic equation below.

<p style="display: flex; gap: 0.4em;">
    <label for="poly" style="white-space: nowrap;">P(s) = </label>
    <input type="text" id="poly" placeholder="s^2 + ks + 1" style="flex-grow: 1;">
    <script src="/js/routh.js"></script>
</p>


[crit]: https://en.wikipedia.org/wiki/Routh%E2%80%93Hurwitz_stability_criterion
