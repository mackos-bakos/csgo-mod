#include "framework.hpp"

POINT cursor;
POINT cursor_corrected;

void menu_framework::group_box(std::int32_t x, std::int32_t y, std::int32_t w, std::int32_t h, unsigned long font, const std::string string, bool show_label) {
	//groupbox background
	render::draw_filled_rect(x, y, w, h, color(25, 25, 25, 255));

	//groupbox outline
	render::draw_rect(x, y, w, h, color(45, 45, 45, 255));

	//groupbox label
	if (show_label)
		render::text(x + 2, y - 12, font, string, false, color::gui_text_2());
}

void menu_framework::tab(std::int32_t x, std::int32_t y, std::int32_t w, unsigned long font, const std::string string, std::int32_t& tab, std::int32_t count) {
	GetCursorPos(&cursor); ScreenToClient(GetForegroundWindow(), &cursor);

	if ((cursor.x > x) && (cursor.x < x + w) && (cursor.y > y) && (cursor.y < y + 10) && (GetAsyncKeyState(VK_LBUTTON) & 1))
		tab = count;
	if (tab == count) {
		render::draw_filled_rect(x, y, w, 10, color::gui_hint_1());
	}
	else {
		render::draw_filled_rect(x, y, w, 10, color::gui_hint_4());
	}
	render::text(x + (w / 2), y - 2, font, string, true, color::gui_text_2());
}

void menu_framework::check_box(std::int32_t x, std::int32_t y, unsigned long font, const std::string string, bool& value) {

	GetCursorPos(&cursor); ScreenToClient(GetForegroundWindow(), &cursor);

	render::draw_filled_rect(x, y, 8, 8, color::gui_hint_4());
	if (value) {
		render::draw_filled_rect(x + 2, y + 2, 4, 4, color::gui_hint_1());
	}
	if ((cursor.x > x) && (cursor.x < x + 8) && (cursor.y > y) && (cursor.y < y + 8)) {
		if (GetAsyncKeyState(VK_LBUTTON) & 1) {
			value = !value;
		}
		if (value) {
			render::draw_filled_rect(x + 2, y + 2, 4, 4, color::gui_hint_3());
		}
		else {
			render::draw_filled_rect(x + 2, y + 2, 4, 4, color::gui_hint_2());
		}
	}


	render::text(x + 13, y - 3, font, string, false, color::gui_text_1());
}

void menu_framework::slider(std::int32_t x, std::int32_t y, std::int32_t position, unsigned long font, const std::string string, float& value, std::int32_t min_value, std::int32_t max_value) {
	GetCursorPos(&cursor); ScreenToClient(GetForegroundWindow(), &cursor);
	if ((cursor.x > x) && (cursor.x < x + position) && (cursor.y > y) && (cursor.y < y + 6) && (GetAsyncKeyState(VK_LBUTTON)))
		value = (cursor.x - x) / (float(position) / float(max_value));
	if (value > max_value) {
		value = max_value;
	}
	if (value < min_value) {
		value = min_value;
	}
	//slider background
	render::draw_filled_rect(x, y, position, 8, color::gui_hint_4());
	render::draw_filled_rect(x, y, value * (float(position) / float(max_value)), 8, color::gui_hint_1());
	std::string display = std::to_string(value);
	render::text(x + position + 5, y - 3, font, display,false,color::white());
}

