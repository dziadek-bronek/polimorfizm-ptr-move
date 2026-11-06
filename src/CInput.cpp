#include "include/CInputPreparator.hpp"

#include <cstddef>
#include <cstdio>
#include <iostream>

#include "include/throw.hpp"

namespace
{
/* Concrete inputs: hidden here, nobody outside this file can name them.
   Fields are part of the implementation, so they are declared in descendants
   only (the role interface CEventSourceIf has none). */

struct CVectorInput : CEventSourceIf
{
    explicit CVectorInput(std::vector<int> events_)
        : events(std::move(events_))
    {
    }

    bool next(int& event) override
    {
        if (index >= events.size())
        {
            return false;
        }
        event = events[index++];
        return true;
    }

  private:
    std::vector<int> events;
    std::size_t index{0};
};

struct CKeyboardInput : CEventSourceIf
{
    /* End of stdin (or something that is not a number) ends the events. */
    bool next(int& event) override
    {
        return static_cast<bool>(std::cin >> event);
    }
};
} // namespace

std::unique_ptr<CEventSourceIf> prepareInput(InputKind kind,
                                             std::unique_ptr<VOID> payload)
{
    switch (kind)
    {
    case InputKind::Vector:
    {
        auto* vectorPayload = dynamic_cast<CVectorInputPayload*>(payload.get());
        if (nullptr == vectorPayload)
        {
            THROW2("Exit", " on error: InputKind::Vector needs "
                           "CVectorInputPayload");
        }
        return std::make_unique<CVectorInput>(std::move(vectorPayload->x));
    }

    case InputKind::Keyboard:
        return std::make_unique<CKeyboardInput>();
    }

    THROW2("Exit", " on error: unknown InputKind");
}
