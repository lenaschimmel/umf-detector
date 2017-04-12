# UMF detector library
## Fork Info

_Forked from [this repo](https://github.com/szist/umf-detector) to add some features and general experimentation. See [the (outdated) project website](http://www.fit.vutbr.cz/research/groups/graph/MF/) for more explanation._

Current enhancements in this fork:

* Runtime-selection of an input module (OpenCV or Firewire) instead of compilation flag (see #1 )
* Runtime-configuration of the detector (greyscale or RGB) instead of compilation flag  (see #1 )
* Runtime-selection of graphical debug output  (see #2 )
* Better graphical debug output  (see #2 )

Planned enhancements:

* Allow runtime-selection of detector flags in a similar way as I added it for graphical debug output
* Display the current detector flags
* Fix missing parts for proper RGB detection
* Code cleanup
    * Make better use of vector and matrix classes in OpenCV and Eigen3
    * General update to C++11

## Referencing
In case you end up using our source code in research, please add a reference to one of our relevant publications:

### Binary UMF detection

I. Szentandrasi, M. Zacharias, J. Havel, A. Herout, M. Dubska, and R. Kajan. Uniform Marker
Fields: Camera localization by orientable De Bruijn tori. In ISMAR 2012, 2012

### Grayscale UMF detection

Adam Herout, Istvan Szentandrasi, Michal Zacharias, Marketa Dubska, and Rudolf Kajan.
Five shades of grey for fast and reliable camera pose estimation. In Proceedings of CVPR,
pages 1384–1390. IEEE Computer Society, 2013

### Unity plugin or Chromakeying UMF

I. Szentandrasi, M. Dubska, M. Zacharias, and A. Herout. Poor man’s virtual camera:
Real-time simultaneous matting and camera pose estimation. IEEE Computer Graphics and
Applications, 2016

### Compilation - linux

Dependencies
- argtable2
- opencv [optional | recommended]
- libdc1394-2 [optional] - firewire support
- Halide [optional] - optimized code

Included
- Eigen3
- glm

```bash
$ touch .depend
$ make depend
$ make all
```

To generate halide 
```bash
$ cd ext/halide
$ export HALIDE_PATH=/your/path/to/halide
$ make all
```

This generates an object archive for linux (you should add the USE_NATIVE in defines.h, and add the ext/lib/native_x.a to Makefile) and assembly files for android build.

### Compilation - windows


Dependencies
- Visual Studio 2013
- opencv
- Halide
- argtable2
- environment variables (see vsproj/README.txt)

Open solution: vsproj/UMF/UMF.sln
This should generate the native libraries with Halide and a .dll

### Related Projects

* [UMF generator server](https://github.com/szist/umf-generator-server)
* UMF generator client ([original](https://github.com/szist/umf-generator-client) / [my fork](https://github.com/lenaschimmel/umf-generator-client) )
* [UMF unity plugin](https://github.com/szist/umf-unity)
