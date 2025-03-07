#ifndef art__seafire__common__io__tcp_acceptor_hxx_
#define art__seafire__common__io__tcp_acceptor_hxx_

#include <art/seafire/common/diagnostics.hxx>

#include <art/seafire/common/io/acceptor.hxx>

#include <asio.hpp>

namespace art::seafire::common::io
{

  /// Implements an tcp acceptor.
  ///
  class tcp_acceptor_t
    : public acceptor_t
  {
  public:
    tcp_acceptor_t(asio::io_context&,
                   asio::ip::tcp::endpoint const&);

    tcp_acceptor_t(tcp_acceptor_t const&) = delete;
    tcp_acceptor_t(tcp_acceptor_t&&) = delete;

    ~tcp_acceptor_t() noexcept override;

    asio::any_io_executor const&
    get_executor() override;

    void
    async_accept(accept_handler_t) override;

    tcp_acceptor_t& operator=(tcp_acceptor_t const&) = delete;
    tcp_acceptor_t& operator=(tcp_acceptor_t&&) = delete;

  private:
    asio::ip::tcp::acceptor acceptor_;

  };

} // namespace art::seafire::common::io

#endif
