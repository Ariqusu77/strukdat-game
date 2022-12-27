#include <systemsatu.hpp>
#include <iostream>
#include <cmath>

//Noisenode Series
//Constructor
Noisenode::Noisenode(int panj, int sudt, int x1, int y1){
    this->panjang = 5+ panj%6;
    this->putar = sudt%28 + 1;
    this->diameter = 15 - this->panjang;

    this->Nloct = new location;

    this->Nloct->x = x1;
    this->Nloct->y = y1;

    this->up = NULL;
    this->down = NULL;
    this->right = NULL;
    this->left = NULL;    
}

//Create a node at up relative to reference
void Noisenode::Noise_up_expand(){
    if(this->up == NULL){
        srand(this->panjang);
        this->up = new Noisenode(rand(),rand(), 0, this->Nloct->y +1);
        this->up->down = this;
    }else{
        return;
    }
}

//Create a node at down relative to reference
void Noisenode::Noise_down_expand(){
    if(this->down == NULL){
        srand(this->panjang + this->putar);
        this->down = new Noisenode(rand(),rand(), 0, this->Nloct->y -1);
        this->down->up = this;
    }else{
        return;
    }
}

//Create a node at right relative to reference
void Noisenode::Noise_right_expand(){
    if(this->right == NULL){
        srand(this->putar);
        this->right = new Noisenode(rand(),rand(), this->Nloct->x +1, 0);
        this->right->left = this;
    }else{
        return;
    }
}

//Create a node at left relative to reference
void Noisenode::Noise_left_expand(){
    if(this->left == NULL){
        srand(this->putar * this->panjang);
        this->left = new Noisenode(rand(),rand(), this->Nloct->x -1, 0);
        this->left->right = this;
    }else{
        return;
    }
}

//Create a node at right up relative to reference
void Noisenode::Noise_rightup_expand(){
    if(this->right == NULL && this->up == NULL){
        return;
    }else{
    Noisenode& Noise_right = *this->right;
    Noisenode& Noise_up = *this->up;

    this->right->up = new Noisenode(Noise_right.panjang*Noise_up.panjang, Noise_right.putar*Noise_up.putar, Noise_right.Nloct->x, Noise_up.Nloct->y);
    this->up->right = this->right->up;

    Noisenode& Target_noise = *this->right->up;
    Target_noise.left = this->up;
    Target_noise.down = this->right;
    }
}

//Create a node at right down relative to reference
void Noisenode::Noise_rightdown_expand(){
    if(this->right == NULL && this->down == NULL){
        return;
    }else{
    Noisenode& Noise_right = *this->right;
    Noisenode& Noise_down = *this->down;

    this->right->down = new Noisenode(Noise_right.panjang*Noise_down.panjang, Noise_right.putar*Noise_down.putar, Noise_right.Nloct->x, Noise_down.Nloct->y);
    this->down->right = this->right->down;

    Noisenode& Target_noise = *this->right->down;
    Target_noise.left = this->down;
    Target_noise.up = this->right;
    }
}

//Create a node at left up relative to reference
void Noisenode::Noise_leftup_expand(){
    if(this->left == NULL && this->up == NULL){
        return;
    }else{
    Noisenode& Noise_left = *this->left;
    Noisenode& Noise_up = *this->up;

    this->left->up = new Noisenode(Noise_left.panjang*Noise_up.panjang, Noise_left.putar*Noise_up.putar, Noise_left.Nloct->x, Noise_up.Nloct->y);
    this->up->left = this->left->up;

    Noisenode& Target_noise = *this->left->up;
    Target_noise.right = this->up;
    Target_noise.down = this->left;
    }
}

//Create a node at left down relative to reference
void Noisenode::Noise_leftdown_expand(){
    if(this->left == NULL && this->down == NULL){
        return;
    }else{
    Noisenode& Noise_left = *this->left;
    Noisenode& Noise_down = *this->down;

    this->left->down = new Noisenode(Noise_left.panjang*Noise_down.panjang, Noise_left.putar*Noise_down.putar, Noise_left.Nloct->x, Noise_down.Nloct->y);
    this->down->left = this->left->down;

    Noisenode& Target_noise = *this->left->down;
    Target_noise.right = this->down;
    Target_noise.up = this->left;
    }
}

