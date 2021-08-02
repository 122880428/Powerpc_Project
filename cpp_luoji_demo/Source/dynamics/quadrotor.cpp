#include "quadrotor.h"
#include "..\drivers\gcs.h"
#include "..\drivers\sbus.h"

#define EULER 1     //皇：使用前进欧拉法
#define ODE45 0     //皇：使用ode45

extern Quadrotor _quadrotor;
extern Gcs _gcs;
extern Sbus _sbus;

/**
 * 函数作用：Quadrotor的构造函数。
 * 作者：皇陆亚
 * 时间：2021-08-01
 */
Quadrotor::Quadrotor()
{
    printf("quadrotor construct!\r\n");
    Ix = 0.1676;     //kg*m2
    Iy = 0.1676;
    Iz = 0.29743;

    //皇：转动惯量对角矩阵
    inertia = Matrix3d(Vector3d(Ix, Iy, Iz).asDiagonal());
    m = 2.356; //飞行器重量

    inertia_inv = inertia.inverse();		//皇：转动惯量对角矩阵的逆



    V0 = Vector3d::Zero(3);                //皇：初始速度
    omega_start = Vector3d::Zero(3);       //皇：初始欧拉角


    //四个输入量 
    input<<0,0,0,0;


    input_last = Vector4d::Zero();
    input_new = Vector4d::Zero();

    //初始状态数组，三个速度，三个角速度，三个位置，三个姿态角 
    //VectorXd state(12);
    state_vel=Vector3d::Zero();
    state_ang=Vector3d::Zero();
    state_pos=Vector3d::Zero();
    state_att=Vector3d::Zero();

    //VectorXd state_dot(12);
    state_dot_vel=Vector3d::Zero();
    state_dot_ang=Vector3d::Zero();
    state_dot_pos=Vector3d::Zero();
    state_dot_att=Vector3d::Zero();


    //VectorXd state_new(12);
    state_new_vel=Vector3d::Zero();
    state_new_ang=Vector3d::Zero();
    state_new_pos=Vector3d::Zero();
    state_new_att=Vector3d::Zero();
}

/**
 * 函数作用：四旋翼飞行动力学方程组
 * 作者：皇陆亚
 * 时间：2021-08-01
 */
void Quadrotor::quad_equation(void)
{

    double p = state_ang[0];
    double q = state_ang[1];
    double r = state_ang[2];

	
	double phi = state_att(0);
	double theta = state_att(1);
	double psi = state_att(2);

    
    double T = input[0];
    double L_ = input[1];
    double M_ = input[2];
    double N_ = input[3];
   
	//三个力 
	Vector3d F(0,0,0);
    F[0] = m * g * (-sin(theta)) + 0 - 0.01 * state_vel.norm() * state_vel[0];
    F[1] = m * g * cos(theta) * sin(phi) + 0 - 0.01 * state_vel.norm() * state_vel[1];
    F[2] = m * g * cos(theta) * cos(phi) - T - 0.01 * state_vel.norm() * state_vel[2];
//  float F = m*g *(-sin(theta);cos(theta)*sin(phi);cos(theta)*cos(phi))+[0 0 -T]'-0.01*sqrt(u^2+v^2+w^2)*V;%其中-0.2*V为简化的气动阻力

    
	Vector3d M(L_ - 0.01 * p, M_ - 0.01 * q, N_ - 0.01 * r);

    Vector3d m_V_dot = F - state_ang.cross(state_vel);
    Vector3d V_dot = m_V_dot / m;

    Vector3d I_omega_dot = M - state_ang.cross(inertia * state_ang); //皇：这里的向量和矩阵相乘对不对呢？？
    Vector3d omega_dot = inertia_inv * I_omega_dot;
	
    Matrix3d MATRIX1 = Matrix3d::Zero();
    MATRIX1 << 1.0, 0.0, -sin(theta),
        0.0, cos(phi), sin(phi) * cos(theta),
        0.0, -sin(phi), cos(theta) * cos(phi);
	
    Vector3d ATTITUDE_DOT = MATRIX1.inverse()*state_ang;
    Matrix3d MATRIX2;
    MATRIX2 << cos(psi) * cos(theta), cos(psi) * sin(theta) * sin(phi) - sin(psi) * cos(phi), cos(psi) * sin(theta) * cos(phi) + sin(psi) * sin(phi),
        sin(psi) * cos(theta), sin(psi) * sin(theta) * sin(phi) + cos(psi) * cos(phi), sin(psi) * sin(theta) * cos(phi) - cos(psi) * sin(phi),
        -sin(theta), cos(theta) * sin(phi), cos(theta) * cos(phi);
    Vector3d POS_DOT = MATRIX2 * state_vel;
//    state_dot << V_dot, omega_dot, POS_DOT, ATTITUDE_DOT;
	state_dot_vel = V_dot;
	state_dot_ang = omega_dot;
	state_dot_pos = POS_DOT;
	state_dot_att = ATTITUDE_DOT;
}
 
