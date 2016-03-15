#include <gtest/gtest.h>

#include "Config.h"
#include <sstream>

struct ConfigTest : testing::Test
{
  Config* config;

  ConfigTest()
  {
    config = new Config();
  }

  virtual ~ConfigTest()
  {
    delete config;
  }
};

// Config::from_file
TEST_F(ConfigTest, FromFile_Initializes)
{
  std::string str =
    "floors=4\n"
    "elevators=2\n"
    "maxLoad=150\n"
    "duration=20.0\n"
    "title=simple\n"
    "seed=666";

  std::istringstream sstream(str);

  config->fromFile(sstream);
  EXPECT_EQ(config->_floors, 4);
  EXPECT_EQ(config->_elevators, 2);
  EXPECT_EQ(config->_maxLoad, 150);
  EXPECT_EQ(config->_duration, 20.0);
  EXPECT_EQ(config->_title, "simple");
  EXPECT_EQ(config->_seed, 666);
}
