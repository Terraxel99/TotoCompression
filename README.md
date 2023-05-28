# TotoCompression

1. [Introduction](#intro)
2. [Technologies](#technologies)
3. [Features](#features)
4. [Installation](#installation)
5. [Program usage](#usage)
6. [Enhancements](#enchancements)
7. [Contributor](#contributor)

<a name="intro"></a>

## Introduction

TotoCompression is a tool I named after a french nickname that can be formed from my first name (Thomas -> Toto). This tool was done in the framework of the [Visual Media Compression course](https://www.ulb.be/fr/programme/info-h516) at the [Université Libre de Bruxelles](https://www.ulb.be). The tasks that were to be done are available in the "tasks.pdf" file, at the root of this repository.

The tool aims to have a simple image and video compression utility that puts in practice the concepts seen during the course.

<a name="technologies"></a>

## Technologies 

The technologies used for this project are C++ with OpenCV library to manipulate the images. To automate the build, I used CMake.

I wanted to keep the project as simple as possible and easy to build on several platforms. This is why I choose CMake.

<a name="features"></a>

## Features

For now, the program can read images and supports the following features :

- Reading an image, applying DCT and quantization to it, doing the reverse operation and display the PSNR between the original and reconstructed image.
- Reading a video, applying basic I-frame compression on each frame, doing the reverse operation and display the mean PSNR between the original and reconstructed videos.
- Reading a video, applying basic D-frame compression for a variable group size, doing the reverse operation and display the mean PSNR between the original and reconstructed videos.

Note that the program supports both grayscale images and coloured images without any problem. Progressbar is available for image but is not available (yet) for videos, where you can expect more latency while processing.

<a name="installation"></a>

## Installation
To build the project, you need to have OpenCV and CMake installed on your machine.

First, clone the project and navigate into it :

```
git clone https://github.com/Terraxel99/TotoCompression.
cd TotoCompression
```

Build the project using CMake :

```
cmake --fresh .
```

That's it ! Navigate into the build folder and refer to the [Program usage](#usage) section :

```
cd build/
```

<a name="usage"></a>

## Program usage

To launch a test on images and retrieve the PSNR values, please run :

```
TotoCompression --image
```

To launch a video test with the I-frame encoding technique, please run :

```
TotoCompression --Ivideo
```

To launch a video test with the D-frame encoding technique, please run :

```
TotoCompression --Dvideo
```

<a name="enchancements"></a>

## Enhancements

The program has been created in such a way that it it possible to change which files are processed by just adding a call to the right function in the main file.

Note that some #define constants can be changed in order to change the behaviour of the program.

<a name="contributor"></a>

## Contributor

The only contributor to this repository is ... myself, since it was a solo school project :

Dudziak Thomas : https://dudziak-thomas.be/


