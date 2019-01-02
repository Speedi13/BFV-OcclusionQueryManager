enum RenderQueryType
{
	RenderQueryType_Occlusion  = 2
};

class DxRenderQuery
{
public:
	void* vtable; //0x0000
	DWORD dword8; //0x0008
	DWORD dwordC; //0x000C
	QWORD qword10; //0x0010 pointer to the allocator i guess
	fb::RenderQueryType m_type; //0x0018
	int m_dwQueryCount; //0x001C
	ID3D11Query** m_queries; //0x0020
};

class WorldOcclusionQueryRenderModule
{
public:
	class ObjectRenderInfo
	{
	public:
		LinearTransform worldTransform;
		Vec4 vertices[8]; //bounding box corners
	};
	class BatchQuery
	{
	public:
		enum QueryStatus
		{
			QS_Init,				// constant 0x0
			QS_WaitingForResult,	// constant 0x1
			QS_Done,				// constant 0x2
			QS_Inactive,			// constant 0x3
		}; // QueryStatus

		unsigned int count; //0x0000
		enum QueryStatus status; //0x0004
		bool queriesInitialized; //0x0008
		PAD(0x3);
		DWORD dwordC; //0x000C
		float* outObjectScreenAreaCoverage; //0x0010
		DWORD doneCounter; //0x0018
		DWORD DWORD1C; //0x001C
		fixed_vector< ObjectRenderInfo, 32, 1> renderInfos; //0x0020
		DxRenderQuery* m_dxQuerys; //0x1840
		PAD(0x8);
	};// Size = 0x1850
	
	_QWORD m_callback__mpBegin;	 //00000000 //vector
	_QWORD m_callback__mpEnd;	 //00000008
	_QWORD m_callback__mpCapacity;//00000010
	_QWORD m_callback__mAllocator;//00000018
	PAD(0x10); //0x0020
	CRITICAL_SECTION m_ciricalSection; //0x0030
	PAD(0x8);//0x0058
	void* m_Allocator;//0x0060
	PAD(0x8);//0x0068
	_QWORD m_usedbatches__mpBegin;	 //00000070 //vector
	_QWORD m_usedbatches__mpEnd;	 //00000078
	_QWORD m_usedbatches__mpCapacity;//00000080
	_QWORD m_usedbatches__mAllocator;//00000088

	_QWORD m_freeBatchesIndices__mpBegin;	//00000090 //vector
	_QWORD m_freeBatchesIndices__mpEnd;		//00000098
	_QWORD m_freeBatchesIndices__mCapacity;	//000000A0
	_QWORD m_freeBatchesIndices__mAllocator;//000000A8

	WorldOcclusionQueryRenderModule::BatchQuery* GetBatchById( unsigned int handle )
	{
		WorldOcclusionQueryRenderModule::BatchQuery* usedbatches = (WorldOcclusionQueryRenderModule::BatchQuery*)this->m_usedbatches__mpBegin;
		return &usedbatches[handle];
	}
};


struct RenderScreenInfo
{
	unsigned int width; //0x0000 
	unsigned int height; //0x0004 
	unsigned int windowWidth; //0x0008 
	unsigned int windowHeight; //0x000C 

};//Size=0x0010

class WorldViewDesc
{
public:
	char _0x0000[32];
	RenderScreenInfo viewport; //0x0020
};//Size=0x0030

class WorldRenderer
{
public:
	char _0x0000[2248];
	class WorldOcclusionQueryRenderModule* m_WorldOcclusionQueriesRenderModule; //0x08C8 
	char _0x08D0[2096];

	class /*fb::WorldRenderer::*/RootView
	{
	public:
		char _0x0000[3232];
		WorldViewDesc m_rootView; //0x0CA0
	};

	RootView m_rootviews; //0x1100 
};

class WorldRenderModule
{
public:
	char _0x0000[56];
	WorldRenderer* m_worldRenderer; //0x0038 
};

class ClientLevel
{
public:
	char _0x0000[0xF8];
	WorldRenderModule* m_worldRenderModule; //0x00F8 
};

class ClientGameContext
{
public:
	ClientLevel* m_pClientLevel; //0x0030 
};

