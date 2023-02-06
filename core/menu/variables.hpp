#pragma once

namespace variables {
	inline bool in_thirdperson = false;
	inline bool extra_chams = false;
	inline vec3_t saved_punch = {0.f,0.f,0.f};
	inline vec3_t saved_punch2 = { 0.f,0.f,0.f };
	inline selections aim_type_selections = { "loud","silent","x","x","x","x","x"};
	inline int aim_type = 1;
	inline bool aim_type_selections_opened = false;
	inline selections aim_priority_selections = { "dist","xhair","health","x","x","x","x" };
	inline int aim_priority = 1;
	inline bool aim_priority_selections_opened = false;
	inline selections tracer_origin_selections = { "top","bottom","xhair","x","x","x","x" };
	inline int tracer_origin = 0;
	inline bool tracer_origin_selections_opened = false;
	inline selections no_flash_selections = { "full","half","quarter","x","x","x","x" };
	inline int no_flash = 0;
	inline bool no_flash_selections_opened = false;
	inline selections rcs_selections = { "silent","loud","full y","half y","x","x","x" };
	inline int rcs_s = 0;
	inline bool rcs_opened = false;
	inline vec2_t angle = {0,0};
	inline bool bBhop = true;
	inline selections bhop_selections = { "tick","legit 70%","legit 50%","legit 30%","x","x","x" };
	inline int bhop = 0;
	inline bool bhop_selections_opened = false;
	inline selections aimbot_trigs_selections = { "in air","moving","flashed","defusing","firing","x","x" };
	inline selected aimbot_trigs_selected = {0,0,0,0,0,0,0};
	inline bool aimbot_trigs_opened = false;
	inline selections aimbot_active_selections = { "m1","firing","scoped","x","x","x","x" };
	inline selected aimbot_active_selected = { 0,0,0,0,0,0,0 };
	inline selections materials_selections = { "platinum","glass","crystal","gold","color","glass","glow" };
	inline bool aimbot_active_opened = false;
	inline int weapons = 4;
	inline bool weapon_color_bool = false;
	inline vec3_t weapon_color = { 0.2f,0.9f,0.2f };
	inline bool weapons_opened = false;
	inline int arms = 4;
	inline bool arms_color_bool = false;
	inline vec3_t arms_color = { 0.9f,0.2f,0.2f };
	inline bool arms_opened = false;
	inline int sleeves = 4;
	inline bool sleeves_color_bool = false;
	inline vec3_t sleeves_color = { 0.2f,0.9f,0.2f };
	inline bool sleeves_opened = false;
	inline int friendly = 4;
	inline bool friendly_color_bool = false;
	inline vec3_t friendly_color = { 0.2f,0.2f,0.9f };
	inline bool friendly_opened = false;
	inline int friendly_invis = 4;
	inline bool friendly_color_bool_invis = false;
	inline vec3_t friendly_color_invis = { 0.9f,0.2f,0.9f };
	inline bool friendly_opened_invis = false;
	inline int enemy = 4;
	inline bool enemy_color_bool = false;
	inline vec3_t enemy_color = { 0.9f,0.2f,0.2f };
	inline bool enemy_opened = false;
	inline int enemy_invis = 4;
	inline bool enemy_color_bool_invis = false;
	inline vec3_t enemy_color_invis = { 0.2f,0.9f,0.2f };
	inline bool enemy_opened_invis = false;
	inline bool bFov = true;
	inline bool bRadar = true;
	inline bool bNoFlash = true;
	inline bool bRcs = false;
	inline bool bTPS = false;
	inline selections removals_selections = { "scope","weapon","hands","sleeve","friendlys","x","x" };
	inline selected removals_selected = { 0,0,0,0,0,0,0 };
	inline bool removals_opened = false;
	inline selections misc_selections = { "hitmarker","x","x","x","x","x","x" };
	inline selected misc_selected = { 0,0,0,0,0,0,0 };
	inline bool misc_opened = false;
	inline float fov = 120;
	inline bool bAimbot = false;
	inline player_t* aimbot_target = NULL;
	namespace aimbot {
		inline bool vischeck = true;
		inline bool sticky = false;
		inline bool rcs = true;
		inline bool teamcheck = true;
		inline bool transpcheck = true;
		inline bool autostop = false;
		inline bool autoshoot = false;
		inline bool autoscope = false;
		inline bool antiuntrusted = false;
		inline bool aimkey = false;
		inline int Selection = 0; //0 is distance 1 is fov
		inline bool TargetInfo = true;
		inline bool b1 = false;
		inline bool b2 = false;
		inline bool remove_punch = true;
		// fov,deadzone,randomisation,smoothing
		inline bool smooth = false;
		inline bool fovcheck = false;
		inline bool random = false;
		inline bool deadzone = false;
		inline bool deadzonedelay = false;

		inline float smoothing = 0.f;
		inline float fovcircle = 10.f;
		inline float randomisation = 0.f;
		inline float deadzonesize = 2.f;
		inline float deadzonedelaytime = 0.2f;
	};
	inline bool bVisuals = true;
	namespace visuals {
		inline bool tracers = false;
		inline bool visualise_target = false;
		inline bool box = true;
		namespace box_esp {
			inline selections box_selections = { "health","armor","distance","flags","x","x","x" };
			inline selected box_selected = { 1,1,1,1,0,0,0 };
			inline bool box_selections_opened = false;
		}
		inline bool glow = false;
		inline bool flags = false;
		inline bool chams = false;
		namespace cham {
			inline bool arms = false;
			inline bool sleeves = false;
			inline bool weapon = false;
			inline bool friendly = false;
			inline bool friendly_invis = false;
			inline bool enemy = false;
			inline bool enemy_invis = false;
			inline bool extend_chams = false;
			inline float blue = 0.f;
		}
	}
	inline DWORD LocalP = NULL;
	namespace menu {
		inline bool opened = false;
		inline int x = 140, y = 140;
		inline int w = 600, h = 400;
	}
}