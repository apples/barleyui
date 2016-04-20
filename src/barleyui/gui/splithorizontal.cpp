#include "splithorizontal.hpp"

namespace barleyui {

void SplitHorizontal::set_top_widget(AnyWidget widget) {
    set_first_widget(std::move(widget));
}

void SplitHorizontal::set_bottom_widget(AnyWidget widget) {
    set_second_widget(std::move(widget));
}

void SplitHorizontal::set_bounds(glm::vec2 top_left, glm::vec2 bottom_right) {
    double side = (split >= 0.0) ? top_left.y : bottom_right.y;

    switch (split_unit) {
        case Unit::PERCENT:
            split_loc = side + (bottom_right.y-top_left.y)*split/100.0;
            break;
        case Unit::PIXEL:
            split_loc = side + split;
            break;
    }

    first_widget.set_bounds(top_left, {bottom_right.x, split_loc});
    second_widget.set_bounds({top_left.x, split_loc}, bottom_right);
}

bool SplitHorizontal::process_event(sushi::event event) {
    boost::apply_visitor(overload<void>(
        [&](const sushi::event_mouse_press&){
            if (event.pos.y < split_loc) {
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
                event.pos.y -= split_loc;
            }
            return get_focused().process_event(event);
        },
        [&](const sushi::event_any&){
            if (event.pos.y < split_loc) {
                return this->get_first_widget().process_event(event);
            } else {
                event.pos.y -= split_loc;
                return this->get_second_widget().process_event(event);
            }
        }
    ), event.data);
}

} // namespace barleyui
