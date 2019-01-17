#include "MovingFloor.h"
#include "SpriteEffect.h"

MovingFloor::MovingFloor( const Vec2& pos,float angle,
	int leftStop,int rightStop,float speed )
	:
	Floor( pos,angle,SurfCodex::Fetch( "Images/MovingPlatform.bmp" ) ),
	leftPos( leftStop ),
	rightPos( rightStop ),
	vel( Vec2::FromAngle( angle ) * speed )
{}

void MovingFloor::Update( float dt )
{
	const Vec2 oldPos = center;

	center += vel * float( dir ) * dt;

	if( center.x < float( leftPos ) )
	{
		dir = 1;
		center += vel * float( dir ) * dt * 2.0f;
	}
	if( center.x > float( rightPos ) )
	{
		dir = -1;
		center += vel * float( dir ) * dt * 2.0f;
	}

	MoveBy( center - oldPos );
}

void MovingFloor::Draw( Graphics& gfx ) const
{
	const auto drawPos = GetDrawPos();

	gfx.DrawSprite( drawPos.x,drawPos.y,*img,
		SpriteEffect::Chroma{ Colors::Magenta },
		rotationMatrix );
}

void MovingFloor::MoveBy( const Vec2& amount )
{
	for( auto& line : lines )
	{
		line.start += amount;
		line.end += amount;
	}
	for( auto& corner : corners )
	{
		corner.pos += amount;
	}
}