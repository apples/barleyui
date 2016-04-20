#include "common.hpp"

namespace barleyui {

null_widget_t null_widget = {};
AnyWidget null_any_widget = null_widget;

void AnyWidget::add_handler(AnyWidget::AnyEventHandler handler) {
    handlers.push_back(std::move(handler));
}

bool AnyWidget::process_event(const sushi::event& event) {
    for (auto&& handler : handlers) {
        if (handler(event)) {
            return true;
        }
    }
    return AnyWidgetBase::process_event(event);
}

} // namespace barleyui
