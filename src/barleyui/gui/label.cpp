#include "label.hpp"

#include "../globals.hpp"

namespace barleyui {

Label::Label() : layout(Pango::Layout::create(globals::pango_context())) {}

Label::Label(const Glib::ustring& str) : Label() {
    set_text(str);
}

void Label::set_text(const Glib::ustring& str) {
    layout->set_text(str);
}

void Label::set_font(const Glib::ustring& str) {
    layout->set_font_description(Pango::FontDescription(str));
}

void Label::set_align(AlignH align) {
    switch (align) {
        case AlignH::LEFT:
            layout->set_alignment(Pango::ALIGN_LEFT);
            break;
        case AlignH::RIGHT:
            layout->set_alignment(Pango::ALIGN_RIGHT);
            break;
        case AlignH::CENTER:
            layout->set_alignment(Pango::ALIGN_CENTER);
            break;
    }
}

void Label::set_align(AlignV align) {
    align_v = align;
}

void Label::set_bounds(glm::vec2 top_left, glm::vec2 bottom_right) {
    layout->set_width((bottom_right.x-top_left.x) * PANGO_SCALE);
    layout->set_height((bottom_right.y-top_left.y) * PANGO_SCALE);
    x = top_left.x;

    int w,h;
    layout->get_pixel_size(w,h);

    switch (align_v) {
        case AlignV::TOP:
            y = top_left.y;
            break;
        case AlignV::BOTTOM:
            y = bottom_right.y - h;
            break;
        case AlignV::CENTER:
            y = (top_left.y + bottom_right.y - h) / 2.0;
            break;
    }
}

void Label::draw(const Cairo::RefPtr<Cairo::Context>& cairo) const {
    cairo->set_source_rgba(0,0,0,1);
    cairo->move_to(x, y);
    layout->show_in_cairo_context(cairo);
}

} // namespace barleyui
