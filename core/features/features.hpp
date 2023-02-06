#pragma once
#include "../../dependencies/utilities/csgo.hpp"
#include "../menu/variables.hpp"
#include "../offsets.h"
#include <ctime>
namespace misc {
	namespace movement {
		void bunny_hop(c_usercmd* cmd);
	};
	namespace view {
		void fov_changer();
		void test();
		void radar_hack();
		void no_flash();
		void third_person();
		void bomb_timer();
	};
	void rcs(c_usercmd* cmd);
}
namespace aimbot {
	namespace master {
		void aim_at_target(c_usercmd* cmd);
	};
	namespace sub {
		player_t* get_best_target();
		bool visible(player_t* entity);
		int distance_to(player_t* entity);
		float Xhair_Distance(player_t* entity);
		bool IsTransparent(player_t* entity);
		bool is_wall_bangable(player_t* entity);
		void auto_stop(c_usercmd* cmd);
		void auto_shoot(c_usercmd* cmd);
		bool hit_chance();
		bool aiming_at(player_t* entity);
	};
}
namespace visuals {
	namespace master {
		vec2_t Get2dPos(player_t* entity);
		vec2_t Get2dBonePos(player_t* entity, int bone);
		vec2_t Get2dCustom(player_t* entity, vec3_t custom);
		vec2_t ViewAnglesToScreen(vec2_t angle);
		void VisualsLoop();
	}
	namespace modules {
		void draw_fake_scope();
		void draw_hit_marker(i_game_event* event);
		void tracers(player_t* entity);
		void visualise_target();
		void box(player_t* entity);
		void ShowTargetInfo();
		namespace box_esp {
			void health_bar();
			void armor_bar();
		}
		void glow(player_t* entity);
		void flags(player_t* entity);
		void chams(float r, float g, float b, bool through_walls, const char* texture);
		void skeleton(player_t* entity);
		const char* resolve_material(int pointer);
	}
}