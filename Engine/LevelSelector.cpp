#include "LevelSelector.h"
#include "SpriteEffect.h"

LevelSelector::LevelSelector( const Mouse& mouse,const Keyboard& kbd,Graphics& gfx )
	:
	mouse( mouse ),
	kbd( kbd ),
	gfx( gfx )
	// minStarPos( -starsImg->GetWidth() + Graphics::ScreenWidth )
{}

void LevelSelector::Update()
{
	const auto dt = ft.Mark();
	// todo: dt stuff
	const auto mousePos = mouse.GetPos();
	const auto mouseDown = mouse.LeftIsPressed();

	// if( mouseDown )
	// {
	// 	const auto diff = mousePos - oldMousePos;
	// 	starPos.x += diff.x;
	// 
	// 	if( starPos.x < minStarPos ) starPos.x = minStarPos;
	// 	if( starPos.x > maxStarPos ) starPos.x = maxStarPos;
	// }

	menuButton.Update( mousePos,mouseDown );

	earth.Update( starPos,mousePos,mouseDown,dt );
	moon.Update( starPos,mousePos,mouseDown,dt );
	mars.Update( starPos,mousePos,mouseDown,dt );
	jupiter.Update( starPos,mousePos,mouseDown,dt );

	oldMousePos = mousePos;
}

void LevelSelector::Draw() const
{
	gfx.DrawSpriteNormal( starPos.x,starPos.y,
		*starsImg,SpriteEffect::Copy{} );

	menuButton.Draw( gfx );

	earth.Draw( starPos,gfx );
	moon.Draw( starPos,gfx );
	mars.Draw( starPos,gfx );
	jupiter.Draw( starPos,gfx );

	earth.DrawMenu( gfx );
	moon.DrawMenu( gfx );
	mars.DrawMenu( gfx );
	jupiter.DrawMenu( gfx );
}

void LevelSelector::Reset()
{
	oldMousePos = mouse.GetPos();
	starPos = Vei2{ 0,0 };
	earth.ReloadSaveInfo();
	moon.ReloadSaveInfo();
	mars.ReloadSaveInfo();
	jupiter.ReloadSaveInfo();
}

int LevelSelector::GotoLevel()
{
	int total = -1;
	total += earth.GetReaction();
	total += moon.GetReaction();
	total += mars.GetReaction();
	total += jupiter.GetReaction();
	return( total );
}

bool LevelSelector::BackToMenu() const
{
	return( menuButton.IsPressed() || kbd.KeyIsPressed( VK_ESCAPE ) );
}
