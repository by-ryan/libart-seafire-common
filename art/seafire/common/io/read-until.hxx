#ifndef art__seafire__common__io__read_until_hxx_
#define art__seafire__common__io__read_until_hxx_

#include <art/seafire/common/io/stream.hxx>

#include <functional>
#include <system_error>

#include <asio.hpp>

namespace art::seafire::common::io
{

  using match_condition_t = std::function<
    std::pair<char const*, bool>(char const*, char const*, std::error_code&)
  >;

  using read_until_handler_t = std::function<
    void(std::error_code, std::size_t)
  >;

  std::size_t
  read_until(stream_t&, asio::streambuf&, match_condition_t);

  std::size_t
  read_until(stream_t&,
             asio::streambuf&,
             match_condition_t,
             std::error_code&);

  void
  async_read_until(stream_t&,
                   asio::streambuf&,
                   match_condition_t,
                   read_until_handler_t);

} // namespace art::seafire::common::io

#endif
