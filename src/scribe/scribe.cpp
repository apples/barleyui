#include "scribe.hpp"

#include <cairomm/cairomm.h>
#include <glibmm/init.h>
#include <pango/pangofc-fontmap.h>
#include <pangomm/cairofontmap.h>
#include <pangomm/init.h>

#include <iostream>

namespace scribe::_detail {

inline namespace {

std::unique_ptr<FcConfig, FcConfig_deleter> make_font_config(const std::string& font_path) {
    auto config = std::unique_ptr<FcConfig, FcConfig_deleter>(FcConfigCreate(), FcConfig_deleter{});
    if (FcConfigAppFontAddDir(config.get(), reinterpret_cast<const FcChar8*>(font_path.data())) == FcFalse) {
        std::clog << "Warning: Failed to find any fonts in \"" << font_path << "\"." << std::endl;
    }
    return config;
}

Glib::RefPtr<Pango::FontMap> make_font_map(FcConfig* font_config) {
    auto font_map = Glib::wrap(pango_cairo_font_map_new_for_font_type(CAIRO_FONT_TYPE_FT));
    auto fc_font_map = PANGO_FC_FONT_MAP(font_map->gobj());
    pango_fc_font_map_set_config(fc_font_map, font_config);
    return font_map;
}

} // internal

void FcConfig_deleter::operator()(FcConfig* config) const {
    if (config) {
        FcConfigDestroy(config);
    }
}

mixin_init_libs::mixin_init_libs() {
    Glib::init();
    Pango::init();
    FcInit();
}

context::context(const std::string& font_path) :
    font_config(make_font_config(font_path)),
    font_map(make_font_map(font_config.get())),
    pango_context(font_map->create_context())
{}

image context::render_markup(const std::string& text) {
    auto layout = Pango::Layout::create(pango_context);
    layout->set_markup(text);

    int width;
    int height;
    layout->get_pixel_size(width, height);

    auto stride = Cairo::ImageSurface::format_stride_for_width(Cairo::FORMAT_ARGB32, width);
    auto buffer = std::make_unique<unsigned char[]>(stride*height);

    {
        auto surface = Cairo::ImageSurface::create(buffer.get(), Cairo::FORMAT_ARGB32, width, height, stride);
        auto cairo = Cairo::Context::create(surface);

        cairo->save();
        cairo->set_operator(Cairo::OPERATOR_SOURCE);
        cairo->set_source_rgba(0,0,0,0);
        cairo->paint();
        cairo->restore();

        layout->show_in_cairo_context(cairo);
    }

    return {std::move(buffer), width, stride, height};
}

} // namespace scribe
