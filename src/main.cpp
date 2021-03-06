#include "Scenario.h"
#include "Simulator.h"
#include "Reporter.h"
#include <memory>

int main(int argc, char *argv[]) {
  auto scenarios = Scenario::Load("config.yaml");
  auto reporter = std::make_shared<Reporter>();

  for (auto scenario : *scenarios) {
    auto simulator = std::make_shared<Simulator>(scenario);
    simulator->run();
    reporter->generate(simulator);
  }

  reporter->generate();

  return 0;
}
