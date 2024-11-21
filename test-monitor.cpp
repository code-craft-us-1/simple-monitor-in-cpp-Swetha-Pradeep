#include "./monitor.h"

#include "gtest/gtest.h"

TEST(Monitor, NotOkWhenAnyVitalIsOffRange) {
 
  ASSERT_TRUE(isTempratureNormal(99,"English"));
  ASSERT_FALSE(isTempratureNormal(94.1,"English"));
  ASSERT_FALSE(isPulseNormal(102,"English"));
  ASSERT_TRUE(isPulseNormal(70,"English"));
  ASSERT_FALSE(isSPo2Normal(70,"English"));
  ASSERT_TRUE(isSPo2Normal(98,"English"));
  ASSERT_FALSE(vitalsOk(99, 102, 70,"English"));
  ASSERT_TRUE(vitalsOk(98.1, 70, 98,"English")); 
}
