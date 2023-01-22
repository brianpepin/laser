#pragma once

enum class DisplayMode
{
    Current,
    Power
};

struct Settings
{
    struct Limits
    {
        float maxPump1Current;
        float maxPump2Current;
    } limits;

    struct Temps
    {
        float pump1;
        float pump2;
        float vanadate;
        float ktp;
    } temps;

    float current;
    DisplayMode displayMode;

    void load();
    void save();
};
