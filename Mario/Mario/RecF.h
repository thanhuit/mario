#ifndef _RECF_H_
#define _RECF_H_
#pragma once
#include <vector>
#include <algorithm>
class RecF
{
public:
	//kich thuoc
	float x, y;
	float width, height;
	//khoang cach di duoc giua 2 frame
	float vx, vy;
	//Thoi gian va cham
	float collisionTime;
	//Thoi gian con lai
	float remainingTime;
	bool blocked;
	RecF();
	RecF(float X, float Y, float Width, float Height, bool Blocked = false, float Vx = 0, float Vy = 0);
	//Tinh tien
	void Tranlate(float dx, float dy);
	//Kiem tra va cham
	static bool AABBCheck(RecF b1, RecF b2);
	//Lay vung di chuyen cua doi tuong
	static RecF GetSweptBroadphaseRec(RecF b);
	//tra ve thoi gian va cham
	static float SweptAABB(RecF b1, RecF b2, float& normalx, float& normaly);
	//thuat toan va cham
	static int Collide(RecF Rec, RecF block);
	~RecF();
};
typedef std::vector <RecF> RecFList;
#endif
