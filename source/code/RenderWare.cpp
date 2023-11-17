#include "RenderWare.h"
#include "manhunt/core.h"

RwBool RpWorldDestroy(RpWorld * world)
{
	return CallAndReturn<RwBool, 0x616290, RpWorld *>(world);
}

RpWorld* RpWorldCreate(RwBBox * boundingBox)
{
	return CallAndReturn<RpWorld*, 0x6163E0, RwBBox *>(boundingBox);
}

RwTexDictionary *RwTexDictionarySetCurrent(RwTexDictionary * dict)
{
	return CallAndReturn<RwTexDictionary*, 0x62F6E0, RwTexDictionary*>(dict);
}

RpClump* RpClumpRender(RpClump * clump)
{
	return CallAndReturn<RpClump*, 0x61ABF0, RpClump*>(clump);
}

RwReal RwV3dLength(const RwV3d * in)
{
	return CallAndReturn<RwReal, 0x615430, const RwV3d*>(in);
}

RwModuleInfo &vectorModule = *(RwModuleInfo*)0x8227B0;

#define RWVECTORGLOBAL(var) (RWPLUGINOFFSET(rwVectorGlobals, RwEngineInstance, vectorModule.globalsOffset)->var)

typedef RwV3d *(*rwVectorMultFn) (RwV3d * pointOut,
                                  const RwV3d * pointIn,
                                  const RwMatrix * matrix);

typedef RwV3d *(*rwVectorsMultFn) (RwV3d * pointsOut,
                                   const RwV3d * pointsIn,
                                   RwInt32 numPoints,
                                   const RwMatrix * matrix);


typedef struct rwVectorGlobals rwVectorGlobals;
struct rwVectorGlobals
{
     RwSplitBits *SqrtTab;
     RwSplitBits *InvSqrtTab;


    rwVectorMultFn  multPoint;
    rwVectorsMultFn multPoints;
    rwVectorMultFn  multVector;
    rwVectorsMultFn multVectors;
};

RwV3d *RwV3dTransformPoints(RwV3d * pointsOut, const RwV3d * pointsIn, RwInt32 numPoints, const RwMatrix * matrix)
{
   return RWVECTORGLOBAL(multPoints)(pointsOut, pointsIn, numPoints, matrix);
}

RwMatrix *
RwMatrixInvert(RwMatrix * matrixOut, const RwMatrix * matrixIn)
{
	return CallAndReturn<RwMatrix *, 0x619880, RwMatrix *, const RwMatrix *>(matrixOut, matrixIn);
}

void _rpAtomicResyncInterpolatedSphere(RpAtomic * atomic)
{
	return Call<0x61A390, RpAtomic *>(atomic);
}

void CameraSize(RwCamera * camera, RwRect * rect, RwReal viewWindow, RwReal aspectRatio)
{
	RwVideoMode         videoMode;
	RwRect              r;
	RwRect              origSize = { 0, 0, 0, 0 };	// FIX just to make the compier happy
	RwV2d               vw;

	viewWindow *= aspectRatio;

	RwEngineGetVideoModeInfo(&videoMode,RwEngineGetCurrentVideoMode());

	origSize.w = RwRasterGetWidth(RwCameraGetRaster(camera));
	origSize.h = RwRasterGetHeight(RwCameraGetRaster(camera));


	if (!rect)
	{
		if (videoMode.flags & rwVIDEOMODEEXCLUSIVE)
		{
			/* For full screen applications, resizing the camera just doesn't
			 * make sense, use the video mode size.
			 */

			r.x = r.y = 0;
			r.w = videoMode.width;
			r.h = videoMode.height;
			rect = &r;
		}
		else
		{
			/*
			rect not specified - reuse current values
			*/
			r.w = RwRasterGetWidth(RwCameraGetRaster(camera));
			r.h = RwRasterGetHeight(RwCameraGetRaster(camera));
			r.x = r.y = 0;
			rect = &r;
		}
	}

	if (videoMode.flags & rwVIDEOMODEEXCLUSIVE)
	{
		/* derive ratio from aspect ratio */
		vw.x = viewWindow;
		vw.y = viewWindow / aspectRatio;
	}
	else
	{
		/* derive from pixel ratios */
		if (rect->w > rect->h)
		{
			vw.x = viewWindow;
			vw.y = (rect->h * viewWindow) / rect->w;
		}
		else
		{
			vw.x = (rect->w * viewWindow) / rect->h;
			vw.y = viewWindow;
		}
	}

	RwCameraSetViewWindow(camera, &vw);
}

