#pragma once

namespace Log
{
  /**
   * @brief An Logger object which disabled log code can be forwarded to.
   */
  class DummyLogger
  {
  public:
    DummyLogger() = default;
    ~DummyLogger() = default;

    DummyLogger(const DummyLogger&) = delete;
    DummyLogger& operator=(const DummyLogger&) = delete;

    DummyLogger(DummyLogger&&) = delete;
    DummyLogger& operator=(DummyLogger&&) = delete;

    /**
     * @brief An empty implementation for every insertion operator one could think of.
     * This should be optimized away by the compiler as it does not do anything.
     */
    template <typename T>
    DummyLogger& operator <<(const T)
    {
        return *this;
    }
  };
} // Namespace Log.
