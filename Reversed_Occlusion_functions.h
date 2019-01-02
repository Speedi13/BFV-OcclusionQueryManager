// called from 1416FD220
//Function address: 1421FDB00
//function pattern: F3 0F 11 86 00 02 00 00 48 8B 75 28
__int64 __fastcall fb::SoldierOcclusionQueryManager::updateBatchedOcclusionQueries(struct_SoldierOcclusionQueryManager *this)
{
  struct_SoldierOcclusionQueryManager *v1; // rbp
  __int64 pPlayerManager; // rdi
  __int64 v3; // r13
  __int64 LocalPlayersStart; // r12
  unsigned __int64 dwLocalPlayerCount; // rcx
  __int64 pLocalPlayer; // rbx
  __int64 LocalPlayerId; // r14
  __int64 dwLocalPlayerId; // rdi
  __int64 LocalPlayerQueryManagerOffset; // rsi
  __int64 pLocalClientSoldierEntity; // rax
  __int64 bDontUpdateMatrix; // r8
  __m128i *LocalTransformPos; // rax
  __int64 v13; // rsi
  unsigned int v14; // er14
  SoldierOcclusionQueryManager::occlusionQuery *OcclusionQuery; // rbx
  unsigned int handle; // edx
  __int64 cntr; // r10
  char mSoldierTransform; // [rsp+40h] [rbp-78h]
  __int128 v20; // [rsp+50h] [rbp-68h]
  eastl::vector localPlayers; // [rsp+60h] [rbp-58h]
  bool v22; // [rsp+C0h] [rbp+8h]
  unsigned __int64 LocalPlayerCount; // [rsp+C0h] [rbp+8h]

  v1 = this;
  _mm_storeu_si128((__m128i *)&localPlayers, (__m128i)0i64);
  _mm_storeu_si128((__m128i *)&localPlayers.mpCapacity, (__m128i)0i64);
  pPlayerManager = this->m_pPlayerManager;
  LOBYTE(this) = 1;
  v22 = sub_14173FF60((__int64)this);
  fb::PlayerManager::GetLocalPlayers(pPlayerManager, (__int64)&localPlayers);
  if ( v22 )
    sub_14173FF60(0i64);
  v3 = 0i64;
  LocalPlayersStart = localPlayers.mpBegin;
  dwLocalPlayerCount = (unsigned __int64)(localPlayers.mpEnd - localPlayers.mpBegin + 7) >> 3;
  if ( (unsigned __int64)localPlayers.mpBegin > localPlayers.mpEnd )
    dwLocalPlayerCount = 0i64;
  LocalPlayerCount = dwLocalPlayerCount;
  if ( dwLocalPlayerCount )
  {
    do
    {
      pLocalPlayer = *(_QWORD *)LocalPlayersStart;
      LocalPlayerId = *(signed int *)(*(_QWORD *)LocalPlayersStart + 0x78i64);
      dwLocalPlayerId = LocalPlayerId;
      LocalPlayerQueryManagerOffset = v1->qword28 + 0x180 * LocalPlayerId;
      sub_1417920A0(
        off_1443A9830,
        LocalPlayerQueryManagerOffset + 0x90,
        *(_DWORD *)(*(_QWORD *)LocalPlayersStart + 0x78i64),
        0,
        0.0);
      pLocalClientSoldierEntity = j_fb::ClientPlayer::GetSoldier(pLocalPlayer);
      if ( pLocalClientSoldierEntity )
      {
        LOBYTE(bDontUpdateMatrix) = 1;
        (*(void (__fastcall **)(_QWORD, char *, __int64))(**(_QWORD **)(pLocalClientSoldierEntity + 0x280) + 8i64))(
          *(_QWORD *)(pLocalClientSoldierEntity + 0x280),
          &mSoldierTransform,
          bDontUpdateMatrix);
        LocalTransformPos = (__m128i *)&mSoldierTransform;
      }
      else
      {
        v20 = 0i64;
        LocalTransformPos = (__m128i *)&v20;
      }
      _mm_store_si128((__m128i *)(LocalPlayerQueryManagerOffset + 0x1F0), *LocalTransformPos);
      *(float *)(LocalPlayerQueryManagerOffset + 0x200) = sub_141792B90(off_1443A9830, LocalPlayerId, 0);// <<
      v13 = v1->qword28;
      v14 = *(_DWORD *)(v13 + 4 * LocalPlayerId + 0x9930);
      while ( *(_DWORD *)(v13 + 4 * dwLocalPlayerId + 0x9934) < v14 )
      {
        OcclusionQuery = (SoldierOcclusionQueryManager::occlusionQuery *)(0x1930
                                                                        * (6 * dwLocalPlayerId
                                                                         + *(_DWORD *)(v13 + 4 * dwLocalPlayerId + 0x9934)
                                                                         % 6u)
                                                                        + v1->qword28
                                                                        + 528i64);
        handle = OcclusionQuery->m_batchQueryHandle;
        if ( handle == -1 )
        {
          ++*(_DWORD *)(v13 + 4 * dwLocalPlayerId + 0x9934);
          OcclusionQuery->queriesInitialized = 0;
          OcclusionQuery->byte1929 = 0;
          *(_QWORD *)OcclusionQuery->gap1909 = 0i64;
          *(_QWORD *)&OcclusionQuery->gap1909[8] = 0i64;
          *(_QWORD *)&OcclusionQuery->gap1909[0x10] = 0i64;
          *(_QWORD *)&OcclusionQuery->gap1909[0x18] = 0i64;
        }
        else
        {
          if ( !(unsigned __int8)fb::WorldOcclusionQueryRenderModule::isBatchQueryDataDone(
                                   v1->m_WorldOcclusionQueryRenderModule,
                                   handle) )
            break;
          cntr = 0i64;
          if ( OcclusionQuery->m_dwQueryCount )
          {
            do
            {
              *(float *)(*(_QWORD *)(v1->qword28
                                   + 8i64 * (unsigned int)(*(_DWORD *)&OcclusionQuery->gap1880[4 * cntr] >> 5))
                       + 4
                       * (dwLocalPlayerId
                        + 2i64
                        * (unsigned int)(*(_DWORD *)&OcclusionQuery->gap1880[4 * cntr]
                                       - 0x20 * (*(_DWORD *)&OcclusionQuery->gap1880[4 * cntr] >> 5)))) = OcclusionQuery->m_outVisibility[cntr];// << writes back result
              OcclusionQuery->gap1909[cntr] = 0;
              cntr = (unsigned int)(cntr + 1);
            }
            while ( (unsigned int)cntr < OcclusionQuery->m_dwQueryCount );
          }
          ++*(_DWORD *)(v13 + 4 * dwLocalPlayerId + 0x9934);
          OcclusionQuery->queriesInitialized = 0;
          OcclusionQuery->byte1929 = 0;
        }
      }
      LocalPlayersStart += 8i64;
      ++v3;
    }
    while ( v3 != LocalPlayerCount );
    LocalPlayersStart = localPlayers.mpBegin;
  }
  if ( LocalPlayersStart )
    sub_140391F60(
      &localPlayers.mAllocator,
      LocalPlayersStart,
      (localPlayers.mpCapacity - LocalPlayersStart) & 0xFFFFFFFFFFFFFFF8ui64);
  return 0i64;
}


