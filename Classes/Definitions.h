#pragma once

// SPRITES - BACKGROUNDS & WINDOWS
#define GRID "backgrounds&windows/grid.png"
#define PAUSE_BACKGROUND GRID
#define GAME_OVER_BACKGROUND "backgrounds&windows/game_over_background.png"
#define GAME_OVER_WINDOW "backgrounds&windows/game_over_window.png"
#define TITLE "backgrounds&windows/title.png"

// SPRITES - BUTTONS
#define PLAY_BUTTON "buttons/play.png"
#define PLAY_PRESSED_BUTTON "buttons/play_pressed.png"

#define LEAVE_BUTTON "buttons/leave.png"
#define LEAVE_PRESSED_BUTTON "buttons/leave_pressed.png"

#define SOUND_ON_BUTTON "buttons/sound_on.png"
#define SOUND_ON_PRESSED_BUTTON "buttons/sound_on_pressed.png"

#define SOUND_OFF_BUTTON "buttons/sound_off.png"
#define SOUND_OFF_PRESSED_BUTTON  "buttons/sound_off_pressed.png"

#define PAUSE_BUTTON "buttons/pause_button.png"
#define PAUSE_BUTTON_PRESSED "buttons/pause_pressed_button.png"

#define RETRY_BUTTON "buttons/retry_button.png"
#define RETRY_BUTTON_PRESSED "buttons/retry_pressed_button.png"

#define RESUME_BUTTON "buttons/resume_button.png"
#define RESUME_BUTTON_PRESSED "buttons/resume_pressed_button.png"

#define HOME_BUTTON "buttons/home_button.png"
#define HOME_BUTTON_PRESSED "buttons/home_pressed_button.png"

#define PLAY_BUTTON_SOUND "sounds/PlaySound.png"
#define LEAVE_BUTTON_SOUND "sounds/LeaveSound.png"


#define PIECE_X "pieces/X.png"
#define PIECE_O "pieces/O.png"
#define PIECE_X_WIN "pieces/X_win.png"
#define PIECE_O_WIN "pieces/O_win.png"

// IDs
#define PIECE_X_ID 8
#define PIECE_O_ID 0
#define PIECE_EMPTY -1
#define PIECE_PLAYER PIECE_X_ID
#define PIECE_AI PIECE_O_ID


// TIMES
#define PIECE_FADE_IN_TIME 0.3
#define GAME_OVER_BACKGROUND_FADE_IN_TIME 0.5
#define PAUSE_BACKGROUND_FADE_TIME 0.5
#define MENU_MOVE_BOUNCE_DURATION 1.5
#define SCENE_TRANSITION_TIME 1.0f

// STATES
#define STATE_PLAYING 98
#define STATE_PAUSED 97
#define STATE_WON 96
#define STATE_LOSE 95
#define STATE_PLACING_PIECE 94
#define STATE_AI_PLAYING 93
#define STATE_DRAW 92