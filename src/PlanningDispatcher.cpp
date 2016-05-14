#include "PlanningDispatcher.h"
#include "Building.h"
#include "Elevator.h"

int PlanningDispatcher::pick_next_elevator(const std::shared_ptr<const CostFunction> costFunction,
                                           const std::shared_ptr<const Building> building,
                                           const std::shared_ptr<const ClientArrival> ca)
{
  return 0;
}

std::map<int, int> PlanningDispatcher::calculate(const std::shared_ptr<const CostFunction> costFunction,
                                                 const std::shared_ptr<const Building> building,
                                                 int horizon)
{
  std::map<int, int> costs;
  for (auto e : *building->getElevators()) {
    costs[e->getNumber()] = 0;
  }

  return next_step(costFunction, building, costs, horizon);
}

std::map<int, int> PlanningDispatcher::next_step(const std::shared_ptr<const CostFunction> costFunction,
                                                 const std::shared_ptr<const Building> building,
                                                 std::map<int, int> current_costs,
                                                 int horizon)
{
  return current_costs;
}
