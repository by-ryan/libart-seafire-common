#ifndef art__seafire__common__extension_context_hxx_
#define art__seafire__common__extension_context_hxx_

#include <map>
#include <stdexcept>
#include <typeindex>

namespace art::seafire::common
{

  /// Implements a context tracking extensions.
  ///
  /// Ownership of registered extensions is not assumed.
  ///
  class extension_context_t
  {
  public:
    template<typename E>
    E&
    use();

    template<typename E>
    E const&
    use() const;

    template<typename E>
    E&
    extend(E* ptr);

    template<typename E>
    void
    erase();

  private:
    void*
    use(std::type_index const& key) const;

    void
    extend(std::type_index const& key, void* ptr);

    void
    erase_extension(std::type_index const& key);

    std::map<std::type_index, void*> extensions_;

  };

  class extension_not_found_t
    : public std::runtime_error
  {
  public:
    extension_not_found_t();

  };

  class duplicate_extension_t
    : public std::runtime_error
  {
  public:
    duplicate_extension_t();

  };

  /// Provides extending an extension context using RAII.
  ///
  template<typename E>
  class extend_t
  {
  public:
    using extension_type = typename std::decay_t<E>;

    extend_t(extension_context_t&, extension_type&);

    extend_t(extend_t const&) = delete;
    extend_t(extend_t&&) = delete;

    ~extend_t() noexcept;

    extend_t& operator=(extend_t const&) = delete;
    extend_t& operator=(extend_t&&) = delete;

  private:
    extension_context_t& target_;

  };

} // namespace art::seafire::common

#include <art/seafire/common/extension-context.txx>

#endif
