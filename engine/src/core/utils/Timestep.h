#ifndef TIMESTEP_H
#define TIMESTEP_H

namespace engine {
    struct Timestep {
        float _time;

        Timestep(float time = 0.0f) : _time(time) {}

        operator float() const { return _time; }

        float GetAsSeconds() const { return _time; }
        float GetAsMilliseconds() const { return _time * 1000.0f; }
    };
}

#endif