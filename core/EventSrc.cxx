#include "EventSrc.h"

bool EventSrc::copy_to_interface(AtlEvent &) {return false;};
int EventSrc::Open(std::list<TString>) {return 0;};
void EventSrc::Close(void) {};
void EventSrc::SetBranches(void) {};
void EventSrc::Initialise(void) {};
void EventSrc::Finalise(void) {};
double EventSrc::GetNEntries(void) {return 0.0;};
void EventSrc::GetEntry(int) {};
