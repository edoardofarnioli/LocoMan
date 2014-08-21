#include <gtest/gtest.h>
#include <LocoMan/CFLMM.h>
#include <yarp/sig/all.h>
#include <yarp/math/Math.h>
#include <cmath>
#define  s 1.0

using namespace yarp::math;
using namespace LocoMan;

namespace {

// The fixture for testing class JointLimits.
class testCFLMM : public ::testing::Test {
 protected:

  // You can remove any or all of the following functions if its body
  // is empty.

    testCFLMM() : cFLMM(NULL) {
    // You can do set-up work for each test here.
    cFLMM = new CFLMM();
  }

  virtual ~testCFLMM() {
    // You can do clean-up work that doesn't throw exceptions here.
      if(cFLMM) {
          delete cFLMM;
          cFLMM = NULL;
      }
  }

  // If the constructor and destructor are not enough for setting up
  // and cleaning up each test, you can define the following methods:

  virtual void SetUp() {
    // Code here will be called immediately after the constructor (right
    // before each test).

  }

  virtual void TearDown() {
    // Code here will be called immediately after each test (right
    // before the destructor).
  }

  // Objects declared here can be used by all tests in the test case for JointLimits.
  CFLMM* cFLMM;
};

TEST_F(testCFLMM, sizesAreCorrect) {
    
    EXPECT_EQ(0,0) << "Dummy Test!";
}

}  // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
