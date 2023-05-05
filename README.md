# TotoCompression

1. [Introduction](#intro)
2. [Technologies](#technologies)
3. [Features](#features)
4. [Program usage](#usage)
5. [Contributor](#contributor)

<a name="intro"></a>

## Introduction

TotoCompression is a tool I named after a french nickname that can be formed from my first name (Thomas -> Toto). This tool was done in the framework of the [Visual Media Compression course](https://www.ulb.be/fr/programme/info-h516) at the [Université Libre de Bruxelles](https://www.ulb.be). The tasks that were to be done are available in the "tasks.pdf" file, at the root of this repository.

<a name="technologies"></a>

## Technologies 

The technologies used for this project are C++ with OpenCV library to manipulate the images. To automate the build, I used CMake.

I wanted to keep the project as simple as possible 

<a name="features"></a>

## Features

For now, the program can read images and supports the following features :

- Reading an image and applying DCT to it.
- Reading an image and applying inverse DCT to it.

Note that the program supports both grayscale images and coloured images without any problem.

<a name="usage"></a>

## Program usage

To compress an image use the following command :

```
TotoCompression --compress {path} [-o {output_path}]
```

To decompress an image use the following command :

```
TotoCompression --decompress {path} [-o {output_path}]
```


<a name="contributor"></a>

## Contributor

The only contributor to this repository is ... myself, since it was a solo school project :

Dudziak Thomas : https://dudziak-thomas.be/


