#include "Angel.h"
#include "glui.h"
#include "freeglut.h"

const int numOfCir = 5;
GLint numberOfSlides = 360 - 2;
GLfloat radius = 0.1f;
GLuint program, vao[6];
int   main_window;
GLint scaleLoc, theta;
GLfloat scale = 1.0, Theta;
float speed;
int growShrink = -1;	/*start with no animation*/
						/*1-growing 2-shrinking*/
GLfloat vertices[]{
	// -----Quad----- //
	0.0f, -0.5f,	//A
	0.5f, 0.0f,		//B
	0.0f, 0.5f,		//C
	0.0f, 0.5f,		//C
	-0.5f, 0.0f,	//D
	0.0f, -0.5,		//A
					// ---Triangle1--- //
					0.0f, -0.5,		//A
					-0.5f, 0.0f,	//D
					-1.0f, -1.0f,	//1
									// ---Triangle2--- //
									0.0f, -0.5f,	//A
									0.5f, 0.0f,		//B
									1.0f, -1.0f,	//2
													// ---Triangle3--- //
													0.5f, 0.0f,		//B
													1.0f, 1.0f,		//3
													0.0f, 0.5f,		//C
																	// ---Triangle4--- //
																	0.0f, 0.5f,		//C
																	-1.0f, 1.0f,	//4
																	-0.5f, 0.0f		//D
};
GLfloat colors[] = {
	0.45f, 0.45f, 0.45f,	0.45f, 0.45f, 0.45f,	0.45f, 0.45f, 0.45f,	// Quad
	0.45f, 0.45f, 0.45f,	0.45f, 0.45f, 0.45f,	0.45f, 0.45f, 0.45f,
	0.45f, 0.45f, 0.45f,	0.45f, 0.45f, 0.45f,	0.45f, 0.45f, 0.45f,	// Triangle1
	0.45f, 0.45f, 0.45f,	0.45f, 0.45f, 0.45f,	0.45f, 0.45f, 0.45f,	// Triangle2
	0.45f, 0.45f, 0.45f,	0.45f, 0.45f, 0.45f,	0.45f, 0.45f, 0.45f,	// Triangle3
	0.45f, 0.45f, 0.45f,	0.45f, 0.45f, 0.45f,	0.45f, 0.45f, 0.45f		// Triangle4
};
GLfloat circle1[360 * numOfCir], circle2[360 * numOfCir], circle3[360 * numOfCir], circle4[360 * numOfCir], circle5[360 * numOfCir];
GLfloat circle1Color[360 * 3], circle2Color[360 * 3], circle3Color[360 * 3], circle4Color[360 * 3], circle5Color[360 * 3];

void drawCircle() {
	GLfloat x, y;
	for (int i = 0; i<180; i++) {
		x = radius * cos(i * 4.0f * M_PI / numberOfSlides);
		y = radius * sin(i * 4.0f * M_PI / numberOfSlides);
		// Circle at (0,0)
		circle1[2 * i] = x;					circle1[(2 * i) + 1] = y;
		circle1Color[(3 * i)] = 1.0f;		circle1Color[(3 * i) + 1] = 1.0f;		circle1Color[(3 * i) + 2] = 0.0f;
		// Circle at (0, -0.5)
		circle2[2 * i] = x;					circle2[(2 * i) + 1] = y - 0.5f;
		circle2Color[(3 * i)] = 1.0f;		circle2Color[(3 * i) + 1] = 1.0f;		circle2Color[(3 * i) + 2] = 0.0f;
		// Circle at (0.5 , 0)
		circle3[2 * i] = x + 0.5f;			circle3[(2 * i) + 1] = y;
		circle3Color[(3 * i)] = 1.0f;		circle3Color[(3 * i) + 1] = 1.0f;		circle3Color[(3 * i) + 2] = 0.0f;
		// Circle at (0, 0.5)
		circle4[2 * i] = x;					circle4[(2 * i) + 1] = y + 0.5f;
		circle4Color[(3 * i)] = 1.0f;		circle4Color[(3 * i) + 1] = 1.0f;		circle4Color[(3 * i) + 2] = 0.0f;
		// Circle at (-5,0)
		circle5[2 * i] = x - 0.5f;			circle5[(2 * i) + 1] = y;
		circle5Color[(3 * i)] = 1.0f;		circle5Color[(3 * i) + 1] = 1.0f;		circle5Color[(3 * i) + 2] = 0.0f;
	}
}