RwStream* RwStreamOpen(RwStreamType type, RwStreamAccessType accessType,	const void *pData)
{
	return CallAndReturn<RwStream*, 0x6121A0, RwStreamType, RwStreamAccessType, const void*>(type,accessType,pData);
}
RwBool RwStreamFindChunk(RwStream *stream, RwUInt32 type, RwUInt32 *lengthOut, RwUInt32 *versionOut)
{
	return CallAndReturn<RwBool, 0x63C420, RwStream*, RwUInt32, RwUInt32*, RwUInt32*>(stream,type,lengthOut,versionOut);
}

RpClump* RpClumpStreamRead(RwStream* stream)
{
	return CallAndReturn<RpClump*, 0x61C1B0, RwStream*>(stream);
}

RwBool RwStreamClose(RwStream * stream, void *pData)
{
	return CallAndReturn<RwBool, 0x6120D0, RwStream*,void*>(stream, pData);
}

RwFrame *RwFrameTransform(RwFrame * frame, const RwMatrix * m, RwOpCombineType combine)
{
	return CallAndReturn<RwFrame*, 0x618900, RwFrame*, const RwMatrix*, RwOpCombineType>(frame,m,combine);
}

RwFrame* RwFrameTranslate(RwFrame * frame, const RwV3d * v, RwOpCombineType combine)
{
	return CallAndReturn<RwFrame*, 0x618860, RwFrame*, const RwV3d*, RwOpCombineType>(frame, v, combine);
}

RwFrame* RwFrameUpdateObjects(RwFrame * frame)
{
	return CallAndReturn<RwFrame*, 0x618440, RwFrame*>(frame);
}
RwFrame *RwFrameRotate(RwFrame * frame, const RwV3d * axis, RwReal angle, RwOpCombineType combine)
{
	return CallAndReturn<RwFrame*, 0x6189A0, RwFrame*, const RwV3d*, RwReal, RwOpCombineType>(frame, axis, angle, combine);
}
RwCamera* RwCameraBeginUpdate(RwCamera * camera)
{
	return CallAndReturn<RwCamera*, 0x6260E0, RwCamera*>(camera);
}
RwCamera* RwCameraEndUpdate(RwCamera * camera)
{
	return CallAndReturn<RwCamera*, 0x6260D0, RwCamera*>(camera);
}

RpLight *RpLightCreate(RwInt32 type)
{
	return CallAndReturn<RpLight*, 0x621740, RwInt32>(type);
}

RpLight *RpLightSetColor(RpLight *light, const RwRGBAReal *color)
{
	return CallAndReturn<RpLight*, 0x6211B0, RpLight*, const RwRGBAReal *>(light,color);
}
RpWorld *RpWorldAddLight(RpWorld *world, RpLight *light)
{
	return CallAndReturn<RpWorld*, 0x61FFA0, RpWorld*, RpLight*>(world,light);
}

RpWorld *RpWorldRemoveLight(RpWorld *world, RpLight *light)
{
	return CallAndReturn<RpWorld*, 0x61FFF0, RpWorld*, RpLight*>(world,light);
}

RwCamera    *RwCameraSetViewWindow(RwCamera *camera, const RwV2d *viewWindow)
{
	return CallAndReturn<RwCamera*, 0x626360, RwCamera*, const RwV2d*>(camera,viewWindow);
}

RwInt32 RwEngineGetCurrentVideoMode()
{
	return CallAndReturn<RwInt32, 0x612740>();
}

