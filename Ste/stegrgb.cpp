#include "stegrgb.h"

Rgb::Rgb(int height, int width, int comp)
{
    this->height_ = height;
    this->width_ = width;
    this->components_ = comp;
}
Rgb::~Rgb(){}

int Rgb::GetHeight()
{
    return height_;
}
int Rgb::GetWidth()
{
    return width_;
}

void Rgb::IntoRGB(uint8_t* d)
{
    for (int i = 0; i < height_ * width_ * components_; i++)
    {
        data_[i] = d[i];
    }
}

void Rgb::OutRGB(uint8_t* d)
{
    for (int i = 0; i < height_ * width_ * components_; i++)
    {
        d[i] = data_[i];
    }
}

void Rgb::HideMessage(std::string s, int row, int col, int shift)
{
    if ((row > height_ - 8) || (col > width_ - 8))
    {
        return;
    }
    int k = 0;
    int color = 0;
    int pos = 0;

    uint8_t pattern = 0;
    uint8_t mask = 3 << shift;

    for (int i = row; i < row + 8; i++)
    {
        for (int j = col; j < col + 8 * components_; j++)
        {
            if (k < s.length())
            {
                pattern = (s[k] >> (3 - pos) * 2) & 0x3;
                data_[width_ * i + j] = data_[width_ * i + j] & ~mask | (pattern << shift) & mask;
                pos++;
                if(pos == 4)
                {
                   pos = pos % 4;
                   k++;
                }
            }
        }
    }  
}
void Rgb::FindBlockAndHideMessage(std::string for_hash, std::string to_hide, int shift)
{
    std::string hash = CalculateHash(for_hash);
    int x = 0;
    int y = 0;

    while(x > width_ - 8 || x < 0 || x == 0)
    {
        hash = CalculateHash(hash);
        x = GetIntFromHash(hash);
    }
    while(y > height_ - 8 || y == 0 || y < 0)
    {
        hash = CalculateHash(hash);
        y = GetIntFromHash(hash);
    }
    HideMessage(to_hide, x, y, shift);
}
int Rgb::HideText(std::string for_hash, std::string text, int shift)
{
    std::string tmp;
    int key = 0;
    for(size_t i = 0; i < text.length(); i+=48)
    {
       tmp = &text[i];
       tmp.resize(48);
       FindBlockAndHideMessage(for_hash, tmp, shift);
       for_hash.append(for_hash);
       tmp = {0};
       key++;
    }
    return key;
}

std::string Rgb::GetMessage(int max_len, int row, int col, int shift)
{
    std::string final;
    uint8_t letter = 0;
    uint8_t mask = 3 << shift;
    int pos = 0;

    for (int i = row; i < row + 8; i++)
    {
        for (int j = col; j < col + 8*3; j++)
        {
          letter = letter | ((data_[width_ * i + j] & mask) >> (pos * 2));
          pos++;
          if(pos == 4)
          {
                pos = pos % 4;
                final += letter;
                letter = 0;
           }
        }
    }
    return final;
}
std::string Rgb::FindBlockAndReturnMessage(std::string for_hash, int shift)
{
    std::string hash = CalculateHash(for_hash);
    int x = 0;
    int y = 0;

    while(x > width_ - 8 || x < 0 || x == 0)
    {
        hash = CalculateHash(hash);
        x = GetIntFromHash(hash);
    }
    while(y > height_ - 8 || y < 0 || y == 0)
    {
        hash = CalculateHash(hash);
        y = GetIntFromHash(hash);
    }
    return GetMessage(for_hash.length() * 3, x, y, shift);
}
std::string Rgb::GetText(std::string for_hash, int shift, int key)
{
    std::string final;
    for(size_t i = key; i > 0; i--)
    {
       final.append(FindBlockAndReturnMessage(for_hash, shift));
       for_hash.append(for_hash);
       key++;
    }
    return final;
}

std::string Rgb::CalculateHash(std::string str)
{
    md5wrapper md5;
    return md5.getHashFromString(str);
}

int Rgb::GetIntFromHash(std::string s)
{
    int x = FirstIntFromHash(s);
    if ((x < height_) && (x < width_))
    {
        return x;
    }
    else
    {
        return -1;
    }
}

