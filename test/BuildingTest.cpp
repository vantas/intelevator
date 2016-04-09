#include <glog/logging.h>
#include <gtest/gtest.h>
#include <iostream>
#include <memory>
#include <vector>

#include "Building.h"
#include "Elevator.h"
#include "Floor.h"
#include "Scenario.h"

#define MAX_LOG_LEVEL -100

using namespace std;

struct BuildingTest : testing::Test
{
  YAML::Node config;
  std::shared_ptr<Scenario> scenario;
  std::shared_ptr<Building> building;

  BuildingTest()
  {
    config = YAML::LoadFile("test_config.yaml")["scenarios"][0];
    scenario = std::shared_ptr<Scenario>(new Scenario(config));
    building = scenario->createBuilding();
  }

  virtual ~BuildingTest()
  {}
};

TEST_F(BuildingTest, GetFloors_ReturnsRightSize)
{
  EXPECT_EQ(config["population"].size(), building->getFloors()->size());
}

TEST_F(BuildingTest, GetElevators_ReturnsRightSize)
{
  EXPECT_EQ(config["elevators"].as<int>(), building->getElevators()->size());
}

TEST_F(BuildingTest, VerifyFloors)
{
  int i = 0;
  for (auto f : *building->getFloors())
  {
    EXPECT_EQ(f->getNumber(), i++);
  }
}

TEST_F(BuildingTest, VerifyElevators)
{
  int i = 0;
  for (auto e : *building->getElevators())
  {
    EXPECT_EQ(e->getNumber(), i++);
  }
}

TEST_F(BuildingTest, GetLocation_NewBuilding_ReturnsLobby)
{
  auto lobby = building->getFloor(0);
  for (auto e : *building->getElevators())
  {
    EXPECT_EQ(lobby->getNumber(), e->getLocation());
  }
}
