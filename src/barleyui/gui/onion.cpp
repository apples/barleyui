#include "onion.hpp"

#include <boost/range/adaptor/reversed.hpp>
#include <boost/variant.hpp>

namespace barleyui {

void Onion::push(AnyWidget widget) {
    layers.push_back(std::move(widget));
}

AnyWidget Onion::pop() {
    auto widget = std::move(layers.back());
    layers.pop_back();
    return widget;
}

void Onion::set_bounds(glm::vec2 top_left, glm::vec2 bottom_right) {
    for (auto& widget : layers) {
        widget.set_bounds(top_left, bottom_right);
    }
}

void Onion::draw(const Cairo::RefPtr<Cairo::Context>& cairo) const {
    for (auto& widget : layers) {
        widget.draw(cairo);
    }
}

bool Onion::process_event(const sushi::event& event) {
    return boost::apply_visitor(overload<bool>(
        [&](const sushi::event_keyboard&){
            if (focused >= 0 && focused < layers.size()) {
                return layers[focused].process_event(event);
            }
            return false;
        },
        [&](const sushi::event_any&){
            int i = layers.size();
            for (auto& widget : boost::adaptors::reverse(layers)) {
                --i;
                if (widget.process_event(event)) {
                    boost::apply_visitor(overload<void>(
                        [&](const sushi::event_mouse_press&){
                            focused = i;
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
