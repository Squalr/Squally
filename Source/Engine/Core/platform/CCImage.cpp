/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2013-2016 Chukong Technologies Inc.
Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/


#include "platform/CCImage.h"

#include <string>
#include <ctype.h>

#include "base/ccConfig.h"
#include "base/CCConsole.h"
#include "base/CCData.h"

extern "C"
{
    // To resolve link error when building 32bits with Xcode 6.
    // More information please refer to the discussion in https://github.com/cocos2d/cocos2d-x/pull/6986
#if defined (__unix)
#ifndef __ENABLE_COMPATIBILITY_WITH_UNIX_2003__
#define __ENABLE_COMPATIBILITY_WITH_UNIX_2003__
#include <stdio.h>
#include <dirent.h>
    FILE *fopen$UNIX2003( const char *filename, const char *mode )
    {
        return fopen(filename, mode);
    }
    size_t fwrite$UNIX2003( const void *a, size_t b, size_t c, FILE *d )
    {
        return fwrite(a, b, c, d);
    }
    int fputs$UNIX2003(const char *res1, FILE *res2){
        return fputs(res1,res2);
    }
    char *strerror$UNIX2003( int errnum )
    {
        return strerror(errnum);
    }
    DIR * opendir$INODE64$UNIX2003( char * dirName )
    {
        return opendir( dirName );
    }
    DIR * opendir$INODE64( char * dirName )
    {
        return opendir( dirName );
    }

    int closedir$UNIX2003(DIR * dir)
    {
        return closedir(dir);
    }

    struct dirent * readdir$INODE64( DIR * dir )
    {
        return readdir( dir );
    }
#endif
#endif

#include "png.h"
}

#include "base/ccMacros.h"
#include "platform/CCCommon.h"
#include "platform/CCStdC.h"
#include "platform/CCFileUtils.h"
#include "base/CCConfiguration.h"
#include "base/ccUtils.h"

#define CC_GL_ATC_RGB_AMD                                          0x8C92
#define CC_GL_ATC_RGBA_EXPLICIT_ALPHA_AMD                          0x8C93
#define CC_GL_ATC_RGBA_INTERPOLATED_ALPHA_AMD                      0x87EE

NS_CC_BEGIN

namespace
{
    typedef struct 
    {
        const unsigned char * data;
        ssize_t size;
        int offset;
    }tImageSource;
 
    static void pngReadCallback(png_structp png_ptr, png_bytep data, png_size_t length)
    {
        tImageSource* isource = (tImageSource*)png_get_io_ptr(png_ptr);
        
		if (data != nullptr && isource != nullptr && isource->data != nullptr)
		{
			if ((int)(isource->offset + length) <= isource->size)
			{
				memcpy(data, isource->data + isource->offset, length);
				isource->offset += length;
			}
			else
			{
				png_error(png_ptr, "pngReaderCallback failed");
			}
		}
    }
}

Texture2D::PixelFormat getDevicePixelFormat(Texture2D::PixelFormat format)
{
    return format;
}

//////////////////////////////////////////////////////////////////////////
// Implement Image
//////////////////////////////////////////////////////////////////////////
bool Image::PNG_PREMULTIPLIED_ALPHA_ENABLED = true;

Image::Image()
: _data(nullptr)
, _dataLen(0)
, _width(0)
, _height(0)
, _unpack(false)
, _fileType(Format::UNKNOWN)
, _renderFormat(Texture2D::PixelFormat::NONE)
, _numberOfMipmaps(0)
, _hasPremultipliedAlpha(false)
{

}

Image::~Image()
{
    if(_unpack)
    {
        for (int i = 0; i < _numberOfMipmaps; ++i)
            CC_SAFE_DELETE_ARRAY(_mipmaps[i].address);
    }
    else
        CC_SAFE_FREE(_data);
}