class DxRenderer
{
public:
	virtual void Function0( );
	virtual void Function1(); //
	virtual void Function2(); //
	virtual void Function3(); //
	virtual void Function4(); //
	virtual void Function5(); //
	virtual void Function6(); //
	virtual void Function7(); //
	virtual void beginFrame(); // fb::DxRenderer::beginFrame
	virtual void endFrame(); // fb::DxRenderer::endFrame
	virtual void acquireThreadOwnership(); //
	virtual void releaseThreadOwnership(); //
	virtual void Function12(); //
	virtual unsigned int GetNumberOfScreens(); //
	virtual RenderScreenInfo* getScreenInfo( unsigned int ScreenNbr ); //fb::DxRenderer::getScreenInfo;
	Screen* GetScreenByNumber( unsigned int ScreenNbr ){ return  (Screen*)( (DWORD_PTR)( (DWORD_PTR)this->getScreenInfo( ScreenNbr ) - (DWORD_PTR)0x68 ) ); }
	virtual void Function15(); //
	virtual void Function16(); //
	virtual void Function17(); //
	virtual void Function18(); //
	virtual void Function19(); //
	virtual void Function20(); //
	virtual void Function21(); //
	virtual void Function22(); //
	virtual void Function23(); //
	virtual void Function24(); //
	virtual void Function25(); //
	virtual void Function26(); //
	virtual void Function27(); //
	virtual void Function28(); //
	virtual void Function29(); //
	virtual class DxRenderQuery * createQuery(void* Allocator, RenderQueryType type, uint32_t size, char* name); // [fb::DxRenderer::createQuery] [ 148F50960 ]
	virtual void Function31(); //
	virtual void Function32(); //
	virtual void Function33(); //
	virtual void Function34(); //
	virtual void Function35(); //
	virtual void Function36(); //
	virtual void Function37(); //
	virtual void Function38(); //
	virtual void Function39(); //
	virtual void Function40(); //
	virtual void Function41(); //
	virtual void Function42(); //
	virtual void Function43(); //
	virtual void Function44(); //
	virtual bool getQueryData( DxRenderQuery* pDxRenderQuery, unsigned int RenderQueryIndex, __int64 OutData, unsigned int OutDataSize); // [fb::DxRenderer::getQueryData] [ 141BD9840 ]
	virtual void Function46(); //
	virtual void Function47(); //
	virtual void Function48(); //
	virtual void Function49(); //
	virtual void Function50(); //
	virtual bool Function51(void); //
	virtual void Function52(); //
	virtual class DxDisplaySettings* getDxDisplaySettings(); //
	virtual void Function54(); //
	virtual void Function55(); //
	virtual void Function56(); //
	virtual void Function57(); //
	virtual void Function58(); //
	virtual void Function59(); //
	virtual void Function60(); //
	virtual void Function61(); //
	virtual void Function62(); //
	virtual void Function63(); //
	virtual void Function64(); //
	virtual void Function65(); //
	virtual void Function66(); //
	virtual void Function67(); //
	virtual void Function68(); //
	virtual void createTexture(); // fb::DxRenderer::createTexture
};

template <class T, INT Count, INT PadSize>
class fixed_vector
{
public:
	T* m_firstElement;
	T* m_lastElement;
	T* m_arrayBound;
	LPVOID m_pad[PadSize];
	T m_data[Count];

public:
	fixed_vector() {
		m_firstElement = (T *)m_data;
		m_lastElement = (T *)m_data;
		m_arrayBound = (T *)&m_data[Count];
	}

	void push_back(T *const value) {
		if (m_lastElement > m_arrayBound) {

			return;
		}
		*m_lastElement = *value;
		m_lastElement = m_lastElement + 1;
	};

	void clear() {
		m_firstElement = m_data;
		m_lastElement = m_data;
		m_arrayBound = (T *)&m_data[Count];
	}

	UINT Size() {
		return ((DWORD_PTR)m_lastElement - (DWORD_PTR)m_firstElement) / sizeof(T);
	}

	T At(INT nIndex) {
		return m_firstElement[nIndex];
	}

	T operator [](INT index) { return At(index); }
};

template <class T>
class vector
{
private:
	T* m_firstElement;
	T* m_lastElement;
	T* m_arrayBound;
	void* vftable;
public:
	size_t size()
	{
		return (((intptr_t)this->m_lastElement - (intptr_t)this->m_firstElement) / sizeof(T));
	}
	T at(int nIndex)
	{
		return *(T*)((intptr_t)m_firstElement + (nIndex * sizeof(T)));
	}
	T operator [](int index)
	{
		return at(index);
	}
};

#if 0 //some test code
//F3 0F 59 C1 F3 0F 59 15 0A 00 00 00 F3 0F 51 CA 90 90 0F 59 C1 C3 00 00 61 49 00 00 00 00 00 00
#pragma code_seg(push, ".text")
__declspec(allocate(".text"))
    UCHAR __math_[] = {
//float __fastcall __math_(float flDistance, float x200, float flVisibility)
	//return (float)(flDistance * x200) * fsqrt(flVisibility * 921600.0);
0xF3, 0x0F, 0x59 , 0xC1,							//- mulss xmm0,xmm1
0xF3, 0x0F, 0x59 , 0x15 , 0x0A, 0x00, 0x00, 0x00,	//- mulss xmm2,[023D0016] { [921600.00] }
0xF3, 0x0F, 0x51, 0xCA,								//- sqrtss xmm1,xmm2
0x90,												//- nop 
0x90,												//- nop 
0x0F, 0x59, 0xC1,									//- mulps xmm0,xmm1
0xC3,												//- ret 
0x00, 0x00, 0x61, 0x49, //dword_143669DB8 dd 49610000h
};
#pragma code_seg()
typedef float (__fastcall* t_Mathz)(float flDistance, float x200, float flVisibility );
t_Mathz MathShellCode = (t_Mathz)&__math_;
#endif