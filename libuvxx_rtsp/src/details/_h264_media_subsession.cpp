#include "H264VideoRTPSink.hh"
#include "H264VideoStreamDiscreteFramer.hh"
#include "pplx/pplpp.hpp"
#include "event_dispatcher_frame.hpp"
#include "details/_live_common.hpp"
#include "details/_h264_media_subsession.hpp"
#include "details/_h264_framed_source.hpp"

using namespace uvxx::rtsp::details;

void _h264_media_subsession::after_playing_dummy_callback(void* clientData) 
{
    _h264_media_subsession* subsess = static_cast<_h264_media_subsession*>(clientData);

    subsess->after_playing_dummy();
}

_h264_media_subsession::_h264_media_subsession(int stream_id) :
    OnDemandServerMediaSubsession(*_get_live_environment().get(), false), 
    _stream_id(stream_id)
{
   
}

_h264_media_subsession::~_h264_media_subsession()
{
}

void _h264_media_subsession::framed_source_created_set(framed_source_created_delegate callback)
{
    _framed_source_created = std::move(callback);
}

char const* _h264_media_subsession::getAuxSDPLine(RTPSink* rtp_sink, FramedSource* input_source)
{
    check_for_aux_sdp_line();

    if (_aux_sdp_line.size())
    {
        return _aux_sdp_line.c_str(); // it's already been set up (for a previous client)
    }

    if (fDummyRTPSink == nullptr) 
    {   // we're not already setting it up for another, concurrent stream
        // Note: For H265 video files, the 'config' information (used for several payload-format
        // specific parameters in the SDP description) isn't known until we start reading the file.
        // This means that "rtpSink"s "auxSDPLine()" will be NULL initially,
        // and we need to start reading data from our file until this changes.
        fDummyRTPSink = rtp_sink;

        // Start reading the file:
        fDummyRTPSink->startPlaying(*input_source, after_playing_dummy_callback, this);

        // Check whether the sink's 'auxSDPLine()' is ready:
    }

    auto dispatcher = event_dispatcher::current_dispatcher();

    dispatcher.begin_invoke([=]
    {
        return uvxx::pplx::create_timer_task(std::chrono::milliseconds(1000)).then([=]() mutable
        {
            _sdp_check_dispatcher_frame.continue_set(false);
        });
    });

    dispatcher.push_frame(_sdp_check_dispatcher_frame);
    
    _sdp_check_dispatcher_frame.continue_set(false);

    check_for_aux_sdp_line();

    return _aux_sdp_line.size() ? _aux_sdp_line.c_str() : nullptr;
}

FramedSource* _h264_media_subsession::createNewStreamSource(unsigned client_session_id, unsigned& estimated_kbps)
{
    if(!_source)
    {
        _source = std::shared_ptr<_h264_framed_source>(new _h264_framed_source(_stream_id), [](_live_framed_source*)
        {
            /* todo add logic later in case live55 doesn't free */
        });

        if (_framed_source_created)
        {
            _framed_source_created(_stream_id, client_session_id, _source);
        }
    }

    estimated_kbps = 2500; /* kbps, estimate */

    auto framesource = H264VideoStreamDiscreteFramer::createNew(envir(), _source.get());

    return framesource;
}

RTPSink* _h264_media_subsession::createNewRTPSink(Groupsock* rtp_groupsock, unsigned char rtp_payload_type_if_dynamic, FramedSource* /*inputSource*/) 
{
    return H264VideoRTPSink::createNew(envir(), rtp_groupsock, rtp_payload_type_if_dynamic);
}

void _h264_media_subsession::closeStreamSource(FramedSource* inputSource)
{
    OnDemandServerMediaSubsession::closeStreamSource(inputSource);
}

void _h264_media_subsession::after_playing_dummy()
{
}

void _h264_media_subsession::check_for_aux_sdp_line()
{
    char const* dasl;

    if (_aux_sdp_line.size()) 
    {
        _sdp_check_dispatcher_frame.continue_set(false);
    }
    else if (fDummyRTPSink != nullptr && (dasl = fDummyRTPSink->auxSDPLine()) != nullptr)
    {
        _aux_sdp_line = dasl;

        fDummyRTPSink = nullptr;

        _sdp_check_dispatcher_frame.continue_set(false);
    }
}