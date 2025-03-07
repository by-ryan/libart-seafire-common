#include <art/seafire/common/allocator.hxx>

namespace art::seafire::common
{

  allocator_t::
  allocator_t() = default;

  allocator_t::allocation_t::
  allocation_t() = default;

  allocator_t::allocation_t::
  ~allocation_t() noexcept = default;

} // namespace art::seafire::common