//Function address: 1421FDB00
//function pattern: 48 8D 41 04 48 89 85 98 00 00 00 48 85 C9
_BOOL8 __fastcall fb::WorldOcclusionQueryRenderModule::isBatchQueryDataDone(WorldOcclusionQueryRenderModule *_this, unsigned int index)
{
  __int64 handle; // rsi
  WorldOcclusionQueryRenderModule *v3; // rbp
  CRITICAL_SECTION *pCriticalSection; // rbx
  BatchQuery *pBatch; // rcx
  int dwStatus; // eax
  bool IsDone; // di
  _DWORD *v8; // rcx
  int v10; // [rsp+58h] [rbp+10h]

  handle = index;
  v3 = _this;
  pCriticalSection = &_this->m_ciricalSection;
  j_RtlEnterCriticalSection(&_this->m_ciricalSection);
  pBatch = &v3->m_usedbatches_mpBegin[handle];
  dwStatus = pBatch->status;
  IsDone = dwStatus == 2;
  if ( dwStatus == 2 )
  {
    v10 = handle;
    pBatch->status = 3;
    v8 = (_DWORD *)v3->m_freeBatchesIndices_mpEnd;
    if ( (unsigned __int64)v8 >= v3->m_freeBatchesIndices_mCapacity )
    {
      eastl::vector<unsigned int,fb::eastl_arena_allocator>::DoInsertValue(
        (__int64)&v3->m_freeBatchesIndices_mpBegin,
        (__int64)&v10);
    }
    else
    {
      v3->m_freeBatchesIndices_mpEnd = v8 + 1;
      if ( v8 )
        *v8 = handle;
    }
  }
  if ( pCriticalSection )
    j_RtlLeaveCriticalSection(pCriticalSection);
  return IsDone;
}

