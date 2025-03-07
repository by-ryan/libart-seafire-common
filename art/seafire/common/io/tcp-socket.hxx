#ifndef art__seafire__common__io__tcp_socket_hxx_
#define art__seafire__common__io__tcp_socket_hxx_

#include <art/seafire/common/io/buffer.hxx>
#include <art/seafire/common/io/stream.hxx>

#include <asio.hpp>

namespace art::seafire::common::io
{

  /// Implements a TCP/IP socket.
  ///
  class tcp_socket_t
    : public stream_t
  {
  public:
    explicit
    tcp_socket_t(asio::ip::tcp::socket);

    tcp_socket_t(tcp_socket_t const&) = delete;
    tcp_socket_t(tcp_socket_t&&) = delete;

    ~tcp_socket_t() noexcept override;

    asio::any_io_executor const&
    get_executor() override;

    void
    cancel() override;

    void
    close() override;

    void
    close(std::error_code&) override;

    void
    graceful_close() override;

    void
    async_graceful_close(graceful_close_handler_t) override;

    std::size_t
    read(mutable_buffer_t const&) override;

    std::size_t
    read(mutable_buffer_t const&, std::error_code&) override;

    void
    async_read(mutable_buffer_t const&, read_handler_t) override;

    std::size_t
    write(const_buffer_t const&) override;

    std::size_t
    write(const_buffers_t const&) override;

    std::size_t
    write(const_buffer_t const&, std::error_code&) override;

    std::size_t
    write(const_buffers_t const&, std::error_code&) override;

    void
    async_write(const_buffer_t const&, write_handler_t) override;

    void
    async_write(const_buffers_t const&, write_handler_t) override;

    tcp_socket_t& operator=(tcp_socket_t const&) = delete;
    tcp_socket_t& operator=(tcp_socket_t&&) = delete;

  private:
    asio::ip::tcp::socket socket_;
    char throwaway_[1];

  };

} // namespace art::seafire::common::io

#endif
