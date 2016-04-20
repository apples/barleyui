#ifndef BARLEYUI_GUI_SPLITVERTICAL_HPP
#define BARLEYUI_GUI_SPLITVERTICAL_HPP

#include "common.hpp"

#include "splitbase.hpp"

namespace barleyui {

class SplitVertical : public SplitBase {
    double split_loc = 0.0;

public:
    void set_left_widget(AnyWidget widget);
    void set_right_widget(AnyWidget widget);

    void set_bounds(glm::vec2 top_left, glm::vec2 bottom_right);

    bool process_event(sushi::event event);
};

} // namespace barleyui

#endif //BARLEYUI_GUI_SPLITVERTICAL_HPP
