#include "basic_sanity.hpp"
#include "depth_and_balance.hpp"
#include "removing_keys.hpp"

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}