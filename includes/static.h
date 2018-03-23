#ifndef STATIC_H
# define STATIC_H

static float VCUBE[108] = {

//FACE UP
	-0.5f , 0.5f, -0.5f,
	0.5f , 0.5f, 0.5f,
	0.5f , 0.5f, -0.5f,

	-0.5f , 0.5f, -0.5f,
	-0.5f , 0.5f, 0.5f,
	0.5f , 0.5f, 0.5f,
//FACE DOWN
	0.5f , -0.5f, 0.5f,
	-0.5f , -0.5f, -0.5f,
	0.5f , -0.5f, -0.5f,

	0.5f , -0.5f, 0.5f,
	-0.5f , -0.5f, 0.5f,
	-0.5f , -0.5f, -0.5f,
// FACE EST
	0.5f , 0.5f, -0.5f,
	0.5f , -0.5f, 0.5f,
	0.5f , -0.5f, -0.5f,

	0.5f , 0.5f, -0.5f,
	0.5f , 0.5f, 0.5f,
	0.5f , -0.5f, 0.5f,

//face ouest
	-0.5f , -0.5f, 0.5f,
	-0.5f , 0.5f, -0.5f,
	-0.5f , -0.5f, -0.5f,

	-0.5f , -0.5f, 0.5f,
	-0.5f , 0.5f, 0.5f,
	-0.5f , 0.5f, -0.5f,
//FACE NORD
	0.5f , 0.5f, 0.5f,
	-0.5f , -0.5f, 0.5f,
	0.5f , -0.5f, 0.5f,

	0.5f , 0.5f, 0.5f,
	-0.5f , 0.5f, 0.5f,
	-0.5f , -0.5f, 0.5f,
//FACE SUD
	0.5f , -0.5f, -0.5f,
	-0.5f , 0.5f, -0.5f,
	0.5f , 0.5f, -0.5f,

	0.5f , -0.5f, -0.5f,
	-0.5f , -0.5f, -0.5f,
	-0.5f , 0.5f, -0.5f
};

const float t1 = 0.332;
const float t2 = 0.667;

static float VCUBEUV[72] = {
//FACE UP
		t1 , t2,
		0.0f , 1.0f,
		0.0f , t2,

		t1 , t2,
		t1 , 1.0f,
		0.0f , 1.0f,
//FACE DOWN
		1.0f , 0.0f,
		0.0f , 1.0f,
		0.0f , 0.0f,

		1.0f , 0.0f,
		1.0f , 1.0f,
		0.0f , 1.0f,
// FACE EST
		t1 , 1.0f,
		t2 , t2,
		t1 , t2,

		t1 , 1.0f,
		t2 , 1.0f,
		t2 , t2,

//face OUEST
t2 , t2,
		t1 , 1.0f,
		t1 , t2,

		t2 , t2,
		t1 , 1.0f,
		t2 , 1.0f,
//FAce nord
		t1 , 1.0f,
		t2 , t2,
		t1 , t2,

		t1 , 1.0f,
		t2 , 1.0f,
		t2 , t2,
//FACE SUD

		t2 , t2,
		t2 , 0.999f,
		t1 , 0.999f,

		t2 , t2,
		t1 , t2,
		t2, 0.999f,
	};
#endif
