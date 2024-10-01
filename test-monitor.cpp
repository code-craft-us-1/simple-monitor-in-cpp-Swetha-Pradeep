#include "./monitor.h"

#include "gtest/gtest.h"

TEST(Monitor, NotOkWhenAnyVitalIsOffRange) {
  ASSERT_TRUE(checkTemprature(99));
  ASSERT_FALSE(checkTemprature(94.1));
  ASSERT_FALSE(checkPulserate(102));
  ASSERT_TRUE(checkPulserate(70));
  ASSERT_FALSE(checkSPO2(70));
  ASSERT_TRUE(checkSPO2(98));
  ASSERT_FALSE(vitalsOk(99, 102, 70));
  ASSERT_TRUE(vitalsOk(98.1, 70, 98));
}
