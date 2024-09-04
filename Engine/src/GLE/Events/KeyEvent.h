//
// Created by Andrew Graser on 2/8/2024.
//

#ifndef GLE_KEYEVENT_H
#define GLE_KEYEVENT_H

#include <sstream>
#include "Event.h"


class KeyEvent : public Event {
public:
    inline int GetKeyCode() const {return mKeyCode; }

    EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)

protected:
    KeyEvent(int keycode)
            : mKeyCode(keycode){

    }

    int mKeyCode;
};


class KeyPressedEvent : public KeyEvent {
public:
    KeyPressedEvent(int keycode, int repeatCount)
            : KeyEvent(keycode), mRepeatCount(repeatCount) {

    }

    inline int GetRepeatCount() const { return mRepeatCount; }

    std::string ToString() const override {
        std::stringstream ss;
        ss << "KeyPressedEvent: " << mKeyCode << " (" << mRepeatCount << " repeats)";
        return ss.str();
    }


    EVENT_CLASS_TYPE(KeyPressed)
private:
    int mRepeatCount;
};

class KeyReleasedEvent : public KeyEvent {
public:
    KeyReleasedEvent(int keycode)
            : KeyEvent(keycode) {

    }

    std::string ToString() const override {
        std::stringstream ss;
        ss << "KeyReleasedEvent: " << mKeyCode;
        return ss.str();
    }

    EVENT_CLASS_TYPE(KeyReleased)
};

class KeyTypedEvent : public KeyEvent {
public:
    KeyTypedEvent(int keycode)
            : KeyEvent(keycode) {

    }

    std::string ToString() const override {
        std::stringstream ss;
        ss << "KeyTypedEvent: " << mKeyCode;
        return ss.str();
    }

    EVENT_CLASS_TYPE(KeyTyped)

private:

};

#endif //GLE_KEYEVENT_H
