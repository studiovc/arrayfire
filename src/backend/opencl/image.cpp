/*******************************************************
 * Copyright (c) 2014, ArrayFire
 * All rights reserved.
 *
 * This file is distributed under 3-clause BSD license.
 * The complete license agreement can be obtained at:
 * http://arrayfire.com/licenses/BSD-3-Clause
 ********************************************************/

#if defined(WITH_GRAPHICS)

#include <GL/glew.h>
#include <Array.hpp>
#include <image.hpp>
#include <err_opencl.hpp>
#include <stdexcept>
#include <cstdio>

namespace opencl
{
    template<typename T>
    void copy_image(const Array<T> &in, const fg_image_handle image)
    {
        printf("Error: Graphics not available for OpenCL backend.\n");
        AF_ERROR("Graphics not Available", AF_ERR_NOT_CONFIGURED);
    }

    #define INSTANTIATE(T)      \
        template void copy_image<T>(const Array<T> &in, const fg_image_handle image);

    INSTANTIATE(float)
    INSTANTIATE(double)
    INSTANTIATE(int)
    INSTANTIATE(uint)
    INSTANTIATE(uchar)
    INSTANTIATE(char)
}

#endif
