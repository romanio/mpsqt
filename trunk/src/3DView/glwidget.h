#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QVector3D>
#include <QVector2D>
#include <QVector3D>
#include <QVector2D>
#include <QMatrix3x3>
#include <QMatrix4x4>
#include <qmath.h>

class GLWidget : public QGLWidget
{
	Q_OBJECT
public:
	GLWidget();
	QSize sizeHint() const;
private:
	// Trackball property
	QVector3D startVector;
	QVector3D endVector;
	QMatrix4x4 mLastRotation;
	QMatrix4x4 mCurRotation;
	bool isLeftDrag;
	bool isMidDrag;
	bool isRightDrag;
	float scale;

	void mapToSphere(const QPointF* point, QVector3D* vector) const
	{
		float x = 2 * (point->x()/width()) - 1.0f;
		float y = 1.0f - 2 * (point->y()/height());
		float len = x * x + y * y;

		if (len > 1.0f)
		{
			float norm = 1.0f / sqrt(len);
			vector->setX(x * norm);
			vector->setY(y * norm);
			vector->setZ(0);
		}
		else
		{
			vector->setX(x);
			vector->setY(y);
			vector->setZ(sqrt(1.0f - len));
		}
	}

	void matrixConversion(QMatrix4x4& m, const QVector3D* pan, const QQuaternion* rot);

protected:
	void initializeGL();
	void paintGL();
	void resizeGL(int w, int h);
	void mouseMoveEvent(QMouseEvent *e);
	void mousePressEvent(QMouseEvent *e);
	void wheelEvent(QWheelEvent *e);
};

#endif // GLWIDGET_H
