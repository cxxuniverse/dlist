#ifndef CXC_EVENTS_CPP
#define CXC_EVENTS_CPP

#include "events.h"

namespace cxc
{

/**
 * @brief Adds an event handler for a specific event type.
 *
 * @tparam EventEnum The type of event enum.
 * @param event_type The event type to add the handler for.
 * @param callback_fn The function to be called when the event occurs.
 */
template <typename EventEnum> void EventListener<EventEnum>::add(EventEnum event_type, EventHandler callback_fn)
{
    handlers[event_type] = callback_fn;
}

/**
 * @brief Triggers the event with the specified event type.
 *
 * @tparam EventEnum The type of event enum.
 * @param event_type The event type to trigger.
 * @throws std::runtime_error if no valid event handler is found for the event type.
 */
template <typename EventEnum> void EventListener<EventEnum>::trigger(EventEnum event_type)
{

    if (!handlers[event_type])
        throw std::runtime_error("EventListener could not locate a valid event handler.");

    handlers[event_type]();
}

} // namespace cxc

#endif