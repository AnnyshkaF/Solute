# define _CRT_SECURE_NO_WARNINGS
# ifndef JPEG_LOADER_H
# define JPEG_LOADER_H
# include <stdio.h>
# include "jpeglib.h"
# include <setjmp.h>
# include <stdint.h>
# include "boost/scoped_ptr.hpp"

class JpegImage
{
public:
    struct ImageInfo
    {
        uint32_t nWidth;
        uint32_t nHeight;
        uint8_t nNumComponent;
        uint8_t* pData;
    };
    boost::scoped_ptr<ImageInfo> m_pImageInfo{new ImageInfo[1]};

    JpegImage(const char* szFileName);

private:

    struct ErrorManager
    {
        jpeg_error_mgr defaultErrorManager;
        jmp_buf jumpBuffer;
    };

    static void ErrorExit(j_common_ptr cinfo);
    static void OutputMessage(j_common_ptr cinfo);
};
#endif
