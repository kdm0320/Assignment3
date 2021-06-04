#define _CRT_SECURE_NO_WARNINGS
#include <bangtal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

SceneID scene[8];
ObjectID start, easy, hard, next[3], npc[3], liveNpc, magazine, reload, rolling, gun[4], change, shot, count, restart, blood
, message[6];
TimerID timers[10];
SoundID effect[7];
int npcCount = 0, bullet = 0, player_bullet = 0, npc_bullet = 0;
bool Easy = true, IsOnRolling = false, IsOnReload = false;

ObjectID createObject(const char* image, SceneID scene, int x, int y, bool shown) {
    ObjectID object = createObject(image);

    locateObject(object, scene, x, y);

    if (shown)
        showObject(object);

    return object;
}
void setTimer(TimerID* timers, int timerNumber, float time) {
    setTimer(timers[timerNumber], time);
    startTimer(timers[timerNumber]);
}
void Create_Timer() {
    for (int i = 0; i < 10; i++) {
        timers[i] = createTimer(1.f);

        hideTimer;
    }
}
void createSound() {
    effect[0] = createSound("Images/sound/reload.mp3");
    effect[1] = createSound("Images/sound/rolling.mp3");
    effect[2] = createSound("Images/sound/heartbeat.mp3");
    effect[3] = createSound("Images/sound/fire.mp3");
    effect[4] = createSound("Images/sound/empty.mp3");
    effect[5] = createSound("Images/sound/first.mp3");
    effect[6] = createSound("Images/sound/dying.mp3");




}
void createScene() {
    scene[0] = createScene("start", "Images/scenes/0.png");
    scene[1] = createScene("choose", "Images/scenes/1.png");
    scene[2] = createScene("aim", "Images/scenes/aim.png");
    scene[3] = createScene("die", "Images/scenes/died.png");
    scene[4] = createScene("second", "Images/scenes/free.png");
    scene[5] = createScene("stage", "Images/scenes/basic.png");
    scene[6] = createScene("intro", "Images/scenes/intro.png");
    scene[7] = createScene("basic", "Images/scenes/basic.png");


}

