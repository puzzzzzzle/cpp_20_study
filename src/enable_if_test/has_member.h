/************************************************
 * @author khalidzhang
 * @email khalidzhang@tencent.com
 * @desc 萃取类中是否有某个函数/变量, 支持参数但是类型时严格的, 不会自动转换
 * 先使用宏定义出模板函数
 * 再使用模板函数来判断
 *
 * 也可以实现在判断函数是否存在后, 进行调用
 * @time 2020/11/7
 * @file ClassTraits.h
 * @version
 * version        author            desc
 * 1.0            khalidzhang       create
 ************************************************/
#pragma once
#define HAS_MEMBER_VOID_FUNC_BASE(prefix, name)                          \
  template <typename T>                                                  \
  struct _HasMember_##name##prefix {                                     \
private:                                                                 \
    template <typename U>                                                \
    static auto Check(int)                                               \
        -> decltype(std::declval<U>().name(), std::true_type());         \
    template <typename U>                                                \
    static std::false_type Check(...);                                   \
                                                                         \
public:                                                                  \
    enum {                                                               \
      value = std::is_same<decltype(Check<T>(0)), std::true_type>::value \
    };                                                                   \
  };

#define HAS_MEMBER_FUNC_ARGS_BASE(prefix, name, arg...)                  \
  template <typename T>                                                  \
  struct _HasMember_##name##prefix {                                     \
private:                                                                 \
    template <typename U>                                                \
    static auto Check(int)                                               \
        -> decltype(std::declval<U>().name(arg), std::true_type());      \
    template <typename U>                                                \
    static std::false_type Check(...);                                   \
                                                                         \
public:                                                                  \
    enum {                                                               \
      value = std::is_same<decltype(Check<T>(0)), std::true_type>::value \
    };                                                                   \
  };
#define HAS_MEMBER_VARIABLE_BASE(name)                                   \
  template <typename T>                                                  \
  struct _HasMemberVar_##name {                                          \
private:                                                                 \
    template <typename U>                                                \
    static auto Check(int)                                               \
        -> decltype(std::declval<U>().name, std::true_type());           \
    template <typename U>                                                \
    static std::false_type Check(...);                                   \
                                                                         \
public:                                                                  \
    enum {                                                               \
      value = std::is_same<decltype(Check<T>(0)), std::true_type>::value \
    };                                                                   \
  };
#define CALL_IF_EXISTS_FUNC(prefix, name, ret, Arg)                         \
  template <typename T>                                                     \
  typename std::enable_if<_HasMember_##name##prefix<T>::value, ret>::type   \
      CALL_##name##prefix(T &para, Arg arg) {                               \
    return para.name(arg);                                                  \
  }                                                                         \
  template <typename T>                                                     \
  typename std::enable_if<!_HasMember_##name##prefix<T>::value, ret>::type  \
      CALL_##name##prefix(T &para, Arg arg) {                               \
    return {};                                                              \
  }                                                                         \
  template <typename T>                                                     \
  typename std::enable_if<_HasMember_##name##prefix<T>::value, void>::type  \
      CALL_##name##prefix##_no_return(T &para, Arg arg) {                   \
    para.name(arg);                                                         \
  }                                                                         \
  template <typename T>                                                     \
  typename std::enable_if<!_HasMember_##name##prefix<T>::value, void>::type \
      CALL_##name##prefix##_no_return(T &para, Arg arg) {}

#define CALL_IF_EXISTS_FUNC_VOID(prefix, name, ret)                         \
  template <typename T>                                                     \
  typename std::enable_if<_HasMember_##name##prefix<T>::value, ret>::type   \
      CALL_##name##prefix##_void(T &para) {                                   \
    return para.name();                                                     \
  }                                                                         \
  template <typename T>                                                     \
  typename std::enable_if<!_HasMember_##name##prefix<T>::value, ret>::type  \
      CALL_##name##prefix##_void(T &para) {                                   \
    return {};                                                              \
  }                                                                         \
  template <typename T>                                                     \
  typename std::enable_if<_HasMember_##name##prefix<T>::value, void>::type  \
      CALL_##name##prefix##_no_return_void(T &para) {                       \
    para.name();                                                            \
  }                                                                         \
  template <typename T>                                                     \
  typename std::enable_if<!_HasMember_##name##prefix<T>::value, void>::type \
      CALL_##name##prefix##_no_return_void(T &para) {}
