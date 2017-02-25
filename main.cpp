/*
*The complete working code needed for Part 1:
* This code allows the ARM board to function as a metronome,
* logging beats at the push of a button and playing them on changing
* modes. The board must log at least 4 beats in ordr to function properly
* (a constant green light indicates that required no of beats are not logged)
*This part of the project doesn't require Internet connection
*/
#include "mbed.h"
#include "utils.hpp"

#include "EthernetInterface.h"
#include "frdm_client.hpp"

#include "metronome.hpp"
#include "log.hpp"

//NOTE: Uncomment the below #define for Part 2
//#define IOT_ENABLED


namespace active_low
{
	const bool on = false;
	const bool off = true;
}

DigitalOut g_led_red(LED1);
DigitalOut g_led_green(LED2);
DigitalOut g_led_blue(LED3);

InterruptIn g_button_mode(SW3);
InterruptIn g_button_tap(SW2);
Ticker flipper;

bool mode_changed = 0;
bool tapped = 0;
bool play = 0;
float beat = 0;

//Change mode from learn to play and vice-versa
void on_mode()
{
	mode_changed = 1;
}

//log beats during learn mode
void on_tap()
{

	tapped = 1;

}

//Play learned beats during play mode
void flip()
{
	g_led_green = active_low::on;
	wait(0.1f);
	g_led_green = active_low::off;
}

int main()
{
	// Seed the RNG for networking purposes
	unsigned seed = utils::entropy_seed();
	srand(seed);

	// LEDs are active LOW - true/1 means off, false/0 means on
	// Use the constants for easier reading

	//Log a message on the terminal
	//pc.printf("Initialize metronome app");
	log_on_terminal("Initializing metronome app.....\n");


	// Button falling edge is on push (rising is on release)
	g_button_mode.fall(&on_mode);
	g_button_tap.fall(&on_tap);

	// Needed for part 2 - ignore for now
#ifdef IOT_ENABLED
	// Turn on the blue LED until connected to the network
	g_led_blue = active_low::off;

	// Need to be connected with Ethernet cable for success
	EthernetInterface ethernet;
	if (ethernet.connect() != 0)
		return 1;

	// Pair with the device connector
	frdm_client client("coap://api.connector.mbed.com:5684", &ethernet);
	if (client.get_state() == frdm_client::state::error)
		return 1;

	// The REST endpoints for this device
	// Add your own M2MObjects to this list with push_back before client.connect()
	M2MObjectList objects;

	M2MDevice* device = frdm_client::make_device();
	objects.push_back(device);

	// Publish the RESTful endpoints
	client.connect(objects);

	// Connect complete; turn off blue LED forever
	g_led_blue = active_low::on;
#endif

	g_led_blue = active_low::off;
	g_led_red = active_low::off;
	g_led_green = active_low::off;

	metronome m = metronome();
	log_on_terminal("Initializing metronome app.....\n");
	m.start_timing();
	while (true) {
#ifdef IOT_ENABLED
		if (client.get_state() == frdm_client::state::error)
			break;
#endif

		// Insert any code that must be run continuously here
		if (mode_changed) {
			mode_changed = 0;
			if (!m.is_timing()) { // play mode - switch to learn mode
				flipper.detach();
				m.start_timing();

			}
			else {          // learn mode - switch to play mode
				m.stop_timing();
				beat = m.get_beat();
				flipper.attach(&flip, beat);

			}

		}


		if (tapped) {
			m.tap();
			tapped = 0;

			if (m.is_timing()) {
				g_led_red = active_low::on;
				wait(0.1f);
				g_led_red = active_low::off;
			}

		}
	}

#ifdef IOT_ENABLED
	client.disconnect();
#endif

	return 1;
}
