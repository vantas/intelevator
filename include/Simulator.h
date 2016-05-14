#pragma once

#include <memory>
#include <random>

class Clock;
class Building;
class Statistics;
class EventQueue;
class EventDispatcher;
class Scenario;

class Simulator : public std::enable_shared_from_this<Simulator> {
public:
  Simulator(std::shared_ptr<const Scenario> scenario);
  virtual ~Simulator();

  std::shared_ptr<Building> createBuilding() const;

  const std::shared_ptr<const Scenario> getScenario() const;
  const std::shared_ptr<Statistics> getStatistics() const;
  const std::shared_ptr<Clock> getClock() const;
  const std::shared_ptr<EventQueue> getEventQueue() const;
  const std::shared_ptr<EventDispatcher> getEventDispatcher() const;
  const std::shared_ptr<std::default_random_engine> getRandomEngine() const;

  void run();

private:
  const std::shared_ptr<const Scenario> _scenario;
  const std::shared_ptr<Statistics> _statistics;
  const std::shared_ptr<Clock> _clock;
  const std::shared_ptr<EventQueue> _eventQueue;
  const std::shared_ptr<EventDispatcher> _eventDispatcher;
  std::seed_seq _seed_seq;
  const std::shared_ptr<std::default_random_engine> _random_engine;

  std::shared_ptr<Building> _building;

  bool nextStep();
};