int Rgb::FirstIntFromHash(std::string s)
{
    int a = 0;
    size_t i = 0;
    std::vector<char> v;
    while (i < s.length())
    {
        if ((s[i] >= '0') && (s[i] <= '9'))
        {
            v.push_back(s[i]);
            a++;
        }
        else if (a > 0)
        {
            break;
        }
        i++;
    }
    v.reserve(v.size());

    a = 0;
    int j = v.size() - 1;
    for (size_t i = 0; i < v.size(); i++)
    {
        a += (v[i] - '0') * pow(10, j);
        j--;
    }
    return a;
}

//void Rgb::CalculateHistogram()
//{
//    std::vector<int> arr_lum;       //яркость каждого пикселя отдельно
//    int lum_col_height[255] = {0};  //гистограмма яркости
//    MaxVal max_lum{0,0,0};
//    int tmp = 0;
//    MaxVal m = dod(lum_col_height, arr_lum);
//    MaxVal m1 = dod(lum_col_height, arr_lum);
//    MaxVal m2 = dod(lum_col_height, arr_lum);
//    int tmpf = 0;
//    for(int i = 0; i < height * width; i++)
//    {
//        int lum = (0.299 * rgb[i].rgbRed + 0.587 * rgb[i].rgbGreen + 0.114 * rgb[i].rgbBlue);
//        if(lum > 255){lum = 255;}
//        if(lum < 0){lum = 0;}
//        arr_lum.push_back(lum);

//        lum_col_height[lum]++;

//            if(max_lum.val < lum_col_height[lum])
//            {
//                max_lum.val = lum_col_height[lum];
//                tmp = lum;
//                max_lum.col = i % width;
//                max_lum.row = i / width;
//            }
//    }
//    //dod(lum_col_height, arr_lum);
//     lum_col_height[tmp] = 0;    //порчу
//    max_val max_lum2{0,0,0};
//    for(int i = 0; i < height * width; i++)
//    {
//        int lum = (0.299 * rgb[i].rgbRed + 0.587 * rgb[i].rgbGreen + 0.114 * rgb[i].rgbBlue);
//        if(lum > 255){lum = 255;}
//        if(lum < 0){lum = 0;}
//        arr_lum.push_back(lum);

//        if(max_lum2.val < lum_col_height[lum])
//        {
//            max_lum2.val = lum_col_height[lum];
//            tmp = lum;
//            max_lum2.col = i % width;
//            max_lum2.row = i / width;
//        }
//    }
//    lum_col_height[tmp] = 0;    //порчу
//    max_val max_lum3{0,0,0};
//    for(int i = 0; i < height * width; i++)
//        {
//            int lum = (0.299 * rgb[i].rgbRed + 0.587 * rgb[i].rgbGreen + 0.114 * rgb[i].rgbBlue);
//            if(lum > 255){lum = 255;}
//            if(lum < 0){lum = 0;}
//            arr_lum.push_back(lum);

//            if(max_lum3.val < lum_col_height[lum])
//            {
//                max_lum3.val = lum_col_height[lum];
//                tmp = lum;
//                max_lum3.col = i % width;
//                max_lum3.row = i / width;
//            }
//    }
//    lum_col_height[tmp] = 0;    //порчу
//    max_val max_lum4{0,0,0};
//    for(int i = 0; i < height * width; i++)
//        {
//            int lum = (0.299 * rgb[i].rgbRed + 0.587 * rgb[i].rgbGreen + 0.114 * rgb[i].rgbBlue);
//            if(lum > 255){lum = 255;}
//            if(lum < 0){lum = 0;}
//            arr_lum.push_back(lum);

//            if(max_lum4.val < lum_col_height[lum])
//            {
//                max_lum4.val = lum_col_height[lum];
//                tmp = lum;
//                max_lum4.col = i % width;
//                max_lum4.row = i / width;
//            }
//    }
//     FindBlockInHistogram(arr_lum, max_lum);
//     FindBlockInHistogram(arr_lum, max_lum2);
//     FindBlockInHistogram(arr_lum, max_lum3);
//     FindBlockInHistogram(arr_lum, max_lum4);
//}
//bool flag = false;
//MaxVal Rgb::dod(int lum_col_height[], std::vector<int>& arr_lum)
//{
//    //std::vector<int> arr_lum;       //яркость каждого пикселя отдельно
//    //int lum_col_height[255] = {0};  //гистограмма яркости
//    MaxVal max_lum{0,0,0};
//    int tmp = 0;
//    int j = 0;
//    int lum = 0;
//    while(j < 5)
//    {
//        MaxVal max_lum{0,0,0};
//        for(int i = 0; i < height_ * width_; i++)
//        {
//           int lum = (0.299 * rgb_[i].Red + 0.587 * rgb_[i].Green + 0.114 * rgb_[i].Blue);
//            if(lum > 255){lum = 255;}
//            if(lum < 0){lum = 0;}
//            if(flag == false)
//            {
//                arr_lum.push_back(lum);

