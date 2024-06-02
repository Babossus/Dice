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

    void curnal(convert &convert) { // & Referenz

        width = convert.get_width();
        height = convert.get_height();
        picture = convert.get_picture();

        for (int i = 1; i < width - 1; i++) {
            for (int j = 1; j < height - 1; j++) {
                
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
                pixel.r = sqrt(pow(pixel_x.r, 2) +pow(pixel_y.r, 2));
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

    void black_white() {

        rgb black;
        rgb white;

        black.r = 0;
        black.g = 0;
        black.b = 0;
        white.r = 255;
        white.g = 255;
        white.b = 255;

        for (int i = 0; i < width; i++) {
            for (int j = 0; j < height; j++) {
                if ((picture_curnal[i][j].r + picture_curnal[i][j].g + picture_curnal[i][j].b) / 3 < 127) { // durchschnitt

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
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                if (picture_bw[j][i].r == 255) // ppm_matrix[x][y]
                {
                    coords.push_back(i);
                }
            }
        }

        // unten zu Würfel
        for (int i = height; i < 0; i--)
        {
            for (int j = 0; j < width; j++)
            {
                if (picture_bw[j][i].r == 255)
                {
                    coords.push_back(i);
                }
            }
        }

        // links zu Würfel
        for (int i = 0; i < width; i++)
        {
            for (int j = 0; j < height; j++)
            {
                if (picture_bw[i][j].r > 255)
                {
                    coords.push_back(j);
                }
            }
        }

        // rechts zu Würfel
        for (int i = width; i < 0; i--)
        {
            for (int j = 0; j < height; j++)
            {
                if (picture_bw[i][j].r == 255)
                {
                    coords.push_back(j);
                }
            }
        }
    }

    void cut_dice() { // !!!!!!! hier vielleicht eine  andere version des Bildes Zuschneiden und nutzen?

        // coords[oben][unten][links][rechts]
        for (int i = coords[1]; i < coords[3]; i++) { // von Lins nach Rechts
            for (int j = coords[0]; j < coords[2]; j++) // von oben nach unten
            {
                picture_row.push_back(picture_bw[i][j]);
            }
            picture_dice.push_back(picture_row);
            picture_row.clear();
        }

        height = coords[2] - coords[0];
        width = coords[3] - coords[1];
    }

    void transfer(convert &convert) {
        convert.set_height(height);
        convert.set_width(width);
        convert.set_picture(picture_curnal); // kommt auf stand an
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
    vector<vector<rgb>> picture_dice;
    vector<rgb> picture_row;
    vector<int> coords;
};