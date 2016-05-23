#include "Scenario.h"
#include "DispatcherType.h"
#include "CostFunctionType.h"
// #include "Direction.h"
// #include "Elevator.h"
// #include "Floor.h"
#include <glog/logging.h>
#include <gtest/gtest.h>
#include <yaml-cpp/yaml.h>
#include <string>

struct ScenarioTest : testing::Test {
  Scenario *s;
  ScenarioTest() {
    std::string config =
      "name: teste\n"
      "duration: 12345\n"
      "dispatcher: 2\n"
      "cost_function: 0 # dummy\n"
      "seed: 54TH7hboAG1iOsDIDhJp\n"
      "elevators: 3\n"
      "elevator_config:\n"
      "  capacity: 5\n"
      "floors:\n"
      "  - [ 1, 150 ]\n"
      "  - [ 2, 300 ]\n"
      "  - [ 3, 450 ]\n"
      "  - [ 4, 600 ]\n";

    YAML::Node node = YAML::Load(config);

    s = new Scenario(node);
  }

  virtual ~ScenarioTest() {}
};

TEST_F(ScenarioTest, Getters) {
  EXPECT_EQ("teste", s->getName());
  EXPECT_EQ(12345, s->getDuration());
  EXPECT_EQ(DispatcherType::NearestNeighbour, s->getDispatcherType());
  EXPECT_EQ(CostFunctionType::Dummy, s->getCostFunctionType());
  EXPECT_EQ("54TH7hboAG1iOsDIDhJp", s->getSeed());
  EXPECT_EQ(3, s->getElevators());
  EXPECT_EQ(5, s->getCapacity());
  EXPECT_EQ(4, s->getFloorCount());
  EXPECT_EQ(4, s->getFloors().size());
  EXPECT_EQ(1, s->getFloors()[0].first);
  EXPECT_EQ(150, s->getFloors()[0].second);
  EXPECT_EQ(2, s->getFloors()[1].first);
  EXPECT_EQ(300, s->getFloors()[1].second);
  EXPECT_EQ(3, s->getFloors()[2].first);
  EXPECT_EQ(450, s->getFloors()[2].second);
  EXPECT_EQ(4, s->getFloors()[3].first);
  EXPECT_EQ(600, s->getFloors()[3].second);
}
