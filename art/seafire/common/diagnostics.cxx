#include <art/seafire/common/diagnostics.hxx>

#include <iomanip>

namespace art::seafire::common
{

  void
  diagnostics_t::
  enable(category_t const& category)
  {
    categories_.emplace(&category);
  }

  void
  diagnostics_t::
  disable(category_t const& category)
  {
    categories_.erase(&category);
  }

  diagnostics_t::proxy_t
  diagnostics_t::
  operator<<(category_t const& category)
  {
    return proxy_t{*this, category};
  }

  diagnostics_t::
  diagnostics_t() = default;

  diagnostics_t::
  ~diagnostics_t() noexcept = default;

  bool
  diagnostics_t::
  is_enabled(category_t const& category)
  {
    return categories_.count(&category) == 1;
  }

  void
  diagnostics_t::
  log(record_t record)
  {
    if (!is_enabled(record.category)) {
      return;
    }

    std::size_t max{0};

    for (auto const& j : categories_) {
      if (auto size = j->prefix().size(); size > max) {
        max = size;
      }
    }

    std::stringstream message;

    for (std::string line; std::getline(record.message, line);) {
      message << std::left
              << std::setw(max)
              << record.category.prefix()
              << ": "
              << line
              << '\n';
    }

    do_log(message.str());
  }

  diagnostics_t::category_t::
  category_t(std::string prefix)
    : prefix_{std::move(prefix)}
  {}

  diagnostics_t::category_t::
  ~category_t() noexcept = default;

  std::string const&
  diagnostics_t::category_t::
  prefix() const
  {
    return prefix_;
  }

  diagnostics_t::proxy_t::
  ~proxy_t() noexcept
  {
    if (diagnostics_) {
      diagnostics_->log({category_, std::move(message_)});
    }
  }

  diagnostics_t::proxy_t::
  proxy_t(diagnostics_t& diagnostics, category_t const& category)
    : diagnostics_{&diagnostics},
      category_{category}
  {}

  diagnostics_t::proxy_t::
  proxy_t(proxy_t&& other) noexcept
    : category_{other.category_}
  {
    std::swap(diagnostics_, other.diagnostics_);
  }

  ostream_diagnostics_t::
  ostream_diagnostics_t(std::ostream& output)
    : output_{output}
  {}

  ostream_diagnostics_t::
  ~ostream_diagnostics_t() noexcept = default;

  std::ostream&
  ostream_diagnostics_t::
  output()
  {
    return output_;
  }

  void
  ostream_diagnostics_t::
  do_log(std::string const& message)
  {
    output() << message;
  }


} // namespace art::seafire::common
