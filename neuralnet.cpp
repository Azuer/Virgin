#include <iostream>
#include <vector>
using namespace std;
Struct SNeuron {
     // 进入神经细胞的输入个数
     int m_NumInputs;
     
     // 为每一输入提供的权重
     vector<double> m_vecWeight;
     
     //构造函数
     SNeuron(int NumInputs);
};
SNeuron::SNeuron(int NumInputs): m_NumInputs(NumInputs+1)
 (
     // 我们要为偏移值也附加一个权重，因此输入数目上要 +1
     for (int i=0; i<NumInputs+1; ++i)
     {
         // 把权重初始化为任意的值
         m_vecWeight.push_back(RandomClamped());
     }
 }
 struct SNeuronLayer {
   　// 本层使用的神经细胞数目
　  int m_NumNeurons;
 
      // 神经细胞的层
　  vector<SNeuron>   m_vecNeurons;
 
 　 SNeuronLayer(int NumNeurons, int NumInputsPerNeuron);
}；
class neuralNet () {
private:
    int m_NumInputs;
    int m_NumOutputs;
    int m_NumHiddenLayers;
    int m_NeuronsPerHiddenLyr;

    vector<SNeuronLayer>  m_vecLayers;// 为每一层（包括输出层）存放所有神经细胞的存储器
public:
    CNeuralNet();
    void CreateNet();
    vector<double> GetWeights() const;

    int GetNumberOfWeights() const;
    void PutWeights(vetor<double> &weights);

    inline double Sigmoid(double activation,double response);
    vector<double>Update(vetor<double> &inputs);
};
int main(int argc, char const *argv[])
{
    
    return 0;
}