#ifndef OGLWIDGET_H
#define OGLWIDGET_H

#include <QWidget>
#include <QOpenGLWidget>
#include <gl/GLU.h>
#include <gl/GL.h>
#include <chrono>
#include <qtimer.h>

class GLWidget : public QOpenGLWidget
{
	Q_OBJECT

public:
	GLWidget(QWidget *parent = 0);
	~GLWidget();

private:
	GLuint texture;
	QTimer timer;
	uint imageWidth;
	uint imageHeight;
	GLenum pixelFormat = GL_BGRA;
	uint channels = 4; // bgra format
	uint imageSize;
	GLubyte *image;
	uint count = 0;
	bool working = false;

	GLint windowWidth;
	GLint windowHeight;

	void updater();
	void updatePixels(GLubyte* dst, int size);

protected:
	void initializeGL();
	void resizeGL(int w, int h);
	void paintGL();

private slots:
	void sender();
signals:
	void sendThroughput(float MBps);
};

#endif // OGLWIDGET_H