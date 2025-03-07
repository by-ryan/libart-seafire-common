namespace art::seafire::common
{

  /// Use an extension of type E.
  ///
  template<typename E>
  E&
  extension_context_t::
  use()
  {
    static std::type_index const key{typeid(E)};
    return *(static_cast<E*>(use(key)));
  }

  /// Use an extension of type E.
  ///
  template<typename E>
  E const&
  extension_context_t::
  use() const
  {
    static std::type_index const key{typeid(E)};
    return *(static_cast<E*>(use(key)));
  }

  /// Add an extension to this context.
  ///
  template<typename E>
  E&
  extension_context_t::
  extend(E* ptr)
  {
    static std::type_index const key{typeid(E)};
    extend(key, ptr);
    return *ptr;
  }

  /// Erase an extension from this context.
  ///
  template<typename E>
  void
  extension_context_t::
  erase()
  {
    static std::type_index const key{typeid(E)};
    erase_extension(key);
  }

  template<typename E>
  extend_t<E>::
  extend_t(extension_context_t& target, extension_type& ext)
    : target_{target}
  {
    target.extend(&ext);
  }

  template<typename E>
  extend_t<E>::
  ~extend_t() noexcept
  {
    target_.erase<extension_type>();
  }

} // namespace art::seafire::common
