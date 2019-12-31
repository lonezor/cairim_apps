#include "time_utils.hpp"

#include <time.h>

namespace vtr {
namespace time_utils {

uint64_t get_ts() {
  uint64_t ts;
  struct timespec now;

  if (clock_gettime(CLOCK_MONOTONIC, &now)) {
    return 0;
  }

  ts = (uint64_t)now.tv_sec * 1000000LLU;
  ts += (uint64_t)now.tv_nsec / 1000LLU;

  return ts;
}

} // namespace time_utils
} // namespace vtr