//Render a node
void Noisenode::Render_noisenode(){
    if(!this->Nloct->data_reserved){
        this->Nloct->x_center =16+ this->panjang* koordinat[this->putar -1][0]/ 10;
        this->Nloct->y_center =16+ this->panjang* koordinat[this->putar -1][1]/ 10;

        for(auto i=0; i< 2*this->diameter +1; i++){
            for(auto j=0; j< 2*this->diameter +1; j++){
                if((this->diameter -i)*(this->diameter -i) + (this->diameter -j)*(this->diameter -j) > this->diameter*this->diameter){
                    this->Nloct->data[this->Nloct->y_center - this->diameter + i][this->Nloct->x_center - this->diameter + j]=0;
                }else{
                    this->Nloct->data[this->Nloct->y_center - this->diameter + i][this->Nloct->x_center - this->diameter + j]= 8 / (sqrt((this->diameter -i)*(this->diameter -i) + (this->diameter -j)*(this->diameter -j))+1) + 1;
                }
            }
        }

        this->Nloct->data_reserved = true;
    }else{
        return;
    }
}

//Noisesystem
//Constructor
Noisesystem::Noisesystem(int random1, int random2){
    this->seed = new Noisenode(random1, random2, 0, 0);
    this->pointing = this->seed;
    this->playerpoint = this->seed;
}

//Generate all necessary node
void Noisesystem::Generating_noise(int sisi){

    //expand domain vertical and horizontal
    for(int i=0; i<sisi; i++){
        for(int j=0; j<i; j++){
            this->pointing = this->pointing->up;
        }
        this->pointing->Noisenode::Noise_up_expand();
        this-> point_y_plus = this->pointing->up;
        this->pointing = this->seed;

        for(int j=0; j<i; j++){
            this->pointing = this->pointing->right;
        }
        this->pointing->Noisenode::Noise_right_expand();
        this->point_x_plus = this->pointing->right;
        this->pointing = this->seed;

        for(int j=0; j<i; j++){
            this->pointing = this->pointing->down;
        }
        this->pointing->Noisenode::Noise_down_expand();
        this->point_y_minus = this->pointing->down;
        this->pointing = this->seed;

        for(int j=0; j<i; j++){
            this->pointing = this->pointing->left;
        }
        this->pointing->Noisenode::Noise_left_expand();
        this->point_x_minus = this->pointing->left;
        this->pointing = this->seed;
    }

    //expand domain right up
    for(int i=0; i<sisi; i++){
        for(int j=0; j<sisi; j++){
            for(int k=0; k<i; k++){
                this->pointing = this->pointing->right;
            }
            for(int l=0; l<j; l++){
                this->pointing = this->pointing->up;
            }
            this->pointing->Noisenode::Noise_rightup_expand();
            this->pointing = this->seed;
        }
    }

    //expand domain right down
    for(int i=0; i<sisi; i++){
        for(int j=0; j<sisi; j++){
            for(int k=0; k<i; k++){
                this->pointing = this->pointing->right;
            }
            for(int l=0; l<j; l++){
                this->pointing = this->pointing->down;
            }
            this->pointing->Noisenode::Noise_rightdown_expand();
            this->pointing = this->seed;
        }
    }

    //expand domain left up
    for(int i=0; i<sisi; i++){
        for(int j=0; j<sisi; j++){
            for(int k=0; k<i; k++){
                this->pointing = this->pointing->left;
            }
            for(int l=0; l<j; l++){
                this->pointing = this->pointing->up;
            }
            this->pointing->Noisenode::Noise_leftup_expand();
            this->pointing = this->seed;
        }
    }

    //expand domain left down
    for(int i=0; i<sisi; i++){
        for(int j=0; j<sisi; j++){
            for(int k=0; k<i; k++){
                this->pointing = this->pointing->left;
            }
            for(int l=0; l<j; l++){
                this->pointing = this->pointing->down;
            }
            this->pointing->Noisenode::Noise_leftdown_expand();
            this->pointing = this->seed;
        }
    }
}

