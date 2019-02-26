// Copyright (c) 2019, NVIDIA CORPORATION. All rights reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef DALI_KERNELS_IMGPROC_RESAMPLE_PARAMS_H_
#define DALI_KERNELS_IMGPROC_RESAMPLE_PARAMS_H_

#include <cuda_runtime.h>
#include "dali/kernels/kernel.h"

namespace dali {
namespace kernels {

enum class ResamplingFilterType : uint8_t {
  Nearest,
  Linear,
  Triangular,
  Gaussian,
  Lanczos3,
};

constexpr int KeepOriginalSize = -1;

inline float DefaultFilterRadius(ResamplingFilterType type, float in_size, float out_size) {
  switch (type) {
  case ResamplingFilterType::Triangular:
    return in_size > out_size ? in_size/out_size : 1;
  case ResamplingFilterType::Gaussian:
    return in_size > out_size ? in_size/out_size : 1;
  case ResamplingFilterType::Lanczos3:
    return 3;
  default:
    return 1;
  }
}

struct FilterDesc {
  constexpr FilterDesc() = default;
  constexpr FilterDesc(ResamplingFilterType type, float radius = 0)  // NOLINT
  : type(type), radius(radius) {}
  ResamplingFilterType type = ResamplingFilterType::Nearest;
  float radius = 0;
};

struct ResamplingParams {
  FilterDesc min_filter, mag_filter;
  int output_size;
};

using ResamplingParams2D = std::array<ResamplingParams, 2>;

}  // namespace kernels
}  // namespace dali

#endif  // DALI_KERNELS_IMGPROC_RESAMPLE_PARAMS_H_