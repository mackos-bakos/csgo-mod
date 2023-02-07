#include "menu.hpp"


auto do_frame = [&](std::int32_t x, std::int32_t y, std::int32_t w, std::int32_t h, color bg) {
	render::draw_filled_rect(x, y, w, h, bg);
	render::draw_line(x, y + 9, x, y + h,color::black());
	render::draw_line(x, y + h, x + w - 1, y + h, color::black());
	render::draw_line(x + w - 1, y + h, x + w - 1, y + 9, color::black());
	/*render::draw_filled_rect(x, y, w, 30, header_text);
	render::draw_filled_rect(x, y + 30, w, 2, header_line);
	*/
};

void menu::render() {
	if (!variables::menu::opened)
		return;
	do_frame(variables::menu::x, variables::menu::y, variables::menu::w, variables::menu::h, color(30, 30, 30, 255));
	int tab_length = variables::menu::w / 4;
	menu_framework::tab(variables::menu::x, variables::menu::y, tab_length, render::fonts::watermark_font, "visuals", menu::current_tab, 0);
	menu_framework::tab(variables::menu::x + tab_length, variables::menu::y, tab_length, render::fonts::watermark_font, "aimbot", menu::current_tab, 1);
	menu_framework::tab(variables::menu::x + (tab_length*2), variables::menu::y, tab_length, render::fonts::watermark_font, "misc", menu::current_tab, 2);
	menu_framework::tab(variables::menu::x + (tab_length*3), variables::menu::y, tab_length, render::fonts::watermark_font, "config", menu::current_tab, 3);
	switch (current_tab) {
	case 0:
		menu_framework::check_box(variables::menu::x + 10, variables::menu::y + 20, render::fonts::button_font, "visuals", variables::bVisuals);
		if (variables::bVisuals) {
			//chams
			menu_framework::slider(variables::menu::x + 230, variables::menu::y + 20,120, render::fonts::button_font, "", variables::visuals::cham::blue, 0, 255);

			menu_framework::check_box(variables::menu::x + 230, variables::menu::y + 40, render::fonts::button_font, "weapons", variables::visuals::cham::weapon);
			menu_framework::check_box(variables::menu::x + 230, variables::menu::y + 60, render::fonts::button_font, "hands", variables::visuals::cham::arms);
			menu_framework::check_box(variables::menu::x + 230, variables::menu::y + 80, render::fonts::button_font, "sleeves", variables::visuals::cham::sleeves);
			menu_framework::check_box(variables::menu::x + 230, variables::menu::y + 100, render::fonts::button_font, "vis friend", variables::visuals::cham::friendly);
			menu_framework::check_box(variables::menu::x + 230, variables::menu::y + 120, render::fonts::button_font, "ivis friend", variables::visuals::cham::friendly_invis);
			menu_framework::check_box(variables::menu::x + 230, variables::menu::y + 140, render::fonts::button_font, "vis enemy", variables::visuals::cham::enemy);
			menu_framework::check_box(variables::menu::x + 230, variables::menu::y + 160, render::fonts::button_font, "ivis enemy", variables::visuals::cham::enemy_invis);
			menu_framework::check_box(variables::menu::x + 230, variables::menu::y + 180, render::fonts::button_font, "extend", variables::visuals::cham::extend_chams);

			menu_framework::selection_interface(variables::menu::x + 300, variables::menu::y + 40, variables::materials_selections, variables::weapons, variables::weapons_opened);
			menu_framework::selection_interface(variables::menu::x + 300, variables::menu::y + 60, variables::materials_selections, variables::arms, variables::arms_opened);
			menu_framework::selection_interface(variables::menu::x + 300, variables::menu::y + 80, variables::materials_selections, variables::sleeves, variables::sleeves_opened);
			menu_framework::selection_interface(variables::menu::x + 300, variables::menu::y + 100, variables::materials_selections, variables::friendly, variables::friendly_opened);
			menu_framework::selection_interface(variables::menu::x + 300, variables::menu::y + 120, variables::materials_selections, variables::friendly_invis, variables::friendly_opened_invis);
			menu_framework::selection_interface(variables::menu::x + 300, variables::menu::y + 140, variables::materials_selections, variables::enemy, variables::enemy_opened);
			menu_framework::selection_interface(variables::menu::x + 300, variables::menu::y + 160, variables::materials_selections, variables::enemy_invis, variables::enemy_opened_invis);

			menu_framework::color_selection(variables::menu::x + 200, variables::menu::y + 40, variables::weapon_color, variables::weapon_color_bool);
			menu_framework::color_selection(variables::menu::x + 200, variables::menu::y + 60, variables::arms_color, variables::arms_color_bool);
			menu_framework::color_selection(variables::menu::x + 200, variables::menu::y + 80, variables::sleeves_color, variables::sleeves_color_bool);
			menu_framework::color_selection(variables::menu::x + 200, variables::menu::y + 100, variables::friendly_color, variables::friendly_color_bool);
			menu_framework::color_selection(variables::menu::x + 200, variables::menu::y + 120, variables::friendly_color_invis, variables::friendly_color_bool_invis);
			menu_framework::color_selection(variables::menu::x + 200, variables::menu::y + 140, variables::enemy_color, variables::enemy_color_bool);
			menu_framework::color_selection(variables::menu::x + 200, variables::menu::y + 160, variables::enemy_color_invis, variables::enemy_color_bool_invis);

			//misc
			menu_framework::check_box(variables::menu::x + 10, variables::menu::y + 330, render::fonts::button_font, "tracers", variables::visuals::tracers);
			menu_framework::check_box(variables::menu::x + 10, variables::menu::y + 350, render::fonts::button_font, "box", variables::visuals::box);

			menu_framework::selection_interface(variables::menu::x + 75, variables::menu::y + 330, variables::tracer_origin_selections, variables::tracer_origin, variables::tracer_origin_selections_opened);

			menu_framework::selection_interface_2(variables::menu::x + 75, variables::menu::y + 350, variables::visuals::box_esp::box_selections, variables::visuals::box_esp::box_selected, variables::visuals::box_esp::box_selections_opened);
		}
		break;
	case 1:
		menu_framework::check_box(variables::menu::x + 10, variables::menu::y + 20, render::fonts::button_font, "aimbot", variables::bAimbot);
		if (variables::bAimbot) {
			menu_framework::selection_interface(variables::menu::x + 10, variables::menu::y + 90, variables::aim_type_selections, variables::aim_type, variables::aim_type_selections_opened);
			menu_framework::selection_interface(variables::menu::x + 10, variables::menu::y + 110, variables::aim_priority_selections, variables::aim_priority, variables::aim_priority_selections_opened);

			menu_framework::check_box(variables::menu::x + 10, variables::menu::y + 35, render::fonts::button_font, "rcs", variables::aimbot::rcs);
			menu_framework::check_box(variables::menu::x + 10, variables::menu::y + 50, render::fonts::button_font, "sticky", variables::aimbot::sticky);
			menu_framework::check_box(variables::menu::x + 10, variables::menu::y + 65, render::fonts::button_font, "remove punch", variables::aimbot::remove_punch);

			menu_framework::check_box(variables::menu::x + 10, variables::menu::y + 135, render::fonts::button_font, "draw fov", variables::aimbot::drawfov);
			menu_framework::check_box(variables::menu::x + 10, variables::menu::y + 155, render::fonts::button_font, "draw deadzone", variables::aimbot::drawdeadzone);

			// fov,rand,smoothing and deadzone
			menu_framework::check_box(variables::menu::x + 250, variables::menu::y + 30, render::fonts::button_font, "smoothing", variables::aimbot::smooth);
			menu_framework::check_box(variables::menu::x + 250, variables::menu::y + 50, render::fonts::button_font, "randomisation", variables::aimbot::random);
			menu_framework::check_box(variables::menu::x + 250, variables::menu::y + 70, render::fonts::button_font, "fov", variables::aimbot::fovcheck);
			menu_framework::check_box(variables::menu::x + 250, variables::menu::y + 90, render::fonts::button_font, "deadzone", variables::aimbot::deadzone);
			menu_framework::check_box(variables::menu::x + 250, variables::menu::y + 110, render::fonts::button_font, "dz ex delay", variables::aimbot::dead_zone_delay);

			menu_framework::slider(variables::menu::x + 330, variables::menu::y + 30, 125, render::fonts::button_font, "smoothing", variables::aimbot::smoothing, 0, 100);
			menu_framework::slider(variables::menu::x + 330, variables::menu::y + 50, 125, render::fonts::button_font, "randomis", variables::aimbot::randomisation, 0, 9);
			menu_framework::slider(variables::menu::x + 330, variables::menu::y + 70, 125, render::fonts::button_font, "aim fov", variables::aimbot::fov_circle, 1, 300);
			menu_framework::slider(variables::menu::x + 330, variables::menu::y + 90, 125, render::fonts::button_font, "aim deadzone", variables::aimbot::dead_zone_size, 1, variables::aimbot::fov_circle * 0.6f);
			menu_framework::slider(variables::menu::x + 330, variables::menu::y + 110, 125, render::fonts::button_font, "dz delay", variables::aimbot::dead_zone_delay_time, 0, 1);
			// activations
			menu_framework::check_box(variables::menu::x + 10, variables::menu::y + 350, render::fonts::button_font, "activations", variables::aimbot::b1);
			menu_framework::check_box(variables::menu::x + 10, variables::menu::y + 370, render::fonts::button_font, "deactivations", variables::aimbot::b2);
			
			menu_framework::selection_interface_2(variables::menu::x + 90, variables::menu::y + 350, variables::aimbot_active_selections, variables::aimbot_active_selected, variables::aimbot_active_opened);
			menu_framework::selection_interface_2(variables::menu::x + 90, variables::menu::y + 370, variables::aimbot_trigs_selections, variables::aimbot_trigs_selected, variables::aimbot_trigs_opened);
			// auto shoot and autoscope with team and vis check to the right along with transp and target info
			menu_framework::check_box(variables::menu::x + 10, variables::menu::y + 240, render::fonts::button_font, "auto shoot", variables::aimbot::autoshoot);
			menu_framework::check_box(variables::menu::x + 10, variables::menu::y + 260, render::fonts::button_font, "auto scope", variables::aimbot::autoscope);
			menu_framework::check_box(variables::menu::x + 10, variables::menu::y + 280, render::fonts::button_font, "show target info", variables::aimbot::TargetInfo);
			menu_framework::check_box(variables::menu::x + 100, variables::menu::y + 240, render::fonts::button_font, "team check", variables::aimbot::teamcheck);
			menu_framework::check_box(variables::menu::x + 100, variables::menu::y + 260, render::fonts::button_font, "visible check", variables::aimbot::vischeck);
			menu_framework::check_box(variables::menu::x + 100, variables::menu::y + 280, render::fonts::button_font, "transparent check", variables::aimbot::transpcheck);
		}

		break;
	case 2:
		// no flash and bhop,no recoil
		menu_framework::check_box(variables::menu::x + 10, variables::menu::y + 225, render::fonts::button_font, "no flash", variables::bNoFlash);
		menu_framework::check_box(variables::menu::x + 10, variables::menu::y + 245, render::fonts::button_font, "bhop", variables::bBhop);
		menu_framework::check_box(variables::menu::x + 10, variables::menu::y + 265, render::fonts::button_font, "no recoil", variables::bRcs);

		menu_framework::selection_interface(variables::menu::x + 90, variables::menu::y + 225, variables::bhop_selections, variables::bhop, variables::bhop_selections_opened);
		menu_framework::selection_interface(variables::menu::x + 90, variables::menu::y + 245, variables::no_flash_selections, variables::no_flash, variables::no_flash_selections_opened);
		menu_framework::selection_interface(variables::menu::x + 90, variables::menu::y + 265, variables::rcs_selections, variables::rcs_s, variables::rcs_opened);
		// radar and thirdperson
		menu_framework::check_box(variables::menu::x + 10, variables::menu::y + 20, render::fonts::button_font, "radar", variables::bRadar);
		menu_framework::check_box(variables::menu::x + 10, variables::menu::y + 40, render::fonts::button_font, "third person", variables::bTPS);
		//fov
		menu_framework::check_box(variables::menu::x + 10, variables::menu::y + 175, render::fonts::button_font, "fov", variables::bFov);

		menu_framework::slider(variables::menu::x + 50, variables::menu::y + 175, 125, render::fonts::button_font, "fov", variables::fov, 30, 160);
		//general
		menu_framework::selection_interface_2(variables::menu::x + 350, variables::menu::y + 20, variables::removals_selections, variables::removals_selected, variables::removals_opened);
		menu_framework::selection_interface_2(variables::menu::x + 350, variables::menu::y + 40, variables::misc_selections, variables::misc_selected, variables::misc_opened);
		break;
	case 3:
		//menu_framework::color_selection(variables::menu::x + 60, variables::menu::x + 80, variables::test_col, variables::test_bool);
		//menu_framework::selection_interface(variables::menu::x + 10, variables::menu::x + 50, variables::aim_type_selections, variables::aim_type, variables::aim_type_selections_opened);
		break;
	}
	if (variables::aim_type == 1 && variables::aimbot::smooth) {
		variables::aim_type == 0;
	}
	if (variables::aimbot::smooth && variables::aim_priority == 1) {
		variables::aimbot::sticky = true;
	}
	//menu_framework::menu_movement(variables::menu::x, variables::menu::y, variables::menu::w, variables::menu::h + 100);
}

void menu::toggle() {
	if (GetAsyncKeyState(VK_INSERT) & 1)
		variables::menu::opened = !variables::menu::opened;
}
