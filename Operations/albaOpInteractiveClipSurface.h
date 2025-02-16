/*=========================================================================

 Program: ALBA (Agile Library for Biomedical Applications)
 Module: albaOpInteractiveClipSurface
 Authors: Paolo Quadrani , Stefano Perticoni , Matteo Giacomoni
 
 Copyright (c) BIC
 All rights reserved. See Copyright.txt or


 This software is distributed WITHOUT ANY WARRANTY; without even
 the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 PURPOSE.  See the above copyright notice for more information.

=========================================================================*/

#ifndef __albaOpInteractiveClipSurface_H__
#define __albaOpInteractiveClipSurface_H__

//----------------------------------------------------------------------------
// Include :
//----------------------------------------------------------------------------
#include "albaDefines.h"
#include "albaOp.h"
#include "albaVME.h"
#include "albaVMESurface.h"

#include "albaVMEPolylineGraph.h"

//----------------------------------------------------------------------------
// forward references :
//----------------------------------------------------------------------------
class albaEvent;
class albaInteractorCompositorMouse;
class albaInteractorGenericMouse;
class albaVMESurface;
class albaVMEGizmo;
class albaVME;
class albaGizmoTranslate;
class albaGizmoRotate;
class albaGizmoScale;

class albaCurvilinearAbscissaOnSkeletonHelper;

class vtkPlane;
class vtkPolyData;
class vtkClipPolyData;
class vtkGlyph3D;
class vtkSphereSource;
class vtkPlaneSource;
class vtkArrowSource;
class vtkAppendPolyData;
class vtkALBAClipSurfaceBoundingBox;

//----------------------------------------------------------------------------
// albaOpInteractiveClipSurface :
//----------------------------------------------------------------------------
/** */
class ALBA_EXPORT albaOpInteractiveClipSurface: public albaOp
{
public:
  albaOpInteractiveClipSurface(const wxString &label = "Interactive Clip Surface");
  ~albaOpInteractiveClipSurface(); 
	virtual void OnEvent(albaEventBase *alba_event);

  albaTypeMacro(albaOpInteractiveClipSurface, albaOp);

  albaOp* Copy();

  void OpRun();

  /** Execute the operation. */
  /*virtual*/ void OpDo();

  void OpUndo();

  enum CLIP_SURFACE_MODALITY
  {
    MODE_SURFACE = 0,
    MODE_IMPLICIT_FUNCTION
  };

	enum GIZMO_TYPE
	{
		GIZMO_TRANSLATE = 0,
		GIZMO_ROTATE,
		GIZMO_SCALE,
	};
  
 	static bool SurfaceAccept(albaVME*node) {return(node != NULL && node->IsALBAType(albaVMESurface));};

  /** Set the modality to clip input surface. Available modality are MODE_SURFACE or MODE_IMPLICIT_FUNCTION*/
  void SetClippingModality(int mode = albaOpInteractiveClipSurface::MODE_IMPLICIT_FUNCTION);

  /** Set the surface VME to use to clip the input surface. It is used only in MODE_SURFACE modality clip*/
  void SetClippingSurface(albaVMESurface *surface);

  /** Set the absolute position for the implicit plane used to clip the input surface*/
  void SetImplicitPlanePosition(albaMatrix &matrix);

  /** Function called to clip the input surface. m_ClipModality member variable, says if the surface will be clipped by 
  another surface or by an implicit function. */
  virtual int Clip();

	/** Function that returns polydata results of clipping operation*/
	vtkPolyData *GetResultPolyData(){return m_ResultPolyData[m_ResultPolyData.size()-1];};

  static bool ConstrainAccept(albaVME* node) {return (node != NULL && \
    (node->IsALBAType(albaVMEPolylineGraph))) ;};

protected: 

	/** Return true for the acceptable vme type. */
	bool InternalAccept(albaVME*node);

	virtual void OpStop(int result);
	
  /** Show/hide the gizmo representing the clipping implicit plane. */
  void ShowClipPlane(bool show);

	/** Show/hide the gizmo for scaling implicit plane. */
	void ShowGizmoScale(bool show);

  /** Attach the interaction to the implicit plane. */
  void AttachInteraction();

  /** Update interactor ref sys*/
  void UpdateISARefSys();

	/** Create the GUI */
	virtual void CreateGui();

  void GuiEnable();
	/** Change Gizmo visualization */
	void BuildTransformGizmos();

	/** Change type of gizmo in the view */
	void ChangeGizmo();

	/** Menage the undo inside the operation */
	void Undo();

  void OnUseGizmo();

	void OnEventThis(albaEventBase *alba_event);
	void OnEventGizmoTranslate(albaEventBase *alba_event);
	void OnEventGizmoRotate(albaEventBase *alba_event);
	void OnEventGizmoScale(albaEventBase *alba_event);
	void OnEventGizmoPlane(albaEventBase *alba_event);

  void OnChooseConstrainVme( albaVME *vme );

	void PostMultiplyEventMatrix(albaEventBase *alba_event);

	/** Clip Using vtkALBAClipSurfaceBoundingBox */
	void ClipBoundingBox();
  
  albaVMESurface   *m_ClipperVME;
	albaVMESurface   *m_ClippedVME;

  albaVMEGizmo     *m_ImplicitPlaneVMEGizmo;
  vtkPlane        *m_ClipperPlane;
  vtkClipPolyData *m_Clipper;
	vtkALBAClipSurfaceBoundingBox	*m_ClipperBoundingBox;
  vtkGlyph3D      *m_Arrow;

  albaInteractorCompositorMouse *m_IsaCompositor;
  albaInteractorGenericMouse    *m_IsaTranslate;
	albaInteractorGenericMouse		 *m_IsaChangeArrowWithoutGizmo;
	albaInteractorGenericMouse		 *m_IsaClipWithoutGizmo;
	albaInteractorCompositorMouse *m_IsaCompositorWithArrowGizmo;
	albaInteractorGenericMouse		 *m_IsaChangeArrowWithGizmo;
	albaInteractorGenericMouse		 *m_IsaClipWithGizmo;

  vtkPolyData *m_OldSurface;
	std::vector<vtkPolyData*> m_ResultPolyData;

  int		m_ClipModality;
	int		m_GizmoType;
  int		m_ClipInside;
	int   m_UseGizmo;
	int		m_ClipBoundBox;
  bool	m_PlaneCreated;

	double m_PlaneWidth;
	double m_PlaneHeight;

	vtkPlaneSource	*m_PlaneSource;
	vtkArrowSource	*m_ArrowSource;
	vtkAppendPolyData	*m_AppendPolydata;
  vtkSphereSource *m_SphereSource;

  albaGizmoTranslate		*m_GizmoTranslate;
	albaGizmoRotate			*m_GizmoRotate;
	albaGizmoScale				*m_GizmoScale;

  albaCurvilinearAbscissaOnSkeletonHelper *m_CASH;
  
  albaVME *m_ConstrainalbaVMEPolylineGraph;

  int m_ActiveBranchId;

};
#endif
