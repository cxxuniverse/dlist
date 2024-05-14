#pragma once

#include <functional>
#include <iostream>
#include <unordered_map>

using EventHandler = std::function<void()>;

namespace cxc
{

// Base class for event listeners.
struct EventListenerBase
{
    enum class Events
    {
    };
};

// Event listener template class.
template <typename EventEnum> struct EventListener : public EventListenerBase
{
  private:
    // Map of event handlers.
    std::unordered_map<EventEnum, EventHandler> handlers{};

  public:
    // Add an event handler.
    void add(EventEnum event_type, EventHandler callback_fn);

    // Trigger an event.
    void trigger(EventEnum event_type);
};

} // namespace cxc

#include "../src/events.cpp"
