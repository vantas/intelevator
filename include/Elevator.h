#pragma once

#include <map>
#include <memory>
#include <queue>
#include <set>
#include "Building.h"
#include "Client.h"
#include "Direction.h"

class Elevator {
public:
  Elevator(const std::shared_ptr<const Building> building);
  virtual ~Elevator();

  Direction getDirection() const;
  double getOccupation() const;

  void addPassenger(std::shared_ptr<const Client> client);

  std::shared_ptr<std::set<const Floor>> getDestinations() const;

private:
  std::set<std::shared_ptr<const Client>> _passengers;
  const std::shared_ptr<const Building> _building;
};
