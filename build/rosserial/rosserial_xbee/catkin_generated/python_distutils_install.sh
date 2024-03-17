#!/bin/sh

if [ -n "$DESTDIR" ] ; then
    case $DESTDIR in
        /*) # ok
            ;;
        *)
            /bin/echo "DESTDIR argument must be absolute... "
            /bin/echo "otherwise python's distutils will bork things."
            exit 1
    esac
fi

echo_and_run() { echo "+ $@" ; "$@" ; }

echo_and_run cd "/home/psychedelic/mantis/src/rosserial/rosserial_xbee"

# ensure that Python install destination exists
echo_and_run mkdir -p "$DESTDIR/home/psychedelic/mantis/install/lib/python3/dist-packages"

# Note that PYTHONPATH is pulled from the environment to support installing
# into one location when some dependencies were installed in another
# location, #123.
echo_and_run /usr/bin/env \
    PYTHONPATH="/home/psychedelic/mantis/install/lib/python3/dist-packages:/home/psychedelic/mantis/build/lib/python3/dist-packages:$PYTHONPATH" \
    CATKIN_BINARY_DIR="/home/psychedelic/mantis/build" \
    "/usr/bin/python3" \
    "/home/psychedelic/mantis/src/rosserial/rosserial_xbee/setup.py" \
     \
    build --build-base "/home/psychedelic/mantis/build/rosserial/rosserial_xbee" \
    install \
    --root="${DESTDIR-/}" \
    --install-layout=deb --prefix="/home/psychedelic/mantis/install" --install-scripts="/home/psychedelic/mantis/install/bin"
