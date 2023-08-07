#include "state-manager.hpp"

void StateManager::begin()
{
	_header.begin();

	_current_state = &_note_state;

	_current_state->begin();
}

void StateManager::update()
{
	_header.update();

	_current_state->update();
}

void StateManager::on_button_a_pressed()
{
	_current_state->on_button_a_pressed();
}

void StateManager::on_button_b_pressed()
{
	_current_state->on_button_b_pressed();
}

void StateManager::on_button_c_pressed()
{
	_current_state->on_button_c_pressed();
}

void StateManager::on_key_pressed(const uint8_t keycode)
{
	_current_state->on_key_pressed(keycode);
}