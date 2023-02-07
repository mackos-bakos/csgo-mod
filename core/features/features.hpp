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
		int distance_to(player_t* entity);

		float Xhair_Distance(player_t* entity);

		player_t* get_best_target();

		bool visible(player_t* entity);

		void auto_shoot(c_usercmd* cmd);
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
		void box(player_t* entity);
		void ShowTargetInfo();


		void glow(player_t* entity);
		void chams(float r, float g, float b, bool through_walls, const char* texture);
		void skeleton(player_t* entity);

		const char* resolve_material(int pointer);
	}
}