bool Image::initWithImageFile(const std::string& path)
{
    bool ret = false;
    _filePath = FileUtils::getInstance()->fullPathForFilename(path);

    Data data = FileUtils::getInstance()->getDataFromFile(_filePath);

    if (!data.isNull())
    {
        ret = initWithImageData(data.getBytes(), data.getSize());
    }

    return ret;
}

bool Image::initWithImageFileThreadSafe(const std::string& fullpath)
{
    bool ret = false;
    _filePath = fullpath;

    Data data = FileUtils::getInstance()->getDataFromFile(fullpath);

    if (!data.isNull())
    {
        ret = initWithImageData(data.getBytes(), data.getSize());
    }

    return ret;
}

bool Image::initWithImageData(const unsigned char * data, ssize_t dataLen)
{
    bool ret = false;
    
    do
    {
        CC_BREAK_IF(! data || dataLen <= 0);

        _fileType = detectFormat(data, dataLen);

        switch (_fileType)
        {
            case Format::PNG:
            {
                ret = initWithPngData(data, dataLen);
                break;
            }
            default:
            {
                CCLOG("cocos2d: unsupported image format!");
                break;
            }
        }
    } while (0);
    
    return ret;
}

bool Image::isPng(const unsigned char * data, ssize_t dataLen)
{
    if (dataLen <= 8)
    {
        return false;
    }

    static const unsigned char PNG_SIGNATURE[] = {0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a};

    return memcmp(PNG_SIGNATURE, data, sizeof(PNG_SIGNATURE)) == 0;
}

Image::Format Image::detectFormat(const unsigned char * data, ssize_t dataLen)
{
    if (isPng(data, dataLen))
    {
        return Format::PNG;
    }
    else
    {
        return Format::UNKNOWN;
    }
}

int Image::getBitPerPixel()
{
    return Texture2D::getPixelFormatInfoMap().at(_renderFormat).bpp;
}

bool Image::hasAlpha()
{
    return Texture2D::getPixelFormatInfoMap().at(_renderFormat).alpha;
}

bool Image::isCompressed()
{
    return Texture2D::getPixelFormatInfoMap().at(_renderFormat).compressed;
}

