#include "citOLCCore.hpp"
#include <string>

#if defined(__clang__)
#define SHARED_EXPORT __attribute__((visibility("default")))
#define SHARED_LOCAL __attribute__((visibility("hidden")))
#endif

#if defined(IS_BUILDING_SHARED)
#define API SHARED_EXPORT
#else
#define API
#endif

std::string API getOLC(std::string const &city) {
  if (city == "Stockholm") {
    return "That is a good place";
  }
  return "I don't know";
}

