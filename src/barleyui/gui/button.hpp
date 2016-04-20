#ifndef BARLEYUI_GUI_BUTTON_HPP
#define BARLEYUI_GUI_BUTTON_HPP

#include "common.hpp"

namespace barleyui {

class Button {
    AnyWidget label = null_widget;
    double x, y, width, height;
    std::function<void(Button&)> callback = [](Button&){};

public:
    void set_label(AnyWidget widget);

    void set_callback(std::function<void(Button&)> f);

    void set_bounds(glm::vec2 top_left, glm::vec2 bottom_right);

    void draw(const Cairo::RefPtr<Cairo::Context>& cairo) const;

    bool process_event(const sushi::event& event);
};

} // namespace barleyui

#endif //BARLEYUI_GUI_BUTTON_HPP
