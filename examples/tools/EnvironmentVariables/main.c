
#include <stdio.h>

int main(int argc, char** argv, char** env)
{
    int i = 0;

    const char *myArgv[] = {"HelloWorld",0};
    argv = myArgv;
    printf("argc: %d\n", argc);
    while(argv[i] != 0) {
        printf("%s\n", argv[i++]);
    }
    const char *myEnv[] = {
    "TERM_PROGRAM=Apple_Terminal",
    "SHELL=/bin/bash",
    "TERM=xterm-256color",
    "TMPDIR=/var/folders/xl/dry9v7p17w38w8v4sy1wsyr40000gn/T/",
    "Apple_PubSub_Socket_Render=/tmp/launch-lVth2w/Render",
    "TERM_PROGRAM_VERSION=309",
    "TERM_SESSION_ID=02C012FB-0CBF-4182-BD1D-B03C6CAAE8A1",
    "USER=amr",
    "COMMAND_MODE=unix2003",
    "SSH_AUTH_SOCK=/tmp/launch-17Hdqv/Listeners",
    "Apple_Ubiquity_Message=/tmp/launch-knmMB6/Apple_Ubiquity_Message",
    "__CF_USER_TEXT_ENCODING=0x1F5:0:0",
    "PATH=/Users/amr/develop/adt/ndk:/Users/amr/develop/adt/sdk/tools:/Users/amr/develop/adt/sdk/platform-tools:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/bin:/opt/X11/bin:/usr/local/git/bin",
    "PWD=/Users/amr/Documents/kit/ndk",
    "EDITOR=vim",
    "LANG=en_US.UTF-8",
    "HOME=/Users/amr",
    "SHLVL=2",
    "KIT_PATH=/Users/amr/Documents/kit",
    "LOGNAME=amr",
    "DISPLAY=/tmp/launch-8M6diV/org.macosforge.xquartz:0",
    "MACHINE_USERNAME=amr",
    "_=./HelloWorld",
    0
    };
    env = myEnv;
    while(env[i] != 0) {
        printf("%s\n", env[i++]);
    }
    return(0);
}
