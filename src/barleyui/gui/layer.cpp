#include "layer.hpp"

namespace barleyui {

void Layer::set_root(AnyWidget widget) {
    root = std::move(widget);
}

void Layer::draw(Cairo::RefPtr<Cairo::Context>& cairo) {
    cairo->save();
    cairo->set_operator(Cairo::OPERATOR_CLEAR);
    cairo->paint();
    cairo->restore();
    auto surface = Cairo::RefPtr<Cairo::ImageSurface>::cast_static(cairo->get_target());
    root.set_bounds({0, 0}, {surface->get_width(), surface->get_height()});
    root.draw(cairo);
}

} // namespace barleyui
