#pragma once

#include "uvxx.hpp"
#include "event_dispatcher_object.hpp"
#include "_live_rtsp_client.hpp"
#include "_uvxx_task_scheduler.h"
#include "BasicUsageEnvironment.hh"
#include "MediaSession.hh"

#include <memory>
#include <string>

namespace uvxx { namespace rtsp { namespace details 
{
    using _usage_environment_ptr = std::shared_ptr<UsageEnvironment>;

    class _media_subsession : public uvxx::event_dispatcher_object
    {
    public:
        _media_subsession(MediaSubsession* live_subsession);

        _media_subsession();

        _media_subsession(const _media_subsession&) = default;

        _media_subsession& operator=(const _media_subsession&) = default;

        _media_subsession(_media_subsession&& rhs);

        _media_subsession& operator=(_media_subsession&& rhs);

        virtual ~_media_subsession();

    public:
        MediaSubsession* live_media_subsession_get() const;

        bool initiate(int use_special_rtp_offset = -1);

        std::string codec_name_get();

    private:
        MediaSubsession* _live_subsession;
    };

    using _media_subsession_ptr = std::shared_ptr<_media_subsession>;

    class _media_session : public uvxx::event_dispatcher_object
    {
    public:
        _media_session();

        _media_session(const _media_session&) = default;

        _media_session& operator=(const _media_session&) = default;

        _media_session(_media_session&& rhs);

        _media_session& operator=(_media_session&& rhs);

    public:
        void set_media_session(const _usage_environment_ptr& usage_environment, MediaSession* live_session);

        virtual ~_media_session();

        const std::vector<_media_subsession_ptr>& subsessions() const;   

        MediaSession* live_media_session_get() const;

    private:
        void reset();

    private:
        std::vector<_media_subsession_ptr> _subsessions;

        _usage_environment_ptr _usage_environment;

        MediaSession* _live_session;
    };

    using _media_session_ptr = std::shared_ptr<_media_session>;
}}}