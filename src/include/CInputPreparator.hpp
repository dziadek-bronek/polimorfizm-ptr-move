#ifndef CINPUTPREPARATOR_HPP
#define CINPUTPREPARATOR_HPP

#include "CEventSourceIf.hpp"
#include "VOID.hpp"
#include <memory>
#include <vector>

/* The only thing the caller (main) decides: WHICH kind of input it wants.
   Details of each kind are the business of the preparator. */
enum class InputKind
{
    Vector,  /* events come from a vector; payload: CVectorInputPayload */
    Keyboard /* events are integers read from stdin; no payload          */
};

/* Contract of the payload for InputKind::Vector. This type is the knowledge
   shared by the caller and the preparator, so it lives here. */
using CVectorInputPayload = CWrapperVOID_1<std::vector<int>>;

/* Prepares a ready-to-use source of events.
   Ownership of 'payload' is taken. Throws (const char*) when the payload does
   not match the kind. */
std::unique_ptr<CEventSourceIf> prepareInput(
    InputKind kind, std::unique_ptr<VOID> payload = nullptr);

#endif
