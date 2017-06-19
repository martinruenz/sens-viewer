/******************************************************************
This file is part of https://github.com/martinruenz/dataset-tools

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>
*****************************************************************/

#include <cstddef>
#include <iostream>
#include "external/sensorData.h"

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

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
        ml::SensorData sd(filename);
        cout << "done!" << endl;
        cout << sd << endl;

        for (size_t i = 0; i < sd.m_frames.size(); i++) {

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
