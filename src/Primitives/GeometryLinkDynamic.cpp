/*
 * GeometryLinkDynamic.cpp
 *
 *  Created on: Apr 1, 2015
 *      Author: vostanin
 */

#include "GeometryLinkDynamic.h"
#include <string.h>
#include <iostream>

GeometryLinkDynamic::GeometryLinkDynamic( cpSpace * space ) : m_Space( space ), m_ConstraintFromTo( 0 )
{
	memset( m_DynamicPoints, 0, sizeof( m_DynamicPoints ) );
	initLink();
}

GeometryLinkDynamic::GeometryLinkDynamic( cpSpace * space, GeometryLink * geometryLink ) : m_Space( space ), m_ConstraintFromTo( 0 )
{
	memset( m_DynamicPoints, 0, sizeof( m_DynamicPoints ) );
	setPointFrom( geometryLink->getPointFrom() );
	setPointTo( geometryLink->getPointTo() );
    setId( geometryLink->getId() );

	initLink();
}

GeometryLinkDynamic::~GeometryLinkDynamic()
{
	if( 0 != m_ConstraintFromTo && true == cpSpaceContainsConstraint( m_Space, m_ConstraintFromTo ) )
	{
		cpSpaceRemoveConstraint( m_Space, m_ConstraintFromTo );
		cpConstraintFree( m_ConstraintFromTo );
		m_ConstraintFromTo = 0;
	}

	if( true == cpSpaceContainsShape( m_Space, m_Shape ) )
	{
		cpSpaceRemoveShape( m_Space, m_Shape );
		cpShapeFree( m_Shape );
		m_Shape = 0;
	}
	if( true == cpSpaceContainsBody( m_Space, m_Body ) )
	{
		cpSpaceRemoveBody( m_Space, m_Body );
		cpBodyFree( m_Body );
		m_Body = 0;
	}
}

void GeometryLinkDynamic::initLink()
{
	cpFloat radius = 0.1;
	cpFloat mass = 1;

	int boxWidth = abs( getPointFrom()->getX() - getPointTo()->getX() );
	int boxHeight = abs( getPointFrom()->getY() - getPointTo()->getY() );

	cpVect startPoint = cpv( getPointFrom()->getX(), getPointFrom()->getY() );
	cpVect endPoint = cpv( getPointTo()->getX(), getPointTo()->getY() );
//	cpFloat moment = cpMomentForSegment( mass, startPoint, endPoint, radius );
	cpFloat moment = cpMomentForBox( mass, boxWidth, boxHeight );
	m_Body = cpBodyNew( mass, moment );

	cpSpaceAddBody( m_Space, m_Body );
//
//	m_Shape = cpSegmentShapeNew( m_Body, startPoint, endPoint, radius );
//
//
////	cpShapeSetFriction( m_Shape, 100 );
//	cpSpaceAddShape( m_Space, m_Shape );
}

void GeometryLinkDynamic::initJoints()
{
	if( 0 != getDynamicPointFrom() && 0 != getDynamicPointTo() )
	{
		m_ConstraintFromTo = cpSpaceAddConstraint( m_Space, cpPinJointNew( getDynamicPointTo()->getBody(), getDynamicPointFrom()->getBody(), cpvzero, cpvzero ) );
//		m_ConstraintFromTo = cpSpaceAddConstraint( m_Space, cpDampedSpringNew( getDynamicPointTo()->getBody(), getDynamicPointFrom()->getBody(), cpvzero, cpvzero, 50, 50, 1.0 ) );

//		cpVect boxOffset = cpvzero;
//		int width = abs( getPointFrom()->getX() - getPointTo()->getX() );
//
//		cpVect globalTo = cpvzero;
//		cpVect globalFrom = cpvzero;
//		cpVect localFrom = cpBodyWorldToLocal( m_Body, globalFrom );
//		cpVect globalFrom_2 = cpBodyLocalToWorld( m_Body, localFrom );
//
//		globalFrom = cpv( getDynamicPointFrom()->getX(), getDynamicPointFrom()->getY() );
//		globalTo   = cpv( getDynamicPointTo()->getX(),   getDynamicPointTo()->getY() );
//
//		m_ConstraintFrom = cpPivotJointNew( m_Body, getDynamicPointFrom()->getBody(), globalFrom );
//		m_ConstraintTo   = cpPivotJointNew( m_Body, getDynamicPointTo()->getBody(), globalTo );
//		cpConstraintSetMaxBias( m_ConstraintFrom, INFINITY );
//		cpConstraintSetMaxBias( m_ConstraintTo, INFINITY );
//		cpConstraintSetMaxForce( m_ConstraintFrom, INFINITY );
//		cpConstraintSetMaxForce( m_ConstraintTo, INFINITY );
//		cpSpaceAddConstraint( m_Space, m_ConstraintFrom );
//		cpSpaceAddConstraint( m_Space, m_ConstraintTo );
	}
}

void GeometryLinkDynamic::clearJoints()
{
	if( m_ConstraintFromTo != 0 )
	{
		cpConstraintFree( m_ConstraintFromTo );
		m_ConstraintFromTo = 0;
	}
}

void GeometryLinkDynamic::setDynamicPointFrom( GeometryPointDynamic * dynamicPoint )
{
	m_DynamicPoints[0] = dynamicPoint;
    setPointFrom( (const GeometryPoint *)&dynamicPoint->getGeometryObject() );

    clearJoints();
    initJoints();
}

void GeometryLinkDynamic::setDynamicPointTo( GeometryPointDynamic * dynamicPoint )
{
	m_DynamicPoints[1] = dynamicPoint;
    setPointTo( (const GeometryPoint *)&dynamicPoint->getGeometryObject() );

    clearJoints();
    initJoints();
}

GeometryPointDynamic * GeometryLinkDynamic::getDynamicPointFrom() const
{
	return m_DynamicPoints[0];
}

GeometryPointDynamic * GeometryLinkDynamic::getDynamicPointTo() const
{
	return m_DynamicPoints[1];
}

cpBody * GeometryLinkDynamic::getBody() const
{
	return m_Body;
}

cpShape * GeometryLinkDynamic::getShape() const
{
	return m_Shape;
}

cpSpace * GeometryLinkDynamic::getSpace() const
{
	return m_Space;
}

const IGeometryObject & GeometryLinkDynamic::getGeometryObject() const
{
	return *this;
}

void GeometryLinkDynamic::update()
{
//	cpFloat moment = cpShapeGetMoment( m_Shape );
//	cout << "link moment=" << moment << endl << flush;
}










