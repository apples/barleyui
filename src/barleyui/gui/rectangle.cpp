#include "rectangle.hpp"

namespace barleyui {

Rectangle::Rectangle(double r, double g, double b, double a) : r(r), g(g), b(b), a(a) {}

void Rectangle::set_bounds(glm::vec2 top_left, glm::vec2 bottom_right) {
    this->top_left = top_left;
    this->bottom_right = bottom_right;
}

void Rectangle::draw(const Cairo::RefPtr<Cairo::Context>& cairo) const {
    if (a > 0) {
        cairo->set_source_rgba(r,g,b,a);
        cairo->rectangle(top_left.x, top_left.y, bottom_right.x-top_left.x, bottom_right.y-top_left.y);
        cairo->fill();
    }
}

std::tuple<const glm::vec2&, const glm::vec2&> Rectangle::get_bounds() const {
    return std::tie(top_left, bottom_right);
}

} // namespace barleyui
