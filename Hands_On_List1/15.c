/*
============================================================================
Name : 15.c
Author : SHASHANK VYAS
Description : Write a C ,Ansi-style program to display the environmental variable of the user (use environ).
Date: 30th Aug, 2024.
============================================================================
*/

#include <stdio.h>

extern char **environ;

int main() {
    char **env = environ;

    // Loop through the environment variables and print them
    while (*env) {
        printf("%s\n", *env);
        env++;
    }

    return 0;
}

/*
    shashank@ubuntu-22:~/Documents/SYS$ ./15
    SHELL=/bin/bash
    SESSION_MANAGER=local/ubuntu-22:@/tmp/.ICE-unix/1807,unix/ubuntu-22:/tmp/.ICE-unix/1807
    QT_ACCESSIBILITY=1
    COLORTERM=truecolor
    XDG_CONFIG_DIRS=/etc/xdg/xdg-ubuntu:/etc/xdg
    SSH_AGENT_LAUNCHER=openssh
    XDG_MENU_PREFIX=gnome-
    TERM_PROGRAM_VERSION=1.92.2
    XDG_CONFIG_DIRS_VSCODE_SNAP_ORIG=/etc/xdg/xdg-ubuntu:/etc/xdg
    GNOME_DESKTOP_SESSION_ID=this-is-deprecated
    GNOME_KEYRING_CONTROL=/run/user/1000/keyring
    GDK_BACKEND_VSCODE_SNAP_ORIG=
    LANGUAGE=en_IN:en
    GIO_MODULE_DIR_VSCODE_SNAP_ORIG=
    GNOME_SHELL_SESSION_MODE=ubuntu
    SSH_AUTH_SOCK=/run/user/1000/keyring/ssh
    XMODIFIERS=@im=ibus
    DESKTOP_SESSION=ubuntu
    GTK_MODULES=gail:atk-bridge
    PWD=/home/shashank/Documents/SYS
    GSETTINGS_SCHEMA_DIR=/home/shashank/snap/code/167/.local/share/glib-2.0/schemas
    XDG_SESSION_DESKTOP=ubuntu
    LOGNAME=shashank
    GTK_EXE_PREFIX=/snap/code/167/usr
    XDG_SESSION_TYPE=wayland
    SYSTEMD_EXEC_PID=2005
    XAUTHORITY=/run/user/1000/.mutter-Xwaylandauth.C6CWS2
    VSCODE_GIT_ASKPASS_NODE=/snap/code/167/usr/share/code/code
    HOME=/home/shashank
    USERNAME=shashank
    IM_CONFIG_PHASE=1
    LANG=en_US.UTF-8
    LS_COLORS=rs=0:di=01;34:ln=01;36:mh=00:pi=40;33:so=01;35:do=01;35:bd=40;33;01:cd=40;33;01:or=40;31;01:mi=00:su=37;41:sg=30;43:ca=30;41:tw=30;42:ow=34;42:st=37;44:ex=01;32:*.tar=01;31:*.tgz=01;31:*.arc=01;31:*.arj=01;31:*.taz=01;31:*.lha=01;31:*.lz4=01;31:*.lzh=01;31:*.lzma=01;31:*.tlz=01;31:*.txz=01;31:*.tzo=01;31:*.t7z=01;31:*.zip=01;31:*.z=01;31:*.dz=01;31:*.gz=01;31:*.lrz=01;31:*.lz=01;31:*.lzo=01;31:*.xz=01;31:*.zst=01;31:*.tzst=01;31:*.bz2=01;31:*.bz=01;31:*.tbz=01;31:*.tbz2=01;31:*.tz=01;31:*.deb=01;31:*.rpm=01;31:*.jar=01;31:*.war=01;31:*.ear=01;31:*.sar=01;31:*.rar=01;31:*.alz=01;31:*.ace=01;31:*.zoo=01;31:*.cpio=01;31:*.7z=01;31:*.rz=01;31:*.cab=01;31:*.wim=01;31:*.swm=01;31:*.dwm=01;31:*.esd=01;31:*.jpg=01;35:*.jpeg=01;35:*.mjpg=01;35:*.mjpeg=01;35:*.gif=01;35:*.bmp=01;35:*.pbm=01;35:*.pgm=01;35:*.ppm=01;35:*.tga=01;35:*.xbm=01;35:*.xpm=01;35:*.tif=01;35:*.tiff=01;35:*.png=01;35:*.svg=01;35:*.svgz=01;35:*.mng=01;35:*.pcx=01;35:*.mov=01;35:*.mpg=01;35:*.mpeg=01;35:*.m2v=01;35:*.mkv=01;35:*.webm=01;35:*.webp=01;35:*.ogm=01;35:*.mp4=01;35:*.m4v=01;35:*.mp4v=01;35:*.vob=01;35:*.qt=01;35:*.nuv=01;35:*.wmv=01;35:*.asf=01;35:*.rm=01;35:*.rmvb=01;35:*.flc=01;35:*.avi=01;35:*.fli=01;35:*.flv=01;35:*.gl=01;35:*.dl=01;35:*.xcf=01;35:*.xwd=01;35:*.yuv=01;35:*.cgm=01;35:*.emf=01;35:*.ogv=01;35:*.ogx=01;35:*.aac=00;36:*.au=00;36:*.flac=00;36:*.m4a=00;36:*.mid=00;36:*.midi=00;36:*.mka=00;36:*.mp3=00;36:*.mpc=00;36:*.ogg=00;36:*.ra=00;36:*.wav=00;36:*.oga=00;36:*.opus=00;36:*.spx=00;36:*.xspf=00;36:
    XDG_CURRENT_DESKTOP=Unity
    VTE_VERSION=7000
    WAYLAND_DISPLAY=wayland-0
    GIT_ASKPASS=/snap/code/167/usr/share/code/resources/app/extensions/git/dist/askpass.sh
    GNOME_TERMINAL_SCREEN=/org/gnome/Terminal/screen/46156493_7bad_4bec_917c_3344d4236ddb
    CHROME_DESKTOP=code-url-handler.desktop
    VSCODE_GIT_ASKPASS_EXTRA_ARGS=
    GNOME_SETUP_DISPLAY=:1
    GSETTINGS_SCHEMA_DIR_VSCODE_SNAP_ORIG=
    GTK_IM_MODULE_FILE_VSCODE_SNAP_ORIG=
    LESSCLOSE=/usr/bin/lesspipe %s %s
    XDG_SESSION_CLASS=user
    TERM=xterm-256color
    GTK_PATH=/snap/code/167/usr/lib/x86_64-linux-gnu/gtk-3.0
    LESSOPEN=| /usr/bin/lesspipe %s
    USER=shashank
    GTK_PATH_VSCODE_SNAP_ORIG=
    VSCODE_GIT_IPC_HANDLE=/run/user/1000/vscode-git-9d1572ceac.sock
    GNOME_TERMINAL_SERVICE=:1.129
    DISPLAY=:0
    SHLVL=2
    LOCPATH=/snap/code/167/usr/lib/locale
    QT_IM_MODULE=ibus
    GTK_EXE_PREFIX_VSCODE_SNAP_ORIG=
    XDG_RUNTIME_DIR=/run/user/1000
    XDG_DATA_DIRS_VSCODE_SNAP_ORIG=/usr/share/ubuntu:/usr/local/share/:/usr/share/:/var/lib/snapd/desktop
    DEBUGINFOD_URLS=https://debuginfod.ubuntu.com 
    VSCODE_GIT_ASKPASS_MAIN=/snap/code/167/usr/share/code/resources/app/extensions/git/dist/askpass-main.js
    XDG_DATA_DIRS=/home/shashank/snap/code/167/.local/share:/home/shashank/snap/code/167:/snap/code/167/usr/share:/usr/share/ubuntu:/usr/local/share/:/usr/share/:/var/lib/snapd/desktop
    GDK_BACKEND=x11
    PATH=/home/shashank/.local/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin:/snap/bin
    GDMSESSION=ubuntu
    ORIGINAL_XDG_CURRENT_DESKTOP=ubuntu:GNOME
    DBUS_SESSION_BUS_ADDRESS=unix:path=/run/user/1000/bus
    GTK_IM_MODULE_FILE=/home/shashank/snap/code/common/.cache/immodules/immodules.cache
    LOCPATH_VSCODE_SNAP_ORIG=
    GIO_MODULE_DIR=/home/shashank/snap/code/common/.cache/gio-modules
    TERM_PROGRAM=vscode
    _=./15
*/

