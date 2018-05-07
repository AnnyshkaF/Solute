#include "stegRGB.h"

#ifndef _WIN32

#include <openssl/md5.h>

#include <sstream>
#include <iomanip>
#include <stdio.h>

std::string md5wrapper::getHashFromString(std::string text)
{
    unsigned char* hash = MD5((const unsigned char *)text.c_str(), text.length(), NULL);

    std::stringstream out;
    out << std::hex;
    for (int i = 0; i < MD5_DIGEST_LENGTH; ++i)
    {
        out << std::setw(2) << std::setfill('0') << (int)hash[i];
    }
    return out.str();
}

md5wrapper::md5wrapper()
{
}

md5wrapper::~md5wrapper()
{
}

#endif

RGB::RGB(int height, int width, int comp)
{
    Height = height;
    Width = width;
    Comp = comp;
}
RGB::~RGB(){}

void RGB::into_RGB(uint8_t* d)
{
    int k = 0;
    int max_k = Height * Width * Comp;
    for (int i = 0; i < Height*Width; i++)
    {
        if (k < max_k)
        {
            RGBQUAD r;
            r.rgbBlue = d[k++];
            r.rgbGreen = d[k++];
            r.rgbRed = d[k++];
            rgb.push_back(r);
        }
    }
}
void RGB::out_RGB(uint8_t* d)
{
    int k = 0;
    int max_k = Height * Width * Comp;
    for (int i = 0; i < Height * Width; i++)
    {
        if (k < max_k)
        {
            d[k++] = rgb[i].rgbBlue ;
            d[k++] = rgb[i].rgbGreen;
            d[k++] = rgb[i].rgbRed;
        }
    }
}

