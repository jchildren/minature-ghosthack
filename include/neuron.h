//neuron.h

#ifndef NEURON_H
#define NEURON_H

#include <vector>
#include <cstdlib>

struct Connection{
  double weight;
  double deltaWeight;
};

class Neuron;

typedef std::vector<Neuron> Layer;

class Neuron{
public:
  Neuron(unsigned numOutputs, unsigned myIndex);
  void setOutputVal(double val) { m_outputVal = val; };
  double getOuputVal(void) const { return m_outputVal; };
  void feedFoward(const Layer &prevLayer);

private:
  static double transferFunction(double x);
  static double transferFunctionDerivative(double x);
  static double randomWeight(void) { return std::rand() / double(RAND_MAX); }
  double m_outputVal;
  std::vector<Connection> m_outputWeights;
  unsigned m_myIndex;

};

#endif
