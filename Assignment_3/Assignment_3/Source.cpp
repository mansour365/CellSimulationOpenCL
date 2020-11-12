//Class COMP 426 – NN
//Instructor : Professor R.Jayakumar
//Student ID : 27739656
//Name : Said-Mansour Maqsoudi
//Assignment 3

#include <windows.h>
#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include <iostream>//for printing
#include <vector> //for storing location of medicine cells
#include <thread> //for multithreading

//OpenCL libraries 
#define CL_USE_DEPRECATED_OPENCL_2_0_APIS
#include <stdio.h>
#include <CL/cl.hpp> //for openCL


//med 1 only correspond to row1 and col1
const char* KernelSource =
"__kernel void multipleInjection(\n"\
"	__global float *output2, __global float *output3, __global float *output4, __global float *output5,\n"\
"	__global float *output6, __global float *output7, __global float *output8, __global float *output9,\n"\
"	int row1, int col1, int row2, int col2, int row3, int col3, int med1, int med2, int med3)\n"\
"{\n"\
"	int medArr[3] = {med1, med2, med3};\n"\
"	for(int i = 0; i < 3 ; i++){\n"\
"		int med = medArr[i];\n"\

"		if(med == 1){\n"\
"			if(i = 0){\n"\
"				output2[0] = row1 - 1;\n"\
"				output2[1] = col1;}\n"
"			else if(i = 1){\n"
"				output2[2] = row2 - 1;\n"\
"				output2[3] = col2;}\n"
"			else if(i = 2){\n"
"				output2[4] = row3 - 1;\n"\
"				output2[5] = col3;}}\n"

"		else if(med == 2){\n"\
"			if(i = 0){\n"\
"				output2[0] = row1 - 1;\n"\
"				output2[1] = col1;\n"
"				output3[0] = row1 - 1;\n"\
"				output3[1] = col1 + 1;}\n"
"			else if(i = 1){\n"
"				output2[2] = row2 - 1;\n"\
"				output2[3] = col2;\n"
"				output3[2] = row2 - 1;\n"\
"				output3[3] = col2 + 1;}\n"
"			else if(i = 2){\n"
"				output2[4] = row3 - 1;\n"\
"				output2[5] = col3;\n"
"				output3[4] = row3 - 1;\n"\
"				output3[5] = col3 + 1;}}\n"

"		else if(med == 3){\n"\
"			if(i = 0){\n"\
"				output2[0] = row1 - 1;\n"\
"				output2[1] = col1;\n"
"				output3[0] = row1 - 1;\n"\
"				output3[1] = col1 + 1;\n"
"				output4[0] = row1;\n"\
"				output4[1] = col1 + 1;}\n"
"			else if(i = 1){\n"
"				output2[2] = row2 - 1;\n"\
"				output2[3] = col2;\n"
"				output3[2] = row2 - 1;\n"\
"				output3[3] = col2 + 1;\n"
"				output4[2] = row2;\n"\
"				output4[3] = col2 + 1;}\n"
"			else if(i = 2){\n"
"				output2[4] = row3 - 1;\n"\
"				output2[5] = col3;\n"
"				output3[4] = row3 - 1;\n"\
"				output3[5] = col3 + 1;\n"
"				output4[4] = row3;\n"\
"				output4[5] = col3 + 1;}}\n"

"		else if(med == 4){\n"\
"			if(i = 0){\n"\
"				output2[0] = row1 - 1;\n"\
"				output2[1] = col1;\n"
"				output3[0] = row1 - 1;\n"\
"				output3[1] = col1 + 1;\n"
"				output4[0] = row1;\n"\
"				output4[1] = col1 + 1;\n"
"				output5[0] = row1 + 1;\n"\
"				output5[1] = col1 + 1;}\n"
"			else if(i = 1){\n"
"				output2[2] = row2 - 1;\n"\
"				output2[3] = col2;\n"
"				output3[2] = row2 - 1;\n"\
"				output3[3] = col2 + 1;\n"
"				output4[2] = row2;\n"\
"				output4[3] = col2 + 1;\n"
"				output5[2] = row2 + 1;\n"\
"				output5[3] = col2 + 1;}\n"
"			else if(i = 2){\n"
"				output2[4] = row3 - 1;\n"\
"				output2[5] = col3;\n"
"				output3[4] = row3 - 1;\n"\
"				output3[5] = col3 + 1;\n"
"				output4[4] = row3;\n"\
"				output4[5] = col3 + 1;\n"
"				output5[4] = row3 + 1;\n"\
"				output5[5] = col3 + 1;}}\n"

