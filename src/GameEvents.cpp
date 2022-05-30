#include "GameEvents.h"

MoveEvent::MoveEvent(const Vector2D& direction) : Event((EventType)MOVE_EVENT)
{
	mDirection = direction;
}

CollisionEvent::CollisionEvent(Unit* unit) : Event((EventType)COLLISION_EVENT)
{
	mpUnit = unit;
}

ClickEvent::ClickEvent(const Vector2D& position) : Event((EventType)CLICK_EVENT)
{
	mPosition = position;
}

DisplayEscapeMenuEvent::DisplayEscapeMenuEvent() : Event((EventType)DISPLAY_ESCAPE_MENU_EVENT)
{
}
