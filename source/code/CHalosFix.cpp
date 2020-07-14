#include "CHalosFix.h"
#include "ManhuntRW.h"
#include "ManhuntSDK.h"

int*& tempRenderStates = *(int**)0x7D2ADC;
int*& dword_7D2B2C = *(int**)0x7D2B2C;
int& dword_7D2AD8 = *(int*)0x7D2AD8;
int& m_nHaloAmount = *(int*)0x7D5E30;
int& dword_7D2A98 = *(int*)0x7D2A98;

int*& dword_7D5A30 = *(int**)0x7D5A30;
int*& dword_7D5A34 = *(int**)0x7D5A34;
int*& dword_7D5A38 = *(int**)0x7D5A38;
int*& dword_7D5A4C = *(int**)0x7D5A4C;



/*
void CHalosFix::HookRenderPickups()
{
	int nHaloCounter = 0;
	int nHaloOffset = 0;

	if (m_nHaloAmount)
	{
		++dword_7D2A98;
		// prepare rendering flags

		/*RwRenderStateSetA(rwRENDERSTATESRCBLEND, rwBLENDNABLEND);
		RwRenderStateSetA(rwRENDERSTATESRCBLEND, rwBLENDNABLEND);
		RwRenderStateSetA(rwRENDERSTATEVERTEXALPHAENABLE, 0);

		RwRenderStateSet(rwRENDERSTATESRCBLEND, rwBLENDONE);
		RwRenderStateSet(rwRENDERSTATEDESTBLEND, rwBLENDONE);

		tempRenderStates[dword_7D2AD8] = rwRENDERSTATEVERTEXALPHAENABLE;
		RwRenderStateSetA(rwRENDERSTATEVERTEXALPHAENABLE, dword_7D2B2C[dword_7D2AD8]);

		++dword_7D2AD8;

		RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, 1);
		tempRenderStates[dword_7D2AD8] = 14;

		RwRenderStateSetA(rwRENDERSTATEFOGENABLE, dword_7D2B2C[dword_7D2AD8]);
		++dword_7D2AD8;

		RwRenderStateSet(rwRENDERSTATEFOGENABLE, 0);
		tempRenderStates[dword_7D2AD8] = rwRENDERSTATECULLMODE;

		RwRenderStateSetA(rwRENDERSTATECULLMODE, 4 * dword_7D2AD8 + 0x7D2B2C);
		++dword_7D2AD8;
		RwRenderStateSet(rwRENDERSTATECULLMODE, rwCULLMODECULLNONE);
		tempRenderStates[dword_7D2AD8] = rwRENDERSTATEZWRITEENABLE;
		RwRenderStateSetA(rwRENDERSTATEZWRITEENABLE, dword_7D2B2C[dword_7D2AD8]);


		++dword_7D2AD8;
		RwRenderStateSet(rwRENDERSTATEZWRITEENABLE, 0);

		tempRenderStates[dword_7D2AD8] = 6;

		RwRenderStateSetA(rwRENDERSTATEZTESTENABLE, dword_7D2B2C[dword_7D2AD8]);

		++dword_7D2AD8;

		RwRenderStateSet(rwRENDERSTATEZTESTENABLE, 1);

		tempRenderStates[dword_7D2AD8] = 2;

		RwRenderStateSetA(rwRENDERSTATETEXTUREADDRESS, dword_7D2B2C[dword_7D2AD8]);
		++dword_7D2AD8;
		RwRenderStateSet(rwRENDERSTATETEXTUREADDRESS, rwTEXTUREADDRESSWRAP);
		tempRenderStates[dword_7D2AD8] = 9;
		RwRenderStateSetA(rwRENDERSTATETEXTUREFILTER, dword_7D2B2C[dword_7D2AD8]);
		++dword_7D2AD8;
		//RwRenderStateSetA(rwRENDERSTATETEXTUREFILTER, dword_7D2B2C[dword_7D2AD8]);
		RwRenderStateSet(rwRENDERSTATETEXTUREFILTER, rwFILTERLINEAR);
		RwRenderStateSet(rwRENDERSTATESRCBLEND, rwBLENDSRCALPHA);
		RwRenderStateSet(rwRENDERSTATEDESTBLEND, rwBLENDONE);

		nHaloCounter = 0;

		if (m_nHaloAmount > 0)
		{
			nHaloOffset = 0;
			do
			{
				int v5 = dword_7D5A30[nHaloOffset];
				int v6 = dword_7D5A34[nHaloOffset];
				int v7 = dword_7D5A38[nHaloOffset];
				Render3DHalo((int)&v5, 1.0f,120,120,120, dword_7D5A4C[nHaloOffset]);
				nHaloCounter++;
				nHaloOffset += 8;
			} while (nHaloCounter < m_nHaloAmount);
		}
		--dword_7D2A98;
	    RwRenderStateSet(rwRENDERSTATESRCBLEND,*(int*)0x7D2AA4);
	    RwRenderStateSet(rwRENDERSTATEDESTBLEND, 0);
		RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, 0);
	}

}

void CHalosFix::Render2DHalo(int ptr, float scale, int r, int g, int b, float range)
{
	Call<0x5FB6D0, int, float, int, int, int, float>(ptr, scale, r,g,b,range);
}

void CHalosFix::Render3DHalo(int ptr, float scale, int r, int g, int b, float range)
{
	Call<0x5FBBD0, int, float, int, int, int, float>(ptr, scale, r, g, b, range);
}
*/