#ifndef BARLEYUI_GLOBALS_HPP
#define BARLEYUI_GLOBALS_HPP

#include <pangomm/context.h>
#include <fontconfig/fontconfig.h>

namespace barleyui {
namespace globals {

struct GlibInitToken{};
struct PangoInitToken{};

GlibInitToken init_glib();
PangoInitToken init_pango();
FcConfig* font_config();
Glib::RefPtr<Pango::FontMap> font_map();
Glib::RefPtr<Pango::Context> pango_context();

} // namespace globals
} // namespace barleyui

#endif //BARLEYUI_GLOBALS_HPP
