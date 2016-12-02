#pragma once

namespace Keybinds{
    enum{
        FORWARD = 0,
        BACKWARD = 1,
        TURN_LEFT = 2,
        TURN_RIGHT = 3,
        MOVE_LEFT = 4,
        MOVE_RIGHT = 5,
        JUMP = 6
    };

    enum{
        SPELLBOOK = 10,
        CLAN = 11,
        HONOR = 12,
        MAINMENU = 13,
        CHARACTER = 14,
        MACRO = 15,
        SOCIAL = 16,
        MAP = 17,
    };

    enum{
        TARGET_NEAREST_ENEMY = 20,
        TARGET_PREVIOUS_ENEMY, //21
        TARGET_NEAREST_ENEMY_PLAYER, //22
        TARGET_PREVIOUS_ENEMY_PLAYER, //23
        TARGET_NEAREST_FRIENDLY_PLAYER, //24
        TARGET_PREVIOUS_FRIENDLY_PLAYER, //25
        TARGET_SELF, //26
        TARGET_PARTY_MEMBER_1, //27
        TARGET_PARTY_MEMBER_2, //28
        TARGET_PARTY_MEMBER_3, //29
        TARGET_PARTY_MEMBER_4, //30
        TARGET_PET, //31
        TARGET_PARTY_PET_1, //32
        TARGET_PARTY_PET_2, //33
        TARGET_PARTY_PET_3, //34
        TARGET_PARTY_PET_4, //35
        ASSIST_TARGET, //36
        TOGGLE_NAMEPLATES, //37
        TOGGLE_FRIENDLY_NAMEPLATES, //38
        SET_FOCUS, //39
        FOCUS_ARENA_1, //40
        FOCUS_ARENA_2, //41
        FOCUS_ARENA_3, //42
        FOCUS_ARENA_4, //43
        FOCUS_ARENA_5, //44
        TARGET_ARENA_1, //45
        TARGET_ARENA_2, //46
        TARGET_ARENA_3, //47
        TARGET_ARENA_4, //48
        TARGET_ARENA_5 //49
    };

    enum{
        CAMERA_ZOOM_IN = 50,
        CAMERA_ZOOM_OUT,
        CAMERA_REVERSE
    };

    enum{
        REPLY_WHISPER = 55,
        RE_WHISPER
    };
}
