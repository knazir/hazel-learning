#pragma once

#include "Event.h"

namespace Hazel
{
class HAZEL_API MouseMovedEvent : public Event
{
public:
	MouseMovedEvent(float x, float y)
		: mMouseX(x)
		, mMouseY(y) {}

	inline float GetX() const { return mMouseX; }
	inline float GetY() const { return mMouseY; }

	std::string ToString() const override
	{
		std::stringstream ss;
		ss << "MouseMovedEvent: " << mMouseX << ", " << mMouseY;
		return ss.str();
	}

	EVENT_CLASS_TYPE(MouseMoved)
	EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

private:
	float mMouseX;
	float mMouseY;
};

class HAZEL_API MouseScrolledEvent : public Event
{
public:
	MouseScrolledEvent(float xOffset, float yOffset)
		: mXOffset(xOffset)
		, mYOffset(yOffset) {}

	inline float GetXOffset() const { return mXOffset; }
	inline float GetYOffset() const { return mYOffset; }

	std::string ToString() const override
	{
		std::stringstream ss;
		ss << "MouseScrolledEvent: " << GetXOffset() << ", " << GetYOffset();
		return ss.str();
	}

	EVENT_CLASS_TYPE(MouseScrolled)
	EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

private:
	float mXOffset;
	float mYOffset;
};

class HAZEL_API MouseButtonEvent : public Event
{
public:
	inline int32_t GetMouseButton() const { return mButton; }

	EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

protected:
	MouseButtonEvent(int32_t button)
		: mButton(button) {}

	int32_t mButton;
};

class HAZEL_API MouseButtonPressedEvent : public MouseButtonEvent
{
public:
	MouseButtonPressedEvent(int32_t button)
		: MouseButtonEvent(button) {}

	std::string ToString() const override
	{
		std::stringstream ss;
		ss << "MouseButtonPressedEvent: " << mButton;
		return ss.str();
	}

	EVENT_CLASS_TYPE(MouseButtonPressed)
};

class HAZEL_API MouseButtonReleasedEvent : public MouseButtonEvent
{
public:
	MouseButtonReleasedEvent(int32_t button)
		: MouseButtonEvent(button) {}

	std::string ToString() const override
	{
		std::stringstream ss;
		ss << "MouseButtonReleasedEvent: " << mButton;
		return ss.str();
	}

	EVENT_CLASS_TYPE(MouseButtonReleased)
};
}
