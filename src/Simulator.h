/*The MIT License (MIT)

Copyright (c) 2016 Lucas Borsatto Simão

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
*/

#ifndef SIMULATOR_H_
#define SIMULATOR_H_

#include "Header.h"

#include "Physics.h"
#include "RobotStrategy.h"
#include "RobotPhysics.h"
#include "strategies/Strategy.h"

#include "strategies/ModelStrategy.h"
#include "VSS-Interface/cpp/interface.h"
#include "Arbiter.h"

class Simulator{
    struct GameState{
        vector<RobotStrategy*> robotStrategiesTeam;
        vector<RobotStrategy*> robotStrategiesAdv;
        bool sameState;

        GameState():sameState(true){};
    };

private:
    Arbiter arbiter;
    int contDebug;

    bool fast_travel;
    int qtd_of_goals;
    bool develop_mode;
    int status_team_1;
    int status_team_2;
    int goals_team_1;
    int goals_team_2;
    string name_team_1;
    string name_team_2;
    bool has_new_name_team_1;
    bool has_new_name_team_2;
    int port;
    string address;

    Report report;
    bool finish_match;
    float timeStep;
    float handTime;
    int simTime;
    int numRobotsTeam;
    bool runningPhysics;
    vector<Command> commands;

    vss_state::Global_State global_state;
    vss_command::Global_Commands global_commands_team_1, global_commands_team_2;
    Interface interface_sender;

    GameState* gameState;
    int stratStep;
    int loopBullet;
    int caseWorld;

	Physics* physics;
	vector<ModelStrategy*> strategies;

    thread *thread_physics;
    thread *thread_strategies;
    thread *thread_send;
    thread *thread_receive_team1;
    thread *thread_receive_team2;

    int count_situation, situation_team1, situation_team2;

	void updateWorld();
    void updateReport();
	btVector3 calcRelativePosition(btVector3 absPos, int attackDir);
	void calcRelativeWorld(vector<RobotStrategy*> robotStrategiesTeam, int attackDir);
	RobotStrategy* updateLocalPhysics(int id, RobotPhysics* bdRobot);


    btVector3 getRobotOrientation(RobotPhysics* robot);
    btVector3 getRobotPosition(RobotPhysics* robot);
    btVector3 getRobotVelocity(RobotPhysics* robot);

    //Auto simulation speed control:
    unsigned int delay;       //miliseconds
    unsigned int commandFreq; //miliseconds/command
    unsigned int desiredFreq; //miliseconds/command

    unsigned int calculateCommandFreq();
    unsigned int adjustDelay(unsigned int currentDelay, unsigned int currtFreq, unsigned int desiredFreq);

public:
	Simulator();
	void runSimulator(int argc, char *argv[], ModelStrategy* strategyTeam, ModelStrategy* strategyAdv, int rate, int qtd_goal, bool develop_mode, int port, bool randInit);

	void runPhysics();
	void runStrategies();
    void runSender();
    void runReceiveTeam1();
    void runReceiveTeam2();

    btVector3 getBallPosition();
};

#endif