"		else if(med == 5){\n"\
"			if(i = 0){\n"\
"				output2[0] = row1 - 1;\n"\
"				output2[1] = col1;\n"
"				output3[0] = row1 - 1;\n"\
"				output3[1] = col1 + 1;\n"
"				output4[0] = row1;\n"\
"				output4[1] = col1 + 1;\n"
"				output5[0] = row1 + 1;\n"\
"				output5[1] = col1 + 1;\n"
"				output6[0] = row1 + 1;\n"\
"				output6[1] = col1;}\n"
"			else if(i = 1){\n"
"				output2[2] = row2 - 1;\n"\
"				output2[3] = col2;\n"
"				output3[2] = row2 - 1;\n"\
"				output3[3] = col2 + 1;\n"
"				output4[2] = row2;\n"\
"				output4[3] = col2 + 1;\n"
"				output5[2] = row2 + 1;\n"\
"				output5[3] = col2 + 1;\n"
"				output6[2] = row2 + 1;\n"\
"				output6[3] = col2;}\n"
"			else if(i = 2){\n"
"				output2[4] = row3 - 1;\n"\
"				output2[5] = col3;\n"
"				output3[4] = row3 - 1;\n"\
"				output3[5] = col3 + 1;\n"
"				output4[4] = row3;\n"\
"				output4[5] = col3 + 1;\n"
"				output5[4] = row3 + 1;\n"\
"				output5[5] = col3 + 1;\n"
"				output6[4] = row3 + 1;\n"\
"				output6[5] = col3;}}\n"

"		else if(med == 6){\n"\
"			output2[0] = row1 - 1;\n"\
"			output2[1] = col1;\n"
"			output3[0] = row1 - 1;\n"\
"			output3[1] = col1 + 1;\n"
"			output4[0] = row1;\n"\
"			output4[1] = col1 + 1;\n"
"			output5[0] = row1 + 1;\n"\
"			output5[1] = col1 + 1;\n"
"			output6[0] = row1 + 1;\n"\
"			output6[1] = col1;\n"
"			output7[0] = row1 + 1;\n"\
"			output7[1] = col1 - 1;}\n"

"		else if(med == 7){\n"\
"			output2[0] = row1 - 1;\n"\
"			output2[1] = col1;\n"
"			output3[0] = row1 - 1;\n"\
"			output3[1] = col1 + 1;\n"
"			output4[0] = row1;\n"\
"			output4[1] = col1 + 1;\n"
"			output5[0] = row1 + 1;\n"\
"			output5[1] = col1 + 1;\n"
"			output6[0] = row1 + 1;\n"\
"			output6[1] = col1;\n"
"			output7[0] = row1 + 1;\n"\
"			output7[1] = col1 - 1;\n"
"			output8[0] = row1;\n"\
"			output8[1] = col1 - 1;}\n"

"		else if(med == 8){\n"\
"			output2[0] = row1 - 1;\n"\
"			output2[1] = col1;\n"
"			output3[0] = row1 - 1;\n"\
"			output3[1] = col1 + 1;\n"
"			output4[0] = row1;\n"\
"			output4[1] = col1 + 1;\n"
"			output5[0] = row1 + 1;\n"\
"			output5[1] = col1 + 1;\n"
"			output6[0] = row1 + 1;\n"\
"			output6[1] = col1;\n"
"			output7[0] = row1 + 1;\n"\
"			output7[1] = col1 - 1;\n"
"			output8[0] = row1;\n"\
"			output8[1] = col1 - 1;\n"
"			output9[0] = row1 - 1;\n"\
"			output9[1] = col1 - 1;}\n"
"	}\n"\
"}\n"\
"\n";



using namespace std;

void timer(int);
void keyboard(unsigned char key, int x, int y); //first argument is key press other two arguments are position of mouse
void generateInitialCancerCells();
void cellCounter();
void simulation(int start);
void display();
void moveMedicineCell();
void trackMedicineCells(int i, int j);

//Stacks that hold location of each type of medicine cells
vector<int> twoCoordinates;
vector<int> threeCoordinates;
vector<int> fourCoordinates;
vector<int> fiveCoordinates;
vector<int> sixCoordinates;
vector<int> sevenCoordinates;
vector<int> eightCoordinates;
vector<int> nineCoordinates;


//macros for grid
#define ROWS 500
#define COLUMNS 500

#define GLOBAL_SIZE 100

//macro for fps
#define FPS 30

//create a 2D array to hold the cell positions (initially all elements in the array are 0's which represent healthy cells)
int cell[ROWS][COLUMNS];

//add cancer cells (represented by integer 1) to 25% of the array
int totalCells = ROWS * COLUMNS;
int cancerCellCount = totalCells * 0.35;


