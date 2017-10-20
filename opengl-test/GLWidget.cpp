#include "GLWidget.h"
#include <qmessagebox.h>
#include <thread>

GLWidget::GLWidget(QWidget *parent)
	: QOpenGLWidget(parent)
{
	imageWidth = 1500;
	imageHeight = 1000;
	
	imageSize = imageWidth * imageHeight * channels;
	// allocate memory for image
	image = (GLubyte *)malloc(imageSize * sizeof(GLubyte));
	memset(image, 0, imageSize);

	connect(&timer, &QTimer::timeout, this, &GLWidget::sender);

	// start a new thread that updates the image
	// (&DAQ::worker_acquire, this, acquisitions_count);
	
}

void GLWidget::updatePixels(GLubyte* dst, int size)
{
	auto start = std::chrono::system_clock::now();
	static int color = 0;

	if (!dst)
		return;

	GLubyte* ptr = dst;
	// copy 4 bytes at once


	for (int i = 0; i < this->imageHeight ; ++i)
	{
	
		int val = ((float)i / imageHeight) * 255;

		for (int j = 0; j < this->imageWidth; ++j)
		{
			*ptr = val;
			*(ptr + 1) = val;
			*(ptr + 2) = 0;
			*(ptr + 3) = 0;
			ptr += 4;
		}
		color += 200;   // add an arbitary number (no meaning)
	}
	//++color;            // scroll down

	auto end = std::chrono::system_clock::now();
	auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	float ms = elapsed.count();
}

GLWidget::~GLWidget()
{
	free(this->image);
	image = NULL;

	glDeleteTextures(1, &texture);
}

void GLWidget::updater()
{
	//GLubyte *newImage = (GLubyte *)malloc(imageSize * sizeof(GLubyte));	
	int *newImage = (int*) this->image;
	int idx = 0;
	int bytesPerRow = this->imageWidth * this->channels;
	for (int i = 0; i < this->imageHeight; i++)
	{
		int val = rand() % 2000;
		//int val = 300;
		for ( ; idx<bytesPerRow ; idx+=4)
		{
			newImage[idx] = val;
			newImage[idx + 1] = val;
			newImage[idx + 2] = val;
			newImage[idx + 3] = val;
		}
		idx = 0;
	}

	//GLubyte *tmp = this->image;
	//this->image = newImage;
	//free(tmp);
}

void GLWidget::initializeGL()
{	
	glShadeModel(GL_FLAT);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	
	glEnable(GL_DEPTH_TEST);	
	glDisable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_CULL_FACE);

	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);

	// background color
	glClearColor(0.1, 0.9, 0.1, 1);

	glClearStencil(0);
	glClearDepth(1.0f);
	glDepthFunc(GL_LEQUAL);

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, imageWidth, imageHeight, 0, pixelFormat, GL_UNSIGNED_BYTE, (GLvoid*)image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// get viewport size
	GLint params[4];	
	glGetIntegerv(GL_VIEWPORT, params);
	this->windowWidth = params[2];
	this->windowHeight = params[3];

	timer.start(16);
}

void GLWidget::sender()
{
	update();
	//update();
	updatePixels(this->image, 0);
	//std::thread t(&GLWidget::updater, this);
	//t.detach();
	//float throughput = count/0.5 * imageSize / 1e6 ;
	//count = 0;
	//emit sendThroughput(throughput);
}

void GLWidget::paintGL()
{

	auto start = std::chrono::system_clock::now();

	// upload pixels to GPU
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, imageWidth, imageHeight,
		pixelFormat, GL_UNSIGNED_BYTE, (GLvoid*)image);
	
	//updatePixels(this->image, 0);
	
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	
	glPushMatrix();
	glTranslatef(0, 0, -0.0f);
	glRotatef(0, 1, 0, 0);
	glRotatef(0, 0, 1, 0);

	glBindTexture(GL_TEXTURE_2D, texture);
	glColor4f(1, 1, 1, 1);

	glBegin(GL_QUADS);
	glNormal3f(0, 0, 1);
	glTexCoord2f(0.0f, 0.0f);   glVertex3f(-1.0f, -1.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f);   glVertex3f( 1.0f, -1.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f);   glVertex3f( 1.0f,  1.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f);   glVertex3f(-1.0f,  1.0f, 0.0f);
	glEnd();
	glMatrixMode(GL_TEXTURE);
	glLoadIdentity();
	glTranslatef(0.5, 0.5, 0.0);
	glRotatef(180, 0.0, 0.0, 1.0);
	glTranslatef(-0.5, -0.5, 0.0);
	glMatrixMode(GL_MODELVIEW);
	// unbind texture
	glBindTexture(GL_TEXTURE_2D, 0);

	glPopMatrix();

	auto end = std::chrono::system_clock::now();
	auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	float ms = elapsed.count();
	
	emit sendThroughput(ms);
	
}

void GLWidget::resizeGL(int w, int h)
{
	this->windowHeight = h;
	this->windowWidth = w;

	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, (float)w / h, 0.01, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 0, 5, 0, 0, 0, 0, 1, 0);
}