//Function address: 142160520
//function pattern: 83 BE ?? ?? 00 00 00 0F 84 ?? ?? ?? ?? 41 83 BD ?? ?? 00 00 00 
char __fastcall fb::ClientSoldierEntity::updateOcclusionState(__int64 ThisClientSoldierEntity, int a2)
{
  __int64 pClientSoldierEntity; // rsi
  __int64 PlayerManager; // rdi
  bool v4; // al
  bool v5; // bl
  __int64 v6; // rax
  _BYTE *v7; // r9
  __int64 LocalPlayersStart; // r15
  __int64 LocalPlayersEnd; // rbx
  __int64 *v10; // r10
  __int64 pLocalPlayer; // r13
  __int64 LocalPlayerID; // r12
  char m_occluded; // cl
  float flScreenAreaCoverage; // xmm13_4
  __int64 *pClientSoldierEntity_plus_268; // rdi
  __int64 vtbl_1436679C8; // rbx
  unsigned int dwActiveView; // eax
  signed __int64 LocalPlayerSoldierOcclusionQueryManagerOffset; // rdi
  __int64 pSoldierOcclusionQueryManager; // rbx
  __m128 v20; // xmm10
  __m128i v21; // xmm10
  __m128 v22; // xmm3
  __m128 v23; // xmm0
  __m128 v24; // xmm9
  __m128 v25; // xmm12
  __m128 v26; // xmm0
  __m128 v27; // xmm1
  __m128 v28; // xmm2
  __m128 v29; // xmm7
  __m128 v30; // xmm9
  __m128 v31; // xmm4
  __m128 v32; // xmm12
  __m128 v33; // xmm8
  __m128 v34; // xmm11
  __m128 v35; // xmm2
  __m128 v36; // xmm1
  __m128 v37; // xmm0
  __m128 v38; // xmm6
  __m128 v39; // xmm12
  __m128 v40; // xmm11
  __m128i v41; // xmm1
  __m128i v42; // xmm4
  __m128 v43; // xmm1
  __m128i v44; // xmm1
  __m128i v45; // xmm2
  __m128 v46; // xmm3
  float flVisibility; // xmm0_4
  __int64 bDontUpdateMatrix; // r8
  __m128 _xmm2; // xmm2
  __m128i v50; // xmm2
  int LocalTeamId; // eax
  int SoldierTeamId; // ecx
  float v53; // xmm6_4
  int v54; // eax
  char v55; // dl
  __int64 v56; // r8
  __int64 v57; // rdx
  _BYTE *v58; // r8
  __int64 v59; // rcx
  __int64 v60; // rdx
  __int64 pLocalPlayersEnd; // [rsp+20h] [rbp-E0h]
  eastl::vector localPlayers; // [rsp+28h] [rbp-D8h]
  _OWORD mTransform[4]; // [rsp+50h] [rbp-B0h]
  float AxisAlignedBox_min[4]; // [rsp+90h] [rbp-70h]
  float AxisAlignedBox_max[4]; // [rsp+A0h] [rbp-60h]
  __int128 v67; // [rsp+B0h] [rbp-50h]
  __int64 v68; // [rsp+C0h] [rbp-40h]
  _OWORD mSoldierTransform[4]; // [rsp+D0h] [rbp-30h]
  bool bOccluded; // [rsp+1D0h] [rbp+D0h]
  char v71; // [rsp+1D8h] [rbp+D8h]

  v68 = -2i64;
  pClientSoldierEntity = ThisClientSoldierEntity;
  _mm_storeu_si128((__m128i *)&localPlayers, (__m128i)0i64);
  _mm_storeu_si128((__m128i *)&localPlayers.mpCapacity, (__m128i)0i64);
  PlayerManager = *(_QWORD *)(g_pClientGameContext + 0x68);
  LOBYTE(ThisClientSoldierEntity) = 1;
  v4 = sub_14173FF60(ThisClientSoldierEntity);
  v5 = v4;
  bOccluded = v4;
  LOBYTE(v6) = fb::PlayerManager::GetLocalPlayers(PlayerManager, (__int64)&localPlayers);
  if ( v5 )
    LOBYTE(v6) = sub_14173FF60(0i64);
  LocalPlayersStart = localPlayers.mpBegin;
  LocalPlayersEnd = localPlayers.mpEnd;
  pLocalPlayersEnd = localPlayers.mpEnd;
  if ( localPlayers.mpBegin != localPlayers.mpEnd )
  {
    v10 = (__int64 *)(pClientSoldierEntity + 0x8E8);
    while ( 1 )
    {
      pLocalPlayer = *(_QWORD *)LocalPlayersStart;
      LocalPlayerID = *(signed int *)(*(_QWORD *)LocalPlayersStart + 0x78i64);
      m_occluded = 0;
      bOccluded = 0;
      flScreenAreaCoverage = 0.0;
      if ( *(_QWORD *)(pClientSoldierEntity + 0x2D0) != pLocalPlayer
        && *(_DWORD *)(pClientSoldierEntity + 0x154)
        && *(_DWORD *)(pLocalPlayer + 0x1C3C) )
      {                                         // vtable: 01436679C8
                                                // => 1417B5790
                                                // ==> 1488CB2D0
        if ( (*(unsigned __int8 (__fastcall **)(__int64))(*(_QWORD *)(pClientSoldierEntity + 0x268) + 0x58i64))(pClientSoldierEntity + 0x268) )
        {
          m_occluded = 1;                       // if is in vehicle
          bOccluded = 1;
        }
        else
        {
          pClientSoldierEntity_plus_268 = *(__int64 **)(pClientSoldierEntity + 0x670);
          if ( !pClientSoldierEntity_plus_268
            || (vtbl_1436679C8 = *pClientSoldierEntity_plus_268,
                dwActiveView = (*(__int64 (__fastcall **)(_QWORD))(*pClientSoldierEntity_plus_268// 142137E90
                                                                 + 0x78))(*(_QWORD *)(pClientSoldierEntity + 0x670)),
                (*(unsigned __int8 (__fastcall **)(__int64 *, _QWORD))(vtbl_1436679C8 + 0x28))(
                  pClientSoldierEntity_plus_268,
                  dwActiveView)) )              // 14214B080
          {
            LocalPlayerSoldierOcclusionQueryManagerOffset = 0x180 * LocalPlayerID;
            pSoldierOcclusionQueryManager = fb::g_soldierOcclusionQueryManager;
            v20 = *(__m128 *)(0x20
                            * (*(unsigned __int8 *)(*(_QWORD *)(pClientSoldierEntity + 0x38) + 10i64)
                             + 2 * (*(unsigned __int8 *)(*(_QWORD *)(pClientSoldierEntity + 0x38) + 9i64) + 1i64))
                            + *(_QWORD *)(pClientSoldierEntity + 0x38));
            v21 = (__m128i)_mm_shuffle_ps(v20, _mm_shuffle_ps((__m128)xmmword_143118160, v20, 237), 100);// stuff written to by 1455533B7
            v22 = *(__m128 *)(0x180 * LocalPlayerID + fb::g_soldierOcclusionQueryManager + 0x1D0);
            v23 = *(__m128 *)(0x180 * LocalPlayerID + fb::g_soldierOcclusionQueryManager + 0x190);
            v24 = _mm_shuffle_ps(
                    *(__m128 *)(0x180 * LocalPlayerID + fb::g_soldierOcclusionQueryManager + 0x180),
                    v23,
                    68);
            v25 = _mm_shuffle_ps(
                    *(__m128 *)(0x180 * LocalPlayerID + fb::g_soldierOcclusionQueryManager + 0x180),
                    v23,
                    238);
            v26 = *(__m128 *)(0x180 * LocalPlayerID + fb::g_soldierOcclusionQueryManager + 432);
            v27 = _mm_shuffle_ps(
                    *(__m128 *)(0x180 * LocalPlayerID + fb::g_soldierOcclusionQueryManager + 0x1A0),
                    v26,
                    68);
            v28 = _mm_shuffle_ps(
                    *(__m128 *)(0x180 * LocalPlayerID + fb::g_soldierOcclusionQueryManager + 0x1A0),
                    v26,
                    238);
            v29 = _mm_shuffle_ps(v24, v27, 136);
            v30 = _mm_shuffle_ps(v24, v27, 221);
            v31 = _mm_shuffle_ps(v25, v28, 136);
            v32 = _mm_shuffle_ps(v25, v28, 221);
            v33 = _mm_shuffle_ps(
                    *(__m128 *)(0x180 * LocalPlayerID + fb::g_soldierOcclusionQueryManager + 0x1C0),
                    v22,
                    68);
            v34 = _mm_shuffle_ps(
                    *(__m128 *)(0x180 * LocalPlayerID + fb::g_soldierOcclusionQueryManager + 0x1C0),
                    v22,
                    238);
            v35 = (__m128)_mm_shuffle_epi32(v21, 0);
            v36 = (__m128)_mm_shuffle_epi32(v21, 85);
            v37 = (__m128)_mm_shuffle_epi32(v21, 170);
            v38 = (__m128)_mm_shuffle_epi32(v21, 255);
            v39 = _mm_add_ps(
                    _mm_add_ps(_mm_add_ps(v32, _mm_mul_ps(v31, v37)), _mm_mul_ps(v30, v36)),
                    _mm_mul_ps(v29, v35));
            v40 = _mm_add_ps(
                    _mm_add_ps(
                      _mm_add_ps(_mm_shuffle_ps(v34, v34, 221), _mm_mul_ps(_mm_shuffle_ps(v34, v34, 136), v37)),
                      _mm_mul_ps(_mm_shuffle_ps(v33, v33, 221), v36)),
                    _mm_mul_ps(_mm_shuffle_ps(v33, v33, 136), v35));
            v41 = (__m128i)_mm_or_ps(_mm_cmpltps(v38, v39), _mm_cmpltps(v38, v40));
            v42 = _mm_or_si128(_mm_shuffle_epi32(v41, 78), v41);
            v43 = _mm_sub_ps((__m128)0i64, v38);
            v44 = (__m128i)_mm_or_ps(_mm_cmpltps(v43, v39), _mm_cmpltps(v43, v40));
            v45 = _mm_or_si128(_mm_shuffle_epi32(v44, 78), v44);
            v46 = _mm_xor_ps(
                    _mm_and_ps(
                      _mm_xor_ps((__m128)_mm_load_si128((const __m128i *)&xmmword_1431180D0), (__m128)0i64),
                      (__m128)_mm_or_si128(v45, _mm_shuffle_epi32(v45, 177))),
                    (__m128)xmmword_1431180D0);
            if ( _mm_cvtsi128_si32((__m128i)_mm_xor_ps(
                                              _mm_and_ps(
                                                _mm_xor_ps(
                                                  (__m128)_mm_load_si128((const __m128i *)&xmmword_1431180E0),
                                                  v46),
                                                (__m128)_mm_or_si128(v42, _mm_shuffle_epi32(v42, 177))),
                                              v46)) == 2 )
            {
              m_occluded = 1;
              bOccluded = 1;
            }
            else
            {
              flVisibility = j_fb::SoldierOcclusionQueryManager::GetVisibility(
                               fb::g_soldierOcclusionQueryManager,
                               *(unsigned int *)(pClientSoldierEntity + 0x8E0),
                               (unsigned int)LocalPlayerID);
              LOBYTE(bDontUpdateMatrix) = 1;
              (*(void (__fastcall **)(_QWORD, _OWORD *, __int64))(**(_QWORD **)(pClientSoldierEntity + 0x280)
                                                                + 8i64))(// vtable: 00000001431666C0
                                                // fnc: 1405F3000
                                                // ==> 1405F3050
                *(_QWORD *)(pClientSoldierEntity + 0x280),
                mSoldierTransform,
                bDontUpdateMatrix);
              _xmm2 = _mm_sub_ps(
                        *(__m128 *)(LocalPlayerSoldierOcclusionQueryManagerOffset + pSoldierOcclusionQueryManager + 0x1F0),
                        (__m128)mSoldierTransform[0]);// 1F0 written from 1421FDC1F
              v50 = (__m128i)_mm_mul_ps(_xmm2, _xmm2);
              flScreenAreaCoverage = (float)(fsqrt(
                                               COERCE_FLOAT(_mm_shuffle_epi32(v50, 170))
                                             + (float)(COERCE_FLOAT(_mm_shuffle_epi32(v50, 85))
                                                     + COERCE_FLOAT(_mm_shuffle_epi32(v50, 0))))
                                           * *(float *)(LocalPlayerSoldierOcclusionQueryManagerOffset
                                                      + pSoldierOcclusionQueryManager
                                                      + 0x200))// << 0x200 written from 1421FDC39
                                   * fsqrt(flVisibility * 921600.0);
              LocalTeamId = *(_DWORD *)(pLocalPlayer + 0x1C3C);
              SoldierTeamId = *(_DWORD *)(pClientSoldierEntity + 0x154);
              if ( LocalTeamId == SoldierTeamId )
                bOccluded = flScreenAreaCoverage == 0.0;
              else
                bOccluded = flScreenAreaCoverage <= 200.0;
              mTransform[0] = *(_OWORD *)(pClientSoldierEntity + 0xAD0);
              mTransform[1] = *(_OWORD *)(pClientSoldierEntity + 0xAE0);
              mTransform[2] = *(_OWORD *)(pClientSoldierEntity + 0xAF0);
              mTransform[3] = *(_OWORD *)(pClientSoldierEntity + 0xB00);
              *(_OWORD *)AxisAlignedBox_min = *(_OWORD *)(pClientSoldierEntity + 0xB10);
              *(_OWORD *)AxisAlignedBox_max = *(_OWORD *)(pClientSoldierEntity + 0xB20);
              v67 = *(_OWORD *)(pClientSoldierEntity + 0xB30);
              if ( LocalTeamId != SoldierTeamId )
              {
                v53 = 0.88;
                v54 = (unsigned __int64)(*(__int64 (__fastcall **)(__int64))(*(_QWORD *)(pClientSoldierEntity + 0x268)
                                                                           + 0x68i64))(pClientSoldierEntity + 0x268)
                    - 1;
                if ( v54 )
                {
                  if ( v54 == 1 )
                    v53 = 0.60000002;
                }
                else
                {
                  v53 = 0.92000002;
                }
                AxisAlignedBox_min[0] = AxisAlignedBox_min[0] * 0.60000002;
                AxisAlignedBox_min[1] = AxisAlignedBox_min[1] * v53;
                AxisAlignedBox_min[2] = AxisAlignedBox_min[2] * 0.60000002;
                AxisAlignedBox_max[0] = AxisAlignedBox_max[0] * 0.60000002;
                AxisAlignedBox_max[1] = AxisAlignedBox_max[1] * v53;
                AxisAlignedBox_max[2] = AxisAlignedBox_max[2] * 0.60000002;
              }
              fb::SoldierOcclusionQueryManager::addRenderObject(
                fb::g_soldierOcclusionQueryManager,
                *(_DWORD *)(pClientSoldierEntity + 0x8E0),
                LocalPlayerID,
                mTransform);
              m_occluded = bOccluded;
            }
          }
          else
          {
            m_occluded = 1;
            bOccluded = 1;
          }
          LocalPlayersEnd = pLocalPlayersEnd;
        }
        v10 = (__int64 *)(pClientSoldierEntity + 0x8E8);
      }
      *(_BYTE *)(pClientSoldierEntity + LocalPlayerID + 0x8DB) = m_occluded;// << writes the bool
      *(float *)(pClientSoldierEntity + 4 * LocalPlayerID + 0x8DC) = flScreenAreaCoverage;
      v55 = 0;
      v71 = 0;
      v6 = 0i64;
      while ( !*(_BYTE *)(pClientSoldierEntity + v6 + 0x8DB) )
      {
        if ( ++v6 >= 1 )
          goto LABEL_32;
      }
      v55 = 1;
      v71 = 1;
LABEL_32:
      v56 = *v10;
      if ( *v10 )
      {
        v7 = *(_BYTE **)(v56 + 8);
        LODWORD(v6) = *(_DWORD *)(v56 + 0x18) & 0x30;
        if ( (*(_BYTE *)(v56 + 0x18) & 0x30) != 0x30 || *v7 != v55 )
        {
          LOBYTE(v56) = 1;
          LOBYTE(v6) = sub_14039ACD0((__int64)v10, (__int64)&v71, v56, (__int64)v7);
          m_occluded = bOccluded;
        }
      }
      if ( (_DWORD)LocalPlayerID )
      {
        v60 = *(_QWORD *)(pClientSoldierEntity + 0x8F8);
        if ( !v60 )
          goto LABEL_46;
        v58 = *(_BYTE **)(v60 + 8);
        LODWORD(v6) = *(_DWORD *)(v60 + 0x18) & 0x30;
        if ( (*(_BYTE *)(v60 + 0x18) & 0x30) == 48 && *v58 == m_occluded )
          goto LABEL_46;
        v59 = pClientSoldierEntity + 0x8F8;
      }
      else
      {
        v57 = *(_QWORD *)(pClientSoldierEntity + 0x8F0);
        if ( !v57 )
          goto LABEL_46;
        v58 = *(_BYTE **)(v57 + 8);
        LODWORD(v6) = *(_DWORD *)(v57 + 24) & 0x30;
        if ( (*(_BYTE *)(v57 + 24) & 0x30) == 48 && *v58 == m_occluded )
          goto LABEL_46;
        v59 = pClientSoldierEntity + 2288;
      }
      LOBYTE(v58) = 1;
      LOBYTE(v6) = sub_14039ACD0(v59, (__int64)&bOccluded, (__int64)v58, (__int64)v7);
LABEL_46:
      LocalPlayersStart += 8i64;
      v10 = (__int64 *)(pClientSoldierEntity + 0x8E8);
      if ( LocalPlayersStart == LocalPlayersEnd )
      {
        LocalPlayersStart = localPlayers.mpBegin;
        break;
      }
    }
  }
  if ( LocalPlayersStart )
    LOBYTE(v6) = sub_140391F60(
                   &localPlayers.mAllocator,
                   LocalPlayersStart,
                   (localPlayers.mpCapacity - LocalPlayersStart) & 0xFFFFFFFFFFFFFFF8ui64);
  return v6;
}