void init()
{
	GLuint buffer[2];
	GLint vPosition, vColor;

	// Load shaders and use the resulting shader program
	GLuint program = InitShader("vshader.glsl", "fshader.glsl");
	glUseProgram(program);

	drawCircle();	// Draw circles
	
	glGenVertexArrays(6, vao);
	
	/* Initialize buffer object and set up vertex arrays*/
	glBindVertexArray(vao[0]);
	glGenBuffers(2, buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	vPosition = glGetAttribLocation(program, "vPosition");
	glEnableVertexAttribArray(vPosition);
	glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	glBindBuffer(GL_ARRAY_BUFFER, buffer[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
	vColor = glGetAttribLocation(program, "vColor");
	glEnableVertexAttribArray(vColor);
	glVertexAttribPointer(vColor, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	glBindVertexArray(vao[1]);

	glGenBuffers(2, buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(circle1), circle1, GL_STATIC_DRAW);
	vPosition = glGetAttribLocation(program, "vPosition");
	glEnableVertexAttribArray(vPosition);
	glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	glBindBuffer(GL_ARRAY_BUFFER, buffer[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(circle1Color), circle1Color, GL_STATIC_DRAW);
	vColor = glGetAttribLocation(program, "vColor");
	glEnableVertexAttribArray(vColor);
	glVertexAttribPointer(vColor, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	glBindVertexArray(vao[2]);

	glGenBuffers(2, buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(circle2), circle2, GL_STATIC_DRAW);
	vPosition = glGetAttribLocation(program, "vPosition");
	glEnableVertexAttribArray(vPosition);
	glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	glBindBuffer(GL_ARRAY_BUFFER, buffer[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(circle2Color), circle2Color, GL_STATIC_DRAW);
	vColor = glGetAttribLocation(program, "vColor");
	glEnableVertexAttribArray(vColor);
	glVertexAttribPointer(vColor, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	glBindVertexArray(vao[3]);

	glGenBuffers(2, buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(circle3), circle3, GL_STATIC_DRAW);
	vPosition = glGetAttribLocation(program, "vPosition");
	glEnableVertexAttribArray(vPosition);
	glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	glBindBuffer(GL_ARRAY_BUFFER, buffer[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(circle3Color), circle3Color, GL_STATIC_DRAW);
	vColor = glGetAttribLocation(program, "vColor");
	glEnableVertexAttribArray(vColor);
	glVertexAttribPointer(vColor, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	glBindVertexArray(vao[4]);

	glGenBuffers(2, buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(circle4), circle4, GL_STATIC_DRAW);
	vPosition = glGetAttribLocation(program, "vPosition");
	glEnableVertexAttribArray(vPosition);
	glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	glBindBuffer(GL_ARRAY_BUFFER, buffer[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(circle4Color), circle4Color, GL_STATIC_DRAW);
	vColor = glGetAttribLocation(program, "vColor");
	glEnableVertexAttribArray(vColor);
	glVertexAttribPointer(vColor, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	glBindVertexArray(vao[5]);

	glGenBuffers(2, buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(circle5), circle5, GL_STATIC_DRAW);
	vPosition = glGetAttribLocation(program, "vPosition");
	glEnableVertexAttribArray(vPosition);
	glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	glBindBuffer(GL_ARRAY_BUFFER, buffer[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(circle5Color), circle5Color, GL_STATIC_DRAW);
	vColor = glGetAttribLocation(program, "vColor");
	glEnableVertexAttribArray(vColor);
	glVertexAttribPointer(vColor, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	theta = glGetUniformLocation(program, "Theta");
	scaleLoc = glGetUniformLocation(program, "scale");

	glEnable(GL_DEPTH_TEST);
	glClearColor(1.0, 1.0, 0.0, 1.0);	// yellow background
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUniform1f(theta, Theta);
	glUniform1f(scaleLoc, scale);
	
	// Draw
	glBindVertexArray(vao[5]);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 360);
	glBindVertexArray(vao[4]);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 360);
	glBindVertexArray(vao[3]);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 360);
	glBindVertexArray(vao[2]);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 360);
	glBindVertexArray(vao[1]);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 360);
	glBindVertexArray(vao[0]);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 18);
	
	glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 033: // Escape Key
	case 'q': case 'Q':
		exit(EXIT_SUCCESS);
		break;
	}
}

void idle(void)
{
	/* According to the GLUT specification, the current window is
	undefined during an idle callback.  So we need to explicitly change
	it if necessary */
	if (glutGetWindow() != main_window)
		glutSetWindow(main_window);

	Theta -= 0.1*speed;			/*For counter clockwise rotation*/
	/* Theta += 0.1*speed;*/	/*For clockwise rotation*/
	
	if (scale <= 0.5)		{		growShrink = 1;		}	/*Start growing*/
	else if (scale >= 1.5)	{		growShrink = 2;		}	/*Start shrinking*/

	if (growShrink == 1)	{		scale += 0.001;		}	/*grow -> increase*/
	else if (growShrink == 2){		scale -= 0.001;		}	/*shrink -> decrease*/

	/*For counter clockwise rotation*/
	if (Theta < 0.0 ) {		Theta += 360.0;	}	
	
	/*For clockwise rotation*/
	/*if (Theta > 360.0) {	Theta -= 360.0;	}*/						

	glutSetWindow(main_window);
	glutPostRedisplay();
}

void reshape(int x, int y)
{
	float xy_aspect;

	xy_aspect = (float)x / (float)y;
	GLUI_Master.auto_set_viewport();

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-xy_aspect*.05, xy_aspect*.05, -.05, .05, .1, 15.0);

	glutPostRedisplay();
}

void glui_cb(int control)
{
	switch (control) 
	{
	case 1:/*start rotation*/
		speed = 1.0;
		break;
	case 2:/*stop rotation*/
		speed = 0.0;
		break;
	case 3:/*start grow and shrink */
		growShrink = 1;
		break;
	case 4:/*stop grow and shrink*/
		growShrink = -1;
		break;
	}
}

int main(int argc, char **argv)
{
	glutInit( &argc, argv );
	glutInitDisplayMode( GLUT_DEPTH | GLUT_SINGLE | GLUT_RGBA );
	glutInitWindowSize( 712, 512 );
	//printf("GLUI version: %3.2f\n", GLUI_Master.get_version());
	//if (glewIsSupported("GL_VERSION_3_1"))
	//{
	//	glutInitContextVersion(3, 1);
	//	glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);

	//	//glutInitContextVersion (3, 2);             
	//	//glutInitContextFlags (GLUT_CORE_PROFILE);
	//}
	//else if (glewIsSupported("GL_VERSION_2_0"))
	//{
	//	glutInitContextVersion(2, 0);
	//}
	
	main_window = glutCreateWindow("Ninja Star");
	glewExperimental = GL_TRUE;
	glewInit();
	init();
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);

	/*GLUI*/
	GLUI *glui = GLUI_Master.create_glui_subwindow(main_window, GLUI_SUBWINDOW_RIGHT);
	new GLUI_StaticText(glui, "NINJA STAR");
	new GLUI_Separator(glui);
	new GLUI_Button(glui, "Start Rotation", 1, glui_cb);
	new GLUI_Button(glui, "Stop Rotation", 2, glui_cb);
	GLUI_Spinner *spinner = new GLUI_Spinner(glui, "Rotation speed", &speed);
	spinner->set_int_limits(-10, 10);
	new GLUI_Separator(glui);
	new GLUI_StaticText(glui, "Grow & Shrink Animation");
	new GLUI_Button(glui, "Start Animation", 3, glui_cb);
	new GLUI_Button(glui, "Stop Animation", 4, glui_cb);
	new GLUI_Separator(glui);
	glui->set_main_gfx_window(main_window);
	GLUI_Master.set_glutReshapeFunc(reshape);
	GLUI_Master.set_glutIdleFunc(idle);
	glui->set_main_gfx_window(main_window);

	glutMainLoop();
	return EXIT_SUCCESS;
}
