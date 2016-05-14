#include "Client.h"
#include "NearestNeighbourCostFunction.h"
#include "Elevator.h"

float NearestNeighbourCostFunction::calculate(
    const std::shared_ptr<const Building> building,
    const std::shared_ptr<const Elevator> elevator,
    const std::shared_ptr<const Client> c) const {
  return abs(c->getArrivalFloor() - elevator->getLocation());
}
