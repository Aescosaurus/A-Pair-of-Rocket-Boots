#pragma once

#include "Vec2.h"
#include "Graphics.h"
#include "Circle.h"
#include "Animation.h"
#include "Codex.h"
#include <vector>

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

		Circle GetCollider() const;
		bool IsDestroyed() const;
	public:
		static constexpr int pointValue = 100;
	private:
		static constexpr int radius = 8;
		static constexpr float speed = 75.0f;
		Vec2 pos;
		Vec2 vel;
		bool destroyed = false;
	};
public:
	MarsTurret( const Vec2& pos,float angle,
		std::vector<Bullet>& bullets );

	void Update( const Vec2& playerPos,float dt );
	void Draw( Graphics& gfx ) const;

	void Destroy();

	Circle GetColl() const;
	bool IsDestroyed() const;
private:
	static constexpr int radius = 32;
	Vec2 pos;
	float angle;
	Matrix rotMat;
	CSurfPtr pSurfSheet = SurfCodex::Fetch( "Images/MarsTurretAnim.bmp" );
	Animation baseAnim;
	Animation topAnim;
	std::vector<Bullet>* pBulletVec;
	bool destroyed = false;
	// Timer shotRefire
};