void init() {
	glClearColor(0.0, 0.0, 0.0, 0.0); //background color
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(-0.5f, COLUMNS - 0.5f, -0.5f, ROWS - 0.5f); //(left, right, bottom, top)
}

void generateInitialCancerCells()
{
	int count = 0;
	while (count != cancerCellCount)
	{
		int row = rand() % ROWS;
		int column = rand() % COLUMNS;
		cell[row][column] = 1;

		count++;
	}
}

void setInitialCellColor()
{
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLUMNS; j++) {

			if (cell[i][j] == 0) { //if cell value is 0 change to green
				glPointSize(10.0f);
				glColor3f(0.0f, 0.5f, 0.0f); //green
				glBegin(GL_POINTS);
				glVertex2i(i, j);
				glEnd();
			}
			else if (cell[i][j] == 1) { //if cell value is 1 change to red
				glPointSize(10.0f);
				glColor3f(0.85f, 0.07f, 0.2f); //red
				glBegin(GL_POINTS);
				glVertex2i(i, j);
				glEnd();
			}
			else {					//if cell value is any other number change to yellow
				glPointSize(10.0f);
				glColor3f(1.0f, 1.0f, 0.0f); //yellow
				glBegin(GL_POINTS);
				glVertex2i(i, j);
				glEnd();
			}
		}
	}
}



void cellHealthyCheck(int x, int y)
{
	int medicineNeighbour = 0;


	if (cell[x][y] == 1) //if cell is equal to cancer cell
	{
		//check if enough neighbours are medicine cells
		for (int i = (x - 1); i < (x + 2); i++)
		{
			if (cell[i][y - 1] == 2 || cell[i][y - 1] == 3 || cell[i][y - 1] == 4 || cell[i][y - 1] == 5 || cell[i][y - 1] == 6 || cell[i][y - 1] == 7 || cell[i][y - 1] == 8 || cell[i][y - 1] == 9)
			{
				medicineNeighbour++;
			}
			if (cell[i][y + 1] == 2 || cell[i][y + 1] == 3 || cell[i][y + 1] == 4 || cell[i][y + 1] == 5 || cell[i][y + 1] == 6 || cell[i][y + 1] == 7 || cell[i][y + 1] == 8 || cell[i][y + 1] == 9)
			{
				medicineNeighbour++;
			}
		}
		if (cell[x - 1][y] == 2 || cell[x - 1][y] == 3 || cell[x - 1][y] == 4 || cell[x - 1][y] == 5 || cell[x - 1][y] == 6 || cell[x - 1][y] == 7 || cell[x - 1][y] == 8 || cell[x - 1][y] == 9)
		{
			medicineNeighbour++;
		}
		if (cell[x + 1][y] == 2 || cell[x + 1][y] == 3 || cell[x + 1][y] == 4 || cell[x + 1][y] == 5 || cell[x + 1][y] == 6 || cell[x + 1][y] == 7 || cell[x + 1][y] == 8 || cell[x + 1][y] == 9)
		{
			medicineNeighbour++;
		}

		//turn cancer cell into healthy cell and turn surounding medicine cells to healthy cells
		if (medicineNeighbour > 5)
		{
			cell[x][y] = 0;
			//turn surounding medcells to healthy cells
			for (int i = (x - 1); i < (x + 2); i++)
			{
				if (cell[i][y - 1] == 2 || cell[i][y - 1] == 3 || cell[i][y - 1] == 4 || cell[i][y - 1] == 5 || cell[i][y - 1] == 6 || cell[i][y - 1] == 7 || cell[i][y - 1] == 8 || cell[i][y - 1] == 9)
				{
					cell[i][y - 1] = 0;
				}
				if (cell[i][y + 1] == 2 || cell[i][y + 1] == 3 || cell[i][y + 1] == 4 || cell[i][y + 1] == 5 || cell[i][y + 1] == 6 || cell[i][y + 1] == 7 || cell[i][y + 1] == 8 || cell[i][y + 1] == 9)
				{
					cell[i][y + 1] = 0;
				}
			}
			if (cell[x - 1][y] == 2 || cell[x - 1][y] == 3 || cell[x - 1][y] == 4 || cell[x - 1][y] == 5 || cell[x - 1][y] == 6 || cell[x - 1][y] == 7 || cell[x - 1][y] == 8 || cell[x - 1][y] == 9)
			{
				cell[x - 1][y] = 0;
			}
			if (cell[x + 1][y] == 2 || cell[x + 1][y] == 3 || cell[x + 1][y] == 4 || cell[x + 1][y] == 5 || cell[x + 1][y] == 6 || cell[x + 1][y] == 7 || cell[x + 1][y] == 8 || cell[x + 1][y] == 9)
			{
				cell[x + 1][y] = 0;
			}
		}
	}
}

