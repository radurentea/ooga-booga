
int entry(int argc, char **argv) {
	
	// This is how we (optionally) configure the window.
	// You can set this at any point in the runtime and it will
	// be applied in os_update().
	// If you don't care, you can ignore all of this as it all
	// has reasonable default values.
	window.title = STR("Radu's Game");
	window.scaled_width = 1280; // We need to set the scaled size if we want to handle system scaling (DPI)
	window.scaled_height = 720; 
	window.x = 200;
	window.y = 90;
	window.clear_color = hex_to_rgba(0x6495EDff);
	window.allow_resize = true;
	window.fullscreen = false;
	
	float64 last_time = os_get_elapsed_seconds();
	while (!window.should_close) {
		if (is_key_just_pressed(KEY_ESCAPE)) {
			window.should_close = true;
		}

		reset_temporary_storage();
		
		float64 now = os_get_elapsed_seconds();
		if ((int)now != (int)last_time) log("%.2f FPS\n%.2fms", 1.0/(now-last_time), (now-last_time)*1000);
		last_time = now;
		
		Matrix4 rect_xform = m4_scalar(1.0);
		rect_xform         = m4_rotate_z(rect_xform, (f32)now);
		rect_xform         = m4_translate(rect_xform, v3(-.25f, -.25f, 0));
		draw_rect_xform(rect_xform, v2(.5f, .5f), COLOR_GREEN);
		
		draw_rect(v2(sin(now), -.8), v2(.5, .25), COLOR_RED);
		
		float aspect = (f32)window.width/(f32)window.height;
		float mx = (input_frame.mouse_x/(f32)window.width  * 2.0 - 1.0)*aspect;
		float my = input_frame.mouse_y/(f32)window.height * 2.0 - 1.0;
		
		draw_line(v2(-.75, -.75), v2(mx, my), 0.005, COLOR_WHITE);
		
		if (is_key_just_pressed('F')) {
			window.fullscreen = !window.fullscreen;
		}
		
		os_update(); 
		gfx_update();
	}

	return 0;
}