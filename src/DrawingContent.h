/*
 * DrawingContent.h
 *
 *  Created on: Mar 16, 2015
 *      Author: vostanin
 */

#ifndef DRAWINGCONTENT_H_
#define DRAWINGCONTENT_H_

#include "GraphicPoint.h"
#include "Timer.h"
#include <Evas.h>
#include <vector>
using namespace std;

class DrawingContent
{

public:
	DrawingContent( Evas_Object *mainWindowObject, Evas_Object *mainLayout );
	virtual ~DrawingContent();

	Evas_Object * getDrawingCanvas();

	void update();

	void setGraphicObjects( vector<IGraphicObject *> & graphicObjects );
	void addGraphicObject( IGraphicObject * graphicObject );
	void deleteGraphicObject( IGraphicObject * graphicObject );
	void changeGraphicObject( IGraphicObject * graphicObject );

   void setGraphicDynamicObjects( vector<IGraphicObject *> & graphicObjects );

   unsigned int getCanvasWidth() const;
   unsigned int getCanvasHeight() const;

private:

	void createDrawingLayout();
	void createDrawingCanvas();
	void preDraw();
	void postDraw();
	void drawObjects();
	void clearObjects();

	static void on_init_gles( Evas_Object * glview );
	static void on_resize_gl( Evas_Object * glview );
	static void on_draw_gl( Evas_Object * glview );
    static void on_draw_dynamic_gl( Evas_Object * glview );

    static bool DynamicDrawTimer( void * userData );

	Evas_Object * m_MainLayout;
	Evas_Object * m_DrawingLayout;

	Evas_Object * m_MainWindowObject;

	Evas_Object * m_DrawingCanvas;

	Evas_GL_API * m_glApi;

	vector<IGraphicObject *> m_GraphicObjects;

	Timer m_DynamicTimer;

	int m_CanvasWidth;
	int m_CanvasHeight;

	bool m_DrawDynamic;
};

#endif /* DRAWINGCONTENT_H_ */
