#pragma once

#pragma once
#include <cstdint>
//GuidedHacking.com r0x0rs ur b0x0rs
namespace offsets
{

	//signatures

	constexpr ptrdiff_t dwClientState = 0x58CFDC;
	constexpr ptrdiff_t dwClientState_GetLocalPlayer = 0x180;
	constexpr ptrdiff_t dwClientState_IsHLTV = 0x4D48;
	constexpr ptrdiff_t dwClientState_Map = 0x28C;
	constexpr ptrdiff_t dwClientState_MapDirectory = 0x188;
	constexpr ptrdiff_t dwClientState_MaxPlayer = 0x388;
	constexpr ptrdiff_t dwClientState_PlayerInfo = 0x52C0;
	constexpr ptrdiff_t dwClientState_State = 0x108;
	constexpr ptrdiff_t dwClientState_ViewAngles = 0x4D90;
	constexpr ptrdiff_t clientstate_delta_ticks = 0x174;
	constexpr ptrdiff_t clientstate_last_outgoing_command = 0x4D2C;
	constexpr ptrdiff_t clientstate_choked_commands = 0x4D30;
	constexpr ptrdiff_t clientstate_net_channel = 0x9C;
	constexpr ptrdiff_t dwEntityList = 0x4DDB8FC;
	constexpr ptrdiff_t dwForceAttack = 0x320BDC8;
	constexpr ptrdiff_t dwForceAttack2 = 0x320BDD4;
	constexpr ptrdiff_t dwForceBackward = 0x320BE10;
	constexpr ptrdiff_t dwForceForward = 0x320BE04;
	constexpr ptrdiff_t dwForceJump = 0x52858A0;
	constexpr ptrdiff_t dwForceLeft = 0x320BE1C;
	constexpr ptrdiff_t dwForceRight = 0x320BE28;
	constexpr ptrdiff_t dwGameDir = 0x62B900;
	constexpr ptrdiff_t dwGameRulesProxy = 0x52F90BC;
	constexpr ptrdiff_t dwGetAllClasses = 0xDE9C9C;
	constexpr ptrdiff_t dwGlobalVars = 0x58CCE0;
	constexpr ptrdiff_t dwGlowObjectManager = 0x5324590;
	constexpr ptrdiff_t dwInput = 0x522CED0;
	constexpr ptrdiff_t dwInterfaceLinkList = 0x96EF44;
	constexpr ptrdiff_t dwLocalPlayer = 0xDBF4BC;
	constexpr ptrdiff_t dwMouseEnable = 0xDC51C8;
	constexpr ptrdiff_t dwMouseEnablePtr = 0xDC5198;
	constexpr ptrdiff_t dwPlayerResource = 0x320A160;
	constexpr ptrdiff_t dwRadarBase = 0x5210674;
	constexpr ptrdiff_t dwSensitivity = 0xDC5064;
	constexpr ptrdiff_t dwSensitivityPtr = 0xDC5038;
	constexpr ptrdiff_t dwSetClanTag = 0x8A410;
	constexpr ptrdiff_t dwViewMatrix = 0x4DCD214;
	constexpr ptrdiff_t dwWeaponTable = 0x522D994;
	constexpr ptrdiff_t dwWeaponTableIndex = 0x326C;
	constexpr ptrdiff_t dwYawPtr = 0xDC4E28;
	constexpr ptrdiff_t dwZoomSensitivityRatioPtr = 0xDCB610;
	constexpr ptrdiff_t dwbSendPackets = 0xD8452;
	constexpr ptrdiff_t dwppDirect3DDevice9 = 0xA6050;
	constexpr ptrdiff_t m_pStudioHdr = 0x2950;
	constexpr ptrdiff_t m_yawClassPtr = 0xDC4E28;
	constexpr ptrdiff_t m_pitchClassPtr = 0x5210910;
	constexpr ptrdiff_t interface_engine_cvar = 0x3EA3C;
	constexpr ptrdiff_t convar_name_hash_table = 0x2F190;
	constexpr ptrdiff_t m_bDormant = 0xED;
	constexpr ptrdiff_t model_ambient_min = 0x590054;
	constexpr ptrdiff_t set_abs_angles = 0x1E59F0;
	constexpr ptrdiff_t set_abs_origin = 0x1E5830;
	constexpr ptrdiff_t is_c4_owner = 0x3CB320;
	constexpr ptrdiff_t force_update_spectator_glow = 0x3BE2BA;
	constexpr ptrdiff_t anim_overlays = 0x2990;
	constexpr ptrdiff_t m_flSpawnTime = 0x103C0;
	constexpr ptrdiff_t find_hud_element = 0x278859D0;
	constexpr ptrdiff_t m_bIsLocalPlayer = 0x3628;


