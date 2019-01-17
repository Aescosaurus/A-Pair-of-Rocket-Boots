#include "Comet.h"
#include "Rect.h"
#include "SpriteEffect.h"
#include "Random.h"

Comet::Comet( const Vei2& pos,float dir )
	:
	pos( Vec2( pos ) ),
	rotate( 0,0,radius * 2,radius * 2,5,*surfSheet,0.2f ),
	rotMat( Matrix::Rotation( dir ) )
{
	auto tempVel = -Vec2::FromAngle( dir );

	// This probably isn't the best way to do things but...
	while( OverlapsScreen() )
	{
		this->pos -= tempVel;
	}
	startPos = this->pos;
	this->pos -= tempVel;

	vel = tempVel * speed;
}

void Comet::Update( float dt )
{
	pos += vel * dt;

	if( !OverlapsScreen() )
	{
		respawn.Update( dt );

		if( respawn.IsDone() )
		{
			pos = startPos + vel * dt;
			respawn.Reset();
		}
	}
	else respawn.Reset();

	rotate.Update( dt );
}

void Comet::Draw( Graphics& gfx ) const
{
	// gfx.DrawCircleSafe( Vei2( pos ),radius,Colors::Red );

	rotate.Draw( Vei2( pos ) - Vei2{ radius,radius },gfx,
		Graphics::GetScreenRect().GetExpanded( radius * 5 ),
		SpriteEffect::SafeChroma{ Colors::Magenta },
		rotMat,false );
}

void Comet::Destroy()
{
	pos = startPos;
}

Circle Comet::GetCollider() const
{
	return( Circle{ pos,float( radius ) } );
}

const Vec2& Comet::GetVel() const
{
	return( vel );
}

bool Comet::OverlapsScreen() const
{
	RectI hitbox = RectI{ Vei2( pos ) -
		Vei2{ radius,radius },radius * 2,radius * 2 };
	return( hitbox/*.GetExpanded( Random{ 2,7 } )*/
		.IsOverlappingWith( Graphics::GetScreenRect() ) );
}
