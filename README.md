# pgm
> Simple tests on PGM based image processing

## Objectives

* write a program capable of read, write and generate simple pgm images
* write fuctions capable of manipulating these images and obtain data
  * noise reduction
  * geometric description of circles

### First stage

  - [x] generate a noisy image of a circle
    - [x] draw a circle by giving its parameters
    - [x] apply noise filter
  - [x] generate and remove grayscale noise
    - [x] normalization
    - [x] binarization
  - [ ] obtain multiple circle geometry
    - [ ] absolute position of center
    - [ ] relative positioning

## Results

Small image (50x50) with extent noise in proportion to the circle

![Noise generated](gen_noise.png)
![Removed noise](removed_noise.png)

> Border loss

Bigger images usually require more than a simple rand() per pixel as noise
algorithm. A more natural noise would be best described in parameters of different orders
of magnitude as seem from further algorithms.
