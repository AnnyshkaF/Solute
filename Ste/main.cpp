#include "stb_image_write.h"
#include "jpegimage.h"
#include "stegrgb.h"

int main(int argc,  char* argv[])  
{
    /*
     * masks to hide(to use)
     *
     *     63(10)  =  0011.1111(2) = 0x3F(16)
     *     207(10) =  1100.1111(2) = 0xCF(16)
     *     243(10) =  1111.0011(2) = 0xF3(16)
     *
     * masks to reveal
     *
     *     192(10) = 1100.0000(2) = 0xC0(16)
     *     48(10)  = 0011.0000(2) = 0x30(16)
     *     12(10)  = 0000.1100(2) = 0xC(16)
     *
    */
    int mask = 63;

    //argc = 3;
    std::cout << "argc = " << argc << std::endl;

	if(argc != 3)
    {
        std::cout << "Not enough arg!" <<std::endl;
        return 1;
    }
    //argv[1] = "C:\\Users\\Anna\\Desktop\\SN.jpg";
    //argv[2] = "C:\\Users\\Anna\\Desktop\\res.jpg";

    JpegImage jpegImage(argv[1]);
    if (jpegImage.m_pImageInfo)
    {
        RGB r(jpegImage.m_pImageInfo->nHeight, jpegImage.m_pImageInfo->nWidth, jpegImage.m_pImageInfo->nNumComponent);
        r.IntoRGB(jpegImage.m_pImageInfo->pData);

        r.FindBlockAndHideMessage("HelloWorld1", "First Secret message", mask);
        r.FindBlockAndHideMessage("HelloWorld2", "First Secret message", mask);
        r.FindBlockAndHideMessage("HelloWorld3", "First Secret message", mask);
        r.FindBlockAndHideMessage("HelloWorld4", "First Secret message", mask);

        r.OutRGB(jpegImage.m_pImageInfo->pData);
        //r.CalculateHistogram();

        stbi_write_jpg(argv[2], jpegImage.m_pImageInfo->nWidth, jpegImage.m_pImageInfo->nHeight, jpegImage.m_pImageInfo->nNumComponent, jpegImage.m_pImageInfo->pData, 100);
    }

    JpegImage jpegImage1(argv[2]);
    if (jpegImage1.m_pImageInfo)
    {
        std::cout << "\nDif pic:\n";
        RGB r(jpegImage1.m_pImageInfo->nHeight, jpegImage1.m_pImageInfo->nWidth, jpegImage1.m_pImageInfo->nNumComponent);
        r.IntoRGB(jpegImage1.m_pImageInfo->pData);

        std::cout << r.FindBlockAndReturnMessage("HelloWorld1", mask) << std::endl;
        std::cout << r.FindBlockAndReturnMessage("HelloWorld2", mask) << std::endl;
        std::cout << r.FindBlockAndReturnMessage("HelloWorld3", mask) << std::endl;
        std::cout << r.FindBlockAndReturnMessage("HelloWorld4", mask) << std::endl;
    }
    return 0;
}

