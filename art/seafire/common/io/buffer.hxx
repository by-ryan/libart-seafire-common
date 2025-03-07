#ifndef art__seafire__common__io__buffer_hxx_
#define art__seafire__common__io__buffer_hxx_

#include <asio.hpp>

#include <vector>

namespace art::seafire::common::io
{

  using const_buffer_t = asio::const_buffer;
  using const_buffers_t = std::vector<const_buffer_t>;

  using mutable_buffer_t = asio::mutable_buffer;
  using mutable_buffers_t = std::vector<mutable_buffer_t>;

  using asio::buffer;
  using asio::buffer_size;
  using asio::buffer_copy;

} // namespace art::seafire::common::io

#endif
