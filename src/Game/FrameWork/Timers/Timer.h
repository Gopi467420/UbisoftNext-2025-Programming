class Timer
{
public:
    void Start(float seconds)
    {
        m_interval = (seconds > 0.0f) ? seconds : 0.0001f;
        m_acc = 0.0f;
        m_running = true;
    }

    void Stop() { m_running = false; }
    void Reset() { m_acc = 0.0f; }

    // returns true when interval is reached
    bool Update(float dt)
    {
        if (!m_running) return false;

        m_acc += dt;

        if (m_acc >= m_interval)
        {
            m_acc -= m_interval; // keep leftover
            return true;         // trigger
        }

        return false;
    }

    bool IsRunning() const { return m_running; }

private:
    float m_interval = 1.0f;
    float m_acc = 0.0f;
    bool  m_running = false;
};
