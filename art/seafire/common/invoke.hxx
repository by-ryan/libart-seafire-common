#ifndef art__seafire__common__invoke_hxx_
#define art__seafire__common__invoke_hxx_

#include <art/seafire/server/request.hxx>
#include <art/seafire/server/response.hxx>

namespace art::seafire::common
{

  template<typename Ret, typename T, typename... Direct, typename... Params>
  Ret
  do_invoke(T& target,
            server::request_t& req,
            Direct const&... direct,
            Ret (T::*func)(Direct const&..., Params const&...));

  template<typename Ret, typename T, typename... Params, typename... Direct>
  Ret
  invoke(T& target,
         server::request_t& req,
         Ret (T::*func)(Params const&...),
         Direct const&... direct);

  template<typename Ret, typename T, typename... Direct, typename... Params>
  Ret
  do_invoke(T const& target,
            server::request_t& req,
            Direct const&... direct,
            Ret (T::*func)(Direct const&..., Params const&...) const);

  template<typename Ret, typename T, typename... Params, typename... Direct>
  Ret
  invoke(T const& target,
         server::request_t& req,
         Ret (T::*func)(Params const&...) const,
         Direct const&... direct);

  template<typename Ret, typename... Direct, typename... Params>
  Ret
  do_invoke(server::request_t& req,
            Direct&&... direct,
            Ret (*func)(Direct..., Params...));

  template<typename Ret, typename... Params, typename... Direct>
  Ret
  invoke(server::request_t& req,
         Ret (*func)(Params...),
         Direct&&... direct);

} // namespace art::seafire::common

#include <art/seafire/common/invoke.txx>

#endif