//Render all Required node
void Noisesystem::Rendering_noise(int sisi){
    //set the pointing to top left
    Noisenode* Render_anchor = this->playerpoint;
    for(int i=0; i<sisi; i++){
        Render_anchor = Render_anchor->up;
        Render_anchor = Render_anchor->left;
    }

    // Rendering the required node
    this->pointing = Render_anchor;
    for(int i=0; i < 2*sisi+1; i++){
        for(int j=0; j< 2*sisi+1; j++){
            for(int k=0; k<i; k++){
                this->pointing = this->pointing->right;
            }
            for(int l=0; l<j; l++){
                this->pointing = this->pointing->down;
            }
            this->pointing->Noisenode::Render_noisenode();
            this->pointing = Render_anchor;
        }
    }

    //populate the data
    for(int i=0; i<2*sisi+1; i++){
        for(int j=0; j<2*sisi+1; j++){
            for(int k=0; k<i; k++){
                this->pointing = this->pointing->down;
            }
            for(int l=0; l<j; l++){
                this->pointing = this->pointing->right;
            }

            for(int m=0; m<16; m++){
                for(int n=0; n<16; n++){
                    this->renderred_maps_data[16*i +m][16*j +n] = this->pointing->Nloct->data[16+m][16+n] + this->pointing->right->Nloct->data[16+m][n] + this->pointing->right->down->Nloct->data[m][n] + this->pointing->down->Nloct->data[m][16+n];
                    this->renderred_maps_data[16*i +m][16*j +n] = this->renderred_maps_data[16*i +m][16*j +n]%10;
                }
            }

            this->pointing = Render_anchor;
        }
    }
    this->pointing = this->seed;
}

//Generate some up addition node
//adding additional up node
void Noisesystem::Expand_up_horizontal(){
    Noisenode* The_point = this->point_y_plus;
    The_point->Noisenode::Noise_up_expand();

    for(int i=0; i<this->point_x_plus->Nloct->x; i++){
        for(int j=0; j<i; j++){
            The_point = The_point->right;
        }
        The_point->Noisenode::Noise_rightup_expand();
        The_point = this->point_y_plus;
    }

    for(int i=0; i>this->point_x_minus->Nloct->x; i--){
        for(int j=0; j<i; j++){
            The_point = The_point->left;
        }
        The_point->Noisenode::Noise_leftup_expand();
        The_point = this->point_y_plus;
    }

    this->point_y_plus = this->point_y_plus->up;
}

//adding additional down node
void Noisesystem::Expand_down_horizontal(){
    Noisenode* The_point = this->point_y_minus;
    The_point->Noisenode::Noise_down_expand();

    for(int i=0; i<this->point_x_plus->Nloct->x; i++){
        for(int j=0; j<i; j++){
            The_point = The_point->right;
        }
        The_point->Noisenode::Noise_rightdown_expand();
        The_point = this->point_y_minus;
    }

    for(int i=0; i>this->point_x_minus->Nloct->x; i--){
        for(int j=0; j<i; j++){
            The_point = The_point->left;
        }
        The_point->Noisenode::Noise_leftdown_expand();
        The_point = this->point_y_minus;
    }

    this->point_y_minus = this->point_y_minus->down;
}

//adding additional right node
void Noisesystem::Expand_right_vertical(){
    Noisenode* The_point = this->point_x_plus;
    The_point->Noisenode::Noise_right_expand();

    for(int i=0; i<this->point_y_plus->Nloct->y; i++){
        for(int j=0; j<i; j++){
            The_point = The_point->up;
        }
        The_point->Noisenode::Noise_rightup_expand();
        The_point = this->point_x_plus;
    }

    for(int i=0; i>this->point_y_minus->Nloct->y; i--){
        for(int j=0; j<i; j++){
            The_point = The_point->down;
        }
        The_point->Noisenode::Noise_rightdown_expand();
        The_point = this->point_x_plus;
    }

    this->point_x_plus = this->point_x_plus->right;
}

//adding additional right node
void Noisesystem::Expand_left_vertical(){
    Noisenode* The_point = this->point_x_minus;
    The_point->Noisenode::Noise_left_expand();

    for(int i=0; i<this->point_y_plus->Nloct->y; i++){
        for(int j=0; j<i; j++){
            The_point = The_point->up;
        }
        The_point->Noisenode::Noise_leftup_expand();
        The_point = this->point_x_minus;
    }

    for(int i=0; i>this->point_y_minus->Nloct->y; i--){
        for(int j=0; j<i; j++){
            The_point = The_point->down;
        }
        The_point->Noisenode::Noise_leftdown_expand();
        The_point = this->point_x_minus;
    }

    this->point_x_minus = this->point_x_minus->left;
}