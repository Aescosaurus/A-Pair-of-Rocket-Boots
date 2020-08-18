#pragma once

#include "Mouse.h"
#include "Graphics.h"
#include "CheckBox.h"
#include "Button.h"
#include <fstream>

class OptionsMenu
{
public:
	OptionsMenu();

	void Update( const Mouse& mouse );
	void Draw( Graphics& gfx ) const;

	void Save();
	void Load();

	bool BackToMenu() const;
	bool DoInvertControls() const;
	bool DoClickMovement() const;
private:
	static constexpr auto saveFileName = "Misc/Options.txt";
	Button menuButton = Button{ Vei2{ 850,480 },"Menu" };
	CheckBox invertControls = CheckBox{ Vei2{ 50,150 },"Invert Controls" };
	CheckBox clickMovement = CheckBox{ Vei2{ 50,210 },"Click Movement" };

	CFontPtr font = FontCodex::Fetch( "Fonts/LuckyPixel6x9.bmp" );
};