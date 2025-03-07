namespace art::seafire::common
{

  template<typename T>
  T&
  allocator_t::
  alloc()
  {
    return alloc_emplace<T>();
  }

  template<typename T>
  T&
  allocator_t::
  alloc(T const& object)
  {
    return alloc_emplace<T>(object);
  }

  template<typename T>
  T&
  allocator_t::
  alloc(T&& object)
  {
    return alloc_emplace<T>(object);
  }

  template<typename T, typename... Args>
  T&
  allocator_t::
  alloc_emplace(Args&&... args)
  {
    struct object_t
      : allocation_t
    {
      object_t(Args&&... args)
        : object{std::forward<Args>(args)...}
      {}

      T object;

    };

    std::unique_ptr<object_t> a{
      new object_t{std::forward<Args>(args)...}
    };

    auto& ref = a->object;

    allocations_.emplace(std::move(a));

    return ref;
  }

} // namespace art::seafire::common
