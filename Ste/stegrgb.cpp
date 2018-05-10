#include "stegRGB.h"

RGB::RGB(int height, int width, int comp)
{
    this->height = height;
    this->width = width;
    this->comp = comp;
}
RGB::~RGB(){}

int RGB::GetHeight()
{
    return height;
}
int RGB::GetWidth()
{
    return width;
}

void RGB::IntoRGB(uint8_t* d)
{
    int k = 0;
    int max_k = height * width * comp;
    for (int i = 0; i < height * width; i++)
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
void RGB::OutRGB(uint8_t* d)
{
    int k = 0;
    int max_k = height * width * comp;
    for (int i = 0; i < height * width; i++)
    {
        if (k < max_k)
        {
            d[k++] = rgb[i].rgbBlue ;
            d[k++] = rgb[i].rgbGreen;
            d[k++] = rgb[i].rgbRed;
        }
    }
}

void RGB::CodeMessageInString(std::string s, int row, int col)
{
    if ((row > height - 8) || (col > width - 8))
    {
        //std::cout << "Out of boundaries";
        return;
    }

    int mask = 63;	////63(10) = 0011 1111(2)
    size_t k = 0;
    char cur;
    int pos = 0, colour = 0;
    std::string finale;
    for (size_t j = col; j < col + s.length(); j++)
    {
        if (k < s.length())
        {
            int cur_val = s[k];
            pos = pos % 4;
            cur = (cur_val & 192); pos++; break;        //1100 0000

            if (pos == 4)
            {
                k++;
            }

            colour = colour % 3;
            switch (colour)
            {
            case 0:
                rgb[row * width + j].rgbBlue = rgb[row * width + j].rgbBlue & mask;
                rgb[row * width + j].rgbBlue = rgb[row * width + j].rgbBlue | cur;
                colour++;
                break;
            case 1:
                rgb[row * width + j].rgbGreen = rgb[row * width + j].rgbGreen & mask;
                rgb[row * width + j].rgbGreen = rgb[row * width + j].rgbGreen | cur;
                colour++;
                break;
            case 2:
                rgb[row * width + j].rgbRed = rgb[row * width + j].rgbRed & mask;
                rgb[row * width + j].rgbRed = rgb[row * width + j].rgbRed | cur;
                colour++;
                j++;
                break;
            }
            cur = 0;
        }
        else { return; }
    }


}

void RGB::CodeMessage_xx00_0000(std::string s, int row, int col)
{
    if ((row > height - 8) || (col > width - 8))
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
                case 0: rgb[i * width + j].rgbBlue = rgb[i * width + j].rgbBlue & mask; rgb[i * width + j].rgbBlue = rgb[i * width + j].rgbBlue | cur; colour++; break;
                case 1: rgb[i * width + j].rgbGreen = rgb[i * width + j].rgbGreen & mask; rgb[i * width + j].rgbGreen = rgb[i * width + j].rgbGreen | cur; colour++; break;
                case 2: rgb[i * width + j].rgbRed = rgb[i * width + j].rgbRed & mask; rgb[i * width + j].rgbRed = rgb[i * width + j].rgbRed | cur; colour++; j++; break;
                }
                cur = 0;
            }
            else { return; }
        }
    }
}
void RGB::CodeMessage_00xx_0000(std::string s, int row, int col)
{
    if ((row > height - 8) || (col > width - 8))
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
                case 0: rgb[i * width + j].rgbBlue = rgb[i * width + j].rgbBlue & mask; rgb[i * width + j].rgbBlue = rgb[i * width + j].rgbBlue | cur; colour++; break;
                case 1: rgb[i * width + j].rgbGreen = rgb[i * width + j].rgbGreen & mask; rgb[i * width + j].rgbGreen = rgb[i * width + j].rgbGreen | cur; colour++; break;
                case 2: rgb[i * width + j].rgbRed = rgb[i * width + j].rgbRed & mask; rgb[i * width + j].rgbRed = rgb[i * width + j].rgbRed | cur; colour++; j++; break;
                }
                cur = 0;
            }
            else { return; }
        }
    }
}
void RGB::CodeMessage_0000_xx00(std::string s, int row, int col)
{
    if ((row > height - 8) || (col > width - 8))
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
                case 1:	cur = (cur_val & 48) >> 2; pos++; break;			//0011 0000
                case 2:	cur = (cur_val & 12); pos++; break;	//0000 1100
                case 3:	cur = (cur_val & 3) << 2; pos++; break;		//0000 0011
                }

                if (pos == 4)
                {
                    k++;
                }

                colour = colour % 3;
                switch (colour)
                {
                case 0: rgb[i * width + j].rgbBlue = rgb[i *  width + j].rgbBlue & mask; rgb[i *  width + j].rgbBlue = rgb[i *  width + j].rgbBlue | cur; colour++; break;
                case 1: rgb[i * width + j].rgbGreen = rgb[i *  width + j].rgbGreen & mask; rgb[i *  width + j].rgbGreen = rgb[i *  width + j].rgbGreen | cur; colour++; break;
                case 2: rgb[i * width + j].rgbRed = rgb[i *  width + j].rgbRed & mask; rgb[i *  width + j].rgbRed = rgb[i *  width + j].rgbRed | cur; colour++; j++; break;
                }
                cur = 0;
            }
            else { return; }
        }
    }
}
void RGB::FindBlockAndHideMessage(std::string for_hash, std::string to_hide)
{
    std::string hash = CalculateHash(for_hash);
    int x = 0;
    int y = 0;

    while(x > width || x < 0 || x == 0) {    //while (x % 8 != 0)
        hash = CalculateHash(hash);
        x = GetIntFromHash(hash);
    }
    while(y > height || y == 0 || y < 0) {    //while (x % 8 != 0)
        hash = CalculateHash(hash);
        y =GetIntFromHash(hash);
    }
    std::cout << "x = " << x ;
    std::cout << " y = " << y << std::endl;

    CodeMessage_xx00_0000(to_hide, x, y);
    //CodeMessage_00xx_0000(to_hide, x, y);
    //CodeMessage_0000_xx00(to_hide, x, y);
}

