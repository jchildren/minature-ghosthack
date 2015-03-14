// main.cpp

#include <vector>
#include <iostream>
#include <cstdlib>
#include <cassert>
#include <cmath>

struct Connection{
  double weight;
  double deltaWeight;
}

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
  std::vector<Connections> m_outputWeights;
  unsigned m_myIndex;

};

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

class Net{
public:
  Net(const std::vector<unsigned> topology);
  void feedForward(const std::vector<double> &inputVals);
  void backProp(const std::vector<double> &targetVals){};
  void getResults(std::vector<double> &resultVals) const{};

private:
  std::vector<Layer> m_layers;
};

void Net::feedForward(const std::vector<double> &inputVals){
  std::assert(inputVals.size() == m_layers[0].size() - 1);

  for (unsigned i = 0; i < inputVals.size(); ++i) {
    m_layers[0][i].setOutputVal(inputVals[i]);
  }

  for (unsigned layerNum = 1; layerNum < m_layers.size(); ++layerNum) {
    Layer &prevLayer = m_layers[layerNum - 1];
    for (unsigned n = 0; n < m_layers[layerNum].size() - 1; ++n){
      m_layers[layerNum][n].feedForward();
    }
  }

}

Net::Net(const std::vector<unsigned> topology){
  unsigned numLayers = topology.size();
  for (unsigned layerNum = 0; layerNum < numLayers; ++layerNum){
    m_layers.push_back(Layer());
    unsigned numOutputs = layerNum == topology.size() - 1 ? 0 : topology[layerNum + 1]

    for (unsigned neuronNum = 0; neuronNum <= topology[layerNum]; ++neuronNum){
      m_layers.back().push_back(Neuron(numOutputs, neuronNum));
      std::cout << "Made a Neuron!" << std::endl;
    }
  }
};

int main(){

  std::vector<unsigned> topology;
  topology.push_back(3);
  topology.push_back(2);
  topology.push_back(1);
  Net myNet(topology);

  std::vector<double> inputVals;
  myNet.feedForward(inputVals);

  std::vector<double> targetVals;
  myNet.backProp(targetVals);

  std::vector<double> resultVals;
  myNet.getResults(resultVals);

  return 0;
}