//Function address: 149CA6720
//function pattern: 41 89 D1 41 C1 E9 05 44 89 C8 C1 E0 05 29 C2 49 63 C0 4A 8B 0C C9 4C 8D 04 50 F3 42 0F 10 04 81
float __fastcall fb::SoldierOcclusionQueryManager::GetVisibility(__int64 a1, unsigned int a2, int a3)
{
  return *(float *)(*(_QWORD *)(a1 + 8i64 * (a2 >> 5)) + 4 * (a3 + 2i64 * (a2 - 32 * (a2 >> 5))));
}

//Function address: 141DEF5E0
//function pattern: 44 3B 65 04 74 09 45 85 E4 0F 85
void __fastcall fb::WorldOcclusionQueryRenderModule::processBatchQueries(WorldOcclusionQueryRenderModule *pWorldOcclusionQueryRenderModule, __int64 Arg2, __int64 rootView, bool a4)
{
  __int64 pRootView; // rdi
  __int64 pArg2_1; // rsi
  WorldOcclusionQueryRenderModule *WorldOcclusionQueryRenderModule; // r14
  CRITICAL_SECTION *pCriticalSection1; // rbx
  float flScreenArea; // xmm6_4
  unsigned int cntr; // er15
  signed __int64 dwUsedbatchesSize; // rcx
  __int64 BatchQueryOffset; // r13
  BatchQuery *Batch; // rbp
  DxRenderQuery *pRenderQuery; // rax
  int QueryStatus; // er12
  unsigned int *v14; // rcx
  __int64 m_callback__mpEnd; // rsi
  __int64 i; // rdi
  signed __int64 v17; // rcx
  CRITICAL_SECTION *pCriticalSection2; // [rsp+30h] [rbp-58h]
  unsigned int v19; // [rsp+90h] [rbp+8h]
  __int64 pArg2_2; // [rsp+98h] [rbp+10h]
  __int64 v21; // [rsp+A0h] [rbp+18h]

  v21 = rootView;
  pArg2_2 = Arg2;
  pRootView = rootView;
  pArg2_1 = Arg2;
  WorldOcclusionQueryRenderModule = pWorldOcclusionQueryRenderModule;
  pCriticalSection1 = &pWorldOcclusionQueryRenderModule->m_ciricalSection;
  pCriticalSection2 = &pWorldOcclusionQueryRenderModule->m_ciricalSection;
  j_RtlEnterCriticalSection(&pWorldOcclusionQueryRenderModule->m_ciricalSection);
  flScreenArea = (float)*(signed int *)(pRootView + 0x24) * (float)*(signed int *)(pRootView + 0x20);
  cntr = 0;
  dwUsedbatchesSize = WorldOcclusionQueryRenderModule->m_usedbatches_mpEnd
                    - (unsigned __int64)WorldOcclusionQueryRenderModule->m_usedbatches_mpBegin;
  if ( ((unsigned __int64)((unsigned __int128)(dwUsedbatchesSize * (signed __int128)0xA87917088E262B7i64) >> 64) >> 63)
     + (unsigned int)((signed __int64)((unsigned __int128)(dwUsedbatchesSize * (signed __int128)0xA87917088E262B7i64) >> 64) >> 8) )
  {
    do
    {
      BatchQueryOffset = cntr;
      Batch = &WorldOcclusionQueryRenderModule->m_usedbatches_mpBegin[BatchQueryOffset];// accessed by
                                                // 141DEF645
                                                // 141DEF68A
                                                // 141DEF7D0
                                                // 141DE9D74
                                                // 141DE9766
                                                // 141DE97EE
      if ( Batch->dwordC == *(_DWORD *)(pRootView + 0x21F4) )
      {
        if ( !Batch->queriesInitialized )
        {
          pRenderQuery = (DxRenderQuery *)((__int64 (__fastcall *)(DxRenderer *, __int64, signed __int64))g_pDxRenderer->vtable->createQuery)(// 148F50960
                                            g_pDxRenderer,// vtable => 1435A5150
                                            WorldOcclusionQueryRenderModule->m_Allocator,
                                            2i64, 
											32, 
											"worldRenderOcclusion");
          Batch->m_dxQuerys = pRenderQuery;
          (*(void (__fastcall **)(DxRenderQuery *))pRenderQuery->vtable)(pRenderQuery);
          Batch->queriesInitialized = 1;        // queriesInitialized
        }
        do
        {
          QueryStatus = Batch->status;
          if ( QueryStatus )
          {
            if ( QueryStatus == 1 )
            {
              fb::WorldOcclusionQueryRenderModule::retrieveBatchQueryData(
                (__int64)WorldOcclusionQueryRenderModule,
                (__int64)Batch,
                flScreenArea);
            }
            else if ( QueryStatus == 2 && ++Batch->doneCounter > 100u )
            {
              v19 = cntr;
              WorldOcclusionQueryRenderModule->m_usedbatches_mpBegin[BatchQueryOffset].status = 3;
              v14 = (unsigned int *)WorldOcclusionQueryRenderModule->m_freeBatchesIndices_mpEnd;
              if ( (unsigned __int64)v14 >= WorldOcclusionQueryRenderModule->m_freeBatchesIndices_mCapacity )
              {
                eastl::vector<unsigned int,fb::eastl_arena_allocator>::DoInsertValue(
                  (__int64)&WorldOcclusionQueryRenderModule->m_freeBatchesIndices_mpBegin,
                  (__int64)&v19);               // WorldOcclusionQueryRenderModule->m_freeBatchesIndices
              }
              else
              {
                WorldOcclusionQueryRenderModule->m_freeBatchesIndices_mpEnd = v14 + 1;
                if ( v14 )
                  *v14 = cntr;
              }
              m_callback__mpEnd = WorldOcclusionQueryRenderModule->m_callback__mpEnd;
              for ( i = WorldOcclusionQueryRenderModule->m_callback__mpBegin; i != m_callback__mpEnd; i += 0x10i64 )
                (*(void (__fastcall **)(_QWORD, _QWORD))(i + 8))(*(_QWORD *)i, cntr);
              pDxRenderer = pArg2_2;
              pRootView = v21;
            }
          }
          else
          {
            fb::WorldOcclusionQueryRenderModule::drawBatchQuery(
              WorldOcclusionQueryRenderModule,
              pArg2_1,
              pRootView,
              Batch);
          }
        }
        while ( QueryStatus != Batch->status && QueryStatus );
      }
      ++cntr;
      v17 = WorldOcclusionQueryRenderModule->m_usedbatches_mpEnd
          - (unsigned __int64)WorldOcclusionQueryRenderModule->m_usedbatches_mpBegin;
    }
    while ( cntr < ((unsigned __int64)((unsigned __int128)(v17 * (signed __int128)0xA87917088E262B7i64) >> 64) >> 63)
                 + (unsigned int)((signed __int64)((unsigned __int128)(v17 * (signed __int128)0xA87917088E262B7i64) >> 64) >> 8) );
    pCriticalSection1 = pCriticalSection2;
  }
  if ( pCriticalSection1 )
    j_RtlLeaveCriticalSection();
}

