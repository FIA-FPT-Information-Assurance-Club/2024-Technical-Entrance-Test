# [FORENSIC] FRS101

---

**Author**: `Evil Duck`

**Difficulty**: `Easy`

**Flag**: `FIA{D0_y0u_r34lly_L1ke_M3t4-Scr4mbl3_puzzl3?42319e79331c50cc296b}`

### Description

> Do you like scramble ? I love it so much
> 

### Objective

> Be able to find the metadata, doing some stegano stuff
> 

---

# Solution

## Information Gathering

- First we have an image file that looks like it's completely messed up

<p align="center">
  <img src="https://github.com/P5ySm1th/CTF/assets/100250271/06c58a9b-5cd4-4c7f-8434-9449f4962f80">
</p>

- After knowing this was a stegno challenge, let's gather more information about this picture via their metadata

- First and foremost, using `exiftool` and getting some information about the file

<p align="center">
  <img src="https://github.com/P5ySm1th/CTF/assets/100250271/c497ba42-93a8-4b98-a601-d1cee7b7a0e6">
</p>

- So from the result from `exiftool`, we can clearly see some metadata information from its. Look closer at the `Comment` section we can retrive some information from the author. But what it's used for, we don't know right now

## Solver

- It's very intuitive, how can we restore the photo to its original image. There are two ways this can be done:

    + Can be used by hand (but it is very time consuming)
    + So we will choose the second way, which is to use the tools available online to solve the problem

- Searching for tool, i mean, `github` is a good play to start for searching for tools.

<p align="center">
  <img src="https://github.com/P5ySm1th/CTF/assets/100250271/62623676-b4f7-4930-900a-28a9db48c0d4">
</p>

- So we will use this tool `Gaps` (you can find it [here](https://github.com/nemanja-m/gaps)). So basically, it is a genetic algorithm based solver for jigsaw puzzles with piece size auto-detection.

- Install it on your machine and run the solver. This would take a little bit of time

<p align="center">
  <img src="https://github.com/P5ySm1th/CTF/assets/100250271/4d394746-0294-45b9-89e4-0d5958d50f20">
</p>

- And now we can be able to see the result :D

<p align="center">
  <img src="https://github.com/P5ySm1th/CTF/assets/100250271/78a07a76-ee6e-4384-af87-92a61737579b">
</p>

- Let's take a look at the `pastebin`, it was secured by `password`

<p align="center">
  <img src="https://github.com/P5ySm1th/CTF/assets/100250271/93ed71a6-6629-4e74-b7ab-2ef1e674374a">
</p>

- Remember about the `Comment` in metadata, just input that in the `password` section, and we got the flag

<p align="center">
  <img src="https://github.com/P5ySm1th/CTF/assets/100250271/c196ac8e-68ac-4e6e-91c2-98692acc7c78">
</p>

P/s: I just wondered why people cannot solve this easy challenge :D