#pragma once

# include "stdio.h"
# include "stdlib.h"
# include "stdint.h"
typedef struct
{
	unsigned short  bfType;
	unsigned int    bfSize;
	unsigned short  bfReserved1;
	unsigned short  bfReserved2;
    unsigned int    bfOffBits;
} BitMapFileHeader;

typedef struct
{
	unsigned int    biSize;
	unsigned int	biWidth;
	unsigned int	biHeight;
	unsigned short  biPlanes;
	unsigned short  biBitCount;
	unsigned int	biCompression;
	unsigned int	biSizeImage;
	unsigned int	biXPelsPerMeter;
	unsigned int	biYPelsPerMeter;
	unsigned int	biClrUsed;
	unsigned int	biClrImportant;
} BitMapInfoHeader;

typedef struct
{
    uint8_t  Blue;
    uint8_t  Green;
    uint8_t  Red;
} RgbTriplet;


