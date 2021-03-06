#pragma once

#include <stdexcept>
#include <string>

enum class Status {
  Moving,  // Elevator is moving. :P
  Stopped, // Elevator is stopped in a floor but is still travelling.
  Idle     // Elevator is stopped and has nothing to do with its life.
};

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-function"
namespace Helpers {
  static std::string statusName(Status type) {
    switch (type) {
    case Status::Moving:
      return "moving";
    case Status::Stopped:
      return "stopped";
    case Status::Idle:
      return "idle";
    default:
      throw std::invalid_argument("");
    }
  }
}
#pragma clang diagnostic pop
