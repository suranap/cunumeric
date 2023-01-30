/* Copyright 2022 NVIDIA Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#pragma once

#include "cunumeric/cunumeric.h"
#include "cunumeric/execution_policy/indexing/parallel_loop.h"
#include "cunumeric/omp_help.h"

#include <omp.h>

namespace cunumeric {

template <class Tag>
struct ParallelLoopPolicy<VariantKind::OMP, Tag> {
  template <class RECT, class KERNEL>
  void operator()(const RECT& rect, KERNEL&& kernel)
  {
    const size_t volume = rect.volume();
#pragma omp for schedule(static)
    for (size_t idx = 0; idx < volume; ++idx) { kernel(idx, Tag{}); }
  }
};

}  // namespace cunumeric
