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
