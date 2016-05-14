#pragma once

#include <memory>
#include <yaml-cpp/yaml.h>
#include "CostFunctionType.h"
#include "DispatcherType.h"

class Scenario {
public:
  Scenario(YAML::Node scenario);
  virtual ~Scenario();

  static std::shared_ptr<std::vector<std::shared_ptr<const Scenario>>> Load(std::string file);

  const std::string getName() const;
  const int getDuration() const;
  const int getElevators() const;
  const int getCapacity() const;
  const int getFloorCount() const;
  const DispatcherType getDispatcherType() const;
  const CostFunctionType getCostFunctionType() const;
  const std::vector<std::pair<int, float>> getFloors() const;
  const std::string getSeed() const;

private:
  const std::string _name;
  const int _duration;
  const int _elevators;
  const int _capacity;
  const int _floorCount;
  const DispatcherType _dispatcherType;
  const CostFunctionType _costFunctionType;
  const std::string _seed;
  std::vector<std::pair<int, float>> _floors;
};