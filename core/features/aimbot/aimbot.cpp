#include "../features.hpp"
void aimbot::master::aim_at_target(c_usercmd* cmd) {
	if (!variables::bAimbot || csgo::local_player->health() < 1) {
		variables::aimbot_target = NULL;
		return;
	}
	vec3_t view_angles;  interfaces::engine->get_view_angles(view_angles);
	if (variables::aimbot::b1) {
		if (variables::aimbot_active_selected.deref(0) && !GetAsyncKeyState(VK_LBUTTON) && !variables::menu::opened) {
			return;
		}
		if (variables::aimbot_active_selected.deref(1) && csgo::local_player->shots_fired() == 0) {
			return;
		}
		if (variables::aimbot_active_selected.deref(2) && !csgo::local_player->is_scoped()) {
			return;
		}
	}
	if (variables::aimbot::b2) {
		if (variables::aimbot_trigs_selected.deref(0) && csgo::local_player->is_in_air()) {
			return;
		}
		if (variables::aimbot_trigs_selected.deref(1) && csgo::local_player->is_moving()) {
			return;
		}
		if (variables::aimbot_trigs_selected.deref(2) && csgo::local_player->is_flashed()) {
			return;
		}
		if (variables::aimbot_trigs_selected.deref(3) && csgo::local_player->is_defusing()) {
			return;
		}
		if (variables::aimbot_trigs_selected.deref(4) && csgo::local_player->shots_fired() > 0) {
			return;
		}
	}

	player_t* target = aimbot::sub::get_best_target();
	variables::aimbot_target = target;
	if (target == NULL) {
		variables::angle = { view_angles.x,view_angles.y };
		return;
	}
	vec3_t AimAt = target->get_bone_position(8);
	vec3_t local_origin = (csgo::local_player->origin() + csgo::local_player->view_offset()); 
	vec3_t dif = AimAt - local_origin;

	int DistanceToEnemy = aimbot::sub::distance_to(target);

	float pitch = -asin(dif.z / DistanceToEnemy) * (180 / 3.14159265358979323846);
	float yaw = atan2(dif.y, dif.x) * (180 / 3.14159265358979323846);
	float xhair_distance = aimbot::sub::Xhair_Distance(target);

	vec3_t angle = { pitch,yaw,0.f };
	vec3_t punch = csgo::local_player->aim_punch_angle();
	vec3_t rec_angle = { angle.x - (punch.x * 2.f),angle.y - (punch.y * 2.f),0.f };

	if (variables::aimbot::remove_punch) {
		vec3_t angle_x = { view_angles.x - punch.x + variables::saved_punch.x,view_angles.y - punch.y + variables::saved_punch.y,0.f };
		interfaces::engine->set_view_angles(angle_x);
		//csgo::local_player->set_view_punch({ 0.f,0.f,0.f });
	}
	// legit bot
	if (variables::aimbot::smooth) {
		float move;
		if (variables::aimbot::randomisation) {
			int meh = variables::aimbot::randomisation; float step = rand() % meh; move = ((10.f - step) * (variables::aimbot::smoothing / 100.f));
		}
		else {
			move = (10.f * (variables::aimbot::smoothing / 100.f));
		}
		if (variables::aim_type == 0) {
			if (variables::aimbot::fovcheck && variables::aimbot::deadzone && xhair_distance < variables::aimbot::deadzonesize) {
				return;
			}
			if (!variables::aimbot::rcs) {
				rec_angle = { pitch,yaw,0.f };
			}
			if (view_angles.x > rec_angle.x) {
				if ((view_angles.x - rec_angle.x) < move) {
					view_angles.x = rec_angle.x;
				}
				else {
					view_angles.x -= move;
				}
			}
			else {
				if ((rec_angle.x - view_angles.x) < move) {
					view_angles.x = rec_angle.x;
				}
				else {
					view_angles.x += move;
				}
			}
			if (view_angles.y > rec_angle.y) {
				if ((view_angles.y - rec_angle.y) < move) {
					view_angles.y = rec_angle.y;
				}
				else {
					view_angles.y -= move;
				}
			}
			else {
				if ((rec_angle.y - view_angles.y) < move) {
					view_angles.y = rec_angle.y;
				}
				else {
					view_angles.y += move;
				}
			}
		interfaces::engine->set_view_angles(view_angles);
		if (view_angles.x == rec_angle.x && view_angles.y == rec_angle.y) {
			aimbot::sub::auto_shoot(cmd);
		}
		}
		if (variables::aim_type == 1) {
			if (!variables::aimbot::rcs) {
				rec_angle = { pitch,yaw,0.f };
			}
			if (variables::angle.x > rec_angle.x) {
				if ((variables::angle.x - rec_angle.x) < move) {
					variables::angle.x = rec_angle.x;
				}
				else {
					variables::angle.x -= move;
				}
			}
			else {
				if ((rec_angle.x - variables::angle.x) < move) {
					variables::angle.x = rec_angle.x;
				}
				else {
					variables::angle.x += move;
				}
			}
			if (variables::angle.y > rec_angle.y) {
				if ((variables::angle.y - rec_angle.y) < move) {
					variables::angle.y = rec_angle.y;
				}
				else {
					variables::angle.y -= move;
				}
			}
			else {
				if ((rec_angle.y - variables::angle.y) < move) {
					variables::angle.y = rec_angle.y;
				}
				else {
					variables::angle.y += move;
				}
			}
			cmd->viewangles.x = variables::angle.x;
			cmd->viewangles.y = variables::angle.y;
			if (variables::angle.x == rec_angle.x && variables::angle.y == rec_angle.y) {
				aimbot::sub::auto_shoot(cmd);
			}
		}
	}
	// legit bot end
	else if (variables::aimbot::rcs) {
		switch (variables::aim_type) {
		case 0:
			interfaces::engine->set_view_angles(rec_angle);
			break;
		case 1:
			cmd->viewangles.x = rec_angle.x;
			cmd->viewangles.y = rec_angle.y;
			break;
		}
		aimbot::sub::auto_shoot(cmd);
	}
	else {
		switch (variables::aim_type) {
		case 0:
			interfaces::engine->set_view_angles(angle);
			break;
		case 1:
			cmd->viewangles.x = angle.x;
			cmd->viewangles.y = angle.y;
			break;
		}
		aimbot::sub::auto_shoot(cmd);
	}
}
player_t* aimbot::sub::get_best_target() {
	int distance = 0;
	player_t* target = NULL; bool TargetOverRide = false;
	for (short int entId = 0; entId < 64; entId++) {
		player_t* entity = static_cast<player_t*>(interfaces::entity_list->get_client_entity(entId));
		float entity_distance = 0;
		if (entity == NULL) {
			continue;
		}
		if (variables::aimbot::vischeck && !visible(entity)) {
			continue;
		}
		if (entity->dormant()) {
			continue;
		}
		if (entity->team() == csgo::local_player->team() && variables::aimbot::teamcheck) {
			continue;
		}
		if (entity->health() < 1) {
			continue;
		}
		switch (variables::aim_priority) {
		default:
			entity_distance = aimbot::sub::Xhair_Distance(entity);
			break;
		case 0:
			entity_distance = aimbot::sub::distance_to(entity);
			break;
		case 1:
			entity_distance = aimbot::sub::Xhair_Distance(entity);
			break;
		case 2:
			entity_distance = entity->health();
			break;
		}
		if (variables::aimbot::fovcheck && variables::aim_priority == 1) {
			if (entity_distance > variables::aimbot::fovcircle){ 
				continue; 
			}
		}
		if (variables::aimbot::transpcheck && entity->has_gun_game_immunity()) {
			continue;
		}
		if (entity == variables::aimbot_target && variables::aimbot::sticky) {
			TargetOverRide = true;
			target = entity;
		}
		if (entity->is_defusing()) {
			TargetOverRide = true;
			target = entity;
		}
		if (!TargetOverRide) {
			if (distance == 0) {
				distance = entity_distance;
				target = entity;
			}
			if (entity_distance < distance) {
				distance = entity_distance;
				target = entity;
			}
		}
	}
	return target;
}
int aimbot::sub::distance_to(player_t* entity) {
	vec3_t local_origin = csgo::local_player->origin() + csgo::local_player->view_offset(); vec3_t enemy_origin = entity->origin() + entity->view_offset();
	vec3_t dif = enemy_origin-local_origin;

	return sqrt(dif.x * dif.x + dif.y * dif.y + dif.z * dif.z);
}
float aimbot::sub::Xhair_Distance(player_t* entity) {
	int x, y;interfaces::engine->get_screen_size(x, y);

	vec2_t crosshair;crosshair.x = (x / 2);crosshair.y = (y / 2); vec2_t EnemyScreen = visuals::master::Get2dPos(entity);

	float ChangeInY = abs(EnemyScreen.y - crosshair.y);
	float ChangeInX = abs(EnemyScreen.x - crosshair.x);

	return sqrt((ChangeInY * ChangeInY) + (ChangeInX * ChangeInX));
}
bool aimbot::sub::visible(player_t* entity) {
	if (csgo::local_player->can_see_player_pos(csgo::local_player, entity->get_bone_position(8))) {
		return true;
	}
}

