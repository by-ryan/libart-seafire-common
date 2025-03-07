#include <art/seafire/common/io/tcp-socket.hxx>

namespace art::seafire::common::io
{

  /// Construct a new TCP/IP socket from an asio socket.
  ///
  tcp_socket_t::
  tcp_socket_t(asio::ip::tcp::socket socket)
    : socket_{std::move(socket)}
  {}

  tcp_socket_t::
  ~tcp_socket_t() noexcept = default;

  asio::any_io_executor const&
  tcp_socket_t::
  get_executor()
  {
    return socket_.get_executor();
  }

  void
  tcp_socket_t::
  cancel()
  {
    socket_.cancel();
  }

  void
  tcp_socket_t::
  close()
  {
    socket_.close();
  }

  void
  tcp_socket_t::
  close(std::error_code& ec)
  {
    socket_.close(ec);
  }

  void
  tcp_socket_t::
  graceful_close()
  {
    try {
      socket_.shutdown(asio::ip::tcp::socket::shutdown_send);
      socket_.read_some(buffer(throwaway_));
    }
    catch (...) {
      // Ignore errors during shutdown/close.
      //
    }
  }

  void
  tcp_socket_t::
  async_graceful_close(graceful_close_handler_t handler)
  {
    std::error_code ec;
    socket_.shutdown(asio::ip::tcp::socket::shutdown_send, ec);

    if (ec) {
      auto bound = [handler]()
      {
        handler();
      };

      asio::post(get_executor(), bound);
      return;
    }

    auto bound = [handler](std::error_code const&, std::size_t)
    {
      // Errors are ignored during graceful shutdown/close, so we
      // don't pass anything to the handler.
      //
      handler();
    };

    socket_.async_read_some(buffer(throwaway_), bound);
  }

  std::size_t
  tcp_socket_t::
  read(mutable_buffer_t const& buffer)
  {
    return socket_.read_some(buffer);
  }

  std::size_t
  tcp_socket_t::
  read(mutable_buffer_t const& buffer, std::error_code& ec)
  {
    return socket_.read_some(buffer, ec);
  }

  void
  tcp_socket_t::
  async_read(mutable_buffer_t const& buffer, read_handler_t handler)
  {
    return socket_.async_read_some(buffer, handler);
  }

  std::size_t
  tcp_socket_t::
  write(const_buffer_t const& buffer)
  {
    return asio::write(socket_, buffer);
  }

  std::size_t
  tcp_socket_t::
  write(const_buffers_t const& buffers)
  {
    return asio::write(socket_, buffers);
  }

  std::size_t
  tcp_socket_t::
  write(const_buffer_t const& buffer, std::error_code& ec)
  {
    return asio::write(socket_, buffer, ec);
  }

  std::size_t
  tcp_socket_t::
  write(const_buffers_t const& buffers, std::error_code& ec)
  {
    return asio::write(socket_, buffers, ec);
  }

  void
  tcp_socket_t::
  async_write(const_buffer_t const& buffer, write_handler_t handler)
  {
    asio::async_write(socket_, buffer, handler);
  }

  void
  tcp_socket_t::
  async_write(const_buffers_t const& buffers, write_handler_t handler)
  {
    asio::async_write(socket_, buffers, handler);
  }

} // namespace art::seafire::common::io
