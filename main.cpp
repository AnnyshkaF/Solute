# include "stegRGB.h"
# include "stb_image_write.h"

int main(int argc, char* argv[])
{
    int secret = 0;
    JpegImage jpegImage("C:\\Users\\Anna\\Desktop\\SN.jpg");
    if (jpegImage.m_pImageInfo)
    {
        RGB r(jpegImage.m_pImageInfo->nHeight, jpegImage.m_pImageInfo->nWidth, jpegImage.m_pImageInfo->nNumComponent);
        r.into_RGB(jpegImage.m_pImageInfo->pData);

        r.find_block_and_hide("HelloWorld1", "First Secret message");

        r.out_RGB(jpegImage.m_pImageInfo->pData);
        //r.calc_hist();
        stbi_write_jpg("C:\\Users\\Anna\\Desktop\\res.jpg", jpegImage.m_pImageInfo->nWidth, jpegImage.m_pImageInfo->nHeight, jpegImage.m_pImageInfo->nNumComponent, jpegImage.m_pImageInfo->pData, 100);
    }

    JpegImage jpegImage1("C:\\Users\\Anna\\Desktop\\res.jpg");
    if (jpegImage1.m_pImageInfo)
    {
        std::cout << "\nDif pic:\n";
        RGB r(jpegImage1.m_pImageInfo->nHeight, jpegImage1.m_pImageInfo->nWidth, jpegImage1.m_pImageInfo->nNumComponent);

        r.into_RGB(jpegImage1.m_pImageInfo->pData);

        std::cout << r.find_block_and_return_mes("HelloWorld1", secret) << std::endl;

    }
    return 0;
}





























/*
r.find_block_and_hide("HelloWorld2", "Second Secret message");
r.find_block_and_hide("HelloWorld3", "Third Secret message");
r.find_block_and_hide("HelloWorld4", "Fourth Secret message");
r.find_block_and_hide("HelloWorld5", "Fifth Secret message");
r.find_block_and_hide("HelloWorld6", "Sixth Secret message");
r.find_block_and_hide("HelloWorld7", "Seventh Secret message");
r.find_block_and_hide("HelloWorld8", "Eighth Secret message");
r.find_block_and_hide("HelloWorld9", "9 Secret message");
r.find_block_and_hide("HelloWorld10", "10 Secret message");
r.find_block_and_hide("HelloWorld11", "11 Secret message");
r.find_block_and_hide("HelloWorld12", "12 Secret message");
r.find_block_and_hide("HelloWorld13", "13 Secret message");
r.find_block_and_hide("HelloWorld14", "14 Secret message");
r.find_block_and_hide("HelloWorld15", "15 Secret message");
r.find_block_and_hide("HelloWorld16", "16 Secret message");
*/


/*
std::cout << r.find_block_and_return_mes("HelloWorld2", secret) << std::endl;
std::cout << r.find_block_and_return_mes("HelloWorld3", secret) << std::endl;
std::cout << r.find_block_and_return_mes("HelloWorld4", secret) << std::endl;
std::cout << r.find_block_and_return_mes("HelloWorld5", secret) << std::endl;
std::cout << r.find_block_and_return_mes("HelloWorld6", secret) << std::endl;
std::cout << r.find_block_and_return_mes("HelloWorld7", secret) << std::endl;
std::cout << r.find_block_and_return_mes("HelloWorld8", secret) << std::endl;
std::cout << r.find_block_and_return_mes("HelloWorld9", secret) << std::endl;
std::cout << r.find_block_and_return_mes("HelloWorld10", secret) << std::endl;
std::cout << r.find_block_and_return_mes("HelloWorl11", secret) << std::endl;
std::cout << r.find_block_and_return_mes("HelloWorld12", secret) << std::endl;
std::cout << r.find_block_and_return_mes("HelloWorld13", secret) << std::endl;
std::cout << r.find_block_and_return_mes("HelloWorld14", secret) << std::endl;
std::cout << r.find_block_and_return_mes("HelloWorld15", secret) << std::endl;
std::cout << r.find_block_and_return_mes("HelloWorld16", secret) << std::endl;
*/
