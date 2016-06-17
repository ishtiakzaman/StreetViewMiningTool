#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <math.h>
#include <CImg.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <time.h>

using namespace cimg_library;
using namespace std;

string getCurrentDateTime()
{
    time_t current_time = time(0);    
    char return_time[100];
    struct tm tmstr;
    tmstr = *localtime(&current_time);
    strftime(return_time, sizeof(return_time), "%Y_%m_%d_%X", &tmstr);
    return return_time;
}

void show_usage(string program_name)
{
    cout << "Usage: " << program_name << endl <<
        "-f filename" << endl <<
        "[-i latitude column in file (default 0)]" << endl <<
        "[-j longitude column in file (default 1)]" << endl <<
        "[-t delimiter between columns in file (default ',')]"  << endl <<
        "[-w width (default 640, maximum allowed limit 640)]"  << endl <<
        "[-h height (default 640, maximum allowed limit 640)]"  << endl <<
        "[-d direction1,direction2,...,directionn (default 0,90,180,270; 0 is NORTH, 90 is EAST etc.)]" << endl <<
        "[-a angle of view (default 90)]"  << endl <<
        "[-p pitch (default 0)]" << endl;
}

int main(int argc, char *argv[])
{
    
    /*  
        Google Street View API key for ishtiak.zaman@gmail.com 
        Restricted for limited free usage only
    */ 
    const string api_key = "AIzaSyBTQmmD0KLx8bMU3PFaUosUMcLq9mZDaKo";


    int opt;
    string file_name, directions = "0,90,180,270";
    char delimiter = ',';
    double pitch = 0;
    int angle = 90, lat_col = 0, lng_col = 1, width = 640, height = 640;
    istringstream iss;
    while ((opt = getopt(argc, argv, "f:d:a:p:i:j:w:h:t:h")) != -1)
    {
        switch (opt)
        {
        case 'f':
            file_name = optarg;
            break;
        case 'd':
            directions = optarg;           
            break;
        case 'a':
            iss.str(optarg);
            iss >> angle;
            break;
        case 'p':
            iss.str(optarg);
            iss >> pitch;
            break;
        case 'w':
            iss.str(optarg);
            iss >> width;
            break;
        case 'h':
            iss.str(optarg);
            iss >> height;
            break;
        case 't':
            iss.str(optarg);
            iss >> delimiter;
            break;
        case 'i':
            iss.str(optarg);
            iss >> lat_col;
            break;
        case 'j':
            iss.str(optarg);
            iss >> lng_col;
            break;        
        default: /* '?' */
            show_usage(argv[0]);
            exit(EXIT_FAILURE);
        }
        iss.clear();
    }    

    string token;
    vector<int> heading_list;
    iss.str(directions);
    while (getline(iss, token, ','))
    {
        istringstream iss2(token);
        int dir;
        iss2 >> dir;
        heading_list.push_back(dir);
    }
    iss.clear();
    
    string directory_name = "street_view_images_" + getCurrentDateTime();
    string cmd = "mkdir " + directory_name;
    system(cmd.c_str());

    ifstream fs(file_name.c_str());
    if (fs.is_open() == false)
    {
        cout << "Failed to read file " << file_name << endl;
        show_usage(argv[0]);
        exit(EXIT_FAILURE); 
    }
    string line;
    int file_counter = 1;
    while (getline(fs, line))
    {
        if (line.size() == 0)
            continue;
        iss.str(line);
        vector<string> line_tokens;
        while (getline(iss, token, delimiter))
        {
            line_tokens.push_back(token);
        } 
        iss.clear(); 
        if (line_tokens.size() > 0 && line_tokens[0][0] == '#')
            continue;        

        double latitude, longitude;
        iss.str(line_tokens[lat_col]);
        iss >> latitude;
        iss.clear();
        iss.str(line_tokens[lng_col]);
        iss >> longitude;
        iss.clear();
        for (int i = 0; i < heading_list.size(); ++i)
        {
            ostringstream oss;
            oss << "https://maps.googleapis.com/maps/api/streetview?";
            oss << "size=" << width << "x" << height << "&";
            oss << "location=" << latitude << "," << longitude << "&";
            oss << "heading=" << heading_list[i] << "&";
            oss << "pitch=" << pitch;
            oss << "key=" << api_key;
            string image_link = oss.str();

            cout << "Getting street view of lat " << latitude << ", lng " << longitude << ", heading " << heading_list[i] << endl;
            
            CImg<double> image(image_link.c_str());
            oss.str("");
            oss.clear();
            oss << directory_name << "/sv" << file_counter++ << ".jpg";
            string file_name = oss.str();
            image.save(file_name.c_str());
        }
    }
    
    return 0;
}