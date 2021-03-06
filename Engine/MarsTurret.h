#pragma once

#include "Vec2.h"
#include "Graphics.h"
#include "Circle.h"
#include "Animation.h"
#include "Codex.h"
#include <vector>
#include "Timer.h"
#include "Line.h"

// Turret that sticks to platforms or walls and shoots
//  bullets at the player periodically (which make
//  the player lose lots of points).
class MarsTurret
{
public:
	class Bullet
	{
	public:
		Bullet( const Vec2& start,const Vec2& target );

		void Update( float dt );
		void Draw( Graphics& gfx ) const;

		void Destroy();
		bool CheckColl( const std::vector<Line>& lines );

		Circle GetCollider() const;
		bool IsDestroyed() const;
		const Vec2& GetPos() const;
	public:
		static constexpr int pointValue = 100;
	private:
		static constexpr int radius = 8;
		static constexpr float speed = 75.0f;
		static constexpr float rotSpeed = 12.6f;
		Vec2 pos;
		Vec2 vel;
		bool destroyed = false;
		float rotAngle;
		CSurfPtr pSurf = SurfCodex::Fetch( "Images/MarsTurretBullet.bmp" );
	};
public:
	MarsTurret( const Vec2& pos,float angle,
		std::vector<Bullet>& bullets );

	void Update( const Vec2& playerPos,float dt );
	void Draw( Graphics& gfx ) const;

	void Destroy();

	Circle GetColl() const;
	bool IsDestroyed() const;
	const Vec2& GetPos() const;
private:
	Vec2 GetCenter() const;
private:
	static constexpr int radius = 32;
	Surface rotatedImage;
	Vei2 myDrawPos;
	Vec2 pos;
	Matrix rotMat;
	CSurfPtr pBaseSurf = SurfCodex::Fetch( "Images/MarsTurretBase.bmp" );
	CSurfPtr pTopSurf = SurfCodex::Fetch( "Images/MarsTurretTop.bmp" );
	std::vector<Bullet>* pBulletVec;
	bool destroyed = false;
	float turretAngle;
	Timer shotRefire = 3.17f;
	CSoundPtr shotSound = SoundCodex::Fetch( "Audio/Turret.wav" );
};