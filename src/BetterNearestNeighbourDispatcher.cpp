#include <memory>
#include "BetterNearestNeighbourDispatcher.h"
#include "Direction.h"
#include "Elevator.h"
#include "NearestNeighbourDispatcher.h"

int BetterNearestNeighbourDispatcher::pick_next_elevator(const std::shared_ptr<const CostFunction> costFunction,
                                                         const std::shared_ptr<const Building> building,
                                                         const std::shared_ptr<const ClientArrival> ca) const
{
  auto elevators = *(building->getElevators());
  auto floors = building->getFloors();
  auto request_floor = floors->at(ca->getLocation());
  auto closest = elevators.front();

  decltype(elevators) sd_elevators;

  // Find all elevators that are going that way, or are idle
  std::copy_if(elevators.begin(), elevators.end(), std::back_inserter(sd_elevators),
  [&](std::shared_ptr<const Elevator> el) {
    auto current_floor = building->getFloor(el->getLocation());
    return (el->getDirection() == current_floor->compareTo(*request_floor)) ||
           (el->getDirection() == Direction::idle);
  });

  // if no elevators are idle or going that way, then look through all elevators
  if (sd_elevators.size() == 0) {
    NearestNeighbourDispatcher disp;

      return disp.pick_next_elevator(costFunction, building, ca);
  }

  for (auto elevator : sd_elevators) {
    auto where_it_is = elevator->getLocation();
    auto where_to = request_floor->getNumber();
    auto where_the_closest_is = closest->getLocation();

    auto distance = where_it_is - where_to;
    auto closest_distance = where_the_closest_is - where_to;

    if (distance < closest_distance) {
        closest = elevator;
    }
  }

  return closest->getNumber();
}
