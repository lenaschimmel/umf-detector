#ifndef _UMF_SUCCESSLOGGER_H_
#define _UMF_SUCCESSLOGGER_H_

#include <vector>
#include "../umf.h"

using namespace umf;

class SuccessLogger {
public:
    SuccessLogger(float fps = 20) {
        this->current = 1;
        this->onepfps = 1000.0f/fps;
        this->detectSum = 0;
    }
    
    void detectStart()
    {
        this->timer.start();
    }

    void addFailure()
    {
        //std::cout << "Failure." << std::endl;
        this->detectSum += (std::max)(0.0, this->timer.stop() - this->onepfps);
    }
    
    void addSuccess(int frameId)
    {
        //std::cout << "Success." << std::endl;
		this->detectSum += this->timer.stop();
        int diff = frameId - current - 1;
        //frameDiffs.push_back(diff*onepfps + detectSum);
        frameDiffs.push_back(diff);
        this->detectSum = 0;
        this->current = frameId;
    }

    void store(std::string outDir, std::string filename_short);

private:
    std::vector<int> frameDiffs;
    Timer timer;
    float onepfps;
    int current;
    double detectSum;
};

#endif