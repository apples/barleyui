#include "floating.hpp"

namespace barleyui {

void Floating::set_widget(AnyWidget w) {
    widget = std::move(w);
}

void Floating::set_position(glm::vec2 p) {
    position = p;
}

void Floating::set_size(glm::vec2 s) {
    size = s;
}

void Floating::set_bounds(glm::vec2 top_left, glm::vec2 bottom_right) {
    top_left += position;
    if (size.x >= 0) {
        bottom_right.x = top_left.x + size.x;
    }
    if (size.y >= 0) {
        bottom_right.y = top_left.y + size.y;
    }
    widget.set_bounds(top_left, bottom_right);
}

void Floating::draw(const Cairo::RefPtr<Cairo::Context>& cairo) const {
    widget.draw(cairo);
}

bool Floating::process_event(sushi::event event) {
    return boost::apply_visitor(overload<bool>(
        [&](const sushi::event_keyboard&){
            if (focused) {
                return widget.process_event(event);
            }
            return false;
        },
        [&](const sushi::event_any&){
            event.pos -= position;
            if (event.pos.x >= 0 && event.pos.y >= 0 &&
                    (size.x < 0 || event.pos.x < size.x) &&
                    (size.y < 0 || event.pos.y < size.y))
            {
                if (widget.process_event(event)) {
                    boost::apply_visitor(overload<void>(
                                             [&](const sushi::event_mouse_press&){
                        focused = true;
                    },
                    [&](const sushi::event_any&){}
                    ), event.data);
                    return true;
                }
            }
            return false;
        }
    ), event.data);
}

} // namespace barleyui
