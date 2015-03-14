//net.h

#ifndef NET_H
#define NET_H

#include <iostream>
#include <vector>
#include <cassert>
#include "neuron.h"

class Net{
public:
  Net(const std::vector<unsigned> topology);
  void feedForward(const std::vector<double> &inputVals);
  void backProp(const std::vector<double> &targetVals){};
  void getResults(std::vector<double> &resultVals) const{};

private:
  std::vector<Layer> m_layers;
};

#endif