RwVideoMode *RwEngineGetVideoModeInfo(RwVideoMode *modeinfo, RwInt32 modeIndex)
{
	return CallAndReturn<RwVideoMode*, 0x612710, RwVideoMode *, RwInt32>(modeinfo,modeIndex);
}

RwBool RpClumpDestroy(RpClump * clump)
{
	return CallAndReturn<RwBool, 0x61B380, RpClump*>(clump);
}

RwBool RpLightDestroy(RpLight *light)
{
	return CallAndReturn<RwBool, 0x621700, RpLight*>(light);
}

RwMatrix* RwMatrixScale(RwMatrix* matrix, const RwV3d* scale, RwOpCombineType combineOp)
{
	return CallAndReturn<RwMatrix*, 0x619AD0, RwMatrix*, const RwV3d*, RwOpCombineType>(matrix, scale, combineOp);
}

RpClump* RpClumpForAllAtomics(RpClump* clump, RpAtomicCallBack callback, void* pData)
{
	return CallAndReturn<RpClump*, 0x61AC40, RpClump*, RpAtomicCallBack, void*>(clump,callback,pData);
}

int RpSkinAtomicGetHAnimHierarchy(RpAtomic* atomic)
{
	return *(int*)(0x824A1C + atomic);
}

static RpAtomic*
GetAnimHierarchyCallback(RpAtomic* atomic, void* data)
{
	*(RpHAnimHierarchy**)data = (RpHAnimHierarchy * )RpSkinAtomicGetHAnimHierarchy(atomic);
	return nullptr;
}

RwInt32 RpHAnimIDGetIndex(RpHAnimHierarchy* hierarchy, RwInt32 ID) 
{ 
	return CallAndReturn<RwInt32, 0x617250, RpHAnimHierarchy*, RwInt32>(hierarchy, ID);
}

RwMatrix* RwFrameGetLTM(RwFrame* frame)
{
	return CallAndReturn<RwMatrix*, 0x6184C0, RwFrame*>(frame);
}

RpHAnimHierarchy* GetAnimHierarchyFromSkinClump(RpClump* clump)
{
	RpHAnimHierarchy result;
	RpClumpForAllAtomics(clump, GetAnimHierarchyCallback, &result);
	return &result;
}


static RwV3d Zero = {0.0f, 0.0f, 0.0f};

static RpAtomic *
AtomicAddBSphereCentre(RpAtomic *atomic, void *data)
{
    RpGeometry *geometry;

    geometry = RpAtomicGetGeometry(atomic);

    if( geometry )
    {
        RwV3d center;
        RwMatrix *LTM;
        RpMorphTarget *morphTarget;
        RwInt32 i, numMorphTargets;
        RwV3d atomicCentre;
        RwSphere *clumpSphere;

        clumpSphere = (RwSphere *)data;

        /*
         * Establish the average centre of this atomic over all morph targets
         */
        atomicCentre = Zero;

        numMorphTargets = RpGeometryGetNumMorphTargets (geometry);

        for( i = 0; i < numMorphTargets; i++ )
        {
            morphTarget = RpGeometryGetMorphTarget(geometry, i);
            center = RpMorphTargetGetBoundingSphere(morphTarget)->center;
            RwV3dAdd(&atomicCentre, &atomicCentre, &center);
        }

        RwV3dScale(&atomicCentre, &atomicCentre, 1.0f / numMorphTargets);

        /*
         * Tranform the average centre of the atomic to world space
         */
        LTM = RwFrameGetLTM(RpAtomicGetFrame(atomic));
        RwV3dTransformPoints(&atomicCentre, &atomicCentre, 1, LTM);

        /*
         * Add the average centre of the atomic up in order to calculate the centre of the clump
         */
        RwV3dAdd(&clumpSphere->center, &clumpSphere->center, &atomicCentre);
    }

    return atomic;
}

