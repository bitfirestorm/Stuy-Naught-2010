/*
 * Function: float Vfunc(int which, float *v1, float *v2, float *vresult, float scalar)
 *   A Jack-of-all-trades vector function.
 *   Input variables:
 *     which: chooses the vector function to compute
 *     v1,v2: input vectors:  float v1[3], v2[3]
 *     vresult: output vector, float vresult[3]
 *     scalar: input scalar
 *
 *  Note: some arguments are ignored for some functions, and so can be given the value NULL
 * 
 *  Assume, for documentation below, the following variables are already declared:
 *      float a1[3], a2[3], a3[3], s;
 *
 *  Functions:
 *
 *    Subtracting vectors:
 *       which == 2: vresult = v1 - v2
 *       Vfunc(2,a1,a2,a3,0);  // a3 = a1 - a2
 *
 *    Unit vector:
 *       which == 3: vresult = unit vector in direction of v1
 *       if s = Vfunc(3,a1,NULL,a3,0); // a3 = a1 / |a1|
 *       Note: returns 0.0 if |a1| == 0, then sets a3 to the zero vector
 *             returns 1.0 under normal circumstances
 *
 *    Scalar times vector:
 *       which == 4: vresult = s * v1
 *        Vfunc(4,a1,NULL,a3,s);  // a3 = s * a1
 *
 *    Dot product:
 *       which == 5: returns v1 * v2
 *       s = Vfunc(5,a1,a2,a3,0);  // returns dot product of a1 and a2
 *
 *    Distance between two vectors (as positions):
 *       which == 6: returns |v1-v2|
 *       s = Vfunc(6,a1,a2,NULL,0);  // s = length(a1-a2)
 *
 *    Angle between 2 vectors (in degrees, not radians):
 *       which == 8: returns angle between v1 and v2
 *       float angle = Vfunc(8,a1,a2,NULL,0);
 *
 *    Unit vector pointing from v1 to v2:
 *       which == 9: vresult is the unit vector pointing from position v1 toward position v2
 *       Vfunc(9,a1,a2,a3,0);   // a3 will be the unit vector
 *    
 *    Rotate v1 towards v2:
 *       which == 10: vresult is vector v1 rotated scalar degrees towards v2
 *       scalar degrees must be less than the angle between the two vectors
 *       Vfunc(10,v1,v2,result,angle);
 *       Note: returns 0 if successful, 1 if the angle is too large
*/

/* Copy function header:

float Vfunc(int which, float *v1, float *v2, float *vresult, float scalar)

{

*/


#define prvect(msg,p) printf("%s (%f,%f,%f)\n",msg,p[0],p[1],p[2])

int i = 0;
float v3[3];

//1 and 2 are no longer needed

if (which == 2) { // vresult = v1 - v2
for (; i < 3; ++i)
 vresult[i] = v1[i] - v2[i];
}

if (which == 3) { // vresult = v1 / |v1|
memcpy(vresult, v1, sizeof(float)*3);
mathVecNormalize(vresult,3);
}

if (which == 4) { // vresult = scalar * v1
for (; i < 3; ++i)
 vresult[i] = scalar * v1[i];
}

if (which == 6) { // returns distance between v1 and v2
Vfunc(2,v1,v2,v3,0); // v3 = v1 - v2
return mathVecMagnitude(v3,3);
}

if (which == 8) { // angle between two vectors
return acosf(mathVecInner(v1,v2,3)/(mathVecMagnitude(v1,3)*mathVecMagnitude(v2,3))) * 180.0 / PI;
}

if (which == 9) { // unit vector pointing from v1 toward v2
Vfunc(2,v2,v1,v3,0);
Vfunc(3,v3,NULL,vresult,0);
}

if (which == 10) { // rotated vector v1 towards v2 at scalar degrees
float ang = scalar*PI/180.0;
float u[3];
float c = cosf(ang);
float s = sinf(ang);
if (Vfunc(8,v3,v1,NULL,0) < Vfunc(8,v1,v2,NULL,0) && Vfunc(8,v3,v2,NULL,0) < Vfunc(8,v1,v2,NULL,0)) {
 c = cosf(-1*ang);
 s = sinf(-1*ang);
}
mathVecNormalize(v1,3);
mathVecNormalize(v2,3);

if (scalar > Vfunc(8,v1,v2,NULL,0)) {
return 1;
}

mathVecCross(u,v1,v2);
mathVecNormalize(u,3);

v3[0] = (v1[0]*(c + u[0] * u[0] * (1-c)) + v1[1]*(u[0] * u[1] * (1-c) - u[2] * s) + v1[2]*(u[0] * u[2] * (1-c) + u[1] * s));
v3[1] = (v1[0]*(u[0] * u[1] * (1-c) + u[2] * s) + v1[1]*(c + u[1] * u[1] * (1-c)) + v1[2]*(u[1] * u[2] * (1-c) - u[0] * s));
v3[2] = (v1[0]*(u[0] * u[2] * (1-c) - u[1] * s) + v1[1]*(u[1] * u[2] * (1-c) + u[0] * s) + v1[2]*(c + u[2] * u[2] * (1-c)));

memcpy(vresult,v3,sizeof(float)*3);
}

return 0;
//}

