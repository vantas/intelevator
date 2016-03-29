#include <gtest/gtest.h>
#include <memory>
#include "ClientArrival.h"

struct ClientArrivalTest : testing::Test
{
  int partySize;
  float arrivalTime;
  const std::shared_ptr<const Floor> destination;
  const std::shared_ptr<const Client> client;
  const std::shared_ptr<const Floor> floor;
  const std::shared_ptr<const ClientArrival> clientArrival;

  ClientArrivalTest()
  : partySize(1)
  , arrivalTime(10)
  , destination(new Floor(0))
  , client(new Client(partySize, arrivalTime, destination))
  , floor(new Floor(1))
  , clientArrival(new ClientArrival(arrivalTime, client, floor))
  {}

  virtual ~ClientArrivalTest()
  {}
};

TEST_F(ClientArrivalTest, GetClient_ReturnsClient)
{
  EXPECT_EQ(clientArrival->getClient(), client);
}
