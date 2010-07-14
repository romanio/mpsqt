#include "glwidget.h"
#include <QQuaternion>
#include <QMouseEvent>

GLWidget::GLWidget():QGLWidget(QGLFormat(QGL::DoubleBuffer))
{
	startVector.setX(0);
	startVector.setY(0);
	startVector.setZ(0);
	endVector.setX(0);
	endVector.setY(0);
	endVector.setZ(0);
	isLeftDrag = false;
	isMidDrag = false;
        isRightDrag = false;
        scale = 1.0f;
}

QSize GLWidget::sizeHint() const
{
	return QSize(400, 200);
}

void GLWidget::initializeGL()
{
	setMouseTracking(true);
	glClearColor(255.0f, 255.0f, 255.0f, 0.0f);
	glPolygonMode(GL_FRONT, GL_LINE);
        glLineWidth(2);
        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
        glFrontFace(GL_CCW);
        //
}


void GLWidget::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();
        glScalef(scale, scale, scale);
        static GLfloat mat[16];
	const qreal* data = mCurRotation.constData();
	for (int index = 0; index < 16; ++index)
		mat[index] = data[index];
	glMultMatrixf(mat);
	//
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_TRIANGLES);
	glVertex3f(-1.0f, -0.5f, 0.0f);
	glVertex3f(1.0f, -0.5f, 0.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);
	glEnd();

}

void GLWidget::resizeGL(int w, int h)
{
	float aspect = w / (float)(w ? h : 1);
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
        gluPerspective(30.0f, aspect, 1.0f, 40.0f);
        gluLookAt(0.0f, 0.0f, 10.0f, 0, 0, 0.0f, 0.0f, 1.0f, 0.0f);
	glMatrixMode(GL_MODELVIEW);
}

void GLWidget::mousePressEvent(QMouseEvent *e)
{
}

void GLWidget::wheelEvent(QWheelEvent *e)
{
    e->delta() > 0? scale *= 1.05f : scale  *= 0.95f;
     this->updateGL();
}

void GLWidget::mouseMoveEvent(QMouseEvent *e)
{
    QPointF pos;
    pos = e->posF();

	if (e->buttons() & Qt::RightButton)
	{
		if (!isRightDrag)
		{
			mLastRotation = mCurRotation;
                        mapToSphere(&pos, &startVector);
                        isRightDrag = true;
                }
		else
		{
                    mapToSphere(&pos, &endVector);
                    float x = (float)(endVector.x() - startVector.x());
                    float y = (float)(endVector.y() - startVector.y());
                    float z = 0;
                    QVector3D pan(x, y, z);

                     QQuaternion rot(0.0f, 0.0f, 0.0f, 0.0f);
                        matrixConversion(mCurRotation, &pan, &rot);
			mCurRotation = mCurRotation * mLastRotation;
			this->updateGL();
                }
	}
	else
	{
                isRightDrag = false;
	}
	//

	if (e->buttons() & Qt::MidButton)
	{
		if (!isMidDrag) // Begin rotation
		{
			mLastRotation = mCurRotation;
                        mapToSphere(&pos, &startVector);
			isMidDrag = true;
		}
		else // ...and continue rotation
		{
			QQuaternion rot;
                        mapToSphere(&pos, &endVector);

			QVector3D vp = QVector3D::crossProduct(startVector, endVector);
			if (vp.length() > 1e-5) // If start and end vector not equal
			{
				rot.setX(vp.x());
				rot.setY(vp.y());
				rot.setZ(vp.z());
				rot.setScalar(QVector3D::dotProduct(startVector, endVector));
				// convert to matrix with scaling, pan and rotate
                                QVector3D pan(0, 0, 0);
                                matrixConversion(mCurRotation, &pan, &rot);
				mCurRotation = mCurRotation * mLastRotation;
				this->updateGL();
			}
		}
	}
	else
	{
		isMidDrag = false;
	}


}

void GLWidget::matrixConversion(QMatrix4x4& m, const QVector3D *pan, const QQuaternion *rot)
{
	float n, s;
	float xs, ys, zs;
	float wx, wy, wz;
	float xx, xy, xz;
	float yy, yz, zz;
        n = rot->x() * rot->x() + rot->y() * rot->y() + rot->z()*rot->z() + rot->scalar()*rot->scalar();
	s = (n > 0.0f) ? 2.0f / n : 0.0f;

	xs = rot->x() * s;
	ys = rot->y() * s;
	zs = rot->z() * s;
	wx = rot->scalar()* xs;
	wy = rot->scalar() * ys;
	wz = rot->scalar() * zs;
	xx = rot->x()* xs;
	xy = rot->x() * ys;
	xz = rot->x() * zs;
	yy = rot->y() * ys;
	yz = rot->y() * zs;
	zz = rot->z() * zs;
	// rotation
	m(0, 0) = 1.0f - (yy + zz);
	m(0, 1) = xy - wz;
	m(0, 2) = xz + wy;
        m(0, 3) = pan->x();

	m(1, 0) = xy + wz;
	m(1, 1) = 1.0f - (xx + zz);
	m(1, 2) = yz - wx;
        m(1, 3) = pan->y();

	m(2, 0) = xz - wy;
	m(2, 1) = yz + wx;
	m(2, 2) = 1.0f - (xx + yy);
        m(2, 3) = 0.0;

        m(3, 0) = 0.0f;
        m(3, 1) = 0.0f;
        m(3, 2) = 0.0f;
	m(3, 3) = 1.0f;
}
