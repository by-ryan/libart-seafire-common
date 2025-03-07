#ifndef art__seafire__common__io__error_hxx_
#define art__seafire__common__io__error_hxx_

#include <system_error>
#include <type_traits>

namespace art::seafire::common::io
{

  /// Common error codes.
  ///
  enum class error_t
  {
    /// Represents an unknown error.
    ///
    unknown = 1,

    read_until_buffer_overflow

  };

  std::error_code
  make_error_code(error_t);

} // namespace art::seafire::common::io

namespace std
{

  template<>
  struct is_error_code_enum<::art::seafire::common::io::error_t>
    : true_type
  {};

} // namespace std

#endif