void RGB::code_xx00_0000(std::string s, int row, int col)
{
    if ((row > Height - 8) || (col > Width - 8))
    {
        //std::cout << "Out of boundaries";
        return;
    }

    int mask = 63;	////63(10) = 0011 1111(2)
    size_t k = 0;
    char cur;
    int pos = 0, colour = 0;
    std::string finale;
    for (int i = row; i < row + 8; i++)
    {
        for (int j = col; j < col + 8; )
        {
            if (k < s.length())
            {
                int cur_val = s[k];
                pos = pos % 4;
                switch (pos)
                {
                case 0:	cur = (cur_val & 192); pos++; break;        //1100 0000
                case 1:	cur = (cur_val & 48) << 2; pos++; break;	//0011 0000
                case 2:	cur = (cur_val & 12) << 4; pos++; break;	//0000 1100
                case 3:	cur = (cur_val & 3) << 6; pos++; break;		//0000 0011
                }

                if (pos == 4)
                {
                    k++;
                }

                colour = colour % 3;
                switch (colour)
                {
                case 0: rgb[i * Width + j].rgbBlue = rgb[i * Width + j].rgbBlue & mask; rgb[i * Width + j].rgbBlue = rgb[i * Width + j].rgbBlue | cur; colour++; break;
                case 1: rgb[i * Width + j].rgbGreen = rgb[i * Width + j].rgbGreen & mask; rgb[i * Width + j].rgbGreen = rgb[i * Width + j].rgbGreen | cur; colour++; break;
                case 2: rgb[i * Width + j].rgbRed = rgb[i * Width + j].rgbRed & mask; rgb[i * Width + j].rgbRed = rgb[i * Width + j].rgbRed | cur; colour++; j++; break;
                }
                cur = 0;
            }
            else { return; }
        }
    }
}
void RGB::code_00xx_0000(std::string s, int row, int col)
{
    if ((row > Height - 8) || (col > Width - 8))
    {
        //std::cout << "Out of boundaries";
        return;
    }
    int mask = 207;	////207(10) = 1100 1111(2)
    size_t k = 0;
    char cur;
    int pos = 0, colour = 0;
    std::string finale;
    for (int i = row; i < row + 8; i++)
    {
        for (int j = col; j < col + 8; )
        {
            if (k < s.length())
            {
                int cur_val = s[k];
                pos = pos % 4;
                switch (pos)
                {
                case 0:	cur = (cur_val & 192) >> 2; pos++; break;	//1100 0000
                case 1:	cur = cur_val & 48; pos++; break;			//0011 0000
                case 2:	cur = (cur_val & 12) << 2; pos++; break;	//0000 1100
                case 3:	cur = (cur_val & 3) << 4; pos++; break;		//0000 0011
                }

                if (pos == 4)
                {
                    k++;
                }

                colour = colour % 3;
                switch (colour)
                {
                case 0: rgb[i * Width + j].rgbBlue = rgb[i * Width + j].rgbBlue & mask; rgb[i * Width + j].rgbBlue = rgb[i * Width + j].rgbBlue | cur; colour++; break;
                case 1: rgb[i * Width + j].rgbGreen = rgb[i * Width + j].rgbGreen & mask; rgb[i * Width + j].rgbGreen = rgb[i * Width + j].rgbGreen | cur; colour++; break;
                case 2: rgb[i * Width + j].rgbRed = rgb[i * Width + j].rgbRed & mask; rgb[i * Width + j].rgbRed = rgb[i * Width + j].rgbRed | cur; colour++; j++; break;
                }
                cur = 0;
            }
            else { return; }
        }
    }
}
void RGB::code_0000_xx00(std::string s, int row, int col)
{
    if ((row > Height - 8) || (col > Width - 8))
    {
        //std::cout << "Out of boundaries";
        return;
    }
    int mask = 243;	////243(10) = 1111 0011(2)
    size_t k = 0;
    char cur;
    int pos = 0, colour = 0;
    std::string finale;
    for (int i = row; i < row + 8; i++)
    {
        for (int j = col; j < col + 8; )
        {
            if (k < s.length())
            {
                int cur_val = s[k];
                pos = pos % 4;
                switch (pos)
                {
                case 0:	cur = (cur_val & 192) >> 4; pos++; break;	//1100 0000
                case 1:	cur = (cur_val & 48) >> 2; pos++; break;	//0011 0000
                case 2:	cur = (cur_val & 12); pos++; break;     	//0000 1100
                case 3:	cur = (cur_val & 3) << 2; pos++; break;		//0000 0011
                }

                if (pos == 4)
                {
                    k++;
                }

                colour = colour % 3;
                switch (colour)
                {
                case 0: rgb[i * Width + j].rgbBlue = rgb[i * Width + j].rgbBlue & mask; rgb[i * Width + j].rgbBlue = rgb[i * Width + j].rgbBlue | cur; colour++; break;
                case 1: rgb[i * Width + j].rgbGreen = rgb[i * Width + j].rgbGreen & mask; rgb[i * Width + j].rgbGreen = rgb[i * Width + j].rgbGreen | cur; colour++; break;
                case 2: rgb[i * Width + j].rgbRed = rgb[i * Width + j].rgbRed & mask; rgb[i * Width + j].rgbRed = rgb[i * Width + j].rgbRed | cur; colour++; j++; break;
                }
                cur = 0;
            }
            else { return; }
        }
    }
}
int RGB::find_block_and_hide(std::string for_hash, std::string to_hide)
{
    //find_solids();
    int secret_number = 0;
    std::string hash = get_hash(for_hash);
    int x = get_x(hash);

    while(x > Height || x > Width || x < 0) {    //while (x % 8 != 0)
        hash = get_hash(hash);
        x = get_x(hash);
    }
    std::cout << "x = " << x << std::endl;

    code_xx00_0000(to_hide, x, x);
    //code_00xx_0000(to_hide, x, x);
    //code_0000_xx00(to_hide, x, x);

    return secret_number;
}

