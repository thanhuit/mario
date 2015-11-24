#pragma once
#include"GameObject.h"
#include<list>
#include"RecF.h"

#define MAX_OBJECT 17
#define MAX_LEVEL 15

typedef std::list<GameObject*> ObjectList;
class Quadtree{
private:
	int level;
	ObjectList* objList;
	RecF* region;
	Quadtree** nodes;
	bool IsContain(GameObject* object);
	void Split();
public:
	Quadtree();
	Quadtree(int pLevel,RecF* region);
	~Quadtree();

	void Clear();
	void Insert(GameObject* obj);
	void Insert(RecF* rec);
	ObjectList* Retrieve(ObjectList* returnObject, GameObject* object);
	ObjectList* Retrieve(ObjectList* returnObject, RecF* collisionRec);

};