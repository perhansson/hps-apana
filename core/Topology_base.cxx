//
// This implementation should not exist since it is a base class, but it
// is included here in order to compile and use it in ROOT for dynamic cast.
// 

#include "Topology_base.h"

void Topology_base::cut(const TString & prefix) {
  TString key=prefix;
};

void Topology_base::book(const TString & prefix, const TString & suffix) {
  TString key=prefix+suffix;
};
