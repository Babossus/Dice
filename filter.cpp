#include <conio.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <math.h>

#include "read_write.cpp"
using namespace std;


class mask
{
public:

    void get(convert& convert) {
        width = convert.get_width();
        height = convert.get_height();
        picture = convert.get_picture();
    }


    void black_white() {

        rgb black;
        rgb white;

        black.r = 0;
        black.g = 0;
        black.b = 0;
        white.r = 255;
        white.g = 255;
        white.b = 255;

        picture_temp = picture;

        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if ((picture_temp[i][j].r + picture_temp[i][j].g + picture_temp[i][j].b) / 3 < 240) { // durchschnitt

                    picture_row.push_back(black);
                }
                else {
                    picture_row.push_back(white);
                }
            }

            picture_bw.push_back(picture_row);
            picture_row.clear();
        }
    }

 

    void Black_percentage() {
        int black = 0;
        int white = 0;
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (picture_bw[i][j].r == 0) {
                    black++;
                }
                else {
                    white++;
                }
            }
        }
        int totalPixels = width * height;
        double percentage = static_cast<double>(black) / totalPixels * 100.0;
        
        if (percentage > 0.008 && percentage < 0.013) {
            cout << "1\n\n";
        }
        else if (percentage > 0.015 && percentage < 0.02) {
            cout << "2\n\n";
        }
        else if (percentage > 0.03 && percentage < 0.035) {
            cout << "3\n\n";
        }
        else if (percentage > 0.035 && percentage < 0.04) {
            cout << "4\n\n";
        }
        else if (percentage > 0.065 && percentage < 0.07) {
            cout << "5\n\n";
        }
        else if (percentage > 0.05 && percentage < 0.055) {
            cout << "6\n\n";
        }
    }

    void transfer(convert& convert) {
        convert.set_height(height);
        convert.set_width(width);
        convert.set_picture(picture_bw/*picture_bw*/); // kommt auf stand an
    }

private:
    int width;
    int height;
    rgb pixel;
    rgb pixel_x;
    rgb pixel_y;
    vector<vector<rgb> > picture;
    vector<vector<rgb> > picture_curnal;
    vector<vector<rgb>> picture_bw;
    vector<vector<rgb>> picture_cut;
    vector<vector<rgb>> picture_temp;
    vector<rgb> picture_row;
    vector<int> coords;
};