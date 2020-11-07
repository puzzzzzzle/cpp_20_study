//
// Created by tao on 19-1-17.
//
#include "common_includes.h"
#include "lib_coro.h"

TEST(test_test, 1) {
  LOG_INFO("aha start")
  ASSERT_EQ(1, 1);
}
coro::task<void> coro_void() { co_return; }
TEST(coro_void, 1) {
  auto ret = coro_void();
  ret.resume();
}
coro::task<int> coro_int() {
  INFO("coro wait ")
  sleep(1);
  INFO("coro end ")
  co_return 42;
}
TEST(coro_int, 1) {
  INFO("start ")
  auto ret = coro_int();
  ret.resume();
  INFO("coro return " << ret.handle().promise().result())
}
int main(int argc, char **argv) {
  int iRet = 0;
  iRet = beforeRun();
  if (iRet) {
    std::cerr << "init fail with " << iRet << std::endl;
  }
  testing::InitGoogleTest(&argc, argv);
  iRet = RUN_ALL_TESTS();
  return iRet;
}