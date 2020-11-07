#include "common_includes.h"
#include "has_member.h"


HAS_MEMBER_VARIABLE_BASE(val)

HAS_MEMBER_VOID_FUNC_BASE(_void,foo)
HAS_MEMBER_VOID_FUNC_BASE(_void,test)
HAS_MEMBER_VOID_FUNC_BASE(_void,get_val)
HAS_MEMBER_FUNC_ARGS_BASE(_1int, set_val, 1)
HAS_MEMBER_FUNC_ARGS_BASE(_2int, set_val, 1, 1)
HAS_MEMBER_FUNC_ARGS_BASE(_1long, set_long, 1l)

CALL_IF_EXISTS_FUNC(_1int, set_val, int, int)
CALL_IF_EXISTS_FUNC(_1long, set_long, void, long)
CALL_IF_EXISTS_FUNC_VOID(_void, foo, void)

struct myStruct {
  public:
  void foo() { std::cout << "hello" << std::endl; }

  private:
  int val{};

  public:
  int set_val(int t) {
    val = t;
    return val;
  }
  int set_val(int t, int) {
    val = t;
    return val;
  }
  void set_long(long t) { val = t; }

  int get_val() { return val; }
};

struct another {
  public:
  void test() { std::cout << "test" << std::endl; }
  void set_long(int t) { val = t; }

  public:
  int val{};
};

TEST(test, 1) {
#define HAS_MEMBER_TEST(class_name, name)             \
  INFO(#class_name << " has member " << #name << "\t" \
                   << _HasMember_##name##_void<class_name>::value)
  HAS_MEMBER_TEST(myStruct, foo)
  HAS_MEMBER_TEST(another, foo)

  HAS_MEMBER_TEST(myStruct, test)
  HAS_MEMBER_TEST(another, test)

  HAS_MEMBER_TEST(myStruct, get_val)
  HAS_MEMBER_TEST(another, get_val)

  INFO("func()  mystruct  get_val " << _HasMember_get_val_void<myStruct>::value)
  INFO("func() another  get_val " << _HasMember_get_val_void<another>::value)
  INFO("func(long)  mystruct  get_val "
       << _HasMember_get_val_void<myStruct>::value)
  INFO("func(long) another  get_val "
       << _HasMember_get_val_void<another>::value)

  INFO("func(int) mystruct  set_val int "
       << _HasMember_set_val_1int<myStruct>::value)
  INFO("func(int,int) mystruct  set_val  2 int "
       << _HasMember_set_val_2int<myStruct>::value)

  INFO("private val  myStruct  val " << _HasMemberVar_val<myStruct>::value)
  INFO("publis val  another  val " << _HasMemberVar_val<another>::value)

  myStruct m{};
  another a{};
  m.set_val(42);

  INFO("!!!!!!!!!! myStruct  " << CALL_set_val_1int(m, 42))
  INFO("!!!!!!!!!! another   " << CALL_set_val_1int(a, 42))
  CALL_set_long_1long_no_return(m, 42);
  CALL_set_long_1long_no_return(a, 42);
  //  HAS_MEMBER_TEST(myStruct, set_val)
  //  HAS_MEMBER_TEST(another, set_val)
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