std::string RGB::get_mes_from_xx00_0000(int max_len, int row, int col)
{
    if ((row > Height - 8) || (col > Width - 8))
    {
        return "Out of boundaries";
    }
    std::string finalle;
    int mask = 192;
    int pos = 0;
    char colour = 0;
    int color = 0;
    char word = 0;
    int count = 0;

    for (int i = row; i < row + 8; i++)
    {
        for (int j = col; j < col + 8;)							
        {
            if (count < max_len)
            {
                colour = colour % 3;
                switch (colour)
                {
                case 0:	color = rgb[i * Width + j].rgbBlue; colour++; break;        //1100 0000
                case 1:	color = rgb[i * Width + j].rgbGreen; colour++; break;	    //0011 0000
                case 2:	color = rgb[i * Width + j].rgbRed; colour++; j++;  break;	//0000 1100
                }

                pos = pos % 4;
                switch (pos)
                {
                case 0: word = word | (color & mask); pos++; break;
                case 1: word = word | (color & mask) >> 2; pos++; break;
                case 2: word = word | (color & mask) >> 4; pos++;  break;
                case 3: word = word | (color & mask) >> 6; pos++; break;
                }
                if (pos == 4)
                {
                    finalle += word;
                    word = 0;
                    count++;
                }
            }
            else
            {
                return finalle;
            }
        }
    }
    return finalle;
}
std::string RGB::get_mes_from_00xx_0000(int max_len, int row, int col)
{
    if ((row > Height - 8) || (col > Width - 8))
    {
        return "Out of boundaries";
    }
    std::string finalle;
    int mask = 48;//0011 0000
    int pos = 0;
    char colour = 0;
    int color = 0;
    char word = 0;
    int count = 0;

    for (int i = row; i < row + 8; i++)
    {
        for (int j = col; j < col + 8;)						
        {
            if (count < max_len)
            {
                colour = colour % 3;
                switch (colour)
                {
                case 0:	color = rgb[i * Width + j].rgbBlue; colour++; break;        //1100 0000
                case 1:	color = rgb[i * Width + j].rgbGreen; colour++; break;	    //0011 0000
                case 2:	color = rgb[i * Width + j].rgbRed; colour++; j++;  break;	//0000 1100
                }

                pos = pos % 4;
                switch (pos)
                {
                case 0: word = word | (color & mask) << 2; pos++; break;
                case 1: word = word | (color & mask); pos++; break;
                case 2: word = word | (color & mask) >> 2; pos++;  break;
                case 3: word = word | (color & mask) >> 4; pos++; break;
                }
                if (pos == 4)
                {
                    finalle += word;
                    word = 0;
                    count++;
                }
            }
            else
            {
                return finalle;
            }
        }
    }
    return finalle;
}
std::string RGB::get_mes_from_0000_xx00(int max_len, int row, int col)
{
    if ((row > Height - 8) || (col > Width - 8))
    {
        return "Out of boundaries";
    }
    std::string finalle;
    int mask = 12;//0000 1100
    int pos = 0;
    char colour = 0;
    int color = 0;
    char word = 0;
    int count = 0;

    for (int i = row; i < row + 8; i++)
    {
        for (int j = col; j < col + 8;)						
        {
            if (count < max_len)
            {
                colour = colour % 3;
                switch (colour)
                {
                case 0:	color = rgb[i * Width + j].rgbBlue; colour++; break;        //1100 0000
                case 1:	color = rgb[i * Width + j].rgbGreen; colour++; break;	    //0011 0000
                case 2:	color = rgb[i * Width + j].rgbRed; colour++; j++;  break;	//0000 1100
                }

                pos = pos % 4;
                switch (pos)
                {
                case 0: word = word | (color & mask) << 4; pos++; break;
                case 1: word = word | (color & mask) << 2; pos++; break;
                case 2: word = word | (color & mask); pos++;  break;
                case 3: word = word | (color & mask) >> 2; pos++; break;
                }
                if (pos == 4)
                {
                    finalle += word;
                    word = 0;
                    count++;
                }
            }
            else
            {
                return finalle;
            }
        }
    }
    return finalle;
}
std::string RGB::find_block_and_return_mes(std::string for_hash, int secret_number)
{
    std::string hash = get_hash(for_hash);
    int x = get_x(hash);
    /*
     * while (count != secret_number)
    {
        hash = get_hash(hash);
        x = get_x(hash);
        count += 2;
    }*/
    while(x > Height || x > Width || x < 0)
    {
        hash = get_hash(hash);
        x = get_x(hash);
    }
    return get_mes_from_xx00_0000(for_hash.length() * 3, x, x);
    //return get_mes_from_00xx_0000(for_hash.length()*3, x, x);
    //return get_mes_from_0000_xx00(for_hash.length() * 3, x, x);
}

