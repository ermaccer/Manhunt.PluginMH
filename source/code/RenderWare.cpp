#include "RenderWare.h"
#include "manhunt/core.h"

RpClump* RpClumpRender(RpClump * clump)
{
	return CallAndReturn<RpClump*, 0x61ABF0, RpClump*>(clump);
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
	return CallAndReturn<RpWorld*, 0x6211B0, RpWorld*, RpLight*>(world,light);
}