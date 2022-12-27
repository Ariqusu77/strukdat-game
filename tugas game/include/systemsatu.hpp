#ifndef __SYSTEM_SATU_HPP__
#define __SYSTEM_SATU_HPP__

#pragma once

const int koordinat[28][2] = {
    {0,10},{4,9},{6,8},{7,7},{8,6},{9,4},{10,0},
    {10,0},{9,-4},{8,-6},{7,-7},{6,-8},{4,-9},{0,-10},
    {0,-10},{-4,-9},{-6,-8},{-7,-7},{-8,-6},{-9,-4},{-10,0},
    {-10,0},{-9,4},{-8,6},{-7,7},{-6,8},{-4,9},{0,10},
};

struct location{
    int x;
    int y;

    int data[32][32];
    bool data_reserved = false;

    int x_center;
    int y_center;
};

class Noisenode {
public:
    int panjang;
    int putar;
    int diameter;

    location* Nloct;

    Noisenode* up;
    Noisenode* down;
    Noisenode* right;
    Noisenode* left;

    Noisenode(int panj, int sudt, int x1, int y1);  

    void Noise_down_expand();
    void Noise_up_expand();
    void Noise_right_expand();
    void Noise_left_expand();

    void Noise_rightup_expand();
    void Noise_leftup_expand();
    void Noise_rightdown_expand();
    void Noise_leftdown_expand();

    void Render_noisenode();
};

class Noisesystem {
public:
    Noisenode* seed;
    Noisenode* pointing;
    Noisenode* playerpoint;

    Noisenode* point_x_plus;
    Noisenode* point_x_minus;
    Noisenode* point_y_plus;
    Noisenode* point_y_minus;

    int renderred_maps_data[96][96];

    Noisesystem(int random1, int random2);

    void Generating_noise(int sisi);
    void Rendering_noise(int sisi);

    void Expand_down_horizontal();
    void Expand_up_horizontal();
    void Expand_right_vertical();
    void Expand_left_vertical();
};

#endif