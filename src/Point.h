/*
 * Point.h
 *
 *  Created on: Mar 16, 2015
 *      Author: vostanin
 */

#ifndef POINT_H_
#define POINT_H_

#include "IGeometryObject.h"

class Point : public IGeometryObject
{
public:
	Point();
	Point( int x, int y );
	Point( const Point & src );
	bool operator == ( Point & src );
	virtual ~Point();

	int getX();
	int getY();

	void setX( int x );
	void setY( int y );

	GeometryObjectsTypes getType();
private:
	int m_x;
	int m_y;
};

#endif /* POINT_H_ */
