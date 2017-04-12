#include "successlogger.h"
#include <string>
#include <fstream>

void SuccessLogger::store(std::string outDir, std::string filename_short)
{
    std::string diff_name = outDir + filename_short + std::string(".diffs.txt");
    std::sort(this->frameDiffs.begin(), this->frameDiffs.end());
    std::fstream successOut(diff_name.c_str(), std::fstream::out);
    double fullSize = this->frameDiffs.size();
    int index = 0;
    for(std::vector<int>::iterator it = this->frameDiffs.begin(); it != this->frameDiffs.end(); it++, index++)
    {
        successOut << *it << " " << index/fullSize << std::endl;
    }
    successOut.close();

    std::fstream successOutPlot((diff_name + std::string(".p")).c_str(), std::fstream::out);

    successOutPlot << "set key right bottom \n";
    successOutPlot << "set auto\n";
    successOutPlot << "\n";


    successOutPlot << "set style line 1 lt 1 lw 1 lc rgb \"red\"\n";
    successOutPlot << "set style line 2 lt 2 lw 1 lc rgb \"green\"\n";
    successOutPlot << "set style line 3 lt 3 lw 1 lc rgb \"blue\"\n";
    successOutPlot << "set style line 4 lt 4 lw 1 lc rgb \"purple\"\n";
    successOutPlot << "set style line 5 lt 5 lw 1 lc rgb \"cyan\"\n";
    successOutPlot << "set style line 6 lt 6 lw 1 lc rgb \"orange\"\n";

    successOutPlot << "set lmargin 5.0\n";
    successOutPlot << "set bmargin 2.5\n";
    successOutPlot << "set rmargin 0.5\n";
    successOutPlot << "set tmargin 0.5\n";

    successOutPlot << "\n";
    successOutPlot << "set xrange[0:20]\n";
    successOutPlot << "set yrange[0: 1]\n";
    successOutPlot << "set xtics 5\n";

    successOutPlot << "\n";
    successOutPlot << "# Make some suitable labels.\n";
    //successOutPlot << "set notitle\n";
    successOutPlot << "set xlabel \"Missed frame count\" offset 0.0, 0.5\n";
    successOutPlot << "set ylabel \"Probability distribution\" offset 2.7, 0.0\n";
    successOutPlot << "set terminal postscript eps enhanced color \"Times-Roman\" 25\n";
    successOutPlot << "set output '| epstopdf --filter --outfile=" << (diff_name + std::string(".pdf")) << "'\n";


    successOutPlot << " plot '" << diff_name << "' using 1:2 title '"<< filename_short << "' with lines\n";

    successOutPlot << "\n";
    successOutPlot.close();
}
