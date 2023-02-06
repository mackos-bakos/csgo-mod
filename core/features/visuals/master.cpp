#include "../features.hpp"

vec2_t visuals::master::Get2dPos(player_t* entity) {
	vec2_t screen;math::world_to_screen(entity->get_eye_pos(), screen);
	return screen;
}
vec2_t visuals::master::Get2dBonePos(player_t* entity,int bone) {
	vec2_t screen; math::world_to_screen(entity->get_bone_position(bone), screen);
	return screen;
}
vec2_t visuals::master::Get2dCustom(player_t* entity,vec3_t custom) {
	vec2_t screen; math::world_to_screen(custom, screen);
	return screen;
}
void visuals::master::VisualsLoop() {
	if (!variables::bVisuals || csgo::local_player == NULL) {
		return;
	}
	visuals::modules::ShowTargetInfo();
	for (short int entId = 0; entId < 64; entId++) {
		player_t* entity = static_cast<player_t*>(interfaces::entity_list->get_client_entity(entId));
		if (entity == NULL) {
			continue;
		}
		if (entity->dormant()) {
			continue;
		}
		if (entity->team() == csgo::local_player->team()) {
			continue;
		}
		if (entity->health() < 1) {
			continue;
		}
		if (variables::visuals::tracers) {
			visuals::modules::tracers(entity);
		}
		if (variables::visuals::box) {
			visuals::modules::box(entity);
		}
		if (variables::visuals::glow) {
			visuals::modules::glow(entity);
		}
	}
}
void visuals::modules::tracers(player_t* entity) {
	int x, y;
	vec2_t raw = visuals::master::Get2dPos(entity);
	interfaces::engine->get_screen_size(x, y);
	std::int32_t draw_from_x = 0; std::int32_t draw_from_y = 0;
	switch (variables::tracer_origin) {
	default:
		draw_from_x = (x / 2);draw_from_y = 0;
		break;
	case 0:
		draw_from_x = (x / 2);draw_from_y = 0;
		break;
	case 1:
		draw_from_x = (x / 2);draw_from_y = y;
		break;
	case 2:
		draw_from_x = (x / 2);draw_from_y = (y / 2);
		break;
	}
	std::int32_t draw_to_x = raw.x; std::int32_t draw_to_y = raw.y;
	if (entity == variables::aimbot_target) {
		render::draw_line(draw_from_x, draw_from_y, draw_to_x, draw_to_y, color(100, 100, 100, 255));
	}
	else if (aimbot::sub::visible(entity)) {
		render::draw_line(draw_from_x, draw_from_y, draw_to_x, draw_to_y, color(0, 255, 0, 255));
	}
	else {
		render::draw_line(draw_from_x, draw_from_y, draw_to_x, draw_to_y, color(255, 0, 0, 255));
	}
	//render::draw_line(400, 400, 200, 200, color(255, 0, 0, 255));
}
void visuals::modules::chams(float r,float g,float b, bool through_walls,const char* texture) {
	i_material* material = interfaces::material_system->find_material(texture);
	material->set_material_var_flag(material_var_ignorez, through_walls);
	material->color_modulate(r, g, b); material->alpha_modulate(1.f);
	interfaces::model_render->override_material(material);
}
const char* visuals::modules::resolve_material(int pointer) {
	if (pointer == 0) { return "models/player/ct_fbi/ct_fbi_glass"; }
	if (pointer == 1) { return "models/inventory_items/cologne_prediction/cologne_prediction_glass"; }
	if (pointer == 2) { return "models/inventory_items/trophy_majors/crystal_clear"; }
	if (pointer == 3) { return "models/inventory_items/trophy_majors/gold"; }
	if (pointer == 4) { return "debug/debugambientcube"; }
	if (pointer == 5) { return "models/inventory_items/trophy_majors/gloss"; }
	if (pointer == 6) { return "vgui/achievements/glow"; }
}
void visuals::modules::box(player_t* entity) {
	vec2_t head_2d = visuals::master::Get2dBonePos(entity,8);
	vec2_t feet_2d = visuals::master::Get2dCustom(entity, entity->origin());
	int scaling = (head_2d.y - feet_2d.y) / 2; bool visible = aimbot::sub::visible(entity);
	int scaling_head = abs((head_2d.y - feet_2d.y) / 4); weapon_t* weapon = entity->active_weapon();
	if ((entity->is_flashed() || weapon->clip1_count() == 0) && variables::visuals::box_esp::box_selected.deref(3)) {
		render::draw_border_line_vertical(feet_2d.x + scaling, head_2d.y - scaling_head, feet_2d.x + scaling, feet_2d.y, color(255, 255, 255, 255));
		render::draw_border_line_vertical(feet_2d.x - scaling, head_2d.y - scaling_head, feet_2d.x - scaling, feet_2d.y, color(255, 255, 255, 255));
		render::draw_border_line_horizontal(feet_2d.x - scaling, head_2d.y - scaling_head, feet_2d.x + scaling, head_2d.y - scaling_head, color(255, 255, 255, 255));
		render::draw_border_line_horizontal(feet_2d.x + scaling, feet_2d.y, feet_2d.x - scaling, feet_2d.y, color(255, 255, 255, 255));

		float dur = entity->flash_duration();
		double dp = (dur / 100.f);
		render::draw_filled_rect(head_2d.x + scaling, head_2d.y - 4, abs(scaling * 2), 3, color(0, 0, 0, 255));
		render::draw_filled_rect(head_2d.x + scaling, head_2d.y - 4, abs(scaling * 2) * dp, 3, color(255, 255, 255, 255));
	}
	else if ((entity->is_defusing() || entity->has_gun_game_immunity()) && variables::visuals::box_esp::box_selected.deref(3)) {
		render::draw_border_line_vertical(feet_2d.x + scaling, head_2d.y - scaling_head, feet_2d.x + scaling, feet_2d.y, color(255, 0, 255, 255));
		render::draw_border_line_vertical(feet_2d.x - scaling, head_2d.y - scaling_head, feet_2d.x - scaling, feet_2d.y, color(255, 0, 255, 255));
		render::draw_border_line_horizontal(feet_2d.x - scaling, head_2d.y - scaling_head, feet_2d.x + scaling, head_2d.y - scaling_head, color(255, 0, 255, 255));
		render::draw_border_line_horizontal(feet_2d.x + scaling, feet_2d.y, feet_2d.x - scaling, feet_2d.y, color(255, 0, 255, 255));
	}
	else if (visible) {
		if ((entity->is_scoped() || entity == variables::aimbot_target) && variables::visuals::box_esp::box_selected.deref(3)) {
			render::draw_border_line_vertical(feet_2d.x + scaling, head_2d.y - scaling_head, feet_2d.x + scaling, feet_2d.y, color(100, 100, 100, 255));
			render::draw_border_line_vertical(feet_2d.x - scaling, head_2d.y - scaling_head, feet_2d.x - scaling, feet_2d.y, color(100, 100, 100, 255));
			render::draw_border_line_horizontal(feet_2d.x - scaling, head_2d.y - scaling_head, feet_2d.x + scaling, head_2d.y - scaling_head, color(100, 100, 100, 255));
			render::draw_border_line_horizontal(feet_2d.x + scaling, feet_2d.y, feet_2d.x - scaling, feet_2d.y, color(100, 100, 100, 255));
		}
		else {
			render::draw_border_line_vertical(feet_2d.x + scaling, head_2d.y - scaling_head, feet_2d.x + scaling, feet_2d.y, color(0, 255, 0, 255));
			render::draw_border_line_vertical(feet_2d.x - scaling, head_2d.y - scaling_head, feet_2d.x - scaling, feet_2d.y, color(0, 255, 0, 255));
			render::draw_border_line_horizontal(feet_2d.x - scaling, head_2d.y - scaling_head, feet_2d.x + scaling, head_2d.y - scaling_head, color(0, 255, 0, 255));
			render::draw_border_line_horizontal(feet_2d.x + scaling, feet_2d.y, feet_2d.x - scaling, feet_2d.y, color(0, 255, 0, 255));
		}
	}
	else {
		render::draw_border_line_vertical(feet_2d.x + scaling, head_2d.y - scaling_head, feet_2d.x + scaling, feet_2d.y, color(255, 0, 0, 255));
		render::draw_border_line_vertical(feet_2d.x - scaling, head_2d.y - scaling_head, feet_2d.x - scaling, feet_2d.y, color(255, 0, 0, 255));
		render::draw_border_line_horizontal(feet_2d.x - scaling, head_2d.y - scaling_head, feet_2d.x + scaling, head_2d.y - scaling_head, color(255, 0, 0, 255));
		render::draw_border_line_horizontal(feet_2d.x + scaling, feet_2d.y, feet_2d.x - scaling, feet_2d.y, color(255, 0, 0, 255));
	}
	if (variables::visuals::box_esp::box_selected.deref(2)) {
		char cDistance[5] = "";
		int iDistance = aimbot::sub::distance_to(entity);
		_itoa_s(iDistance, cDistance, 10);
		render::text(head_2d.x - scaling + 4, head_2d.y - scaling_head, render::fonts::watermark_font, cDistance, false, color::white());
	}
	if (variables::visuals::box_esp::box_selected.deref(0)) {
		float health = entity->health();

		double dp = (health / 100.f); int base = abs(scaling * 2);

		render::draw_line(feet_2d.x + scaling - 1, feet_2d.y + 3, feet_2d.x + scaling - 1 + base,feet_2d.y + 3,color::black());
		render::draw_line(feet_2d.x + scaling - 1, feet_2d.y + 7, feet_2d.x + scaling - 1 + base, feet_2d.y + 7, color::black());
		render::draw_line(feet_2d.x + scaling - 1, feet_2d.y + 3, feet_2d.x + scaling - 1, feet_2d.y + 7, color::black());
		render::draw_line(feet_2d.x + scaling + base, feet_2d.y + 3, feet_2d.x + scaling + base, feet_2d.y + 7, color::black());

		render::draw_filled_rect(feet_2d.x + scaling, feet_2d.y + 4, base, 3, color(0, 0, 0, 255));
		render::draw_filled_rect(feet_2d.x + scaling, feet_2d.y + 4, base * dp, 3, color(0, 255, 0, 255));
	}
	if (variables::visuals::box_esp::box_selected.deref(1)) {
		float armor = entity->armor();

		double dp = (armor / 100.f); int base = abs(scaling * 2);

		render::draw_line(feet_2d.x + scaling - 1, feet_2d.y + 7, feet_2d.x + scaling - 1 + base, feet_2d.y + 7, color::black());
		render::draw_line(feet_2d.x + scaling - 1, feet_2d.y + 11, feet_2d.x + scaling - 1 + base, feet_2d.y + 11, color::black());
		render::draw_line(feet_2d.x + scaling - 1, feet_2d.y + 7, feet_2d.x + scaling - 1, feet_2d.y + 11, color::black());
		render::draw_line(feet_2d.x + scaling + base, feet_2d.y + 7, feet_2d.x + scaling + base, feet_2d.y + 11, color::black());

		render::draw_filled_rect(feet_2d.x + scaling, feet_2d.y + 8, base, 3, color(0, 0, 0, 255));
		render::draw_filled_rect(feet_2d.x + scaling, feet_2d.y + 8, base * dp, 3, color(0, 0, 255, 255));
	}
}

