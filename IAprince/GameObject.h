#pragma once
#include "VECTOR4D.h"
class GameObject
{
public:
	GameObject();
	//~ClassGameObject();

	//init destroy render 
	//Vector get y set position
	//virtual destructor
	//protected-> vector position 

	virtual void Init();
	virtual void Destroy();
	virtual void Update(float _deltaTime);
	virtual void Render();

	VECTOR4D getPos;
	VECTOR4D setPos;

	virtual ~GameObject();

protected:
	VECTOR4D Pos;


};