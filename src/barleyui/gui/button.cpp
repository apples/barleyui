#include "button.hpp"

namespace barleyui {

void Button::set_label(AnyWidget widget) {
    label = std::move(widget);
}

void Button::set_callback(std::function<void (Button&)> f) {
    callback = std::move(f);
}

void Button::set_bounds(glm::vec2 top_left, glm::vec2 bottom_right) {
    label.set_bounds(top_left, bottom_right);
    x = top_left.x;
    y = top_left.y;
    width = bottom_right.x-top_left.x;
    height = bottom_right.y-top_left.y;
}

void Button::draw(const Cairo::RefPtr<Cairo::Context>& cairo) const {
    cairo->set_source_rgba(0.3, 0.3, 0.3, 1.0);
    cairo->rectangle(x, y, width, height);
    cairo->fill();
    cairo->set_source_rgba(0.9, 0.9, 0.9, 1.0);
    cairo->rectangle(x+5, y+5, width-10, height-10);
    cairo->fill();
    label.draw(cairo);
}

bool Button::process_event(const sushi::event& event) {
    return boost::apply_visitor(overload<bool>(
        [&](const sushi::event_any&){return false;},
        [&](const sushi::event_mouse_press&){
            callback(*this);
            return true;
        }
    ), event.data);
}

} // namespace barleyui
