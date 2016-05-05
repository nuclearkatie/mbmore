// Implements the Region class
#include "InteractRegion.h"
#include "behavior_functions.h"

#include <iostream>
#include <string>


namespace mbmore {


// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
InteractRegion::InteractRegion(cyclus::Context* ctx)
  : cyclus::Region(ctx) {
    //  kind_ = "InteractRegion";
  cyclus::Warn<cyclus::EXPERIMENTAL_WARNING>("the InteractRegion agent is experimental.");

}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  InteractRegion::~InteractRegion() {}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  void InteractRegion::Build(cyclus::Agent* parent) {
    cyclus::Agent::Build(parent);
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
std::map<std::string, double>
  InteractRegion::GetWeights(std::string eqn_type) {
    //TODO: use eqn_type ot expand in offering PE or AQ results
    return p_wts;
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
double InteractRegion::GetLikely(std::string phase, double eqn_val) {

  std::pair<std::string, std::vector<double> > likely_pair = likely[phase];
  std::string function = likely_pair.first;
  std::vector<double> constants = likely_pair.second;
  
  /*
  std::map<std::string, double> curr_likely;
  
  std::map<std::string,
	   std::pair<std::string, std::vector<double> > >::iterator eqn_it;

  for(eqn_it = likely.begin(); eqn_it != likely.end(); eqn_it++) {
    std::string phase = eqn_it->first;
    std::string function = eqn_it->second.first;
    std::vector<double> constants = eqn_it->second.second;
  */

    double phase_likely = CalcYVal(function, constants, eqn_val);
    std::cout << "phase " << phase << " fn " << function << "likely " << phase_likely << std::endl;
    return phase_likely;

    //    curr_likely[phase] = phase_likely;
    //  }
    //  return curr_likely;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
std::string InteractRegion::str() {
  std::string s = cyclus::Agent::str();

  s += " has insts: ";
  for (std::set<Agent*>::const_iterator inst = children().begin();
       inst != children().end();
       inst++) {
    s += (*inst)->prototype() + ", ";
  }
  return s;
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
extern "C" cyclus::Agent* ConstructInteractRegion(cyclus::Context* ctx) {
  return new InteractRegion(ctx);
}
  
}  // namespace mbmore