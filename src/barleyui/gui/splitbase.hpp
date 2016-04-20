#ifndef BARLEYUI_GUI_SPLITBASE_HPP
#define BARLEYUI_GUI_SPLITBASE_HPP

#include "common.hpp"

namespace barleyui {

class SplitBase {
    friend class SplitVertical;
    friend class SplitHorizontal;

    double split = 50.0;
    Unit split_unit = Unit::PERCENT;

    AnyWidget first_widget = null_widget;
    AnyWidget second_widget = null_widget;

    using Focuser = AnyWidget&(SplitBase::*)();
    Focuser focused = nullptr;

    AnyWidget& null_focused();

public:
    void set_first_widget(AnyWidget widget);
    void set_second_widget(AnyWidget widget);

    AnyWidget& get_first_widget();
    AnyWidget& get_second_widget();

    void set_split_percent(double percent);
    void set_split_pixels(double pixels);

    void focus_first();
    void focus_second();

    AnyWidget& get_focused();

    void draw(const Cairo::RefPtr<Cairo::Context>& cairo) const;
};

} // namespace barleyui

#endif //BARLEYUI_GUI_SPLITBASE_HPP
