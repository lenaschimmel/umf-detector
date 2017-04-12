#ifndef __UMF_UMFDEBUG_H
#define __UMF_UMFDEBUG_H

#include "singleton.h"
#include "image.h"
#include "renderer.h"
#include "../defines.h"

#include <vector>
#include <map>
#include <string>

#if defined(__WIN32__) || defined(_WIN32) || defined(__CYGWIN__)
#include <Windows.h>
#else
#include <sys/time.h>
#endif

#include <assert.h>

namespace umf
{

enum DEBUG_SHOW {
    DEBUG_SHOW_NONE = 0x0,
    DEBUG_SHOW_DIRECTIONS_BIT = 0x1,
    DEBUG_SHOW_FIELD_CENTERS_BIT = 0x2,
    DEBUG_SHOW_SCANLINES_BIT = 0x4,
    DEBUG_SHOW_UNFILTERED_LINES_BIT = 0x8,
    DEBUG_SHOW_PENCILS_BIT = 0x10,
    DEBUG_SHOW_FILTERED_LINES_BIT = 0x20,
    DEBUG_SHOW_CORNERS_BIT = 0x40,
    DEBUG_SHOW_CORRESPONDENCES_BIT = 0x80,
    DEBUG_SHOW_BOX_BIT = 0x100,
    DEBUG_SHOW_TRACKING_BIT = 0x200,
    DEBUG_SHOW_EDGELS_BIT = 0x400,
    DEBUG_SHOW_MANUAL_BIT = 0x800,

    // some internal magic to compute the "all" flag
    INT_DEBUG_SHOW_NEXT,
    INT_DEBUG_SHOW_LAST_REAL = INT_DEBUG_SHOW_NEXT - 1,
    DEBUG_SHOW_ALL = INT_DEBUG_SHOW_LAST_REAL * 2 - 1
};

/**
 * Timer for measuiring performance. Should provide nanosecond precision.
 * Don't use directly. Better to use the logged times as implemented in
 * the debug class below. 
 */
class UMF Timer {
private:

#if defined(__WIN32__) || defined(_WIN32) || defined(__CYGWIN__)
    LARGE_INTEGER startTime;
    LARGE_INTEGER frequency;
    int initialized;
#else
    timeval startTime;
#endif

public:

    Timer(){
#if defined(__WIN32__) || defined(_WIN32) || defined(__CYGWIN__)
        this->initialized = 0;
#endif

    }
    ~Timer(){}

    void start(){
#if defined(__WIN32__) || defined(_WIN32) || defined(__CYGWIN__)
        BOOL r;

        if (!initialized) {                           /* first call */
            initialized = 1;
            r = QueryPerformanceFrequency(&frequency);  /* take the sampling frequency */
            if (r == 0) {                               /* in case high-res frequency timer is not available */
                assert(0 && "HiRes timer is not available.");
                exit(-1);
            }
        }

        r = QueryPerformanceCounter(&(this->startTime));          /* take the value of the counter */
        assert(r != 0 && "This should never happen.");
#else
        gettimeofday(&startTime, NULL);
#endif
    }

    double stop(){
        double duration;
#if defined(__WIN32__) || defined(_WIN32) || defined(__CYGWIN__)
        BOOL r;
        LARGE_INTEGER value;
        r = QueryPerformanceCounter(&value); 
        assert(r != 0 && "This should never happen.");
        duration = (double)(value.QuadPart - startTime.QuadPart)*1000.0 / (double)frequency.QuadPart; /* vrat hodnotu v milisekundach */
#else
        timeval endTime;
        long seconds, useconds;

        gettimeofday(&endTime, NULL);

        seconds  = endTime.tv_sec  - startTime.tv_sec;
        useconds = endTime.tv_usec - startTime.tv_usec;

        duration = seconds*1000 + useconds/1000.0;

#endif
        return duration;
    }
};

template<typename ENUM>
class BitSet {
public:
    BitSet();
    void toggleBit(ENUM d);
    void setBit(ENUM d);
    void setBit(ENUM d, bool b);
    void clearBit(ENUM d);
    bool isBitSet(ENUM d);

private:
    ENUM value;
};

/**
 * Debug and Performance evaluation helper. Also provides interface for accessing the renderer
 * for debug purposes (drawing lines, points).
 */
class UMF UMFDebug
{
public:
    UMFDebug();

    void setRenderer(Renderer *r){ this->renderer = r; }
    Renderer *getRenderer(){ return this->renderer; }

    //PIXEL counter
#ifdef UMF_DEBUG_COUNT_PIXELS
    void addPixels(int count) { this->pixelCount += count; }
    long long getPixels() { return this->pixelCount; }
#endif

#ifdef UMF_DEBUG_TIMING
    //TIMING loger
    
    /**
     * Start a timer - an ID is returned for further use
     */
    int logEventStart();
    
    /**
     * Tag the end of the timer given by ID. the messages are groupped
     */
    void logEventEnd(int id, std::string message);
    
    /**
     * More verbose and direct way of logging events
     * @param time in milliseconds
     */
    void logEvent(double time, std::string name);
    
    /**
     * Get all logged events from the beginning of the program
     */
    std::vector< std::pair<double, std::string> > &getEvents(){return this->timeEvents;}
    
    /**
     * Fill the vector with all the events
     */
    void getTimeLog(std::vector< std::pair<double, std::string> > &events);

    /**
     * Group by message and compute the average time for all events
     */
    void getUniqLog(std::vector< std::pair<double, std::string> > &events);

    void clearEvents();
#endif

	void setReasonFailed(std::string reason) { this->failedReason = reason; }
	std::string getReasonFailed() { return this->failedReason; }

    //platform independent log (android + stdout)
    static void logMsg(std::string message);

    BitSet<DEBUG_SHOW> debugShowBits;

private:
    Renderer *renderer;
    long long pixelCount;

    //timing stuff
    std::vector< std::pair<double, std::string> > timeEvents;
    std::map<int, Timer> startTick;
    std::map< std::string, std::pair<int, double> > eventMap;
    int prevID;
	std::string failedReason;
    //timing stuff ent

};


typedef Singleton<UMFDebug> UMFDSingleton;

}

#endif // UMFDEBUG_H
