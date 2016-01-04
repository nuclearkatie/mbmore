#include <gtest/gtest.h>

#include "behavior_functions.h"

#include "agent_tests.h"
#include "context.h"
#include "facility_tests.h"

namespace mbmore {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Should return True for even #s and False for odd #s
TEST(Behavior_Functions_Test, TestEveryX) {

  int interval = 2;
  int curr_time = 0;

  bool t0 = EveryXTimestep(curr_time, interval);
  curr_time++;
  bool t1 = EveryXTimestep(curr_time, interval);
  curr_time++;
  bool t2 = EveryXTimestep(curr_time, interval);

  EXPECT_TRUE(t0);
  EXPECT_FALSE(t1);
  EXPECT_EQ(t0, t2);
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Should return True about 1/freq times. For freq=2, should have ~equal
// number of True and False, but on a given instance can vary by 15% or
// more. Therefore, give it 3 tries to get within a reasonable tolerance.
TEST(Behavior_Functions_Test, TestEveryRandomX) {

  int freq = 2;
  int rng_seed = -1;

  double tol = 0.05;

  bool good = false;
  int ntries = 0;
  
  while ((good == false) and (ntries < 3)){
    double n_true = 0;
    double n_false = 0;
    for (int i = 0; i < 1000; i++) {
      bool res = EveryRandomXTimestep(freq, rng_seed);
      (res == true) ? (n_true++) : (n_false++);
    }
    
    ((n_true/n_false < 1.0 + tol) && (n_true/n_false > 1.0 - tol)) ?
      good = true : ntries++;
    std::cout << "T: " << n_true << "F: "<< n_false << std::endl;
    std::cout << "ntries: " << ntries << std::endl;
  }
  EXPECT_TRUE(good);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Mean and Standard deviation of a Normal Gaussian Distribution should be
// within 5% of the requested value.
TEST(Behavior_Functions_Test, TestNormalDist) {
  double mean = 10;
  double sigma = 1;
  double rng_seed = -1;
  double tol = 0.05;
  
  int array_size = 1000;
  std::vector<double> record(array_size);
  
  double sum = 0;
  for (int i = 0; i < array_size; i++) {
    record[i] = RNG_NormalDist(mean, sigma, rng_seed);
    sum += record[i];
  }

  double mu = sum / record.size();

  double accum = 0.0;
  for (int d = 0; d < record.size(); ++d) {
    accum += (record[d] - mu) * (record[d] - mu);
  };
  double stdev = std::sqrt(accum / (record.size() - 1)); 

  EXPECT_NEAR(mean/mu, 1.0, tol);
  EXPECT_NEAR(stdev/sigma, 1.0, tol);
  
}

} // namespace mbmore