void visuals::modules::glow(player_t* entity) {
}
void visuals::modules::skeleton(player_t* entity) {
}

void visuals::modules::ShowTargetInfo() {
	if (!variables::aimbot::TargetInfo || variables::aimbot_target == NULL || !csgo::local_player->is_alive() || variables::aimbot_target->health() < 1) {
		return;
	}
	if (interfaces::entity_list->get_client_entity(variables::aimbot_target->index()) == NULL) {
		return;
	}

	int x, y; interfaces::engine->get_screen_size(x, y); x /= 2; y /= 2;

	vec2_t crosshair; crosshair.x = x; crosshair.y = y;
	vec3_t velocity = variables::aimbot_target->velocity();

	float health = variables::aimbot_target->health();
	float armor = variables::aimbot_target->armor();

	int vel = abs(velocity.x) + abs(velocity.y);

	double dp = (health / 100.f);

	render::draw_filled_rect(crosshair.x - 25, crosshair.y + 25, 50, 3, color(0, 0, 0, 255));
	render::draw_filled_rect(crosshair.x - 25, crosshair.y + 25, 50 * dp, 3, color(0, 255, 0, 255));

	dp = (armor / 100.f);

	render::draw_filled_rect(crosshair.x - 25, crosshair.y + 29, 50, 3, color(0, 0, 0, 255));
	render::draw_filled_rect(crosshair.x - 25, crosshair.y + 29, 50 * dp, 3, color(0, 0, 255, 255));

	dp = (vel / 900.f);

	render::draw_filled_rect(crosshair.x - 25, crosshair.y + 33, 50, 3, color(0, 0, 0, 255));

	if (dp < 1) {
		render::draw_filled_rect(crosshair.x - 25, crosshair.y + 33, 50 * dp, 3, color(255, 255, 255, 255));
	}
	if (variables::aimbot_target->active_weapon() != NULL) {
		float mag_ammo = variables::aimbot_target->active_weapon()->clip1_count();
		float max_ammo = variables::aimbot_target->active_weapon()->get_weapon_data()->weapon_max_clip;

		render::draw_filled_rect(crosshair.x - 25, crosshair.y + 37, 50, 3, color(0, 0, 0, 255));

		if (mag_ammo != 0 && max_ammo != 0) {
			dp = (mag_ammo / max_ammo);
			render::draw_filled_rect(crosshair.x - 25, crosshair.y + 37, 50 * dp, 3, color(255, 215, 0, 255));
		}
	}
}
void visuals::modules::draw_fake_scope() {
	if (!variables::removals_selected.deref(0) || !csgo::local_player->is_scoped()) {
		return;
	}
	int x, y; interfaces::engine->get_screen_size(x, y);

	render::draw_border_line_vertical(x/2, 0, x/2, y, color::gui_hint_2());
	render::draw_border_line_horizontal(0, y/2, x, y/2, color::gui_hint_2());

}
void visuals::modules::draw_hit_marker(i_game_event* event) {
	if (!variables::misc_selected.deref(0) || !(event->get_int("attacker") == csgo::local_player->index())) {
		return;
	}
}