#ifndef __ZHELPERS_HPP_INCLUDED__
#define __ZHELPERS_HPP_INCLUDED__

#include <zmq.hpp> // https://github.com/zeromq/cppzmq

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>

#include <time.h>
#include <assert.h>
#include <stdlib.h>        // random()  RAND_MAX
#include <stdio.h>
#include <stdarg.h>
#include <signal.h>

#if (!defined(WIN32))
#   include <sys/time.h>
#   include <unistd.h>
#endif

//  Bring Windows MSVC up to C99 scratch
#if (defined (WIN32))
    typedef unsigned long ulong;
    typedef unsigned int  uint;
    typedef __int64 int64_t;
#endif

//  On some version of Windows, POSIX subsystem is not installed by default.
//  So define srandom and random ourself.
//  
#if (defined (WIN32))
#   define srandom srand
#   define random rand
#endif

// Visual Studio versions below 2015 do not support sprintf properly. This is a workaround.
// Taken from http://stackoverflow.com/questions/2915672/snprintf-and-visual-studio-2010
#if defined(_MSC_VER) && _MSC_VER < 1900

#define snprintf c99_snprintf
#define vsnprintf c99_vsnprintf

	inline int c99_vsnprintf(char *outBuf, size_t size, const char *format, va_list ap)
	{
		int count = -1;

		if (size != 0)
			count = _vsnprintf_s(outBuf, size, _TRUNCATE, format, ap);
		if (count == -1)
			count = _vscprintf(format, ap);

		return count;
	}

	inline int c99_snprintf(char *outBuf, size_t size, const char *format, ...)
	{
		int count;
		va_list ap;

		va_start(ap, format);
		count = c99_vsnprintf(outBuf, size, format, ap);
		va_end(ap);

		return count;
	}

#endif

static std::string s_recv(zmq::socket_t &socket) {
    zmq::message_t message;
    socket.recv(&message);

    return std::string(static_cast<char*>(message.data()), message.size());
}

//  Provide random number from 0..(num-1)
#define within(num) (int) ((float) (num) * random () / (RAND_MAX + 1.0))

#endif