/* Copyright 2021 The TensorFlow Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/

#include "tensorflow/core/common_runtime/request_cost.h"

#include <string>
#include <utility>
#include <vector>

#include "absl/container/flat_hash_map.h"
#include "absl/strings/string_view.h"
#include "absl/synchronization/mutex.h"
#include "absl/time/time.h"

namespace tensorflow {

void RequestCost::RecordCost(
    const std::vector<std::pair<absl::string_view, absl::Duration>>& costs) {
  absl::MutexLock lock(&mutex_);
  for (const auto& cost : costs) {
    cost_map_[cost.first] += cost.second;
  }
}

absl::flat_hash_map<std::string, absl::Duration> RequestCost::GetCosts() const {
  absl::MutexLock lock(&mutex_);
  return cost_map_;
}

}  // namespace tensorflow