void cellCancerCheck(int x, int y)
{
	int cancerousNeighbours = 0;

	if (cell[x][y] == 0) //if cell is equal to healthy cell
	{
		//check if enough neighbours are cancer cells
		for (int i = (x - 1); i < (x + 2); i++)
		{
			if (cell[i][y - 1] == 1)
			{
				cancerousNeighbours++;
			}
			if (cell[i][y + 1] == 1)
			{
				cancerousNeighbours++;
			}
		}
		if (cell[x - 1][y] == 1)
		{
			cancerousNeighbours++;
		}
		if (cell[x + 1][y] == 1)
		{
			cancerousNeighbours++;
		}

		if (cancerousNeighbours > 5)
		{
			cell[x][y] = 1;
		}
	}


}



void display()
{
	//clear buffer at the begining of each frame
	glClear(GL_COLOR_BUFFER_BIT);

	setInitialCellColor(); //set cell color given its current value

	//Multi-threading
	std::thread thread1(simulation, ROWS / 3 * 0);
	std::thread thread2(simulation, ROWS / 3 * 1);
	std::thread thread3(simulation, ROWS / 3 * 2);

	//Wait for threads to finish
	thread1.join();
	thread2.join();
	thread3.join();

	moveMedicineCell(); //move medicine cells to new cell

	cellCounter(); //count number of each type of cell, display results

	glutKeyboardFunc(keyboard); //check for user input

	glutSwapBuffers();
}


void simulation(int start)
{
	for (int i = start; i < start + (ROWS / 3); i++) {
		for (int j = 0; j < COLUMNS; j++) {

			cellCancerCheck(i, j); //check if current cell should become cancerous

			cellHealthyCheck(i, j); //check if current cell should become healthy

			trackMedicineCells(i, j); //track movement of each medicine cell

		}
	}
}


int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(900, 900); //original 640 x 480
	glutCreateWindow("Assignment 3 - Cancer Cell Simulation");
	init(); //initialize background color and 2D ortho grid
	generateInitialCancerCells(); //randomly generate initial cancer cells in 2D array

	glutDisplayFunc(display);

	glutTimerFunc(0, timer, 0); //first argument is when the first frame is displayed, function, int value passed to timer (only executes once)

	//cout << "printing main array" << endl;
	//for (int i = 0; i < ROWS; i++)
	//{
	//	for (int j = 0; j < COLUMNS; j++)
	//	{
	//		cout << cell[i][j]<<" ";
	//	}
	//}

	glutMainLoop();
	return 0;
}

