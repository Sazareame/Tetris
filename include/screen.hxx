#ifndef SCREEN_HXX_
#define SCREEN_HXX_

#include <array>
#include <bitset>
#include "macros.hxx"


class Screen{
private:
int height;
int width;
std::array<std::bitset<SCREEN_WIDTH>, SCREEN_HEIGHT> status;
// void get_window_size(int* height, int* width);
// bool screen_should_close(int height, int width);

public:
Screen(int _height, int _width): height(_height), width(_width){}
void flush();
void show();
};


#endif