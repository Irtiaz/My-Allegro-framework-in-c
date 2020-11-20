#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include "sketch.h"


//Fix the FPS here
#define FPS 60.0

ALLEGRO_DISPLAY *display;
ALLEGRO_EVENT_QUEUE *queue;
ALLEGRO_TIMER *timer;



int main(int argc, char **argv) {
	al_init();
	display = al_create_display(width, height);
	queue = al_create_event_queue();
	timer = al_create_timer(1.0 / FPS);

	al_install_mouse();
	al_install_keyboard();


	al_register_event_source(queue, al_get_display_event_source(display));
	al_register_event_source(queue, al_get_timer_event_source(timer));
	al_register_event_source(queue, al_get_mouse_event_source());
	al_register_event_source(queue, al_get_keyboard_event_source());

	//Initialize addons
	al_init_primitives_addon();
	al_init_font_addon();
	al_init_ttf_addon();

	//User defined function
	setup();

	al_start_timer(timer);

	bool runFrame = true;
	while (runFrame) {
		bool redraw = false;
		
		while (!al_is_event_queue_empty(queue)) {
			ALLEGRO_EVENT event;
			al_wait_for_event(queue, &event);

			switch (event.type) {
				case ALLEGRO_EVENT_DISPLAY_CLOSE :
					runFrame = false;
					break;

				case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN :
					mousePressed(event);
					break;

				
				case ALLEGRO_EVENT_KEY_DOWN :
					keyPressed(event.keyboard.keycode);
					break;

				case ALLEGRO_EVENT_MOUSE_AXES :
					mouseX = event.mouse.x;
					mouseY = event.mouse.y;
					break;
				
				case ALLEGRO_EVENT_TIMER :
					redraw = true;
					break;
			}
		}
		
		if (redraw == true) {
			//User defined function
			draw();

			al_flip_display();
		}
	}

	al_uninstall_mouse();
	al_uninstall_keyboard();
	al_destroy_display(display);
	al_destroy_event_queue(queue);
	al_destroy_timer(timer);

	return 0;
}