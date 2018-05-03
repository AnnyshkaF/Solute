# pragma once

# include <math.h>
# include <fstream>
# include <string>
# include "md5wrapper.h"
# include "rgb_structure.h"
# include <iostream>
# include <vector>
# include "JpegImage.h"

struct max_val
{
    int val;
    int col;
    int row;
};

class RGB
{
private:
	int Height;
	int Width;
	int Comp;
    std::vector<std::vector<bool>> sol;
public:
    std::vector<RGBQUAD> rgb;

    RGB(int height, int width, int comp);
    ~RGB();
	
    void into_RGB(uint8_t* d);
    void out_RGB(uint8_t* d);

    void code_xx00_0000(std::string s, int row, int col);
    void code_00xx_0000(std::string s, int row, int col);
    void code_0000_xx00(std::string s, int row, int col);
    int	find_block_and_hide(std::string for_hash, std::string to_hide);

    std::string get_mes_from_xx00_0000(int max_len, int row, int col);
    std::string get_mes_from_00xx_0000(int max_len, int row, int col);
    std::string get_mes_from_0000_xx00(int max_len, int row, int col);
    std::string find_block_and_return_mes(std::string for_hash, int secret_number);

    std::string get_hash(std::string str);
    int get_x(std::string s);
    int getint(std::string s);
	
    void calc_hist();
    int find_block_from_hist(int *a, std::vector<int> mas_lum, max_val point);
    void write_hist_to_file(int* a);
};

