#include <art/seafire/common/io/read-until.hxx>

#include <art/seafire/common/io/error.hxx>

namespace art::seafire::common::io
{

  std::size_t
  read_until(stream_t& s, asio::streambuf& b, match_condition_t m)
  {
    std::error_code ec;
    auto n = read_until(s, b, m, ec);

    if (ec) {
      throw std::system_error{ec};
    }

    return n;
  }

  std::size_t
  read_until(stream_t& s,
             asio::streambuf& b,
             match_condition_t m,
             std::error_code& ec)
  {
    for (;;) {
      // search for a match.
      //
      auto begin = static_cast<char const*>(b.data().data());
      auto result = m(begin, begin + b.data().size(), ec);

      if (ec) {
        return 0;
      }

      if (result.second) {
        return result.first - begin;
      }

      // bail out if buffer is already full.
      //
      if (b.size() == b.max_size()) {
        ec = make_error_code(error_t::read_until_buffer_overflow);
        return 0;
      }

      // read more data.
      //
      auto bytes_to_read = std::min<std::size_t>(
        std::max<std::size_t>(  512, b.capacity() - b.size()),
        std::min<std::size_t>(65536, b.max_size() - b.size())
      );

      auto n = s.read(b.prepare(bytes_to_read), ec);
      b.commit(n);

      if (ec) {
        return 0;
      }
    }
  }

  void
  async_read_until(stream_t& s,
                   asio::streambuf& b,
                   match_condition_t m,
                   read_until_handler_t h)
  {
    struct operation_t
    {
      stream_t& s;
      asio::streambuf& b;
      match_condition_t match;
      read_until_handler_t handler;

      void
      operator()(std::error_code const& ec,
                 std::size_t n,
                 bool start = false)
      {
        if (ec || (!start && n == 0)) {
          handler(ec, 0);
          return;
        }

        b.commit(n);

        // search for a match.
        //
        auto begin = static_cast<char const*>(b.data().data());

        std::error_code match_ec;
        auto result = match(begin, begin + b.data().size(), match_ec);

        if (match_ec) {
          handler(match_ec, 0);
          return;
        }

        if (result.second) {
          handler({}, result.first - begin);
          return;
        }

        if (b.size() == b.max_size()) {
          handler(make_error_code(error_t::read_until_buffer_overflow), 0);
          return;
        }

        // read more data.
        //
        auto bytes_to_read = std::min<std::size_t>(
          std::max<std::size_t>(  512, b.capacity() - b.size()),
          std::min<std::size_t>(65536, b.max_size() - b.size())
        );

        s.async_read(b.prepare(bytes_to_read), std::move(*this));
      }

    };

    auto init = [&s, &b, m, h]
    {
      operation_t{s, b, m, h}({}, 0, true);
    };

    asio::post(s.get_executor(), init);
  }

} // namespace art::seafire::common::io
