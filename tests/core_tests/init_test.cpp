#include <CppUTest/TestHarness.h>

TEST_GROUP(intergration)
{
    void setup()
   {
        auto& engine = Yokai::getInstance();
   }

   void teardown()
   {
      auto& engine = Yokai::getInstance();
      engine.Shutdown();
   }
};

TEST(intergration,tick)
{

};