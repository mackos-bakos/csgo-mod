#include "../features.hpp"

void misc::movement::bunny_hop(c_usercmd* cmd) {
	if (!variables::bBhop)
		return;

	const int move_type = csgo::local_player->move_type();

	if (move_type == movetype_ladder || move_type == movetype_noclip || move_type == movetype_observer)
		return;
	int should_jump = rand() % 101; int chance;
	switch (variables::bhop) {
	case 0:
		chance = 100;
		break;
	case 1:
		chance = 70;
		break;
	case 2:
		chance = 50;
		break;
	case 3:
		chance = 30;
		break;
	}
	if (!(csgo::local_player->flags() & fl_onground) && should_jump <= chance)
		cmd->buttons &= ~in_jump;
};
void misc::view::fov_changer() {
	if (!variables::bFov || csgo::local_player->active_weapon() == NULL) {
		csgo::local_player->set_view_fov(90);
		return;
	}
	weapon_t* weapon = csgo::local_player->active_weapon();

	weapon_info_t* info = weapon->get_weapon_data();

	int weapon_type = info->weapon_type;

	if (weapon_type == 5) {
		csgo::local_player->set_view_fov(90);
	}
	else {
		csgo::local_player->set_view_fov(variables::fov);
	}
}
void misc::view::test() {
	
}
void misc::view::no_flash() {
	if (!variables::bNoFlash) {
		return;
	}
	if (csgo::local_player != NULL) {
		if (csgo::local_player->is_flashed()) {
			switch (variables::no_flash) {
			case 0:
				csgo::local_player->set_flash(0);
				break;
			case 1:
				csgo::local_player->set_flash_alpha(50.f);
				break;
			case 2:
				csgo::local_player->set_flash_alpha(25.f);
				break;
			}
		}
	}
}
void misc::view::radar_hack() {
	if (!variables::bRadar) {
		return;
	}

	for (short int entId = 0; entId < 64; entId++) {

		player_t* entity = static_cast<player_t*>(interfaces::entity_list->get_client_entity(entId));

		if (entity == NULL) {
			continue;
		}
		if (entity->dormant()) {
			continue;
		}
		if (entity->health() < 1) {
			continue;
		}
		if (entity->team() != csgo::local_player->team()) {
			entity->set_spotted(true);
		}

	}
}
void misc::rcs(c_usercmd* cmd) {
	if (!variables::bRcs || variables::aimbot_target != NULL) {
		return;
	}

	vec3_t punch = csgo::local_player->aim_punch_angle();
	vec3_t view_angles; interfaces::engine->get_view_angles(view_angles);

	if (variables::rcs_s == 0) {
		cmd->viewangles.x -= punch.x;
		cmd->viewangles.y -= punch.y;
	}
	else{
		vec3_t angle;
		switch (variables::rcs_s) {
		case 1:
			angle = { view_angles.x - punch.x + variables::saved_punch.x,view_angles.y - punch.y + variables::saved_punch.y,0.f };
			break;
		case 2:
			angle = { view_angles.x,view_angles.y - punch.y + variables::saved_punch.y,0.f };
			break;
		case 3:
			angle = { view_angles.x ,view_angles.y - ((punch.y + variables::saved_punch.y) * 0.5f),0.f };
			break;
		}
		interfaces::engine->set_view_angles(angle);
	}
}
void misc::view::third_person() {
	if (!variables::bTPS) {
		if (variables::in_thirdperson) {
			interfaces::engine->execute_cmd("firstperson");
			variables::in_thirdperson = false;
		}
		if (variables::visuals::cham::extend_chams && !variables::extra_chams) {
			interfaces::engine->execute_cmd("r_DrawOtherModels 2");
			variables::extra_chams = true;
		}
		else if (variables::extra_chams && !variables::visuals::cham::extend_chams) {
			interfaces::engine->execute_cmd("r_DrawOtherModels 1");
			variables::extra_chams = false;
		}
		return;
	}
	if (!variables::in_thirdperson) {
		interfaces::engine->execute_cmd("thirdperson");
		variables::in_thirdperson = true;
	}
	interfaces::engine->execute_cmd("thirdperson");
	if (variables::visuals::cham::extend_chams && !variables::extra_chams) { 
		interfaces::engine->execute_cmd("r_DrawOtherModels 2"); 
		variables::extra_chams = true;
	}
	else if (variables::extra_chams && !variables::visuals::cham::extend_chams) {
		interfaces::engine->execute_cmd("r_DrawOtherModels 1");
		variables::extra_chams = false;
	}
}
void misc::view::bomb_timer() {
}