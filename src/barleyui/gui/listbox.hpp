#ifndef BARLEYUI_GUI_LISTBOX_HPP
#define BARLEYUI_GUI_LISTBOX_HPP

#include "common.hpp"

#include "../globals.hpp"

#include <pangomm.h>

namespace barleyui {

template <typename T>
Glib::ustring get_string(const T& t) {
    std::ostringstream oss;
    oss << t;
    return oss.str();
}

inline Glib::ustring get_string(const std::string& t) {
    return t;
}

inline const Glib::ustring& get_string(const Glib::ustring& t) {
    return t;
}

template <typename Container>
class ListBox {
    using DataFunc = std::function<Container&()>;
    using Callback = std::function<void(typename Container::iterator)>;

    DataFunc data_func;
    Callback callback = [](auto){};

    std::vector<Glib::RefPtr<Pango::Layout>> layouts;
    glm::vec2 pos;
    double width;
    int selected = -1;

    Pango::FontDescription font {"Sans 12"};

    void make_layouts(int width) {
        const auto& data = get_data();
        auto sz = data.size();
        layouts.resize(sz);
        for (auto i = 0u; i < sz; ++i) {
            auto& datum = data[i];
            auto& layout = layouts[i];
            if (!layout) {
                layout = Pango::Layout::create(globals::pango_context());
            }
            layout->set_text(get_string(datum));
            layout->set_font_description(font);
            layout->set_width(width * PANGO_SCALE);
        }
    }

public:
    ListBox(DataFunc data_func) : data_func(std::move(data_func)) {}

    ListBox(const ListBox&) = delete;
    ListBox(ListBox&&) = default;
    ListBox& operator=(const ListBox&) = delete;
    ListBox& operator=(ListBox&&) = default;
    ~ListBox() = default;

    Container& get_data() {
        return data_func();
    }

    void set_data_func(DataFunc func) {
        data_func = std::move(func);
    }

    void set_callback(Callback func) {
        callback = std::move(func);
    }

    glm::vec2 get_preferred_size() {
        make_layouts(-1);
        glm::vec2 size = {0,0};
        for (auto& layout : layouts) {
            int w,h;
            layout->get_pixel_size(w,h);
            size.x = std::max(size.x,float(w));
            size.y += h;
        }
        return size;
    }

    void set_bounds(glm::vec2 top_left, glm::vec2 bottom_right) {
        pos = top_left;
        width = bottom_right.x-top_left.x;
        make_layouts(width);
    }

    void draw(const Cairo::RefPtr<Cairo::Context>& cairo) const {
        glm::vec2 curpos = pos;
        int current = 0;
        for (auto& layout : layouts) {
            int ignore,h;
            layout->get_pixel_size(ignore,h);
            if (current == selected) {
                cairo->set_source_rgba(1,1,0,1);
                cairo->rectangle(curpos.x, curpos.y, width, h);
                cairo->fill();
            }
            cairo->set_source_rgba(0,0,0,1);
            cairo->move_to(curpos.x, curpos.y);
            layout->show_in_cairo_context(cairo);
            curpos.y += h;
            ++current;
        }
    }

    void select(int i) {
        selected = i;
        auto& data = get_data();
        if (i < data.size()) {
            auto iter = data.begin();
            std::advance(iter, i);
            return callback(iter);
        }
    }

    bool process_event(sushi::event event) {
        return boost::apply_visitor(overload<bool>(
            [&](const sushi::event_any&){return false;},
            [&](const sushi::event_mouse_press& e){
                if (e.button == GLFW_MOUSE_BUTTON_LEFT)
                for (auto i = 0u; i < layouts.size(); ++i) {
                    auto& layout = layouts[i];
                    int w,h;
                    layout->get_pixel_size(w,h);
                    event.pos.y -= h;
                    if (event.pos.y < 0) {
                        select(i);
                        return true;
                    }
                }
                return false;
            }
        ), event.data);
    }
};

} // namespace barleyui

#endif //BARLEYUI_GUI_LISTBOX_HPP
