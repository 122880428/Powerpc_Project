 #ifndef _QUADROTOR_H_
 #define _QUADROTOR_H_
 
 #include <iostream>
 #include <Eigen/Dense>
using Eigen::Matrix3f;
using Eigen::Matrix3d;
using Eigen::Matrix2d;
using Eigen::Vector3d;
using Eigen::VectorXd;
using Eigen::Vector4d;


#define g (9.81)         //重力加速度
 
using namespace std;

/*
坐标系定义同直升机飞行力学书上。
x朝前，y朝右，z朝下。
 */

//皇：这个类里面的成员有些冗余了，后续需要用三维向量的数组重构一下。
class Quadrotor
{
private:
	double Ix;     //kg*m2
	double Iy;
	double Iz;

	//皇：转动惯量对角矩阵
	Matrix3d inertia;
	double m; //飞行器重量

	Matrix3d inertia_inv;		//皇：转动惯量对角矩阵的逆

	Vector3d V0;                //皇：初始速度
	Vector3d omega_start;       //皇：初始欧拉角


	//四个输入量 
	Vector4d input;


	Vector4d input_last;
	Vector4d input_new;

	//初始状态数组，三个速度，三个角速度，三个位置，三个姿态角 
	//VectorXd state(12);
	Vector3d state_vel;
	Vector3d state_ang;
	Vector3d state_pos;
	Vector3d state_att;

	//VectorXd state_dot(12);
	Vector3d state_dot_vel;
	Vector3d state_dot_ang;
	Vector3d state_dot_pos;
	Vector3d state_dot_att;

	//VectorXd state_new(12);
	Vector3d state_new_vel;
	Vector3d state_new_ang;
	Vector3d state_new_pos;
	Vector3d state_new_att;


	bool _reset_flag;

public:
	Quadrotor();	//修改构造函数的时候记得修改reset_all()函数
	~Quadrotor(){}

	 /*
皇：运行飞行动力学模型。
数据输入通过串口2
输出通过串口3
*/
void test_quadrotor_dynamics(void);
void quad_equation(void);
void quad_equation(const Vector3d* state, Vector3d* dot);

//用于打印调试。放在一个慢点的循环里面
void debug_printf(void);
//皇：将数据存到地面站类里面
void data_to_gcs(void);
//从遥控器得到四个力矩
void data_from_sbus(void);
void Vec12addVec12(Vector3d* ansvec,const Vector3d* vec1, const Vector3d* vec2, const double num);
void reset_all(void);	//重置飞行动力学模型，
void reset_monitor(void);		//监视遥控器，触发重置标志
};

 #endif