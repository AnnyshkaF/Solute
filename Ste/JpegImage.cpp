#include "jpegimage.h"


JpegImage::JpegImage(const char* szFileName)
{
    jpeg_decompress_struct cinfo;
    ErrorManager errorManager;

    FILE* pFile = fopen(szFileName, "rb");
    if (!pFile)
       throw "Can't open file";
     //return NULL;

    // set our custom error handler
    cinfo.err = jpeg_std_error(&errorManager.defaultErrorManager);
    errorManager.defaultErrorManager.error_exit = ErrorExit;
    errorManager.defaultErrorManager.output_message = OutputMessage;
    if (setjmp(errorManager.jumpBuffer))
    {
        // We jump here on errorz
        jpeg_destroy_decompress(&cinfo);
        fclose(pFile);
        throw "Can't open file";
        //return NULL;
    }

    jpeg_create_decompress(&cinfo);
    jpeg_stdio_src(&cinfo, pFile);
    jpeg_read_header(&cinfo, TRUE);
    jpeg_start_decompress(&cinfo);

    m_pImageInfo->nWidth = cinfo.image_width;
    m_pImageInfo->nHeight = cinfo.image_height;
    m_pImageInfo->nNumComponent = cinfo.num_components;
    m_pImageInfo->pData = new uint8_t[m_pImageInfo->nWidth*m_pImageInfo->nHeight*m_pImageInfo->nNumComponent];

    while (cinfo.output_scanline < cinfo.image_height)
    {
        uint8_t* p = m_pImageInfo->pData + cinfo.output_scanline*cinfo.image_width*cinfo.num_components;
        jpeg_read_scanlines(&cinfo, &p, 1);
    }

    jpeg_finish_decompress(&cinfo);
    jpeg_destroy_decompress(&cinfo);
    fclose(pFile);

}

void JpegImage::ErrorExit(j_common_ptr cinfo)
{
	// cinfo->err is actually a pointer to my_error_mgr.defaultErrorManager, since pub
	// is the first element of my_error_mgr we can do a sneaky cast
	ErrorManager* pErrorManager = (ErrorManager*)cinfo->err;
	(*cinfo->err->output_message)(cinfo); // print error message (actually disabled below)
	longjmp(pErrorManager->jumpBuffer, 1);
}

void JpegImage::OutputMessage(j_common_ptr cinfo)
{
	// disable error messages
	/*char buffer[JMSG_LENGTH_MAX];
	(*cinfo->err->format_message) (cinfo, buffer);
	fprintf(stderr, "%s\n", buffer);*/
}