void settingGameOption() {
    setGameOption(GameOption::GAME_OPTION_INVENTORY_BUTTON, false);
    setGameOption(GameOption::GAME_OPTION_ROOM_TITLE, false);
    setGameOption(GameOption::GAME_OPTION_MESSAGE_BOX_BUTTON, false);
}
void createGame() {
    createScene();
    createSound();
    Create_Timer();
    playSound(effect[5], true);
    start = createObject("Images/button/start.png", scene[0], 520, 200, true);

}
void result(int player, int npc) {
    if (player <= bullet) {
        playSound(effect[3]);
        enterScene(scene[3]);

        restart = createObject("Images/button/restart.png", scene[3], 520, 200, true);
    }
    else if (player > bullet && npc > bullet) {
        playSound(effect[4]);
        switch (npcCount)
        {
        case 1:
            liveNpc = createObject("Images/npc/1.png", scene[7], 520, 0, true);
            message[1] = createObject("Images/messages/1-1.png", scene[7], 760, 500, true);
            break;
        case 2:
            hideObject(message[1]);
            liveNpc = createObject("Images/npc/2.png", scene[7], 400, 0, true);
            message[3] = createObject("Images/messages/2-1.png", scene[7], 760, 500, true);

            break;

        case 3:
            hideObject(message[3]);
            liveNpc = createObject("Images/npc/3.png", scene[7], 400, 0, true);
            message[5] = createObject("Images/messages/3-1.png", scene[7], 760, 500, true);

            break;


        }
        enterScene(scene[7]);
        next[1] = createObject("Images/button/next.png", scene[7], 1000, 100, true);

    }
    else if (player > bullet && npc <= bullet) {
        hideObject(message[1]);
        hideObject(message[3]);
        hideObject(message[5]);

        playSound(effect[3]);
        blood = createObject("Images/button/blood.png", scene[7], 200, 100, true);
        playSound(effect[6]);
        enterScene(scene[7]);
        next[1] = createObject("Images/button/next.png", scene[7], 1000, 100, true);
    }
    npcCount++;
    playSound(effect[5], true);

}
void mouseCallback(ObjectID object, int x, int y, MouseAction) {
    if (object == start) {
        enterScene(scene[6]);
        gun[2] = createObject("Images/gun/npcs-1.png", scene[5], 220, 80, true);
        next[0] = createObject("Images/button/next.png", scene[6], 1000, 100, true);
    }
    else if (object == next[0]) {
        enterScene(scene[1]);
        easy = createObject("Images/button/easy.png", scene[1], 150, 400, true);
        hard = createObject("Images/button/hard.png", scene[1], 920, 400, true);

    }
    else if (object == next[1]) {

        hideObject(liveNpc);
        hideObject(npc[0]);
        hideObject(message[0]);
        hideObject(blood);
        hideObject(gun[3]);
        showObject(gun[2]);
        if (npcCount <= 3) {
            if (npcCount == 2) {
                npc[1] = createObject("Images/npc/2.png", scene[5], 400, 0, true);
                message[2] = createObject("Images/messages/2.png", scene[5], 50, 450, true);
                enterScene(scene[5]);
                hideObject(gun[1]);
                showObject(magazine);
                showObject(reload);
            }
            else if (npcCount == 3) {
                hideObject(npc[1]);
                hideObject(message[2]);
                npc[2] = createObject("Images/npc/3.png", scene[5], 400, 0, true);
                message[4] = createObject("Images/messages/3.png", scene[5], 150, 450, true);

                enterScene(scene[5]);
                hideObject(gun[1]);
                showObject(magazine);
                showObject(reload);
            }
            else {
                enterScene(scene[5]);
                hideObject(gun[1]);
                showObject(magazine);
                showObject(reload);
            }

        }
        else {
            enterScene(scene[4]);
            next[2] = createObject("Images/button/out.png", scene[4], 1000, 50, true);
        }
    }
    else if (object == next[2]) {
        endGame();
    }
    else if (object == easy) {
        npcCount++;

        enterScene(scene[5]);
        npc[0] = createObject("Images/npc/1.png", scene[5], 520, 0, true);
        message[0] = createObject("Images/messages/1.png", scene[5], 90, 350, true);

        magazine = createObject("Images/gun/1.png", scene[5], 950, 500, true);
        scaleObject(magazine, 0.6f);
        reload = createObject("Images/button/reload.png", scene[5], 920, 400, true);

    }
    else if (object == hard) {
        Easy = false;
        npcCount++;
        bullet++;
        enterScene(scene[5]);
        npc[0] = createObject("Images/npc/1.png", scene[5], 520, 0, true);
        message[0] = createObject("Images/messages/1.png", scene[5], 90, 350, true);

        magazine = createObject("Images/gun/2.png", scene[5], 950, 500, true);
        scaleObject(magazine, 0.6f);
        reload = createObject("Images/button/reload.png", scene[5], 920, 400, true);
    }
    else if (object == reload) {
        IsOnReload = true;
        if (IsOnReload) {
            IsOnReload = false;
            if (Easy && npcCount == 1) {
                playSound(effect[0]);
                setObjectImage(magazine, "Images/gun/2.png");
                bullet++;
                setTimer(timers, 0, 0.8f);

            }
            else if (Easy && npcCount == 2) {
                playSound(effect[0]);
                setObjectImage(magazine, "Images/gun/3.png");
                bullet++;
                setTimer(timers, 0, 0.8f);
            }
            else if (Easy && npcCount == 3) {
                playSound(effect[0]);
                setObjectImage(magazine, "Images/gun/4.png");
                bullet++;
                setTimer(timers, 0, 0.8f);
            }
            else if (Easy == false && npcCount == 1) {
                playSound(effect[0]);
                setObjectImage(magazine, "Images/gun/3.png");
                bullet++;
                setTimer(timers, 0, 0.8f);
            }
            else if (Easy == false && npcCount == 2) {
                playSound(effect[0]);
                setObjectImage(magazine, "Images/gun/4.png");
                bullet++;
                setTimer(timers, 0, 0.8f);
            }
            else if (Easy == false && npcCount == 3) {
                playSound(effect[0]);
                setObjectImage(magazine, "Images/gun/5.png");
                bullet++;
                setTimer(timers, 0, 0.8f);
            }
        }
    }
    else if (object == rolling) {
        IsOnRolling = true;
        if (IsOnRolling == true) {
            IsOnRolling = false;
            playSound(effect[1]);
            player_bullet = rand() % 6;
            npc_bullet = rand() % 6;
            setTimer(timers, 1, 3);
        }
    }
    else if (object == change) {
        hideObject(gun[0]);
        hideObject(change);
        gun[1] = createObject("Images/gun/npcs.png", scene[5], 850, 450, true);
        hideObject(gun[2]);
        gun[3] = createObject("Images/gun/npcs-2.png", scene[5], 220, 80, true);

        setTimer(timers, 2, 0.5f);
    }
    else if (object == shot) {
        stopSound(effect[5]);
        enterScene(scene[2]);
        hideObject(shot);
        setObjectImage(gun[2], "Images/gun/npcs-1.png");
        playSound(effect[2]);
        setTimer(timers, 3, 1.0f);
    }
    else if (object == restart) {
        npcCount = 0, bullet = 0, player_bullet = 0, npc_bullet = 0;
        Easy = true;
        hideObject(gun[1]);
        hideObject(gun[0]);
        hideObject(npc[0]);
        hideObject(npc[1]);
        hideObject(npc[2]);
        hideObject(gun[2]);
        hideObject(gun[3]);

        for (int i = 0; i < 6; i++) {
            hideObject(message[i]);
        }

        enterScene(scene[0]);
    }
}

void timerCallback(TimerID timer) {
    if (timer == timers[0]) {
        hideObject(reload);
        hideObject(magazine);
        gun[0] = createObject("Images/gun/players.png", scene[5], 900, 450, true);
        rolling = createObject("Images/button/rolling.png", scene[5], 1000, 350, true);

    }
    else if (timer == timers[1]) {
        hideObject(rolling);
        change = createObject("Images/button/change.png", scene[5], 1000, 350, true);

    }
    else if (timer == timers[2]) {
        shot = createObject("Images/button/shot.png", scene[5], 900, 200, true);
    }
    else if (timer == timers[3]) {
        count = createObject("Images/count/3.png", scene[2], 950, 400, true);
        setTimer(timers, 4, 1.0f);
    }
    else if (timer == timers[4]) {
        setObjectImage(count, "Images/count/2.png");
        setTimer(timers, 5, 1.0f);
    }
    else if (timer == timers[5]) {
        setObjectImage(count, "Images/count/1.png");
        setTimer(timers, 6, 1.0f);
    }
    else if (timer == timers[6]) {
        setObjectImage(count, "Images/count/0.png");
        stopSound(effect[2]);
        setTimer(timers, 7, 0.2f);
    }
    else if (timer == timers[7]) {
        hideObject(count);
        result(player_bullet, npc_bullet);
    }
}
int main()
{
    srand(time(NULL));
    setMouseCallback(mouseCallback);
    setTimerCallback(timerCallback);
    settingGameOption();
    createGame();





    startGame(scene[0]);

}

