#pragma once

class LinkablePart {
    public:
        LinkablePart() = default;
        virtual ~LinkablePart() = default;
        virtual void execute(float p_pression) = 0;
};