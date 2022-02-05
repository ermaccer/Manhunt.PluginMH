#include "Camera.h"

float& CCamera::ms_freeCameraRotationSpeed = *(float*)0x715AB8;
float& CCamera::ms_freeCameraSpeed = *(float*)0x715ABC;
CCamera& TheCamera = *(CCamera*)0x7A0FAC;