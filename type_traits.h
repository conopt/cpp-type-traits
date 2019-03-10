#pragma once

#include <type_traits>
#include <functional>

#define DEFINE_CONCEPT(name, cond)             \
  template <typename>                          \
  auto name##Impl(...) -> std::false_type;     \
  template <typename T>                        \
  auto name##Impl(int) ->                      \
    std::enable_if_t<(cond), std::true_type>;  \
  template <typename T>                        \
  constexpr bool name =                        \
    decltype(name##Impl<T>(0))::value

#define CONVERTIBLE(expr, type) (std::is_convertible<decltype(expr), type>::value)

DEFINE_CONCEPT(Hashable, CONVERTIBLE(std::hash<T>()(std::declval<T>()), size_t));

DEFINE_CONCEPT(HasEqual, CONVERTIBLE(std::declval<T>() == std::declval<T>(), bool));

DEFINE_CONCEPT(HasKey, (std::is_same<typename T::key_type, typename T::key_type>::value));

DEFINE_CONCEPT(HasLess, CONVERTIBLE(std::less<T>()(std::declval<T>(), std::declval<T>()), bool));

#undef CONVERTIBLE
#undef DEFINE_CONCEPT

template <typename T>
constexpr bool IsHashMapKey = Hashable<T> && HasEqual<T>;

template <typename>
auto TryGetKeyImpl(...) -> void;

template <typename T>
auto TryGetKeyImpl(int) -> std::enable_if_t<HasKey<T>, typename T::key_type>;

template <typename T>
using TryGetKey = decltype(TryGetKeyImpl<T>(0));

template <typename T>
auto TryGetValueImpl(...) -> typename T::value_type;

template <typename T>
auto TryGetValueImpl(int) -> decltype(std::declval<typename T::value_type>().second);

template <typename T>
using TryGetValue = decltype(TryGetValueImpl<T>(0));

template <template <typename...> class T>
struct InstanceOfImpl {
  template <typename...>
  auto test(...) -> std::false_type;

  template <typename ...U>
  auto test(const T<U...>&) -> std::true_type;
};

// Determine whether I is an instantiation of template T
template <typename I, template <typename...> class T>
constexpr bool InstanceOf =
  decltype(std::declval<InstanceOfImpl<T>>().test(std::declval<I>()))::value;

template <bool, typename A, typename B>
struct enable_if_else { using type = B; };

template <typename A, typename B>
struct enable_if_else<true, A, B> { using type = A; };

template <bool Cond, typename A, typename B>
using enable_if_else_t = typename enable_if_else<Cond, A, B>::type;
