#include <art/seafire/common/io/diagnostics.hxx>

namespace art::seafire::common::io
{

  common::diagnostics_t::category_t const&
  io_category()
  {
    static common::diagnostics_t::category_t category{"io"};
    return category;
  }

} // namespace art::seafire::common::io
