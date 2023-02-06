#include "../../dependencies/utilities/csgo.hpp"
#include "../features/features.hpp"
#include "../features/misc/engine_prediction.hpp"
#include "../menu/menu.hpp"
hooks::create_move::fn create_move_original = nullptr;
hooks::paint_traverse::fn paint_traverse_original = nullptr;
hooks::drawmodel_execute::fn drawmodelexecute_original = nullptr;
bool hooks::initialize() {
	const auto create_move_target = reinterpret_cast<void*>(get_virtual(interfaces::clientmode, 24));
	const auto paint_traverse_target = reinterpret_cast<void*>(get_virtual(interfaces::panel, 41));
	const auto drawmodelexecute_target = reinterpret_cast<void*>(get_virtual(interfaces::model_render, 21));
	if (MH_Initialize() != MH_OK)
		throw std::runtime_error("failed to initialize MH_Initialize.");

	if (MH_CreateHook(create_move_target, &create_move::hook, reinterpret_cast<void**>(&create_move_original)) != MH_OK)
		throw std::runtime_error("failed to initialize create_move. (outdated index?)");

	if (MH_CreateHook(paint_traverse_target, &paint_traverse::hook, reinterpret_cast<void**>(&paint_traverse_original)) != MH_OK)
		throw std::runtime_error("failed to initialize paint_traverse. (outdated index?)");

	if (MH_CreateHook(drawmodelexecute_target, &drawmodel_execute::hook, reinterpret_cast<void**>(&drawmodelexecute_original)) != MH_OK) {
		throw std::runtime_error("failed to initialize drawmodel_execute. (outdated index?)");
	}

	if (MH_EnableHook(MH_ALL_HOOKS) != MH_OK)
		throw std::runtime_error("failed to enable hooks.");

	console::log("[setup] hooks initialized!\n");
	return true;
}

void hooks::release() {
	MH_Uninitialize();

	MH_DisableHook(MH_ALL_HOOKS);
}

bool __stdcall hooks::create_move::hook(float input_sample_frametime, c_usercmd* cmd) {
	csgo::local_player = static_cast<player_t*>(interfaces::entity_list->get_client_entity(interfaces::engine->get_local_player()));
	if (!cmd || !cmd->command_number || csgo::local_player == NULL)
		return false;
	create_move_original(input_sample_frametime, cmd);

	uintptr_t* frame_pointer;
	__asm mov frame_pointer, ebp;
	bool& send_packet = *reinterpret_cast<bool*>(*frame_pointer - 0x1C);

	auto old_viewangles = cmd->viewangles;
	auto old_forwardmove = cmd->forwardmove;
	auto old_sidemove = cmd->sidemove;

	misc::movement::bunny_hop(cmd);
	misc::view::no_flash();
	misc::view::radar_hack();
	aimbot::master::aim_at_target(cmd);

	misc::rcs(cmd);
	variables::saved_punch = csgo::local_player->aim_punch_angle();
	variables::saved_punch2 = csgo::local_player->punch_angle();
	misc::view::fov_changer(); player_t* a;
	//visuals::modules::glow(a);
	misc::view::third_person();
	interfaces::console->get_convar("sv_cheats")->set_value(true);

	//misc::view::test();
	/*
	prediction::start(cmd); {



	} prediction::end();
	*/
	math::correct_movement(old_viewangles, cmd, old_forwardmove, old_sidemove);
	cmd->forwardmove = std::clamp(cmd->forwardmove, -450.0f, 450.0f);
	cmd->sidemove = std::clamp(cmd->sidemove, -450.0f, 450.0f);
	cmd->upmove = std::clamp(cmd->upmove, -320.0f, 320.0f);

	cmd->viewangles.normalize();
	cmd->viewangles.x = std::clamp(cmd->viewangles.x, -89.0f, 89.0f);
	cmd->viewangles.y = std::clamp(cmd->viewangles.y, -180.0f, 180.0f);
	cmd->viewangles.z = 0.0f;
	return false;
}

