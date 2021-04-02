# Trojan Map

This is the final project of EE599 (Computer Principles) in Spring 2021 at University of Southern California.

Author: Haoxin Ma, Ziyou Geng  
Instructor: Arash Saifhashemi 

## Overview  

  ### Data structure  

  ```c++
  class Node {
   public:
    string id;                 // A unique id assigned to each point
    double lat;                // Latitude
    double lon;                // Longitude
    string name;               // Name of the location
    vector<string> neighbors;  // List of the ids of all neighbor points
  };

  class TrojanMap {
   public:
    map<string, Node> data;    // A map of ids to Nodes
  ```

## Source Code Dependencies 

- ### gcc

  ```shell
  sudo apt update
  sudo apt install build-essential
  ```

- ### CMake

  ```shell
  sudo apt update
  sudo apt install cmake pkg-config
  ```

- ### Bazel

  See https://docs.bazel.build/versions/4.0.0/install-ubuntu.html#install-on-ubuntu

- ### git

  ```shell
  sudo apt update
  sudo apt install git
  ```

- ### OpenCV

  ```shell
  mkdir ./opencv
  git clone https://github.com/opencv/opencv.git
  sudo apt update
  sudo apt install libgtk2.0-dev libcanberra-gtk-module libcanberra-gtk3-module
  cd opencv/
  mkdir build install
  cd build/
  cmake -D CMAKE_INSTALL_PREFIX= ../install\
   -D BUILD_LIST=core,highgui,imgcodecs,imgproc,videoio\
   -D WITH_TBB=ON -D WITH_OPENMP=ON -D WITH_IPP=ON\
   -D CMAKE_BUILD_TYPE=RELEASE -D BUILD_EXAMPLES=OFF\
   -D WITH_NVCUVID=ON\
   -D WITH_CUDA=ON\
   -D BUILD_DOCS=OFF\
   -D BUILD_PERF_TESTS=OFF\
   -D BUILD_TESTS=OFF\
   -D WITH_CSTRIPES=ON\
   -D WITH_OPENCL=ON ..
  make install
  ```

- ### Qt

  See https://www.qt.io/download


## Directory Description

`./bazel-*`			GoogleTest output files  
`./opencv`			OpenCV source files  
`./qt`				Qt source files  
`./release`			Released executables  
`./src`				C++ source files  
`./tests`			GoogleTest files  
`./ncurses.BUILD`	ncurses build file  
`./opencv.BUILD`	OpenCV build file  
`./WORKSPACE`		bazel build file  

## Reference

Project Guidance: https://github.com/hongshuochen/2021Spring_TrojanMap/blob/master/README.md