std::string RGB::get_hash(std::string str)
{
    md5wrapper md5;
    return md5.getHashFromString(str);
}
int RGB::get_x(std::string s)
{
    int x = getint(s);
    if ((x < Height) && (Width))
    {
        return x;
    }
    else
    {
        return -1;
    }
}
int RGB::getint(std::string s)
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

void RGB::calc_hist()
{
    std::vector<int> mas_lum;
    int lum_col_height[255] = {0};
    int blue_col_height[255] = {0};
    int green_col_height[255] = {0};
    int red_col_height[255] = {0};
    max_val str_max_lum{0,0,0};
    max_val max_blue{0,0,0};
    max_val max_green{0,0,0};
    max_val max_red{0,0,0};
int num = 0;
    for(int i = 0; i < Height * Width; i++)
        {
            int lum = (0.299 * rgb[i].rgbRed + 0.587 * rgb[i].rgbGreen + 0.114 * rgb[i].rgbBlue);
            if(lum > 255){lum = 255;}if(lum < 0){lum = 0;}
            mas_lum.push_back(lum);

            lum_col_height[lum]++;
            blue_col_height[rgb[i].rgbBlue]+=1;
            green_col_height[rgb[i].rgbGreen]+=1;
            red_col_height[rgb[i].rgbRed]+=1;

            if(str_max_lum.val < lum_col_height[lum])
            {
                str_max_lum.val = lum_col_height[lum];
                str_max_lum.col = i % Width;
                str_max_lum.row = i / Width;
            }
    }
     write_hist_to_file(lum_col_height);
     find_block_from_hist(lum_col_height, mas_lum, str_max_lum);
}
int RGB::find_block_from_hist(int *a, std::vector<int> mas_lum, max_val point)
{
    struct max_val lv,pv,ln,pn;
    for(int y = 0; y < 80; y++)
    {
        if(point.col + y > Height){std::cout << "out of Y"; return - 1;}
        for(int x = 1; x < 80; x++)
        {
            if(point.col + x > Width){std::cout << "out of X"; return -1;}
            if(((point.col + y) * Width + point.row + x) > Width*Height)
            {break;}

            if(abs(mas_lum[(point.col + y) * Width + point.row + x]  - mas_lum[point.col * Width + point.row]) < 100)
            {pv.row = point.row + x; pn.row = point.row + x; pv.col = point.col + y; lv.col = point.col + y;}
            if(abs(mas_lum[(point.col + y) * Width + point.row - x]  - mas_lum[point.col * Width + point.row]) < 100)
            {lv.row = point.row - x; ln.row = point.row - x; lv.col = point.col + y; pv.col = point.col + y;}

            if(abs(mas_lum[(point.col - y) * Width + point.row + x]  - mas_lum[point.col * Width + point.row]) < 100)
            {pv.row = point.row + x; pn.row = point.row + x; pn.col = point.col - y; ln.col = point.col - y;}
            if(abs(mas_lum[(point.col - y) * Width + point.row - x]  - mas_lum[point.col * Width + point.row]) < 100)
            {lv.row = point.row - x; ln.row = point.row - x; ln.col = point.col - y; pn.col = point.col - y;}
        }
    }
}


void RGB::write_hist_to_file(int* a)
{
    FILE* f = fopen("C:\\Users\\Anna\\Desktop\\1.txt", "w");
    for(int i = 0; i < 255; i++)
    {
        int cur = a[i] / 10;
        while(cur > -1)
        {
            fprintf(f,"%c",'*');
            //std::cout << "x";
            cur--;
        }
        fprintf(f, "%c", '\n');
    }
    fclose(f);
}
