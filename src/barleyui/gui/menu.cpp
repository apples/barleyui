#include "menu.hpp"

namespace barleyui {

namespace {
    struct DefaultMenuData {
        std::vector<MenuEntry> data;
        auto& operator()() {
            return data;
        }
    };
}

Menu::Menu() : list(DefaultMenuData{}) {
    list.set_callback([](auto iter){
        iter->callback();
    });
}

void Menu::add_item(std::__cxx11::string name, std::function<void ()> callback) {
    list.get_data().push_back({std::move(name), std::move(callback)});
}

void Menu::set_bounds(glm::vec2 top_left, glm::vec2 bottom_right) {
    list.set_bounds(top_left, bottom_right);
}

void Menu::draw(const Cairo::RefPtr<Cairo::Context>& cairo) const {
    list.draw(cairo);
}

bool Menu::process_event(const sushi::event& event) {
    return list.process_event(event);
}

} // namespace barleyui
