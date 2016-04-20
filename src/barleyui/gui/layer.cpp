#include "layer.hpp"

namespace barleyui {

Layer::Layer(int width, int height) :
    surface(Cairo::ImageSurface::create(Cairo::FORMAT_ARGB32, width, height)),
    cairo(Cairo::Context::create(surface)),
    root(null_widget)
{}

void Layer::set_root(AnyWidget widget) {
    root = std::move(widget);
}

void Layer::draw() {
    cairo->save();
    cairo->set_operator(Cairo::OPERATOR_CLEAR);
    cairo->paint();
    cairo->restore();
    root.set_bounds({0, 0}, {surface->get_width(), surface->get_height()});
    root.draw(cairo);
}

const Cairo::RefPtr<Cairo::ImageSurface>& Layer::get_surface() const {
    return surface;
}

} // namespace barleyui
