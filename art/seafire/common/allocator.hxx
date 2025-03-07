#ifndef art__seafire__common__allocator_hxx_
#define art__seafire__common__allocator_hxx_

#include <memory>
#include <set>

namespace art::seafire::common
{

  /// Implements a memory allocator keeping track of allocations.
  ///
  /// All allocations made through an allocator_t are valid for the
  /// lifetime of the allocator_t object.
  ///
  class allocator_t
  {
  public:
    allocator_t();

    allocator_t(allocator_t const&) = delete;
    allocator_t(allocator_t&&) = delete;

    template<typename T>
    T&
    alloc();

    template<typename T>
    T&
    alloc(T const&);

    template<typename T>
    T&
    alloc(T&&);

    template<typename T, typename... Args>
    T&
    alloc_emplace(Args&&...);

    allocator_t& operator=(allocator_t const&) = delete;
    allocator_t& operator=(allocator_t&&) = delete;

  private:
    struct allocation_t
    {
      allocation_t();

      allocation_t(allocation_t const&) = delete;
      allocation_t(allocation_t&&) = delete;

      virtual
      ~allocation_t() noexcept;

      allocation_t& operator=(allocation_t const&) = delete;
      allocation_t& operator=(allocation_t&&) = delete;

    };

    std::set<std::unique_ptr<allocation_t>> allocations_;

  };

} // namespace art::seafire::common

#include <art/seafire/common/allocator.txx>

#endif
