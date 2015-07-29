#pragma once
#include <memory>
#include "event_dispatcher_timer.hpp"

class UsageEnvironment;

namespace uvxx { namespace rtsp
{
    class media_session;

    class media_subsession;
}}

namespace uvxx { namespace rtsp { namespace details 
{
    class _uvxx_task_scheduler;

    class _live_rtsp_server;

    using _live_rtsp_server_ptr = std::shared_ptr<_live_rtsp_server>;

    using _uvxx_task_scheduler_ptr = std::shared_ptr<_uvxx_task_scheduler>;

    using _usage_environment_ptr = std::shared_ptr<UsageEnvironment>;
   
    class _rtsp_server_impl : public event_dispatcher_object
    {
    public:
        _rtsp_server_impl(uint16_t port);

    private:
        _usage_environment_ptr _usage_environment;

        _live_rtsp_server_ptr _live_server;

        _uvxx_task_scheduler* _task_scheduler;
    };

}}}