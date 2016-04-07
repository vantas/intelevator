#pragma once

#include <map>
#include <memory>
#include <queue>
#include <set>
#include "Client.h"
#include "Direction.h"
#include "Event.h"
#include "EventObserver.h"

class Elevator : public EventObserver {
public:
  Elevator(int number, int capacity, int floor);
  virtual ~Elevator();

  Direction getDirection() const;
  double getOccupation() const;
  int getNumber() const;
  int getCapacity() const;

  void addPassenger(std::shared_ptr<const Client> client);

  std::shared_ptr<std::set<const Floor>> getDestinations() const;

  int getCurrentFloor() const;

  constexpr static float seconds_per_floor = 10.f;

  void notify(const std::shared_ptr<const Event> event) const;

private:
  const int _number;
  const int _capacity;
  int _current_floor;

  std::set<std::shared_ptr<const Client>> _passengers;
};