//Function address: 141DE9720
//function pattern: 48 C1 ?? 3F 48 ?? ?? FF ?? C6 ?? 08 00 EB
__int64 __fastcall fb::WorldOcclusionQueryRenderModule::insertBatchQuery(WorldOcclusionQueryRenderModule *a1, int _dwordC, unsigned int QueryCount, ObjectRenderInfo *ObjectRenderInfo, float *outObjectScreenAreaCoverage)
{
  ObjectRenderInfo *pObjectRenderInfo; // r15
  __int64 dwQueryCount; // r14
  int dwordC; // er12
  WorldOcclusionQueryRenderModule *v8; // rdi
  CRITICAL_SECTION *v9; // rbx
  BatchQuery **v10; // rbp
  signed __int64 v11; // r10
  __int64 v12; // rsi
  __int64 m_freeBatchesIndices.mpEnd; // rcx
  BatchQuery *newBatchQuery; // rdi
  unsigned __int64 v15; // rdx

  pObjectRenderInfo = ObjectRenderInfo;
  dwQueryCount = QueryCount;
  dwordC = _dwordC;
  v8 = a1;
  v9 = &a1->m_ciricalSection;
  j_RtlEnterCriticalSection(&a1->m_ciricalSection);
  v10 = &v8->m_usedbatches_mpBegin;
  v11 = v8->m_usedbatches_mpEnd - (unsigned __int64)v8->m_usedbatches_mpBegin;
  if ( ((unsigned __int64)((unsigned __int128)(v11 * (signed __int128)0xA87917088E262B7i64) >> 64) >> 63)
     + (unsigned int)((signed __int64)((unsigned __int128)(v11 * (signed __int128)0xA87917088E262B7i64) >> 64) >> 8) <= 11 )
  {
    m_freeBatchesIndices.mpEnd = v8->m_freeBatchesIndices_mpEnd;
    if ( v8->m_freeBatchesIndices_mpBegin == m_freeBatchesIndices.mpEnd )// WorldOcclusionQueryRenderModule->m_freeBatchesIndices.mpBegin == WorldOcclusionQueryRenderModule->m_freeBatchesIndices.mpEnd
    {
      eastl::vector<fb::WorldOcclusionQueryRenderModule::BatchQuery,fb::eastl_arena_allocator>::push_back((__int64)&v8->m_usedbatches_mpBegin);
      newBatchQuery = (BatchQuery *)(v8->m_usedbatches_mpEnd - 0x1850i64);
      v15 = (signed __int64)((unsigned __int128)(((char *)v10[1] - (char *)*v10) * (signed __int128)0xA87917088E262B7i64) >> 64) >> 8;
      LODWORD(v12) = v15 + (v15 >> 63) - 1;
      newBatchQuery->queriesInitialized = 0;
    }
    else
    {
      v12 = *(unsigned int *)(m_freeBatchesIndices.mpEnd - 4);
      v8->m_freeBatchesIndices_mpEnd -= 4i64;
      newBatchQuery = &(*v10)[v12];
    }
    j_memcpy_1(newBatchQuery->renderInfos__m_firstElement, pObjectRenderInfo, 0xC0 * dwQueryCount);
    newBatchQuery->count = dwQueryCount;
    newBatchQuery->status = 0;
    newBatchQuery->doneCounter = 0;
    newBatchQuery->outObjectScreenAreaCoverage = outObjectScreenAreaCoverage;
    newBatchQuery->dwordC = dwordC;
  }
  else
  {
    LODWORD(v12) = -1;
  }
  if ( v9 )
    j_RtlLeaveCriticalSection(v9);
  return (unsigned int)v12;
}

