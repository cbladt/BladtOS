#pragma once

///
/// \brief The DisableInterrupt class, Disables and enables interrupts RAII style.
/// Disable interrupt on ctor
/// Enable interrupt on
/// // TODO How do I test this?
///
class DisableInterrupt
{
public:
    DisableInterrupt();
    ~DisableInterrupt();

    DisableInterrupt(const DisableInterrupt&) = delete;
    DisableInterrupt& operator=(const DisableInterrupt&) = delete;

    DisableInterrupt(DisableInterrupt&&) = delete;
    DisableInterrupt& operator=(DisableInterrupt&&) = delete;
};
