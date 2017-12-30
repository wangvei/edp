# EDP

## Introduction
Electron density plotter is a tiny tool for generating electron density plots from VASP output.

![CO orbitals generated using EDP](https://raw.githubusercontent.com/ifilot/edp/master/examples/CO_orbitals.jpg)

Figure: Four molecular orbitals of CO as generated by EDP.

## Compilation
EDP depends on a couple of libraries, which are normally directly available by your favorite package manager.
* Boost
* GLM
* Cairo
* TCLAP

Compilation is done using CMake
```
mkdir build
cd build
cmake ../src
make -j5
```

## Usage
A short tutorial on using the program is provided in this [blog post](http://www.ivofilot.nl/posts/view/27/Visualising+the+electron+density+of+the+binding+orbitals+of+the+CO+molecule+using+VASP).

## References

Color schemes have been taken from the following sources

* [Color brewer 2.0](http://colorbrewer2.org)
* [Colorpicker for data (tristen.ca)](http://tristen.ca/hcl-picker/#/hlc/6/1.05/CAF270/453B52)
* [Chroma.js Color Scale Helper](http://gka.github.io/palettes)