//Function address: 1421FD890
//function pattern: 4C 8D 2C 8D 38 99 00 00 48 8B 4D 28 
// called from 1416FD467, sub_1416FCFE0
char __fastcall fb::SoldierOcclusionQueryManager::updateOccludedSoldiers(struct_SoldierOcclusionQueryManager *pSoldierOcclusionQueryManager)
{
  struct_SoldierOcclusionQueryManager *SoldierOcclusionQueryManager; // rbp
  __int64 pClientPlayerManager; // rdi
  bool v3; // bl
  __int64 v4; // rax
  __int64 cntr; // rdx
  __int64 PlayerList_firstElement; // r12
  unsigned __int64 PlayerCount; // r8
  __int64 playerNum; // r14
  signed __int64 v9; // r13
  __int64 v10; // rcx
  unsigned int v11; // ebx
  unsigned int v12; // er15
  unsigned int v13; // esi
  __int64 v14; // r8
  SoldierOcclusionQueryManager::occlusionQuery *OcclusionQuery; // rdi
  unsigned int dwQueryCount; // er8
  __int64 _cntr; // [rsp+30h] [rbp-78h]
  unsigned __int64 dwPlayerCount; // [rsp+38h] [rbp-70h]
  _QWORD playerList[4]; // [rsp+48h] [rbp-60h]
  __int64 pPlayerList_firstElement; // [rsp+C8h] [rbp+20h]

  SoldierOcclusionQueryManager = pSoldierOcclusionQueryManager;
  _mm_storeu_si128((__m128i *)playerList, (__m128i)0i64);
  _mm_storeu_si128((__m128i *)&playerList[2], (__m128i)0i64);
  pClientPlayerManager = pSoldierOcclusionQueryManager->m_pPlayerManager;
  LOBYTE(pSoldierOcclusionQueryManager) = 1;
  v3 = sub_14173FF60((__int64)pSoldierOcclusionQueryManager);
  LOBYTE(v4) = fb::PlayerManager::GetLocalPlayers(pClientPlayerManager, (__int64)playerList);
  if ( v3 )
    LOBYTE(v4) = sub_14173FF60(0i64);
  cntr = 0i64;
  _cntr = 0i64;
  PlayerList_firstElement = playerList[0];
  pPlayerList_firstElement = playerList[0];
  PlayerCount = (unsigned __int64)(playerList[1] - playerList[0] + 7i64) >> 3;
  if ( playerList[0] > playerList[1] )
    PlayerCount = 0i64;
  dwPlayerCount = PlayerCount;
  if ( PlayerCount )
  {
    do
    {
      playerNum = *(signed int *)(*(_QWORD *)PlayerList_firstElement + 0x78i64);
      v9 = 4 * playerNum + 0x9938;
      v10 = SoldierOcclusionQueryManager->qword28;
      v11 = *(_DWORD *)(v10 + 4 * playerNum + 0x9930);
      v12 = v11 + ((unsigned int)(*(_DWORD *)(v10 + v9) + 31) >> 5);
      v13 = *(_DWORD *)(v10 + 4 * playerNum + 0x9930) - *(_DWORD *)(v10 + 4 * playerNum + 0x9934);
      if ( v11 < v12 )
      {
        do
        {
          if ( v13 >= 6 )
            break;
          v14 = SoldierOcclusionQueryManager->qword28;
          OcclusionQuery = (SoldierOcclusionQueryManager::occlusionQuery *)(0x1930 * (v11++ % 6 + 6 * playerNum)
                                                                          + v14
                                                                          + 0x210);
          if ( !OcclusionQuery->queriesInitialized && OcclusionQuery->byte1929 )
          {
            dwQueryCount = *(_DWORD *)(v14 + v9);
            if ( dwQueryCount > 32 )
              dwQueryCount = 32;
            OcclusionQuery->m_dwQueryCount = dwQueryCount;
            OcclusionQuery->m_batchQueryHandle = fb::WorldOcclusionQueryRenderModule::insertBatchQuery(
                                                   SoldierOcclusionQueryManager->m_WorldOcclusionQueryRenderModule,
                                                   playerNum,
                                                   dwQueryCount,
                                                   OcclusionQuery->m_objects,
                                                   OcclusionQuery->m_outVisibility);
            OcclusionQuery->queriesInitialized = 1;
            *(_DWORD *)(SoldierOcclusionQueryManager->qword28 + v9) -= OcclusionQuery->m_dwQueryCount;
            ++*(_DWORD *)(SoldierOcclusionQueryManager->qword28 + 4 * playerNum + 0x9930);
            ++v13;
          }
        }
        while ( v11 < v12 );
        PlayerList_firstElement = pPlayerList_firstElement;
        cntr = _cntr;
        PlayerCount = dwPlayerCount;
      }
      v4 = SoldierOcclusionQueryManager->qword28;
      *(_DWORD *)(v4 + v9) = 0;
      PlayerList_firstElement += 8i64;
      pPlayerList_firstElement = PlayerList_firstElement;
      _cntr = ++cntr;
    }
    while ( cntr != PlayerCount );
    PlayerList_firstElement = playerList[0];
  }
  if ( PlayerList_firstElement )
    LOBYTE(v4) = sub_140391F60(
                   &playerList[3],
                   PlayerList_firstElement,
                   (playerList[2] - PlayerList_firstElement) & 0xFFFFFFFFFFFFFFF8ui64);
  return v4;
}

