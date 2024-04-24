#ifndef SCREEN_HXX_
#define SCREEN_HXX_

#include "macros.hxx"
#include <cstdint>
#include <deque>


class Screen{
private:
// void get_window_size(int* height, int* width);
// bool screen_should_close(int height, int width);

public:
Screen() = default;
void flush();
void show(std::deque<uint16_t> const& status);
};


#endif