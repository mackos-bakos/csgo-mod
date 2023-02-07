#pragma once
#include "../../dependencies/utilities/csgo.hpp"
#include "variables.hpp"
namespace menu_framework {

	void group_box(std::int32_t x, std::int32_t y, std::int32_t w, std::int32_t h, unsigned long font, const std::string string, bool show_label);
	void tab(std::int32_t x, std::int32_t y, std::int32_t w, unsigned long font, const std::string string, std::int32_t& tab, std::int32_t count);
	void check_box(std::int32_t x, std::int32_t y, unsigned long font, const std::string string, bool& value);
	void slider(std::int32_t x, std::int32_t y, std::int32_t position, unsigned long font, const std::string string, float& value, std::int32_t min_value, std::int32_t max_value);
	void menu_movement(std::int32_t& x, std::int32_t& y, std::int32_t w, std::int32_t h);
	void selection_interface(std::int32_t x, std::int32_t y, selections selections, std::int32_t& current,bool& opened);
	void selection_interface_2(std::int32_t x, std::int32_t y, selections selections, selected& selected, bool& opened);
	void color_selection(std::int32_t x, std::int32_t y, vec3_t& col, bool& opened);
	void view_angles_to_screen(vec2_t view_angles,vec2_t &angle);

	inline bool should_drag = false;
	inline bool should_move = false;
};