#ifndef BARLEYUI_GUI_LAYER_HPP
#define BARLEYUI_GUI_LAYER_HPP

#include "common.hpp"

namespace barleyui {

class Layer {
    Cairo::RefPtr<Cairo::ImageSurface> surface;
    Cairo::RefPtr<Cairo::Context> cairo;
    AnyWidget root;

public:
    Layer(int width, int height);

    void set_root(AnyWidget widget);

    void draw();
    const Cairo::RefPtr<Cairo::ImageSurface>& get_surface() const;

    bool process_event(const sushi::event& event) {
        return root.process_event(event);
    }
};

} // namespace barleyui

#endif //BARLEYUI_GUI_LAYER_HPP
