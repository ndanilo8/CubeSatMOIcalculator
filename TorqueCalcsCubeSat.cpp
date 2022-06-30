/*
Author: Danilo Nascimento
E-mail: me@daniloonspace.com

This calculates the minimum required torque to control the attitude of a 3U cubesat
it may be addapted to other for other sizes... by changing the dimensions or creating a dimension law and make the user insert the size prefered...

this is an estimate as it considers the Cubesat a solid parallelepiped
Its ofc better to 3D model your exact cubesat model to get better usage-case MOI values

sources: 
Spacecraft Systems Engineering, 4th Edition by Peter Fortescue. ISBN-13: 978-0470750124 https://www.amazon.com/Spacecraft-Systems-Engineering-Peter-Fortescue/dp/047075012X
List of moments of inertia https://en.wikipedia.org/wiki/List_of_moments_of_inertia
*/

#include <iostream>
#define _USE_MATH_DEFINES // Define before including math.h to use math constants like m_pi , e...
#include <math.h>
using namespace std;

#define DEG2RAD M_PI/180.0 // Deg to radians

int main()
{
	cout << "MOI and minimum Torque calculator for 3U cubesat\n" << endl;
	double MOIx, MOIy, MOIz; // Moment of Inertia X Y Z Axis

	double mass;
	cout << "Mass of 3U Cubesat [kg]: ";
	cin >> mass;

	double omega_dot; // alpha = Angular acceleration
	cout << "Required rotation accel [deg/s2]: ";
	cin >> omega_dot;
	omega_dot *= DEG2RAD; // Deg to Rad


	// 3U Sat in SI Units
	// Height Width, Depth
	double const h = 0.1; // 10 cm
	double const w = 0.1; // 10 cm
	double const d = 0.3; // 30 cm

	MOIx = (1.0 / 12.0) * mass * (pow(w, 2) + pow(d, 2));
	MOIy = (1.0 / 12.0) * mass * (pow(d, 2) + pow(h, 2));
	MOIz = (1.0 / 12.0) * mass * (pow(w, 2) + pow(h, 2));

	cout << "MOI x: " << MOIx << "kg m^2" << endl;
	cout << "MOI y: " << MOIy << "kg m^2" << endl;
	cout << "MOI z: " << MOIz << "kg m^2" << endl;

	double Tx, Ty, Tz, Tnet; // 3-axis Torque
	
	Tx = MOIx * omega_dot;
	Ty = MOIy * omega_dot;
	Tz = MOIz * omega_dot;
	Tnet = Tx + Ty + Tz;
	
	cout << "Torque x: " << Tx <<" Nm" << endl;
	cout << "Torque y: " << Ty << " Nm" << endl;
	cout << "Torque z: " << Tz << " Nm" << endl;
	cout << "Net Torque: " << Tnet << " Nm" << endl;

}