//                lum_col_height[lum]++;
//            }
//            if(max_lum.val < lum_col_height[lum])
//            {
//                max_lum.val = lum_col_height[lum];
//                tmp = lum;
//                max_lum.col = i % width_;
//                max_lum.row = i / width_;
//            }
//        }
//        FindBlockInHistogram(arr_lum, max_lum);
//        lum_col_height[tmp] = 0;    //порчу
//        if(flag == false){flag = true;}
//     return max_lum;

//     if(max_lum.row < 30|| max_lum.col < 30)
//     {continue;}
//     FindBlockInHistogram(arr_lum, max_lum);
//     j++;
//    }
//}
//     //WriteHistogramToFile(lum_col_height);
//int Rgb::FindBlockInHistogram(std::vector<int> arr_lum, MaxVal point)
//{
//    int g = 10;
//    struct MaxVal lv,pv,ln,pn;
//    for(int y = 0; y < 100; y++)
//    {
//        if(point.row + y > height_ || point.row - y < 0){ break;}
//        for(int x = 1; x < 100; x++)
//        {
////            if((point.row + y) * width + point.col + x < 0){ return -1;}
////            if((point.row + y) * width + point.row - x < 0){ return -1;}
////            if((point.row - y) * width + point.col + x < 0){ return -1;}
////            if((point.row - y) * width + point.col - x < 0){ return -1;}
////            if(((point.row + y) * width + point.col - x) > (width * height))
////            {return -1;}

//            if(abs(arr_lum[(point.row + y) * width_ + point.col + x]  - arr_lum[point.row * width_ + point.col]) < g)
//            {pn.col = point.col + x; pn.row = point.row + y;}
//            if(abs(arr_lum[(point.row + y) * width_ + point.row - x]  - arr_lum[point.row * width_ + point.col]) < g)
//            {ln.col = point.col - x; ln.row = point.row + y;}

//            if(abs(arr_lum[(point.row - y) * width_ + point.col + x]  - arr_lum[point.row * width_ + point.col]) < g)
//            {pv.col = point.col + x; pv.row = point.row - y;}
//            if(abs(arr_lum[(point.row - y) * width_ + point.col - x]  - arr_lum[point.row * width_ + point.col]) < g)
//            {lv.col = point.col - x; lv.row = point.row - y;}

//            (ln.row < pn.row)? pn.row = ln.row: ln.row = pn.row;
//            //(lv.row < pv.row)? pv.row = lv.row: lv.row = pv.row;
//            (ln.col < lv.col)? lv.col = ln.col: ln.col = lv.col;
//            (pn.col < pv.col)? pv.col = pn.col: pn.col = pv.col;

//        }
//    }
//    HighlightBlock(ln, lv, pn, pv);
//    return 0;
//}

//void Rgb::HighlightBlock(MaxVal ln, MaxVal lv, MaxVal pn, MaxVal pv)
//{
//    for(int i = lv.col; i < pv.col; i++)
//    {
//        rgb_[lv.row * width_ + i].Blue = 255;
//        rgb_[lv.row * width_ + i].Green = 255;
//        rgb_[lv.row * width_ + i].Red = 255;

//        rgb_[ln.row * width_ + i].Blue = 255;
//        rgb_[ln.row * width_ + i].Green = 255;
//        rgb_[ln.row * width_ + i].Red = 255;
//    }
//    for(int i = lv.row; i < ln.row; i++)
//    {
//        rgb_[i * width_ + ln.col].Blue = 255;
//        rgb_[i * width_ + ln.col].Green = 255;
//        rgb_[i * width_ + ln.col].Red = 255;

//        rgb_[i * width_ + pn.col].Blue = 255;
//        rgb_[i * width_ + pn.col].Green = 255;
//        rgb_[i * width_ + pn.col].Red = 255;
//    }
//}


