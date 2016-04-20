#ifndef BARLEYUI_GUI_COMMON_HPP
#define BARLEYUI_GUI_COMMON_HPP

#include <raspberry/raspberry.hpp>
#include <sushi/event.hpp>
#include <glm/vec2.hpp>

#include <cairomm/cairomm.h>

namespace barleyui {

template <typename R, typename T, typename... Ts>
struct Overloaded : T, Overloaded<R, Ts...> {
    using T::operator();
    using Overloaded<R, Ts...>::operator();
    Overloaded(T&& t, Ts&&... ts) : T(std::forward<T>(t)), Overloaded<R, Ts...>(std::forward<Ts>(ts)...) {}
};

template <typename R, typename T>
struct Overloaded<R,T> : T, boost::static_visitor<R> {
    using T::operator();
    Overloaded(T&& t) : T(std::forward<T>(t)), boost::static_visitor<R>() {}
};

template <typename R, typename... Ts>
Overloaded<R,Ts...> overload(Ts&&... ts) {
    return Overloaded<R,Ts...>(std::forward<Ts>(ts)...);
}

enum class Unit {
    PERCENT,
    PIXEL
};

enum class AlignH {
    LEFT,
    RIGHT,
    CENTER
};

enum class AlignV {
    TOP,
    BOTTOM,
    CENTER
};

#define HOOKSHOT_DECL_METHOD(NAME) RASPBERRY_DECL_METHOD(_has_##NAME, NAME)

HOOKSHOT_DECL_METHOD(set_bounds);
HOOKSHOT_DECL_METHOD(draw);
HOOKSHOT_DECL_METHOD(process_event);

#undef HOOKSHOT_DECL_METHOD

using AnyWidgetBase = raspberry::Any<
    _has_set_bounds<void(glm::vec2,glm::vec2)>,
    _has_draw<void(const Cairo::RefPtr<Cairo::Context>&)const>,
    _has_process_event<bool(const sushi::event&)>
>;

struct AnyWidget : AnyWidgetBase {
    using AnyWidgetBase::Any;

    using AnyEventHandler = std::function<bool(const sushi::event&)>;

    std::vector<AnyEventHandler> handlers;

    void add_handler(AnyEventHandler handler);

    bool process_event(const sushi::event& event);
};

struct null_widget_t {
    void set_bounds(glm::vec2,glm::vec2) {}
    void draw(const Cairo::RefPtr<Cairo::Context>&) const {}
    bool process_event(const sushi::event&) {return false;}
} extern null_widget;

extern AnyWidget null_any_widget;

} // namespace barleyui

#endif //BARLEYUI_GUI_COMMON_HPP
