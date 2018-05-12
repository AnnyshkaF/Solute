#ifndef STEGRGB_H
#define STEGRGB_H

#include "md5/md5wrapper.h"
#include "rgb_structure.h"
#include <iostream>
#include <math.h>
#include <string>
#include <vector>

struct max_val
{
    int val;
    int col;
    int row;
};

class RGB
{
private:
    int height;
    int width;
    int comp;
public:
    std::vector<RGBQUAD> rgb;

    RGB(int height, int width, int comp);
    ~RGB();
    int GetHeight();
    int GetWidth();

    void IntoRGB(uint8_t* d);
    void OutRGB(uint8_t* d);


    void CodeMessageInString(std::string s, int row, int col);

    void CodeMessage(std::string s, int row, int col, int mask);
    void FindBlockAndHideMessage(std::string for_hash, std::string to_hide, int mask);

    std::string GetMessage(int max_len, int row, int col, int mask);
    std::string FindBlockAndReturnMessage(std::string for_hash, int mask);


    std::string CalculateHash(std::string str);
    int GetIntFromHash(std::string s);
    int FirstIntFromHash(std::string s);

    void CalculateHistogram();
    int FindBlockInHistogram(std::vector<int> mas_lum, max_val point);
    void HighlightBlock(max_val ln, max_val lv, max_val pn, max_val pv);
    void WriteHistogramToFile(int* a);
};

#endif

