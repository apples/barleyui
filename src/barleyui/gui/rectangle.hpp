#ifndef BARLEYUI_GUI_RECTANGLE_HPP
#define BARLEYUI_GUI_RECTANGLE_HPP

#include "common.hpp"

namespace barleyui {

class Rectangle {
    glm::vec2 top_left;
    glm::vec2 bottom_right;
    double r, g, b, a;

public:
    Rectangle(double r, double g, double b, double a);

    void set_bounds(glm::vec2 top_left, glm::vec2 bottom_right);
    void draw(const Cairo::RefPtr<Cairo::Context>& cairo) const;
    std::tuple<const glm::vec2&, const glm::vec2&> get_bounds() const;
    bool process_event(const sushi::event&) {return false;}
};

} // namespace barleyui

#endif //BARLEYUI_GUI_RECTANGLE_HPP
