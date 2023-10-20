/*
 * SPDX-FileCopyrightText: Copyright (c) 2023 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
 * SPDX-License-Identifier: MIT
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#ifndef __LIDAR_POSTPROCESS_HPP__
#define __LIDAR_POSTPROCESS_HPP__

#include <memory>
#include "common/dtype.hpp"

namespace pointpillar {
namespace lidar {

struct PostProcessParameter {
    nvtype::Float3 min_range;
    nvtype::Float3 max_range;
    nvtype::Int2 feature_size;
    int num_classes = 3;
    int num_anchors = 6;
    int len_per_anchor = 4;
    float anchors[24] = {
            3.9,1.6,1.56,0.0,
            3.9,1.6,1.56,1.57,
            0.8,0.6,1.73,0.0,
            0.8,0.6,1.73,1.57,
            1.76,0.6,1.73,0.0,
            1.76,0.6,1.73,1.57,
        };
    nvtype::Float3 anchor_bottom_heights{-1.78,-0.6,-0.6};
    int num_box_values = 7;
    float score_thresh = 0.1;
    float dir_offset = 0.78539;
};

class PostProcess {
    public:
        virtual void forward(const float* cls, const float* box, const float* dir, void* stream) = 0;

        virtual const float* bndbox() = 0;
};

std::shared_ptr<PostProcess> create_postprocess(const PostProcessParameter& param);

};  // namespace lidar
};  // namespace pointpillar

#endif  // __LIDAR_POSTPROCESS_HPP__