void injectMedicineCells() {

	cl_platform_id platformID; //this is where we put ID of platform
	cl_uint numOfPlatforms = 0; //The number of platforms we found

	cl_device_id deviceID; //this is where we put ID of the device (GPU)
	cl_uint numOfDevices = 0; //The number of devices we found

	cl_context context; //this is where we store the context
	cl_int err; //error code variable
	cl_command_queue commandQueue; //this is where we store the command queue

	cl_program program; //openCL program
	cl_kernel kernel; //openCL kernel

	cl_mem arr2, arr3, arr4, arr5, arr6, arr7, arr8, arr9; //Output arguments 

	//Input arguments for kernel
	int row1 = rand() % 497 + 2;
	int col1 = rand() % 497 + 2;
	int row2 = rand() % 497 + 2;
	int col2 = rand() % 497 + 2;
	int row3 = rand() % 497 + 2;
	int col3 = rand() % 497 + 2;

	int med1 = (rand() % 8) + 1;
	int med2 = (rand() % 8) + 1;
	int med3 = (rand() % 8) + 1;

	size_t global;

	//this is where the results of the kernel will be placed
	float resultArr2[6] = {};
	float resultArr3[6] = {};
	float resultArr4[6] = {};
	float resultArr5[6] = {};
	float resultArr6[6] = {};
	float resultArr7[6] = {};
	float resultArr8[6] = {};
	float resultArr9[6] = {};


	//Get list of platforms available
	// (number of platform ids that can be added, where platform id is stored, # of platforms available)
	if (clGetPlatformIDs(1, &platformID, &numOfPlatforms) != CL_SUCCESS) 
		printf("Unable to get platform ID\n");


	//Try to get a GPU device
	//(platform id, GPU device type, # of devices to return, where device id is stored, # of opencl devices that match the device type)
	if (clGetDeviceIDs(platformID, CL_DEVICE_TYPE_GPU, 1, &deviceID, &numOfDevices) != CL_SUCCESS) 
		printf("Unable to get deviceID\n");


	//Create a context with the device
	//(properties set to 0, # of devices, the device id, notify == null, user_data == null, where to return error code)
	context = clCreateContext(0, 1, &deviceID, NULL, NULL, &err);


	//create command queue with context and device
	commandQueue = clCreateCommandQueue(context, deviceID, 0, &err);



	//Program Source --> Program Object --> Program Executable --> Kernel Object 


	//Create program object from the program (kernel) source code
	program = clCreateProgramWithSource(context, 1, (const char**) &KernelSource, NULL, &err);


	//Make executable program (kernel) by compiling the program object
	if (clBuildProgram(program, 0, NULL, NULL, NULL, NULL) != CL_SUCCESS) 
		printf("Error building program\n");


	//Convert program executable into a kernel object (which kernel to execute)
	kernel = clCreateKernel(program, "multipleInjection", &err);



	//Create buffers for the output
	//2 types: buffer object (1D things, int, float, vector), and image objects (2D or 3D data such as image or texture)	
	cl_mem bufferArr2 = clCreateBuffer(context, CL_MEM_WRITE_ONLY, sizeof(float) * 6, NULL, NULL);
	cl_mem bufferArr3 = clCreateBuffer(context, CL_MEM_WRITE_ONLY, sizeof(float) * 6, NULL, NULL);
	cl_mem bufferArr4 = clCreateBuffer(context, CL_MEM_WRITE_ONLY, sizeof(float) * 6, NULL, NULL);
	cl_mem bufferArr5 = clCreateBuffer(context, CL_MEM_WRITE_ONLY, sizeof(float) * 6, NULL, NULL);
	cl_mem bufferArr6 = clCreateBuffer(context, CL_MEM_WRITE_ONLY, sizeof(float) * 6, NULL, NULL);
	cl_mem bufferArr7 = clCreateBuffer(context, CL_MEM_WRITE_ONLY, sizeof(float) * 6, NULL, NULL);
	cl_mem bufferArr8 = clCreateBuffer(context, CL_MEM_WRITE_ONLY, sizeof(float) * 6, NULL, NULL);
	cl_mem bufferArr9 = clCreateBuffer(context, CL_MEM_WRITE_ONLY, sizeof(float) * 6, NULL, NULL);



	//Set the arguments for the kernel
	clSetKernelArg(kernel, 0, sizeof(cl_mem), &bufferArr2);
	clSetKernelArg(kernel, 1, sizeof(cl_mem), &bufferArr3);
	clSetKernelArg(kernel, 2, sizeof(cl_mem), &bufferArr4);
	clSetKernelArg(kernel, 3, sizeof(cl_mem), &bufferArr5);
	clSetKernelArg(kernel, 4, sizeof(cl_mem), &bufferArr6);
	clSetKernelArg(kernel, 5, sizeof(cl_mem), &bufferArr7);
	clSetKernelArg(kernel, 6, sizeof(cl_mem), &bufferArr8);
	clSetKernelArg(kernel, 7, sizeof(cl_mem), &bufferArr9);
	clSetKernelArg(kernel, 8, sizeof(cl_int), &row1);
	clSetKernelArg(kernel, 9, sizeof(cl_int), &col1);
	clSetKernelArg(kernel, 10, sizeof(cl_int), &row2);
	clSetKernelArg(kernel, 11, sizeof(cl_int), &col2);
	clSetKernelArg(kernel, 12, sizeof(cl_int), &row3);
	clSetKernelArg(kernel, 13, sizeof(cl_int), &col3);
	clSetKernelArg(kernel, 14, sizeof(cl_int), &med1);
	clSetKernelArg(kernel, 15, sizeof(cl_int), &med2);
	clSetKernelArg(kernel, 16, sizeof(cl_int), &med3);

	

	//Enqueue the kernel command on the command queue
	//(valid command queue, valid kernel, work problem dimensions, NULL, work-items for each dimension, work-group size for each dimension, ..., ..., ...)
	global = GLOBAL_SIZE;
	if(clEnqueueNDRangeKernel(commandQueue, kernel, 1, NULL, &global, NULL, 0, NULL, NULL) != CL_SUCCESS)
		printf("Failed to enqueueNDRangeKernel.\n");



	//wait for completion of a commands on a device
	clFinish(commandQueue);



	//Copy Results from output buffer
	clEnqueueReadBuffer(commandQueue, bufferArr2, CL_TRUE, 0, sizeof(float) * 6, resultArr2, 0, NULL, NULL);
	clEnqueueReadBuffer(commandQueue, bufferArr3, CL_TRUE, 0, sizeof(float) * 6, resultArr3, 0, NULL, NULL);
	clEnqueueReadBuffer(commandQueue, bufferArr4, CL_TRUE, 0, sizeof(float) * 6, resultArr4, 0, NULL, NULL);
	clEnqueueReadBuffer(commandQueue, bufferArr5, CL_TRUE, 0, sizeof(float) * 6, resultArr5, 0, NULL, NULL);
	clEnqueueReadBuffer(commandQueue, bufferArr6, CL_TRUE, 0, sizeof(float) * 6, resultArr6, 0, NULL, NULL);
	clEnqueueReadBuffer(commandQueue, bufferArr7, CL_TRUE, 0, sizeof(float) * 6, resultArr7, 0, NULL, NULL);
	clEnqueueReadBuffer(commandQueue, bufferArr8, CL_TRUE, 0, sizeof(float) * 6, resultArr8, 0, NULL, NULL);
	clEnqueueReadBuffer(commandQueue, bufferArr9, CL_TRUE, 0, sizeof(float) * 6, resultArr9, 0, NULL, NULL);


	//display message of completion
	printf("\nPerformed computation using OpenCL on the GPU\n\n");
	printf("Updating main Simulation\n\n");


	/*printf("output: \n");
	printf("array2: \n");
	for (int i = 0; i < 6; i++)
	{
		cout << resultArr2[i] << endl;
	for (int i = 0; i < 6; i++)
	{
		cout << resultArr4[i] << endl;
	}
	printf("array5: \n");
	for (int i = 0; i < 6; i++)
	{
		cout << resultArr5[i] << endl;
	}
	printf("array6: \n");
	for (int i = 0; i < 6; i++)
	{
		cout << resultArr6[i] << endl;
	}
	printf("array7: \n");
	for (int i = 0; i < 6; i++)
	{
		cout << resultArr7[i] << endl;
	}
	printf("array8: \n");
	for (int i = 0; i < 6; i++)
	{
		cout << resultArr8[i] << endl;
	}
	printf("array9: \n");
	for (int i = 0; i < 6; i++)
	{
		cout << resultArr9[i] << endl;
	}*/

	//Update the main simulation with new data
	row1 = resultArr2[0];
	col1 = resultArr2[1];
	row2 = resultArr2[2];
	col2 = resultArr2[3];
	row3 = resultArr2[4];
	col3 = resultArr2[5];
	if (row1 != 0 && col1 != 0)
		cell[row1][col1] = 2;
	if (row2 != 0 && col2 != 0)
		cell[row2][col2] = 2;
	if (row3 != 0 && col3 != 0)
		cell[row3][col3] = 2;

	row1 = resultArr3[0];
	col1 = resultArr3[1];
	row2 = resultArr3[2];
	col2 = resultArr3[3];
	row3 = resultArr3[4];
	col3 = resultArr3[5];
	if (row1 != 0 && col1 != 0)
		cell[row1][col1] = 3;
	if (row2 != 0 && col2 != 0)
		cell[row2][col2] = 3;
	if (row3 != 0 && col3 != 0)
		cell[row3][col3] = 3;

	row1 = resultArr4[0];
	col1 = resultArr4[1];
	row2 = resultArr4[2];
	col2 = resultArr4[3];
	row3 = resultArr4[4];
	col3 = resultArr4[5];
	if (row1 != 0 && col1 != 0)
		cell[row1][col1] = 4;
	if (row2 != 0 && col2 != 0)
		cell[row2][col2] = 4;
	if (row3 != 0 && col3 != 0)
		cell[row3][col3] = 4;

	row1 = resultArr5[0];
	col1 = resultArr5[1];
	row2 = resultArr5[2];
	col2 = resultArr5[3];
	row3 = resultArr5[4];
	col3 = resultArr5[5];
	if (row1 != 0 && col1 != 0)
		cell[row1][col1] = 5;
	if (row2 != 0 && col2 != 0)
		cell[row2][col2] = 5;
	if (row3 != 0 && col3 != 0)
		cell[row3][col3] = 5;

	row1 = resultArr6[0];
	col1 = resultArr6[1];
	row2 = resultArr6[2];
	col2 = resultArr6[3];
	row3 = resultArr6[4];
	col3 = resultArr6[5];
	if (row1 != 0 && col1 != 0)
		cell[row1][col1] = 6;
	if (row2 != 0 && col2 != 0)
		cell[row2][col2] = 6;
	if (row3 != 0 && col3 != 0)
		cell[row3][col3] = 6;

	row1 = resultArr7[0];
	col1 = resultArr7[1];
	row2 = resultArr7[2];
	col2 = resultArr7[3];
	row3 = resultArr7[4];
	col3 = resultArr7[5];
	if (row1 != 0 && col1 != 0)
		cell[row1][col1] = 7;
	if (row2 != 0 && col2 != 0)
		cell[row2][col2] = 7;
	if (row3 != 0 && col3 != 0)
		cell[row3][col3] = 7;

	row1 = resultArr8[0];
	col1 = resultArr8[1];
	row2 = resultArr8[2];
	col2 = resultArr8[3];
	row3 = resultArr8[4];
	col3 = resultArr8[5];
	if (row1 != 0 && col1 != 0)
		cell[row1][col1] = 8;
	if (row2 != 0 && col2 != 0)
		cell[row2][col2] = 8;
	if (row3 != 0 && col3 != 0)
		cell[row3][col3] = 8;

	row1 = resultArr9[0];
	col1 = resultArr9[1];
	row2 = resultArr9[2];
	col2 = resultArr9[3];
	row3 = resultArr9[4];
	col3 = resultArr9[5];
	if (row1 != 0 && col1 != 0)
		cell[row1][col1] = 9;
	if (row2 != 0 && col2 != 0)
		cell[row2][col2] = 9;
	if (row3 != 0 && col3 != 0)
		cell[row3][col3] = 9;


	// Release OpenCL resources to avoid memory leaks
	clReleaseMemObject(bufferArr2);
	clReleaseMemObject(bufferArr3);
	clReleaseMemObject(bufferArr4);
	clReleaseMemObject(bufferArr5);
	clReleaseMemObject(bufferArr6);
	clReleaseMemObject(bufferArr7);
	clReleaseMemObject(bufferArr8);
	clReleaseMemObject(bufferArr9);
	clReleaseProgram(program);
	clReleaseKernel(kernel);
	clReleaseCommandQueue(commandQueue);
	clReleaseContext(context);
	
};



