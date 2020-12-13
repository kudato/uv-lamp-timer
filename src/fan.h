#pragma once
#include "../uv-lamp-timer.h"

//--------------------------------------------------------------------
// Class for control cooling fan
//--------------------------------------------------------------------

class Fan {
    public:
        Fan(void);
        bool status(void) const;
        void start(void);
        void stop(void);
    private:
        bool _status;
};

