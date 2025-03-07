#include <art/seafire/common/io/error.hxx>

namespace art::seafire::common::io
{

  std::error_code
  make_error_code(error_t e)
  {
    static
    struct : std::error_category
    {
      char const* name() const noexcept override
      {
        return "seafire.common.io";
      }

      std::string message(int e) const override
      {
        switch (static_cast<error_t>(e)) {
          case error_t::unknown: return "unknown error";
          case error_t::read_until_buffer_overflow: return "buffer overflow";
        }

        return "(unrecognized error)";
      }
    } category;

    return {static_cast<int>(e), category};
  }

} // namespace art::seafire::common::io