//Function address: 141DDAFC0
//look for the string in this function
__int64 __fastcall fb::WorldOcclusionQueryRenderModule::drawBatchQuery(WorldOcclusionQueryRenderModule *WorldOcclusionQueryRenderModule, __int64 unknown, __int64 a3, BatchQuery *Batch)
{
  BatchQuery *pBatch; // r14
  __int64 v5; // r13
  __int64 pUnknown; // rdi
  WorldOcclusionQueryRenderModule *pWorldOcclusionQueryRenderModule; // r12
  __int64 result; // rax
  unsigned int cntr; // ebx
  __int64 v10; // r11
  unsigned int v11; // er15
  __m128i v12; // xmm7
  __m128i v13; // xmm8
  ObjectRenderInfo *v14; // rcx
  __m128i v15; // xmm0
  __m128 v16; // xmm6
  __m128 v17; // xmm5
  __m128 v18; // xmm4
  __m128 v19; // xmm3
  __m128 v20; // xmm2
  __m128i v21; // xmm0
  __m128 v22; // xmm2
  __m128i v23; // xmm0
  __m128 v24; // xmm2
  __m128i v25; // xmm0
  __m128 v26; // xmm2
  __m128i v27; // xmm0
  __m128 v28; // xmm2
  __m128i v29; // xmm0
  __m128 v30; // xmm2
  __m128i v31; // xmm0
  __m128 v32; // xmm2
  __m128i v33; // xmm0
  __m128 v34; // xmm2
  __m128i *v35; // r10
  __int16 *v36; // r8
  signed __int64 v37; // rsi
  unsigned int v38; // ecx
  __int64 v39; // rdx
  __m128i *v40; // r9
  __int128 v41; // [rsp+20h] [rbp-A0h]
  ObjectRenderInfo *pObjectRenderInfo; // [rsp+30h] [rbp-90h]
  __int64 v43; // [rsp+38h] [rbp-88h]
  __int64 v44; // [rsp+40h] [rbp-80h]
  __int64 v45; // [rsp+48h] [rbp-78h]
  __int64 v46; // [rsp+50h] [rbp-70h]
  int v47; // [rsp+58h] [rbp-68h]
  __int64 v48; // [rsp+60h] [rbp-60h]
  int v49; // [rsp+68h] [rbp-58h]
  const char *v50; // [rsp+70h] [rbp-50h]
  void *v51; // [rsp+78h] [rbp-48h]
  int v52; // [rsp+80h] [rbp-40h]
  __int64 v53; // [rsp+88h] [rbp-38h]
  __int64 v54; // [rsp+90h] [rbp-30h]
  __int128 v55; // [rsp+D0h] [rbp+10h]
  int v56; // [rsp+E0h] [rbp+20h]
  int v57; // [rsp+E4h] [rbp+24h]
  int v58; // [rsp+E8h] [rbp+28h]
  int v59; // [rsp+F0h] [rbp+30h]
  int v60; // [rsp+F4h] [rbp+34h]
  int v61; // [rsp+F8h] [rbp+38h]
  int v62; // [rsp+100h] [rbp+40h]
  int v63; // [rsp+104h] [rbp+44h]
  int v64; // [rsp+108h] [rbp+48h]
  int v65; // [rsp+110h] [rbp+50h]
  int v66; // [rsp+114h] [rbp+54h]
  int v67; // [rsp+118h] [rbp+58h]
  int v68; // [rsp+120h] [rbp+60h]
  int v69; // [rsp+124h] [rbp+64h]
  int v70; // [rsp+128h] [rbp+68h]
  int v71; // [rsp+130h] [rbp+70h]
  int v72; // [rsp+134h] [rbp+74h]
  int v73; // [rsp+138h] [rbp+78h]
  int v74; // [rsp+140h] [rbp+80h]
  int v75; // [rsp+144h] [rbp+84h]
  int v76; // [rsp+148h] [rbp+88h]

  v48 = -2i64;
  pBatch = Batch;
  v5 = a3;
  *(_QWORD *)&v41 = a3;
  pUnknown = unknown;
  pWorldOcclusionQueryRenderModule = WorldOcclusionQueryRenderModule;
  pObjectRenderInfo = Batch->renderInfos__m_firstElement;
  result = (unsigned int)Batch->count;
  if ( (_DWORD)result )
  {
    cntr = 0;
    v50 = 0i64;
    v44 = 51i64;
    v47 = 0;
    LODWORD(v51) = 0x240 * result;
    HIDWORD(v48) = 2;
    v49 = 2;
    HIDWORD(v51) = 1;
    v43 = 0i64;
    LODWORD(v44) = 0;
    v45 = 0i64;
    v46 = 0i64;
    result = ((__int64 (__fastcall *)(DxRenderer *, __int64 *, __int64 *))g_pDxRenderer->vtable->sub_141BDDE70_2)(// => 141BDDE70
               g_pDxRenderer,
               &v48,
               &v43);
    if ( (_BYTE)result )
    {
      v10 = v45;
      v11 = 0;
      if ( pBatch->count > 0u )
      {
        v12 = (__m128i)v41;
        v13 = (__m128i)v41;
        do
        {
          v14 = &pObjectRenderInfo[v11];
          v15 = _mm_load_si128((const __m128i *)v14->vertices);
          v16 = *(__m128 *)v14->worldTransform;
          v17 = *(__m128 *)&v14->worldTransform[4];
          v18 = *(__m128 *)&v14->worldTransform[8];
          v19 = *(__m128 *)&v14->worldTransform[12];
          v20 = _mm_add_ps(
                  _mm_add_ps(
                    _mm_add_ps(_mm_mul_ps((__m128)_mm_shuffle_epi32(v15, 0), *(__m128 *)v14->worldTransform), v19),
                    _mm_mul_ps((__m128)_mm_shuffle_epi32(v15, 85), v17)),
                  _mm_mul_ps((__m128)_mm_shuffle_epi32(v15, 170), v18));
          LODWORD(v55) = v20.m128_i32[0];
          DWORD1(v55) = (unsigned __int128)_mm_shuffle_ps(v20, v20, 85);
          DWORD2(v55) = (unsigned __int128)_mm_shuffle_ps(v20, v20, 170);
          v21 = _mm_load_si128((const __m128i *)&v14->vertices[1]);
          v22 = _mm_add_ps(
                  _mm_add_ps(
                    _mm_add_ps(_mm_mul_ps((__m128)_mm_shuffle_epi32(v21, 0), v16), v19),
                    _mm_mul_ps((__m128)_mm_shuffle_epi32(v21, 85), v17)),
                  _mm_mul_ps((__m128)_mm_shuffle_epi32(v21, 170), v18));
          v56 = v22.m128_i32[0];
          v57 = (unsigned __int128)_mm_shuffle_ps(v22, v22, 85);
          v58 = (unsigned __int128)_mm_shuffle_ps(v22, v22, 170);
          v23 = _mm_load_si128((const __m128i *)&v14->vertices[5]);
          v24 = _mm_add_ps(
                  _mm_add_ps(
                    _mm_add_ps(_mm_mul_ps((__m128)_mm_shuffle_epi32(v23, 0), v16), v19),
                    _mm_mul_ps((__m128)_mm_shuffle_epi32(v23, 85), v17)),
                  _mm_mul_ps((__m128)_mm_shuffle_epi32(v23, 170), v18));
          v59 = v24.m128_i32[0];
          v60 = (unsigned __int128)_mm_shuffle_ps(v24, v24, 85);
          v61 = (unsigned __int128)_mm_shuffle_ps(v24, v24, 170);
          v25 = _mm_load_si128((const __m128i *)&v14->vertices[4]);
          v26 = _mm_add_ps(
                  _mm_add_ps(
                    _mm_add_ps(_mm_mul_ps((__m128)_mm_shuffle_epi32(v25, 0), v16), v19),
                    _mm_mul_ps((__m128)_mm_shuffle_epi32(v25, 85), v17)),
                  _mm_mul_ps((__m128)_mm_shuffle_epi32(v25, 170), v18));
          v62 = v26.m128_i32[0];
          v63 = (unsigned __int128)_mm_shuffle_ps(v26, v26, 85);
          v64 = (unsigned __int128)_mm_shuffle_ps(v26, v26, 170);
          v27 = _mm_load_si128((const __m128i *)&v14->vertices[2]);
          v28 = _mm_add_ps(
                  _mm_add_ps(
                    _mm_add_ps(_mm_mul_ps((__m128)_mm_shuffle_epi32(v27, 0), v16), v19),
                    _mm_mul_ps((__m128)_mm_shuffle_epi32(v27, 85), v17)),
                  _mm_mul_ps((__m128)_mm_shuffle_epi32(v27, 170), v18));
          v65 = v28.m128_i32[0];
          v66 = (unsigned __int128)_mm_shuffle_ps(v28, v28, 85);
          v67 = (unsigned __int128)_mm_shuffle_ps(v28, v28, 170);
          v29 = _mm_load_si128((const __m128i *)&v14->vertices[3]);
          v30 = _mm_add_ps(
                  _mm_add_ps(
                    _mm_add_ps(_mm_mul_ps((__m128)_mm_shuffle_epi32(v29, 0), v16), v19),
                    _mm_mul_ps((__m128)_mm_shuffle_epi32(v29, 85), v17)),
                  _mm_mul_ps((__m128)_mm_shuffle_epi32(v29, 170), v18));
          v68 = v30.m128_i32[0];
          v69 = (unsigned __int128)_mm_shuffle_ps(v30, v30, 85);
          v70 = (unsigned __int128)_mm_shuffle_ps(v30, v30, 170);
          v31 = _mm_load_si128((const __m128i *)&v14->vertices[7]);
          v32 = _mm_add_ps(
                  _mm_add_ps(
                    _mm_add_ps(_mm_mul_ps((__m128)_mm_shuffle_epi32(v31, 0), v16), v19),
                    _mm_mul_ps((__m128)_mm_shuffle_epi32(v31, 85), v17)),
                  _mm_mul_ps((__m128)_mm_shuffle_epi32(v31, 170), v18));
          v71 = v32.m128_i32[0];
          v72 = (unsigned __int128)_mm_shuffle_ps(v32, v32, 85);
          v73 = (unsigned __int128)_mm_shuffle_ps(v32, v32, 170);
          v33 = _mm_load_si128((const __m128i *)&v14->vertices[6]);
          v34 = _mm_add_ps(
                  _mm_add_ps(
                    _mm_add_ps(_mm_mul_ps((__m128)_mm_shuffle_epi32(v33, 0), v16), v19),
                    _mm_mul_ps((__m128)_mm_shuffle_epi32(v33, 85), v17)),
                  _mm_mul_ps((__m128)_mm_shuffle_epi32(v33, 170), v18));
          v74 = v34.m128_i32[0];
          v75 = (unsigned __int128)_mm_shuffle_ps(v34, v34, 85);
          v76 = (unsigned __int128)_mm_shuffle_ps(v34, v34, 170);
          v35 = (__m128i *)(v10 + 0x50);
          v36 = word_143FEAE58;
          v37 = 6i64;
          do
          {
            v38 = 0;
            v39 = 0i64;
            v40 = (__m128i *)v10;
            do
            {
              _mm_store_si128(v40, (__m128i)*(&v55 + (unsigned __int16)v36[v39]));
              if ( v38 )
              {
                if ( v38 == 2 )
                  v13 = (__m128i)*(&v55 + (unsigned __int16)v36[v39]);
              }
              else
              {
                v12 = (__m128i)*(&v55 + (unsigned __int16)v36[v39]);
              }
              ++v38;
              ++v40;
              ++v39;
            }
            while ( v38 < 4 );
            _mm_store_si128(v35 - 1, v12);
            _mm_store_si128(v35, v13);
            v10 += 96i64;
            v35 += 6;
            v36 += 4;
            --v37;
          }
          while ( v37 );
          ++v11;
        }
        while ( v11 < pBatch->count );
        v5 = v41;
      }
      ((void (__fastcall *)(DxRenderer *, __int64 *))g_pDxRenderer->vtable->sub_141BD6870)(g_pDxRenderer, &v43);
      if ( dword_1443E8BE4 > *(_DWORD *)(*(_QWORD *)(__readgsqword(0x58u) + 8i64 * (unsigned int)TlsIndex) + 0x2D8i64) )
      {
        sub_142458918(&dword_1443E8BE4);
        if ( dword_1443E8BE4 == -1 )
        {
          sub_141DAEDC0(&unk_1443E8B90);
          sub_1424588B8(&dword_1443E8BE4);
        }
      }
      (*(void (__fastcall **)(__int64))(*(_QWORD *)pUnknown + 80i64))(pUnknown);
      (*(void (__fastcall **)(__int64, signed __int64))(*(_QWORD *)pUnknown + 480i64))(pUnknown, 1i64);
      (*(void (__fastcall **)(__int64, _QWORD))(*(_QWORD *)pUnknown + 496i64))(pUnknown, 0i64);
      v41 = 0ui64;
      _mm_store_si128((__m128i *)&v41, (__m128i)0i64);
      (*(void (__fastcall **)(__int64, signed __int64, __int128 *))(*(_QWORD *)pUnknown + 0x1B8i64))(
        pUnknown,
        0xFD372409i64,
        &v41);
      (*(void (__fastcall **)(__int64, _QWORD, __int64))(*(_QWORD *)pUnknown + 0x218i64))(
        pUnknown,
        *(unsigned int *)&pWorldOcclusionQueryRenderModule->gap8[0x18],
        v5 + 0x610);
      v50 = "WorldOcclusionQuery";
      v52 = 3;
      v51 = &unk_1443E8B90;
      v53 = 0x24i64;
      v54 = v43;
      if ( pBatch->count )
      {
        do
        {
          (*(void (__fastcall **)(__int64, DxRenderQuery *, _QWORD))(*(_QWORD *)pUnknown + 0xE0i64))(
            pUnknown,
            pBatch->m_dxQuerys,
            cntr);
          (*(void (__fastcall **)(__int64, const char **))(*(_QWORD *)pUnknown + 0x188i64))(pUnknown, &v50);
          (*(void (__fastcall **)(__int64, DxRenderQuery *, _QWORD))(*(_QWORD *)pUnknown + 0xE8i64))(
            pUnknown,
            pBatch->m_dxQuerys,
            cntr);
          HIDWORD(v53) += 0x240;
          ++cntr;
        }
        while ( cntr < pBatch->count );
      }
      result = (*(__int64 (__fastcall **)(__int64))(*(_QWORD *)pUnknown + 88i64))(pUnknown);
      pBatch->status = 1;
    }
  }
  return result;
}

