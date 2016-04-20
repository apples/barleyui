#include "splitvertical.hpp"

namespace barleyui {

void SplitVertical::set_left_widget(AnyWidget widget) {
    set_first_widget(std::move(widget));
}

void SplitVertical::set_right_widget(AnyWidget widget) {
    set_second_widget(std::move(widget));
}

void SplitVertical::set_bounds(glm::vec2 top_left, glm::vec2 bottom_right) {
    double side = (split >= 0.0) ? top_left.x : bottom_right.x;

    switch (split_unit) {
        case Unit::PERCENT:
            split_loc = side + (bottom_right.x-top_left.x)*split/100.0;
            break;
        case Unit::PIXEL:
            split_loc = side + split;
            break;
    }

    first_widget.set_bounds(top_left, {split_loc, bottom_right.y});
    second_widget.set_bounds({split_loc, top_left.y}, bottom_right);
}

bool SplitVertical::process_event(sushi::event event) {
    boost::apply_visitor(overload<void>(
        [&](const sushi::event_mouse_press&){
            if (event.pos.x < split_loc) {
                focus_first();
            } else {
                focus_second();
            }
        },
        [&](const sushi::event_any&){}
    ), event.data);
    return boost::apply_visitor(overload<bool>(
        [&](const sushi::event_keyboard&){
            if (focused == &get_second_widget) {
                event.pos.x -= split_loc;
            }
            return get_focused().process_event(event);
        },
        [&](const sushi::event_any&){
            if (event.pos.x < split_loc) {
                return this->get_first_widget().process_event(event);
            } else {
                event.pos.x -= split_loc;
                return this->get_second_widget().process_event(event);
            }
        }
    ), event.data);
}

} // namespace barleyui
