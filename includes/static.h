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

const float t1 = 0.3333;
const float t2 = 0.6666;

static float VCUBEUV[72] = {
//FACE UP
		t1 , t2,
		0.0f , 1.0f,
		0.0f , t2,

		t1 , t2,
		t1 , 1.0f,
		0.0f , 1.0f,
//FACE DOWN
		t2 , 0.0f,
		t1 , t1,
		t1 , 0.0f,

		t2 , 0.0f,
		t2 , t1,
		t1 , t1,
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

	static float VCUBEUVWATER[72] = {
	//FACE UP
			t1 , 0,
			0.0f , t1,
			0.0f , 0,

			t1 , 0,
			t1 , t1,
			0.0f , t1,
	//FACE DOWN
	t1 , 0,
	0.0f , t1,
	0.0f , 0,

	t1 , 0,
	t1 , t1,
	0.0f , t1,
	// FACE EST
	t1 , 0,
	0.0f , t1,
	0.0f , 0,

	t1 , 0,
	t1 , t1,
	0.0f , t1,

	//face OUEST
	t1 , 0,
	0.0f , t1,
	0.0f , 0,

	t1 , 0,
	t1 , t1,
	0.0f , t1,
	//FAce nord
	t1 , 0,
	0.0f , t1,
	0.0f , 0,

	t1 , 0,
	t1 , t1,
	0.0f , t1,
	//FACE SUD

	t1 , 0,
	0.0f , t1,
	0.0f , 0,

	t1 , 0,
	t1 , t1,
	0.0f , t1
		};

#endif



static float VCUBEUVEARTH[72] = {
//FACE UP
t2 , 0.01f,
t1 , t1,
t1 , 0.01f,

t2 , 0.01f,
t2 , t1,
t1 , t1,
//FACE DOWN
t2 , 0.01f,
t1 , t1,
t1 , 0.01f,

t2 , 0.01f,
t2 , t1,
t1 , t1,
// FACE EST
t2 , 0.0f,
t1 , t1,
t1 , 0.0f,

t2 , 0.0f,
t2 , t1,
t1 , t1,

//face OUEST
t2 , 0.0f,
t1 , t1,
t1 , 0.0f,

t2 , 0.0f,
t2 , t1,
t1 , t1,
//FAce nord
t2 , 0.0f,
t1 , t1,
t1 , 0.0f,

t2 , 0.0f,
t2 , t1,
t1 , t1,
//FACE SUD
t2 , 0.0f,
t1 , t1,
t1 , 0.0f,

t2 , 0.0f,
t2 , t1,
t1 , t1
};
