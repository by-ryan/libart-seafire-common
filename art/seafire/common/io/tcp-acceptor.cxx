#include <art/seafire/common/io/tcp-acceptor.hxx>
#include <art/seafire/common/io/tcp-socket.hxx>


namespace art::seafire::common::io
{

  tcp_acceptor_t::
  tcp_acceptor_t(asio::io_context& io_context,
                 asio::ip::tcp::endpoint const& endpoint)
    : acceptor_{io_context, endpoint}
  {}

  tcp_acceptor_t::
  ~tcp_acceptor_t() noexcept = default;

  asio::any_io_executor const&
  tcp_acceptor_t::
  get_executor()
  {
    return acceptor_.get_executor();
  }

  void
  tcp_acceptor_t::
  async_accept(accept_handler_t handler)
  {
    auto bound = [handler](std::error_code const& ec, asio::ip::tcp::socket socket)
    {
      handler(ec, std::make_unique<tcp_socket_t>(std::move(socket)));
    };

    acceptor_.async_accept(bound);
  }

} // namespace art::seafire::common::io
