#include "no_sway.hpp"

#include "../../../engine/engine.hpp"
#include "../../../renderer/menu/config/config.hpp"

void modules::weapon::no_sway::callback( )
{
	std::unique_lock<std::mutex> initiate_thread_locker( engine::values::global_locker );

	const auto camera_copy = engine::values::camera;

	const auto local_game_world_copy = engine::values::local_game_world;

	if ( !camera_copy.instance || !local_game_world_copy.instance )
		return;

	const auto local_player_copy = local_game_world_copy.get_local_player( );

	initiate_thread_locker.unlock( );

	if (std::get< bool >(menu::config::config_map["enable_no_sway"]))
	{
		if ( !local_player_copy.instance )
			return;

		const auto local_player_breath_effector = local_player_copy.get_procedural_weapon_animation( ).get_breath_effector( );

		if ( !local_player_breath_effector.instance )
			return;

		local_player_breath_effector.set_sway_intensity( static_cast< float >( std::get< int >( menu::config::config_map["sway_intensity"] ) ) );
	}
}