#include "../includes/image.h"



Image::Image(std::string image_path, std::string wordmap_path, Graph* graph) {
  image_ = cs225::PNG();
  worldmap_ = cs225::PNG();
  image_.readFromFile(image_path);
  worldmap_.readFromFile(wordmap_path);
  data_ = graph->get_data();
  graph_ = graph;
}




void Image::draw_circle(int x, int y, int hue){
  //drawing a 9x9 square centered at pixel x,y (if in bounds)
  draw_circle(x, y, 4, hue);
}
void Image::draw_circle(int x, int y, int radius, int hue){
  //drawing a 9x9 square centered at pixel x,y (if in bounds)
  for(int i = x-radius; i <= x+radius; i++){
    for(int j = y-radius; j <= y+radius; j++){
      if(inbounds(i,j)){
        cs225::HSLAPixel& pixel = image_.getPixel(i,j);
        pixel.h = hue;
        pixel.s = 1;
        pixel.l = 0.5;  
      }
    }
  }

}

void Image::SaveImg(std::string path) {
    image_.writeToFile(path);
}

bool Image::inbounds(unsigned int i,unsigned int j){
  //returns whether a point i,j is in bounds of the image
  return i >= 0 && i < image_.width() && j >= 0 && j < image_.height();
}


void Image::draw_line_steep(std::vector<int> from, std::vector<int> to, int width, int hue) {
  int x0 = from[0];
  int y0 = from[1];
  int x1 = to[0];
  int y1 = to[1];
  int dx = x1 - x0;
  int dy = y1 - y0;
  int factor = 1;

  if (dx < 0) {
    factor = -1;
    dx = -dx;
  }

  int delta = (2 * dx) - dy;
  int x = x0;

  for (int y = y0; y <= y1; y++) {
    draw_circle(x, y, width/2, hue);
    if (delta > 0) {
      x += factor;
      delta += 2 * (dx - dy);
    } 
    else {
      delta += 2 * dx;
    }
  }
}

void Image::draw_line(std::vector<int> from, std::vector<int> to, int hue) {
  draw_line(from, to, 2, hue);
}
void Image::draw_line(std::string from, std::string to, int hue) {
  draw_line(from, to, 2, hue);
}

void Image::draw_line(std::vector<int> from, std::vector<int> to, int width, int hue){
  if(from.at(0) == to.at(0) && from.at(1) == to.at(1)){
    return;
  }
  int x0 = from[0];
  int y0 = from[1];
  int x1 = to[0];
  int y1 = to[1];

  if (std::abs(y1 - y0) < std::abs(x1 - x0)) {
    if (x0 > x1) {
      draw_line_flat(to, from, width, hue);
    }
    else {
      draw_line_flat(from, to, width, hue);
    }
  }
  else {
    if (y0 > y1) {
      draw_line_steep(to, from, width, hue);
    }
    else {
      draw_line_steep(from, to, width, hue);
    }
  }
  
}

void Image::draw_line_flat(std::vector<int> from, std::vector<int> to, int width, int hue){
  int x0 = from.at(0);
  int y0 = from.at(1);
  int x1 = to.at(0);
  int y1 = to.at(1);
  int dx = x1 - x0;
  int dy = y1 - y0;
  int factor = 1;
  if (dy < 0) {
      factor = -1;
      dy = -dy;
  }
  int delta = (2 * dy) - dx;
  int y = y0;
  for (int x = x0; x <= x1; x++){
    draw_circle(x,y,width/2, hue);
    if (delta > 0){
        y = y + factor;
        delta += (2 * (dy - dx));
    }
    else{
        delta += 2*dy;
    }
  }  
}

PNG Image::get_inverted(HSLAPixel pixel){
  return PNG();
}

std::vector<int> Image::coord_to_pixel(std::vector<double> input) {
    int image_size_factor = 4;
    double x = (input.at(1) + 180) * ((double)worldmap_.width() / (double)360);
    double latRad = input.at(0)  * 3.141592653589 / (double)180;
    double mercN = std::log(std::tan((3.141592653589 / (double)4) + (latRad / 2)));
    double y = (worldmap_.height() / (double)2) - (worldmap_.width() * mercN / (double) ((double) 2 * 3.141592653589));
    double x_corrected = x+8;
    double y_corrected = y+4;
    double x_offset = 1146;
    double y_offset = 1862;
    double x_new = image_size_factor*(x_corrected - x_offset);
    double y_new = image_size_factor*(y_corrected - y_offset);
    std::vector<int> ret;
    ret.push_back((int)x_new);
    ret.push_back((int)y_new);
    return ret;
}
       
std::vector<double> Image::pixel_to_coord(std::vector<int>input){
  std::vector<double> to_return; //store the vector of doubles to return
  return to_return; //return the vector of coordinates
}

void Image::plot_stations(int radius, int hue) {
  
  for (int i = 0; i < (int) data_->getCodes().size(); i++) {
    std::vector<double> cords;
    cords.push_back(data_->getLat(i));
    cords.push_back(data_->getLong(i));
    std::vector<int> pixel = coord_to_pixel(cords);
    draw_circle(pixel[0], pixel[1], radius, hue);
  }
}

void Image::plot_paths(int width, int hue) {
  std::vector<std::vector<std::string>> edges = graph_->GetEdges();
  for (int i = 0; i < (int) edges.size(); i++) {
    std::vector<std::string> edge = edges[i];
    std::string stn1 = edge[0];
    std::string stn2 = edge[1];
    draw_line(stn1, stn2, width, hue);
  }
}

void Image::plot_paths(std::vector<std::vector<std::string>> paths, int width, int hue) {
  for (int i = 0; i < (int) paths.size(); i++) {
    std::vector<std::string> edge = paths[i];
    std::string stn1 = edge[0];
    std::string stn2 = edge[1];
    draw_line(stn1, stn2, width, hue);
  }
}

void Image::draw_line(std::string stn1, std::string stn2, int width, int hue){
  double lat0 = data_->getLat(stn1);
  double long0 = data_->getLong(stn1);
  double lat1 = data_->getLat(stn2);
  double long1 = data_->getLong(stn2);
  std::vector<double> coord0;
  std::vector<double> coord1;
  coord0.push_back(lat0);
  coord0.push_back(long0);
  coord1.push_back(lat1);
  coord1.push_back(long1);
  std::vector<int> pixels0 = coord_to_pixel(coord0);
  std::vector<int> pixels1 = coord_to_pixel(coord1);
  draw_line(pixels0,pixels1,width, hue);
}


 void Image::PlotTrains(std::vector<Train> trains) {
    for (int i = 0; i < (int) trains.size(); i++) {
      std::vector<std::vector<std::string>> edges = trains[i].getEdges();
      for (int j = 0; j < (int) edges.size(); j++) {
        std::string stn1 = edges[j][0];
        std::string stn2 = edges[j][1];
        int hue = rand() % 360;
        draw_line(stn1, stn2, hue);
      }
    }
 }