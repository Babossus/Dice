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

    void curnal() { // & Referenz



        for (int i = 1; i < height - 1; i++) {
            for (int j = 1; j < width - 1; j++) {
                
                // curnal x
                pixel_x.r = (picture[i - 1][j - 1].r * - 1) + 
                            (picture[i - 1][j].r * - 2) +
                            (picture[i - 1][j + 1].r * - 1) +
                            (picture[i + 1][j - 1].r * 1) +
                            (picture[i + 1][j].r * 2) +
                            (picture[i + 1][j + 1].r * 1);

                pixel_x.g = (picture[i - 1][j - 1].g * -1) +
                            (picture[i - 1][j].g * -2) +
                            (picture[i - 1][j + 1].g * -1) +
                            (picture[i + 1][j - 1].g * 1) +
                            (picture[i + 1][j].g * 2) +
                            (picture[i + 1][j + 1].g * 1);

                pixel_x.b = (picture[i - 1][j - 1].b * -1) +
                            (picture[i - 1][j].b * -2) +
                            (picture[i - 1][j + 1].b * -1) +
                            (picture[i + 1][j - 1].b * 1) +
                            (picture[i + 1][j].b * 2) +
                            (picture[i + 1][j + 1].b * 1);
                
                // curnal y
                pixel_y.r = (picture[i - 1][j - 1].r * -1) +
                            (picture[i][j - 1].r * -2) +
                            (picture[i + 1][j - 1].r * -1) +
                            (picture[i - 1][j + 1].r * 1) +
                            (picture[i][j + 1].r * 2) +
                            (picture[i + 1][j + 1].r * 1);

                pixel_y.g = (picture[i - 1][j - 1].g * -1) +
                            (picture[i][j - 1].g * -2) +
                            (picture[i + 1][j - 1].g * -1) +
                            (picture[i - 1][j + 1].g * 1) +
                            (picture[i][j + 1].g * 2) +
                            (picture[i + 1][j + 1].g * 1);

                pixel_y.b = (picture[i - 1][j - 1].b * -1) +
                            (picture[i][j - 1].b * -2) +
                            (picture[i + 1][j - 1].b * -1) +
                            (picture[i - 1][j + 1].b * 1) +
                            (picture[i][j + 1].b * 2) +
                            (picture[i + 1][j + 1].b * 1);
                
                // vertikal und Horizontal zusammenführen
                pixel.r = sqrt(pow(pixel_x.r, 2) + pow(pixel_y.r, 2));
                pixel.g = sqrt(pow(pixel_x.g, 2) + pow(pixel_y.g, 2));
                pixel.b = sqrt(pow(pixel_x.b, 2) + pow(pixel_y.b, 2));  

                picture_row.push_back(pixel);
            }

            picture_curnal.push_back(picture_row);
            picture_row.clear();
        }

        // jewils 2 entfernen da der rand nicht Bearbeitet wurde 
        height -= 2;
        width -= 2;
        


    }

    void black_white(int turn) {

        rgb black;
        rgb white;

        black.r = 0;
        black.g = 0;
        black.b = 0;
        white.r = 255;
        white.g = 255;
        white.b = 255;

        int Filter;
        if (turn == 1) {
            picture_temp = picture_curnal;
            Filter = 240; // muss bei der Box geändert werden
        }
        if (turn == 2) {
            picture_bw.clear();
            picture_temp = picture;// picture_cut;
            Filter = 50/*40*/;
        }
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if ((picture_temp[i][j].r + picture_temp[i][j].g + picture_temp[i][j].b) / 3 < Filter) { // durchschnitt

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

    // vllt for schleifen wechsenl
    void mark_dice() {

        // oben zu Würfel
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (picture_bw[i][j].r == 255) {
                    coords.push_back(i);
                    i = height;
                    j = width;
                }
            }
        }

        // unten zu Würfel
        for (int i = height-1; i > 0; i--) {
            for (int j = 0; j < width; j++) {
                if (picture_bw[i][j].r == 255) {
                    coords.push_back(i);
                    i = 0;
                    j = width;
                }
            }
        }

        // links zu Würfel
        for (int i = 0; i < width; i++) {
            for (int j = 0; j < height; j++) {
                if (picture_bw[j][i].r == 255) {
                    coords.push_back(i);
                    i = width;
                    j = height;
                }
            }
        }

        // rechts zu Würfel
        for (int i = width-1; i > 0; i--) {
            for (int j = 0; j < height; j++) {
                if (picture_bw[j][i].r == 255) {
                    coords.push_back(i);
                    i = 0;
                    j = height;
                }
            }
        }
    }

    void cut_dice() {

        // coords[oben][unten][links][rechts]
        for (int i = coords[0]; i < coords[1]; i++) { // von Lins nach Rechts
            for (int j = coords[2]; j < coords[3]; j++) { // von oben nach unten      
                picture_row.push_back(picture[i][j]);
            }
            picture_cut.push_back(picture_row);
            picture_row.clear();
        }

        height = coords[1] - coords[0];
        width = coords[3] - coords[2];
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
        cout << percentage << endl;
        
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
        convert.set_picture(pictture_bw/*picture_bw*/); // kommt auf stand an
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