/**
 * 函数作用：飞行动力学模型测试函数
 * 作者：皇陆亚
 * 时间：2021-08-01
 */
void Quadrotor::test_quadrotor_dynamics(void)
{

    const float deltat = 0.01;
  //static VectorXd state_last(12);
static Vector3d state_last_vel=Vector3d::Zero();
static Vector3d state_last_ang=Vector3d::Zero();
static Vector3d state_last_pos=Vector3d::Zero();
static Vector3d state_last_att=Vector3d::Zero();

	state_last_vel = state_new_vel;
	state_last_ang = state_new_ang;
	state_last_pos = state_new_pos;
	state_last_att = state_new_att;
	input_last = input_new;
	input_new = input;

    quad_equation();
    
//data_from_sbus();
/************前进欧拉**********************/   


#ifdef EULER

    //state_new = state_dot * deltat + state_last;
    state_new_vel = state_dot_vel * deltat + state_last_vel;
    state_new_ang = state_dot_ang * deltat + state_last_ang;
    state_new_pos = state_dot_pos * deltat + state_last_pos;
    state_new_att = state_dot_att * deltat + state_last_att;
#endif
#ifdef ODE45
    const double h=0.01;

    Vector3d* state_last = new Vector3d [4];
    Vector3d* tempvec = new Vector3d [4];
    Vector3d* slope = new Vector3d [4];
    Vector3d* k1 = new Vector3d [4];
    Vector3d* k2 = new Vector3d [4];
    Vector3d* k3 = new Vector3d [4];
    Vector3d* k4 = new Vector3d [4];
    state_last[0] = state_last_vel;
    state_last[1] = state_last_ang;
    state_last[2] = state_last_pos;
    state_last[3] = state_last_att;
//printf("state_last_vel:%f,%f,%f\n\r",state_last_vel[0],state_last_vel[1],state_last_vel[2]);
//printf("state_last[0]:%f,%f,%f\n\r",state_last[0][0],state_last[0][1],state_last[0][2]);   
    /*tempvec[0] = state_last[0];
    tempvec[1] = state_last[1];
    tempvec[2] = state_last[2];
    tempvec[3] = state_last[3];*/

    quad_equation(state_last,k1);
    Vec12addVec12(tempvec,state_last ,k1, 0.5*h);
    quad_equation(tempvec,k2);
    Vec12addVec12(tempvec,state_last, k2, 0.5*h);
    quad_equation(tempvec,k3);
    Vec12addVec12(tempvec,state_last ,k3, h);
    quad_equation(tempvec,k4);

    Vec12addVec12(tempvec,k1, k2,2);
    Vec12addVec12(slope,tempvec, k3,2);
    Vec12addVec12(tempvec,slope, k4,1);

    state_new_vel = tempvec[0] * h/6 + state_last_vel;
    state_new_ang = tempvec[1] * h/6 + state_last_ang;
    state_new_pos = tempvec[2] * h/6 + state_last_pos;
    state_new_att = tempvec[3] * h/6 + state_last_att;
    delete [] state_last;
    delete [] tempvec;
    delete [] slope;
    delete [] k1;
    delete [] k2;
    delete [] k3;
    delete [] k4;
//printf("state_last[0]:%f,%f,%f\n\r",state_last[0][0],state_last[0][1],state_last[0][2]);
#endif

    
	state_vel=state_new_vel;
	state_ang=state_new_ang;
	state_pos=state_new_pos;
	state_att=state_new_att;
    
    data_to_gcs();
}

/**
 * 函数作用：打印调试一些数据
 * 作者：皇陆亚
 * 时间：2021-08-01
 */
void Quadrotor::debug_printf(void)
{
    //printf("running\r\n");
    printf("statevel:%f,%f,%f\n\r",state_new_vel[0],state_new_vel[1],state_new_vel[2]);
    printf("stateang:%f,%f,%f\n\r",state_new_ang[0],state_new_ang[1],state_new_ang[2]);
    printf("statepos:%f,%f,%f\n\r",state_new_pos[0],state_new_pos[1],state_new_pos[2]);
    printf("stateatt:%f,%f,%f\n\r",state_new_att[0],state_new_att[1],state_new_att[2]);
}

/**
 * 函数作用：将数据存到地面站类里面
 * 作者：皇陆亚
 * 时间：2021-08-01
 */
