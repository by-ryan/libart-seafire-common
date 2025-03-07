#ifndef art__seafire__common__traits_hxx_
#define art__seafire__common__traits_hxx_

#include <optional>
#include <tuple>
#include <type_traits>

namespace art::seafire::common::traits
{

  // is_optional
  //

  template<typename T>
  struct is_optional
    : std::false_type
  {};

  template<typename T>
  struct is_optional<std::optional<T>>
    : std::true_type
  {};

  template<typename T>
  constexpr bool is_optional_v{is_optional<T>::value};

  // remove_optional
  //

  template<typename T>
  struct remove_optional
  {
    using type = T;
  };

  template<typename T>
  struct remove_optional<std::optional<T>>
  {
    using type = T;
  };

  template<typename T>
  using remove_optional_t = remove_optional<T>::type;

  // add_optional
  //

  template<typename T>
  std::optional<remove_optional_t<T>>
  add_optional(remove_optional<T>&& non_optional)
  {
    return std::optional<remove_optional<T>>{non_optional};
  }

  // function_traits
  //

  template<typename>
  struct function_traits;

  template<typename Ret, typename... Args>
  struct function_traits<Ret(Args...)>
  {
    static constexpr std::size_t arity = sizeof...(Args);
    using return_type = std::decay_t<Ret>;
    using argument_tuple = std::tuple<std::decay_t<Args>...>;
  };

  template<typename Ret, typename Class, typename... Args>
  struct function_traits<Ret (Class::*)(Args...)>
  {
    static constexpr std::size_t arity = sizeof...(Args);
    using return_type = std::decay_t<Ret>;
    using class_type = Class;
    using argument_tuple = std::tuple<std::decay_t<Args>...>;
  };

  template<typename Ret, typename Class, typename... Args>
  struct function_traits<Ret (Class::*)(Args...) const>
  {
    static constexpr std::size_t arity = sizeof...(Args);
    using return_type = std::decay_t<Ret>;
    using class_type = Class;
    using argument_tuple = std::tuple<std::decay_t<Args>...>;
  };

  template<typename Ret, typename... Args>
  struct function_traits<Ret(*)(Args...)>
  {
    static constexpr std::size_t arity = sizeof...(Args);
    using return_type = std::decay_t<Ret>;
    using argument_tuple = std::tuple<std::decay_t<Args>...>;
  };

  // return_type_t
  //

  template<typename F>
  using return_type_t = typename function_traits<F>::return_type;

  // first_arg
  //

  template<typename F>
  struct first_arg
  {
    using function_traits = traits::function_traits<F>;
    using type = std::tuple_element_t<0, typename function_traits::argument_tuple>;
  };

  template<typename F>
  using first_arg_t = first_arg<F>::type;

  // function_arg_n
  //

  template<
    typename F,
    std::size_t arg,
    std::size_t arity = function_traits<F>::arity
  >
  struct function_arg_n;

  template<
    typename F,
    std::size_t arg
  >
  struct function_arg_n<F, arg, 0>
  {
    using function_traits = traits::function_traits<F>;
    using type = void;
  };

  template<
    typename F,
    std::size_t arg
  >
  struct function_arg_n<F, arg, 1>
  {
    using function_traits = traits::function_traits<F>;
    using type = std::tuple_element_t<arg, typename function_traits::argument_tuple>;
  };

  template<
    typename F,
    std::size_t arg
  >
  struct function_arg_n<F, arg, 2>
  {
    using function_traits = traits::function_traits<F>;
    using type = std::tuple_element_t<arg, typename function_traits::argument_tuple>;
  };

  template<
    typename F,
    std::size_t arg
  >
  using function_arg_n_t = function_arg_n<F, arg>::type;

} // namespace art::seafire::common::traits

#endif
