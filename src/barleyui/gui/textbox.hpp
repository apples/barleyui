#ifndef BARLEYUI_GUI_TEXTBOX_HPP
#define BARLEYUI_GUI_TEXTBOX_HPP

#include "common.hpp"

#include <pangomm.h>

namespace barleyui {

class TextBox {
    std::vector<Glib::RefPtr<Pango::Layout>> layouts;
    glm::vec2 top_left;
    int cursor_line = 0;
    int cursor_index = 0;
    Pango::FontDescription font {"Liberation Mono, 12"};

public:
    TextBox();

    void set_bounds(glm::vec2 top_left, glm::vec2 bottom_right);

    void draw(const Cairo::RefPtr<Cairo::Context>& cairo) const;

    bool process_event(sushi::event event);
};

} // namespace barleyui

#endif //BARLEYUI_GUI_TEXTBOX_HPP
