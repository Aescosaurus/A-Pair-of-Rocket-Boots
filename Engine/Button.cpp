#include "Button.h"

Button::Button( const Vei2& center,const std::string& text )
	:
	size( GetSize( text ) ),
	pos( center - size / 2 ),
	text( text )
{}

bool Button::Update( const Vei2& mousePos,bool mouseDown )
{
	hovering = ( ContainsPoint( mousePos ) );

	if( mouseDown && hovering && canClick )
	{
		clicking = true;
	}
	else clicking = false;

	if( !mouseDown ) canClick = true;
	else canClick = false;

	return( clicking );
}

void Button::Draw( Graphics& gfx ) const
{
	const auto drawCol = hovering
		? Colors::White
		: Colors::LightGray;

	luckyPixel->DrawText( text,pos + padding / 2,
		drawCol,gfx );
}

void Button::DrawBackground( Graphics& gfx ) const
{
	const auto drawCol = hovering
		? Colors::White
		: Colors::LightGray;
	gfx.DrawRect( pos.x,pos.y,size.x,size.y,
		hovering ? Colors::LightGray : Colors::DarkGray );

	luckyPixel->DrawText( text,pos + padding / 2,
		drawCol,gfx );
}

void Button::Reset()
{
	hovering = false;
	canClick = false;
	clicking = false;
}

bool Button::IsPressed() const
{
	return( clicking );
}

bool Button::IsHovering() const
{
	return( hovering );
}

Vei2 Button::GetSize( const std::string& msg ) const
{
	const int msgWidth = int( msg.size() );
	const auto fontCharSize = luckyPixel->GetCharSize();
	return( Vei2{ fontCharSize.x * msgWidth,
		fontCharSize.y } + padding );
}

bool Button::ContainsPoint( const Vei2& point ) const
{
	return( point.x > pos.x && point.x < pos.x + size.x &&
		point.y > pos.y && point.y < pos.y + size.y );
}
