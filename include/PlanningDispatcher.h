#pragma once

#include "Dispatcher.h"
#include <map>
#include <vector>

class Client;
class Building;
class CostFunction;
class ClientArrival;
class Elevator;

class PlanningDispatcher : public Dispatcher
{
public:
  int pick_next_elevator(const std::shared_ptr<const CostFunction> costFunction,
                         const std::shared_ptr<const Building> building,
                         const std::shared_ptr<const ClientArrival>);

private:
  std::map<std::shared_ptr<const Elevator>, int>
  calculate(const std::shared_ptr<const CostFunction> costFunction,
            const std::shared_ptr<const Building> building,
            int horizon);

  std::vector<std::shared_ptr<Client>>
  getAllWaitingClients(const std::shared_ptr<const Building> b);

  std::map<std::shared_ptr<const Elevator>, int>
  next_step(const std::shared_ptr<const CostFunction> costFunction,
            std::vector<std::shared_ptr<Client>> clients,
            std::map<std::shared_ptr<const Elevator>, int> current_costs,
            int horizon);
};
