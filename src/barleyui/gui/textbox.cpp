#include "textbox.hpp"

#include "../globals.hpp"

namespace barleyui {

TextBox::TextBox() {
    auto layout = Pango::Layout::create(globals::pango_context());
    layout->set_font_description(font);
    layouts.push_back(std::move(layout));
}

void TextBox::set_bounds(glm::vec2 top_left, glm::vec2 bottom_right) {
    this->top_left = top_left;
    auto size = bottom_right - top_left;
    //layout->set_width(size.x * PANGO_SCALE);
    //layout->set_height(size.y * PANGO_SCALE);
}

void TextBox::draw(const Cairo::RefPtr<Cairo::Context>& cairo) const {
    cairo->set_source_rgba(0,0,0,1);
    auto yoff = double(0);
    auto i = 0;
    for (auto&& layout : layouts) {
        cairo->move_to(top_left.x, top_left.y + yoff);
        layout->show_in_cairo_context(cairo);
        if (i == cursor_line) {
            auto cursor = layouts[cursor_line]->get_cursor_strong_pos(cursor_index);
            cairo->rectangle(top_left.x + cursor.get_x()/PANGO_SCALE, top_left.y + yoff + cursor.get_y()/PANGO_SCALE, cursor.get_width()/PANGO_SCALE, cursor.get_height()/PANGO_SCALE);
            cairo->fill_preserve();
            cairo->set_line_width(1);
            cairo->stroke();
        }
        int w,h;
        layout->get_pixel_size(w,h);
        yoff += h;
        ++i;
    }
}

bool TextBox::process_event(sushi::event event) {
    return boost::apply_visitor(overload<bool>(
        [&](const sushi::event_any&){return false;},
        [&](const sushi::event_mouse_press& e){
            if (e.button == GLFW_MOUSE_BUTTON_LEFT) {
                auto yoff = double(0);
                int line = 0;
                for (auto&& layout : layouts) {
                    int w,h;
                    layout->get_pixel_size(w,h);
                    if (yoff+h > event.pos.y) {
                        event.pos.y -= yoff;
                        int trailing;
                        layout->xy_to_index(event.pos.x * PANGO_SCALE, event.pos.y * PANGO_SCALE, cursor_index, trailing);
                        cursor_index += trailing;
                        cursor_line = line;
                    }
                    ++line;
                }
            }
            return true;
        },
        [&](const sushi::event_char& e){
            auto text = layouts[cursor_line]->get_text();
            text.insert(cursor_index, 1, gunichar(e.codepoint));
            layouts[cursor_line]->set_text(text);
            ++cursor_index;
            return true;
        },
        [&](const sushi::event_keyboard_press& e){
            switch (e.key) {
                case GLFW_KEY_BACKSPACE: {
                    if (cursor_index > 0) {
                        --cursor_index;
                        auto text = layouts[cursor_line]->get_text();
                        text.erase(cursor_index, 1);
                        layouts[cursor_line]->set_text(text);
                    }
                } break;
                case GLFW_KEY_DELETE: {
                    auto text = layouts[cursor_line]->get_text();
                    text.erase(cursor_index, 1);
                    layouts[cursor_line]->set_text(text);
                } break;
                case GLFW_KEY_LEFT: {
                    if (cursor_index > 0) {
                        --cursor_index;
                    }
                } break;
                case GLFW_KEY_RIGHT: {
                    if (cursor_index < layouts[cursor_line]->get_text().size()) {
                        ++cursor_index;
                    }
                } break;
                case GLFW_KEY_UP: {
                    if (cursor_line > 0) {
                        --cursor_line;
                        auto sz = layouts[cursor_line]->get_text().size();
                        if (cursor_index > sz) {
                            cursor_index = sz;
                        }
                    }
                } break;
                case GLFW_KEY_DOWN: {
                    if (cursor_line < layouts.size()-1) {
                        ++cursor_line;
                        auto sz = layouts[cursor_line]->get_text().size();
                        if (cursor_index > sz) {
                            cursor_index = sz;
                        }
                    }
                } break;
                case GLFW_KEY_ENTER: {
                    auto text = layouts[cursor_line]->get_text();
                    auto nline = text.substr(cursor_index);
                    text.erase(cursor_index);
                    layouts[cursor_line]->set_text(text);
                    auto nlayout = Pango::Layout::create(globals::pango_context());
                    nlayout->set_text(nline);
                    nlayout->set_font_description(font);
                    layouts.insert(layouts.begin()+cursor_line+1, std::move(nlayout));
                    ++cursor_line;
                    cursor_index = 0;
                } break;
            }
            return true;
        }
    ), event.data);
}

} // namespace barleyui
