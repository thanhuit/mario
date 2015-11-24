#include "RecF.h"


RecF::RecF()
{
}
RecF::RecF(float X, float Y, float Width, float Height, bool Blocked, float Vx , float Vy)
{
	collisionTime = 1;
	remainingTime = 1 - collisionTime;
	x = X;
	y = Y;
	width = Width;
	height = Height;
	blocked = Blocked;
	//Vx=vx*dt...
	vx = Vx;
	vy = Vy;
}

void RecF::Tranlate(float dx, float dy)
{
	x += dx;
	y += dy;
}

bool RecF::AABBCheck(RecF b1, RecF b2)
{
	return !(b1.x + b1.width < b2.x || b1.x > b2.x + b2.width || b1.y + b1.height < b2.y || b1.y > b2.y + b2.height);
}

RecF RecF::GetSweptBroadphaseRec(RecF b)
{
	//hinh chu nhat bao quanh
	RecF broadphaseRecF(0.0f, 0.0f, 0.0f, 0.0f);

	//trong sach tr248
	broadphaseRecF.x = b.vx > 0 ? b.x : b.x + b.vx;
	broadphaseRecF.y = b.vy > 0 ? b.y : b.y + b.vy;
	broadphaseRecF.width = b.vx > 0 ? b.vx + b.width : b.width - b.vx;
	broadphaseRecF.height = b.vy > 0 ? b.vy + b.height : b.height - b.vy;

	return broadphaseRecF;
}

float RecF::SweptAABB(RecF b1, RecF b2, float& normalx, float& normaly)
{
	float xInvEntry, yInvEntry;
	float xInvExit, yInvExit;

	// find the distance between the objects on the near and far sides for both x and y
	if (b1.vx > 0.0f)
	{
		xInvEntry = b2.x - (b1.x + b1.width);
		xInvExit = (b2.x + b2.width) - b1.x;
	}
	else
	{
		xInvEntry = (b2.x + b2.width) - b1.x;
		xInvExit = b2.x - (b1.x + b1.width);
	}

	if (b1.vy > 0.0f)
	{
		yInvEntry = b2.y - (b1.y + b1.height);
		yInvExit = (b2.y + b2.height) - b1.y;
	}
	else
	{
		yInvEntry = (b2.y + b2.height) - b1.y;
		yInvExit = b2.y - (b1.y + b1.height);
	}

	// find time of collision and time of leaving for each axis (if statement is to prevent divide by zero)
	float xEntry, yEntry;
	float xExit, yExit;

	if (b1.vx == 0.0f)
	{
		xEntry = -std::numeric_limits<float>::infinity();
		xExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		xEntry = xInvEntry / b1.vx;
		xExit = xInvExit / b1.vx;
	}

	if (b1.vy == 0.0f)
	{
		yEntry = -std::numeric_limits<float>::infinity();
		yExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		yEntry = yInvEntry / b1.vy;
		yExit = yInvExit / b1.vy;
	}

	// find the earliest/latest times of collision
	float entryTime = std::max(xEntry, yEntry);
	float exitTime = std::min(xExit, yExit);

	// if there was no collision
	if (entryTime > exitTime || xEntry < 0.0f && yEntry < 0.0f || xEntry > 1.0f || yEntry > 1.0f)
	{
		normalx = 0.0f;
		normaly = 0.0f;
		return 1.0f;
	}
	else // if there was a collision
	{
		// calculate normal of collided surface
		if (xEntry > yEntry)
		{
			if (xInvEntry < 0.0f)
			{
				normalx = 1.0f;
				normaly = 0.0f;
			}
			else
			{
				normalx = -1.0f;
				normaly = 0.0f;
			}
		}
		else
		{
			if (yInvEntry < 0.0f)
			{
				normalx = 0.0f;
				normaly = 1.0f;
			}
			else
			{
				normalx = 0.0f;
				normaly = -1.0f;
			}
		}

		// return the time of collision
		return entryTime;
	}
}


int RecF::Collide(RecF Rec, RecF block)
{
	// RecF is the moving RecF
	// block is the static RecF
	RecF broadphaseRecF = GetSweptBroadphaseRec(Rec);
	if (AABBCheck(broadphaseRecF, block))
	{
		float normalx, normaly;
		float collisiontime = SweptAABB(Rec, block, normalx, normaly);
		float remainingtime = 1.0f - collisiontime;
		if (collisiontime < 1.0f)
		{
			if (Rec.collisionTime > collisiontime)
				Rec.collisionTime = collisiontime;
			if (normalx == -1)
				return 2;
			if (normalx == 1)
				return 1;
			if (normaly == -1)
				return 4;
			if (normaly == 1)
				return 3;
		}
		else
		if (AABBCheck(Rec, block))
		{
			return 5;
		}
	}
	return 0;
}


RecF::~RecF()
{
}
