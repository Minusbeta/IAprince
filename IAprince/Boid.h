#pragma once
#include "VECTOR4D.h"
#include "MATRIX4D.h"
#include <memory.h>

class CBoid :public GameObject
{
public:
	CBoid();
	virtual ~CBoid();

	//static float m_SeekForce;
	//static float m_FleeForce;
	//static float m_ArriveForce;
	//static float m_WanderForce;
	//static float m_WanderForce2;
	//static float m_PursueForce;
	//static float m_EvadeForce;
	//static float m_ObstacleAvoidance;
	//static float m_ObstacleAvoidance2;

	VECTOR4D m_Vel;
	VECTOR4D m_GeneralForce;
	//float VelMax;
	float MaxForce;

	void Init();
	void Destroy();
	void Update(float _DeltaTime, VECTOR4D(_targetPosition));
	void Render();
	float Force;


	VECTOR4D Seek(VECTOR4D _targetPosition); //los que empiecen con _ van a ser parametros
	VECTOR4D Flee(VECTOR4D _targetPosition, float _DangerZoneFlee, float Force);
	VECTOR4D Arrive(VECTOR4D _targetPosition, float _ArriveZoneArrive, float Force);
	VECTOR4D Pursue(VECTOR4D _targetPosition, VECTOR4D _Direction, VECTOR4D Vel, float _futureTime);
	VECTOR4D Evade(VECTOR4D _targetPosition, VECTOR4D _Direction, VECTOR4D _Vel, float _futureTime, float _EvadeRadioForce, float Force);
	VECTOR4D Wander(float _worldSizeX, float _worldSizeY, float _timeLimit, float Force);



};