static RpAtomic *
AtomicCompareBSphere(RpAtomic *atomic, void *data)
{
    RpGeometry *geometry;

    geometry = RpAtomicGetGeometry(atomic);

    if( geometry )
    {
        RwSphere *sphere, morphTargetSphere;
        RwV3d tempVec;
        RpMorphTarget *morphTarget;
        RwReal dist;
        RwMatrix *LTM;
        RwInt32 i, numMorphTargets;

        sphere = (RwSphere *)data;

        LTM = RwFrameGetLTM(RpAtomicGetFrame(atomic));

        numMorphTargets = RpGeometryGetNumMorphTargets(geometry);

        for( i = 0; i < numMorphTargets; i++ )
        {
            morphTarget = RpGeometryGetMorphTarget(geometry, i);
            morphTargetSphere = *RpMorphTargetGetBoundingSphere(morphTarget);

            RwV3dTransformPoints(&morphTargetSphere.center,
                &morphTargetSphere.center, 1, LTM);

            RwV3dSub(&tempVec, &morphTargetSphere.center, &sphere->center);

            dist = RwV3dLength(&tempVec) + morphTargetSphere.radius;
            if( dist > sphere->radius )
            {
                sphere->radius = dist;
            }
        }
    }

    return atomic;
}


RpClump *RpClumpGetBoundingSphere(RpClump *Clump, RwSphere *Sphere, bool UseLTM)
{
	RwMatrix matrix;
	RwSphere sphere = { 0.0f, 0.0f, 0.0f, 0.0f };
	 
	if ( Clump == NULL || Sphere == NULL )
		return NULL;
  
	Sphere->radius = 0.0f;
	Sphere->center.x = 0.0f;
	Sphere->center.y = 0.0f;
	Sphere->center.z = 0.0f;
	
	RpClumpForAllAtomics(Clump, AtomicAddBSphereCentre, &sphere);
	
	RwV3dScale(&sphere.center, &sphere.center, 1.0f);

	RpClumpForAllAtomics(Clump, AtomicCompareBSphere, &sphere);
	
	RwMatrixInvert(&matrix, RwFrameGetLTM(RpClumpGetFrame(Clump)));
	
	RwV3dTransformPoints(&sphere.center, &sphere.center, 1, &matrix);

	RwSphereAssign(Sphere, &sphere);
	  
	return Clump;
}

RpClump *
ClumpRotate(RpClump *clump, RwCamera *camera, RwReal xAngle, RwReal yAngle)
{
    RwFrame *clumpFrame = NULL;
    RwFrame *cameraFrame = NULL;
    RwMatrix *cameraMatrix = NULL;
    RwMatrix *clumpMatrix = NULL;
	RwSphere ClumpSphere;
    
    RwV3d right, up, pos;

    /*
     * Rotate clump about it's origin...
     */           
    clumpFrame = RpClumpGetFrame(clump);
    cameraFrame = RwCameraGetFrame(camera); 
     
    clumpMatrix = RwFrameGetMatrix(clumpFrame);
    cameraMatrix = RwFrameGetMatrix(cameraFrame);

    right = *RwMatrixGetRight(cameraMatrix);
    up = *RwMatrixGetUp(cameraMatrix);

    //pos = *RwMatrixGetPos(clumpMatrix);
	
	RpClumpGetBoundingSphere(clump, &ClumpSphere, false);
	
	RwV3dTransformPoints(&pos, &(ClumpSphere.center), 1, RwFrameGetLTM(clumpFrame));

    /*
     * Translate back to the origin...
     */
    RwV3dScale(&pos, &pos, -1.0f);
    RwFrameTranslate(clumpFrame, &pos, rwCOMBINEPOSTCONCAT);

    /*
     * Do the rotation...
     */
    RwFrameRotate(clumpFrame, &up, xAngle, rwCOMBINEPOSTCONCAT);
    RwFrameRotate(clumpFrame, &right, yAngle, rwCOMBINEPOSTCONCAT);

    /*
     * And translate back...
     */
    RwV3dScale(&pos, &pos, -1.0f);
    RwFrameTranslate(clumpFrame, &pos, rwCOMBINEPOSTCONCAT);

    return clump;
}