bool aimbot::sub::IsTransparent(player_t* entity) {
	model_t* model = entity->model();
	if (model->flags & material_var_translucent) {
		return true;
	}
	return false;
}

bool aimbot::sub::is_wall_bangable(player_t* entity) {
	return true;
}

void aimbot::sub::auto_stop(c_usercmd* cmd) {
	if (!variables::aimbot::autostop) {
		return;
	}
	vec3_t cur_vel = csgo::local_player->velocity();
	if (csgo::local_player->is_moving()) {
		if (cur_vel.x > 0) {
			console::log("moving forward \n");
			cmd->forwardmove = -(cur_vel.x);
		}
		else {
			console::log("moving backward \n");
			cmd->forwardmove = abs(cur_vel.x);
		}
		if (cur_vel.y > 0) {
			console::log("moving left \n");
			cmd->sidemove = -(cur_vel.y);
		}
		else {
			console::log("moving right \n");
			cmd->sidemove = abs(cur_vel.y);
		}
	}
}

void aimbot::sub::auto_shoot(c_usercmd* cmd) {
	weapon_t* weapon = csgo::local_player->active_weapon();
	weapon_info_t* info = weapon->get_weapon_data();
	int weapon_type = info->weapon_type; int spread = weapon->inaccuracy();
	if (!variables::aimbot::autoshoot || weapon->clip1_count() == 0 || csgo::local_player->health() < 1) {
		return;
	}
	if (hit_chance()) {
		if (weapon_type == 5 && csgo::local_player->aim_punch_angle().x == 0){
			if (!csgo::local_player->is_scoped() && variables::aimbot::autoscope) {
				cmd->buttons |= in_attack2;
			}
			else {
				cmd->buttons |= in_attack;
			}
			return;
		}
		if (info->weapon_full_auto && weapon->recoil_index() < 5) {
			cmd->buttons |= in_attack;
		}
		else if (csgo::local_player->aim_punch_angle().x  == 0) {
			cmd->buttons |= in_attack;
		}
	}
}
bool aimbot::sub::hit_chance() {
	return true;
}