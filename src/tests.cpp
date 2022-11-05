#include <gtest/gtest.h>

#include "slau.h"

TEST(Slau, constructors) {
  Slau A, B, C;
  A.ReadFile("../data-samples/ex0.txt");
  B = A;
  C = std::move(A);
  Slau D{std::move(B)};
  Slau E(3);
  EXPECT_ANY_THROW(Slau F(0));
}

TEST(Slau, ReadFile) {
  Slau A;
  EXPECT_NO_THROW(A.ReadFile("../data-samples/test0.txt"));
  EXPECT_ANY_THROW(A.ReadFile("../data-samples/test1.txt"));
  EXPECT_NO_THROW(A.ReadFile("../data-samples/test2.txt"));
}

TEST(Slau, get_solution) {
  Slau A;
  A.ReadFile("../data-samples/ex1.txt");
  auto sol = A.get_solution();
  std::vector<double> exp{-11, 31};
  EXPECT_EQ(sol.size(), exp.size());
  for (unsigned i{}; i < sol.size(); i++) EXPECT_DOUBLE_EQ(sol[i], exp[i]);
}

TEST(Slau, CheckDet) {
  Slau A;
  A.ReadFile("../data-samples/test3.txt");
  EXPECT_ANY_THROW(auto sol = A.get_solution());
}

TEST(Slau, div_by_zero) {
  Slau A;
  A.ReadFile("../data-samples/test4.txt");
  EXPECT_NO_THROW(auto sol = A.get_solution());
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
