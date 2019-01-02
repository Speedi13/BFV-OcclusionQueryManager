struct eastl::vector
{
  __int64 mpBegin;
  __int64 mpEnd;
  __int64 mpCapacity;
  __int64 mAllocator;
};

struct ObjectRenderInfo
{
  float worldTransform[16];
  _OWORD vertices[8];
};

struct __declspec(align(8)) BatchQuery
{
  int count;
  _DWORD status;
  _BYTE queriesInitialized;
  _DWORD dwordC;
  float *outObjectScreenAreaCoverage;
  int doneCounter;
  int dword1C;
  ObjectRenderInfo *renderInfos__m_firstElement;
  __int64 renderInfos__m_lastElement;
  __int64 renderInfos__m_arrayBound;
  void *renderInfos__padding;
  ObjectRenderInfo renderInfos__data[32];
  DxRenderQuery *m_dxQuerys;
  __int64 padding;
};

struct __declspec(align(8)) WorldOcclusionQueryRenderModule
{
  __int64 m_callback__mpBegin;
  __int64 m_callback__mpEnd;
  __int64 m_callback__mpCapacity;
  __int64 m_callback__mAllocator;
  _BYTE gap20[16];
  CRITICAL_SECTION m_ciricalSection;
  __int64 field_58;
  __int64 m_Allocator;
  __int64 field_68;
  BatchQuery *m_usedbatches_mpBegin;
  _QWORD m_usedbatches_mpEnd;
  __int64 m_usedbatches_mpCapacity;
  __int64 m_usedbatches_mAllocator;
  _QWORD m_freeBatchesIndices_mpBegin;
  _QWORD m_freeBatchesIndices_mpEnd;
  __int64 m_freeBatchesIndices_mCapacity;
  __int64 m_freeBatchesIndices_mAllocator;
};


struct __declspec(align(8)) SoldierOcclusionQueryManager::occlusionQuery
{
  ObjectRenderInfo m_objects[32];
  float m_outVisibility[32];
  _BYTE gap1880[128];
  _DWORD m_batchQueryHandle;
  _DWORD m_dwQueryCount;
  _BYTE queriesInitialized;
  _BYTE gap1909[32];
  _BYTE byte1929;
};

struct __declspec(align(8)) struct_SoldierOcclusionQueryManager
{
  _BYTE gap0[40];
  _QWORD qword28;
  __int64 m_pPlayerManager;
  WorldOcclusionQueryRenderModule *m_WorldOcclusionQueryRenderModule;
};
struct __declspec(align(8)) DxRendererVtable
{
  void *sub_141BC96A0;
  void *sub_Return1;
  void *sub_141BDA410;
  void *sub_141C778B0;
  void *sub_141C77890;
  void *sub_141C1AD00;
  void *sub_14091E1E0_1;
  void *sub_14091E1E0_2;
  void *beginFrame;
  void *endFrame;
  void *acquireThreadOwnership;
  void *releaseThreadOwnership;
  void *sub_141BD8900;
  void *sub_141BD99E0;
  void *getScreenInfo;
  void *sub_140959D70;
  void *sub_141BE0D10;
  void *sub_141BE0D00;
  void *sub_141BE0CF0;
  void *sub_141BE1D00;
  void *sub_141BD9D90;
  void *sub_14091E1E0_3;
  void *sub_141BD95B0;
  void *sub_141BD8B60;
  void *sub_141BD73C0;
  void *sub_141BD19C0;
  void *sub_141BD3FE0;
  void *sub_141BD3740;
  void *sub_1404E95D0;
  void *sub_141C1AC90;
  void *createQuery;
  void *sub_141BD1B90;
  void *sub_141BDDE70_1;
  void *sub_141BDE040;
  void *sub_141BDDE70_2;
  void *sub_141BD6870;
  void *sub_141BD19E0;
  void *sub_141C1AEA0;
  void *sub_1429CFF30_1;
  void *sub_1429CFF30_2;
  void *sub_14091E1E0_4;
  void *sub_141BDD420;
  void *sub_141BE2490;
  void *sub_141BE2290;
  void *sub_141BDF170;
  void *getQueryData;
  void *sub_141BD97A0;
  void *sub_141C155C0;
  void *sub_141C18820;
  void *sub_141C155B0;
  void *sub_141C18810;
  void *sub_1419521B0_1;
  void *sub_1429CFF30_3;
  void *sub_14091E1E0_5;
  void *getDxDisplaySettings;
  void *sub_141BD77C0;
  void *sub_141BDAD30;
  void *sub_141BD95C0;
  void *sub_14091E1E0_6;
  void *sub_14091E1E0_7;
  void *sub_141BD8A80;
  void *sub_141BDE050;
  void *sub_141C16060;
  void *sub_141C187F0;
  void *sub_1419521B0_2;
  void *sub_141BD5080;
  void *getDxDisplaySettings_;
  void *sub_141BD3F00;
  void *sub_141BD19A0;
  void *createTexture;
};

struct __declspec(align(4)) DxRenderer
{
  DxRendererVtable *vtable;
  _BYTE gap8[2216];
  _QWORD qword8B0;
  _QWORD qword8B8;
  _QWORD qword8C0;
  _QWORD qword8C8;
  _BYTE gap8D0[48];
  _DWORD dword900;
  _BYTE gap904[4];
  _DWORD dword908;
  _BYTE byte90C;
  _BYTE gap90D[3];
  _QWORD qword910;
  _QWORD qword918;
  _QWORD qword920;
  _QWORD qword928;
  _QWORD qword930;
  _QWORD qword938;
  _BYTE gap940[16];
  _QWORD qword950;
  _DWORD dword958;
  _BYTE gap95C[44];
  _QWORD qword988;
  _QWORD qword990;
  _QWORD qword998;
  _QWORD qword9A0;
  _QWORD qword9A8;
  _BYTE gap9B0[48];
  _BYTE byte9E0;
  _BYTE gap9E1[7];
  _QWORD qword9E8;
  _QWORD qword9F0;
  _BYTE gap9F8[1384];
  _QWORD qwordF60;
  _QWORD qwordF68;
  _QWORD qwordF70;
  _QWORD qwordF78;
  _QWORD qwordF80;
  _QWORD qwordF88;
  _QWORD qwordF90;
  _QWORD qwordF98;
  _BYTE gapFA0[8];
  _QWORD qwordFA8;
  _QWORD qwordFB0;
  _QWORD qwordFB8;
  _BYTE gapFC0[488];
  _QWORD qword11A8;
  _DWORD dword11B0;
  _WORD word11B4;
};
