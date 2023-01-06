// SONIC ROBO BLAST 2
//-----------------------------------------------------------------------------
// Copyright (C) 1993-1996 by id Software, Inc.
// Copyright (C) 1998-2000 by DooM Legacy Team.
// Copyright (C) 1999-2020 by Sonic Team Junior.
//
// This program is free software distributed under the
// terms of the GNU General Public License, version 2.
// See the 'LICENSE' file for more details.
//-----------------------------------------------------------------------------
/// \file  doomdata.h
/// \brief all external data is defined here
///
///        most of the data is loaded into different structures at run time
///        some internal structures shared by many modules are here

#ifndef __DOOMDATA__
#define __DOOMDATA__

// The most basic types we use, portability.
#include "doomtype.h"

// Some global defines, that configure the game.
#include "doomdef.h"

#include "taglist.h"
#include "m_fixed.h" // See the mapthing_t scale.

#ifdef __cplusplus
extern "C" {
#endif

//
// Map level types.
// The following data structures define the persistent format
// used in the lumps of the WAD files.
//

// Lump order in a map WAD: each map needs a couple of lumps
// to provide a complete scene geometry description.
enum
{
	ML_LABEL,    // A separator, name, MAPxx
	ML_THINGS,   // Enemies, rings, monitors, scenery, etc.
	ML_LINEDEFS, // Linedefs, from editing
	ML_SIDEDEFS, // Sidedefs, from editing
	ML_VERTEXES, // Vertices, edited and BSP splits generated
	ML_SEGS,     // Linesegs, from linedefs split by BSP
	ML_SSECTORS, // Subsectors, list of linesegs
	ML_NODES,    // BSP nodes
	ML_SECTORS,  // Sectors, from editing
	ML_REJECT,    // LUT, sector-sector visibility
	ML_BLOCKMAP,  // LUT, motion clipping, walls/grid element
};

// Extra flag for objects.
#define MTF_EXTRA 1

// Reverse gravity flag for objects.
#define MTF_OBJECTFLIP 2

// Special flag used with certain objects.
#define MTF_OBJECTSPECIAL 4

// Deaf monsters/do not react to sound.
#define MTF_AMBUSH 8

// Do not use bit five or after, as they are used for object z-offsets.

#if defined(_MSC_VER)
#pragma pack(1)
#endif

// A single Vertex.
struct  mapvertex_t
{
	INT16 x, y;
}ATTRPACK;

// A SideDef, defining the visual appearance of a wall,
// by setting textures and offsets.
struct mapsidedef_t
{
	INT16 textureoffset, rowoffset;
	char toptexture[8], bottomtexture[8], midtexture[8];
	// Front sector, towards viewer.
	INT16 sector;
} ATTRPACK;

// A LineDef, as used for editing, and as input
// to the BSP builder.
struct maplinedef_t
{
	INT16 v1, v2;
	INT16 flags;
	INT16 special;
	INT16 tag;
	// sidenum[1] will be 0xffff if one sided
	UINT16 sidenum[2];
} ATTRPACK;

//
// LineDef attributes.
//

enum
{
	// Solid, is an obstacle.
	ML_IMPASSABLE    = 0x00000001,

	// Blocks enemies only
	ML_BLOCKMONSTERS = 0x00000002,

	// Backside will not be present at all if not two sided.
	ML_TWOSIDED      = 0x00000004,

	// If a texture is pegged, the texture will have
	// the end exposed to air held constant at the
	// top or bottom of the texture (stairs or pulled
	// down things) and will move with a height change
	// of one of the neighbor sectors.
	// Unpegged textures allways have the first row of
	// the texture at the top pixel of the line for both
	// top and bottom textures (use next to windows).

	// upper texture unpegged
	ML_DONTPEGTOP		= 0x00000008,

	// lower texture unpegged
	ML_DONTPEGBOTTOM	= 0x00000010,

	ML_SKEWTD			= 0x00000020,

	// Don't let Knuckles climb on this line
	ML_NOCLIMB			= 0x00000040,

	ML_NOSKEW			= 0x00000080,
	ML_MIDPEG			= 0x00000100,
	ML_MIDSOLID			= 0x00000200,
	ML_WRAPMIDTEX		= 0x00000400,

	// Apply effect only in netgames
	ML_NETONLY			= 0x00000800,
	ML_NETONLY_OLD		= 0x3800, // Combination of old ML_NOSONIC, ML_NOTAILS and ML_NOKNUX

	// Apply effect only in single player games
	ML_NONET			= 0x00001000,

	// SRB2Kart: Blocks players only; items can be thrown through these.
	ML_BLOCKPLAYERS		= 0x00002000,

	// Don't bounce off this wall!
	ML_NOTBOUNCY		= 0x00004000,

	// Transfers FOF properties.
	ML_TFERLINE			= 0x00008000,
};

enum
{
	// Special action is repeatable.
	SPAC_REPEATSPECIAL		= 0x00000001,

	// Activates when crossed by a player.
	SPAC_CROSS				= 0x00000002,

	// Activates when crossed by an enemy.
	SPAC_CROSSMONSTER		= 0x00000004,

	// Activates when crossed by a projectile.
	SPAC_CROSSMISSILE		= 0x00000008,

	// Activates when bumped by a player.
	SPAC_PUSH				= 0x00000010,

	// Activates when bumped by an enemy.
	SPAC_PUSHMONSTER		= 0x00000020,

	// Activates when bumped by a missile.
	SPAC_IMPACT				= 0x00000040,
};

// Sector definition, from editing.
struct mapsector_t
{
	INT16 floorheight;
	INT16 ceilingheight;
	char floorpic[8];
	char ceilingpic[8];
	INT16 lightlevel;
	INT16 special;
	INT16 tag;
} ATTRPACK;

// SubSector, as generated by BSP.
struct mapsubsector_t
{
	UINT16 numsegs;
	// Index of first one, segs are stored sequentially.
	UINT16 firstseg;
} ATTRPACK;


// LineSeg, generated by splitting LineDefs
// using partition lines selected by BSP builder.
struct mapseg_t
{
	INT16 v1, v2;
	INT16 angle;
	INT16 linedef;
	INT16 side;
	INT16 offset;
} ATTRPACK;

// BSP node structure.

// Indicate a leaf.
#define NF_SUBSECTOR 0x8000

struct mapnode_t
{
	// Partition line from (x,y) to x+dx,y+dy)
	INT16 x, y;
	INT16 dx, dy;

	// Bounding box for each child, clip against view frustum.
	INT16 bbox[2][4];

	// If NF_SUBSECTOR it's a subsector, else it's a node of another subtree.
	UINT16 children[2];
} ATTRPACK;

#if defined(_MSC_VER)
#pragma pack()
#endif

typedef enum
{
	USER_PROP_BOOL,
	USER_PROP_INT,
	USER_PROP_FIXED,
	USER_PROP_STR
} mapUserPropertyType_e;

struct mapUserProperties_t
{
	mapUserProperty_t *properties;
	size_t length;
	size_t capacity;
};

#define NUMMAPTHINGARGS 10
#define NUMMAPTHINGSTRINGARGS 2

// Thing definition, position, orientation and type,
// plus visibility flags and attributes.
struct mapthing_t
{
	INT16 x, y;
	INT16 angle, pitch, roll;
	UINT16 type;
	UINT16 options;
	INT16 z;
	UINT8 extrainfo;
	taglist_t tags;
	fixed_t scale;
	fixed_t spritexscale, spriteyscale;
	INT16 special;
	INT32 args[NUMMAPTHINGARGS];
	char *stringargs[NUMMAPTHINGSTRINGARGS];
	UINT8 layer; // FOF layer to spawn on, see P_GetMobjSpawnHeight
	mapUserProperties_t user; // UDMF user-defined custom properties.
	mobj_t *mobj;
};

#define ZSHIFT 4

#define NUMMAPS 1035

/* slope thing types */
enum
{
	FLOOR_SLOPE_THING   = 777,
	CEILING_SLOPE_THING = 778,
};

#ifdef __cplusplus
} // extern "C"
#endif

#endif // __DOOMDATA__
