/******************************************************************
This file is part of https://github.com/martinruenz/sens-viewer

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as
published by the Free Software Foundation, version 3.

This program is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.
*****************************************************************/

#include <cstddef>
#include <iostream>
#include "external/sensorData.h"

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

typedef std::chrono::time_point<std::chrono::system_clock> Timepoint;
typedef std::chrono::duration<double> Duration;
typedef std::chrono::system_clock Clock;

int main(int argc, char* argv[])
{

    try {
        //non-cached read
        string filename;
        if (argc == 2) filename = string(argv[1]);
        else {
            cout << "use ./sens-viewer <filename>" << endl;
            return 1;
        }

        cout << "Loading data ... ";
        cout.flush();
        ml::SensorData sd(filename);
        cout << "done!" << endl;
        cout << sd << endl;

        for (size_t i = 0; i < sd.m_frames.size(); i++) {

            Timepoint t = Clock::now();

            //de-compress color and depth values
            ml::vec3uc* colorData = sd.decompressColorAlloc(i);
            unsigned short* depthData = sd.decompressDepthAlloc(i);

            Mat depth_raw(sd.m_depthHeight, sd.m_depthWidth, CV_16UC1, depthData);
            Mat rgb(sd.m_colorHeight, sd.m_colorWidth, CV_8UC3, (unsigned char*)colorData);
            cvtColor(rgb, rgb, CV_BGR2RGB);
            Mat depth;
            depth_raw.convertTo(depth, CV_16UC1, 20);

            cv::imshow("Depth", depth);
            cv::waitKey(1);
            cv::imshow("RGB", rgb);
            cv::waitKey(1);

            free(colorData);
            free(depthData);

            Duration d = Clock::now() - t;
            cout << "Playback speed: " <<  1.0f / d.count() << "Hz\r";
            cout.flush();
        }

        cout << endl;
    }catch (const exception& e){
        cout << "Exception " << e.what() << endl;
        return 1;
    }catch (...){
        cout << "Exception (unknown)";
        return 1;
    }

    return 0;
}