void trackMedicineCells(int i, int j)
{
	if (cell[i][j] == 2)
	{
		twoCoordinates.push_back(j);
		twoCoordinates.push_back(i);
	}
	if (cell[i][j] == 3)
	{
		threeCoordinates.push_back(j);
		threeCoordinates.push_back(i);
	}
	if (cell[i][j] == 4)
	{
		fourCoordinates.push_back(j);
		fourCoordinates.push_back(i);
	}
	else if (cell[i][j] == 5)
	{
		fiveCoordinates.push_back(j);
		fiveCoordinates.push_back(i);
	}
	else if (cell[i][j] == 6)
	{
		sixCoordinates.push_back(j);
		sixCoordinates.push_back(i);
	}
	else if (cell[i][j] == 7)
	{
		sevenCoordinates.push_back(j);
		sevenCoordinates.push_back(i);
	}
	else if (cell[i][j] == 8)
	{
		eightCoordinates.push_back(j);
		eightCoordinates.push_back(i);
	}
	else if (cell[i][j] == 9)
	{
		nineCoordinates.push_back(j);
		nineCoordinates.push_back(i);
	}
}

void moveMedicineCell()
{
	while (!twoCoordinates.empty())
	{
		int i = twoCoordinates.back();
		twoCoordinates.pop_back();
		int j = twoCoordinates.back();
		twoCoordinates.pop_back();

		if (j + 1 == 0 || i + 1 == 0 || i == 0 || j == 0 || i == ROWS - 1 || i == ROWS - 2 || j == COLUMNS - 2 || j == COLUMNS - 1 || i == ROWS || j == COLUMNS) //if to close to the end of array disappear
		{
			cell[i][j] = 0;
		}
		else {//move cell up
			int temp = cell[i - 1][j];
			cell[i][j] = temp;
			cell[i - 1][j] = 2;
		}
	}
	while (!threeCoordinates.empty())
	{
		int i = threeCoordinates.back();
		threeCoordinates.pop_back();
		int j = threeCoordinates.back();
		threeCoordinates.pop_back();

		if (j + 1 == 0 || i + 1 == 0 || i == 0 || j == 0 || i == ROWS - 1 || i == ROWS - 2 || j == COLUMNS - 2 || j == COLUMNS - 1 || i == ROWS || j == COLUMNS) //if to close to the end of array disappear
		{
			cell[i][j] = 0;
		}
		else {//move cell top right
			int temp = cell[i - 1][j + 1];
			cell[i][j] = temp;
			cell[i - 1][j + 1] = 3;
		}
	}
	while (!fourCoordinates.empty())
	{
		int i = fourCoordinates.back();
		fourCoordinates.pop_back();
		int j = fourCoordinates.back();
		fourCoordinates.pop_back();

		if (j + 1 == 0 || i + 1 == 0 || i == 0 || j == 0 || i == ROWS - 1 || i == ROWS - 2 || j == COLUMNS - 2 || j == COLUMNS - 1 || i == ROWS || j == COLUMNS) //if to close to the end of array disappear
		{
			cell[i][j] = 0;
		}
		else {//move cell right
			int temp = cell[i][j + 1];
			cell[i][j] = temp;
			cell[i][j + 1] = 4;
		}
	}

	while (!fiveCoordinates.empty())
	{
		int i = fiveCoordinates.back();
		fiveCoordinates.pop_back();
		int j = fiveCoordinates.back();
		fiveCoordinates.pop_back();

		if (i + 1 == 0 || j + 1 == 0 || i == 0 || j == 0 || i == ROWS - 1 || j == COLUMNS - 1) //if to close to the end of array disappear
		{
			cell[i][j] = 0;
		}
		else {//move cell bottom-right diagonal
			int temp = cell[i + 1][j + 1];
			cell[i][j] = temp;
			cell[i + 1][j + 1] = 5;
		}
	}

	while (!sixCoordinates.empty())
	{
		int i = sixCoordinates.back();
		sixCoordinates.pop_back();
		int j = sixCoordinates.back();
		sixCoordinates.pop_back();

		if (i + 1 == 0 || i == 0 || j == 0 || i == ROWS - 1 || j == COLUMNS - 1) //if to close to the end of array disappear
		{
			cell[i][j] = 0;
		}
		else {//move cell down
			int temp = cell[i + 1][j];
			cell[i][j] = temp;
			cell[i + 1][j] = 6;
		}
	}

	while (!sevenCoordinates.empty())
	{
		int i = sevenCoordinates.back();
		sevenCoordinates.pop_back();
		int j = sevenCoordinates.back();
		sevenCoordinates.pop_back();

		if (i + 1 == 0 || j - 1 == 0 || i == 0 || j == 0 || i == ROWS - 1 || j == COLUMNS - 1) //if to close to the end of array disappear
		{
			cell[i][j] = 0;
		}
		else { //move cell bottom-left down
			int temp = cell[i + 1][j - 1];
			cell[i][j] = temp;
			cell[i + 1][j - 1] = 7;
		}

	}
	while (!eightCoordinates.empty())
	{
		int i = eightCoordinates.back();
		eightCoordinates.pop_back();
		int j = eightCoordinates.back();
		eightCoordinates.pop_back();

		if (i + 1 == 0 || j - 1 == 0 || i == 0 || j == 0 || i == ROWS - 1 || j == COLUMNS - 1) //if to close to the end of array disappear
		{
			cell[i][j] = 0;
		}
		else { //move cell left
			int temp = cell[i][j - 1];
			cell[i][j] = temp;
			cell[i][j - 1] = 8;
		}

	}
	while (!nineCoordinates.empty())
	{
		int i = nineCoordinates.back();
		nineCoordinates.pop_back();
		int j = nineCoordinates.back();
		nineCoordinates.pop_back();

		if (i + 1 == 0 || j - 1 == 0 || i == 0 || j == 0 || i == ROWS - 1 || j == COLUMNS - 1) //if to close to the end of array disappear
		{
			cell[i][j] = 0;
		}
		else { //move cell top left
			int temp = cell[i - 1][j - 1];
			cell[i][j] = temp;
			cell[i - 1][j - 1] = 9;
		}

	}
}



void cellCounter()
{
	int healthyCells = 0;
	int cancerCells = 0;
	int medicineCells = 0;

	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLUMNS; j++)
		{
			if (cell[i][j] == 0)
			{
				healthyCells++;
			}
			else if (cell[i][j] == 1)
			{
				cancerCells++;
			}
			else
			{
				medicineCells++;
			}
		}
	}
	cout << "Healthy: " << healthyCells;
	cout << ", Cancer: " << cancerCells;
	cout << ", Medicine: " << medicineCells << endl;

}

void keyboard(unsigned char key, int x, int y) //we dont need to know mouse position
{
	if (key == 27) // pressing escape key will end the program
	{
		exit(0);
	}

	if (key == 32) //pressing spacebar will generate a new random injection of medicine cells (32 == ascii code)
	{
		injectMedicineCells();
	}
}

void timer(int)
{
	glutPostRedisplay(); //tells opengl to call display function
	//re call the glutTimerFunc found in main
	//if we want 10 fps, 1s = 1000ms ,  1s / 10frames = 10 frames per second 
	glutTimerFunc(1000 / FPS, timer, 0);
}
 