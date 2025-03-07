#ifndef art__seafire__common__io__stream_hxx_
#define art__seafire__common__io__stream_hxx_

#include <art/seafire/common/io/buffer.hxx>

#include <asio.hpp>

#include <functional>
#include <system_error>

namespace art::seafire::common::io
{

  /// Abstract base class for stream.
  ///
  class stream_t
  {
  public:
    /// Non-blocking read handler type.
    ///
    using read_handler_t = std::function<void(std::error_code, std::size_t)>;

    /// Non-blocking write handler type.
    ///
    using write_handler_t = std::function<void(std::error_code, std::size_t)>;

    /// Non-blocking graceful close handler type.
    ///
    using graceful_close_handler_t = std::function<void()>;

    virtual
    ~stream_t() noexcept;

    /// Get the asio executor associated with this stream.
    ///
    virtual
    asio::any_io_executor const&
    get_executor() = 0;

    /// Cancel any pending non-blocking operations.
    ///
    virtual
    void
    cancel() = 0;

    /// Close this stream.
    ///
    virtual
    void
    close() = 0;

    /// Close this stream.
    ///
    virtual
    void
    close(std::error_code&) = 0;

    /// Perform a blocking graceful close of this stream.
    ///
    virtual
    void
    graceful_close() = 0;

    /// Initiate a non-blocking graceful close of this stream.
    ///
    virtual
    void
    async_graceful_close(graceful_close_handler_t) = 0;

    /// Perform a blocking read on this stream.
    ///
    virtual
    std::size_t
    read(mutable_buffer_t const&) = 0;

    /// Perform a blocking read on this stream.
    ///
    virtual
    std::size_t
    read(mutable_buffer_t const&, std::error_code&) = 0;

    /// Initiate a non-blocking read on this stream.
    ///
    virtual
    void
    async_read(mutable_buffer_t const&, read_handler_t) = 0;

    /// Perform a blocking write on this stream.
    ///
    virtual
    std::size_t
    write(const_buffer_t const&) = 0;

    /// Perform a blocking write on this stream.
    ///
    virtual
    std::size_t
    write(const_buffers_t const&) = 0;

    /// Initiate a non-block write on this stream.
    ///
    virtual
    std::size_t
    write(const_buffer_t const&, std::error_code&) = 0;

    /// Initiate a non-block write on this stream.
    ///
    virtual
    std::size_t
    write(const_buffers_t const&, std::error_code&) = 0;

    /// Initiate a non-blocking write on this stream.
    ///
    virtual
    void
    async_write(const_buffer_t const&, write_handler_t) = 0;

    /// Initiate a non-blocking write on this stream.
    ///
    virtual
    void
    async_write(const_buffers_t const&, write_handler_t) = 0;

  protected:
    stream_t();

    stream_t(stream_t const&) = delete;
    stream_t(stream_t&&) = delete;

    stream_t& operator=(stream_t const&) = delete;
    stream_t& operator=(stream_t&&) = delete;

  };

} // namespace art::seafire::common::io

#endif
