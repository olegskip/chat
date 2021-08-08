## Overview
This project definitely can be improved. It's not protected from hacking or etc. The server probably won't manage to deal with a large quantity of users. First of all it was created to get used with boost and mariadb. There is no feature to chat with somebody directly, so you can only send messages to the global chat. It doesn't have any tests
## Dependencies
1. Boost(tested with 1.76.0)
2. QT(tested with QT6)
3. mariadb(mysql can be used as well)
## How to build
There is two CMakeLists.txt. You should build the server and the client separately. For example how to build the server:
cd chat/server
cmake . && cmake --build build/