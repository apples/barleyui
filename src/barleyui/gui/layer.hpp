#ifndef BARLEYUI_GUI_LAYER_HPP
#define BARLEYUI_GUI_LAYER_HPP

#include "common.hpp"

namespace barleyui {

class Layer {
    AnyWidget root = null_widget;

public:
    void set_root(AnyWidget widget);

    void draw(Cairo::RefPtr<Cairo::Context>& cairo);

    bool process_event(const sushi::event& event) {
        return root.process_event(event);
    }
};

} // namespace barleyui

#endif //BARLEYUI_GUI_LAYER_HPP