std::string RGB::GetMessageFrom_xx00_0000(int max_len, int row, int col)
{
    if ((row > height - 8) || (col > width - 8))
    {
        return "Out of boundaries";
    }
    std::string finalle;
    int mask = 192;//0011 0000
    int pos = 0;
    char colour = 0;
    int color = 0;
    char word = 0;
    int count = 0;

    for (int i = row; i < row + 8; i++)
    {
        for (int j = col; j < col + 8;)							//252(10) = 1111 1100(2)
        {
            if (count < max_len)
            {
                colour = colour % 3;
                switch (colour)
                {
                case 0:	color = rgb[i * width + j].rgbBlue; colour++; break;//1100 0000
                case 1:	color = rgb[i * width + j].rgbGreen; colour++; break;	//0011 0000
                case 2:	color = rgb[i * width + j].rgbRed; colour++; j++;  break;	//0000 1100
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
std::string RGB::GetMessageFrom_00xx_0000(int max_len, int row, int col)
{
    if ((row > height - 8) || (col > width - 8))
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
        for (int j = col; j < col + 8;)							//252(10) = 1111 1100(2)
        {
            if (count < max_len)
            {
                colour = colour % 3;
                switch (colour)
                {
                case 0:	color = rgb[i * width + j].rgbBlue; colour++; break;//1100 0000
                case 1:	color = rgb[i * width + j].rgbGreen; colour++; break;	//0011 0000
                case 2:	color = rgb[i * width + j].rgbRed; colour++; j++;  break;	//0000 1100
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
std::string RGB::GetMessageFrom_0000_xx00(int max_len, int row, int col)
{
    if ((row > height - 8) || (col > width - 8))
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
        for (int j = col; j < col + 8;)							//252(10) = 1111 1100(2)
        {
            if (count < max_len)
            {
                colour = colour % 3;
                switch (colour)
                {
                case 0:	color = rgb[i * width + j].rgbBlue; colour++; break;//1100 0000
                case 1:	color = rgb[i * width + j].rgbGreen; colour++; break;	//0011 0000
                case 2:	color = rgb[i * width + j].rgbRed; colour++; j++;  break;	//0000 1100
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
std::string RGB::FindBlockAndReturnMessage(std::string for_hash)
{
    std::string hash = CalculateHash(for_hash);
    int x = 0;
    int y = 0;

    while(x > width || x < 0 || x == 0)
    {
        hash = CalculateHash(hash);
        x = GetIntFromHash(hash);
    }
     while(y > height || y < 0 || y == 0) {    //while (x % 8 != 0) // (y < 300) чтобы справа прятать
        hash = CalculateHash(hash);
        y = GetIntFromHash(hash);
    }

    return GetMessageFrom_xx00_0000(for_hash.length() * 3, x, y);
    //return GetMessageFrom_00xx_0000(for_hash.length() * 3, x, y);
    //return GetMessageFrom_0000_xx00(for_hash.length() * 3, x, y);
}

std::string RGB::CalculateHash(std::string str)
{
    md5wrapper md5;
    return md5.getHashFromString(str);
}
int RGB::GetIntFromHash(std::string s)
{
    int x = FirstIntFromHash(s);
    if ((x < height) && (x < width))
    {
        return x;
    }
    else
    {
        return -1;
    }
}
int RGB::FirstIntFromHash(std::string s)
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

void RGB::CalculateHistogram()
{
    std::vector<int> mas_lum;       //яркость каждого пикселя отдельно
    int lum_col_height[255] = {0};  //гистограмма яркости
    int blue_col_height[255] = {0};
    int green_col_height[255] = {0};
    int red_col_height[255] = {0};
    max_val str_max_lum{0,0,0};

    for(int i = 0; i < height * width; i++)
        {
            int lum = (0.299 * rgb[i].rgbRed + 0.587 * rgb[i].rgbGreen + 0.114 * rgb[i].rgbBlue);
            if(lum > 255){lum = 255;}
            if(lum < 0){lum = 0;}
            mas_lum.push_back(lum);

            lum_col_height[lum]++;
            blue_col_height[rgb[i].rgbBlue]+=1;
            green_col_height[rgb[i].rgbGreen]+=1;
            red_col_height[rgb[i].rgbRed]+=1;

            if(str_max_lum.val < lum_col_height[lum])
            {
                str_max_lum.val = lum_col_height[lum];
                str_max_lum.col = i % width;
                str_max_lum.row = i / width;
            }
            //if(max_blue.val < blue_col_height[lum]) {max_blue.val = blue_col_height[lum];max_blue.col = i / Width; max_blue.row = i % Width;}
            //if(max_green.val < green_col_height[lum]) {max_green.val = green_col_height[lum];max_green.col = i / Width; max_green.row = i % Width;}
            //if(max_red.val < red_col_height[lum]) {max_red.val = red_col_height[lum];max_red.col = i / Width; max_red.row = i % Width;}
    }
     WriteHistogramToFile(lum_col_height);
     FindBlockInHistogram(mas_lum, str_max_lum);
}
int RGB::FindBlockInHistogram(std::vector<int> mas_lum, max_val point)
{
    struct max_val lv,pv,ln,pn;
    for(int y = 0; y < 80; y++)
    {
        if(point.col + y > height){std::cout << "out of Y"; return - 1;}
        for(int x = 1; x < 80; x++)
        {
            if(point.col + x > width){std::cout << "out of X"; return -1;}
            if(((point.col + y) * width + point.row + x) > width * height)
            {break;}

            /*if(abs(mas_lum[(point.col + y) * Width + point.row + x]  - mas_lum[point.col * Width + point.row]) < 100)
            {pv.row = point.row + x; pn.row = point.row + x; pv.col = point.col + y; lv.col = point.col + y;}
            if(abs(mas_lum[(point.col + y) * Width + point.row - x]  - mas_lum[point.col * Width + point.row]) < 100)
            {lv.row = point.row - x; ln.row = point.row - x; lv.col = point.col + y; pv.col = point.col + y;}

            if(abs(mas_lum[(point.col - y) * Width + point.row + x]  - mas_lum[point.col * Width + point.row]) < 100)
            {pv.row = point.row + x; pn.row = point.row + x; pn.col = point.col - y; ln.col = point.col - y;}
            if(abs(mas_lum[(point.col - y) * Width + point.row - x]  - mas_lum[point.col * Width + point.row]) < 100)
            {lv.row = point.row - x; ln.row = point.row - x; ln.col = point.col - y; pn.col = point.col - y;}*/

            if(abs(mas_lum[(point.row + y) * width + point.col + x]  - mas_lum[point.row * width + point.col]) < 100)
            {pn.col = point.col + x; pn.row = point.row + y;}
            if(abs(mas_lum[(point.row + y) * width + point.row - x]  - mas_lum[point.row * width + point.col]) < 100)
            {ln.col = point.col - x; ln.row = point.row + y;}

            if(abs(mas_lum[(point.row - y) * width + point.col + x]  - mas_lum[point.row * width + point.col]) < 100)
            {pv.col = point.col + x; pv.row = point.row - y;}
            if(abs(mas_lum[(point.row - y) * width + point.col - x]  - mas_lum[point.row * width + point.col]) < 100)
            {lv.col = point.col - x; lv.row = point.row - y;}
        }
    }
    HighlightBlock(ln, lv, pn, pv);
    return 0;
}

void RGB::HighlightBlock(max_val ln, max_val lv, max_val pn, max_val pv)
{
    for(int i = lv.col; i < pv.col; i++)
    {
        rgb[lv.row * width + i].rgbBlue = 0;
        rgb[lv.row * width + i].rgbGreen = 0;
        rgb[lv.row * width + i].rgbRed = 0;

        rgb[ln.row * width + i].rgbBlue = 0;
        rgb[ln.row * width + i].rgbGreen = 0;
        rgb[ln.row * width + i].rgbRed = 0;
    }
    for(int i = lv.row; i < ln.row; i++)
    {
        rgb[i * width + ln.col].rgbBlue = 0;
        rgb[i * width + ln.col].rgbGreen = 0;
        rgb[i * width + ln.col].rgbRed = 0;

        rgb[i * width + pn.col].rgbBlue = 0;
        rgb[i * width + pn.col].rgbGreen = 0;
        rgb[i * width + pn.col].rgbRed = 0;
    }
}

void RGB::WriteHistogramToFile(int* a)
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
