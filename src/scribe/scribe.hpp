#ifndef SCRIBE_SCRIBE_HPP
#define SCRIBE_SCRIBE_HPP

#include <fontconfig/fontconfig.h>
#include <pangomm/context.h>
#include <pangomm/layout.h>

#include <memory>
#include <string>

namespace scribe::_detail {

struct FcConfig_deleter {
    void operator()(FcConfig* config) const;
};

class mixin_init_libs {
public:
    mixin_init_libs();
};

struct image {
    std::unique_ptr<unsigned char[]> pixels_bgra;
    int width;
    int stride;
    int height;
};

class context : private mixin_init_libs {
public:
    context(const std::string& font_path);

    image render_markup(const std::string& text);

private:
    std::unique_ptr<FcConfig, FcConfig_deleter> font_config;
    Glib::RefPtr<Pango::FontMap> font_map;
    Glib::RefPtr<Pango::Context> pango_context;
};

} // namespace scribe::detail

namespace scribe {

using _detail::image;
using _detail::context;

} // namespace scribe

#endif // SCRIBE_SCRIBE_HPP
