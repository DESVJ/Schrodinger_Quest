#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "Console.h"
#include "j1Player.h"
#include "j1Gui.h"
#include "EntityManager.h"
#include "j1Input.h"
#include "j1Scene.h"

Console::Console() {
	name.create("console");
	console_active = false;
}


bool Console::Awake(pugi::xml_node& node) {
	background_pos = { node.child("background").attribute("position_x").as_int(),node.child("background").attribute("position_y").as_int(),node.child("background").attribute("position_w").as_int(),
	node.child("background").attribute("position_h").as_int() };
	background_red = node.child("background").attribute("red").as_int();
	background_green = node.child("background").attribute("green").as_int();
	background_blue = node.child("background").attribute("blue").as_int();
	background_alpha = node.child("background").attribute("alpha").as_int();

	input_pos = { node.child("input").attribute("position_x").as_int(),node.child("input").attribute("position_y").as_int(),node.child("input").attribute("position_w").as_int(),
	node.child("input").attribute("position_h").as_int() };
	input_red = node.child("input").attribute("red").as_int();
	input_green = node.child("input").attribute("green").as_int();
	input_blue = node.child("input").attribute("blue").as_int();
	input_alpha = node.child("input").attribute("alpha").as_int();

	output_pos = { node.child("output").attribute("position_x").as_int(),node.child("output").attribute("position_y").as_int(),node.child("output").attribute("position_w").as_int(),
	node.child("output").attribute("position_h").as_int() };
	output_drag_area = { node.child("output").attribute("d_area_x").as_int(),node.child("output").attribute("d_area_y").as_int(),node.child("output").attribute("d_area_w").as_int(),
	node.child("output").attribute("d_area_h").as_int() };

	label = "";
	return true;
}

bool Console::PreUpdate() {
	if (App->input->GetKey(SDL_SCANCODE_GRAVE) == KEY_DOWN) 
	{
		console_active = !console_active;
		if (console_active == true) {
			ActivateConsole();
		}
		else {
			App->gui->DeleteUIElement(console_log);
			App->gui->DeleteUIElement(console_background);
			App->gui->DeleteUIElement(console_input);
		}
	}
	if (console_active == true) {
		console_input->focus = true;
		if (App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN) {
			p2SString argument=CheckCommand();
			ExecuteCommand(argument);
			console_input->SetLabel("");
			console_input->SetPositionToZero();
		}
		label = console_input->GetLabel();
		for (int i = console_log->GetNumberOfStrings(); i < App->num_logs; i++)
			console_log->SetListOfStrings(App->logs.At(i)->data.GetString(), i);
	}
	return true;
}

void Console::ActivateConsole() {
	console_background = (ImageUI*)App->gui->CreateUIElement(Type::IMAGE, nullptr, background_pos, "", background_red, background_green, background_blue, background_alpha);
	console_log = (ListTextsUI*)App->gui->CreateUIElement(Type::LISTTEXTS, console_background, output_pos, { 0,0,0,0 }, App->logs.At(0)->data.GetString(), { 0,0,0,0 }, { 0,0,0,0 }, true,
		output_drag_area, nullptr, true);
	console_input = (TextInputUI*)App->gui->CreateUIElement(Type::INPUT, nullptr, input_pos, "", input_red, input_green, input_blue, input_alpha);
	console_input->SetLabel(label.GetString());
}

p2SString Console::CheckCommand() {
	p2SString argument = "";
	const char* command_text = console_input->GetLabel().GetString();
	if (!strcmp(command_text, "list"))
		command = commands::list;
	else if (!strcmp(command_text, "god_mode") || !strcmp(command_text, "god mode") || !strcmp(command_text, "godmode"))
		command = commands::god_mode;
	else if (!strcmp(command_text, "quit"))
		command = commands::quit;
	else if (!strcmp(command_text, "FPS") || !strcmp(command_text, "Fps") || !strcmp(command_text, "fps"))
		command = commands::FPS;
	else if (!strcmp(command_text, "map"))
		command = commands::map;
	else {
		p2SString three_letters_command = argument = console_input->GetLabel();
		int num_of_letters = three_letters_command.Length();
		for (int i = 3; i < num_of_letters; i++) {
			three_letters_command= three_letters_command.Supr(3);
		}
		for (int i = 0; i < 4; i++) {
			argument = argument.Supr(0);
		}
		if (!strcmp(three_letters_command.GetString(), "FPS") || !strcmp(three_letters_command.GetString(), "Fps") || !strcmp(three_letters_command.GetString(), "fps"))
			command = commands::FPS;
		else if (!strcmp(three_letters_command.GetString(), "map"))
			command = commands::map;
		else
			command = commands::none;
	}
	return argument;
}

void Console::ExecuteCommand(p2SString argument) {
	int fps = 0;
	switch (command) {
	case commands::list:
		LOG("Commands available: list, god_mode, quit, FPS, map");
		break;

	case commands::god_mode:
		App->entity_manager->Player->player.player_god_mode = !App->entity_manager->Player->player.player_god_mode;
		App->entity_manager->Player->player.player_not_jumping = true;
		App->entity_manager->Player->player.spacebar_pushed = false;
		if(App->entity_manager->Player->player.player_god_mode==true)
			LOG("God_mode activated");
		else
			LOG("God_mode deactivated");
		break;

	case commands::quit:
		LOG("Exiting game");
		exitGame = true;
		break;

	case commands::FPS:
		if(strcmp(argument.GetString(),""))
			fps = std::stoul(argument.GetString());
		if (fps >= 30 && fps <= 120) {
			App->fps_limit = fps;
			LOG("Changing FPS limit to %d", fps);
		}
		else
			LOG("Please, write as argument a number that goes between 30 and 120");
		break;

	case commands::map:
		if (App->scene->Load_Map_By_Name(argument.GetString()) == true)
			LOG("Changing scene to map: %s", argument.GetString());
		else
			LOG("Could not change scene to map %s", argument.GetString());
		break;

	case commands::none:
		LOG("Command not found");
		break;
	}
}