bool Image::initWithPngData(const unsigned char * data, ssize_t dataLen)
{
    // length of bytes to check if it is a valid png file
    #define PNGSIGSIZE  8
    
    bool ret = false;
    png_byte        header[PNGSIGSIZE]   = {0}; 
    png_structp     png_ptr     =   0;
    png_infop       info_ptr    = 0;

    do 
    {
        // png header len is 8 bytes
        CC_BREAK_IF(dataLen < PNGSIGSIZE);

        // check the data is png or not
        memcpy(header, data, PNGSIGSIZE);
        CC_BREAK_IF(png_sig_cmp(header, 0, PNGSIGSIZE));

        // init png_struct
        png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, 0, 0, 0);
        CC_BREAK_IF(! png_ptr);

        // init png_info
        info_ptr = png_create_info_struct(png_ptr);
        CC_BREAK_IF(!info_ptr);

        CC_BREAK_IF(setjmp(png_jmpbuf(png_ptr)));

        // set the read call back function
        tImageSource imageSource;
        imageSource.data    = (unsigned char*)data;
        imageSource.size    = dataLen;
        imageSource.offset  = 0;
        png_set_read_fn(png_ptr, &imageSource, pngReadCallback);

        // read png header info

        // read png file info
        png_read_info(png_ptr, info_ptr);

        _width = png_get_image_width(png_ptr, info_ptr);
        _height = png_get_image_height(png_ptr, info_ptr);
        png_byte bit_depth = png_get_bit_depth(png_ptr, info_ptr);
        png_uint_32 color_type = png_get_color_type(png_ptr, info_ptr);

        //CCLOG("color type %u", color_type);

        // force palette images to be expanded to 24-bit RGB
        // it may include alpha channel
        if (color_type == PNG_COLOR_TYPE_PALETTE)
        {
            png_set_palette_to_rgb(png_ptr);
        }
        // low-bit-depth grayscale images are to be expanded to 8 bits
        if (color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8)
        {
            bit_depth = 8;
            png_set_expand_gray_1_2_4_to_8(png_ptr);
        }
        // expand any tRNS chunk data into a full alpha channel
        if (png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS))
        {
            png_set_tRNS_to_alpha(png_ptr);
        }  
        // reduce images with 16-bit samples to 8 bits
        if (bit_depth == 16)
        {
            png_set_strip_16(png_ptr);            
        } 

        // Expanded earlier for grayscale, now take care of palette and rgb
        if (bit_depth < 8)
        {
            png_set_packing(png_ptr);
        }
        // update info
        png_read_update_info(png_ptr, info_ptr);
        color_type = png_get_color_type(png_ptr, info_ptr);

        switch (color_type)
        {
        case PNG_COLOR_TYPE_GRAY:
            _renderFormat = Texture2D::PixelFormat::I8;
            break;
        case PNG_COLOR_TYPE_GRAY_ALPHA:
            _renderFormat = Texture2D::PixelFormat::AI88;
            break;
        case PNG_COLOR_TYPE_RGB:
            _renderFormat = Texture2D::PixelFormat::RGB888;
            break;
        case PNG_COLOR_TYPE_RGB_ALPHA:
            _renderFormat = Texture2D::PixelFormat::RGBA8888;
            break;
        default:
            break;
        }

        // read png data
        png_size_t rowbytes;
        png_bytep* row_pointers = (png_bytep*)malloc( sizeof(png_bytep) * _height );

        rowbytes = png_get_rowbytes(png_ptr, info_ptr);

        _dataLen = rowbytes * _height;
        _data = static_cast<unsigned char*>(malloc(_dataLen * sizeof(unsigned char)));
        if (!_data)
        {
            if (row_pointers != nullptr)
            {
                free(row_pointers);
            }
            break;
        }

        for (unsigned short i = 0; i < _height; ++i)
        {
            row_pointers[i] = _data + i*rowbytes;
        }
        png_read_image(png_ptr, row_pointers);

        png_read_end(png_ptr, nullptr);

        // premultiplied alpha for RGBA8888
        if (PNG_PREMULTIPLIED_ALPHA_ENABLED && color_type == PNG_COLOR_TYPE_RGB_ALPHA)
        {
            premultipliedAlpha();
        }

        if (row_pointers != nullptr)
        {
            free(row_pointers);
        }

        ret = true;
    } while (0);

    if (png_ptr)
    {
        png_destroy_read_struct(&png_ptr, (info_ptr) ? &info_ptr : 0, 0);
    }
    return ret;
}

bool Image::initWithRawData(const unsigned char * data, ssize_t /*dataLen*/, int width, int height, int /*bitsPerComponent*/, bool preMulti)
{
    bool ret = false;
    do 
    {
        CC_BREAK_IF(0 == width || 0 == height);

        _height   = height;
        _width    = width;
        _hasPremultipliedAlpha = preMulti;
        _renderFormat = Texture2D::PixelFormat::RGBA8888;

        // only RGBA8888 supported
        int bytesPerComponent = 4;
        _dataLen = height * width * bytesPerComponent;
        _data = static_cast<unsigned char*>(malloc(_dataLen * sizeof(unsigned char)));
        CC_BREAK_IF(! _data);
        memcpy(_data, data, _dataLen);

        ret = true;
    } while (0);

    return ret;
}

void Image::premultipliedAlpha()
{
    CCASSERT(_renderFormat == Texture2D::PixelFormat::RGBA8888, "The pixel format should be RGBA8888!");
    
    unsigned int* fourBytes = (unsigned int*)_data;
    for(int i = 0; i < _width * _height; i++)
    {
        unsigned char* p = _data + i * 4;
        fourBytes[i] = CC_RGB_PREMULTIPLY_ALPHA(p[0], p[1], p[2], p[3]);
    }
    
    _hasPremultipliedAlpha = true;
}

NS_CC_END

