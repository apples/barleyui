#ifndef BARLEYUI_GUI_FLOATING_HPP
#define BARLEYUI_GUI_FLOATING_HPP

#include "common.hpp"

namespace barleyui {

class Floating {
    AnyWidget widget = null_widget;
    glm::vec2 position = {};
    glm::vec2 size = {-1,-1};
    bool focused = false;

public:
    void set_widget(AnyWidget w);

    void set_position(glm::vec2 p);

    void set_size(glm::vec2 s);

    void set_bounds(glm::vec2 top_left, glm::vec2 bottom_right);

    void draw(const Cairo::RefPtr<Cairo::Context>& cairo) const;

    bool process_event(sushi::event event);
};

} // namespace barleyui

#endif //BARLEYUI_GUI_FLOATING_HPP
