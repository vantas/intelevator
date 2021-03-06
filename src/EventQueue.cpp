#include "EventQueue.h"
#include "Clock.h"
#include <vector>

EventQueue::EventQueue() {}

EventQueue::~EventQueue() {
  while (!_eventQueue.empty()) {
    _eventQueue.pop();
  }
}

bool EventQueue::hasNextEvent() const { return !_eventQueue.empty(); }

std::shared_ptr<Event> EventQueue::top() const {
  if (_eventQueue.empty())
    return std::shared_ptr<Event>(nullptr);

  return _eventQueue.top();
}

std::shared_ptr<Event> EventQueue::pop() {
  if (_eventQueue.empty())
    return std::shared_ptr<Event>(nullptr);

  auto event = _eventQueue.top();
  _eventQueue.pop();

  return event;
}

void EventQueue::push(std::shared_ptr<Event> event) {
  _eventQueue.push(event);
}

void EventQueue::refresh(const unsigned long currentTime) {
  std::vector<std::shared_ptr<Event>> events;

  while (!_eventQueue.empty()) {
    auto event = _eventQueue.top();
    // event->setTime(event->getTime() - currentTime);
    _eventQueue.pop();
    events.push_back(event);
  }

  for (auto event : events)
    _eventQueue.push(event);
}