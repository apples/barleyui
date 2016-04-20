#ifndef BARLEYUI_GUI_MENU_HPP
#define BARLEYUI_GUI_MENU_HPP

#include "common.hpp"

#include "listbox.hpp"

#include <pangomm.h>

namespace barleyui {

struct MenuEntry {
    std::string name;
    std::function<void()> callback;
};

inline Glib::ustring get_string(const MenuEntry& e) {
    return e.name;
}

class Menu {
    ListBox<std::vector<MenuEntry>> list;

public:
    Menu();

    void add_item(std::string name, std::function<void()> callback);

    void set_bounds(glm::vec2 top_left, glm::vec2 bottom_right);

    void draw(const Cairo::RefPtr<Cairo::Context>& cairo) const;

    bool process_event(const sushi::event& event);
};

} // namespace barleyui

#endif //BARLEYUI_GUI_MENU_HPP
