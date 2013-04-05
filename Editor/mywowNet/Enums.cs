using System;

namespace mywowNet
{
    public enum DriverType
    {
        Direct3D9 = 1,
        Direct3D11
    }

    public enum E_LEVEL
    {
        EL_ZERO = 0,
        EL_ONE,
        EL_TWO,
        EL_THREE,
        EL_FOUR,
        EL_FIVE,
    };

    public enum E_TEXTURE_FILTER
    {
        ETF_NONE = 0,
        ETF_BILINEAR,
        ETF_TRILINEAR,
        ETF_ANISOTROPIC_X1,
        ETF_ANISOTROPIC_X2,
        ETF_ANISOTROPIC_X4,
        ETF_ANISOTROPIC_X8,
        ETF_ANISOTROPIC_X16
    };

    public enum E_CHAR_SLOTS
    {
        CS_HEAD,

        CS_NECK,

        CS_SHOULDER,

        CS_BOOTS,

        CS_BELT,

        CS_SHIRT,

        CS_PANTS,

        CS_CHEST,

        CS_BRACERS,

        CS_GLOVES,

        CS_HAND_RIGHT,

        CS_HAND_LEFT,

        CS_CAPE,

        CS_TABARD,

        CS_QUIVER,

        NUM_CHAR_SLOTS,
    }

    public enum E_ITEM_TYPE
    {
        IT_ALL = 0,

        IT_HEAD,

        IT_NECK,

        IT_SHOULDER,

        IT_SHIRT,

        IT_CHEST,

        IT_BELT,

        IT_PANTS,

        IT_BOOTS,

        IT_BRACERS,

        IT_GLOVES,

        IT_RINGS,

        IT_ACCESSORY,

        IT_DAGGER,

        IT_SHIELD,

        IT_BOW,

        IT_CAPE,

        IT_2HANDED,

        IT_QUIVER,

        IT_TABARD,

        IT_ROBE,

        IT_LEFTHANDED,

        IT_RIGHTHANDED,

        IT_OFFHAND,

        IT_UNUSED,

        IT_THROWN,

        IT_GUN,

        NUM_ITEM_TYPES,
    }

    public enum M2Type
    {
        MT_NONE = 0,
        MT_CHARACTER,
        MT_CREATRUE,
        MT_ITEM,
        MT_SPELLS,
        MT_PARTICLES,
        MT_INTERFACE,
        MT_COUNT
    }

    public enum E_MODEL_REPLACE_TEXTURE
    {
        EMRT_BODY = 0,
        EMRT_CAPE,
        EMRT_HAIR,
        EMRT_FUR,
        EMRT_NPC1,
        EMRT_NPC2,
        EMRT_NPC3,
    }

    public enum ECharRegions
    {
        CR_BASE = 0,
        CR_ARM_UPPER,
        CR_ARM_LOWER,
        CR_HAND,
        CR_FACE_UPPER,
        CR_FACE_LOWER,
        CR_TORSO_UPPER,								//躯干
        CR_TORSO_LOWER,
        CR_PELVIS_UPPER,						//骨盆，其实也是腿的区域
        CR_PELVIS_LOWER,
        CR_FOOT,
        NUM_REGIONS,

        CR_LEG_UPPER = CR_PELVIS_UPPER,			//腿
        CR_LEG_LOWER = CR_PELVIS_LOWER,
    };

    public enum E_SCENE_DEBUG_PART
	{
		ESDP_BASE = 0,
		ESDP_M2_GEOSETS,
		ESDP_M2_PARTICLES,
	};

    public enum E_MODEL_PART
    {
        EMP_ALL = 0,

        EMP_HEAD,

        EMP_CAPE,

        EMP_SHOULDER,

        EMP_LEFTHAND,

        EMP_RIGHTHAND
    }

    public enum E_MODEL_EDIT_PART
    {
        EEP_MODEL = 0,

        EEP_PARTICLES,

        EEP_RIBBONS,

        EEP_BOUNDINGBOX,

        EEP_BONES,

        EEP_ATTACHMENTPOINTS,
    }

    public enum E_OVERRIDE_WIREFRAME
    {
        EOW_NONE = 0,
        EOW_WIREFRAME,
        EOW_WIREFRAME_SOLID,
        EOW_WIREFRAME_ONECOLOR,
    };

    public enum E_WMO_EDIT_PART
    {
        EEP_WMO = 0,

        EEP_DOODADS,

        EEP_BOUNDINGBOX,
    }

    public enum E_POSITION_2D
    {
        EP2D_NONE = 0,
        EP2D_TOPLEFT,
        EP2D_TOPRIGHT,
        EP2D_BOTTOMLEFT,
        EP2D_BOTTOMRIGHT,
        EP2D_TOPCENTER,
        EP2D_BOTTOMCENTER,
        EP2D_CENTERLEFT,
        EP2D_CENTERRIGHT,
    };

    public enum E_M2_STATES
    {
        EMS_STAND = 0,
        EMS_ROLL,
        EMS_JUMP,
        EMS_KNEEL,
        EMS_DANCE,
        EMS_FLYINGKICK,
        EMS_EMOTEREAD,
        EMS_CRANE,
        EMS_SPINNINGKICK,
        EMS_TORPEDO,
        EMS_WALK,
        EMS_RUN,
        EMS_SITGROUND,

        EMS_COUNT,
    };

}
