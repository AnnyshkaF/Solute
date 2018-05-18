#include "stb_image_write.h"
#include "jpegimage.h"
#include "stegrgb.h"

int main(int argc,  char* argv[])  
{
    int shift = 6;

    int key = 0;
	if(argc != 3)
    {
        std::cout << "Not enough arg!" <<std::endl;
        return 1;
    }

    JpegImage jpegImage(argv[1]);
    if (jpegImage.m_pImageInfo)
    {
        Rgb r(jpegImage.m_pImageInfo->nHeight, jpegImage.m_pImageInfo->nWidth, jpegImage.m_pImageInfo->nNumComponent);
        r.IntoRGB(jpegImage.m_pImageInfo->pData);

        key = r.HideText("HelloWorld", "First Secret message!Second secret message! Third secret message! Fourth secret message! Fifth secret message! Sixth secret message! Seventh secret message!", shift);

        //r.CalculateHistogram();

        r.OutRGB(jpegImage.m_pImageInfo->pData);
        stbi_write_jpg(argv[2], jpegImage.m_pImageInfo->nWidth, jpegImage.m_pImageInfo->nHeight, jpegImage.m_pImageInfo->nNumComponent, jpegImage.m_pImageInfo->pData, 100);
    }

    JpegImage jpegImage1(argv[2]);
    if (jpegImage1.m_pImageInfo)
    {
        std::cout << "\nDif pic:\n";
        Rgb r(jpegImage1.m_pImageInfo->nHeight, jpegImage1.m_pImageInfo->nWidth, jpegImage1.m_pImageInfo->nNumComponent);
        r.IntoRGB(jpegImage1.m_pImageInfo->pData);

        std::cout << r.GetText("HelloWorld", shift, key);

    }
    return 0;
}

