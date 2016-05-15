#include "Simulator.h"
#include "Building.h"
#include "Client.h"
#include "ClientArrival.h"
#include "Clock.h"
#include "CostFunctionCreator.h"
#include "CostFunctionType.h"
#include "DispatcherCreator.h"
#include "DispatcherType.h"
#include "EventDispatcher.h"
#include "EventQueue.h"
#include "FinishSimulation.h"
#include "Floor.h"
#include "Scenario.h"
#include "Statistics.h"
#include "DispatcherType.h"
#include "CostFunctionType.h"
#include "Elevator.h"
#include <glog/logging.h>
#include <random>

Simulator::Simulator(const std::shared_ptr<const Scenario> scenario)
    : _scenario(scenario), _statistics(std::make_shared<Statistics>()),
      _clock(std::make_shared<Clock>()),
      _eventQueue(std::make_shared<EventQueue>()),
      _eventDispatcher(std::make_shared<EventDispatcher>()),
      _seed_seq(scenario->getSeed().begin(), scenario->getSeed().end()),
      _random_engine(std::make_shared<std::default_random_engine>(_seed_seq)) {}

Simulator::~Simulator() {}

std::shared_ptr<Building> Simulator::createBuilding() const {
  auto floors = Floor::create(shared_from_this());
  auto elevators = Elevator::create(shared_from_this());
  auto dispatcher = DispatcherCreator::create(_scenario->getDispatcherType());
  auto costFunction = CostFunctionCreator::create(_scenario->getCostFunctionType());

  auto building = std::make_shared<Building>(shared_from_this(), floors, elevators, dispatcher, costFunction);

  LOG(INFO) << "Created '" << _scenario->getName() << "' scenario with "
            << floors->size() << " floors, "
            << elevators->size() << " elevators, '"
            << Helpers::dispatcherName(_scenario->getDispatcherType()) << "' dispatcher and '"
            << Helpers::costFunctionName(_scenario->getCostFunctionType())
            << "' cost function.";

  return building;
}

const std::shared_ptr<const Scenario> Simulator::getScenario() const { return _scenario; }

const std::shared_ptr<Statistics> Simulator::getStatistics() const { return _statistics; }

const std::shared_ptr<Clock> Simulator::getClock() const { return _clock; }

const std::shared_ptr<EventQueue> Simulator::getEventQueue() const { return _eventQueue; }

const std::shared_ptr<EventDispatcher> Simulator::getEventDispatcher() const { return _eventDispatcher; }

const std::shared_ptr<std::default_random_engine> Simulator::getRandomEngine() const { return _random_engine; }

void Simulator::run() {
  LOG(INFO) << "Running '" << _scenario->getName() << "' scenario.";

  _building = createBuilding();
  _building->createFutureArrival();

  _eventDispatcher->subscribe(std::static_pointer_cast<EventObserver>(_clock));
  _eventDispatcher->subscribe(std::static_pointer_cast<EventObserver>(_building));
  _eventDispatcher->subscribe(std::static_pointer_cast<EventObserver>(_statistics));

  // auto ca1 = std::make_shared<ClientArrival>(5, std::make_shared<Client>(1, 0, 17, _clock->currentTime()));
  // auto ca2 = std::make_shared<ClientArrival>(15, std::make_shared<Client>(1, 14, 16, _clock->currentTime()));
  // auto ca3 = std::make_shared<ClientArrival>(10, std::make_shared<Client>(1, 4, 1, _clock->currentTime()));
  // auto ca4 = std::make_shared<ClientArrival>(11, std::make_shared<Client>(1, 0, 10, _clock->currentTime()));

  // _eventQueue->push(std::static_pointer_cast<Event>(ca1));
  // _eventQueue->push(std::static_pointer_cast<Event>(ca2));
  // _eventQueue->push(std::static_pointer_cast<Event>(ca3));
  // _eventQueue->push(std::static_pointer_cast<Event>(ca4));

  auto finishSimulationEvent = std::make_shared<FinishSimulation>(_scenario->getDuration());
  _eventQueue->push(std::static_pointer_cast<Event>(finishSimulationEvent));

  while (_statistics->keepRunning() && _eventQueue->hasNextEvent()) {
    auto e = _eventQueue->pop();
    if (e) {
      _eventDispatcher->broadcast(e);
      _eventQueue->refresh(_clock->currentTime());
    }
  }

  LOG(INFO) << "Finished '" << _scenario->getName() << "' scenario.";

  _statistics->printToFile(_scenario->getName());
}

bool Simulator::nextStep() { return true; }
