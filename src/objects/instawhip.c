#include "../doomdef.h"
#include "../info.h"
#include "../k_objects.h"
#include "../p_local.h"

#define recharge_target(o) ((o)->target)
#define recharge_offset(o) ((o)->movedir)

void Obj_InstaWhipThink (mobj_t *whip)
{
	if (P_MobjWasRemoved(whip->target))
	{
		P_RemoveMobj(whip);
	}
	else
	{
		mobj_t *mo = whip->target;
		player_t *player = mo->player;

		// Follow player
		whip->flags &= ~(MF_NOCLIPTHING);
		P_SetScale(whip, whip->target->scale);
		P_MoveOrigin(whip, mo->x, mo->y, mo->z + mo->height/2);
		whip->flags |= MF_NOCLIPTHING;

		// Twirl
		whip->angle = whip->target->angle + (ANG30 * 2 * whip->fuse);
		whip->target->player->drawangle = whip->angle;
		if (player->follower)
			player->follower->angle = whip->angle;
		player->pflags |= PF_GAINAX;
		player->glanceDir = -2;

		// Visuals
		whip->renderflags |= RF_NOSPLATBILLBOARD|RF_FULLBRIGHT;

		if (whip->renderflags & RF_DONTDRAW)
			whip->renderflags &= ~RF_DONTDRAW;
		else
			whip->renderflags |= RF_DONTDRAW;

		if (whip->extravalue2) // Whip has no hitbox but removing it is a pain in the ass
			whip->renderflags |= RF_DONTDRAW;
	}
}

void Obj_SpawnInstaWhipRecharge(player_t *player, angle_t angleOffset)
{
	mobj_t *x = P_SpawnMobjFromMobj(player->mo, 0, 0, 0, MT_INSTAWHIP_RECHARGE);

	x->tics = max(player->instaShieldCooldown - states[x->info->raisestate].tics, 0);
	x->renderflags |= RF_SLOPESPLAT | RF_NOSPLATBILLBOARD;

	P_SetTarget(&recharge_target(x), player->mo);
	recharge_offset(x) = angleOffset;
}

void Obj_InstaWhipRechargeThink(mobj_t *x)
{
	mobj_t *target = recharge_target(x);

	if (P_MobjWasRemoved(target))
	{
		P_RemoveMobj(x);
		return;
	}

	P_MoveOrigin(x, target->x, target->y, target->z + (target->height / 2));
	P_InstaScale(x, 2 * target->scale);
	x->angle = target->angle + recharge_offset(x);

	// Flickers every other frame
	x->renderflags ^= RF_DONTDRAW;
}