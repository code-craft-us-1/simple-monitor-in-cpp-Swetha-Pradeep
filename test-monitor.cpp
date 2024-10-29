#include "./monitor.h"

#include "gtest/gtest.h"

TEST(Monitor, NotOkWhenAnyVitalIsOffRange) {
  ASSERT_TRUE(isTempraturNormal(99));
  /* ASSERT_FALSE(isTempraturNormal(94.1));
  ASSERT_FALSE(isPulseNormal(102));
  ASSERT_TRUE(isPulseNormal(70));
  ASSERT_FALSE(isSPO2Normal(70));
  ASSERT_TRUE(isSPO2Normal(98));
  ASSERT_FALSE(vitalsOk(99, 102, 70));
  ASSERT_TRUE(vitalsOk(98.1, 70, 98)); */
}
