#include "eventqueue.h"

void EventQueue::push(std::unique_ptr<Event> event)
{
}

std::unique_ptr<Event> EventQueue::pop()
{
  return nullptr;
}

std::unique_ptr<Event> EventQueue::peek()
{
  return nullptr;
}
