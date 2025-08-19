+++
title = 'Routh-Hourwitz Criterion'
date = 2025-04-08T15:46:03+02:00
tags = ["routh","calculator","tool","math"]
category = ["tool"]
custom_js = ["routh.js"]
+++

A simple [Routh-Hourwitz criterion][crit] visual calculator.

<!--more-->

## Calculator

<noscript>
Javascript support is required by this tool
</noscript>

Enter the characteristic equation below.

<p style="display: flex; gap: 0.4em; flex: 1;">
    <label for="poly" style="white-space: nowrap;">P(s) = </label>
    <input type="text" id="poly" placeholder="s^2 + ks + 1" style="flex: 1;">
</p>

<div style="display: flex;justify-content: center;">
<button id="start">Calculate</button>
</div>

<div id="result"></div>

<style>
#result {
  width: max-content;
  margin: 2rem auto;
  max-width: 100%;
  overflow-x: auto;
  text-align: center;
}
#result table {
  margin-bottom: 1em;
}
</style>

[crit]: https://en.wikipedia.org/wiki/Routh%E2%80%93Hurwitz_stability_criterion