void Quadrotor::data_to_gcs(void)
{
    _gcs.set("roll",state_att[0]);
    _gcs.set("pitch",state_att[1]);
    _gcs.set("yaw",state_att[2]);
    _gcs.set("gyrox",state_ang[0]);
    _gcs.set("gyroy",state_ang[1]);
    _gcs.set("gyroz",state_ang[2]);
    _gcs.set("velx",state_vel[0]);
    _gcs.set("vely",state_vel[1]);
    _gcs.set("velz",state_vel[2]);
    _gcs.set("posx",state_pos[0]);
    _gcs.set("posy",state_pos[1]);
    _gcs.set("posz",state_pos[2]);
    /*if(_gcs.set("posz",state_pos[2]))
        printf("set is ok!\r\n");
    else
        printf("set is wrong!\r\n");*/
}   

/**
 * 函数作用：将sbus的四个通道缩放成一个力三个力矩
 * 作者：皇陆亚
 * 时间：2021-08-01
 */
void Quadrotor::data_from_sbus(void)
{
    input[1]=(_sbus.GetChannel(1)-1500)/300;   //皇：ail副翼，滚转，绕x轴转
    input[2]=(_sbus.GetChannel(2)-1500)/300;   //皇：ele升降，绕y轴
    input[0]=-_sbus.GetChannel(3)/40;   //皇：油门
    input[3]=(_sbus.GetChannel(4)-1500)/300;   //皇：rud偏航，绕z轴
}


void Quadrotor::quad_equation(const Vector3d* state, Vector3d* dot)
{
    
    double p = state[1][0];
    double q = state[1][1];
    double r = state[1][2];

    
    double phi = state[3](0);
    double theta = state[3](1);
    double psi = state[3](2);

    //data_from_sbus();
    double T = input[0];
    double L_ = input[1];
    double M_ = input[2];
    double N_ = input[3];
   
    //三个力 
    Vector3d F(0,0,0);
    F[0] = m * g * (-sin(theta)) + 0 - 0.01 * state[0].norm() * state[0][0];
    F[1] = m * g * cos(theta) * sin(phi) + 0 - 0.01 * state[0].norm() * state[0][1];
    F[2] = m * g * cos(theta) * cos(phi) - T - 0.01 * state[0].norm() * state[0][2];
    //printf("F2 is %f\r\n",F[2]);
//  float F = m*g *(-sin(theta);cos(theta)*sin(phi);cos(theta)*cos(phi))+[0 0 -T]'-0.01*sqrt(u^2+v^2+w^2)*V;%其中-0.2*V为简化的气动阻力

    
    Vector3d M(L_ - 0.01 * p, M_ - 0.01 * q, N_ - 0.01 * r);

    Vector3d m_V_dot = F - state[1].cross(state[0]);
    Vector3d V_dot = m_V_dot / m;

    Vector3d I_omega_dot = M - state[1].cross(inertia * state[1]); //皇：这里的向量和矩阵相乘对不对呢？？
    Vector3d omega_dot = inertia_inv * I_omega_dot;
    
    Matrix3d MATRIX1 = Matrix3d::Zero();
    MATRIX1 << 1.0, 0.0, -sin(theta),
        0.0, cos(phi), sin(phi) * cos(theta),
        0.0, -sin(phi), cos(theta) * cos(phi);
    
    Vector3d ATTITUDE_DOT = MATRIX1.inverse()*state[1];
    Matrix3d MATRIX2;
    MATRIX2 << cos(psi) * cos(theta), cos(psi) * sin(theta) * sin(phi) - sin(psi) * cos(phi), cos(psi) * sin(theta) * cos(phi) + sin(psi) * sin(phi),
        sin(psi) * cos(theta), sin(psi) * sin(theta) * sin(phi) + cos(psi) * cos(phi), sin(psi) * sin(theta) * cos(phi) - cos(psi) * sin(phi),
        -sin(theta), cos(theta) * sin(phi), cos(theta) * cos(phi);
    Vector3d POS_DOT = MATRIX2 * state[0];
//    state_dot << V_dot, omega_dot, POS_DOT, ATTITUDE_DOT;
    

    dot[0] = V_dot;
    dot[1] = omega_dot;
    dot[2] = POS_DOT;
    dot[3] = ATTITUDE_DOT;
}

void Quadrotor::Vec12addVec12(Vector3d* ansvec,const Vector3d* vec1, const Vector3d* vec2, const double num)
{
    ansvec[0]=vec1[0]+vec2[0]*num;
    ansvec[1]=vec1[1]+vec2[1]*num;
    ansvec[2]=vec1[2]+vec2[2]*num;
    ansvec[3]=vec1[3]+vec2[3]*num;
}