void menu_framework::menu_movement(std::int32_t& x, std::int32_t& y, std::int32_t w, std::int32_t h) {
	GetCursorPos(&cursor); ScreenToClient(GetForegroundWindow(), &cursor);

	if (GetAsyncKeyState(VK_LBUTTON) < 0 && (cursor.x > x && cursor.x < x + w && cursor.y > y && cursor.y < y + h)) {
		should_drag = true;

		if (!should_move) {
			cursor_corrected.x = cursor.x - x;
			cursor_corrected.y = cursor.y - y;
			should_move = true;
		}
	}

	if (should_drag) {
		x = cursor.x - cursor_corrected.x;
		y = cursor.y - cursor_corrected.y;
	}

	if (GetAsyncKeyState(VK_LBUTTON) == 0) {
		should_drag = false;
		should_move = false;
	}
}
void menu_framework::selection_interface(std::int32_t x, std::int32_t y, selections selections, std::int32_t& current, bool& opened) {
	GetCursorPos(&cursor); ScreenToClient(GetForegroundWindow(), &cursor);
	if (opened) {
		render::draw_filled_rect(x, y, 50, 10, color::gui_hint_4());
		render::text(x + 25, y - 2, render::fonts::watermark_font, "--->", true, color::gui_text_2());
		for (short int pointer = 0; pointer < 6; pointer++) {
			if (!selections.valid(selections.deref(pointer))) {
				continue;
			}
			if ((cursor.x > x) && (cursor.x < x + 50) && (cursor.y > y) && (cursor.y < y + 10) && (GetAsyncKeyState(VK_LBUTTON) & 1)) {
				opened = !opened;
			}
			if ((cursor.x > x + 50 + pointer * 50) && (cursor.x < x + 100 + pointer * 50) && (cursor.y > y) && (cursor.y < y + 10) && (GetAsyncKeyState(VK_LBUTTON) & 1)) {
				current = pointer;
				opened = !opened;
			}
			render::draw_filled_rect(x + 50 + pointer * 50, y, 50, 10, color::gui_hint_4());
			render::text(x + 75 + pointer * 50, y - 2, render::fonts::watermark_font, selections.deref(pointer), true, color::gui_text_2());
		}
	}
	else {
		render::draw_filled_rect(x, y, 50, 10, color::gui_hint_4());
		render::text(x + 25, y - 2, render::fonts::watermark_font, selections.deref(current), true, color::gui_text_2());
		if ((cursor.x > x) && (cursor.x < x + 50) && (cursor.y > y) && (cursor.y < y + 10) && (GetAsyncKeyState(VK_LBUTTON) & 1)) {
			opened = !opened;
		}
	}
}
void menu_framework::selection_interface_2(std::int32_t x, std::int32_t y, selections selections, selected& current, bool& opened) {
	GetCursorPos(&cursor); ScreenToClient(GetForegroundWindow(), &cursor);
	if (opened) {
		render::draw_filled_rect(x, y, 50, 10, color::gui_hint_4());
		render::text(x + 25, y - 2, render::fonts::watermark_font, "-->", true, color::gui_text_2());
		for (short int pointer = 0; pointer < 6; pointer++) {
			if (!selections.valid(selections.deref(pointer))) {
				continue;
			}
			if ((cursor.x > x) && (cursor.x < x + 50) && (cursor.y > y) && (cursor.y < y + 10) && (GetAsyncKeyState(VK_LBUTTON) & 1)) {
				opened = !opened;
			}
			if ((cursor.x > x + 50 + pointer * 50) && (cursor.x < x + 100 + pointer * 50) && (cursor.y > y) && (cursor.y < y + 10) && (GetAsyncKeyState(VK_LBUTTON) & 1)) {
				current.select(pointer);
			}
			if (current.deref(pointer)) {
				render::draw_filled_rect(x + 50 + pointer * 50, y, 50, 10, color::gui_hint_3());
			}
			else {
				render::draw_filled_rect(x + 50 + pointer * 50, y, 50, 10, color::gui_hint_4());
			}
			render::text(x + 75 + pointer * 50, y - 2, render::fonts::watermark_font, selections.deref(pointer), true, color::gui_text_2());
		}
	}
	else {
		render::draw_filled_rect(x, y, 50, 10, color::gui_hint_4());
		render::text(x + 25, y - 2, render::fonts::watermark_font, "---", true, color::gui_text_2());
		if ((cursor.x > x) && (cursor.x < x + 50) && (cursor.y > y) && (cursor.y < y + 10) && (GetAsyncKeyState(VK_LBUTTON) & 1)) {
			opened = !opened;
		}
	}
}
void menu_framework::color_selection(std::int32_t x, std::int32_t y, vec3_t& col, bool& opened) {
	GetCursorPos(&cursor); ScreenToClient(GetForegroundWindow(), &cursor);
	if(opened) {
		//render::draw_filled_rect(x, y, 60, 60, color::gui_hint_4()); //foreground
		for (int red = 0; red < 50; red ++) {
			for (int green = 0.f; green < 50; green ++) {
				render::draw_filled_rect(x + red + 5,y + green + 5, 1, 1, color(red * 5, green * 5, 255 - ((green * 2.5f) + (red * 2.5f)), 255));
			}
		}
		if ((cursor.x > x + 5) && (cursor.x < x + 55) && (cursor.y > y + 5) && (cursor.y < y + 55) && (GetAsyncKeyState(VK_LBUTTON) & 1)) {
			float c2s_x, c2s_y; c2s_x = cursor.x - (x + 5); c2s_y = cursor.y - (y + 5);
			float red = ((c2s_x * 5.f) / 255.f);
			float green = ((c2s_y * 5.f) / 255.f);
			float blue = ((255.f - ((c2s_x * 2.5f) + (c2s_y * 2.5))) / 255.f);
			col = {red,green,blue};
			opened = !opened;
		}
	}
	else {
		render::draw_filled_rect(x, y, 5, 5, color(col.x * 255.f, col.y * 255.f, col.z * 255.f, 255));
		if ((cursor.x > x) && (cursor.x < x + 5) && (cursor.y > y) && (cursor.y < y + 5) && (GetAsyncKeyState(VK_LBUTTON) & 1)) {
			opened = !opened;
		}
	}
	//render::draw_filled_rect(x, y, 5, 5, color(col.x * 255.f, col.y * 255.f, col.z * 255.f, 255));
}
void menu_framework::view_angles_to_screen(vec2_t view_angles, vec2_t& angle) {
	//Convert angles to radians
	float pitch = view_angles.x;
	float yaw = view_angles.y;
	yaw = yaw * (3.141592653589793 / 180.0);
	pitch = pitch * (3.141592653589793 / 180.0);

	//Calculate x and y coordinates
	angle.x = cos(yaw) * cos(pitch);
	angle.y = sin(yaw) * cos(pitch);

	//Scale down x and y to fit the screen
	angle.x = angle.x * 0.5 + 0.5;
	angle.y = angle.y * 0.5 + 0.5;
}