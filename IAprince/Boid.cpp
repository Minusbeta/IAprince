#include "stdafx.h"
#include "Boid.h"


CBoid::CBoid()
{
}


CBoid::~CBoid()
{
}

void CBoid::Init()
{
}

void CBoid::Destroy()
{
}

void CBoid::Update(float _DeltaTime, VECTOR4D(_targetPosition))
{
}

void CBoid::Render()
{
}



VECTOR4D CBoid::Seek(VECTOR4D _targetPosition)
{
	VECTOR4D Result = _targetPosition - Pos;
	return Normalize(Result)*Force;
}

VECTOR4D CBoid::Flee(VECTOR4D _targetPosition, float _DangerZoneFlee, float Force)
{
	if (Magnity(Pos - _targetPosition) > _DangerZoneFlee)
	{
		return VECTOR4D(0, 0, 0, 0);
	}
	VECTOR4D Result = Pos - _targetPosition;
	return Normalize(Result)*Force;


}

VECTOR4D CBoid::Arrive(VECTOR4D _targetPosition, float _ArriverZoneArrive, float Force)
{
	VECTOR4D Direction = Normalize(Pos - _targetPosition);
	if (Magnity(_targetPosition - Pos) > _ArriverZoneArrive)
	{
		return Seek(Pos);
	}
	return Magnity(Pos - _targetPosition) / _ArriverZoneArrive*(Direction - _targetPosition);
}

VECTOR4D CBoid::Pursue(VECTOR4D _targetPosition, VECTOR4D _Direction, VECTOR4D Vel, float _futureTime)
{
	VECTOR4D futurePos = Pos + (Vel*_futureTime);
	float pursueRadio = Magnity(futurePos - Pos);
	if (Magnity(_targetPosition - Pos) < pursueRadio)
	{
		_futureTime = Magnity(_targetPosition - Pos) / pursueRadio;
		futurePos = Pos + (Vel*_futureTime);
	}
	return Seek(futurePos);
}

VECTOR4D CBoid::Evade(VECTOR4D _targetPosition, VECTOR4D _Direction, VECTOR4D _Vel, float _futureTime, float _EvadeRadioForce, float Force)
{
	VECTOR4D futurePos = _targetPosition + (_Vel*_futureTime);
	VECTOR4D Evade = Flee(Pos, _EvadeRadioForce, Force);
	if (Magnity(Pos - _targetPosition) < _EvadeRadioForce)
	{
		Evade = Evade + Flee(futurePos, _EvadeRadioForce, Force);
	}
	return Evade;
}

VECTOR4D CBoid::Wander(float _worldSizeX, float _worldSizeY, float _timeLimit, float Force)
{
	static float maxTime = 3;
	static VECTOR4D PuntoWander;
	static VECTOR4D FuerzaResultante;

	if (maxTime - _timeLimit <= 0)
	{
		PuntoWander = VECTOR4D((rand() % 1)*_worldSizeX, (rand() % 1)*_worldSizeY, 0, 1);
		maxTime = 3;
	}
	FuerzaResultante = Normalize(Seek(PuntoWander))*Force;


	return FuerzaResultante;
}

