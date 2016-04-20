#ifndef BARLEYUI_GUI_ONION_HPP
#define BARLEYUI_GUI_ONION_HPP

#include "common.hpp"

namespace barleyui {

class Onion {
    std::vector<AnyWidget> layers;
    int focused = -1;

public:
    void push(AnyWidget widget);

    AnyWidget pop();

    void set_bounds(glm::vec2 top_left, glm::vec2 bottom_right);

    void draw(const Cairo::RefPtr<Cairo::Context>& cairo) const;

    bool process_event(const sushi::event& event);
};

} // namespace barleyui

#endif //BARLEYUI_GUI_ONION_HPP
