#include "SayajinScheduler.h"
#include "Building.h"
#include "CostFunction.h"
#include "Elevator.h"
#include "Floor.h"
#include "Scenario.h"
#include "Simulator.h"
#include <algorithm>

int SayajinScheduler::schedule(const std::shared_ptr<CostFunction> costFunction,
                               const std::shared_ptr<const Building> building,
                               const std::shared_ptr<const Client> client,
                               const int elevatorToExclude) {

  auto elevators = getAvailableElevators(building, elevatorToExclude);
  auto horizon = building->getSimulator()->getScenario()->getPlanningHorizon();
  auto clients = getClients(horizon, client, building);
  auto the_answer_to_life_the_universe_and_everything =
      calculate(costFunction, building, elevators, clients);

  return the_answer_to_life_the_universe_and_everything.first->getNumber();
}

std::pair<std::shared_ptr<Elevator>, float>
SayajinScheduler::calculate(const std::shared_ptr<CostFunction> costFunction,
                            const std::shared_ptr<const Building> building,
                            Elevators elevators, Clients& clients) {

  if (clients.empty()) return {nullptr, 0.f};
  auto client = clients.front();
  clients.pop();

  float best_cost = std::numeric_limits<float>::infinity();
  auto the_chosen_one = elevators->front();

  for (auto elevator : *elevators) {
    auto cost1 = costFunction->calculate(building, elevator, client);
    auto cost2 = calculate(costFunction, building, elevators, clients).second;
    auto cost = cost1 + cost2;
    if (cost < best_cost) {
      best_cost = cost;
      the_chosen_one = elevator;
    }
  }

  return {the_chosen_one, best_cost};
}

Clients
SayajinScheduler::getClients(const int horizon,
                             const std::shared_ptr<const Client> client,
                             const std::shared_ptr<const Building> building) {
  Clients clients;
  clients.push(client);
  if (horizon > 1) {
    auto globalQueue = getGlobalQueue(horizon, building);
    while(!globalQueue.empty() && clients.size() < horizon) {
      if (client->getId() != globalQueue.top()->getId()) {
        clients.push(globalQueue.top());
      }
      globalQueue.pop();
    }
  }
  return clients;
}

ClientsPriorityQueue SayajinScheduler::getGlobalQueue(
    const int horizon, const std::shared_ptr<const Building> building) {

  std::priority_queue<std::shared_ptr<Client>,
                      std::vector<std::shared_ptr<Client>>, ClientComparator>
      clients;

  for (auto floor : *building->getFloors()) {
    for (auto client : floor->getUpLine(horizon))
      clients.push(client);
    for (auto client : floor->getDownLine(horizon))
      clients.push(client);
  }

  return clients;
}