#include "PcHeader.h"

#include "Trace.h"
#include "TraceSys.h"
#include "TraceMath.h"
#include "SystemTrace.h"

#include "MultilayerPerceptron.h"

using namespace core;

namespace math
{
//+-------------------------------------------------------------+
//! MultilayerPerceptron										!
//+-------------------------------------------------------------+
MultilayerPerceptron::MultilayerPerceptron()
{
	m_SizeLayer	= 0;
	m_SizeUnit	= NULL;
	m_Activity	= NULL;
	m_Weight	= NULL;
	m_Delta		= NULL;

	Clear();
}

MultilayerPerceptron::~MultilayerPerceptron()
{
	Clear();
}

void MultilayerPerceptron::Clear()
{
	for(uint32_t iL=0; iL<m_SizeLayer; ++iL)
	{
		DELETE_ARRAY(m_Activity[iL]);
		DELETE_ARRAY(m_Delta[iL]);
	}

	DELETE_ARRAY(m_Activity);
	DELETE_ARRAY(m_Delta);

	if(m_SizeLayer)
	{
		for(uint32_t iP=0; iP<m_SizeLayer-1; ++iP) // Perzeptron
		{
			for(uint32_t iU=0; iU<m_SizeUnit[iP+1]; ++iU)
			{
				DELETE_ARRAY(m_Weight[iP][iU]);
			}

			DELETE_ARRAY(m_Weight[iP]);
		}
	}

	DELETE_ARRAY(m_Weight);

	DELETE_ARRAY(m_SizeUnit);
	m_SizeLayer = 0;
}

uint32_t MultilayerPerceptron::Setup(ARRAY_UINT& p_Setup)
{
	uint32_t error = 0;
	uint32_t* pSizeUnit = NULL;
	uint32_t idx = 0;

	Clear();

	if(!error && p_Setup.Size() < 2) error = TRACE_MATH(MTE_DIMENSION,_T("layer"));
	if(!error) pSizeUnit = p_Setup.Data();

	if(!error)
	{
		for(idx = 0; idx < p_Setup.Size() && !error; ++idx)
		{
			if(!pSizeUnit[idx]) error = TRACE_MATH(MTE_DIMENSION,_T("unit"));
		}
	}

	if(!error)
	{
		m_SizeLayer = p_Setup.Size();
		m_SizeUnit = new uint32_t[m_SizeLayer];
		m_Activity = new float*[m_SizeLayer];
		m_Delta = new float*[m_SizeLayer];
		m_Weight = new float**[m_SizeLayer-1]; 

		for(idx = 0; idx < m_SizeLayer; ++idx)
		{
			m_SizeUnit[idx] = pSizeUnit[idx];

			m_Activity[idx] = new float[m_SizeUnit[idx]];
			m_Delta[idx] = new float[m_SizeUnit[idx]];

			if(idx)
			{
				m_Weight[idx-1] = new float*[m_SizeUnit[idx]];

				for(uint32_t i=0; i<m_SizeUnit[idx]; ++i)
				{
					m_Weight[idx-1][i] = new float[m_SizeUnit[idx-1]];
				}
			}
		}
	}

	return error;
}

void MultilayerPerceptron::PresetWeights(float Value)
{
	if(m_SizeLayer)
	{
		for(uint32_t iP=0; iP<m_SizeLayer-1; ++iP) // Perzeptron
		{
			for(uint32_t iU1=0; iU1<m_SizeUnit[iP+1]; ++iU1)
			{
				for(uint32_t iU0=0; iU0<m_SizeUnit[iP]; ++iU0)
				{
					m_Weight[iP][iU1][iU0] = Value;
				}
			}
		}
	}
}

uint32_t MultilayerPerceptron::Layers()
{
	return m_SizeLayer;
}


uint32_t MultilayerPerceptron::Units()
{
	uint32_t units = 0;

	for(uint32_t i=0; i<m_SizeLayer; ++i)
	{
		units += m_SizeUnit[i];
	}

	return units;
}

uint32_t MultilayerPerceptron::Units(uint32_t Layer)
{
	uint32_t units = 0;

	if(Layer < m_SizeLayer) units = m_SizeUnit[Layer];

	return units;
}

uint32_t MultilayerPerceptron::Weights()
{
	uint32_t weights = 0;

	for(uint32_t i=0; i<m_SizeLayer; ++i)
	{
		if(i) weights += m_SizeUnit[i-1] * m_SizeUnit[i];
	}

	return weights;
}

uint32_t MultilayerPerceptron::Weights(uint32_t Interface)
{
	uint32_t weights = 0;

	if(Interface<m_SizeLayer-1)
		weights = m_SizeUnit[Interface] * m_SizeUnit[Interface+1];

	return weights;
}

uint32_t MultilayerPerceptron::GetActivity(uint32_t Layer, uint32_t Unit, float& Activity)
{
	uint32_t error = 0;
	Activity = 0;

	if(!error && Layer >= m_SizeLayer) error = TRACE_MATH(MTE_INDEX,_T("layer"));
	if(!error && Unit >= m_SizeUnit[Layer]) error = TRACE_MATH(MTE_INDEX,_T("unit"));
	if(!error) Activity = m_Activity[Layer][Unit];

	return error;
}

uint32_t MultilayerPerceptron::GetWeight(uint32_t Interface, uint32_t Unit0, uint32_t Unit1, float& Weight)
{
	uint32_t error = 0;
	Weight = 0;

	if(!error && Interface >= m_SizeLayer-1) error = TRACE_MATH(MTE_INDEX,_T("interface"));
	if(!error && Unit0 >= m_SizeUnit[Interface]) error = TRACE_MATH(MTE_INDEX,_T("unit"));
	if(!error && Unit1 >= m_SizeUnit[Interface+1]) error = TRACE_MATH(MTE_INDEX,_T("unit"));
	if(!error) Weight = m_Weight[Interface][Unit1][Unit0];

	return error;
}

uint32_t MultilayerPerceptron::SetActivity(uint32_t Layer, uint32_t Unit, float Activity)
{
	uint32_t error = 0;

	if(!error && Layer >= m_SizeLayer) error = TRACE_MATH(MTE_INDEX,_T("layer"));
	if(!error && Unit >= m_SizeUnit[Layer]) error = TRACE_MATH(MTE_INDEX,_T("unit"));
	if(!error) m_Activity[Layer][Unit] = Activity;

	return error;
}

uint32_t MultilayerPerceptron::SetWeight(uint32_t Interface, uint32_t Unit0, uint32_t Unit1, float Weight)
{
	uint32_t error = 0;

	if(!error && Interface >= m_SizeLayer-1) error = TRACE_MATH(MTE_INDEX,_T("interface"));
	if(!error && Unit0 >= m_SizeUnit[Interface]) error = TRACE_MATH(MTE_INDEX,_T("unit"));
	if(!error && Unit1 >= m_SizeUnit[Interface+1]) error = TRACE_MATH(MTE_INDEX,_T("unit"));
	if(!error) m_Weight[Interface][Unit1][Unit0] = Weight;

	return error;
}

float MultilayerPerceptron::Activity(const float& p_NetIn)
{
	return 1.0f/(1.0f+exp(-p_NetIn));
}


uint32_t MultilayerPerceptron::OutputSize()
{
	uint32_t size = 0;

	if(m_SizeLayer)
	{
		size = m_SizeUnit[m_SizeLayer-1];
	}

	return size;
}

uint32_t MultilayerPerceptron::InputSize()
{
	uint32_t size = 0;

	if(m_SizeLayer)
	{
		size = m_SizeUnit[0];
	}

	return size;
}

float* MultilayerPerceptron::OutActivMemory()
{
	float* mem = NULL;

	if(m_SizeLayer)
	{
		mem = m_Activity[m_SizeLayer-1];
	}

	return mem;
}

float* MultilayerPerceptron::OutDeltaMemory()
{
	float* mem = NULL;

	if(m_SizeLayer)
	{
		mem = m_Delta[m_SizeLayer-1];
	}

	return mem;
}

float* MultilayerPerceptron::InActivMemory()
{
	float* mem = NULL;

	if(m_SizeLayer)
	{
		mem = m_Activity[0];
	}

	return mem;
}

uint32_t MultilayerPerceptron::Output(ARRAY_FLOAT& p_Input, ARRAY_FLOAT& p_Output)
{
	uint32_t nError = 0;
	uint32_t nInSize = 0;
	uint32_t nOutSize = 0;
	float* pInput = NULL;
	float* pOutput = NULL;


	if(!nError && m_SizeLayer < 2) nError = TRACE_MATH(MTE_DIMENSION,_T("layer"));

	if(!nError)
	{
		nOutSize = OutputSize();
		nInSize = InputSize();
		pInput = InActivMemory();
		pOutput = OutActivMemory();
	}

	if(!nError && p_Input.Size() != nInSize) nError = TRACE_MATH(MTE_DIMENSION,_T("units"));
	if(!nError) memcpy(pInput,p_Input.Data(),nInSize*sizeof(float));

	if(!nError) nError = CalculateForward();

	if(!nError) p_Output.Resize(nOutSize);
	if(!nError) memcpy(p_Output.Data(),pOutput,nOutSize*sizeof(float));

	return nError;
}

uint32_t MultilayerPerceptron::CalculateForward()
{
	uint32_t nError = 0;
	uint32_t nInSize = 0;
	uint32_t nOutSize = 0;

	float** pInterface = NULL;
	float* pLayer = NULL;	

	float* pInput = NULL;
	float* pOutput = NULL;
	float* pWeight = NULL;

	if(!nError)
	{
		for(uint32_t nL = 1; nL < m_SizeLayer; ++nL)
		{
			nInSize = m_SizeUnit[nL-1];
			pInput = m_Activity[nL-1];		
			nOutSize = m_SizeUnit[nL];
			pOutput = m_Activity[nL];	
			pInterface = m_Weight[nL-1];

			for(uint32_t nP = 0; nP < nOutSize; ++nP)
			{
				pOutput[nP] = 0.0f;
				pWeight = pInterface[nP];

				for(uint32_t nW = 0; nW < nInSize; ++nW)
				{
					pOutput[nP] += pWeight[nW] * pInput[nW];
				}		

				pOutput[nP] = Activity(pOutput[nP]);
			}
		}
	}

	return nError;
}

uint32_t MultilayerPerceptron::CalculateBackward()
{
	uint32_t error = 0;
	uint32_t nSize0 = 0;
	uint32_t nSize1 = 0;

	float** pInterface = NULL;

	float* pActiv0= NULL;
	float* pActiv1 = NULL;
	float* pDelta0 = NULL;
	float* pDelta1 = NULL;

	if(!error && m_SizeLayer > 1)
	{
		for (uint32_t nL = m_SizeLayer-2; nL > 0; --nL)
		{
			nSize0 = m_SizeUnit[nL];
			nSize1 = m_SizeUnit[nL+1];
			pActiv0 = m_Activity[nL];
			pActiv1 = m_Activity[nL+1];
			pDelta0 = m_Delta[nL];
			pDelta1 = m_Delta[nL+1];
			pInterface = m_Weight[nL];

			for (uint32_t nU = 0; nU < nSize0; ++nU)
			{
				pDelta0[nU] = 0.0f;
				for(uint32_t nP=0; nP < nSize1; ++nP)
				{
					pDelta0[nU] += pDelta1[nP] * pInterface[nP][nU] * pActiv0[nU] * (1.0f - pActiv0[nU]);
				}
			}
		}
	}

	return error;
}

uint32_t MultilayerPerceptron::AdjustWeights(float p_Rate)
{
	uint32_t error = 0;
	float** pInterface = NULL;
	float* pWeight = NULL;
	float* pDelta = NULL;
	float* pActiv = NULL;

	if(!error)
	{
		for (uint32_t nL = 1; nL < m_SizeLayer; ++nL)
		{
			pInterface = m_Weight[nL-1];
			pDelta = m_Delta[nL];

			for (uint32_t nP = 0; nP < m_SizeUnit[nL]; ++nP)
			{
				pWeight = pInterface[nP];
				pActiv = m_Activity[nL-1];

				for (uint32_t nW = 0; nW < m_SizeUnit[nL-1]; ++nW)
				{
					pWeight[nW] = pWeight[nW] + p_Rate * pDelta[nP] * pActiv[nW];
				}
			}
		}
	}

	return error;
}

uint32_t MultilayerPerceptron::Teach(ARRAY_FLOAT& p_Input, ARRAY_FLOAT& p_Output, float p_Rate)
{
	uint32_t error = 0;
	uint32_t nInSize = 0;
	uint32_t nOutSize = 0;

	float* pInActiv = NULL;
	float* pOutActiv = NULL;
	float* pOutDelta = NULL;
	float* pOutTarget = NULL;


	if(!error && m_SizeLayer < 2) error = TRACE_MATH(MTE_DIMENSION,_T("layer"));

	if(!error)
	{
		nOutSize = OutputSize();
		nInSize = InputSize();
		pInActiv = InActivMemory();
		pOutActiv= OutActivMemory();
		pOutDelta = OutDeltaMemory();
		pOutTarget = p_Output.Data();
	}

	if(!error && p_Input.Size() != nInSize) error = TRACE_MATH(MTE_DIMENSION,_T("units"));
	if(!error && p_Output.Size() != nOutSize) error = TRACE_MATH(MTE_DIMENSION,_T("units"));

	if(!error) memcpy(pInActiv,p_Input.Data(),nInSize*sizeof(float));
	if(!error) error = CalculateForward();


	if(!error)
	{
		for (uint32_t nU = 0; nU < nOutSize; nU++)
		{
			pOutDelta[nU] = (pOutTarget[nU] - pOutActiv[nU]) * pOutActiv[nU] * (1 - pOutActiv[nU]);
		}
	}

	if(!error) error = CalculateBackward();
	if(!error) error = AdjustWeights(p_Rate); 

	return error;
}

} // namespace