#ifndef art__seafire__common__io__acceptor_hxx_
#define art__seafire__common__io__acceptor_hxx_

#include <art/seafire/common/io/stream.hxx>

#include <asio.hpp>

#include <functional>
#include <memory>

namespace art::seafire::common::io
{

  /// Abstract base class for acceptors.
  ///
  class acceptor_t
  {
  public:
    /// Non-blocking accept handler type.
    ///
    using accept_handler_t = std::function<
      void(std::error_code, std::unique_ptr<stream_t>)
    >;

    virtual
    ~acceptor_t() noexcept;

    virtual
    asio::any_io_executor const&
    get_executor() = 0;

    /// Initiate a non-blocking accept of a new stream.
    ///
    virtual
    void
    async_accept(accept_handler_t) = 0;

  protected:
    acceptor_t();

    acceptor_t(acceptor_t const&) = delete;
    acceptor_t(acceptor_t&&) = delete;

    acceptor_t& operator=(acceptor_t const&) = delete;
    acceptor_t& operator=(acceptor_t&&) = delete;

  };

} // namespace art::seafire::common::io

#endif
