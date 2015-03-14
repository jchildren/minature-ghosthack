//neuron.cpp

#include <cmath>
#include "neuron.h"

double Neuron::transferFunction(double x){
  return std::tanh(x);
};

double transferFunctionDerivative(double x){
  return 1.0 - x * x;
};

void Neuron::feedFoward(const Layer &prevLayer){
  double sum = 0;

  for (unsigned n = 0; n < prevLayer.size(); ++n){
    sum += prevLayer[n].m_outputVal() *
      prevLayer[n].m_outputWeights[m_myIndex].weight;
  }

  m_outputVal  = Neuron::transferFunction(sum);

};

Neuron::Neuron(unsigned numOutputs, unsigned myIndex){
  for (unsigned c = 0; c < numOutputs; ++c) {
    m_outputWeights.push_back(Connection());
    m_outputWeights.back().weight = randomWeight();
  }

  m_myIndex = myIndex
};
