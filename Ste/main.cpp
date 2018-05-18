#include "stb_image_write.h"
#include "jpegimage.h"
#include "stegrgb.h"

int main(int argc,  char* argv[])  
{
    int shift = 6;

    argc = 3;
    std::cout << "argc = " << argc << std::endl;

	if(argc != 3)
    {
        std::cout << "Not enough arg!" <<std::endl;
        return 1;
    }
    argv[1] = "C:\\Users\\Anna\\Desktop\\SN.jpg";
    argv[2] = "C:\\Users\\Anna\\Desktop\\r.jpg";

    JpegImage jpegImage(argv[1]);
    if (jpegImage.m_pImageInfo)
    {
        Rgb r(jpegImage.m_pImageInfo->nHeight, jpegImage.m_pImageInfo->nWidth, jpegImage.m_pImageInfo->nNumComponent);
        r.IntoRGB(jpegImage.m_pImageInfo->pData);

        r.FindBlockAndHideMessage("HelloWorld1", "First Secret message", shift);
        r.FindBlockAndHideMessage("HelloWorld2", "Second Secret message", shift);
//        r.FindBlockAndHideMessage("HelloWorld3", "First Secret message", shift);
//        r.FindBlockAndHideMessage("HelloWorld4", "First Secret message", shift);

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

        std::cout << r.FindBlockAndReturnMessage("HelloWorld1", shift) << std::endl;
        std::cout << r.FindBlockAndReturnMessage("HelloWorld2", shift) << std::endl;
//        std::cout << r.FindBlockAndReturnMessage("HelloWorld3", shift) << std::endl;
//        std::cout << r.FindBlockAndReturnMessage("HelloWorld4", shift) << std::endl;
    }
    return 0;
}

