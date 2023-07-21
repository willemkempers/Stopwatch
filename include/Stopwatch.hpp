//
//  Stopwatch.hpp
//
//  Created by Willem Kempers on 25/03/2021.
//

#pragma once

#include <chrono>

/**
 * @brief Stopwatch class
 * @details Uses a std::chrono::steady_clock to keep track of elapsed time
 */
class Stopwatch
{
    using clock = std::chrono::steady_clock;
    using time_point = clock::time_point;
    using duration = clock::duration;

public:
    enum class Mode
    {
        run,
        pause,
        stop
    };

public:
    Stopwatch(bool run = false,
              time_point begin = clock::now())
    {
        if (run)
            start(begin);
    }
    
    Stopwatch(const duration offset)
    {
        start(clock::now() - offset);
    }
    
    /**
     * @brief Start timing
     * @param now Current time - defaults to clock::now()
     */
    void start(const time_point begin = clock::now())
    {
        m_begin = begin;
        m_mode = Mode::run;
    }

    /**
     * @brief Start timing
     * @param offset Used to offset the m_start variable and therefore offset the time elapsed.
     */
    void start(const duration offset)
    {
        start(clock::now() - offset);
    }
    
    /**
     * @brief Pause timing
     * @param end Current time, defaults to `clock::now()`
     */
    void pause(const time_point end = clock::now())
    {
        if (m_mode == Mode::run)
        {
            m_end = end;
            m_mode = Mode::pause;
        }
    }
    
    /**
     * @brief Stop timing
     */
    void stop()
    {
        m_mode = Mode::stop;
    }
    
    /**
     * @brief Resume timing
     * @details calls start(m_end)
     */
    void resume()
    {
        if (m_mode == Mode::pause)
            start(m_end);
        else if (m_mode == Mode::stop)
            start();
    }

    /**
     * @brief Get the elapsed time since the Stopwatch was started
     * @param now Current time - defaults to clock::now()
     * @return Delta between \a now and m_start if the Stopwatch is running. If the Stopwatch is stopped will return the delta between m_start and m_end.
     */
    duration elapsed(time_point now = clock::now()) const
    {
        if (m_mode == Mode::stop)
            return duration(0);
        else if (m_mode == Mode::pause)
            now = m_end;
        
        duration delta = now - m_begin;
        
        return delta;
    }
    
    /**
     * @brief Check if the Stopwatch is running
     * @return true if the Stopwatch is running, else false
     */
    bool running() const
    {
        return m_mode == Mode::run;
    }
    
    /**
     * @brief Check if the Stopwatch is paused
     * @return true if the Stopwatch is paused, else false
     */
    bool paused() const
    {
        return m_mode == Mode::pause;
    }

    /**
     * @brief Check if the Stopwatch is stopped
     * @return true if the Stopwatch is stopped, else false
     */
    bool stopped() const
    {
        return m_mode == Mode::stop;
    }

private:
    time_point m_begin, m_end;
    Mode m_mode = Mode::stop;
};
