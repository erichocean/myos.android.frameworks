/*
 * Copyright 2014 myOS Group. All rights reserved.
 *
 */

typedef enum {
    MAPipeMessageEndOfMessage,
    MAPipeMessageHello,
    MAPipeMessageInt,
    MAPipeMessageCharString,
    MAPipeMessageScreenSize,
    MAPipeMessageData,
    MAPipeMessageWillEnterBackground,
    MAPipeMessageTerminateApp,
} MAPipeMessage;

typedef enum {
    MLPipeMessageEndOfMessage,
    MLPipeMessageChildIsReady,
    MLPipeMessageTerminateApp,
} MLPipeMessage;

void IOPipeSetPipes(int pipeRead, int pipeWrite);
NSString *IOPipeReadLine();
void IOPipeWriteLine(NSString *message);
void IOPipeWriteMessage(int message, BOOL withEnd);
void IOPipeWriteMessageWithPipe(int message, BOOL withEnd, int pipeWrite);
int IOPipeReadMessage();
int IOPipeReadMessageWithPipe(int pipeRead);
void IOPipeWriteCharString(NSString *aString);
NSString *IOPipeReadCharString();
void IOPipeWriteInt(int value);
void IOPipeWriteIntWithPipe(int value, int pipeWrite);
int IOPipeReadInt();
int IOPipeReadIntWithPipe(int pipeRead);
void IOPipeWriteFloat(float value);
void IOPipeWriteFloatWithPipe(float value, int pipeWrite);
float IOPipeReadFloat();
float IOPipeReadFloatWithPipe(int pipeRead);
void IOPipeWriteData(void *data, int size);
void IOPipeWriteDataWithPipe(void *data, int size, int pipeWrite);
void IOPipeReadData(void *data, int size);
void IOPipeReadDataWithPipe(void *data, int size, int pipeRead);
int IOPipeClosePipes();
NSString *IOPipeRunCommand(NSString *command, BOOL usingPipe);
