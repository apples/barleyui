#ifndef BARLEYUI_GUI_LABEL_HPP
#define BARLEYUI_GUI_LABEL_HPP

#include "common.hpp"

#include <pangomm.h>

namespace barleyui {

class Label {
    double x = 0;
    double y = 0;
    AlignV align_v = AlignV::TOP;
    Glib::RefPtr<Pango::Layout> layout;

public:
    Label();
    Label(const Glib::ustring& str);

    void set_text(const Glib::ustring& str);
    void set_font(const Glib::ustring& str);
    void set_align(AlignH align);
    void set_align(AlignV align);

    void set_bounds(glm::vec2 top_left, glm::vec2 bottom_right);
    void draw(const Cairo::RefPtr<Cairo::Context>& cairo) const;
    bool process_event(const sushi::event&) {return false;}
};

} // namespace barleyui

#endif //BARLEYUI_GUI_LABEL_HPP
