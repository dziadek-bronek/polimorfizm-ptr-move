#ifndef CEVENTSOURCEIF_HPP
#define CEVENTSOURCEIF_HPP

/* ROLE: "source of events".
   Defined from the point of view of the framework (the caller): the framework
   needs exactly one thing - the next event, or the information that there are
   no more events. Everything else about an input (how it is configured, where
   events come from) is not the framework's business.
*/
struct CEventSourceIf
{
    virtual ~CEventSourceIf() = default;

    /* true  - 'event' is set, process it.
       false - no more events (this is the normal end, not an error). */
    virtual bool next(int& event) = 0;
};

#endif
