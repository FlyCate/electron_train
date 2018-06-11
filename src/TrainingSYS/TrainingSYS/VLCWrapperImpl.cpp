/************************************************************************
    This file is part of VLCWrapper.
    
    File:   VLCWrapperImpl.cpp
    Desc.:  VLCWrapperImpl Implementation.

	Author:  Alex Skoruppa
	Date:    08/10/2009
	Updated: 03/12/2012
	eM@il:   alex.skoruppa@googlemail.com

	Updated by luxiaoxun
	Date: 2013.11.29
	email: luxiaoxun001@qq.com

	VLCWrapper is distributed under the Code Project Open License (CPOL).

	You should have received a copy of the Code Project Open License
	along with VLCWrapper.  If not, see <http://www.codeproject.com/info/cpol10.aspx>.
************************************************************************/
#include "stdafx.h"

#include "VLCWrapperImpl.h"
#include "vlc\vlc.h"
#include "vlc\libvlc_events.h"
#include <stdio.h>
#include <vector>

#pragma comment(lib, "lib\\libvlc.lib")
#pragma comment(lib, "lib\\libvlccore.lib")

VLCWrapperImpl::VLCWrapperImpl(void)
:	pVLCInstance_(0),
	pMediaPlayer_(0),
	pMedia_(0),
    pEventManager_(0),
    eventHandler(0)
{
	const char * const vlc_args[] = {
		"-I", "dumy",      // No special interface
		"--ignore-config", // Don't use VLC's config
		"--plugin-path=./plugins" };

	// init vlc modules, should be done only once
	pVLCInstance_ = libvlc_new(sizeof(vlc_args) / sizeof(vlc_args[0]), vlc_args);

    // Create a media player playing environement
    pMediaPlayer_ = libvlc_media_player_new(pVLCInstance_);

    // Create an event manager for the player for handling e.g. time change events
    pEventManager_ = libvlc_media_player_event_manager(pMediaPlayer_);
}

VLCWrapperImpl::~VLCWrapperImpl(void)
{
    // Free the media_player
    libvlc_media_player_release(pMediaPlayer_);
	libvlc_release(pVLCInstance_);
}

void VLCWrapperImpl::OpenMedia(const char* pMediaPathName)
{
	// Load a new item
	std::string strPath(pMediaPathName);
	bool bURL = false;
    std::vector<std::string> vctURL;

    vctURL.push_back("http"); 
    vctURL.push_back("https"); 
    vctURL.push_back("ftp");
    vctURL.push_back("rstp");

    for (unsigned i = 0; i < vctURL.size(); i++)
    {
        // 实际使用请判断大小写
        if (! strPath.compare(0, vctURL[i].size(), vctURL[i]))
        {
            bURL = true;
            break;
        }
    }
	if (bURL)
    {
		pMedia_ = libvlc_media_new_location(pVLCInstance_, pMediaPathName); //network media stream
	}
	else
	{
		pMedia_ = libvlc_media_new_path(pVLCInstance_, pMediaPathName); //local media
	}
    libvlc_media_player_set_media (pMediaPlayer_, pMedia_);
}

void VLCWrapperImpl::SetOutputWindow(void* pHwnd)
{
    // Set the output window    
	libvlc_media_player_set_hwnd(pMediaPlayer_, pHwnd);
}

void VLCWrapperImpl::SetEventHandler( VLCEventHandler event, void* pUserData )
{
    eventHandler = event;
    libvlc_event_attach(pEventManager_,        
                        libvlc_MediaPlayerTimeChanged,
                        eventHandler,
                        pUserData);
}

void VLCWrapperImpl::Play()
{
	// play the media_player
	if(pMediaPlayer_)
	{
		libvlc_media_player_play (pMediaPlayer_);
	}
}

void VLCWrapperImpl::Pause()
{
	// Pause playing
	if(pMediaPlayer_)
	{
		libvlc_media_player_pause (pMediaPlayer_);
	}
}

void VLCWrapperImpl::Stop()
{
    // Stop playing
	if(pMediaPlayer_)
	{
	    libvlc_media_player_stop (pMediaPlayer_);
	}
}

bool VLCWrapperImpl::IsPlaying()
{
    if (pMediaPlayer_)
    {
        return (1 == libvlc_media_player_is_playing(pMediaPlayer_));
    }
    return false;
}

void VLCWrapperImpl::FastForward()
{
    // Fast Forward 5 seconds
    if (pMediaPlayer_)
    {
        libvlc_time_t time = libvlc_media_player_get_time(pMediaPlayer_) + 5000;
		int64_t allTime = GetLength();
        if (time > allTime)
        {
            time = allTime;
        }
        libvlc_media_player_set_time(pMediaPlayer_, time);
    }
}

void VLCWrapperImpl::FastBackward()
{
    // Fast Forward 5 seconds
    if (pMediaPlayer_)
    {
        libvlc_time_t time = libvlc_media_player_get_time(pMediaPlayer_) - 5000;
        if (time < 0)
        {
            time = 0;
        }
        libvlc_media_player_set_time(pMediaPlayer_, time);
    }
}

int64_t VLCWrapperImpl::GetLength()
{
    int64_t length = libvlc_media_player_get_length(pMediaPlayer_);
    return length;
}

int64_t VLCWrapperImpl::GetTime()
{
    int64_t time = libvlc_media_player_get_time(pMediaPlayer_);    
    return time;
}

void VLCWrapperImpl::SetTime( int64_t newTime )
{
    libvlc_media_player_set_time(pMediaPlayer_,(libvlc_time_t)newTime);
}

void VLCWrapperImpl::Mute( bool mute /*= true*/ )
{
    libvlc_audio_set_mute(pMediaPlayer_, mute);
}

bool VLCWrapperImpl::GetMute()
{
    bool bMuteState=!!libvlc_audio_get_mute(pMediaPlayer_);
    return bMuteState;
}

int VLCWrapperImpl::GetVolume()
{
    int volume = libvlc_audio_get_volume(pMediaPlayer_);
    return volume;
}

void VLCWrapperImpl::SetVolume( int volume )
{
    libvlc_audio_set_volume(pMediaPlayer_, volume);
}


