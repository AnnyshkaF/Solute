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
