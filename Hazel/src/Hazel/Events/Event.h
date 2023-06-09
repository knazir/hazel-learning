#pragma once

#include "Hazel/Core.h"

#include <functional>

namespace Hazel
{
enum class EventType
{
	None = 0,
	WindowClose,
	WindowResize,
	WindowFocus,
	WindowLostFocus,
	WindowMoved,
	AppTick,
	AppUpdate,
	AppRender,
	KeyPressed,
	KeyReleased,
	MouseButtonPressed,
	MouseButtonReleased,
	MouseMoved,
	MouseScrolled
};

enum EventCategory
{
	None = 0,
	EventCategoryApplication	= BIT(0),
	EventCategoryInput			= BIT(1),
	EventCategoryKeyboard		= BIT(2),
	EventCategoryMouse			= BIT(3),
	EventCategoryMouseButton	= BIT(4)
};

#define EVENT_CLASS_TYPE(type)  static EventType GetStaticType() { return EventType::##type; }\
								virtual EventType GetEventType() const override { return GetStaticType(); }\
								virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int32_t GetCategoryFlags() const override { return category; }

class HAZEL_API Event
{
public:
	virtual EventType GetEventType() const = 0;
	virtual const char* GetName() const = 0;
	virtual int32_t GetCategoryFlags() const = 0;

	virtual bool IsHandled() const { return mHandled; }
	virtual void SetHandled(bool handled) { mHandled = handled; }
	virtual std::string ToString() const { return GetName(); }

	inline bool IsInCategory(EventCategory category) const { return GetCategoryFlags() & category; }

protected:
	bool mHandled = false;
};

class EventDispatcher
{
	template<typename T>
	using EventFn = std::function<bool(T&)>;
	
public:
	EventDispatcher(Event& event)
		: mEvent(event) {}

	template<typename T = Event>
	bool Dispatch(EventFn<T> func)
	{
		if (mEvent.GetEventType() == T::GetStaticType())
		{
			const bool handled = func(static_cast<T&>(mEvent));
			mEvent.SetHandled(handled);
			return true;
		}

		return false;
	}

private:
	Event& mEvent;
};

inline std::ostream& operator<<(std::ostream& os, const Event& e)
{
	return os << e.ToString();
}
}
