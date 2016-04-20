#include "splitbase.hpp"

namespace barleyui {

AnyWidget& SplitBase::null_focused() {
    return null_any_widget;
}

void SplitBase::set_first_widget(AnyWidget widget) {
    first_widget = std::move(widget);
}

void SplitBase::set_second_widget(AnyWidget widget) {
    second_widget = std::move(widget);
}

AnyWidget& SplitBase::get_first_widget() {
    return first_widget;
}

AnyWidget& SplitBase::get_second_widget() {
    return second_widget;
}

void SplitBase::set_split_percent(double percent) {
    split = percent;
    split_unit = Unit::PERCENT;
}

void SplitBase::set_split_pixels(double pixels) {
    split = pixels;
    split_unit = Unit::PIXEL;
}

void SplitBase::focus_first() {
    focused = get_first_widget;
}

void SplitBase::focus_second() {
    focused = get_second_widget;
}

AnyWidget& SplitBase::get_focused() {
    return (this->*focused)();
}

void SplitBase::draw(const Cairo::RefPtr<Cairo::Context>& cairo) const {
    first_widget.draw(cairo);
    second_widget.draw(cairo);
}

} // namespace barleyui
