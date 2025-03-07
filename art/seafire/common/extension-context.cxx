#include <art/seafire/common/extension-context.hxx>

namespace art::seafire::common
{

  void*
  extension_context_t::
  use(std::type_index const& key) const
  {
    auto it = extensions_.find(key);

    if (it == extensions_.end())
      throw extension_not_found_t{};

    return it->second;
  }

  void
  extension_context_t::
  extend(std::type_index const& key, void* ptr)
  {
    if (0 != extensions_.count(key))
      throw duplicate_extension_t{};

    if (!ptr)
      throw std::invalid_argument{"invalid pointer"};

    extensions_.emplace(key, ptr);
  }

  void
  extension_context_t::
  erase_extension(std::type_index const& key)
  {
    extensions_.erase(key);
  }

  extension_not_found_t::
  extension_not_found_t()
    : std::runtime_error{"extension not found"}
  {}

  duplicate_extension_t::
  duplicate_extension_t()
    : std::runtime_error{"extension already registered"}
  {}

} // namespace art::seafire::common
