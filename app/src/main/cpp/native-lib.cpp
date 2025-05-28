#include <jni.h>
#include <string>
#include <memory>
#include "Maze.h"
#include "Ghost.h"
#include "BonusPoints.h"
#include "HighScore.h"

Ghost ghostWorker;

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_maze_MainActivity_getMap(
        JNIEnv* env,
        jobject /* this */) {

    shared_ptr<Maze> maze = Maze::instance();
    std::string map = maze->getMap();
    return env->NewStringUTF(map.c_str());
}

extern "C" JNIEXPORT jstring JNICALL
        Java_com_example_maze_MainActivity_getHighScore(
                JNIEnv* env,
                jobject /* this */) {
    shared_ptr<HighScore> score = HighScore::instance();
    string s = to_string(score->getHighScore());
    return env->NewStringUTF(s.c_str());
}

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_maze_MainActivity_isGameOver(
        JNIEnv* env,
        jobject /* this */) {
    shared_ptr<Maze> maze = Maze::instance();
    shared_ptr<HighScore> score = HighScore::instance();
    if(maze->isGameOver()){
        shared_ptr<BonusPoints> bonus = BonusPoints::instance();
        bonus->cancel();

        score->setHighScore(maze->getPoints());
        string highScore = to_string(score->getHighScore());
        string combined = "Game Over   high score  " + highScore;
        return env->NewStringUTF(combined.c_str());
    }
    else{
        int val = score->getHighScore();
        if(val > 0){
            string highScore = to_string(val);
            string combined = "high score  " + highScore;
            return env->NewStringUTF(combined.c_str());
        }
        else{
            return env->NewStringUTF("");
        }


    }
}


extern "C" JNIEXPORT void JNICALL
Java_com_example_maze_MainActivity_setMazeSize(JNIEnv* env, jobject /* this */,
                                               int width, int height) {

    shared_ptr<Maze> maze = Maze::instance();
    maze->newGame(width, height);

    shared_ptr<BonusPoints> bonus = BonusPoints::instance();
    bonus->createTimerThead();
}

extern "C" JNIEXPORT int JNICALL
Java_com_example_maze_MainActivity_moveItem(JNIEnv* env, jobject /* this */,
                                               int direction) {

    shared_ptr<Maze> maze = Maze::instance();
    int points = maze->moveItem(direction);
    pair<int,int> currPlayerPos = maze->getPlayerPosition();

    std::shared_ptr<newGhostPosition> data(new newGhostPosition());
    data->pos.first=currPlayerPos.first;
    data->pos.second= currPlayerPos.second;

    // Post the message to worker thread 1
    ghostWorker.createThread();
    ghostWorker.PostMsg(data);

    return points;
}
