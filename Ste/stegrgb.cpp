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
        data_.push_back(d[i]);
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
       for_hash.append(for_hash);
       FindBlockAndHideMessage(for_hash, tmp, shift);       
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
    int pos = 3;

    for (int i = row; i < row + 8; i++)
    {
        for (int j = col; j < col + 8*3; j++)
        {
          if((shift/2 - pos) * 2 < 0)
          {
              letter = letter | ((data_[width_ * i + j] & mask) << (-((shift/2 - pos) * 2)));
          }
          else
          {
              letter = letter | ((data_[width_ * i + j] & mask) >> ((shift/2 - pos) * 2));
          }
          pos--;
          if(pos == -1)
          {
                pos = 3;
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
       for_hash.append(for_hash);
       final.append(FindBlockAndReturnMessage(for_hash, shift));
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

void Rgb::CalculateHistogram()
{
    for(int i = 0; i < height_ * width_ * components_;)
    {
        int lum = (0.299 * data_[i++] + 0.587 * data_[i++] + 0.114 * data_[i++]);
        if(lum > 254){lum = 254;}
        if(lum < 0){lum = 0;}
        lum_pixels.push_back(lum);
        histogram[lum]++;
    }
}
void Rgb::WriteHistogramToFile(const char* filename, Format format)
{
    FILE* file = fopen(filename, "w");
    if(format == NUMBER)
    {
        for(int i = 0; i < 255; i++)
        {
            fprintf(file, "%d\n", histogram[i]);
        }
    }
    if(format == GRAPHIC)
    {
        for(int i = 0; i < 255; i++)
        {
            int cur = histogram[i];
            while(cur > -1)
            {
                fprintf(file, "%c", '*');
                cur--;
            }
            fprintf(file, "%c", '\n');
        }
    }
    fclose(file);
}
int Rgb::FindBlockInHistogram(MaxVal point, int difference)
{
    int g = difference;
    bool flag1 = false;
    bool flag2 = false;
    bool flag3 = false;
    bool flag4 = false;
    struct MaxVal lv,pv,ln,pn;
    for(int y = 0; y < 100; y++)
    {
        if(point.row + y > height_ || point.row - y < 0){ break;}
        for(int x = 1; x < 100; x++)
        {
            if(abs(lum_pixels[(point.row + y) * width_ + point.col + x] - lum_pixels[point.row * width_ + point.col]) < g)
            {pn.col = point.col + x; pn.row = point.row + y; flag1 = true;}
            else{if(flag1 == true && flag2 == true && flag3 == true && flag4 == true && ln.row != lv.row) break;}
            if(abs(lum_pixels[(point.row + y) * width_ + point.col - x] - lum_pixels[point.row * width_ + point.col]) < g)
            {ln.col = point.col - x; ln.row = point.row + y; flag2 = true;}
            else{if(flag1 == true && flag2 == true && flag3 == true && flag4 == true && ln.row != lv.row) break;}

            if(abs(lum_pixels[(point.row - y) * width_  + point.col + x] - lum_pixels[point.row * width_ + point.col]) < g)
            {pv.col = point.col + x  ; pv.row = point.row - y; flag3 = true;}
            else{if(flag1 == true && flag2 == true && flag3 == true && flag4 == true && ln.row != lv.row) goto l;}
            if(abs(lum_pixels[(point.row - y) * width_  + point.col - x] - lum_pixels[point.row * width_ + point.col]) < g)
            {lv.col = point.col - x  ; lv.row = point.row - y; flag4 = true;}
            else{if(flag1 == true && flag2 == true && flag3 == true && flag4 == true && ln.row != lv.row) goto l;}
        }
    }
    l:;
    (ln.row < pn.row)? pn.row = ln.row: ln.row = pn.row;

    (ln.col < lv.col)? lv.col = ln.col: ln.col = lv.col;
    (pn.col < pv.col)? pv.col = pn.col: pn.col = pv.col;
    (lv.col < pv.col)? pv.col = pn.col: pn.col = pv.col;

    (lv.col < ln.col)? ln.col = lv.col: lv.col = ln.col;
    HighlightBlock(ln, lv, pn, pv);
    return 0;
}
void Rgb::HighlightBlock(MaxVal ln, MaxVal lv, MaxVal pn, MaxVal pv)
{
    for(int i = lv.col * components_; i < pv.col * components_; i+=3)
    {
        data_[lv.row * width_ * components_ + i] = 255;
        data_[lv.row * width_ * components_ + i + 1] = 255;
        data_[lv.row * width_ * components_ + i + 2] = 255;

        data_[ln.row * width_ * components_ + i] = 255;
        data_[ln.row * width_ * components_+ i + 1] = 255;
        data_[ln.row * width_ * components_+ i + 2] = 255;
    }
    for(int i = lv.row; i < ln.row; i++)
    {
        data_[i * width_ * components_ + ln.col * components_] = 255;
        data_[i * width_ * components_ + ln.col * components_ + 1] = 255;
        data_[i * width_ * components_ + ln.col * components_ + 2] = 255;

        data_[i * width_ * components_ + pn.col * components_] = 255;
        data_[i * width_ * components_ + pn.col * components_ + 1] = 255;
        data_[i * width_ * components_ + pn.col * components_ + 2] = 255;
    }
}



