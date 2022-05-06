#pragma once

#ifndef IMAGE_H
#define IMAGE_H


#include <iostream>
#include "../cs225/HSLAPixel.h"
#include "../cs225/PNG.h"
#include "data.h"
#include "graph.h"
#include "train.h"
#include <vector>
#include <algorithm>
#include "cmath"
#include <random>

using namespace std;
using cs225::HSLAPixel;
using cs225::PNG;

 class Image: public PNG {
    public:
       Image(std::string image_path, std::string wordmap_path, Graph* graph);
       ~Image() = default;

       //////////////////PLOT STATIONS/////////////////
       void plot_stations(int radius, int hue);
       void plot_paths(int width, int hue);
       void plot_paths(std::vector<std::vector<std::string>> paths, int width, int hue);
       ////////////////////////////////////////////////

       ////////////////DRAWING COORDINATES/////////////
       void draw_circle(int x, int y, int hue);
       void draw_circle(int x, int y, int radius, int hue);
       void draw_line(std::string stn1, std::string stn2, int hue);
       void draw_line(std::vector<int> from, std::vector<int> to, int hue);
       void draw_line(std::string stn1, std::string stn2, int width, int hue);
       void draw_line(std::vector<int> from, std::vector<int> to, int width, int hue);
       PNG get_inverted(HSLAPixel pixel);
       std::vector<int> coord_to_pixel(std::vector<double>input);
       std::vector<double> pixel_to_coord(std::vector<int>input);
       

      ////////////HELPER FUNCTIONS//////////
       bool inbounds(unsigned int i,unsigned int j);
       cs225::PNG get_image();
       cs225::PNG get_worldmap();


       void SaveImg(std::string path);

      //plot all trains
       void PlotTrains(std::vector<Train> trains);

    private:
      void draw_line_steep(std::vector<int> from, std::vector<int> to, int width, int hue);
      void draw_line_flat(std::vector<int> from, std::vector<int> to, int width, int hue);
      
      cs225::PNG image_;
      cs225::PNG worldmap_;
      //given data object
      Data* data_;
      //given Graph object
      Graph* graph_;
 };


#endif