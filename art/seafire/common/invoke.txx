namespace art::seafire::common
{

  template<typename Ret, typename T, typename... Direct, typename... Params>
  Ret
  do_invoke(T& target,
            server::request_t& req,
            Direct const&... direct,
            Ret (T::*func)(Direct const&..., Params const&...))
  {
    return (target.*func)(direct..., std::decay_t<Params>::fetch(req)...);
  }

  template<typename Ret, typename T, typename... Params, typename... Direct>
  Ret
  invoke(T& target,
         server::request_t& req,
         Ret (T::*func)(Params const&...),
         Direct const&... direct)
  {
    return do_invoke<Ret, T, Direct...>(target, req, direct..., func);
  }

  template<typename Ret, typename T, typename... Direct, typename... Params>
  Ret
  do_invoke(T const& target,
            server::request_t& req,
            Direct const&... direct,
            Ret (T::*func)(Direct const&..., Params const&...) const)
  {
    return (target.*func)(direct..., std::decay_t<Params>::fetch(req)...);
  }

  template<typename Ret, typename T, typename... Params, typename... Direct>
  Ret
  invoke(T const& target,
         server::request_t& req,
         Ret (T::*func)(Params const&...) const,
         Direct const&... direct)
  {
    return do_invoke<Ret, T, Direct...>(target, req, direct..., func);
  }

  template<typename Ret, typename... Direct, typename... Params>
  Ret
  do_invoke(server::request_t& req,
            Direct&&... direct,
            Ret (*func)(Direct..., Params...))
  {
    return (*func)(direct..., std::decay_t<Params>::fetch(req)...);
  }

  template<typename Ret, typename... Params, typename... Direct>
  Ret
  invoke(server::request_t& req,
         Ret (*func)(Params...),
         Direct&&... direct)
  {
    return do_invoke<Ret, Direct...>(req, direct..., func);
  }

} // namespace art::seafire::common
