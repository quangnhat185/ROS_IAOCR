
#include <iostream>
#include <vector>
#include <math.h>
using namespace std;

vector<int> forward_kinematic(vector<int>  vec_velocity, float l=0.1){

    int v_x, v_y;
    int w;
    int v1, v2, v3;
    v1 = vec_velocity[0];
    v2 = vec_velocity[1];
    v3 = vec_velocity[2];

    v_x = (2*v2 - v1 -v3)/3;
    v_y = (sqrt(3)*(v3-v1))/3;
    w = (v1+v2+v3)/(3*l);

    vector<int> result = {v_x, v_y, w};
    return result;
    
}

vector<int> inverse_kinematic(vector<int> vec_state, float l=0.1){
    int v1, v2, v3;    
    int v_x, v_y, w;
    v_x = vec_state[0];
    v_y = vec_state[1];
    w = vec_state[2];

    v1 = -v_x/2 - (sqrt(3)*v_y)/2 + l*w;
    v2 = v_x + l*w;
    v3 = -v_x/2 + (sqrt(3)*v_y)/2 + l*w;

    vector<int> result = {v1, v2, v3};
    return result;

} 

int main(){
    int v1 = 150;
    int v2 = 150;
    int v3 = 100;

    vector<int> wheel_speed =  {v1, v2, v3};
    vector<int> forward_result;

    forward_result = forward_kinematic(wheel_speed);
    cout << "forward kinematic: ";
    for (int i: forward_result){
        cout << i << " ";
    }
    cout <<endl;

    vector<int> inverse_result;
    inverse_result = inverse_kinematic(forward_result);
    cout << "inverse kinematic: ";
    for (int i: inverse_result){
        cout << i << " ";
    }
    cout <<endl;


}