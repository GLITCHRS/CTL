#pragma once

#include <string>
#include <thread>
#include <chrono>
#include <fstream>

#if PROFILING == 1
#define PROFILE_SCOPE(name) BenchEngine::InstrumentationTimer timer##__LINE__(name)
#define PROFILE_FUNCTION() PROFILE_SCOPE(__FUNCSIG__)
#define START_PROFILE(name) BenchEngine::Instrumentor::Get().BeginSession(name)
#define END_PROFILE() BenchEngine::Instrumentor::Get().EndSession()
#define COLISSION_DEFENDER() std::this_thread::sleep_for(std::chrono::microseconds(1))
#else
#define PROFILE_SCOPE(name)
#define PROFILE_FUNCTION()
#define START_PROFILE(name)
#define END_PROFILE()
#define COLISSION_DEFENDER()
#endif

struct InstrumentationSession
{
    std::string Name;
};

struct ProfileResult
{
    std::string Name;
    long long Start, End;
    size_t ThreadID;
};

namespace BenchEngine
{
    class InstrumentationTimer
    {
    public:
        InstrumentationTimer(const char* name);

        ~InstrumentationTimer();

        void Stop();
    private:
        const char* m_Name;
        std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTimepoint;
        bool m_Stopped;
    };

    class Instrumentor
    {
    private:
        InstrumentationSession m_CurrentSession;
        std::ofstream m_OutputStream;
        int m_ProfileCount;
    public:
        Instrumentor();

        void BeginSession(const std::string& name, const std::string& filepath = "results");

        void EndSession();

        void WriteProfile(const ProfileResult& result);

        void WriteHeader();

        void WriteFooter();

        static Instrumentor& Get()
        {
            static Instrumentor instance;
            return instance;
        }
    };
};