void __stdcall hooks::paint_traverse::hook(unsigned int panel, bool force_repaint, bool allow_force) {

	auto panel_to_draw = fnv::hash(interfaces::panel->get_panel_name(panel));
	if (variables::removals_selected.deref(0) && !strcmp("HudZoom", interfaces::panel->get_panel_name(panel))) {
		visuals::modules::draw_fake_scope();
		return;
		paint_traverse_original(interfaces::panel, panel, force_repaint, allow_force);
	}
	switch (panel_to_draw) {
	case fnv::hash("MatSystemTopPanel"):

		render::text(2, 2, render::fonts::watermark_font, "africa hook", false, color::red(255));
		visuals::master::VisualsLoop();
		menu::toggle();
		menu::render();
		if (variables::aimbot::fovcheck && csgo::local_player->is_alive()) {
			int x, y; interfaces::engine->get_screen_size(x, y);
			render::draw_circle(x/2, y/2, variables::aimbot::fovcircle, 360, color(255, 255, 255, 255));
			render::draw_circle(x/2, y/2, variables::aimbot::deadzonesize, 360, color(255, 0, 0, 255));
		}
		break;

	case fnv::hash("FocusOverlayPanel"):
		interfaces::panel->set_keyboard_input_enabled(panel, variables::menu::opened);
		interfaces::panel->set_mouse_input_enabled(panel, variables::menu::opened);
		break;
	}

	paint_traverse_original(interfaces::panel, panel, force_repaint, allow_force);
}
void __fastcall hooks::drawmodel_execute::hook(void* ecx, void* edx, i_mat_render_ctx* context, const draw_model_state_t& state, const model_render_info_t& render_info, matrix3x4_t* matrix)
{
	const char* model_name = interfaces::model_info->get_model_name(render_info.model); player_t* entity;
	if (strstr(model_name, "models/player")){
		entity = static_cast<player_t*>(interfaces::entity_list->get_client_entity(render_info.entity_index));
	}
	else {
		entity = nullptr;
	}
	float r, g, b;
	if (strstr(model_name, "models/weapons") && !strstr(model_name, "arms")) {
		if (variables::removals_selected.deref(1)) {
			return;
			drawmodelexecute_original(ecx, context, state, render_info, matrix);
		}
		else if (variables::visuals::cham::weapon) {
			r = variables::weapon_color.x; g = variables::weapon_color.y; b = variables::weapon_color.z;
			visuals::modules::chams(r, g, b, false, visuals::modules::resolve_material(variables::weapons));
			drawmodelexecute_original(ecx, context, state, render_info, matrix);
		}
	}
	if (strstr(model_name, "models/weapons") && strstr(model_name, "arms") && !strstr(model_name, "sleeve")) {
		if (variables::removals_selected.deref(2)) {
			return;
			drawmodelexecute_original(ecx, context, state, render_info, matrix);
		}
		else if (variables::visuals::cham::arms) {
			r = variables::arms_color.x; g = variables::arms_color.y; b = variables::arms_color.z;
			visuals::modules::chams(r, g, b, false, visuals::modules::resolve_material(variables::arms));
			drawmodelexecute_original(ecx, context, state, render_info, matrix);
		}
	}
	if (strstr(model_name, "models/weapons") && strstr(model_name, "arms") && strstr(model_name, "sleeve")) {
		if (variables::removals_selected.deref(3)) {
			return;
			drawmodelexecute_original(ecx, context, state, render_info, matrix);
		}
		else if (variables::visuals::cham::sleeves) {
			r = variables::sleeves_color.x; g = variables::sleeves_color.y; b = variables::sleeves_color.z;
			visuals::modules::chams(r, g, b, false, visuals::modules::resolve_material(variables::sleeves));
			drawmodelexecute_original(ecx, context, state, render_info, matrix);
		}
	}
	if (entity != nullptr) {
		if (variables::visuals::cham::friendly_invis && entity->team() == csgo::local_player->team()) {
			r = variables::friendly_color_invis.x; g = variables::friendly_color_invis.y; b = variables::friendly_color_invis.z;
			visuals::modules::chams(r, g, b, true, visuals::modules::resolve_material(variables::friendly_invis));
			drawmodelexecute_original(ecx, context, state, render_info, matrix);
		}
		if (variables::visuals::cham::enemy_invis && entity->team() != csgo::local_player->team()) {
			r = variables::enemy_color_invis.x; g = variables::enemy_color_invis.y; b = variables::enemy_color_invis.z;
			visuals::modules::chams(r, g, b, true, visuals::modules::resolve_material(variables::enemy_invis));
			drawmodelexecute_original(ecx, context, state, render_info, matrix);
		}
		if (entity->team() == csgo::local_player->team()) {
			if (variables::removals_selected.deref(4)) {
				return;
				drawmodelexecute_original(ecx, context, state, render_info, matrix);
			}
			else if (variables::visuals::cham::friendly) {
				r = variables::friendly_color.x; g = variables::friendly_color.y; b = variables::friendly_color.z;
				visuals::modules::chams(r, g, b, false, visuals::modules::resolve_material(variables::friendly));
				drawmodelexecute_original(ecx, context, state, render_info, matrix);
			}
		}
		if (variables::visuals::cham::enemy&& entity->team() != csgo::local_player->team()) {
			r = variables::enemy_color.x; g = variables::enemy_color.y; b = variables::enemy_color.z;
			visuals::modules::chams(r, g, b, false, visuals::modules::resolve_material(variables::enemy));
			drawmodelexecute_original(ecx, context, state, render_info, matrix);
		}
	}
	drawmodelexecute_original(ecx,context, state, render_info, matrix);
	interfaces::model_render->override_material(nullptr);
}

