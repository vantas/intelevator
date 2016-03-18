#pragma once

#include <list>
#include <map>
#include <memory>
#include <set>
#include "Config.h"
#include "EventObserver.h"

class Elevator; // forward declaration
class Floor;    // forward declaration

class Building : public EventObserver
{
public:
  Building(const std::shared_ptr<const Config> config);
  virtual ~Building();

  void build();
  void notify(const std::shared_ptr<const Event> event) const;

  const std::shared_ptr<const Config> getConfig() const;

  void setLocation(std::shared_ptr<const Elevator> elevator, std::shared_ptr<const Floor> location);
  const std::shared_ptr<const Floor> getLocation(std::shared_ptr<const Elevator> elevator);
  const std::list<std::shared_ptr<const Elevator>>& getElevators() const;
  const std::list<std::shared_ptr<const Floor>>& getFloors() const;

private:
  const std::shared_ptr<const Config> _config;
  std::map<std::shared_ptr<const Elevator>, std::shared_ptr<const Floor>> _locations;
  std::list<std::shared_ptr<const Elevator>> _elevators;
  std::list<std::shared_ptr<const Floor>> _floors;
};
