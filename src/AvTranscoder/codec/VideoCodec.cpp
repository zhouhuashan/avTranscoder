#include "VideoCodec.hpp"

#include <cassert>

namespace avtranscoder
{

VideoCodec::VideoCodec( const ECodecType type, const std::string& codecName )
	: ICodec( type, codecName )
{
}

VideoCodec::VideoCodec( const ECodecType type, const AVCodecID codecId )
	: ICodec( type, codecId )
{
}

VideoCodec::VideoCodec( const ECodecType type, AVCodecContext& avCodecContext )
	: ICodec( type, avCodecContext )
{
}

VideoCodec::VideoCodec( const ICodec& codec )
	: ICodec( codec )
{
}

VideoFrameDesc VideoCodec::getVideoFrameDesc() const
{
	assert( _avCodecContext != NULL );
	VideoFrameDesc videoFrameDesc( _avCodecContext->width, _avCodecContext->height, _avCodecContext->pix_fmt );
	return videoFrameDesc;
}

std::pair< size_t, size_t > VideoCodec::getTimeBase() const
{
	assert( _avCodecContext != NULL );
	std::pair< size_t, size_t > timeBase;
	timeBase.first = _avCodecContext->time_base.num;
	timeBase.second = _avCodecContext->time_base.den;
	return timeBase;
}

void VideoCodec::setImageParameters( const VideoFrameDesc& videoFrameDesc )
{
	setImageParameters( videoFrameDesc.getWidth(), videoFrameDesc.getHeight(), videoFrameDesc.getPixelFormat() );
}

void VideoCodec::setImageParameters( const size_t width, const size_t height, const AVPixelFormat& pixel )
{
	_avCodecContext->width = width;
	_avCodecContext->height = height;
	_avCodecContext->pix_fmt = pixel;
}

void VideoCodec::setTimeBase( const size_t num, const size_t den, const size_t ticksPerFrame )
{
	_avCodecContext->time_base.num = num;
	_avCodecContext->time_base.den = den;
	_avCodecContext->ticks_per_frame = ticksPerFrame;
}

}
