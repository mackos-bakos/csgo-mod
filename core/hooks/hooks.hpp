#pragma once

namespace hooks {
	bool initialize();
	void release();

	inline unsigned int get_virtual(void* _class, unsigned int index) { return static_cast<unsigned int>((*static_cast<int**>(_class))[index]); }

	namespace create_move {
		using fn = bool(__stdcall*)(float, c_usercmd*);
		bool __stdcall hook(float input_sample_frametime, c_usercmd* cmd);
	};

	namespace paint_traverse {
		using fn = void(__thiscall*)(i_panel*, unsigned int, bool, bool);
		void __stdcall hook(unsigned int panel, bool force_repaint, bool allow_force);
	}

	namespace drawmodel_execute {
		using fn = void(__thiscall*)(void*,i_mat_render_ctx*, const draw_model_state_t&, const model_render_info_t&, matrix3x4_t*);
		void __fastcall hook(void* ecx, void* edx, i_mat_render_ctx* context, const draw_model_state_t& state, const model_render_info_t& render_info, matrix3x4_t* matrix);
	}
}
