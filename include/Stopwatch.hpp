//
//  Stopwatch.hpp
//
//  Created by Willem Kempers on 25/03/2021.
//

#pragma once

#include <chrono>
#include <memory>

namespace form
{

using clock = std::chrono::steady_clock;
using double_seconds = std::chrono::duration<double>;
using time_point = std::chrono::time_point<clock, double_seconds>;

/**
 * @brief Stopwatch class
 * @details Uses a std::chrono::steady_clock to keep track of elapsed time
 */
class Stopwatch
{
public:
    Stopwatch (bool run = false,
               time_point begin = clock::now())
    {
        if (run)
            start (begin);
    }
    
    Stopwatch (const double_seconds offset)
    {
        start (clock::now() - offset);
    }
    
    /**
     * @brief Start timing
     * @param now Current time - defaults to clock::now()
     */
    void start (const time_point begin = clock::now())
    {
        m_begin = begin;
        m_running = true;
    }

    /**
     * @brief Start timing
     * @param offset Used to offset the m_start variable and therefore offset the time elapsed.
     */
    void start (const double_seconds offset)
    {
        start (clock::now() - offset);
    }
    
    /**
     * @brief Stop timing
     * @param now Current time - defaults to clock::now()
     */
    void stop (const time_point end = clock::now())
    {
        m_end = end;
        m_running = false;
    }
    
    /**
     * @brief Get the elapsed time since the Stopwatch was started
     * @param now Current time - defaults to clock::now()
     * @return Delta between \a now and m_start if the Stopwatch is running. If the Stopwatch is stopped will return the delta between m_start and m_end.
     */
    double_seconds elapsed (time_point now = clock::now()) const
    {        
        if (!m_running)
            now = m_end;
        
        double_seconds delta = now - m_begin;
        
        return delta;
    }
    
    /**
     * @brief Resume timing
     * @details calls start(m_end)
     */
    void resume()
    {
        start (m_end);
    }
    
    /**
     * @brief Check if the Stopwatch is running
     * @return const reference to m_running. If true the Stopwatch is running, if false the Stopwatch is stopped
     */
    const bool& running() const
    {
        return m_running;
    }
    
private:
    time_point m_begin, m_end;
    bool m_running;
};

} // namespace form
