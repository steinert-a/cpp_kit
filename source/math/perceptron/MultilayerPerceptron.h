#pragma once

namespace math
{
//+-------------------------------------------------------------+
//! MultilayerPerceptron										!
//+-------------------------------------------------------------+
class MultilayerPerceptron
{
public:
	MultilayerPerceptron();
	~MultilayerPerceptron();

private:
	uint32_t	m_SizeLayer;
	uint32_t*	m_SizeUnit;
	float**		m_Activity;
	float***	m_Weight;
	float**		m_Delta;

private:
	uint32_t OutputSize();
	uint32_t InputSize();
	float* OutActivMemory();
	float* OutDeltaMemory();
	float* InActivMemory();

	uint32_t CalculateForward();
	uint32_t CalculateBackward();
	uint32_t AdjustWeights(float); 
	float Activity(const float&);

public:
	void Clear();
	uint32_t Setup(core::ARRAY_UINT&);	
	void PresetWeights(float);

	uint32_t Layers();
	uint32_t Units();	
	uint32_t Units(uint32_t);

	uint32_t Weights();
	uint32_t Weights(uint32_t);

	uint32_t GetActivity(uint32_t,uint32_t,float&);
	uint32_t GetWeight(uint32_t,uint32_t,uint32_t,float&);
	uint32_t SetActivity(uint32_t,uint32_t,float);
	uint32_t SetWeight(uint32_t,uint32_t,uint32_t,float);

	uint32_t Output(core::ARRAY_FLOAT&,core::ARRAY_FLOAT&);
	uint32_t Teach(core::ARRAY_FLOAT&,core::ARRAY_FLOAT&,float);
};

} // namespace

typedef math::MultilayerPerceptron	MULTILAYER_PERCEPTRON;	