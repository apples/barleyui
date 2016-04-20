#include "globals.hpp"

#include <glibmm/init.h>
#include <pangomm/init.h>
#include <pango/pangofc-fontmap.h>
#include <pangomm/cairofontmap.h>

#include <iostream>

namespace barleyui {
namespace globals {

namespace {

struct FcConfigDeleter {
    void operator()(FcConfig* config) const {
        if (config) {
            FcConfigDestroy(config);
        }
    }
};

} // static

GlibInitToken init_glib() {
    static auto token = (Glib::init(), GlibInitToken{});
    return token;
}

PangoInitToken init_pango() {
    static auto glib_token = init_glib();
    static auto token = (Pango::init(), PangoInitToken{});
    return token;
}

FcConfig* font_config() {
    static auto config = []{
        FcInit();
        std::unique_ptr<FcConfig,FcConfigDeleter> config (FcConfigCreate(), FcConfigDeleter{});
        if (FcConfigAppFontAddDir(config.get(), reinterpret_cast<const FcChar8*>("assets/fonts/")) == FcFalse) {
            std::clog << "Failed to find any fonts in \"assets/fonts/\"" << std::endl;
        }
        return config;
    }();
    return config.get();
}

Glib::RefPtr<Pango::FontMap> font_map() {
    static auto font_map = []{
        auto font_map = Glib::wrap(pango_cairo_font_map_new_for_font_type(CAIRO_FONT_TYPE_FT));
        auto fc_font_map = PANGO_FC_FONT_MAP(font_map->gobj());
        pango_fc_font_map_set_config(fc_font_map, font_config());
        return font_map;
    }();
    return font_map;
}

Glib::RefPtr<Pango::Context> pango_context() {
    static auto pango_token = init_pango();
    static auto context = font_map()->create_context();
    return context;
}

} // namespace globals
} // namespace barleyui