	//netvars

	constexpr ptrdiff_t m_ArmorValue = 0x117CC;
	constexpr ptrdiff_t m_Collision = 0x320;
	constexpr ptrdiff_t m_CollisionGroup = 0x474;
	constexpr ptrdiff_t m_Local = 0x2FCC;
	constexpr ptrdiff_t m_MoveType = 0x25C;
	constexpr ptrdiff_t m_OriginalOwnerXuidHigh = 0x31D4;
	constexpr ptrdiff_t m_OriginalOwnerXuidLow = 0x31D0;
	constexpr ptrdiff_t m_aimPunchAngle = 0x303C;
	constexpr ptrdiff_t m_aimPunchAngleVel = 0x3048;
	constexpr ptrdiff_t m_bGunGameImmunity = 0x9990;
	constexpr ptrdiff_t m_bHasDefuser = 0x117DC;
	constexpr ptrdiff_t m_bHasHelmet = 0x117C0;
	constexpr ptrdiff_t m_bInReload = 0x32B5;
	constexpr ptrdiff_t m_bIsDefusing = 0x997C;
	constexpr ptrdiff_t m_bIsScoped = 0x9974;
	constexpr ptrdiff_t m_bSpotted = 0x93D;
	constexpr ptrdiff_t m_bSpottedByMask = 0x980;
	constexpr ptrdiff_t m_dwBoneMatrix = 0x26A8;
	constexpr ptrdiff_t m_fAccuracyPenalty = 0x3340;
	constexpr ptrdiff_t m_fFlags = 0x104;
	constexpr ptrdiff_t m_hViewModel = 0x3308;
	constexpr ptrdiff_t m_flFallbackWear = 0x31E0;
	constexpr ptrdiff_t m_flFlashDuration = 0x10470;
	constexpr ptrdiff_t m_flFlashMaxAlpha = 0x1046C;
	constexpr ptrdiff_t m_flNextPrimaryAttack = 0x3248;
	constexpr ptrdiff_t m_hActiveWeapon = 0x2F08;
	constexpr ptrdiff_t m_hMyWeapons = 0x2E08;
	constexpr ptrdiff_t m_hObserverTarget = 0x339C;
	constexpr ptrdiff_t m_hOwner = 0x29DC;
	constexpr ptrdiff_t m_hOwnerEntity = 0x14C;
	constexpr ptrdiff_t m_iAccountID = 0x2FD8;
	constexpr ptrdiff_t m_iClip1 = 0x3274;
	constexpr ptrdiff_t m_zoomLevel = 0x33E0;
	constexpr ptrdiff_t m_iCompetitiveRanking = 0x1A84;
	constexpr ptrdiff_t m_iCompetitiveWins = 0x1B88;
	constexpr ptrdiff_t m_iCrosshairId = 0x11838;
	constexpr ptrdiff_t m_iEntityQuality = 0x2FBC;
	constexpr ptrdiff_t m_iFOVStart = 0x31F8;
	constexpr ptrdiff_t m_iGlowIndex = 0x10488;
	constexpr ptrdiff_t m_iHealth = 0x100;
	constexpr ptrdiff_t m_iItemDefinitionIndex = 0x2FBA;
	constexpr ptrdiff_t m_iItemIDHigh = 0x2FD0;
	constexpr ptrdiff_t m_iObserverMode = 0x3388;
	constexpr ptrdiff_t m_iShotsFired = 0x103E0;
	constexpr ptrdiff_t m_iState = 0x3268;
	constexpr ptrdiff_t m_iTeamNum = 0xF4;
	constexpr ptrdiff_t m_lifeState = 0x25F;
	constexpr ptrdiff_t m_nFallbackPaintKit = 0x31D8;
	constexpr ptrdiff_t m_nFallbackSeed = 0x31DC;
	constexpr ptrdiff_t m_nFallbackStatTrak = 0x31E4;
	constexpr ptrdiff_t m_iDefaultFOV = 0x333C;
	constexpr ptrdiff_t m_iFOV = 0x31F4;
	constexpr ptrdiff_t m_nForceBone = 0x268C;
	constexpr ptrdiff_t m_nTickBase = 0x3440;
	constexpr ptrdiff_t m_rgflCoordinateFrame = 0x444;
	constexpr ptrdiff_t m_szCustomName = 0x304C;
	constexpr ptrdiff_t m_szLastPlaceName = 0x35C4;
	constexpr ptrdiff_t m_vecOrigin = 0x138;
	constexpr ptrdiff_t m_vecVelocity = 0x114;
	constexpr ptrdiff_t m_vecViewOffset = 0x108;
	constexpr ptrdiff_t m_viewPunchAngle = 0x3030;
	constexpr ptrdiff_t m_thirdPersonViewAngles = 0x31E8;
	constexpr ptrdiff_t m_clrRender = 0x70;
	constexpr ptrdiff_t m_bBombTicking = 0x2990;
	constexpr ptrdiff_t m_bBombDefused = 0x29C0;
	constexpr ptrdiff_t m_flC4Blow = 0x29A0;
	constexpr ptrdiff_t m_hBombDefuser = 0x29C4;
	constexpr ptrdiff_t m_flTimerLength = 0x29A4;
	constexpr ptrdiff_t m_flDefuseLength = 0x29B8;
	constexpr ptrdiff_t m_flDefuseCountDown = 0x29BC;
	constexpr ptrdiff_t m_nBombSite = 0x2994;
	constexpr ptrdiff_t cs_gamerules_data = 0x0;
	constexpr ptrdiff_t m_SurvivalRules = 0xD00;
	constexpr ptrdiff_t m_SurvivalGameRuleDecisionTypes = 0x1328;
	constexpr ptrdiff_t m_bIsValveDS = 0x7C;
	constexpr ptrdiff_t m_bFreezePeriod = 0x20;
	constexpr ptrdiff_t m_bBombPlanted = 0x9A5;
	constexpr ptrdiff_t m_bIsQueuedMatchmaking = 0x74;
	constexpr ptrdiff_t m_flSimulationTime = 0x268;
	constexpr ptrdiff_t m_flLowerBodyYawTarget = 0x9ADC;
	constexpr ptrdiff_t m_angEyeAnglesX = 0x117D0;
	constexpr ptrdiff_t m_angEyeAnglesY = 0x117D4;
	constexpr ptrdiff_t m_flNextAttack = 0x2D80;
	constexpr ptrdiff_t m_iMostRecentModelBoneCounter = 0x2690;
	constexpr ptrdiff_t m_flLastBoneSetupTime = 0x2928;
	constexpr ptrdiff_t m_bStartedArming = 0x3400;
	constexpr ptrdiff_t m_bUseCustomBloomScale = 0x9DA;
	constexpr ptrdiff_t m_bUseCustomAutoExposureMin = 0x9D8;
	constexpr ptrdiff_t m_bUseCustomAutoExposureMax = 0x9D9;
	constexpr ptrdiff_t m_flCustomBloomScale = 0x9E4;
	constexpr ptrdiff_t m_flCustomAutoExposureMin = 0x9DC;
	constexpr ptrdiff_t m_flCustomAutoExposureMax = 0x9E0;
	constexpr ptrdiff_t m_nViewModelIndex = 0x29D0;
	constexpr ptrdiff_t m_nModelIndex = 0x258;

}