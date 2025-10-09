+++
title = 'Routh-Hurwitz criterion calculator'
date = 2025-04-08T15:46:03+02:00
tags = ["routh","calculator","tool","math"]
category = ["tool"]
custom_js = ["routh.js"]
+++

A simple [Routh-Hurwitz criterion][crit] visual calculator.

<!--more-->

## Online calculator

<noscript>
Javascript support is required by this tool!
</noscript>

Enter the characteristic equation below as a list of coefficients.

<p style="display: flex; gap: 0.4em; flex: 1;">
    <label for="poly" style="white-space: nowrap;">P(s) = </label>
    <input type="text" id="poly" placeholder="1, -2, 3" style="flex: 1;">
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
