#include "ps1_lib.h"

#include "gtest/gtest.h"

namespace {

struct Ps1Test : public testing::Test {};

TEST_F(Ps1Test, GetPs1) {
  EXPECT_EQ(GetPs1(), "ello");
}

}  // namespace