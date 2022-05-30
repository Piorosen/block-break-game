#pragma once
#include <fmod/fmod.h>
namespace grc {
	enum class audiomode {						   
		DEFAULT			 			= 0x00000000,
		LOOP_OFF					= 0x00000001,
		LOOP_NORMAL					= 0x00000002,
		LOOP_BIDI					= 0x00000004,
		_2D							= 0x00000008,
		_3D							= 0x00000010,
		CREATESTREAM				= 0x00000080,
		CREATESAMPLE				= 0x00000100,
		CREATECOMPRESSEDSAMPLE		= 0x00000200,
		OPENUSER					= 0x00000400,
		OPENMEMORY					= 0x00000800,
		OPENMEMORY_POINT 			= 0x10000000,
		OPENRAW						= 0x00001000,
		OPENONLY					= 0x00002000,
		ACCURATETIME				= 0x00004000,
		MPEGSEARCH					= 0x00008000,
		NONBLOCKING					= 0x00010000,
		UNIQUE						= 0x00020000,
		_3D_HEADRELATIVE			= 0x00040000,
		_3D_WORLDRELATIVE			= 0x00080000,
		_3D_INVERSEROLLOFF			= 0x00100000,
		_3D_LINEARROLLOFF			= 0x00200000,
		_3D_LINEARSQUAREROLLOFF		= 0x00400000,
		_3D_INVERSETAPEREDROLLOFF	= 0x00800000,
		_3D_CUSTOMROLLOFF			= 0x04000000,
		_3D_IGNOREGEOMETRY			= 0x40000000,
		IGNORETAGS					= 0x02000000,
		LOWMEM						= 0x08000000,
		LOADSECONDARYRAM			= 0x20000000,
		VIRTUAL_PLAYFROMSTART		= 0x80000000,
	};
}