//Function address: 1491CB270
//function pattern: 75 0D C7 47 04 02 00 00 00 48 83 C4 ?? 5F C3
__int64 __fastcall fb::WorldOcclusionQueryRenderModule::retrieveBatchQueryData(WorldOcclusionQueryRenderModule *WorldOcclusionQueryRenderModule, BatchQuery *BatchQueries, float flScreenArea)
{
  __int64 result; // rax
  BatchQuery *pBatch; // rdi
  int Cntrrrr; // esi
  unsigned int RenderQueryIndex; // ebx
  float v7; // xmm0_4
  __int64 OutSize; // [rsp+20h] [rbp-48h]
  void *retaddr; // [rsp+68h] [rbp+0h]
  __int64 OutData; // [rsp+78h] [rbp+10h]

  result = (__int64)&retaddr;
  pBatch = BatchQueries;
  Cntrrrr = 0;
  RenderQueryIndex = 0;
  if ( BatchQueries->count )
  {
    do
    {
      LODWORD(OutSize) = 8;
      result = ((__int64 (__fastcall *)(DxRenderer *, DxRenderQuery *, _QWORD, __int64 *, __int64))g_pDxRenderer->vtable->getQueryData)( //[fb::DxRenderer::getQueryData] [ 141BD9840 ]
                 g_pDxRenderer,
                 pBatch->m_dxQuerys,            // RenderQuery
                 RenderQueryIndex,
                 &OutData,
                 OutSize);
      if ( (_BYTE)result )
      {
        v7 = (float)(signed int)OutData;
        if ( OutData < 0 )
          v7 = v7 + 1.8446744e19;
        result = (__int64)pBatch->outObjectScreenAreaCoverage;
        ++Cntrrrr;
        *(float *)(result + 4i64 * RenderQueryIndex) = fminf(v7 / flScreenArea, 1.0);
      }
      ++RenderQueryIndex;
    }
    while ( RenderQueryIndex < pBatch->count );
  }
  if ( Cntrrrr == pBatch->count )
  {
    pBatch->status = 2;
  }
  else
  {
    result = (unsigned int)pBatch->status;
    pBatch->status = result;
  }
  return result;
}

//Function address: 149C9B1A0
char __fastcall fb::SoldierOcclusionQueryManager::addRenderObject(__int64 a1, int a2, int LocalPlayerID, _OWORD *mTransform)
{
  __int64 dwLocalPlayerID; // r10
  unsigned __int32 v5; // ebx
  unsigned __int32 v6; // er8
  __int64 v7; // rbx
  SoldierOcclusionQueryManager::occlusionQuery *pOcclusionQuery; // rcx
  ObjectRenderInfo *pObjectRenderInfo; // rax
  __m128 v10; // xmm1
  __m128i v11; // xmm1
  __m128 v12; // xmm0
  __m128i v13; // xmm1
  char result; // al

  dwLocalPlayerID = LocalPlayerID;
  v5 = _InterlockedExchangeAdd((volatile signed __int32 *)(a1 + 4i64 * LocalPlayerID + 0x9938), 1u);
  v6 = v5 >> 5;
  v7 = v5 & 0x1F;
  pOcclusionQuery = (SoldierOcclusionQueryManager::occlusionQuery *)(0x1930
                                                                   * ((*(_DWORD *)(a1 + 4 * dwLocalPlayerID + 0x9930)
                                                                     + v6)
                                                                    % 6
                                                                    + 6 * dwLocalPlayerID)
                                                                   + a1
                                                                   + 0x210);
  if ( pOcclusionQuery->queriesInitialized || pOcclusionQuery->gap1909[v7] )
    return 0;
  *(_DWORD *)&pOcclusionQuery->gap1880[4 * v7] = a2;
  pObjectRenderInfo = &pOcclusionQuery->m_objects[v7];
  _mm_store_si128((__m128i *)pObjectRenderInfo->vertices, (__m128i)mTransform[4]);
  _mm_store_si128(
    (__m128i *)&pObjectRenderInfo->vertices[1],
    (__m128i)_mm_shuffle_ps((__m128)mTransform[4], (__m128)mTransform[5], 228));
  v10 = _mm_shuffle_ps((__m128)mTransform[4], (__m128)mTransform[5], 39);
  _mm_store_si128((__m128i *)&pObjectRenderInfo->vertices[5], (__m128i)_mm_shuffle_ps(v10, v10, 39));
  v11 = *((__m128i *)mTransform + 4);
  *(float *)v11.m128i_i32 = COERCE_FLOAT(mTransform[5]);
  _mm_store_si128((__m128i *)&pObjectRenderInfo->vertices[4], v11);
  v12 = _mm_shuffle_ps((__m128)mTransform[4], (__m128)mTransform[5], 114);
  _mm_store_si128((__m128i *)&pObjectRenderInfo->vertices[2], (__m128i)_mm_shuffle_ps(v12, v12, 141));
  v13 = *((__m128i *)mTransform + 5);
  *(float *)v13.m128i_i32 = COERCE_FLOAT(mTransform[4]);
  _mm_store_si128((__m128i *)&pObjectRenderInfo->vertices[3], v13);
  _mm_store_si128((__m128i *)&pObjectRenderInfo->vertices[7], (__m128i)mTransform[5]);
  _mm_store_si128(
    (__m128i *)&pObjectRenderInfo->vertices[6],
    (__m128i)_mm_shuffle_ps((__m128)mTransform[5], (__m128)mTransform[4], 228));
  *(_OWORD *)pObjectRenderInfo->worldTransform = *mTransform;
  *(_OWORD *)&pObjectRenderInfo->worldTransform[4] = mTransform[1];
  *(_OWORD *)&pObjectRenderInfo->worldTransform[8] = mTransform[2];
  *(_OWORD *)&pObjectRenderInfo->worldTransform[0xC] = mTransform[3];
  result = 1;
  pOcclusionQuery->gap1909[v7] = 1;
  pOcclusionQuery->byte1929 = 1;
  return result;
}