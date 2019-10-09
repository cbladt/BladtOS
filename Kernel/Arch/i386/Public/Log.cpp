#include "Log.hpp"

namespace Log::__internal
{
    namespace
    {
        Logger<Printer> _debugLogger;
        Logger<Printer> _errorLogger;
        DummyLogger _dummmyLogger;
    }

    // TODO Research: Could these be inlined in header file? Right now placed in cpp to ensure a single copy across translations units.
    Logger<Printer>& GetDebugLogger()
    {
        return _debugLogger;
    }

    Logger<Printer>& GetErrorLogger()
    {
        return _errorLogger;
    }

    DummyLogger& GetDummyLogger()
    {
        return _dummmyLogger;
    }
}
