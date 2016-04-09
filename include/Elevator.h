#pragma once

#include "Client.h"
#include "Direction.h"
#include "Event.h"
#include "Status.h"
#include <map>
#include <memory>
#include <queue>
#include <vector>

class Elevator {
public:
  Elevator(int number, int capacity, int floor);
  virtual ~Elevator();

  int getNumber() const;
  int getCapacity() const;
  int getLocation() const;
  int getDestination() const;
  Status getStatus() const;
  Direction getDirection() const;

  const std::shared_ptr<const std::vector<std::shared_ptr<const Client>>> getPassengers() const;
  int getAvailableCapacity() const;
  int getNextLocation() const;

  void setLocation(int location);
  void setDestination(int destination);
  void setDirection(Direction direction);
  void setStatus(Status status);

  std::shared_ptr<std::vector<std::shared_ptr<const Client>>> dropPassengersToCurrentLocation();
  void stopAtNextLocation();
  void addPassenger(std::shared_ptr<const Client> client);

  void start();
  void stop();
  void turn();
  void move();

private:
  const int _number;
  const int _capacity;
  int _location;
  int _destination;
  Status _status;
  Direction _direction;
  bool _stopAtNextLocation;
  std::shared_ptr<std::vector<std::shared_ptr<const Client>>> _passengers;
};
