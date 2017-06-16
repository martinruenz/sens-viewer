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

#include "external/sensorData.h"

using namespace std;
//using namespace cv;

int main(int argc, char * argv[])
{


    return 0;
}


//THIS IS A DEMO FUNCTION: HOW TO DECODE .SENS FILES: CHECK IT OUT! (doesn't do anything real though)
void processFrame(const ml::SensorData& sd, size_t frameIdx) {

    //de-compress color and depth values
    ml::vec3uc* colorData = sd.decompressColorAlloc(frameIdx);
    unsigned short* depthData = sd.decompressDepthAlloc(frameIdx);

    //dimensions of a color/depth frame
    sd.m_colorWidth;
    sd.m_colorHeight;
    sd.m_depthWidth;
    sd.m_depthHeight;

    for (unsigned int i = 0; i < sd.m_depthWidth * sd.m_depthHeight; i++) {
        //convert depth values to m:
        float depth_in_meters = sd.m_depthShift * depthData[i];
    }

    std::free(colorData);
    std::free(depthData);
}


int main(int argc, char* argv[])
{

    try {
        //non-cached read
        std::string filename = "scene0001_00.sens";
        std::string outDir = "./out/";
        if (argc >= 2) filename = std::string(argv[1]);
        else {
            std::cout << "run ./sens <sensfilename>.sens";
            std::cout << "type in filename manually: ";
            std::cin >> filename;
        }
        if (argc >= 3) outDir = std::string(argv[2]);

        std::cout << "filename =\t" << filename << std::endl;
        std::cout << "outDir =\t" << outDir << std::endl;

        std::cout << "loading from file... ";
        ml::SensorData sd(filename);
        std::cout << "done!" << std::endl;

        std::cout << sd << std::endl;

        // color frames are written out as 'jpgs' and depth frames as binary dumps: <width : uint32, height : uint32, unsigned short* data>
        sd.saveToImages(outDir);

        //THIS SHOWS HOW DE-COMPRESSION WORKS
        //for (size_t i = 0; i < sd.m_frames.size(); i++) {
        {
            size_t i = 0;
            //std::cout << "\r[ processing frame " << std::to_string(i) << " of " << std::to_string(sd.m_frames.size()) << " ]";
            processFrame(sd, i);
        }


        std::cout << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cout << "Exception " << e.what() << std::endl;
        return 1;
    }
    catch (...)
    {
        std::cout << "Exception (unknown)";
        return 1;
    }

    std::cout << "All done :)" << std::endl;

    return 0;
}
