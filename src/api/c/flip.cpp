/*******************************************************
 * Copyright (c) 2014, ArrayFire
 * All rights reserved.
 *
 * This file is distributed under 3-clause BSD license.
 * The complete license agreement can be obtained at:
 * http://arrayfire.com/licenses/BSD-3-Clause
 ********************************************************/

#include <cassert>
#include <vector>

#include <Array.hpp>
#include <optypes.hpp>
#include <backend.hpp>
#include <common/ArrayInfo.hpp>
#include <common/err_common.hpp>
#include <common/half.hpp>
#include <lookup.hpp>
#include <af/defines.h>
#include <af/array.h>
#include <af/arith.h>
#include <af/data.h>
#include <af/index.h>
#include <af/seq.h>
#include <handle.hpp>

using namespace detail;
using common::half;
using std::swap;
using std::vector;

template<typename T>
static af_array flipArray(const af_array in, const unsigned dim) {
    const Array<T> &input = getArray<T>(in);
    vector<af_seq> index(4);

    for (int i = 0; i < 4; i++) { index[i] = af_span; }

    // Reverse "dim"
    dim4 in_dims = input.dims();
    af_seq s     = {(double)(in_dims[dim] - 1), 0, -1};

    index[dim] = s;

    Array<T> dst = createSubArray(input, index);

    return getHandle(dst);
}

af_err af_flip(af_array *result, const af_array in, const unsigned dim) {
    af_array out;
    try {
        const ArrayInfo &in_info = getInfo(in);

        if (in_info.ndims() <= dim) {
            *result = retain(in);
            return AF_SUCCESS;
        }

        af_dtype in_type = in_info.getType();

        switch (in_type) {
            case f16: out = flipArray<half>(in, dim); break;
            case f32: out = flipArray<float>(in, dim); break;
            case c32: out = flipArray<cfloat>(in, dim); break;
            case f64: out = flipArray<double>(in, dim); break;
            case c64: out = flipArray<cdouble>(in, dim); break;
            case b8: out = flipArray<char>(in, dim); break;
            case s32: out = flipArray<int>(in, dim); break;
            case u32: out = flipArray<unsigned>(in, dim); break;
            case s64: out = flipArray<intl>(in, dim); break;
            case u64: out = flipArray<uintl>(in, dim); break;
            case s16: out = flipArray<short>(in, dim); break;
            case u16: out = flipArray<ushort>(in, dim); break;
            case u8: out = flipArray<uchar>(in, dim); break;
            default: TYPE_ERROR(1, in_type);
        }
        swap(*result, out);
    }
    CATCHALL

    return AF_SUCCESS;
}
