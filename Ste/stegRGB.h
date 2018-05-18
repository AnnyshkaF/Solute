#ifndef STEGRGB_H
#define STEGRGB_H

#include "md5/md5wrapper.h"
#include "rgb_structure.h"
#include <iostream>
#include <math.h>
#include <string>
#include <vector>

struct MaxVal
{
    int val;
    int col;
    int row;
};

class Rgb
{
private:
    int height_;
    int width_;
    int components_;

    void HideMessage(std::string s, int row, int col, int shift);
    void FindBlockAndHideMessage(std::string for_hash, std::string to_hide, int shift);

    std::string GetMessage(int max_len, int row, int col, int mask);
    std::string FindBlockAndReturnMessage(std::string for_hash, int mask);
public:
    std::vector<uint8_t> data_;

    Rgb(int height_, int width_, int comp);
    ~Rgb();
    int GetHeight();
    int GetWidth();

    void IntoRGB(uint8_t* d);
    void OutRGB(uint8_t* d);


    int HideText(std::string for_hash, std::string text, int shift);  
    std::string GetText(std::string for_hash, int shift, int key);

    std::string CalculateHash(std::string str);
    int GetIntFromHash(std::string s);
    int FirstIntFromHash(std::string s);

    void CalculateHistogram();
    int FindBlockInHistogram(std::vector<int> mas_lum, MaxVal point);
    void HighlightBlock(MaxVal ln, MaxVal lv, MaxVal pn, MaxVal pv);
    void WriteHistogramToFile(int* a);
    MaxVal dod(int arr_lum[], std::vector<int>& lum_col_height);
    //max_val FindHistMaximum(int* lum_col_height, std::vector<int> arr_lum);
};

#endif

