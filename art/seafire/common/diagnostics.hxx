#ifndef art__seafire__common__diagnostics_hxx_
#define art__seafire__common__diagnostics_hxx_

#include <ostream>
#include <set>
#include <sstream>
#include <string>

namespace art::seafire::common
{

  /// Provides a base for implementing diagnostics.
  ///
  class diagnostics_t
  {
  public:
    class category_t;
    class proxy_t;

    friend proxy_t;

    void
    enable(category_t const&);

    void
    disable(category_t const&);

    proxy_t
    operator<<(category_t const&);

  protected:
    struct record_t;

    diagnostics_t();

    diagnostics_t(diagnostics_t const&) = delete;
    diagnostics_t(diagnostics_t&&) = delete;

    ~diagnostics_t() noexcept;

    bool
    is_enabled(category_t const&);

    void
    log(record_t);

    virtual
    void
    do_log(std::string const&) = 0;

    diagnostics_t& operator=(diagnostics_t const&) = delete;
    diagnostics_t& operator=(diagnostics_t&&) = delete;

  private:
    std::set<category_t const*> categories_;

  };

  /// Represents a diagnostic category.
  ///
  class diagnostics_t::category_t
  {
  public:
    explicit
    category_t(std::string);

    category_t(category_t const&) = delete;
    category_t(category_t&&) = delete;

    ~category_t() noexcept;

    std::string const&
    prefix() const;

    category_t& operator=(category_t const&) = delete;
    category_t& operator=(category_t&&) = delete;

  private:
    std::string prefix_;

  };

  /// Proxy for writing diagnostics.
  ///
  class diagnostics_t::proxy_t
  {
  public:
    ~proxy_t() noexcept;

    template<typename T>
    proxy_t&
    operator<<(T const& other)
    {
      message_ << other;
      return *this;
    }

  protected:
    friend diagnostics_t;

    proxy_t(diagnostics_t&, category_t const&);

    proxy_t(proxy_t const&) = delete;

    proxy_t(proxy_t&&) noexcept;

    proxy_t& operator=(proxy_t const&) = delete;
    proxy_t& operator=(proxy_t&&) = delete;

  private:
    diagnostics_t* diagnostics_{};
    category_t const& category_;
    std::stringstream message_;

  };

  /// Represents a diagnostic record.
  ///
  struct diagnostics_t::record_t
  {
    /// The diagnostic category.
    ///
    category_t const& category;

    /// The diagnostic message.
    ///
    std::stringstream message;

  };

  class ostream_diagnostics_t
    : public diagnostics_t
  {
  public:
    explicit
    ostream_diagnostics_t(std::ostream&);

    ostream_diagnostics_t(ostream_diagnostics_t const&) = delete;
    ostream_diagnostics_t(ostream_diagnostics_t&&) = delete;

    ~ostream_diagnostics_t() noexcept;

    std::ostream&
    output();

    ostream_diagnostics_t& operator=(ostream_diagnostics_t const&) = delete;
    ostream_diagnostics_t& operator=(ostream_diagnostics_t&&) = delete;

  protected:
    void
    do_log(std::string const&) override;

  private:
    std::ostream& output_;

  };

} // namespace art::seafire::common

#endif
